// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.classes;

import otava.ast;
import otava.symbols.class_group.symbol;
import otava.symbols.context;
import otava.symbols.emitter;
import otava.symbols.exception;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.templates;
import otava.symbols.visitor;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.type.resolver;
import otava.symbols.statement.binder;
import otava.symbols.variable.symbol;
import otava.symbols.function.symbol;
import otava.symbols.overload.resolution;
import otava.symbols.argument.conversion.table;
import otava.symbols.fundamental.type.operation;
import otava.symbols.function.group.symbol;
import otava.symbols.declaration;
import util.unicode;
import util.sha1;

namespace otava::symbols {

void GenerateDestructor(ClassTypeSymbol* classTypeSymbol, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);

int32_t GetSpecialFunctionIndex(SpecialFunctionKind specialFunctionKind)
{
    switch (specialFunctionKind)
    {
        case SpecialFunctionKind::defaultCtor:
        {
            return defaultCtorIndex;
        }
        case SpecialFunctionKind::copyCtor:
        {
            return copyCtorIndex;
        }
        case SpecialFunctionKind::moveCtor:
        {
            return moveCtorIndex;
        }
        case SpecialFunctionKind::copyAssignment:
        {
            return copyAssignmentIndex;
        }
        case SpecialFunctionKind::moveAssignment:
        {
            return moveAssignmentIndex;
        }
        case SpecialFunctionKind::dtor:
        {
            return destructorIndex;
        }
    }
    return 0;
}


RecordedParseCompoundStatementFn recordedParseCompoundStatementFn = nullptr;

void SetRecordedParseCompoundStatementFn(RecordedParseCompoundStatementFn fn)
{
    recordedParseCompoundStatementFn = fn;
}

void RecordedParseCompoundStatement(otava::ast::CompoundStatementNode* compoundStatementNode, Context* context)
{
    if (recordedParseCompoundStatementFn)
    {
        recordedParseCompoundStatementFn(compoundStatementNode, context);
    }
}

RecordedParseCtorInitializerFn recordedParseInitializerFn = nullptr;

void SetRecordedParseCtorInitializerFn(RecordedParseCtorInitializerFn fn)
{
    recordedParseInitializerFn = fn;
}

void RecordedParseCtorInitializer(otava::ast::ConstructorInitializerNode* ctorInitializerNode, Context* context)
{
    recordedParseInitializerFn(ctorInitializerNode, context);
}

ClassTypeSymbol::ClassTypeSymbol(const std::u32string& name_) : 
    TypeSymbol(SymbolKind::classTypeSymbol, name_), 
    flags(ClassTypeSymbolFlags::none),
    classKind(ClassKind::class_), 
    specialization(nullptr),
    level(0), 
    irType(nullptr),
    currentFunctionIndex(1),
    specializationId(),
    vtabSize(0),
    vptrIndex(-1),
    vtabVariable(nullptr)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

ClassTypeSymbol::ClassTypeSymbol(SymbolKind kind_, const std::u32string& name_) : 
    TypeSymbol(kind_, name_),
    flags(ClassTypeSymbolFlags::none),
    classKind(ClassKind::class_),
    specialization(nullptr),
    level(0),
    irType(nullptr),
    currentFunctionIndex(1),
    specializationId(),
    vtabSize(0),
    vptrIndex(-1),
    vtabVariable(nullptr)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

bool ClassTypeSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope: 
        case ScopeKind::templateDeclarationScope: 
        case ScopeKind::classScope: 
        case ScopeKind::blockScope: 
        {
            return true;
        }
    }
    return false;
}

void ClassTypeSymbol::AddBaseClass(ClassTypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context)
{
    baseClasses.push_back(baseClass);
    GetScope()->AddBaseScope(baseClass->GetScope(), sourcePos, context);
}

void ClassTypeSymbol::AddDerivedClass(ClassTypeSymbol* derivedClass)
{
    if (std::find(derivedClasses.begin(), derivedClasses.end(), derivedClass) == derivedClasses.end())
    {
        derivedClasses.push_back(derivedClass);
    }
}

bool ClassTypeSymbol::HasBaseClass(TypeSymbol* baseClass, int& distance) const
{
    for (const auto& baseCls : baseClasses)
    {
        if (TypesEqual(baseCls, baseClass))
        {
            ++distance;
            return true;
        }
        else 
        {
            ++distance;
            if (baseCls->HasBaseClass(baseClass, distance))
            {
                return true;
            }
            --distance;
        }
    }
    return false;
}

bool ClassTypeSymbol::HasPolymorphicBaseClass() const
{
    for (const auto& baseCls : baseClasses)
    {
        if (baseCls->IsPolymorphic())
        {
            return true;
        }
    }
    return false;
}

void ClassTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ClassTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(flags));
    uint32_t nb = baseClasses.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(nb);
    for (const auto& baseClass : baseClasses)
    {
        writer.GetBinaryStreamWriter().Write(baseClass->Id());
    }
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(classKind));
    util::uuid specializationId = util::nil_uuid();
    if (specialization)
    {
        specializationId = specialization->Id();
    }
    writer.GetBinaryStreamWriter().Write(specializationId);
    writer.GetBinaryStreamWriter().Write(level);
    writer.GetBinaryStreamWriter().WriteULEB128UInt(objectLayout.size());
    for (const auto& type : objectLayout)
    {
        writer.GetBinaryStreamWriter().Write(type->Id());
    }
    uint32_t nfm = functionMap.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(nfm);
    for (const auto& fn : functionMap)
    {
        writer.GetBinaryStreamWriter().Write(fn.first);
        writer.GetBinaryStreamWriter().Write(fn.second->Id());
    }
    writer.GetBinaryStreamWriter().Write(vtabSize);
    writer.GetBinaryStreamWriter().Write(vptrIndex);
}

void ClassTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    flags = static_cast<ClassTypeSymbolFlags>(reader.GetBinaryStreamReader().ReadByte());
    uint32_t nb = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < nb; ++i)
    {
        util::uuid baseClassId;
        reader.GetBinaryStreamReader().ReadUuid(baseClassId);
        baseClassIds.push_back(baseClassId);
    }
    classKind = static_cast<ClassKind>(reader.GetBinaryStreamReader().ReadByte());
    reader.GetBinaryStreamReader().ReadUuid(specializationId);
    level = reader.GetBinaryStreamReader().ReadInt();
    uint32_t nol = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < nol; ++i)
    {
        util::uuid tid;
        reader.GetBinaryStreamReader().ReadUuid(tid);
        objectLayoutIds.push_back(tid);
    }
    uint32_t nfm = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < nfm; ++i)
    {
        int32_t fnIndex = reader.GetBinaryStreamReader().ReadInt();
        util::uuid fnId;
        reader.GetBinaryStreamReader().ReadUuid(fnId);
        functionIdMap[fnIndex] = fnId;
    }
    vtabSize = reader.GetBinaryStreamReader().ReadInt();
    vptrIndex = reader.GetBinaryStreamReader().ReadInt();
}

void ClassTypeSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    for (const util::uuid& baseClassId : baseClassIds)
    {
        Symbol* baseClassSymbol = symbolTable.GetSymbolMap()->GetSymbol(baseClassId);
        if (baseClassSymbol->IsClassTypeSymbol())
        {
            GetScope()->AddBaseScope(baseClassSymbol->GetScope(), soul::ast::SourcePos(), nullptr);
            baseClasses.push_back(static_cast<ClassTypeSymbol*>(baseClassSymbol));
        }
    }
    if (specializationId != util::nil_uuid())
    {
        specialization = symbolTable.GetType(specializationId);
    }
    for (const auto& tid : objectLayoutIds)
    {
        TypeSymbol* type = symbolTable.GetType(tid);
        objectLayout.push_back(type);
    }
    for (const auto& fnIndexId : functionIdMap)
    {
        FunctionSymbol* function = symbolTable.GetFunction(fnIndexId.second);
        if (!function)
        {
            function = symbolTable.GetFunctionDefinition(fnIndexId.second);
        }
        functionMap[fnIndexId.first] = function;
    }
}

bool ClassTypeSymbol::IsPolymorphic() const
{
    for (const auto& baseClass : baseClasses)
    {
        if (baseClass->IsPolymorphic()) return true;
    }
    for (const auto& memberFunction : memberFunctions)
    {
        if (memberFunction->IsVirtual()) return true;
    }
    return false;
}

void ClassTypeSymbol::MakeObjectLayout(Context* context)
{
    if (ObjectLayoutComputed()) return;
    SetObjectLayoutComputed();
    for (const auto& baseClass : baseClasses)
    {
        baseClass->MakeObjectLayout(context);
        objectLayout.push_back(baseClass);
    }
    if (baseClasses.empty())
    {
        if (IsPolymorphic())
        {
            SetVPtrIndex(objectLayout.size());
            objectLayout.push_back(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType)->AddPointer(context));
        }
        else if (memberVariables.empty())
        {
            objectLayout.push_back(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedCharType));
        }
    }
    for (const auto& memberVar : memberVariables)
    {
        int32_t layoutIndex = objectLayout.size();
        memberVar->SetLayoutIndex(layoutIndex);
        objectLayout.push_back(memberVar->GetType());
    }
}

TemplateDeclarationSymbol* ClassTypeSymbol::ParentTemplateDeclaration() const
{
    Symbol* parentSymbol = const_cast<ClassTypeSymbol*>(this)->Parent();
    if (parentSymbol && parentSymbol->IsTemplateDeclarationSymbol())
    {
        return static_cast<TemplateDeclarationSymbol*>(parentSymbol);
    }
    return nullptr;
}

bool ClassTypeSymbol::IsTemplate() const
{
    return ParentTemplateDeclaration() != nullptr;
}

void ClassTypeSymbol::MakeVTab(Context* context, const soul::ast::SourcePos& sourcePos)
{
    if (baseClasses.size() > 1)
    {
        otava::symbols::SetExceptionThrown();
        throw std::runtime_error("multiple inheritance not supported yet, class is '" + util::ToUtf8(Name()) + "'");
    }
    InitVTab(vtab, context, sourcePos);
    vtabSize = vtab.size();
}

bool Overrides(FunctionSymbol* f, FunctionSymbol* g)
{
    if (f->GroupName() == g->GroupName())
    {
        int n = f->Parameters().size();
        if (n == g->Parameters().size())
        {
            for (int i = 0; i < n; ++i)
            {
                ParameterSymbol* p = f->Parameters()[i];
                ParameterSymbol* q = g->Parameters()[i];
                if (!TypesEqual(p->GetType(), q->GetType())) return false;
            }
            return true;
        }
    }
    return false;
}

void ClassTypeSymbol::InitVTab(std::vector<FunctionSymbol*>& vtab, Context* context, const soul::ast::SourcePos& sourcePos)
{
    if (!IsPolymorphic()) return;
    if (!baseClasses.empty())
    {
        ClassTypeSymbol* baseClass = baseClasses[0];
        baseClass->InitVTab(vtab, context, sourcePos);
    }
    std::vector<FunctionSymbol*> virtualFunctions;
    for (const auto& function : memberFunctions)
    {
        if (function->IsVirtual())
        {
            virtualFunctions.push_back(function);
        }
    }
    int n = virtualFunctions.size();
    for (int i = 0; i < n; ++i)
    {
        FunctionSymbol* f = virtualFunctions[i];
        bool found = false;
        int m = vtab.size();
        for (int j = 0; j < m; ++j)
        {
            FunctionSymbol* v = vtab[j];
            if (Overrides(f, v))
            {
                if (!f->IsOverride())
                {
                    ThrowException("overriding function should be declared with override specifier: (" + 
                        util::ToUtf8(f->FullName()) + " overrides " + util::ToUtf8(v->FullName()) + ")", sourcePos, context);
                }
                f->SetVTabIndex(j);
                vtab[j] = f;
                found = true;
                break;
            }
        }
        if (!found)
        {
            if (f->IsOverride())
            {
                ThrowException("no suitable function to override ('" + util::ToUtf8(f->FullName()) + "')", sourcePos, context);
            }
            f->SetVTabIndex(m);
            vtab.push_back(f);
        }
    }
}

std::string ClassTypeSymbol::IrName(Context* context) const
{
    std::string irName;
    irName.append("class_").append(util::ToUtf8(Name()));
    std::string fullName = util::ToUtf8(FullName());
    irName.append("_").append(util::GetSha1MessageDigest(fullName));
    return irName;
}

std::string ClassTypeSymbol::VTabName(Context* context) const
{
    std::string vtabName;
    vtabName.append("vtab_").append(IrName(context));
    return vtabName;
}

void ClassTypeSymbol::SetVTabVariable(otava::intermediate::Value* vtabVariable_)
{
    vtabVariable = vtabVariable_;
}

otava::intermediate::Type* ClassTypeSymbol::VPtrType(Emitter& emitter) const
{
    otava::intermediate::Type* voidPtrIrType = emitter.MakePtrType(emitter.GetVoidType());
    otava::intermediate::Type* vptrType = emitter.MakePtrType(emitter.MakeArrayType(vtabSize * 2 + otava::symbols::vtabClassIdElementCount, voidPtrIrType));
    return vptrType;
}

otava::intermediate::Value* ClassTypeSymbol::GetVTabVariable(Emitter& emitter, Context* context)
{
    if (!vtabVariable)
    {
        otava::intermediate::Type* voidPtrIrType = emitter.MakePtrType(emitter.GetVoidType());
        otava::intermediate::Type* arrayType = emitter.MakeArrayType(vtabSize * 2 + otava::symbols::vtabClassIdElementCount, voidPtrIrType);
        vtabVariable = emitter.EmitGlobalVariable(arrayType, VTabName(context), nullptr);
    }
    return vtabVariable;
}

ClassTypeSymbol* ClassTypeSymbol::VPtrHolderClass() const
{
    if (vptrIndex != -1)
    {
        return const_cast<ClassTypeSymbol*>(this);
    }
    else
    {
        for (const auto& baseClass : baseClasses)
        {
            ClassTypeSymbol* vptrHolderBaseClass = baseClass->VPtrHolderClass();
            if (vptrHolderBaseClass)
            {
                return vptrHolderBaseClass;
            }
        }
    }
    return nullptr;
}

int ClassTypeSymbol::Arity() 
{
    TemplateDeclarationSymbol* templateDeclaration = ParentTemplateDeclaration();
    if (templateDeclaration)
    {
        return templateDeclaration->Arity();
    }
    else
    {
        return 0;
    }
}

void ClassTypeSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol::AddSymbol(symbol, sourcePos, context);
    if (symbol->IsVariableSymbol())
    {
        VariableSymbol* memberVariable = static_cast<VariableSymbol*>(symbol);
        if ((symbol->GetDeclarationFlags() & DeclarationFlags::staticFlag) != DeclarationFlags::none)
        {
            staticMemberVariables.push_back(memberVariable);
        }
        else
        {
            memberVariable->SetIndex(memberVariables.size());
            memberVariables.push_back(memberVariable);
        }
    }
    else if (symbol->IsFunctionSymbol())
    {
        memberFunctions.push_back(static_cast<FunctionSymbol*>(symbol));
    }
    if (symbol->IsFunctionDefinitionSymbol())
    {
        FunctionDefinitionSymbol* memFunDefSymbol = static_cast<FunctionDefinitionSymbol*>(symbol);
        if (memFunDefSymbol->DefIndex() == -1)
        {
            memFunDefSymbol->SetDefIndex(memFunDefSymbols.size());
            memFunDefSymbols.push_back(memFunDefSymbol);
        }
        else
        {
            while (memFunDefSymbol->DefIndex() >= memFunDefSymbols.size())
            {
                memFunDefSymbols.push_back(nullptr);
            }
            memFunDefSymbols[memFunDefSymbol->DefIndex()] = memFunDefSymbol;
        }
    }
}

otava::intermediate::Type* ClassTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Type* irType = emitter.GetType(Id());
    if (!irType)
    {
        MakeObjectLayout(context);
        std::vector<otava::intermediate::Type*> elementTypes;
        int n = objectLayout.size();
        for (int i = 0; i < n; ++i)
        {
            TypeSymbol* type = objectLayout[i];
            elementTypes.push_back(type->IrType(emitter, sourcePos, context));
        }
        irType = emitter.MakeStructureType(elementTypes);
        emitter.SetType(Id(), irType);
    }
    return irType;
}

int32_t ClassTypeSymbol::NextFunctionIndex()
{
    return currentFunctionIndex++;
}

void ClassTypeSymbol::MapFunction(FunctionSymbol* function)
{
    functionMap[function->Index()] = function;
}

FunctionSymbol* ClassTypeSymbol::GetFunction(int32_t functionIndex) const
{
    auto it = functionMap.find(functionIndex);
    if (it != functionMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

ForwardClassDeclarationSymbol::ForwardClassDeclarationSymbol(const std::u32string& name_) : 
    TypeSymbol(SymbolKind::forwardClassDeclarationSymbol, name_), 
    classKind(ClassKind::class_),
    specialization(nullptr),
    classTypeSymbol(nullptr),
    classTypeSymbolId()
{
    GetScope()->SetKind(ScopeKind::classScope);
}

bool ForwardClassDeclarationSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope:
        case ScopeKind::templateDeclarationScope:
        case ScopeKind::classScope:
        case ScopeKind::blockScope:
        {
            return true;
        }
    }
    return false;
}

TemplateDeclarationSymbol* ForwardClassDeclarationSymbol::ParentTemplateDeclaration()
{
    Symbol* parentSymbol = Parent();
    if (parentSymbol->IsTemplateDeclarationSymbol())
    {
        return static_cast<TemplateDeclarationSymbol*>(parentSymbol);
    }
    return nullptr;
}

void ForwardClassDeclarationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ForwardClassDeclarationSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(classKind));
    writer.GetBinaryStreamWriter().Write(classTypeSymbol != nullptr);
    if (classTypeSymbol)
    {
        writer.GetBinaryStreamWriter().Write(classTypeSymbol->Id());
    }
}

void ForwardClassDeclarationSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    classKind = static_cast<ClassKind>(reader.GetBinaryStreamReader().ReadByte());
    bool hasClassType = reader.GetBinaryStreamReader().ReadBool();
    if (hasClassType)
    {
        reader.GetBinaryStreamReader().ReadUuid(classTypeSymbolId);
    }
}

void ForwardClassDeclarationSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    if (classTypeSymbolId != util::nil_uuid())
    {
        TypeSymbol* type = symbolTable.GetType(classTypeSymbolId);
        if (type->IsClassTypeSymbol())
        {
            classTypeSymbol = static_cast<ClassTypeSymbol*>(type);
        }
        else
        {
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("otava.symbols.classes: class type expected");
        }
    }
}

int ForwardClassDeclarationSymbol::Arity()
{
    TemplateDeclarationSymbol* templateDeclaration = ParentTemplateDeclaration();
    if (templateDeclaration)
    {
        return templateDeclaration->Arity();
    }
    else
    {
        return 0;
    }
}

class ClassResolver : public otava::ast::DefaultVisitor
{
public:
    ClassResolver(Context* context_);
    std::u32string GetName() const { return name; }
    otava::symbols::ClassKind GetClassKind() const { return classKind; }
    TypeSymbol* Specialization() const { return specialization; }
    void Visit(otava::ast::ClassSpecifierNode& node) override;
    void Visit(otava::ast::ClassHeadNode& node) override;
    void Visit(otava::ast::ElaboratedTypeSpecifierNode& node) override;
    void Visit(otava::ast::ClassNode& node) override;
    void Visit(otava::ast::StructNode& node) override;
    void Visit(otava::ast::UnionNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::TemplateIdNode& node) override;
private:
    Context* context;
    std::u32string name;
    otava::symbols::ClassKind classKind;
    TypeSymbol* specialization;
};

ClassResolver::ClassResolver(Context* context_) : context(context_), classKind(otava::symbols::ClassKind::class_), specialization(nullptr)
{
}

void ClassResolver::Visit(otava::ast::ClassSpecifierNode& node)
{
    node.ClassHead()->Accept(*this);
}

void ClassResolver::Visit(otava::ast::ClassHeadNode& node)
{
    node.ClassKey()->Accept(*this);
    node.ClassHeadName()->Accept(*this);
}

void ClassResolver::Visit(otava::ast::IdentifierNode& node)
{
    name = node.Str();
}

void ClassResolver::Visit(otava::ast::TemplateIdNode& node)
{
    node.TemplateName()->Accept(*this);
    specialization = ResolveType(&node, DeclarationFlags::none, context, TypeResolverFlags::dontInstantiate);
}

void ClassResolver::Visit(otava::ast::ElaboratedTypeSpecifierNode& node)
{
    node.ClassKey()->Accept(*this);
    name = node.Id()->Str();
}

void ClassResolver::Visit(otava::ast::ClassNode& node)
{
    classKind = otava::symbols::ClassKind::class_;
}

void ClassResolver::Visit(otava::ast::StructNode& node)
{
    classKind = otava::symbols::ClassKind::struct_;
}

void ClassResolver::Visit(otava::ast::UnionNode& node)
{
    classKind = otava::symbols::ClassKind::union_;
}

class BaseClassResolver : public otava::ast::DefaultVisitor
{
public:
    BaseClassResolver(Context* context_);
    void Visit(otava::ast::BaseSpecifierNode& node) override;
private:
    Context* context;
};

BaseClassResolver::BaseClassResolver(Context* context_) : context(context_)
{
}

void BaseClassResolver::Visit(otava::ast::BaseSpecifierNode& node)
{
    TypeSymbol* baseClassType = ResolveType(node.ClassOrDeclType(), DeclarationFlags::none, context);
    if (baseClassType->IsClassTypeSymbol())
    {
        ClassTypeSymbol* baseClass = static_cast<ClassTypeSymbol*>(baseClassType);
        context->GetSymbolTable()->AddBaseClass(baseClass, node.GetSourcePos(), context);
    }
    else
    {
        ThrowException("class type symbol expected", node.GetSourcePos(), context);
    }
}

void GetClassAttributes(otava::ast::Node* node, std::u32string& name, otava::symbols::ClassKind& kind, TypeSymbol*& specialization, Context* context)
{
    ClassResolver resolver(context);
    node->Accept(resolver);
    name = resolver.GetName();
    kind = resolver.GetClassKind();
    specialization = resolver.Specialization();
}

void BeginClass(otava::ast::Node* node, otava::symbols::Context* context)
{
    std::u32string name;
    otava::symbols::ClassKind kind;
    TypeSymbol* specialization = nullptr;
    GetClassAttributes(node, name, kind, specialization, context);
    context->GetSymbolTable()->BeginClass(name, kind, specialization, node, context);
    BaseClassResolver resolver(context);
    node->Accept(resolver);
    context->PushSetFlag(ContextFlags::parseMemberFunction);
}

void EndClass(otava::ast::Node* node, otava::symbols::Context* context)
{
    Symbol* symbol = context->GetSymbolTable()->CurrentScope()->GetSymbol();
    if (!symbol->IsClassTypeSymbol())
    {
        ThrowException("cpp20.symbols.classes: EndClass(): class scope expected", node->GetSourcePos(), context);
    }
    ClassTypeSymbol* classTypeSymbol = static_cast<ClassTypeSymbol*>(symbol);
    otava::ast::Node* specNode = context->GetSymbolTable()->GetSpecifierNode(classTypeSymbol);
    if (specNode && specNode->IsClassSpecifierNode())
    {
        otava::ast::ClassSpecifierNode* specifierNode = static_cast<otava::ast::ClassSpecifierNode*>(specNode);
        specifierNode->SetComplete();
    }
    else
    {
        ThrowException("otava.symbols.classes: EndClass(): class specifier node expected", node->GetSourcePos(), context);
    }
    if (!classTypeSymbol->IsTemplate() && !classTypeSymbol->HasUserDefinedDestructor())
    {
        GenerateDestructor(classTypeSymbol, node->GetSourcePos(), context);
    }
    context->PopFlags();
    context->GetSymbolTable()->EndClass();
    if (classTypeSymbol->Level() == 0)
    {
        ParseInlineMemberFunctions(specNode, classTypeSymbol, context);
    }
    if (!classTypeSymbol->IsTemplate())
    {
        context->GetBoundCompileUnit()->AddBoundNode(new BoundClassNode(classTypeSymbol, node->GetSourcePos()));
    }
}

void AddForwardClassDeclaration(otava::ast::Node* node, otava::symbols::Context* context)
{
    std::u32string name;
    otava::symbols::ClassKind kind;
    TypeSymbol* specialization = nullptr;
    GetClassAttributes(node, name, kind, specialization, context);
    context->GetSymbolTable()->AddForwardClassDeclaration(name, kind, specialization, node, context);
}

void SetCurrentAccess(otava::ast::Node* node, otava::symbols::Context* context)
{
    switch (node->Kind())
    {
        case otava::ast::NodeKind::publicNode:
        {
            context->GetSymbolTable()->SetCurrentAccess(Access::public_);
            break;
        }
        case otava::ast::NodeKind::protectedNode:
        {
            context->GetSymbolTable()->SetCurrentAccess(Access::protected_);
            break;
        }
        case otava::ast::NodeKind::privateNode:
        {
            context->GetSymbolTable()->SetCurrentAccess(Access::private_);
            break;
        }
    }
}

class InlineMemberFunctionParserVisitor : public otava::ast::DefaultVisitor
{
public:
    InlineMemberFunctionParserVisitor(Context* context_);
    void Visit(otava::ast::FunctionDefinitionNode& node) override;
private:
    Context* context;
};

InlineMemberFunctionParserVisitor::InlineMemberFunctionParserVisitor(Context* context_) : context(context_)
{
}

void InlineMemberFunctionParserVisitor::Visit(otava::ast::FunctionDefinitionNode& node)
{
    try
    {
        Symbol* symbol = context->GetSymbolTable()->GetSymbol(&node);
        otava::ast::Node* fnBody = node.FunctionBody();
        otava::ast::ConstructorInitializerNode* ctorInitializerNode = nullptr;
        otava::ast::CompoundStatementNode* compoundStatementNode = nullptr;
        otava::ast::ConstructorNode* constructorNode = nullptr;
        otava::ast::FunctionBodyNode* functionBodyNode = nullptr;
        if (fnBody->IsConstructorNode())
        {
            constructorNode = static_cast<otava::ast::ConstructorNode*>(fnBody);
            ctorInitializerNode = static_cast<otava::ast::ConstructorInitializerNode*>(constructorNode->Left());
            compoundStatementNode = static_cast<otava::ast::CompoundStatementNode*>(constructorNode->Right());
        }
        else if (fnBody->IsFunctionBodyNode())
        {
            functionBodyNode = static_cast<otava::ast::FunctionBodyNode*>(node.FunctionBody());
            compoundStatementNode = static_cast<otava::ast::CompoundStatementNode*>(functionBodyNode->Child());
        }
        if (ctorInitializerNode)
        {
            if (ctorInitializerNode->GetLexerPosPair().IsValid())
            {
                RecordedParseCtorInitializer(ctorInitializerNode, context);
            }
        }
        if (compoundStatementNode)
        {
            if (compoundStatementNode->GetLexerPosPair().IsValid())
            {
                RecordedParseCompoundStatement(compoundStatementNode, context);
            }
        }
        FunctionDefinitionSymbol* functionDefinitionSymbol = nullptr;
        if (symbol->IsFunctionDefinitionSymbol())
        {
            functionDefinitionSymbol = static_cast<FunctionDefinitionSymbol*>(symbol);
        }
        else
        {
            ThrowException("function definition symbol expected", node.GetSourcePos(), context);
        }
        if (!context->GetFlag(ContextFlags::parsingTemplateDeclaration))
        {
            context->PushBoundFunction(new BoundFunctionNode(functionDefinitionSymbol, node.GetSourcePos()));
            BindFunction(&node, functionDefinitionSymbol, context);
            BoundFunctionNode* boundFunction = context->ReleaseBoundFunction();
            if (functionDefinitionSymbol->IsBound())
            {
                context->GetBoundCompileUnit()->AddBoundNode(boundFunction);
            }
            context->PopBoundFunction();
        }
    }
    catch (const std::exception& ex)
    {
        ThrowException("error parsing inline member function body: " + std::string(ex.what()), node.GetSourcePos(), context);
    }
}

void ParseInlineMemberFunctions(otava::ast::Node* classSpecifierNode, ClassTypeSymbol* classTypeSymbol, otava::symbols::Context* context)
{
    context->GetSymbolTable()->BeginScope(classTypeSymbol->GetScope());
    InlineMemberFunctionParserVisitor visitor(context);
    classSpecifierNode->Accept(visitor);
    context->GetSymbolTable()->EndScope();
}

bool ClassLess::operator()(ClassTypeSymbol* left, ClassTypeSymbol* right) const
{
    return left->Name() < right->Name();
}

void ThrowMemberDeclarationParsingError(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    ThrowException("class member declaration parsing error", sourcePos, context);
}

void ThrowStatementParsingError(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    ThrowException("statement parsing error", sourcePos, context);
}

class TrivialClassDtor : public FunctionSymbol
{
public:
    TrivialClassDtor();
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
};

TrivialClassDtor::TrivialClassDtor() : FunctionSymbol(U"@destructor")
{
    SetFunctionKind(FunctionKind::destructor);
    SetAccess(Access::public_);
    SetFlag(FunctionSymbolFlags::trivialDestructor);
}

void TrivialClassDtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
}

void GenerateDestructor(ClassTypeSymbol* classTypeSymbol, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    Symbol* dtorSymbol = classTypeSymbol->GetScope()->Lookup(U"@destructor", SymbolGroupKind::functionSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::none);
    if (dtorSymbol) return;
    std::unique_ptr<TrivialClassDtor> trivialClassDestructor(new TrivialClassDtor());
    int nm = classTypeSymbol->MemberVariables().size();
    int nb = classTypeSymbol->BaseClasses().size();
    if (nm == 0 && nb == 0)
    {
        FunctionGroupSymbol* functionGroup = classTypeSymbol->GetScope()->GroupScope()->GetOrInsertFunctionGroup(U"@destructor", sourcePos, context);
        functionGroup->AddFunction(trivialClassDestructor.get());
        classTypeSymbol->AddSymbol(trivialClassDestructor.release(), sourcePos, context);
        return;
    }
    bool hasNonTrivialDestructor = false;
    std::unique_ptr<FunctionDefinitionSymbol> destructorSymbol(new FunctionDefinitionSymbol(U"@destructor"));
    destructorSymbol->SetParent(classTypeSymbol);
    destructorSymbol->SetFunctionKind(FunctionKind::destructor);
    destructorSymbol->SetAccess(Access::public_);
    std::unique_ptr<BoundDtorTerminatorNode> terminator(new BoundDtorTerminatorNode(sourcePos));
    for (int i = nm - 1; i >= 0; --i)
    {
        VariableSymbol* memberVar = classTypeSymbol->MemberVariables()[i];
        if (memberVar->GetType()->IsPointerType() || memberVar->GetType()->IsReferenceType()) continue;
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        BoundVariableNode* boundVariableNode = new BoundVariableNode(memberVar, sourcePos);
        ParameterSymbol* thisParam = destructorSymbol->ThisParam(context);
        BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, thisParam->GetReferredType(context));
        boundVariableNode->SetThisPtr(thisPtr);
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariableNode, sourcePos, boundVariableNode->GetType()->AddPointer(context))));
        std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
            context->GetSymbolTable()->CurrentScope(), U"@destructor", args, sourcePos, context);
        if (!boundFunctionCall->GetFunctionSymbol()->GetFlag(FunctionSymbolFlags::trivialDestructor))
        {
            hasNonTrivialDestructor = true;
        }
        terminator->AddMemberTerminator(boundFunctionCall.release());
    }
    for (int i = nb - 1; i >= 0; --i)
    {
        TypeSymbol* baseClass = classTypeSymbol->BaseClasses()[i];
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        ParameterSymbol* thisParam = destructorSymbol->ThisParam(context);
        BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, thisParam->GetType());
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            baseClass->AddPointer(context), thisPtr->GetType(), context);
        if (conversion)
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
                context->GetSymbolTable()->CurrentScope(), U"@destructor", args, sourcePos, context);
            if (!boundFunctionCall->GetFunctionSymbol()->GetFlag(FunctionSymbolFlags::trivialDestructor))
            {
                hasNonTrivialDestructor = true;
            }
            terminator->AddMemberTerminator(boundFunctionCall.release());
        }
        else
        {
            ThrowException("base class conversion not found", sourcePos, context);
        }
    }
    if (!hasNonTrivialDestructor)
    {
        FunctionGroupSymbol* functionGroup = classTypeSymbol->GetScope()->GroupScope()->GetOrInsertFunctionGroup(U"@destructor", sourcePos, context);
        functionGroup->AddFunction(trivialClassDestructor.get());
        classTypeSymbol->AddSymbol(trivialClassDestructor.release(), sourcePos, context);
        return;
    }
    BoundFunctionNode* boundDestructor = new BoundFunctionNode(destructorSymbol.get(), sourcePos);
    FunctionGroupSymbol* functionGroup = classTypeSymbol->GetScope()->GroupScope()->GetOrInsertFunctionGroup(U"@destructor", sourcePos, context);
    functionGroup->AddFunction(destructorSymbol.get());
    FunctionSymbol* destructor = destructorSymbol.get();
    classTypeSymbol->AddSymbol(destructorSymbol.release(), sourcePos, context);
    BoundCompoundStatementNode* body = new BoundCompoundStatementNode(sourcePos);
    if (classTypeSymbol->IsPolymorphic())
    {
        if (classTypeSymbol->HasPolymorphicBaseClass())
        {
            destructor->SetOverride();
        }
        else
        {
            destructor->SetVirtual();
        }
        if (!classTypeSymbol->ObjectLayoutComputed())
        {
            classTypeSymbol->MakeObjectLayout(context);
        }
        BoundExpressionNode* thisPtr = new BoundParameterNode(destructor->ThisParam(context), sourcePos, destructor->ThisParam(context)->GetReferredType(context));
        ClassTypeSymbol* vptrHolderClass = classTypeSymbol->VPtrHolderClass();
        if (!vptrHolderClass)
        {
            ThrowException("vptr holder class not found", sourcePos, context);
        }
        if (vptrHolderClass != classTypeSymbol)
        {
            FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                vptrHolderClass->AddPointer(context), thisPtr->GetType(), context);
            if (conversion)
            {
                BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr, conversion, sourcePos);
                BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtrConverted, sourcePos);
                body->AddStatement(setVPtrStatement);
            }
            else
            {
                ThrowException("vptr holder class conversion not found", sourcePos, context);
            }
        }
        else
        {
            BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtr, sourcePos);
            body->AddStatement(setVPtrStatement);
        }
    }
    boundDestructor->SetBody(body);
    boundDestructor->SetDtorTerminator(terminator.release());
    context->GetBoundCompileUnit()->AddBoundNode(boundDestructor);
}

} // namespace otava::symbols

