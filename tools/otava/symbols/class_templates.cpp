// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.class_templates;

import otava.symbols.bound.tree;
import otava.symbols.modules;
import otava.symbols.context;
import otava.symbols.function.symbol;
import otava.symbols.symbol.table;
import otava.symbols.exception;
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
import otava.opt;
import otava.ast;
import util.unicode;
import util.sha1;

namespace otava::symbols {

ClassTemplateSpecializationSymbol::ClassTemplateSpecializationSymbol(const std::u32string& name_) : 
    ClassTypeSymbol(SymbolKind::classTemplateSpecializationSymbol, name_), classTemplate(nullptr), instantiated(false), destructor(nullptr), instantiatingDestructor(false)
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

std::string ClassTemplateSpecializationSymbol::IrName(Context* context) const
{
    std::string fullIrName = classTemplate->IrName(context);
    std::string templateArgIrNames;
    for (const auto& templateArg : templateArguments)
    {
        templateArgIrNames.append(1, '_').append(templateArg->IrName(context));
    }
    fullIrName.append(1, '_').append(util::GetSha1MessageDigest(templateArgIrNames));
    return fullIrName;
}

void ClassTemplateSpecializationSymbol::Write(Writer& writer)
{
    ClassTypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(instantiated);
    writer.GetBinaryStreamWriter().Write(classTemplate->Id());
    writer.GetBinaryStreamWriter().WriteULEB128UInt(templateArguments.size());
    for (Symbol* templateArg : templateArguments)
    {
        if (templateArg->IsTypeSymbol())
        {
            writer.GetBinaryStreamWriter().Write(true);
            writer.GetBinaryStreamWriter().Write(templateArg->Id());
        }
        else
        {
            writer.GetBinaryStreamWriter().Write(false);
            writer.GetBinaryStreamWriter().Write(templateArg->Id());
        }
    }
    if (destructor)
    {
        writer.GetBinaryStreamWriter().Write(destructor->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
    writer.GetBinaryStreamWriter().WriteULEB128UInt(instantiatedVirtualFunctionSpecializations.size());
    for (auto nf : instantiatedVirtualFunctionSpecializations)
    {
        writer.GetBinaryStreamWriter().Write(nf->Id());
    }
}

void ClassTemplateSpecializationSymbol::Read(Reader& reader)
{
    ClassTypeSymbol::Read(reader);
    reader.GetSymbolTable()->AddClassTemplateSpecializationToSet(this);
    instantiated = reader.GetBinaryStreamReader().ReadBool();
    util::uuid id;
    reader.GetBinaryStreamReader().ReadUuid(id);
    ids.push_back(std::make_pair(id, true));
    std::uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < count; ++i)
    {
        util::uuid id;
        bool isType = reader.GetBinaryStreamReader().ReadBool();
        reader.GetBinaryStreamReader().ReadUuid(id);
        ids.push_back(std::make_pair(id, isType));
    }
    reader.GetBinaryStreamReader().ReadUuid(destructorId);
    std::uint32_t nfids = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < nfids; ++i)
    {
        util::uuid vfid;
        reader.GetBinaryStreamReader().ReadUuid(vfid);
        instantiatedVirtualFunctionSpecializationIds.push_back(vfid);
    }
}

void ClassTemplateSpecializationSymbol::Resolve(SymbolTable& symbolTable)
{
    ClassTypeSymbol::Resolve(symbolTable);
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
        symbolTable.AddClassTemplateSpecializationToSet(this);
    }
    else
    {
        std::cout << "ClassTemplateSpecializationSymbol::Resolve(): warning: class template not resolved" << "\n";
    }
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
        for (const auto& templateArg : templateArguments)
        {
            if (templateArg->IsTemplateParameterInstantiation(context, visited)) return true;
        }
    }
    return false;
}

TypeSymbol* ClassTemplateSpecializationSymbol::FinalType(const soul::ast::SourcePos& sourcePos, Context* context) 
{
    std::vector<Symbol*> templateArgs;
    for (const auto& templateArg : templateArguments)
    {
        if (templateArg->IsTypeSymbol())
        {
            TypeSymbol* typeTemplateArg = static_cast<TypeSymbol*>(templateArg);
            typeTemplateArg = typeTemplateArg->DirectType(context)->FinalType(sourcePos, context);
            templateArgs.push_back(typeTemplateArg);
        }
        else
        {
            templateArgs.push_back(templateArg);
        }
    }
    ClassTemplateSpecializationSymbol* specialization = InstantiateClassTemplate(classTemplate, templateArgs, sourcePos, context);
    return specialization;
}

bool ClassTemplateSpecializationSymbol::IsComplete(std::set<const TypeSymbol*>& visited) const
{
    if (visited.find(this) != visited.end()) return true;
    visited.insert(this);
    for (const auto& templateArg : templateArguments)
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
    for (auto prev : instantiatedVirtualFunctionSpecializations)
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
    for (const auto& instance : instantiatedVirtualFunctionSpecializations)
    {
        if (instance == specialization) return true;
    }
    return false;
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

void InstantiateDestructor(ClassTemplateSpecializationSymbol* specialization, const soul::ast::SourcePos& sourcePos, Context* context)
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
    Symbol* destructor = classTemplate->GetScope()->Lookup(U"@destructor", SymbolGroupKind::functionSymbolGroup, ScopeLookup::thisScope, sourcePos, context, 
        LookupFlags::dontResolveSingle);
    if (destructor && destructor->IsFunctionGroupSymbol())
    {
        FunctionGroupSymbol* destructorGroup = static_cast<FunctionGroupSymbol*>(destructor);
        FunctionDefinitionSymbol* destructorFn = destructorGroup->GetSingleDefinition();
        if (destructorFn)
        {
            std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
            FunctionSymbol* instantiatedDestructor = InstantiateMemFnOfClassTemplate(destructorFn, specialization, templateParameterMap, sourcePos, context);
            instantiatedDestructor->SetFlag(FunctionSymbolFlags::fixedIrName);
            std::string irName = instantiatedDestructor->IrName(context);
            specialization->SetDestructor(instantiatedDestructor);
        }
    }
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    context->PopFlags();
    specialization->SetInstantiatingDestructor(false);
}

class VirtualFunctionNodeClassifierVisitor : public otava::ast::DefaultVisitor
{
public:
    VirtualFunctionNodeClassifierVisitor();
    void Visit(otava::ast::VirtualNode& node);
    void Visit(otava::ast::OverrideNode& node);
    void Visit(otava::ast::FinalNode& node);
    bool Value() const { return value; }
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
    return visitor.Value();
}

void InstantiateVirtualFunctions(ClassTemplateSpecializationSymbol* specialization, const soul::ast::SourcePos& sourcePos, Context* context)
{
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    std::set<const Symbol*> visited;
    std::vector<FunctionSymbol*> virtualFunctions;
    if (!specialization->IsTemplateParameterInstantiation(context, visited))
    {
        ClassTypeSymbol* classTemplate = specialization->ClassTemplate();
        for (const auto& memFn : classTemplate->MemberFunctions())
        {
            otava::ast::Node* node = context->GetSymbolTable()->GetNode(memFn);
            if (node && IsVirtualFunctionNode(node))
            {
                virtualFunctions.push_back(memFn);
            }
        }
    }
    for (const auto& virtualMemFn : virtualFunctions)
    {
        std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
        FunctionSymbol* instance = InstantiateMemFnOfClassTemplate(virtualMemFn, specialization, templateParameterMap, sourcePos, context);
        specialization->AddInstantiatedVirtualFunctionSpecialization(instance);
    }
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
}

ClassTemplateSpecializationSymbol* InstantiateClassTemplate(ClassTypeSymbol* classTemplate, const std::vector<Symbol*>& templateArgs, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    if (classTemplate->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(classTemplate);
        classTemplate = specialization->ClassTemplate();
    }
    TemplateDeclarationSymbol* templateDeclaration = classTemplate->ParentTemplateDeclaration();
    if (!templateDeclaration)
    {
        ThrowException("otava.symbols.class_templates: template declaration not found from class template '" + util::ToUtf8(classTemplate->Name()) + "'", 
            sourcePos, context);
    }
    int arity = templateDeclaration->Arity();
    ClassTemplateSpecializationSymbol* specialization = context->GetSymbolTable()->MakeClassTemplateSpecialization(classTemplate, templateArgs);
    int m = templateArgs.size();
    if (specialization->Instantiated() && arity == m)
    {
        return specialization;
    }
    ExplicitInstantiationSymbol* explicitInstantiation = context->GetSymbolTable()->GetExplicitInstantiation(specialization);
    if (explicitInstantiation)
    {
        return explicitInstantiation->Specialization();
    }
    otava::ast::Node* classNode = context->GetSymbolTable()->GetSpecifierNode(classTemplate);
    if (!classNode)
    {
        return specialization;
    }
    if (classNode->IsClassSpecifierNode())
    {
        otava::ast::ClassSpecifierNode* classSpecifierNode = static_cast<otava::ast::ClassSpecifierNode*>(classNode);
        if (!classSpecifierNode->Complete())
        {
            return specialization;
        }
    }
    specialization->SetInstantiated();
    context->GetBoundCompileUnit()->AddBoundNodeForClass(specialization, sourcePos, context);
    int argCount = templateArgs.size();
    if (argCount > arity)
    {
        ThrowException("otava.symbols.class_templates: wrong number of template args for instantiating class template '" +
            util::ToUtf8(classTemplate->Name()) + "'",
            sourcePos, context);
    }
    specialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope());
    specialization->GetScope()->AddParentScope(specialization->ClassTemplate()->GetScope()->GetNamespaceScope());
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
                templateArg = ResolveType(defaultTemplateArgNode, DeclarationFlags::none, context);
                context->GetSymbolTable()->EndScope();
                specialization->AddTemplateArgument(templateArg);
            }
            else
            {
                ThrowException("otava.symbols.templates: template parameter " + std::to_string(i) + " has no default type argument", sourcePos, context);
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
                        ThrowException("otava.symbols.templates: specialization argument type not resolved", sourcePos, context);
                    }
                }
            }
        }
        BoundTemplateParameterSymbol* boundTemplateParameter(new BoundTemplateParameterSymbol(templateParameter->Name()));
        boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
        boundTemplateParameter->SetBoundSymbol(templateArg);
        boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
        instantiationScope.Install(boundTemplateParameter);
    }
    context->GetSymbolTable()->BeginScope(&instantiationScope);
    Instantiator instantiator(context, &instantiationScope);
    try
    {
        context->PushSetFlag(ContextFlags::dontBind | ContextFlags::skipFunctionDefinitions);
        classNode->Accept(instantiator);
        std::vector<ClassTypeSymbol*> baseClasses = instantiator.GetBaseClasses();
        for (ClassTypeSymbol* baseClass : baseClasses)
        {
            specialization->AddBaseClass(baseClass, sourcePos, context);
        }
        context->PopFlags();
        std::set<const Symbol*> visited;
        if (!specialization->IsTemplateParameterInstantiation(context, visited))
        {
            AddClassInfo(specialization, context);
            InstantiateDestructor(specialization, sourcePos, context);
            InstantiateVirtualFunctions(specialization, sourcePos, context);
        }
    }
    catch (const std::exception& ex)
    {
        ThrowException("otava.symbols.templates: error instantiating specialization '" +
            util::ToUtf8(specialization->FullName()) + "': " + std::string(ex.what()), sourcePos, context);
    }
    context->GetSymbolTable()->EndScope();
    context->GetSymbolTable()->EndScope();
    specialization->GetScope()->ClearParentScopes();
    for (const auto& boundTemplateParameter : boundTemplateParameters)
    {
        context->GetSymbolTable()->UnmapType(boundTemplateParameter.get());
    }
    return specialization;
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

FunctionSymbol* InstantiateMemFnOfClassTemplate(FunctionSymbol* memFn, ClassTemplateSpecializationSymbol* classTemplateSpecialization, 
    const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::string specializationName = util::ToUtf8(memFn->Name());
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
                ThrowException("template parameter type not found", sourcePos, context);
            }
        }
        classTemplateSpecialization = InstantiateClassTemplate(classTemplate, templateArguments, sourcePos, context);
    }
    else
    {
        classTemplateSpecialization = InstantiateClassTemplate(classTemplateSpecialization->ClassTemplate(), classTemplateSpecialization->TemplateArguments(), sourcePos, context);
    }
    classTemplateSpecialization = static_cast<ClassTemplateSpecializationSymbol*>(classTemplateSpecialization->FinalType(sourcePos, context));
    context->GetBoundCompileUnit()->AddBoundNodeForClass(classTemplateSpecialization, sourcePos, context);
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
        return functionDefinitionSymbol;
    }
    ExplicitInstantiationSymbol* explicitInstantiation = context->GetSymbolTable()->GetExplicitInstantiation(classTemplateSpecialization);
    if (explicitInstantiation)
    {
        bool isInline = memFn->IsInline() && context->ReleaseConfig() && otava::optimizer::HasOptimization(otava::optimizer::Optimizations::inlining);
        bool hasDefaultParams = memFn->HasDefaultParams();
        if (!isInline && !hasDefaultParams)
        {
            if (memFn->IsFunctionDefinitionSymbol())
            {
                FunctionDefinitionSymbol* memFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(memFn);
                FunctionDefinitionSymbol* functionDefinitionSymbol = explicitInstantiation->GetFunctionDefinitionSymbol(memFnDefSymbol->DefIndex());
                functionDefinitionSymbol->SetDestructor(explicitInstantiation->Destructor());
                return functionDefinitionSymbol;
            }
            else
            {
                ThrowException(util::ToUtf8(memFn->Name()) + ": otava.symbols.class_templates: function definition symbol expected", sourcePos, context);
            }
        }
    }
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    bool prevParseMemberFunction = context->GetFlag(ContextFlags::parseMemberFunction);
    context->ResetFlag(ContextFlags::parseMemberFunction);
    otava::ast::Node* node = context->GetSymbolTable()->GetNodeNothrow(memFn);
    if (node)
    {
        node = node->Clone();
    }
    else
    {
        if (memFn->IsDestructor())
        {
            InstantiateDestructor(classTemplateSpecialization, sourcePos, context);
            return memFn;
        }
        else
        {
            ThrowException("node for symbol '" + util::ToUtf8(memFn->FullName()) + "¨' not found", sourcePos, context);
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
                ThrowException("attempt to instantiate a deleted function", sourcePos, context);
            }
        }
        ClassTypeSymbol* parentClass = memFn->ParentClassType();
        if (parentClass)
        {
            if (parentClass->IsClassTemplateSpecializationSymbol())
            {
                parentClass = static_cast<ClassTemplateSpecializationSymbol*>(parentClass)->ClassTemplate();
            }
            TemplateDeclarationSymbol* templateDeclaration = parentClass->ParentTemplateDeclaration();
            if (templateDeclaration)
            {
                int arity = templateDeclaration->Arity();
                int argCount = templateArgumentTypes.size();
                if (argCount > arity)
                {
                    ThrowException("otava.symbols.class_templates: wrong number of template args for instantiating class template member function '" +
                        util::ToUtf8(memFn->Name()) + "'", sourcePos, node->GetSourcePos(), context);
                }
                classTemplateSpecialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
                classTemplateSpecialization->GetScope()->AddParentScope(classTemplateSpecialization->ClassTemplate()->GetScope()->GetNamespaceScope());
                InstantiationScope instantiationScope(classTemplateSpecialization->GetScope());
                std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
                for (int i = 0; i < arity; ++i)
                {
                    Symbol* templateArg = templateArgumentTypes[i];
                    TemplateParameterSymbol* templateParameter = templateDeclaration->TemplateParameters()[i];
                    BoundTemplateParameterSymbol* boundTemplateParameter(new BoundTemplateParameterSymbol(templateParameter->Name()));
                    boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
                    boundTemplateParameter->SetBoundSymbol(templateArg);
                    boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
                    instantiationScope.Install(boundTemplateParameter);
                }
                BoundTemplateParameterSymbol* templateNameParameter(new BoundTemplateParameterSymbol(classTemplateSpecialization->ClassTemplate()->Name()));
                templateNameParameter->SetBoundSymbol(classTemplateSpecialization);
                boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(templateNameParameter));
                instantiationScope.Install(templateNameParameter);
                context->GetSymbolTable()->BeginScope(&instantiationScope);
                Instantiator instantiator(context, &instantiationScope);
                FunctionSymbol* specialization = nullptr;
                try
                {
                    context->PushSetFlag(ContextFlags::instantiateMemFnOfClassTemplate | ContextFlags::saveDeclarations | ContextFlags::dontBind);
                    if (memFn->IsFunctionDefinitionSymbol())
                    {
                        FunctionDefinitionSymbol* memFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(memFn);
                        context->SetMemFunDefSymbolIndex(memFnDefSymbol->DefIndex());
                    }
                    instantiator.SetFunctionNode(functionDefinitionNode);
                    context->SetClassTemplateSpecialization(functionDefinitionNode, classTemplateSpecialization);
                    functionDefinitionNode->Accept(instantiator);
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
                        return specialization;
                    }
                    if (specialization && specialization->IsFunctionDefinitionSymbol())
                    {
                        if (specialization->IsVirtual())
                        {
                            classTemplateSpecialization->AddInstantiatedVirtualFunctionSpecialization(specialization);
                        }
                        specializationName = util::ToUtf8(specialization->Name());
                        FunctionDefinitionSymbol* functionDefinition = static_cast<FunctionDefinitionSymbol*>(specialization);
                        functionDefinition->SetFlag(FunctionSymbolFlags::fixedIrName);
                        functionDefinition->SetCompileUnitId(context->GetBoundCompileUnit()->Id());
                        std::string irName = functionDefinition->IrName(context);
                        classTemplateRepository->AddFunctionDefinition(key, functionDefinition, node);
                        context->PushBoundFunction(new BoundFunctionNode(functionDefinition, sourcePos));
                        Scope* nsScope = classTemplateSpecialization->ClassTemplate()->GetScope()->GetNamespaceScope();
                        instantiationScope.PushParentScope(nsScope);
                        functionDefinition = BindFunction(functionDefinitionNode, functionDefinition, context);
                        specialization = functionDefinition;
                        context->PopFlags();
                        if (specialization->IsBound())
                        {
                            context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
                        }
                        context->PopBoundFunction();
                        instantiationScope.PopParentScope();
                        functionDefinition->GetScope()->ClearParentScopes();
                    }
                    else
                    {
                        ThrowException("otava.symbols.class_templates: function definition symbol expected", node->GetSourcePos(), context);
                    }
                }
                catch (const std::exception& ex)
                {
                    ThrowException("otava.symbols.class_templates: error instantiating specialization '" + specializationName + 
                        "': " + std::string(ex.what()), node->GetSourcePos(), sourcePos, context);
                }
                context->GetSymbolTable()->EndScope();
                context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
                if (prevParseMemberFunction)
                {
                    context->SetFlag(ContextFlags::parseMemberFunction);
                }
                if (specialization->GroupName() != U"@destructor")
                {
                    InstantiateDestructor(classTemplateSpecialization, sourcePos, context);
                }
                for (const auto& boundTemplateParameter : boundTemplateParameters)
                {
                    context->GetSymbolTable()->UnmapType(boundTemplateParameter.get());
                }
                return specialization;
            }
            else
            {
                ThrowException("otava.symbols.class_templates: parent class template declaration not found", node->GetSourcePos(), sourcePos, context);
            }
        }
        else
        {
            ThrowException("otava.symbols.class_templates: parent class template not found", node->GetSourcePos(), sourcePos, context);
        }
    }
    else
    {
        ClassTypeSymbol* parentClass = memFn->ParentClassType();
        if (parentClass)
        {
            TemplateDeclarationSymbol* templateDeclaration = parentClass->ParentTemplateDeclaration();
            if (templateDeclaration)
            {
                int arity = templateDeclaration->Arity();
                int argCount = templateArgumentTypes.size();
                if (argCount > arity)
                {
                    ThrowException("otava.symbols.class_templates: wrong number of template args for instantiating class template member function '" +
                        util::ToUtf8(memFn->Name()) + "'", sourcePos, node->GetSourcePos(), context);
                }
                classTemplateSpecialization->GetScope()->AddParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
                classTemplateSpecialization->GetScope()->AddParentScope(classTemplateSpecialization->ClassTemplate()->GetScope()->GetNamespaceScope());
                InstantiationScope instantiationScope(classTemplateSpecialization->GetScope());
                std::vector<std::unique_ptr<BoundTemplateParameterSymbol>> boundTemplateParameters;
                for (int i = 0; i < arity; ++i)
                {
                    Symbol* templateArg = templateArgumentTypes[i];
                    TemplateParameterSymbol* templateParameter = templateDeclaration->TemplateParameters()[i];
                    BoundTemplateParameterSymbol* boundTemplateParameter(new BoundTemplateParameterSymbol(templateParameter->Name()));
                    boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
                    boundTemplateParameter->SetBoundSymbol(templateArg);
                    boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
                    instantiationScope.Install(boundTemplateParameter);
                }
                BoundTemplateParameterSymbol* templateNameParameter(new BoundTemplateParameterSymbol(classTemplateSpecialization->ClassTemplate()->Name()));
                templateNameParameter->SetBoundSymbol(classTemplateSpecialization);
                boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(templateNameParameter));
                instantiationScope.Install(templateNameParameter);
                context->GetSymbolTable()->BeginScope(&instantiationScope);
                Instantiator instantiator(context, &instantiationScope);
                FunctionSymbol* specialization = nullptr;
                try
                {
                    context->PushSetFlag(ContextFlags::instantiateMemFnOfClassTemplate | ContextFlags::saveDeclarations | ContextFlags::dontBind);
                    if (memFn->IsFunctionDefinitionSymbol())
                    {
                        FunctionDefinitionSymbol* memFnDefSymbol = static_cast<FunctionDefinitionSymbol*>(memFn);
                        context->SetMemFunDefSymbolIndex(memFnDefSymbol->DefIndex());
                    }
                    instantiator.SetFunctionNode(node);
                    context->SetClassTemplateSpecialization(node, classTemplateSpecialization);
                    node->Accept(instantiator);
                    context->PopFlags();
                    context->SetMemFunDefSymbolIndex(-1);
                    specialization = instantiator.GetSpecialization();
                    context->RemoveSpecialization(node);
                    context->RemoveClassTemplateSpecialization(node);
                    if (specialization)
                    {
                        specializationName = util::ToUtf8(specialization->FullName());
                        if (classTemplateSpecialization->ContainsVirtualFunctionSpecialization(specialization))
                        {
                            context->PopFlags();
                            context->GetSymbolTable()->EndScope();
                            context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
                            if (prevParseMemberFunction)
                            {
                                context->SetFlag(ContextFlags::parseMemberFunction);
                            }
                            return specialization;
                        }
                        if (specialization->IsVirtual())
                        {
                            classTemplateSpecialization->AddInstantiatedVirtualFunctionSpecialization(specialization);
                        }
                    }
                    else
                    {
                        ThrowException("otava.symbols.function_templates: function symbol expected", node->GetSourcePos(), context);
                    }
                    instantiationScope.PopParentScope();
                }
                catch (const std::exception& ex)
                {
                    ThrowException("otava.symbols.class_templates: error instantiating specialization '" + specializationName +
                        "': " + std::string(ex.what()), node->GetSourcePos(), sourcePos, context);
                }
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
                return specialization;
            }
            else
            {
                ThrowException("otava.symbols.class_templates: parent class template declaration not found", node->GetSourcePos(), sourcePos, context);
            }
        }
        else
        {
            ThrowException("otava.symbols.class_templates: parent class template not found", node->GetSourcePos(), sourcePos, context);
        }
    }
}

} // namespace otava::symbols

