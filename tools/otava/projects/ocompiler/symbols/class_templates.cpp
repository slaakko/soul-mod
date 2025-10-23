// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.class_templates;

import otava.symbols.bound.tree;
import otava.symbols.modules;
import otava.symbols.context;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.symbol.table;
import otava.symbols.error;
import otava.symbols.templates;
import otava.symbols.declaration;
import otava.symbols.type.resolver;
import otava.symbols.compound.type.symbol;
import otava.symbols.instantiator;
import otava.symbols.statement.binder;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.visitor;
import otava.symbols.namespaces;
import otava.symbols.function.group.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
import otava.ast;
import util.unicode;
import util.sha1;

namespace otava::symbols {

ClassTemplateSpecializationSymbol::ClassTemplateSpecializationSymbol(const std::u32string& name_) :
    ClassTypeSymbol(SymbolKind::classTemplateSpecializationSymbol, name_),
    classTemplate(nullptr), instantiated(false), destructor(nullptr), instantiatingDestructor(false)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

ClassTemplateSpecializationSymbol::ClassTemplateSpecializationSymbol(const util::uuid& id_, const std::u32string& name_) :
    ClassTypeSymbol(SymbolKind::classTemplateSpecializationSymbol, id_, name_),
    classTemplate(nullptr), instantiated(false), destructor(nullptr), instantiatingDestructor(false)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

void ClassTemplateSpecializationSymbol::SetClassTemplate(ClassTypeSymbol* classTemplate_)
{
    classTemplate = classTemplate_;
}

void ClassTemplateSpecializationSymbol::AddTemplateArgument(Symbol* templateArgument)
{
    templateArguments.push_back(templateArgument);
}

std::expected<std::string, int> ClassTemplateSpecializationSymbol::IrName(Context* context) const
{
    std::expected<std::string, int> rv = classTemplate->IrName(context);
    if (!rv) return rv;
    std::string fullIrName = *rv;
    std::string shaMaterial;
    for (Symbol* templateArg : templateArguments)
    {
        rv = templateArg->IrName(context);
        if (!rv) return rv;
        shaMaterial.append(1, '.').append(*rv);
    }
    shaMaterial.append(".").append(context->GetBoundCompileUnit()->Id());
    fullIrName.append(1, '_').append(util::GetSha1MessageDigest(shaMaterial));
    return std::expected<std::string, int>(fullIrName);
}

std::expected<bool, int> ClassTemplateSpecializationSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = ClassTypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(instantiated);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(classTemplate->Id());
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(static_cast<std::uint32_t>(templateArguments.size()));
    if (!rv) return rv;
    for (Symbol* templateArg : templateArguments)
    {
        if (templateArg->IsTypeSymbol())
        {
            rv = writer.GetBinaryStreamWriter().Write(true);
            if (!rv) return rv;
            rv = writer.GetBinaryStreamWriter().Write(templateArg->Id());
            if (!rv) return rv;
        }
        else
        {
            rv = writer.GetBinaryStreamWriter().Write(false);
            if (!rv) return rv;
            rv = writer.GetBinaryStreamWriter().Write(templateArg->Id());
            if (!rv) return rv;
        }
    }
    if (destructor)
    {
        rv = writer.GetBinaryStreamWriter().Write(destructor->Id());
        if (!rv) return rv;
    }
    else
    {
        rv = writer.GetBinaryStreamWriter().Write(util::nil_uuid());
        if (!rv) return rv;
    }
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(static_cast<std::uint32_t>(instantiatedVirtualFunctionSpecializations.size()));
    if (!rv) return rv;
    for (FunctionSymbol* nf : instantiatedVirtualFunctionSpecializations)
    {
        rv = writer.GetBinaryStreamWriter().Write(nf->Id());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ClassTemplateSpecializationSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = ClassTypeSymbol::Read(reader);
    if (!rv) return rv;
    ids.clear();
    std::expected<bool, int> brv = reader.GetBinaryStreamReader().ReadBool();
    if (!brv) return brv;
    instantiated = *brv;
    util::uuid id;
    rv = reader.GetBinaryStreamReader().ReadUuid(id);
    if (!rv) return rv;
    ids.push_back(std::make_pair(id, true));
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::int32_t count = static_cast<std::int32_t>(*urv);
    for (std::int32_t i = 0; i < count; ++i)
    {
        util::uuid id;
        brv = reader.GetBinaryStreamReader().ReadBool();
        if (!brv) return brv;
        bool isType = *brv;
        rv = reader.GetBinaryStreamReader().ReadUuid(id);
        if (!rv) return rv;
        ids.push_back(std::make_pair(id, isType));
    }
    rv = reader.GetBinaryStreamReader().ReadUuid(destructorId);
    if (!rv) return rv;
    instantiatedVirtualFunctionSpecializationIds.clear();
    urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::int32_t nfids = static_cast<std::int32_t>(*urv);
    for (std::int32_t i = 0; i < nfids; ++i)
    {
        util::uuid vfid;
        rv = reader.GetBinaryStreamReader().ReadUuid(vfid);
        if (!rv) return rv;
        instantiatedVirtualFunctionSpecializationIds.push_back(vfid);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ClassTemplateSpecializationSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = ClassTypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    classTemplate = static_cast<ClassTypeSymbol*>(symbolTable.GetType(ids[0].first));
    if (classTemplate)
    {
        for (int i = 1; i < ids.size(); ++i)
        {
            const std::pair<util::uuid, bool>& idType = ids[i];
            if (idType.second)
            {
                TypeSymbol* templateArg = symbolTable.GetType(idType.first);
                if (templateArg)
                {
                    templateArguments.push_back(templateArg);
                }
                else
                {
                    std::cout << "ClassTemplateSpecializationSymbol::Resolve(): warning: template argument not resolved" << "\n";
                }
            }
            else
            {
                EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
                Value* value = evaluationContext->GetValue(idType.first);
                templateArguments.push_back(value);
            }
        }
        if (destructorId != util::nil_uuid())
        {
            destructor = symbolTable.GetFunctionDefinition(destructorId);
        }
        for (const auto& vfId : instantiatedVirtualFunctionSpecializationIds)
        {
            FunctionSymbol* vf = symbolTable.GetFunction(vfId);
            if (vf)
            {
                instantiatedVirtualFunctionSpecializations.push_back(vf);
            }
        }
    }
    else
    {
        std::cout << "ClassTemplateSpecializationSymbol::Resolve(): warning: class template not resolved" << "\n";
    }
    return std::expected<bool, int>(true);
}

void ClassTemplateSpecializationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeSymbol* ClassTemplateSpecializationSymbol::UnifyTemplateArgumentType(const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, Context* context)
{
    std::vector<Symbol*> targetTemplateArguments;
    for (int i = 0; i < templateArguments.size(); ++i)
    {
        Symbol* sourceTemplateArgumentSymbol = templateArguments[i];
        TypeSymbol* sourceTemplateArgumentType = nullptr;
        if (sourceTemplateArgumentSymbol->IsTypeSymbol())
        {
            sourceTemplateArgumentType = static_cast<TypeSymbol*>(sourceTemplateArgumentSymbol);
        }
        else
        {
            return nullptr;
        }
        TypeSymbol* templateArgumentType = sourceTemplateArgumentType->UnifyTemplateArgumentType(templateParameterMap, context);
        if (templateArgumentType)
        {
            targetTemplateArguments.push_back(templateArgumentType);
        }
        else
        {
            return nullptr;
        }
    }
    return context->GetSymbolTable()->MakeClassTemplateSpecialization(classTemplate, targetTemplateArguments);
}

bool ClassTemplateSpecializationSymbol::IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const
{
    if (visited.find(this) == visited.end())
    {
        if (ClassTypeSymbol::IsTemplateParameterInstantiation(context, visited)) return true;
        for (Symbol* templateArg : templateArguments)
        {
            if (templateArg->IsTemplateParameterInstantiation(context, visited)) return true;
        }
    }
    return false;
}

std::expected<TypeSymbol*, int> ClassTemplateSpecializationSymbol::FinalType(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::vector<Symbol*> templateArgs;
    for (Symbol* templateArg : templateArguments)
    {
        if (templateArg->IsTypeSymbol())
        {
            TypeSymbol* typeTemplateArg = static_cast<TypeSymbol*>(templateArg);
            std::expected<TypeSymbol*, int> rv = typeTemplateArg->DirectType(context)->FinalType(sourcePos, context);
            if (!rv) return rv;
            TypeSymbol* finalType = *rv;
            typeTemplateArg = finalType;
            templateArgs.push_back(typeTemplateArg);
        }
        else
        {
            templateArgs.push_back(templateArg);
        }
    }
    std::expected<ClassTemplateSpecializationSymbol*, int> rv = InstantiateClassTemplate(classTemplate, templateArgs, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    ClassTemplateSpecializationSymbol* specialization = *rv;
    return std::expected<TypeSymbol*, int>(specialization);
}

bool ClassTemplateSpecializationSymbol::IsComplete(std::set<const TypeSymbol*>& visited) const
{
    if (visited.find(this) != visited.end()) return true;
    visited.insert(this);
    for (Symbol* templateArg : templateArguments)
    {
        if (templateArg->IsTypeSymbol())
        {
            TypeSymbol* templateArgType = static_cast<TypeSymbol*>(templateArg);
            if (!templateArgType->IsComplete(visited)) return false;
        }
    }
    return true;
}

void ClassTemplateSpecializationSymbol::AddInstantiatedVirtualFunctionSpecialization(FunctionSymbol* specialization)
{
    if (std::find(instantiatedVirtualFunctionSpecializations.begin(), instantiatedVirtualFunctionSpecializations.end(), specialization) ==
        instantiatedVirtualFunctionSpecializations.end())
    {
        instantiatedVirtualFunctionSpecializations.push_back(specialization);
    }
}

FunctionSymbol* ClassTemplateSpecializationSymbol::GetMatchingVirtualFunctionSpecialization(FunctionSymbol* newcomer, Context* context) const
{
    bool found = false;
    bool def = newcomer->IsFunctionDefinitionSymbol();
    for (FunctionSymbol* prev : instantiatedVirtualFunctionSpecializations)
    {
        bool prevDef = prev->IsFunctionDefinitionSymbol();
        if (def == prevDef && FunctionMatches(newcomer, prev, context))
        {
            return prev;
        }
    }
    return nullptr;
}

bool ClassTemplateSpecializationSymbol::ContainsVirtualFunctionSpecialization(FunctionSymbol* specialization) const
{
    for (FunctionSymbol* instance : instantiatedVirtualFunctionSpecializations)
    {
        if (instance == specialization) return true;
    }
    return false;
}

util::uuid MakeClassTemplateSpecializationSymbolId(ClassTypeSymbol* classTemplate, const std::vector<Symbol*>& templateArguments, int level, SymbolTable& symbolTable)
{
    util::uuid id = classTemplate->Id();
    int n = static_cast<int>(templateArguments.size());
    for (int i = 0; i < n; ++i)
    {
        Symbol* arg = templateArguments[i];
        util::uuid argId = arg->Id();
        if (arg->IsClassTemplateSpecializationSymbol())
        {
            ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(arg);
            argId = MakeClassTemplateSpecializationSymbolId(sp->ClassTemplate(), sp->TemplateArguments(), level + 1, symbolTable);
        }
        util::Rotate(argId, (i + level + 1) & (util::uuid::static_size() - 1));
        util::Xor(id, argId);
    }
    util::Xor(id, symbolTable.GetLevelId(level));
    return id;
}

util::uuid MakeClassTemplateSpecializationSymbolId(ClassTypeSymbol* classTemplate, const std::vector<Symbol*>& templateArguments, SymbolTable& symbolTable)
{
    return MakeClassTemplateSpecializationSymbolId(classTemplate, templateArguments, 0, symbolTable);
}

std::u32string MakeSpecializationName(TypeSymbol* templateSymbol, const std::vector<Symbol*>& templateArguments)
{
    std::u32string specializationName;
    specializationName.append(templateSymbol->Name());
    specializationName.append(1, '<');
    bool first = true;
    for (Symbol* templateArg : templateArguments)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            specializationName.append(U", ");
        }
        specializationName.append(templateArg->Name());
    }
    specializationName.append(1, '>');
    return specializationName;
}

CompoundTypeSymbol* GetCompoundSpecializationArgType(TypeSymbol* specialization, int index)
{
    if (specialization->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specializationSymbol = static_cast<ClassTemplateSpecializationSymbol*>(specialization);
        if (index >= 0 && index < specializationSymbol->TemplateArguments().size())
        {
            Symbol* specializationArg = specializationSymbol->TemplateArguments()[index];
            if (specializationArg->IsCompoundTypeSymbol())
            {
                CompoundTypeSymbol* specializationArgType = static_cast<CompoundTypeSymbol*>(specializationArg);
                return specializationArgType;
            }
        }
    }
    return nullptr;
}

ClassTemplateSpecializationSymbol* GetClassTemplateSpecializationArgType(TypeSymbol* specialization, int index)
{
    if (specialization->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specializationSymbol = static_cast<ClassTemplateSpecializationSymbol*>(specialization);
        if (index >= 0 && index < specializationSymbol->TemplateArguments().size())
        {
            Symbol* specializationArg = specializationSymbol->TemplateArguments()[index];
            if (specializationArg->IsClassTemplateSpecializationSymbol())
            {
                ClassTemplateSpecializationSymbol* specializationArgType = static_cast<ClassTemplateSpecializationSymbol*>(specializationArg);
                return specializationArgType;
            }
        }
    }
    return nullptr;
}

std::expected<bool, int> InstantiateDestructor(ClassTemplateSpecializationSymbol* specialization, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::set<const Symbol*> tpi_visited;
    if (specialization->IsTemplateParameterInstantiation(context, tpi_visited)) return;
    if (specialization->Destructor()) return;
    std::set<const TypeSymbol*> visited;
    if (!specialization->IsComplete(visited)) return;
    if (specialization->InstantiatingDestructor()) return;
    specialization->SetInstantiatingDestructor(true);
    context->PushResetFlag(ContextFlags::skipFunctionDefinitions);
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    ClassTypeSymbol* classTemplate = specialization->ClassTemplate();
    std::expected<Symbol*, int> drv = classTemplate->GetScope()->Lookup(U"@destructor", SymbolGroupKind::functionSymbolGroup, ScopeLookup::thisScope, sourcePos, 
        context, LookupFlags::dontResolveSingle);
    if (!drv) return std::unexpected<int>(drv.error());
    Symbol* destructor = *drv;
    if (destructor && destructor->IsFunctionGroupSymbol())
    {
        FunctionGroupSymbol* destructorGroup = static_cast<FunctionGroupSymbol*>(destructor);
        FunctionDefinitionSymbol* destructorFn = destructorGroup->GetSingleDefinition();
        if (destructorFn)
        {
            std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
            std::expected< FunctionSymbol*, int> rv = InstantiateMemFnOfClassTemplate(destructorFn, specialization, templateParameterMap, sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
            FunctionSymbol* instantiatedDestructor = *rv;
            instantiatedDestructor->SetFlag(FunctionSymbolFlags::fixedIrName);
            std::expected<std::string, int> irv = instantiatedDestructor->IrName(context);
            if (!irv) return std::unexpected<int>(irv.error());
            std::string irName = *irv;
            specialization->SetDestructor(instantiatedDestructor);
        }
    }
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    context->PopFlags();
    specialization->SetInstantiatingDestructor(false);
    return std::expected<bool, int>(true);
}

class VirtualFunctionNodeClassifierVisitor : public otava::ast::DefaultVisitor
{
public:
    VirtualFunctionNodeClassifierVisitor();
    void Visit(otava::ast::VirtualNode& node);
    void Visit(otava::ast::OverrideNode& node);
    void Visit(otava::ast::FinalNode& node);
    bool GetValue() const { return value; }
private:
    bool value;
};

VirtualFunctionNodeClassifierVisitor::VirtualFunctionNodeClassifierVisitor() : value(false)
{
}

void VirtualFunctionNodeClassifierVisitor::Visit(otava::ast::VirtualNode& node)
{
    value = true;
}

void VirtualFunctionNodeClassifierVisitor::Visit(otava::ast::OverrideNode& node)
{
    value = true;
}

void VirtualFunctionNodeClassifierVisitor::Visit(otava::ast::FinalNode& node)
{
    value = true;
}

bool IsVirtualFunctionNode(otava::ast::Node* node)
{
    VirtualFunctionNodeClassifierVisitor visitor;
    node->Accept(visitor);
    return visitor.GetValue();
}

std::expected<bool, int> InstantiateVirtualFunctions(ClassTemplateSpecializationSymbol* specialization, const soul::ast::SourcePos& sourcePos, Context* context)
{
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    std::set<const Symbol*> visited;
    std::vector<FunctionSymbol*> virtualFunctions;
    if (!specialization->IsTemplateParameterInstantiation(context, visited))
    {
        ClassTypeSymbol* classTemplate = specialization->ClassTemplate();
        for (FunctionSymbol* memFn : classTemplate->MemberFunctions())
        {
            otava::ast::Node* node = context->GetSymbolTable()->GetNode(memFn);
            if (node && IsVirtualFunctionNode(node))
            {
                virtualFunctions.push_back(memFn);
            }
        }
    }
    for (FunctionSymbol* virtualMemFn : virtualFunctions)
    {
        std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
        std::expected<FunctionSymbol*, int> rv = InstantiateMemFnOfClassTemplate(virtualMemFn, specialization, templateParameterMap, sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        FunctionSymbol* instance = *rv;
        specialization->AddInstantiatedVirtualFunctionSpecialization(instance);
    }
    if (!virtualFunctions.empty())
    {
        std::expected<bool, int> rv = specialization->MakeVTab(context, sourcePos);
        if (!rv) return rv;
    }
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    return std::expected<bool, int>(true);
}

std::expected<ClassTemplateSpecializationSymbol*, int> InstantiateClassTemplate(ClassTypeSymbol* classTemplate, const std::vector<Symbol*>& templateArgs, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (classTemplate->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(classTemplate);
        classTemplate = specialization->ClassTemplate();
    }
    TemplateDeclarationSymbol* templateDeclaration = classTemplate->ParentTemplateDeclaration();
    if (!templateDeclaration)
    {
        std::expected<std::string, int> name = util::ToUtf8(classTemplate->Name());
        if (!name) return std::unexpected<int>(name.error());
        return Error("otava.symbols.class_templates: template declaration not found from class template '" + *name + "'", sourcePos, context);
    }
    int arity = templateDeclaration->Arity();
    ClassTemplateSpecializationSymbol* specialization = context->GetSymbolTable()->MakeClassTemplateSpecialization(classTemplate, templateArgs);
    int m = templateArgs.size();
    bool wasInstantiated = specialization->Instantiated();
    if (wasInstantiated && arity == m)
    {
        return std::expected<ClassTemplateSpecializationSymbol*, int>(specialization);
    }
    ExplicitInstantiationSymbol* explicitInstantiation = context->GetSymbolTable()->GetExplicitInstantiation(specialization);
    if (explicitInstantiation)
    {
        return std::expected<ClassTemplateSpecializationSymbol*, int>(explicitInstantiation->Specialization());
    }
    otava::ast::Node* classNode = context->GetSymbolTable()->GetSpecifierNode(classTemplate);
    if (!classNode)
    {
        return std::expected<ClassTemplateSpecializationSymbol*, int>(specialization);
    }
    if (classNode->IsClassSpecifierNode())
    {
        otava::ast::ClassSpecifierNode* classSpecifierNode = static_cast<otava::ast::ClassSpecifierNode*>(classNode);
        if (!classSpecifierNode->Complete())
        {
            return std::expected<ClassTemplateSpecializationSymbol*, int>(specialization);
        }
    }
    specialization->SetInstantiated();
    std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNodeForClass(specialization, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    int argCount = templateArgs.size();
    if (argCount > arity)
    {
        std::expected<std::string, int> name = util::ToUtf8(classTemplate->Name());
        if (!name) return std::unexpected<int>(name.error());
        return Error("otava.symbols.class_templates: wrong number of template args for instantiating class template '" + *name + "'", sourcePos, context);
    }
    std::expected<bool, int> prv = specialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope());
    if (!prv) return std::unexpected<int>(prv.error());
    prv = specialization->GetScope()->AddParentScope(specialization->ClassTemplate()->GetScope()->GetNamespaceScope());
    if (!prv) return std::unexpected<int>(prv.error());
    context->GetSymbolTable()->BeginScope(specialization->GetScope());
    InstantiationScope instantiationScope(specialization->GetScope());
    std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
    for (int i = 0; i < arity; ++i)
    {
        TemplateParameterSymbol* templateParameter = templateDeclaration->TemplateParameters()[i];
        Symbol* templateArg = nullptr;
        if (i >= argCount)
        {
            otava::ast::Node* defaultTemplateArgNode = templateParameter->DefaultTemplateArg();
            if (defaultTemplateArgNode)
            {
                context->GetSymbolTable()->BeginScope(&instantiationScope);
                auto rv = ResolveType(defaultTemplateArgNode, DeclarationFlags::none, context);
                if (!rv) return std::unexpected<int>(rv.error());
                templateArg = *rv;
                context->GetSymbolTable()->EndScope();
                if (specialization->TemplateArguments().size() < arity)
                {
                    specialization->AddTemplateArgument(templateArg);
                    context->GetSymbolTable()->UnmapClassTemplateSpecialization(specialization);
                    std::string oldId = util::ToString(specialization->Id());
                    specialization->SetId(MakeClassTemplateSpecializationSymbolId(specialization->ClassTemplate(), specialization->TemplateArguments(),
                        *context->GetSymbolTable()));
                    context->GetSymbolTable()->MapClassTemplateSpecialization(specialization);
                }
            }
            else
            {
                return Error("otava.symbols.templates: template parameter " + std::to_string(i) + " has no default type argument", sourcePos, context);
            }
        }
        else
        {
            templateArg = templateArgs[i];
        }
        if (templateArg->IsTypeSymbol())
        {
            TypeSymbol* templateArgType = static_cast<TypeSymbol*>(templateArg);
            TypeSymbol* specialization = classTemplate->Specialization();
            if (specialization)
            {
                CompoundTypeSymbol* specializationArgType = GetCompoundSpecializationArgType(specialization, i);
                if (specializationArgType)
                {
                    templateArg = templateArgType->RemoveDerivations(specializationArgType->GetDerivations(), context);
                }
                else
                {
                    ClassTemplateSpecializationSymbol* specializationArgType = GetClassTemplateSpecializationArgType(specialization, i);
                    if (!specializationArgType)
                    {
                        return Error("otava.symbols.templates: specialization argument type not resolved", sourcePos, context);
                    }
                }
            }
        }
        BoundTemplateParameterSymbol* boundTemplateParameter = new BoundTemplateParameterSymbol(templateParameter->Name());
        boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
        boundTemplateParameter->SetBoundSymbol(templateArg);
        boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
        instantiationScope.Install(boundTemplateParameter, context);
    }
    if (wasInstantiated)
    {
        context->GetSymbolTable()->EndScope();
        specialization->GetScope()->ClearParentScopes();
        for (const auto& boundTemplateParameter : boundTemplateParameters)
        {
            context->GetSymbolTable()->UnmapType(boundTemplateParameter.get());
        }
        return std::expected<ClassTemplateSpecializationSymbol*, int>(specialization);
    }
    specialization->SetNextMemFnDefIndex(classTemplate->NextMemFnDefIndex());
    context->GetSymbolTable()->BeginScope(&instantiationScope);
    Instantiator instantiator(context, &instantiationScope);
    context->PushSetFlag(ContextFlags::dontBind | ContextFlags::skipFunctionDefinitions);
    classNode->Accept(instantiator);
    if (!instantiator)
    {
        std::expected<std::u32string, int> fname = specialization->FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        return Error("otava.symbols.templates: error instantiating specialization '" + *sfname + "': " + util::GetErrorMessage(instantiator.Error()), sourcePos, context);
    }
    std::vector<ClassTypeSymbol*> baseClasses = instantiator.GetBaseClasses();
    for (ClassTypeSymbol* baseClass : baseClasses)
    {
        std::expected<bool, int> brv = specialization->AddBaseClass(baseClass, sourcePos, context);
        if (!brv) return std::unexpected<int>(brv.error());
    }
    context->PopFlags();
    std::set<const Symbol*> visited;
    if (!specialization->IsTemplateParameterInstantiation(context, visited))
    {
        //AddClassInfo(specialization, context); // todo
        std::expected<bool, int> rv = InstantiateDestructor(specialization, sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        rv = InstantiateVirtualFunctions(specialization, sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    context->GetSymbolTable()->EndScope();
    context->GetSymbolTable()->EndScope();
    specialization->GetScope()->ClearParentScopes();
    for (const auto& boundTemplateParameter : boundTemplateParameters)
    {
        context->GetSymbolTable()->UnmapType(boundTemplateParameter.get());
    }
    if (!specialization->IsProject())
    {
        specialization->SetProject();
        context->GetSymbolTable()->AddChangedClassTemplateSpecialization(specialization);
    }
    return std::expected<ClassTemplateSpecializationSymbol*, int>(specialization);
}

MemFunKey::MemFunKey(FunctionSymbol* memFun_, const std::vector<TypeSymbol*>& templateArgumentTypes_) : memFun(memFun_), templateArgumentTypes(templateArgumentTypes_)
{
}

bool MemFunKeyLess::operator()(const MemFunKey& left, const MemFunKey& right) const
{
    if (left.memFun < right.memFun) return true;
    if (left.memFun > right.memFun) return false;
    return left.templateArgumentTypes < right.templateArgumentTypes;
}

ClassTemplateRepository::ClassTemplateRepository()
{
}

FunctionDefinitionSymbol* ClassTemplateRepository::GetFunctionDefinition(const MemFunKey& key) const
{
    auto it = memFunMap.find(key);
    if (it != memFunMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void ClassTemplateRepository::AddFunctionDefinition(const MemFunKey& key, FunctionDefinitionSymbol* functionDefinitionSymbol, otava::ast::Node* functionDefinitionNode)
{
    memFunMap[key] = functionDefinitionSymbol;
    functionDefinitionNodes.push_back(std::unique_ptr<otava::ast::Node>(functionDefinitionNode));
}

std::expected<FunctionSymbol*, int> InstantiateMemFnOfClassTemplate(FunctionSymbol* memFn, ClassTemplateSpecializationSymbol* classTemplateSpecialization,
    const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::string, int> name = util::ToUtf8(memFn->Name());
    if (!name) return std::unexpected<int>(name.error());
    std::string specializationName = std::move(*name);
    if (!classTemplateSpecialization)
    {
        ClassTypeSymbol* classTemplate = memFn->ParentClassType();
        std::vector<Symbol*> templateArguments;
        TemplateDeclarationSymbol* templateDeclaration = classTemplate->ParentTemplateDeclaration();
        for (TemplateParameterSymbol* templateParameter : templateDeclaration->TemplateParameters())
        {
            auto it = templateParameterMap.find(templateParameter);
            if (it != templateParameterMap.cend())
            {
                TypeSymbol* templateArgumentType = it->second;
                templateArguments.push_back(templateArgumentType);
            }
            else
            {
                return Error("template parameter type not found", sourcePos, context);
            }
        }
        std::expected<ClassTemplateSpecializationSymbol*, int> rv = InstantiateClassTemplate(classTemplate, templateArguments, sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        classTemplateSpecialization = *rv;
    }
    else
    {
        std::expected<ClassTemplateSpecializationSymbol*, int> rv = InstantiateClassTemplate(classTemplateSpecialization->ClassTemplate(), 
            classTemplateSpecialization->TemplateArguments(), sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        classTemplateSpecialization = *rv;
    }
    std::expected<TypeSymbol*, int> frv = classTemplateSpecialization->FinalType(sourcePos, context);
    if (!frv) return std::unexpected<int>(frv.error());
    TypeSymbol* finalType = *frv;
    classTemplateSpecialization = static_cast<ClassTemplateSpecializationSymbol*>(finalType);
    std::expected<bool, int> brv = context->GetBoundCompileUnit()->AddBoundNodeForClass(classTemplateSpecialization, sourcePos, context);
    if (!brv) return std::unexpected<int>(brv.error());
    ClassTemplateRepository* classTemplateRepository = context->GetBoundCompileUnit()->GetClassTemplateRepository();
    std::vector<TypeSymbol*> templateArgumentTypes;
    int n = classTemplateSpecialization->TemplateArguments().size();
    for (int i = 0; i < n; ++i)
    {
        Symbol* templateArg = classTemplateSpecialization->TemplateArguments()[i];
        if (templateArg->IsTypeSymbol())
        {
            TypeSymbol* templateArgumentType = static_cast<TypeSymbol*>(templateArg);
            templateArgumentTypes.push_back(templateArgumentType);
        }
    }
    MemFunKey key(memFn, templateArgumentTypes);
    FunctionDefinitionSymbol* functionDefinitionSymbol = classTemplateRepository->GetFunctionDefinition(key);
    if (functionDefinitionSymbol)
    {
        return std::expected<FunctionSymbol*, int>(functionDefinitionSymbol);
    }
    ExplicitInstantiationSymbol* explicitInstantiation = context->GetSymbolTable()->GetExplicitInstantiation(classTemplateSpecialization);
    if (explicitInstantiation)
    {
        //bool isInline = memFn->IsInline() && context->ReleaseConfig() && otava::optimizer::HasOptimization(otava::optimizer::Optimizations::inlining);
        bool isInline = false; // todo
        bool hasDefaultParams = memFn->HasDefaultParams();
        if (!isInline && !hasDefaultParams)
        {
            if (memFn->IsFunctionDefinitionSymbol())
            {
                FunctionDefinitionSymbol* memFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(memFn);
                FunctionDefinitionSymbol* functionDefinitionSymbol = explicitInstantiation->GetFunctionDefinitionSymbol(memFnDefSymbol->DefIndex());
                functionDefinitionSymbol->SetDestructor(explicitInstantiation->Destructor());
                return std::expected<FunctionSymbol*, int>(functionDefinitionSymbol);
            }
            else
            {
                std::expected<std::string, int> name = util::ToUtf8(memFn->Name());
                if (!name) return std::unexpected<int>(name.error());
                return Error(*name + ": otava.symbols.class_templates: function definition symbol expected", sourcePos, context);
            }
        }
    }
    if (memFn->IsFunctionDefinitionSymbol())
    {
        FunctionDefinitionSymbol* memFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(memFn);
        std::int32_t memFnDefIndex = memFnDefSymbol->DefIndex();
        FunctionDefinitionSymbol* memFnSpecialization = classTemplateSpecialization->GetMemFnDefSymbol(memFnDefIndex);
        if (memFnSpecialization)
        {
            return std::expected<FunctionSymbol*, int>(memFnSpecialization);
        }
    }
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    bool prevParseMemberFunction = context->GetFlag(ContextFlags::parseMemberFunction);
    context->ResetFlag(ContextFlags::parseMemberFunction);
    otava::ast::Node* node = context->GetSymbolTable()->GetNodeNothrow(memFn);
    if (node)
    {
        std::expected<otava::ast::Node*, int> c = node->Clone();
        if (!c) return std::unexpected<int>(c.error());
        node = *c;
    }
    else
    {
        if (memFn->IsDestructor())
        {
            std::expected<bool, int> rv = InstantiateDestructor(classTemplateSpecialization, sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
            return std::expected<FunctionSymbol*, int>(memFn);
        }
        else
        {
            std::expected<std::u32string, int> fname = memFn->FullName();
            if (!fname) return std::unexpected<int>(fname.error());
            std::expected<std::string, int> sfname = util::ToUtf8(*fname);
            if (!sfname) return std::unexpected<int>(sfname.error());
            return Error("node for symbol '" + *sfname + "' not found", sourcePos, context);
        }
    }
    if (node->IsFunctionDefinitionNode())
    {
        otava::ast::FunctionDefinitionNode* functionDefinitionNode = static_cast<otava::ast::FunctionDefinitionNode*>(node);
        if (functionDefinitionNode->FunctionBody()->IsDefaultedOrDeletedFunctionNode())
        {
            otava::ast::DefaultedOrDeletedFunctionNode* bodyNode = static_cast<otava::ast::DefaultedOrDeletedFunctionNode*>(functionDefinitionNode->FunctionBody());
            if (bodyNode->DefaultOrDelete()->Kind() == otava::ast::NodeKind::deleteNode)
            {
                return Error("attempt to instantiate a deleted function", sourcePos, context);
            }
        }
        ClassTypeSymbol* parentClass = memFn->ParentClassType();
        if (parentClass)
        {
            if (parentClass->IsClassTemplateSpecializationSymbol())
            {
                ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(parentClass);
                parentClass = sp->ClassTemplate();
            }
            TemplateDeclarationSymbol* templateDeclaration = parentClass->ParentTemplateDeclaration();
            if (templateDeclaration)
            {
                int arity = templateDeclaration->Arity();
                int argCount = templateArgumentTypes.size();
                if (argCount > arity)
                {
                    std::expected<std::string, int> name = util::ToUtf8(memFn->Name());
                    if (!name) return std::unexpected<int>(name.error());
                    return Error("otava.symbols.class_templates: wrong number of template args for instantiating class template member function '" +
                        *name + "'", sourcePos, node->GetSourcePos(), context);
                }
                std::expected<bool, int> prv = classTemplateSpecialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
                if (!prv) return std::unexpected<int>(prv.error());
                prv = classTemplateSpecialization->GetScope()->AddParentScope(classTemplateSpecialization->ClassTemplate()->GetScope()->GetNamespaceScope());
                if (!prv) return std::unexpected<int>(prv.error());
                InstantiationScope instantiationScope(classTemplateSpecialization->GetScope());
                std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
                for (int i = 0; i < arity; ++i)
                {
                    Symbol* templateArg = templateArgumentTypes[i];
                    TemplateParameterSymbol* templateParameter = templateDeclaration->TemplateParameters()[i];
                    BoundTemplateParameterSymbol* boundTemplateParameter = new BoundTemplateParameterSymbol(templateParameter->Name());
                    boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
                    boundTemplateParameter->SetBoundSymbol(templateArg);
                    boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
                    instantiationScope.Install(boundTemplateParameter, context);
                }
                BoundTemplateParameterSymbol* templateNameParameter = new BoundTemplateParameterSymbol(classTemplateSpecialization->ClassTemplate()->Name());
                templateNameParameter->SetBoundSymbol(classTemplateSpecialization);
                boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(templateNameParameter));
                instantiationScope.Install(templateNameParameter, context);
                context->GetSymbolTable()->BeginScope(&instantiationScope);
                Instantiator instantiator(context, &instantiationScope);
                FunctionSymbol* specialization = nullptr;
                context->PushSetFlag(ContextFlags::instantiateMemFnOfClassTemplate | ContextFlags::saveDeclarations | ContextFlags::dontBind);
                if (memFn->IsFunctionDefinitionSymbol())
                {
                    FunctionDefinitionSymbol* memFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(memFn);
                    context->SetMemFunDefSymbolIndex(memFnDefSymbol->DefIndex());
                }
                instantiator.SetFunctionNode(functionDefinitionNode);
                context->SetClassTemplateSpecialization(functionDefinitionNode, classTemplateSpecialization);
                functionDefinitionNode->Accept(instantiator);
                if (!instantiator)
                {
                    return Error("otava.symbols.class_templates: error instantiating specialization '" + specializationName +
                        "': " + util::GetErrorMessage(instantiator.Error()), node->GetSourcePos(), sourcePos, context);
                }
                context->SetMemFunDefSymbolIndex(-1);
                specialization = instantiator.GetSpecialization();
                context->RemoveSpecialization(functionDefinitionNode);
                context->RemoveClassTemplateSpecialization(functionDefinitionNode);
                if (classTemplateSpecialization->ContainsVirtualFunctionSpecialization(specialization))
                {
                    context->PopFlags();
                    context->GetSymbolTable()->EndScope();
                    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
                    if (prevParseMemberFunction)
                    {
                        context->SetFlag(ContextFlags::parseMemberFunction);
                    }
                    return std::expected<FunctionSymbol*, int>(specialization);
                }
                if (specialization && specialization->IsFunctionDefinitionSymbol())
                {
                    if (specialization->IsVirtual())
                    {
                        classTemplateSpecialization->AddInstantiatedVirtualFunctionSpecialization(specialization);
                    }
                    std::expected<std::string, int> name = util::ToUtf8(specialization->Name());
                    if (!name) return std::unexpected<int>(name.error());
                    specializationName = *name;
                    FunctionDefinitionSymbol* functionDefinition = static_cast<FunctionDefinitionSymbol*>(specialization);
                    functionDefinition->SetFlag(FunctionSymbolFlags::fixedIrName);
                    functionDefinition->SetCompileUnitId(context->GetBoundCompileUnit()->Id());
                    std::expected<std::string, int> irv = functionDefinition->IrName(context);
                    if (!irv) return std::unexpected<int>(irv.error());
                    std::string irName = *irv;
                    classTemplateRepository->AddFunctionDefinition(key, functionDefinition, node);
                    context->PushBoundFunction(new BoundFunctionNode(functionDefinition, sourcePos));
                    Scope* nsScope = classTemplateSpecialization->ClassTemplate()->GetScope()->GetNamespaceScope();
                    std::expected<bool, int> prv = instantiationScope.PushParentScope(nsScope);
                    if (!prv) return std::unexpected<int>(prv.error());
                    std::expected<FunctionDefinitionSymbol*, int> rv = BindFunction(functionDefinitionNode, functionDefinition, context);
                    if (!rv)
                    {
                        return Error("otava.symbols.class_templates: error instantiating specialization '" + specializationName +
                            "': " + util::GetErrorMessage(rv.error()), node->GetSourcePos(), sourcePos, context);
                    }
                    functionDefinition = *rv;
                    specialization = functionDefinition;
                    context->PopFlags();
                    if (specialization->IsBound())
                    {
                        std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
                        if (!rv) return std::unexpected<int>(rv.error());
                    }
                    context->PopBoundFunction();
                    prv = instantiationScope.PopParentScope();
                    if (!prv) return std::unexpected<int>(prv.error());
                    functionDefinition->GetScope()->ClearParentScopes();
                    context->GetSymbolTable()->MapClassTemplateSpecialization(classTemplateSpecialization);
                }
                else
                {
                    return Error("otava.symbols.class_templates: function definition symbol expected", node->GetSourcePos(), context);
                }
                context->GetSymbolTable()->EndScope();
                context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
                if (prevParseMemberFunction)
                {
                    context->SetFlag(ContextFlags::parseMemberFunction);
                }
                if (specialization->GroupName() != U"@destructor")
                {
                    std::expected<bool, int> rv = InstantiateDestructor(classTemplateSpecialization, sourcePos, context);
                    if (!rv) return std::unexpected<int>(rv.error());
                }
                for (const auto& boundTemplateParameter : boundTemplateParameters)
                {
                    context->GetSymbolTable()->UnmapType(boundTemplateParameter.get());
                }
                return std::expected<FunctionSymbol*, int>(specialization);
            }
            else
            {
                return Error("otava.symbols.class_templates: parent class template declaration not found", node->GetSourcePos(), sourcePos, context);
            }
        }
        else
        {
            return Error("otava.symbols.class_templates: parent class template not found", node->GetSourcePos(), sourcePos, context);
        }
    }
    else
    {
        ClassTypeSymbol* parentClass = memFn->ParentClassType();
        if (parentClass)
        {
            if (parentClass->IsClassTemplateSpecializationSymbol())
            {
                ClassTemplateSpecializationSymbol* sp = static_cast<ClassTemplateSpecializationSymbol*>(parentClass);
                parentClass = sp->ClassTemplate();
            }
            TemplateDeclarationSymbol* templateDeclaration = parentClass->ParentTemplateDeclaration();
            if (templateDeclaration)
            {
                int arity = templateDeclaration->Arity();
                int argCount = templateArgumentTypes.size();
                if (argCount > arity)
                {
                    std::expected<std::string, int> name = util::ToUtf8(memFn->Name());
                    if (!name) return std::unexpected<int>(name.error());
                    return Error("otava.symbols.class_templates: wrong number of template args for instantiating class template member function '" +
                        *name + "'", sourcePos, node->GetSourcePos(), context);
                }
                std::expected<bool, int> prv = classTemplateSpecialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
                if (!prv) return std::unexpected<int>(prv.error());
                prv = classTemplateSpecialization->GetScope()->AddParentScope(classTemplateSpecialization->ClassTemplate()->GetScope()->GetNamespaceScope());
                if (!prv) return std::unexpected<int>(prv.error());
                InstantiationScope instantiationScope(classTemplateSpecialization->GetScope());
                std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
                for (int i = 0; i < arity; ++i)
                {
                    Symbol* templateArg = templateArgumentTypes[i];
                    TemplateParameterSymbol* templateParameter = templateDeclaration->TemplateParameters()[i];
                    BoundTemplateParameterSymbol* boundTemplateParameter = new BoundTemplateParameterSymbol(templateParameter->Name());
                    boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
                    boundTemplateParameter->SetBoundSymbol(templateArg);
                    boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
                    instantiationScope.Install(boundTemplateParameter, context);
                }
                BoundTemplateParameterSymbol* templateNameParameter = new BoundTemplateParameterSymbol(classTemplateSpecialization->ClassTemplate()->Name());
                templateNameParameter->SetBoundSymbol(classTemplateSpecialization);
                boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(templateNameParameter));
                instantiationScope.Install(templateNameParameter, context);
                context->GetSymbolTable()->BeginScope(&instantiationScope);
                Instantiator instantiator(context, &instantiationScope);
                FunctionSymbol* specialization = nullptr;
                context->PushSetFlag(ContextFlags::instantiateMemFnOfClassTemplate | ContextFlags::saveDeclarations | ContextFlags::dontBind);
                if (memFn->IsFunctionDefinitionSymbol())
                {
                    FunctionDefinitionSymbol* memFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(memFn);
                    context->SetMemFunDefSymbolIndex(memFnDefSymbol->DefIndex());
                }
                instantiator.SetFunctionNode(node);
                context->SetClassTemplateSpecialization(node, classTemplateSpecialization);
                node->Accept(instantiator);
                if (!instantiator)
                {
                    return Error("otava.symbols.class_templates: error instantiating specialization '" + specializationName +
                        "': " + util::GetErrorMessage(instantiator.Error()), node->GetSourcePos(), sourcePos, context);
                }
                context->PopFlags();
                context->SetMemFunDefSymbolIndex(-1);
                specialization = instantiator.GetSpecialization();
                context->RemoveSpecialization(node);
                context->RemoveClassTemplateSpecialization(node);
                if (specialization)
                {
                    std::expected<std::u32string, int> fname = specialization->FullName();
                    if (!fname)  return std::unexpected<int>(fname.error());
                    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                    if (!sfname) return std::unexpected<int>(sfname.error());
                    specializationName = *sfname;
                    if (classTemplateSpecialization->ContainsVirtualFunctionSpecialization(specialization))
                    {
                        context->PopFlags();
                        context->GetSymbolTable()->EndScope();
                        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
                        if (prevParseMemberFunction)
                        {
                            context->SetFlag(ContextFlags::parseMemberFunction);
                        }
                        return std::expected<FunctionSymbol*, int>(specialization);
                    }
                    if (specialization->IsVirtual())
                    {
                        classTemplateSpecialization->AddInstantiatedVirtualFunctionSpecialization(specialization);
                    }
                }
                else
                {
                    return Error("otava.symbols.class_templates: function symbol expected", node->GetSourcePos(), context);
                }
                prv = instantiationScope.PopParentScope();
                if (!prv) return std::unexpected<int>(prv.error());
                context->GetSymbolTable()->EndScope();
                context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
                if (prevParseMemberFunction)
                {
                    context->SetFlag(ContextFlags::parseMemberFunction);
                }
                for (const auto& boundTemplateParameter : boundTemplateParameters)
                {
                    context->GetSymbolTable()->UnmapType(boundTemplateParameter.get());
                }
                return std::expected<FunctionSymbol*, int>(specialization);
            }
            else
            {
                return Error("otava.symbols.class_templates: parent class template declaration not found", node->GetSourcePos(), sourcePos, context);
            }
        }
        else
        {
            return Error("otava.symbols.class_templates: parent class template not found", node->GetSourcePos(), sourcePos, context);
        }
    }
}

} // namespace otava::symbols
