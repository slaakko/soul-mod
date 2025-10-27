// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.classes;

import otava.ast;
import otava.symbols.class_group.symbol;
import otava.symbols.context;
import otava.symbols.emitter;
import otava.symbols.error;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.symbol_map;
import otava.symbols.templates;
import otava.symbols.visitor;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.type.resolver;
import otava.symbols.statement.binder;
import otava.symbols.variable.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.overload.resolution;
import otava.symbols.argument.conversion.table;
import otava.symbols.class_templates;
import otava.symbols.fundamental.type.operation;
import otava.symbols.function.group.symbol;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.operation.repository;
import otava.symbols.declaration;
import otava.symbols.type_compare;
import soul.lexer;
import util.unicode;
import util.sha1;

namespace otava::symbols {

std::int32_t GetSpecialFunctionIndex(SpecialFunctionKind specialFunctionKind)
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
    deltaIndex(-1),
    group(nullptr),
    copyCtor(nullptr),
    nextMemFnDefIndex(0)
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
    deltaIndex(-1),
    group(nullptr),
    copyCtor(nullptr),
    nextMemFnDefIndex(0)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

ClassTypeSymbol::ClassTypeSymbol(SymbolKind kind_, const util::uuid& id_, const std::u32string& name_) :
    TypeSymbol(kind_, id_, name_),
    flags(ClassTypeSymbolFlags::none),
    classKind(ClassKind::class_),
    specialization(nullptr),
    level(0),
    irType(nullptr),
    currentFunctionIndex(1),
    specializationId(),
    vtabSize(0),
    vptrIndex(-1),
    group(nullptr),
    copyCtor(nullptr),
    nextMemFnDefIndex(0)
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

std::expected<bool, int> ClassTypeSymbol::AddBaseClass(ClassTypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context)
{
    baseClasses.push_back(baseClass);
    std::expected<bool, int> rv = GetScope()->AddBaseScope(baseClass->GetScope(), sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

void ClassTypeSymbol::AddDerivedClass(ClassTypeSymbol* derivedClass)
{
    if (std::find(derivedClasses.begin(), derivedClasses.end(), derivedClass) == derivedClasses.end())
    {
        derivedClasses.push_back(derivedClass);
    }
}

bool ClassTypeSymbol::HasBaseClass(TypeSymbol* baseClass, int& distance, Context* context) const
{
    for (ClassTypeSymbol* baseCls : baseClasses)
    {
        if (TypesEqual(baseCls, baseClass, context))
        {
            ++distance;
            return true;
        }
        else
        {
            ++distance;
            if (baseCls->HasBaseClass(baseClass, distance, context))
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
    for (ClassTypeSymbol* baseCls : baseClasses)
    {
        if (baseCls->IsPolymorphic())
        {
            return true;
        }
    }
    return false;
}

bool ClassTypeSymbol::IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const
{
    if (visited.find(this) == visited.end())
    {
        visited.insert(this);
        for (VariableSymbol* memberVariable : memberVariables)
        {
            if (memberVariable->IsTemplateParameterInstantiation(context, visited)) return true;
        }
        for (VariableSymbol* staticMemberVar : staticMemberVariables)
        {
            if (staticMemberVar->IsTemplateParameterInstantiation(context, visited)) return true;
        }
    }
    return false;
}

void ClassTypeSymbol::SetSpecialization(TypeSymbol* specialization_, Context* context)
{
    specialization = specialization_;
    if (specialization)
    {
        context->GetSymbolTable()->MapType(specialization);
        if (specialization->IsClassTemplateSpecializationSymbol())
        {
            context->GetSymbolTable()->MapClassTemplateSpecialization(static_cast<ClassTemplateSpecializationSymbol*>(specialization));
        }
    }
}

void ClassTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ClassTypeSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(flags));
    if (!rv) return rv;
    std::uint32_t nb = baseClasses.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(nb);
    if (!rv) return rv;
    for (ClassTypeSymbol* baseClass : baseClasses)
    {
        rv = writer.GetBinaryStreamWriter().Write(baseClass->Id());
        if (!rv) return rv;
    }
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(classKind));
    if (!rv) return rv;
    util::uuid specializationId = util::nil_uuid();
    if (specialization)
    {
        specializationId = specialization->Id();
    }
    rv = writer.GetBinaryStreamWriter().Write(specializationId);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(level);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(static_cast<std::uint32_t>(objectLayout.size()));
    if (!rv) return rv;
    for (TypeSymbol* type : objectLayout)
    {
        rv = writer.GetBinaryStreamWriter().Write(type->Id());
        if (!rv) return rv;
    }
    std::uint32_t nfm = functionIndexMap.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(nfm);
    if (!rv) return rv;
    for (const auto& fn : functionIndexMap)
    {
        rv = writer.GetBinaryStreamWriter().Write(fn.first);
        if (!rv) return rv;
        rv = writer.GetBinaryStreamWriter().Write(fn.second->Id());
        if (!rv) return rv;
    }
    rv = writer.GetBinaryStreamWriter().Write(vtabSize);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(vptrIndex);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(deltaIndex);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(vtabName);
    if (!rv) return rv;
    util::uuid groupId = util::nil_uuid();
    if (group)
    {
        groupId = group->Id();
    }
    rv = writer.GetBinaryStreamWriter().Write(groupId);
    if (!rv) return rv;
    std::uint32_t nmfnds = memFnDefSymbolMap.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(nmfnds);
    if (!rv) return rv;
    for (const auto& memFnDefSymbolPair : memFnDefSymbolMap)
    {
        int32_t index = memFnDefSymbolPair.first;
        rv = writer.GetBinaryStreamWriter().Write(index);
        if (!rv) return rv;
        FunctionDefinitionSymbol* mfnds = memFnDefSymbolPair.second;
        rv = writer.GetBinaryStreamWriter().Write(mfnds->Id());
        if (!rv) return rv;
    }
    rv = writer.GetBinaryStreamWriter().Write(nextMemFnDefIndex);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ClassTypeSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint8_t, int> brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t f = *brv;
    flags = static_cast<ClassTypeSymbolFlags>(f);
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::int32_t nb = static_cast<std::int32_t>(*urv);
    for (std::int32_t i = 0; i < nb; ++i)
    {
        util::uuid baseClassId;
        rv = reader.GetBinaryStreamReader().ReadUuid(baseClassId);
        if (!rv) return rv;
        baseClassIds.push_back(baseClassId);
    }
    brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t c = *brv;
    classKind = static_cast<ClassKind>(c);
    rv = reader.GetBinaryStreamReader().ReadUuid(specializationId);
    if (!rv) return rv;
    std::expected<std::int32_t, int> irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    level = *irv;
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::int32_t nol = static_cast<std::int32_t>(*urv);
    for (std::int32_t i = 0; i < nol; ++i)
    {
        util::uuid tid;
        rv = reader.GetBinaryStreamReader().ReadUuid(tid);
        if (!rv) return rv;
        objectLayoutIds.push_back(tid);
    }
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::int32_t nfm = static_cast<std::int32_t>(*urv);
    for (std::int32_t i = 0; i < nfm; ++i)
    {
        irv = reader.GetBinaryStreamReader().ReadInt();
        if (!irv) return std::unexpected<int>(irv.error());
        std::int32_t fnIndex = *irv;
        util::uuid fnId;
        rv = reader.GetBinaryStreamReader().ReadUuid(fnId);
        if (!rv) return rv;
        functionIdMap[fnIndex] = fnId;
    }
    irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    vtabSize = *irv;
    irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    vptrIndex = *irv;
    irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    deltaIndex = *irv;
    std::expected<std::string, int> srv = reader.GetBinaryStreamReader().ReadUtf8String();
    if (!srv) return std::unexpected<int>(srv.error());
    vtabName = *srv;
    rv = reader.GetBinaryStreamReader().ReadUuid(groupId);
    if (!rv) return rv;
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::int32_t nmfnds = static_cast<std::int32_t>(*urv);
    for (std::int32_t i = 0; i < nmfnds; ++i)
    {
        util::uuid mfnid;
        irv = reader.GetBinaryStreamReader().ReadInt();
        if (!irv) return std::unexpected<int>(irv.error());
        int32_t memFnDefSymboIndex = *irv;
        rv = reader.GetBinaryStreamReader().ReadUuid(mfnid);
        if (!rv) return rv;
        memFnDefSymbolIdMap[memFnDefSymboIndex] = mfnid;
    }
    irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    nextMemFnDefIndex = *irv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ClassTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    for (const util::uuid& baseClassId : baseClassIds)
    {
        std::expected<Symbol*, int> rv= symbolTable.GetSymbolMap()->GetSymbol(symbolTable.GetModule(), SymbolKind::null, baseClassId);
        if (!rv) return std::unexpected<int>(rv.error());
        Symbol* baseClassSymbol = *rv;
        if (baseClassSymbol->IsClassTypeSymbol())
        {
            std::expected<bool, int> brv = GetScope()->AddBaseScope(baseClassSymbol->GetScope(), soul::ast::SourcePos(), nullptr);
            if (!brv) return brv;
            baseClasses.push_back(static_cast<ClassTypeSymbol*>(baseClassSymbol));
        }
    }
    if (specializationId != util::nil_uuid())
    {
        specialization = symbolTable.GetType(specializationId);
        if (!specialization)
        {
            std::expected<std::u32string, int> fname = FullName();
            if (!fname) return std::unexpected<int>(fname.error());
            std::expected<std::string, int> sfname = util::ToUtf8(*fname);
            if (!sfname) return std::unexpected<int>(sfname.error());
            std::cout << "ClassTypeSymbol::Resolve(): warning: specialization type of '" + *sfname + "' not resolved" << "\n";
        }
    }
    for (const auto& tid : objectLayoutIds)
    {
        TypeSymbol* type = symbolTable.GetType(tid);
        if (type)
        {
            objectLayout.push_back(type);
        }
        else
        {
            std::expected<std::u32string, int> fname = FullName();
            if (!fname) return std::unexpected<int>(fname.error());
            std::expected<std::string, int> sfname = util::ToUtf8(*fname);
            if (!sfname) return std::unexpected<int>(sfname.error());
            std::cout << "ClassTypeSymbol::Resolve(): warning: object layout type of '" + *sfname + "' not resolved" << "\n";
        }
    }
    for (const auto& fnIndexId : functionIdMap)
    {
        std::expected<FunctionSymbol*, int> f = symbolTable.GetFunction(fnIndexId.second);
        if (!f) return std::unexpected<int>(f.error());
        FunctionSymbol* function = *f;
/*
        if (!function)
        {
            function = symbolTable.GetFunctionDefinition(fnIndexId.second);
        }
*/
        functionIndexMap[fnIndexId.first] = function;
    }
    if (groupId != util::nil_uuid())
    {
        std::expected<ClassGroupSymbol*, int> g = symbolTable.GetClassGroup(groupId);
        if (!g) return std::unexpected<int>(g.error());
        group = *g;
    }
    memFnDefSymbolMap.clear();
    for (const auto& mfIndexSymbolIdPair : memFnDefSymbolIdMap)
    {
        int32_t index = mfIndexSymbolIdPair.first;
        util::uuid mfnid = mfIndexSymbolIdPair.second;
        std::expected<FunctionDefinitionSymbol*, int> d = symbolTable.GetFunctionDefinition(mfnid);
        if (!d) return std::unexpected<int>(d.error());
        FunctionDefinitionSymbol* mfn = *d;
        memFnDefSymbolMap[index] = mfn;
    }
    memFnDefSymbolIdMap.clear();
    return std::expected<bool, int>(true);
}

bool ClassTypeSymbol::IsPolymorphic() const
{
    for (ClassTypeSymbol* baseClass : baseClasses)
    {
        if (baseClass->IsPolymorphic()) return true;
    }
    for (FunctionSymbol* memberFunction : memberFunctions)
    {
        if (memberFunction->IsVirtual()) return true;
    }
    return false;
}

std::expected<bool, int> ClassTypeSymbol::MakeObjectLayout(const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (ObjectLayoutComputed())
    {
        for (VariableSymbol* memberVar : memberVariables)
        {
            if (memberVar->LayoutIndex() == -1)
            {
                ResetObjectLayoutComputed();
                break;
            }
        }
    }
    if (ObjectLayoutComputed()) return std::expected<bool, int>(true);
    SetObjectLayoutComputed();
    objectLayout.clear();
    for (ClassTypeSymbol* baseClass : baseClasses)
    {
        std::expected<bool, int> rv = baseClass->MakeObjectLayout(sourcePos, context);
        if (!rv) return rv;
        objectLayout.push_back(baseClass);
    }
    if (baseClasses.empty())
    {
        if (IsPolymorphic())
        {
            SetVPtrIndex(static_cast<std::int32_t>(objectLayout.size()));
            std::expected<TypeSymbol*, int> pt = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType)->AddPointer(context);
            if (!pt) return std::unexpected<int>(pt.error());
            objectLayout.push_back(*pt);
            SetDeltaIndex(static_cast<std::int32_t>(objectLayout.size()));
            objectLayout.push_back(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType));
        }
        else if (memberVariables.empty())
        {
            objectLayout.push_back(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedCharType));
        }
    }
    for (VariableSymbol* memberVar : memberVariables)
    {
        std::int32_t layoutIndex = objectLayout.size();
        memberVar->SetLayoutIndex(layoutIndex);
        std::expected<TypeSymbol*, int> rv = memberVar->GetType()->FinalType(sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        TypeSymbol* memberVarType = *rv;
        if (memberVarType->IsForwardClassDeclarationSymbol())
        {
            return Error("could not make object layout: incomplete types not allowed", sourcePos, context);
        }
        objectLayout.push_back(memberVarType);
    }
    return std::expected<bool, int>(true);
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

std::expected<bool, int> ClassTypeSymbol::MakeVTab(Context* context, const soul::ast::SourcePos& sourcePos)
{
    if (!IsClassTemplateSpecializationSymbol())
    {
        if (VTabInitialized()) return;
        SetVTabInitialized();
    }
    std::expected<bool, int> rv = ComputeVTabName(context);
    if (!rv) return rv;
    rv = InitVTab(vtab, context, sourcePos, IsClassTemplateSpecializationSymbol());
    if (!rv) return rv;
    vtabSize = static_cast<std::int32_t>(vtab.size());
    return std::expected<bool, int>(true);
}

bool Overrides(FunctionSymbol* f, FunctionSymbol* g, Context* context)
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
                context->PushSetFlag(ContextFlags::matchClassGroup);
                if (!TypesEqual(p->GetType(), q->GetType(), context))
                {
                    context->PopFlags();
                    return false;
                }
                context->PopFlags();
            }
            if (f->IsConst() != g->IsConst()) return false;
            return true;
        }
    }
    return false;
}

std::expected<bool, int> ClassTypeSymbol::InitVTab(std::vector<FunctionSymbol*>& vtab, Context* context, const soul::ast::SourcePos& sourcePos, bool clear)
{
    if (!IsPolymorphic()) return std::expected<bool, int>(false);
    if (clear)
    {
        vtab.clear();
    }
    if (!baseClasses.empty())
    {
        for (ClassTypeSymbol* baseClass : baseClasses)
        {
            std::expected<bool, int> rv = baseClass->InitVTab(vtab, context, sourcePos, false);
            if (!rv) return rv;
        }
    }
    std::vector<FunctionSymbol*> virtualFunctions;
    for (FunctionSymbol* function : memberFunctions)
    {
        FunctionSymbol* fn = function;
        if (function->IsFunctionDefinitionSymbol())
        {
            FunctionDefinitionSymbol* definition = static_cast<FunctionDefinitionSymbol*>(function);
            FunctionSymbol* declaration = definition->Declaration();
            if (declaration)
            {
                fn = declaration;
            }
        }
        if ((fn->IsVirtual() || fn->IsDestructor()) && !fn->IsTrivialDestructor())
        {
            bool found = false;
            for (FunctionSymbol* existing : virtualFunctions)
            {
                if (FunctionMatches(fn, existing, context))
                {
                    if (existing->VTabIndex() != -1)
                    {
                        fn->SetVTabIndex(existing->VTabIndex());
                    }
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                virtualFunctions.push_back(fn);
            }
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
            if (Overrides(f, v, context))
            {
                if (!f->IsOverride() && !f->IsFinal() && !f->IsDestructor())
                {
                    std::expected<std::u32string, int> fname = f->FullName();
                    if (!fname) return std::unexpected<int>(fname.error());
                    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                    if (!sfname) return std::unexpected<int>(sfname.error());
                    std::expected<std::u32string, int> vfname = v->FullName();
                    if (!vfname) return std::unexpected<int>(vfname.error());
                    std::expected<std::string, int> vname = util::ToUtf8(*vfname);
                    if (!vname) return std::unexpected<int>(vname.error());
                    return Error("overriding function should be declared with override or final specifier: (" +
                        *sfname + " overrides " + *vname + ")", sourcePos, context);
                }
                vtab[j] = f;
                f->SetVTabIndex(j);
                if (f->Group())
                {
                    f->Group()->SetVTabIndex(f, j, context);
                }
                found = true;
                break;
            }
        }
        if (!found)
        {
            if (f->IsOverride())
            {
                std::expected<std::u32string, int> fname = f->FullName();
                if (!fname) return std::unexpected<int>(fname.error());
                std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                if (!sfname) return std::unexpected<int>(sfname.error());
                return Error("no suitable function to override ('" + *sfname + "')", sourcePos, context);
            }
            f->SetVTabIndex(m);
            if (f->Group())
            {
                f->Group()->SetVTabIndex(f, m, context);
            }
            vtab.push_back(f);
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<std::string, int> ClassTypeSymbol::IrName(Context* context) const
{
    std::string irName;
    std::expected<std::string, int> name = util::ToUtf8(Name());
    if (!name) return std::unexpected<int>(name.error());
    irName.append("class_").append(*name);
    std::expected<std::u32string, int> fname = FullName();
    if (!fname) return std::unexpected<int>(fname.error());
    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
    if (!sfname) return std::unexpected<int>(sfname.error());
    std::string shaMaterial = std::move(*sfname);
    irName.append("_").append(util::GetSha1MessageDigest(shaMaterial));
    return std::expected<std::string, int>(irName);
}

std::expected<bool, int> ClassTypeSymbol::ComputeVTabName(Context* context)
{
    vtabName = "vtab_";
    std::expected<std::string, int> is = IrName(context);
    if (!is) return std::unexpected<int>(is.error());
    vtabName.append(*is);
    return std::expected<bool, int>(true);
}

std::expected<otava::intermediate::Type*, int> ClassTypeSymbol::VPtrType(Emitter& emitter) const
{
    std::expected<otava::intermediate::Type*, int> prv = emitter.MakePtrType(emitter.GetVoidType());
    if (!prv) return std::unexpected<int>(prv.error());
    otava::intermediate::Type* voidPtrIrType = *prv;
    std::expected<otava::intermediate::Type*, int> rv = emitter.MakeArrayType(vtabSize * 2 + otava::symbols::vtabClassIdElementCount, voidPtrIrType);
    if (!rv) return rv;
    otava::intermediate::Type* type = *rv;
    prv = emitter.MakePtrType(type);
    otava::intermediate::Type* vptrType = *prv;
    return std::expected<otava::intermediate::Type*, int>(vptrType);
}

std::expected<otava::intermediate::Value*, int> ClassTypeSymbol::GetVTabVariable(Emitter& emitter, Context* context)
{
    std::expected<std::u32string, int> fname = FullName();
    if (!fname) return std::unexpected<int>(fname.error());
    otava::intermediate::Value* vtabVariable = emitter.GetVTabVariable(*fname);
    if (!vtabVariable)
    {
        std::expected<otava::intermediate::Type*, int> prv = emitter.MakePtrType(emitter.GetVoidType());
        if (!prv) return std::unexpected<int>(prv.error());
        otava::intermediate::Type* voidPtrIrType = *prv;
        std::expected<otava::intermediate::Type*, int> rv = emitter.MakeArrayType(vtabSize * 2 + otava::symbols::vtabClassIdElementCount, voidPtrIrType);
        if (!rv) return std::unexpected<int>(rv.error());
        otava::intermediate::Type* arrayType = *rv;
        std::expected<otava::intermediate::Value*, int> grv = emitter.EmitGlobalVariable(arrayType, VTabName(context), nullptr);
        if (!grv) return std::unexpected<int>(grv.error());
        vtabVariable = *grv;
        emitter.SetVTabVariable(*fname, vtabVariable);
    }
    return vtabVariable;
}

std::vector<ClassTypeSymbol*> ClassTypeSymbol::VPtrHolderClasses() const
{
    std::vector<ClassTypeSymbol*> vptrHolderClasses;
    if (vptrIndex != -1)
    {
        vptrHolderClasses.push_back(const_cast<ClassTypeSymbol*>(this));
    }
    else
    {
        for (ClassTypeSymbol* baseClass : baseClasses)
        {
            std::vector<ClassTypeSymbol*> vptrHolderBaseClasses = baseClass->VPtrHolderClasses();
            for (ClassTypeSymbol* vptrHolderClass : vptrHolderBaseClasses)
            {
                if (std::find(vptrHolderClasses.begin(), vptrHolderClasses.end(), vptrHolderClass) == vptrHolderClasses.end())
                {
                    vptrHolderClasses.push_back(vptrHolderClass);
                }
            }
        }
    }
    return vptrHolderClasses;
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

void ClassTypeSymbol::SetMemFnDefSymbol(FunctionDefinitionSymbol* memFnDefSymbol)
{
    if (memFnDefSymbol->DefIndex() == -1)
    {
        memFnDefSymbol->SetDefIndex(nextMemFnDefIndex++);
    }
    memFnDefSymbolMap[memFnDefSymbol->DefIndex()] = memFnDefSymbol;
    nextMemFnDefIndex = std::max(nextMemFnDefIndex, memFnDefSymbol->DefIndex() + 1);
}

FunctionDefinitionSymbol* ClassTypeSymbol::GetMemFnDefSymbol(int32_t defIndex) const
{
    auto it = memFnDefSymbolMap.find(defIndex);
    if (it != memFnDefSymbolMap.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

std::expected<bool, int> ClassTypeSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::AddSymbol(symbol, sourcePos, context);
    if (!rv) return rv;
    if (symbol->IsVariableSymbol())
    {
        VariableSymbol* memberVariable = static_cast<VariableSymbol*>(symbol);
        if ((symbol->GetDeclarationFlags() & DeclarationFlags::staticFlag) != DeclarationFlags::none)
        {
            staticMemberVariables.push_back(memberVariable);
        }
        else
        {
            memberVariable->SetIndex(static_cast<std::int32_t>(memberVariables.size()));
            memberVariables.push_back(memberVariable);
        }
    }
    else if (symbol->IsFunctionSymbol())
    {
        FunctionSymbol* functionSymbol = static_cast<FunctionSymbol*>(symbol);
        memberFunctions.push_back(functionSymbol);
        if (functionSymbol->IsConversionMemFn())
        {
            conversionFunctions.push_back(functionSymbol);
        }
        MapFunction(functionSymbol);
    }
    if (symbol->IsFunctionDefinitionSymbol())
    {
        FunctionDefinitionSymbol* memFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(symbol);
        SetMemFnDefSymbol(memFnDefSymbol);
    }
    return std::expected<bool, int>(true);
}

std::expected<otava::intermediate::Type*, int> ClassTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Type* irType = emitter.GetType(Id());
    if (!irType)
    {
        std::expected<std::u32string, int> fname = FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        irType = emitter.GetOrInsertFwdDeclaredStructureType(Id(), *sfname);
        emitter.SetType(Id(), irType);
        std::expected<bool, int> rv = MakeObjectLayout(sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        int n = objectLayout.size();
        std::vector<otava::intermediate::Type*> elementTypes;
        for (int i = 0; i < n; ++i)
        {
            TypeSymbol* type = objectLayout[i];
            std::expected<otava::intermediate::Type*, int> irv = type->IrType(emitter, sourcePos, context);
            if (!irv) return std::unexpected<int>(irv.error());
            elementTypes.push_back(*irv);
        }
        otava::intermediate::MetadataStruct* metadataStruct = emitter.CreateMetadataStruct();
        metadataStruct->AddItem("fullName", emitter.CreateMetadataString(*sfname));
        otava::intermediate::MetadataRef* metadataRef = emitter.CreateMetadataRef(metadataStruct->Id());
        std::expected<otava::intermediate::Type*, int> srv = emitter.MakeStructureType(elementTypes, *sfname);
        if (!srv) return std::unexpected<int>(srv.error());
        otava::intermediate::Type* type = *srv;
        otava::intermediate::StructureType* structureType = static_cast<otava::intermediate::StructureType*>(type);
        structureType->SetMetadataRef(metadataRef);
        irType = type;
        emitter.SetType(Id(), irType);
        emitter.ResolveForwardReferences(Id(), structureType);
    }
    return std::expected<otava::intermediate::Type*, int>(irType);
}

std::int32_t ClassTypeSymbol::NextFunctionIndex()
{
    return currentFunctionIndex++;
}

void ClassTypeSymbol::MapFunction(FunctionSymbol* function)
{
    functionIndexMap[function->Index()] = function;
}

FunctionSymbol* ClassTypeSymbol::GetFunctionByIndex(std::int32_t functionIndex) const
{
    auto it = functionIndexMap.find(functionIndex);
    if (it != functionIndexMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

FunctionSymbol* ClassTypeSymbol::GetFunctionByNodeId(std::int32_t nodeId) const
{
    auto it = functionNodeIdMap.find(nodeId);
    if (it != functionNodeIdMap.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

FunctionSymbol* ClassTypeSymbol::GetConversionFunction(TypeSymbol* type, Context* context) const
{
    for (FunctionSymbol* conversionFunction : conversionFunctions)
    {
        if (TypesEqual(conversionFunction->ReturnType(), type, context))
        {
            return conversionFunction;
        }
    }
    for (ClassTypeSymbol* baseClass : baseClasses)
    {
        FunctionSymbol* baseClassConversionFn = baseClass->GetConversionFunction(type, context);
        if (baseClassConversionFn)
        {
            return baseClassConversionFn;
        }
    }
    return nullptr;
}

bool ClassTypeSymbol::IsComplete(std::set<const TypeSymbol*>& visited) const
{
    if (visited.find(this) != visited.end()) return true;
    visited.insert(this);
    for (ClassTypeSymbol* baseClass : baseClasses)
    {
        if (!baseClass->IsComplete(visited)) return false;
    }
    for (VariableSymbol* memberVariable : memberVariables)
    {
        if (!memberVariable->GetType()->IsComplete(visited)) return false;
    }
    for (VariableSymbol* staticMemberVariable : staticMemberVariables)
    {
        if (!staticMemberVariable->GetType()->IsComplete(visited)) return false;
    }
    return true;
}

std::expected<bool, int> ClassTypeSymbol::GenerateCopyCtor(const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (copyCtor) return;
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
    VariableSymbol* classTempVar = new VariableSymbol(U"@class_temp");
    classTempVar->SetDeclaredType(this);
    tempVars.push_back(std::unique_ptr<Symbol>(classTempVar));
    std::expected<TypeSymbol*, int> pt = classTempVar->GetType()->AddPointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(
        new BoundVariableNode(classTempVar, sourcePos), sourcePos, *pt)));
    VariableSymbol* constLvalueRefTempVar = new VariableSymbol(U"@const_lvalue_ref_temp");
    pt = this->AddConst(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* type = *pt;
    pt = type->AddLValueRef(context);
    if (!pt) return std::unexpected<int>(pt.error());
    type = *pt;
    constLvalueRefTempVar->SetDeclaredType(type);
    tempVars.push_back(std::unique_ptr<Symbol>(constLvalueRefTempVar));
    args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundVariableNode(constLvalueRefTempVar, sourcePos)));
    std::vector<TypeSymbol*> templateArgs;
    std::expected<std::unique_ptr<BoundFunctionCallNode>, int> rv = ResolveOverload(
        context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    std::unique_ptr<BoundFunctionCallNode> functionCall = std::move(*rv);
    copyCtor = functionCall->GetFunctionSymbol();
    return std::expected<bool, int>(true);
}

std::expected<std::int64_t, int> ClassTypeSymbol::Delta(ClassTypeSymbol* base, Emitter& emitter, Context* context)
{
    if (TypesEqual(base, this, context)) return std::expected<std::int64_t, int>(0);
    std::int64_t delta = 0;
    for (ClassTypeSymbol* bc : BaseClasses())
    {
        std::expected<std::int64_t, int> bcDeltaRv = bc->Delta(base, emitter, context);
        if (bcDeltaRv)
        {
            std::int64_t bcDelta = *bcDeltaRv;
            return std::expected<std::int64_t, int>(delta + bcDelta);
        }
        std::expected<otava::intermediate::Type*, int> irv = bc->IrType(emitter, soul::ast::SourcePos(), context);
        if (!irv) return std::unexpected<int>(irv.error());
        otava::intermediate::Type* bctype = *irv;
        std::int64_t bcsize = bctype->Size();
        delta += bcsize;
    }
    return std::unexpected<int>(util::AllocateError("delta not found"));
}

int ClassTypeSymbol::TotalMemberCount() const
{
    int totalMemberCount = 0;
    for (ClassTypeSymbol* baseClass : baseClasses)
    {
        totalMemberCount += baseClass->TotalMemberCount();
    }
    totalMemberCount += static_cast<int>(memberVariables.size());
    return totalMemberCount;
}

ForwardClassDeclarationSymbol::ForwardClassDeclarationSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::forwardClassDeclarationSymbol, name_),
    classKind(ClassKind::class_),
    specialization(nullptr),
    classTypeSymbol(nullptr),
    classTypeSymbolId(),
    group(nullptr)
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

std::expected<bool, int> ForwardClassDeclarationSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(classKind));
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(classTypeSymbol != nullptr);
    if (!rv) return rv;
    if (classTypeSymbol)
    {
        rv = writer.GetBinaryStreamWriter().Write(classTypeSymbol->Id());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ForwardClassDeclarationSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint8_t, int> brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t c = *brv;
    classKind = static_cast<ClassKind>(c);
    std::expected<bool, int> crv = reader.GetBinaryStreamReader().ReadBool();
    if (!crv) return std::unexpected<int>(crv.error());
    bool hasClassType = *crv;
    if (hasClassType)
    {
        rv = reader.GetBinaryStreamReader().ReadUuid(classTypeSymbolId);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ForwardClassDeclarationSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    if (classTypeSymbolId != util::nil_uuid())
    {
        TypeSymbol* type = symbolTable.GetType(classTypeSymbolId);
        if (type && type->IsClassTypeSymbol())
        {
            classTypeSymbol = static_cast<ClassTypeSymbol*>(type);
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.classes: class type expected"));
        }
    }
    return std::expected<bool, int>(true);
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

std::expected<TypeSymbol*, int> ForwardClassDeclarationSymbol::FinalType(const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (classTypeSymbol)
    {
        return classTypeSymbol->FinalType(sourcePos, context);
    }
    else
    {
        return this;
    }
}

std::expected<otava::intermediate::Type*, int> ForwardClassDeclarationSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<TypeSymbol*, int> rv = FinalType(sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    TypeSymbol* finalType = *rv;
    if (finalType->IsForwardClassDeclarationSymbol())
    {
        return context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType)->IrType(emitter, sourcePos, context);    
    }
    else
    {
        return finalType->IrType(emitter, sourcePos, context);
    }
}

bool ForwardClassDeclarationSymbol::IsComplete(std::set<const TypeSymbol*>& visited) const
{
    if (visited.find(this) != visited.end()) return true;
    visited.insert(this);
    if (classTypeSymbol)
    {
        return classTypeSymbol->IsComplete(visited);
    }
    else
    {
        return false;
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
    if (!Valid()) return;
    node.ClassHead()->Accept(*this);
}

void ClassResolver::Visit(otava::ast::ClassHeadNode& node)
{
    if (!Valid()) return;
    node.ClassKey()->Accept(*this);
    if (!Valid()) return; 
    node.ClassHeadName()->Accept(*this);
}

void ClassResolver::Visit(otava::ast::IdentifierNode& node)
{
    if (!Valid()) return;
    name = node.Str();
}

void ClassResolver::Visit(otava::ast::TemplateIdNode& node)
{
    if (!Valid()) return;
    node.TemplateName()->Accept(*this);
    if (!Valid()) return;
    auto rv = ResolveType(&node, DeclarationFlags::none, context, TypeResolverFlags::dontInstantiate);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    specialization = *rv;
}

void ClassResolver::Visit(otava::ast::ElaboratedTypeSpecifierNode& node)
{
    if (!Valid()) return;
    node.ClassKey()->Accept(*this);
    if (!Valid()) return;
    name = node.Id()->Str();
}

void ClassResolver::Visit(otava::ast::ClassNode& node)
{
    if (!Valid()) return;
    classKind = otava::symbols::ClassKind::class_;
}

void ClassResolver::Visit(otava::ast::StructNode& node)
{
    if (!Valid()) return;
    classKind = otava::symbols::ClassKind::struct_;
}

void ClassResolver::Visit(otava::ast::UnionNode& node)
{
    if (!Valid()) return;
    classKind = otava::symbols::ClassKind::union_;
}

class BaseClassResolver : public otava::ast::DefaultVisitor
{
public:
    BaseClassResolver(Context* context_);
    void Visit(otava::ast::BaseSpecifierNode& node) override;
    std::vector<ClassTypeSymbol*> BaseClasses() const { return std::move(baseClasses); }
private:
    Context* context;
    std::vector<ClassTypeSymbol*> baseClasses;
};

BaseClassResolver::BaseClassResolver(Context* context_) : context(context_)
{
}

void BaseClassResolver::Visit(otava::ast::BaseSpecifierNode& node)
{
    if (!Valid()) return;
    auto rv = ResolveType(node.ClassOrDeclType(), DeclarationFlags::none, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    TypeSymbol* baseClassType = *rv;
    if (baseClassType->IsClassTypeSymbol())
    {
        ClassTypeSymbol* baseClass = static_cast<ClassTypeSymbol*>(baseClassType);
        baseClasses.push_back(baseClass);
    }
    else
    {
        std::unexpected<int> result = Error("class type symbol expected", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

std::expected<bool, int> GetClassAttributes(otava::ast::Node* node, std::u32string& name, otava::symbols::ClassKind& kind, TypeSymbol*& specialization, Context* context)
{
    ClassResolver resolver(context);
    node->Accept(resolver);
    name = resolver.GetName();
    kind = resolver.GetClassKind();
    if (!resolver) return std::unexpected<int>(resolver.Error());
    specialization = resolver.Specialization();
    return std::expected<bool, int>(true);
}

std::expected<std::vector<ClassTypeSymbol*>, int> ResolveBaseClasses(otava::ast::Node* node, Context* context)
{
    BaseClassResolver resolver(context);
    node->Accept(resolver);
    if (!resolver) return std::unexpected<int>(resolver.Error());
    return std::expected<std::vector<ClassTypeSymbol*>, int>(resolver.BaseClasses());
}

std::expected<bool, int> BeginClass(otava::ast::Node* node, Context* context)
{
    std::u32string name;
    otava::symbols::ClassKind kind;
    TypeSymbol* specialization = nullptr;
    std::expected<bool, int> rv = GetClassAttributes(node, name, kind, specialization, context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->BeginClass(name, kind, specialization, node, context);
    if (!rv) return rv;
    std::expected<std::vector<ClassTypeSymbol*>, int> brv = ResolveBaseClasses(node, context);
    if (!brv) return std::unexpected<int>(brv.error());
    std::vector<ClassTypeSymbol*> baseClasses = std::move(*brv);
    for (ClassTypeSymbol* baseClass : baseClasses)
    {
        rv = context->GetSymbolTable()->AddBaseClass(baseClass, node->GetSourcePos(), context);
        if (!rv) return rv;
    }
    context->PushSetFlag(ContextFlags::parseMemberFunction);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EndClass(otava::ast::Node* node, Context* context)
{
    Symbol* symbol = context->GetSymbolTable()->CurrentScope()->GetSymbol();
    if (!symbol->IsClassTypeSymbol())
    {
        return Error("otava.symbols.classes: EndClass(): class scope expected", node->GetSourcePos(), context);
    }
    ClassTypeSymbol* classTypeSymbol = static_cast<ClassTypeSymbol*>(symbol);
    // AddClassInfo(classTypeSymbol, context); todo
    otava::ast::Node* specNode = context->GetSymbolTable()->GetSpecifierNode(classTypeSymbol);
    if (specNode && specNode->IsClassSpecifierNode())
    {
        otava::ast::ClassSpecifierNode* specifierNode = static_cast<otava::ast::ClassSpecifierNode*>(specNode);
        specifierNode->SetComplete();
    }
    else
    {
        return Error("otava.symbols.classes: EndClass(): class specifier node expected", node->GetSourcePos(), context);
    }
    if (!classTypeSymbol->IsTemplate() && !classTypeSymbol->HasUserDefinedDestructor())
    {
        std::set<const TypeSymbol*> visited;
        if (classTypeSymbol->IsComplete(visited))
        {
            std::expected<Symbol*, int> rv = GenerateDestructor(classTypeSymbol, node->GetSourcePos(), context);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        else
        {
            context->GetBoundCompileUnit()->AddClassToGenerateDestructorList(classTypeSymbol);
        }
    }
    context->PopFlags();
    std::expected<bool, int> rv = context->GetSymbolTable()->EndClass();
    if (!rv) return rv;
    if (classTypeSymbol->Level() == 0)
    {
        rv = ParseInlineMemberFunctions(specNode, classTypeSymbol, context);
        if (!rv) return rv;
    }
    std::set<const Symbol*> visited;
    if (!classTypeSymbol->IsTemplate() && !classTypeSymbol->IsTemplateParameterInstantiation(context, visited))
    {
        std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNodeForClass(classTypeSymbol, node->GetSourcePos(), context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ProcessElaboratedClassDeclaration(otava::ast::Node* node, otava::symbols::Context* context)
{
    std::u32string name;
    otava::symbols::ClassKind kind;
    TypeSymbol* specialization = nullptr;
    std::expected<bool, int> rv = GetClassAttributes(node, name, kind, specialization, context);
    if (!rv) return rv;
    if (context->GetFlag(ContextFlags::friendSpecifier))
    {
        rv = context->GetSymbolTable()->AddFriend(name, node, context);
        if (!rv) return rv;
    }
    else
    {
        rv = context->GetSymbolTable()->AddForwardClassDeclaration(name, kind, specialization, node, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
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
    std::expected<Symbol*, int> s = context->GetSymbolTable()->GetSymbol(&node);
    if (!s)
    {
        SetError(s.error());
        return;
    }
    Symbol* symbol = *s;
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
    FunctionSymbol* functionSymbol = nullptr;
    if (symbol->IsFunctionSymbol())
    {
        functionSymbol = static_cast<FunctionSymbol*>(symbol);
    }
    else
    {
        std::unexpected<int> rv = Error("function symbol expected", node.GetSourcePos(), context);
        SetError(rv.error());
        return;
    }
    if (!context->GetFlag(ContextFlags::parsingTemplateDeclaration) && functionSymbol->IsFunctionDefinitionSymbol())
    {
        FunctionDefinitionSymbol* functionDefinitionSymbol = static_cast<FunctionDefinitionSymbol*>(functionSymbol);
        context->PushBoundFunction(new BoundFunctionNode(functionDefinitionSymbol, node.GetSourcePos()));
        std::expected<FunctionDefinitionSymbol*, int> rv = BindFunction(&node, functionDefinitionSymbol, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        functionDefinitionSymbol = *rv;
        std::unique_ptr<BoundNode> boundFunctionNode(context->ReleaseBoundFunction());
        if (functionDefinitionSymbol->IsBound())
        {
            std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::move(boundFunctionNode), context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
        context->PopBoundFunction();
    }
}

std::expected<bool, int> ParseInlineMemberFunctions(otava::ast::Node* classSpecifierNode, ClassTypeSymbol* classTypeSymbol, otava::symbols::Context* context)
{
    context->GetSymbolTable()->BeginScope(classTypeSymbol->GetScope());
    InlineMemberFunctionParserVisitor visitor(context);
    classSpecifierNode->Accept(visitor);
    if (!visitor) return std::unexpected<int>(visitor.Error());
    std::expected<bool, int> erv = context->GetSymbolTable()->EndScope();
    if (!erv) return std::unexpected<int>(erv.error());
    return std::expected<bool, int>(true);
}

bool ClassLess::operator()(ClassTypeSymbol* left, ClassTypeSymbol* right) const
{
    return left->Name() < right->Name();
}

std::unexpected<int> ReturnMemberDeclarationParsingError(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    return Error("class member declaration parsing error", sourcePos, context);
}

std::unexpected<int> ReturnStatementParsingError(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    return Error("statement parsing error", sourcePos, context);
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

std::expected<Symbol*, int> GenerateDestructor(ClassTypeSymbol* classTypeSymbol, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<Symbol*, int> lrv = classTypeSymbol->GetScope()->Lookup(U"@destructor", SymbolGroupKind::functionSymbolGroup, ScopeLookup::thisScope, sourcePos, 
        context, LookupFlags::dontResolveSingle);
    if (!lrv) return lrv;
    Symbol* dtorFunctionGroupSymbol = *lrv;
    Symbol* destructorFn = nullptr;
    if (dtorFunctionGroupSymbol && dtorFunctionGroupSymbol->IsFunctionGroupSymbol())
    {
        FunctionGroupSymbol* destructorGroup = static_cast<FunctionGroupSymbol*>(dtorFunctionGroupSymbol);
        destructorFn = destructorGroup->GetSingleDefinition();
        if (destructorFn)
        {
            return std::expected<Symbol*, int>(destructorFn);
        }
        destructorFn = destructorGroup->GetSingleSymbol();
        if (destructorFn && destructorFn != destructorGroup)
        {
            return std::expected<Symbol*, int>(destructorFn);
        }
    }
    if (classTypeSymbol->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(classTypeSymbol);
        std::set<const Symbol*> visited;
        if (!sp->IsTemplateParameterInstantiation(context, visited))
        {
            if (!sp->Destructor())
            {
                std::set<const TypeSymbol*> visited;
                if (sp->IsComplete(visited))
                {
                    std::expected<bool, int> rv = InstantiateDestructor(sp, sourcePos, context);
                    if (!rv) return std::unexpected<int>(rv.error());
                }
            }
            destructorFn = sp->Destructor();
            if (destructorFn)
            {
                return std::expected<Symbol*, int>(destructorFn);
            }
        }
    }
    std::unique_ptr<TrivialClassDtor> trivialClassDestructor(new TrivialClassDtor());
    int nm = classTypeSymbol->MemberVariables().size();
    int nb = classTypeSymbol->BaseClasses().size();
    if (nm == 0 && nb == 0)
    {
        std::expected<FunctionGroupSymbol*, int> frv = classTypeSymbol->GetScope()->GroupScope()->GetOrInsertFunctionGroup(U"@destructor", sourcePos, context);
        if (!frv) return std::unexpected<int>(frv.error());
        FunctionGroupSymbol* functionGroup = *frv;
        Symbol* destructorSymbol = trivialClassDestructor.get();
        functionGroup->AddFunction(trivialClassDestructor.get());
        std::expected<bool, int> rv = classTypeSymbol->AddSymbol(trivialClassDestructor.release(), sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        return std::expected<Symbol*, int>(destructorSymbol);
    }
    bool hasNonTrivialDestructor = false;
    std::unique_ptr<FunctionSymbol> destructorSymbol(new FunctionSymbol(U"@destructor"));
    destructorSymbol->SetParent(classTypeSymbol);
    destructorSymbol->SetFunctionKind(FunctionKind::destructor);
    destructorSymbol->SetAccess(Access::public_);
    destructorSymbol->SetCompileUnitId(context->GetBoundCompileUnit()->Id());
    std::expected<std::string, int> is = destructorSymbol->IrName(context);
    if (!is) return std::unexpected<int>(is.error());
    destructorSymbol->SetFixedIrName(*is);
    std::unique_ptr<FunctionDefinitionSymbol> destructorDefinitionSymbol(new FunctionDefinitionSymbol(U"@destructor"));
    destructorDefinitionSymbol->SetParent(classTypeSymbol);
    destructorDefinitionSymbol->SetFunctionKind(FunctionKind::destructor);
    destructorDefinitionSymbol->SetAccess(Access::public_);
    destructorDefinitionSymbol->SetDeclaration(destructorSymbol.get());
    destructorDefinitionSymbol->SetCompileUnitId(context->GetBoundCompileUnit()->Id());
    destructorDefinitionSymbol->SetFixedIrName(*is);
    std::unique_ptr<BoundDtorTerminatorNode> terminator(new BoundDtorTerminatorNode(sourcePos));
    for (int i = nm - 1; i >= 0; --i)
    {
        VariableSymbol* memberVar = classTypeSymbol->MemberVariables()[i];
        if (memberVar->GetType()->IsPointerType() || memberVar->GetType()->IsReferenceType()) continue;
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        if (memberVar->GetType()->IsClassTypeSymbol())
        {
            ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(memberVar->GetType());
            std::expected<Symbol*, int> rv = GenerateDestructor(classType, sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        BoundVariableNode* boundVariableNode = new BoundVariableNode(memberVar, sourcePos);
        std::expected<ParameterSymbol*, int> tp = destructorDefinitionSymbol->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        TypeSymbol* referredType = *rrv;
        BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, referredType);
        boundVariableNode->SetThisPtr(thisPtr);
        std::expected<TypeSymbol*, int> pt = boundVariableNode->GetType()->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariableNode, sourcePos, *pt)));
        std::vector<TypeSymbol*> templateArgs;
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> rv = ResolveOverload(
            context->GetSymbolTable()->CurrentScope(), U"@destructor", templateArgs, args, sourcePos, context);
        if (rv)
        {
            std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = std::move(*rv);
            if (!boundFunctionCall->GetFunctionSymbol()->GetFlag(FunctionSymbolFlags::trivialDestructor))
            {
                hasNonTrivialDestructor = true;
                terminator->AddMemberTerminator(boundFunctionCall.release());
            }
        }
    }
    for (int i = nb - 1; i >= 0; --i)
    {
        ClassTypeSymbol* baseClass = classTypeSymbol->BaseClasses()[i];
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::expected<ParameterSymbol*, int> tp = destructorDefinitionSymbol->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, thisParam->GetType());
        std::expected<TypeSymbol*, int> pt = baseClass->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        std::expected<FunctionSymbol*, int> rv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            *pt, thisPtr->GetType(), sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        FunctionSymbol* conversion = *rv;
        if (conversion)
        {
            std::expected<Symbol*, int> rv = GenerateDestructor(baseClass, sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            std::vector<TypeSymbol*> templateArgs;
            std::expected<std::unique_ptr<BoundFunctionCallNode>, int> rrv = ResolveOverload(
                context->GetSymbolTable()->CurrentScope(), U"@destructor", templateArgs, args, sourcePos, context);
            if (rrv)
            {
                std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = std::move(*rrv);
                if (!boundFunctionCall->GetFunctionSymbol()->GetFlag(FunctionSymbolFlags::trivialDestructor))
                {
                    hasNonTrivialDestructor = true;
                    terminator->AddMemberTerminator(boundFunctionCall.release());
                }
            }
        }
        else
        {
            return Error("base class conversion not found", sourcePos, context);
        }
    }
    if (!hasNonTrivialDestructor)
    {
        std::expected<FunctionGroupSymbol*, int> frv = classTypeSymbol->GetScope()->GroupScope()->GetOrInsertFunctionGroup(U"@destructor", sourcePos, context);
        if (!frv)  return std::unexpected<int>(frv.error());
        FunctionGroupSymbol* functionGroup = *frv;
        FunctionSymbol* trivialDestructor = trivialClassDestructor.get();
        functionGroup->AddFunction(trivialClassDestructor.get());
        std::expected<bool, int> rv = classTypeSymbol->AddSymbol(trivialClassDestructor.release(), sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        return std::expected<Symbol*, int>(trivialDestructor);
    }
    BoundFunctionNode* boundDestructor = new BoundFunctionNode(destructorDefinitionSymbol.get(), sourcePos);
    std::expected<FunctionGroupSymbol*, int> frv = classTypeSymbol->GetScope()->GroupScope()->GetOrInsertFunctionGroup(U"@destructor", sourcePos, context);
    if (!frv)  return std::unexpected<int>(frv.error());
    FunctionGroupSymbol* functionGroup = *frv;
    functionGroup->AddFunction(destructorSymbol.get());
    FunctionSymbol* destructor = destructorDefinitionSymbol.get();
    std::expected<bool, int> rv = classTypeSymbol->AddSymbol(destructorSymbol.release(), sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    functionGroup->AddFunctionDefinition(destructorDefinitionSymbol.get(), context);
    rv = classTypeSymbol->AddSymbol(destructorDefinitionSymbol.release(), sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
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
            std::expected<bool, int> rv = classTypeSymbol->MakeObjectLayout(sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        std::vector<ClassTypeSymbol*> vptrHolderClasses = classTypeSymbol->VPtrHolderClasses();
        if (vptrHolderClasses.empty())
        {
            std::expected<std::u32string, int> fname = classTypeSymbol->FullName();
            if (!fname) return std::unexpected<int>(fname.error());
            std::expected<std::string, int> sfname = util::ToUtf8(*fname);
            if (!sfname) return std::unexpected<int>(sfname.error());
            return Error("no vptr holder classes for the class '" + *sfname + "'", sourcePos, context);
        }
        for (ClassTypeSymbol* vptrHolderClass : vptrHolderClasses)
        {
            if (vptrHolderClass != classTypeSymbol)
            {
                std::expected<ParameterSymbol*, int> tp = destructor->ThisParam(context);
                if (!tp) return std::unexpected<int>(tp.error());
                ParameterSymbol* thisParam = *tp;
                std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
                if (!rrv) return std::unexpected<int>(rrv.error());
                TypeSymbol* referredType = *rrv;
                BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, referredType);
                std::expected<TypeSymbol*, int> pt = vptrHolderClass->AddPointer(context);
                if (!pt) return std::unexpected<int>(pt.error());
                std::expected<FunctionSymbol*, int> rv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    *pt, thisPtr->GetType(), sourcePos, context);
                if (!rv) return std::unexpected<int>(rv.error());
                FunctionSymbol* conversion = *rv;
                if (conversion)
                {
                    BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr, conversion, sourcePos);
                    BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtrConverted, classTypeSymbol, vptrHolderClass, sourcePos);
                    body->AddStatement(setVPtrStatement);
                }
                else
                {
                    return Error("vptr holder class conversion not found", sourcePos, context);
                }
            }
            else
            {
                std::expected<ParameterSymbol*, int> tp = destructor->ThisParam(context);
                if (!tp) return std::unexpected<int>(tp.error());
                ParameterSymbol* thisParam = *tp;
                std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
                if (!rrv) return std::unexpected<int>(rrv.error());
                TypeSymbol* referredType = *rrv;
                BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, referredType);
                BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtr, classTypeSymbol, classTypeSymbol, sourcePos);
                body->AddStatement(setVPtrStatement);
            }
        }
    }
    boundDestructor->SetBody(body);
    boundDestructor->SetDtorTerminator(terminator.release());
    std::expected<bool, int> nrv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(boundDestructor), context);
    if (!nrv) return std::unexpected<int>(nrv.error());
    return std::expected<Symbol*, int>(destructor);
}

std::expected<bool, int> GenerateDestructors(BoundCompileUnitNode* boundCompileUnit, Context* context)
{
    for (ClassTypeSymbol* classType : boundCompileUnit->GenerateDestructorList())
    {
        soul::ast::SourcePos sourcePos;
        std::expected<TypeSymbol*, int> rv = classType->FinalType(sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        TypeSymbol* finalType = *rv;
        if (finalType->IsClassTypeSymbol())
        {
            ClassTypeSymbol* finalClass = static_cast<ClassTypeSymbol*>(finalType);
            std::expected<Symbol*, int> rv = GenerateDestructor(finalClass, sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
        }
    }
    return std::expected<bool, int>(true);
}

/*
void AddClassInfo(ClassTypeSymbol* classTypeSymbol, Context* context)
{
    std::uint64_t clsidh = 0;
    std::uint64_t clsidl = 0;
    util::UuidToInts(classTypeSymbol->Id(), clsidh, clsidl);
    ClassKind kind = classTypeSymbol->GetClassKind();
    info::class_id id = std::make_pair(clsidh, clsidl);
    info::class_key key = info::class_key::cls;
    switch (kind)
    {
        case ClassKind::class_: key = info::class_key::cls; break;
        case ClassKind::struct_: key = info::class_key::strct; break;
        case ClassKind::union_: key = info::class_key::uni; break;
    }
    info::class_info info(id, key, util::ToUtf8(classTypeSymbol->FullName()));
    for (const auto& base : classTypeSymbol->BaseClasses())
    {
        std::uint64_t h = 0;
        std::uint64_t l = 0;
        util::UuidToInts(base->Id(), h, l);
        info.add_base(std::make_pair(h, l));
    }
    context->GetSymbolTable()->ClassIndex().add_class(info);
}
*/

std::expected<std::int64_t, int> Delta(ClassTypeSymbol* left, ClassTypeSymbol* right, Emitter& emitter, Context* context)
{
    std::expected<std::int64_t, int> rv = left->Delta(right, emitter, context);
    if (rv)
    {
        return rv;
    }
    rv = right->Delta(left, emitter, context);
    if (rv)
    {
        std::int64_t rdelta = *rv;
        return std::expected<std::int64_t, int>(-rdelta);
    }
    return std::unexpected<int>(util::AllocateError("delta not found"));
}

} // namespace otava::symbols
