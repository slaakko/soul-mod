// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

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

namespace otava::symbols {

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


RecordedParseFn recordedParseFn = nullptr;

void SetRecordedParseFn(RecordedParseFn fn)
{
    recordedParseFn = fn;
}

void RecordedParse(otava::ast::CompoundStatementNode* compoundStatementNode, Context* context)
{
    if (recordedParseFn)
    {
        recordedParseFn(compoundStatementNode, context);
    }
}

ClassTypeSymbol::ClassTypeSymbol(const std::u32string& name_) : 
    TypeSymbol(SymbolKind::classTypeSymbol, name_), 
    classKind(ClassKind::class_), 
    specialization(nullptr),
    level(0), 
    irType(nullptr),
    objectLayoutComputed(false),
    vptrIndex(-1),
    currentFunctionIndex(1)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

ClassTypeSymbol::ClassTypeSymbol(SymbolKind kind_, const std::u32string& name_) : 
    TypeSymbol(kind_, name_),
    classKind(ClassKind::class_),
    specialization(nullptr),
    level(0),
    irType(nullptr),
    objectLayoutComputed(false),
    vptrIndex(-1),
    currentFunctionIndex(1)
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

void ClassTypeSymbol::AddBaseClass(TypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context)
{
    baseClasses.push_back(baseClass);
    GetScope()->AddBaseScope(baseClass->GetScope(), sourcePos, context);
}

void ClassTypeSymbol::AddDerivedClass(TypeSymbol* derivedClass)
{
    if (std::find(derivedClasses.begin(), derivedClasses.end(), derivedClass) == derivedClasses.end())
    {
        derivedClasses.push_back(derivedClass);
    }
}

void ClassTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ClassTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
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
    writer.GetBinaryStreamWriter().Write(objectLayoutComputed);
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
}

void ClassTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
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
    objectLayoutComputed = reader.GetBinaryStreamReader().ReadBool();
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
    if (objectLayoutComputed) return;
    objectLayoutComputed = true;
    for (const auto& baseClass : baseClasses)
    {
        objectLayout.push_back(baseClass);
    }
    if (baseClasses.empty())
    {
        if (IsPolymorphic())
        {
            vptrIndex = objectLayout.size();
            objectLayout.push_back(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType)->AddPointer());
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

TemplateDeclarationSymbol* ClassTypeSymbol::ParentTemplateDeclaration() 
{
    Symbol* parentSymbol = Parent();
    if (parentSymbol->IsTemplateDeclarationSymbol())
    {
        return static_cast<TemplateDeclarationSymbol*>(parentSymbol);
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
        memberVariables.push_back(static_cast<VariableSymbol*>(symbol));
    }
    else if (symbol->IsFunctionSymbol())
    {
        memberFunctions.push_back(static_cast<FunctionSymbol*>(symbol));
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
    classTypeSymbol(nullptr)
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
    TypeSymbol* baseClass = ResolveType(node.ClassOrDeclType(), DeclarationFlags::none, context);
    context->GetSymbolTable()->AddBaseClass(baseClass, node.GetSourcePos(), context);
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
    context->PopFlags();
    context->GetSymbolTable()->EndClass();
    if (classTypeSymbol->Level() == 0)
    {
        ParseInlineMemberFunctions(specNode, classTypeSymbol, context);
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
        if (!context->GetFlag(ContextFlags::parsingTemplateDeclaration))
        {
            Symbol* symbol = context->GetSymbolTable()->GetSymbol(&node);
            otava::ast::Node* fnBody = node.FunctionBody();
            otava::ast::CompoundStatementNode* compoundStatementNode = nullptr;
            if (fnBody->IsConstructorNode())
            {
                otava::ast::ConstructorNode* constructorNode = static_cast<otava::ast::ConstructorNode*>(fnBody);
                compoundStatementNode = static_cast<otava::ast::CompoundStatementNode*>(constructorNode->Right());
            }
            else if (fnBody->IsFunctionBodyNode())
            {
                otava::ast::FunctionBodyNode* functionBody = static_cast<otava::ast::FunctionBodyNode*>(node.FunctionBody());
                compoundStatementNode = static_cast<otava::ast::CompoundStatementNode*>(functionBody->Child());
            }
            if (compoundStatementNode)
            {
                if (compoundStatementNode->GetLexerPosPair().IsValid())
                {
                    RecordedParse(compoundStatementNode, context);
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
            BindFunction(&node, functionDefinitionSymbol, context);
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

} // namespace otava::symbols
