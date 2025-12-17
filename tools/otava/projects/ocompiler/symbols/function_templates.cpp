// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.function.templates;

import otava.symbols.context;
import otava.symbols.bound.tree;
import otava.symbols.function.kind;
import otava.symbols.function.group.symbol;
import otava.symbols.error;
import otava.symbols.symbol.table;
import otava.symbols.declaration;
import otava.symbols.type.resolver;
import otava.symbols.instantiator;
import otava.symbols.statement.binder;
import otava.symbols.modules;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
import otava.symbols.inline_functions;
import otava.ast.function;
import util.unicode;

namespace otava::symbols {

FunctionTemplateKey::FunctionTemplateKey(FunctionSymbol* functionTemplate_, const std::vector<TypeSymbol*>& templateArgumentTypes_) :
    functionTemplate(functionTemplate_), templateArgumentTypes(templateArgumentTypes_)
{
}

FunctionTemplateKey::FunctionTemplateKey() : functionTemplate(nullptr), templateArgumentTypes()
{
}

bool FunctionTemplateKeyLess::operator()(const FunctionTemplateKey& left, const FunctionTemplateKey& right) const
{
    if (left.functionTemplate < right.functionTemplate) return true;
    if (left.functionTemplate > right.functionTemplate) return false;
    return left.templateArgumentTypes < right.templateArgumentTypes;
}

FunctionTemplateRepository::FunctionTemplateRepository()
{
}

FunctionDefinitionSymbol* FunctionTemplateRepository::GetFunctionDefinition(const FunctionTemplateKey& key) const
{
    auto it = functionTemplateMap.find(key);
    if (it != functionTemplateMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void FunctionTemplateRepository::AddFunctionDefinition(const FunctionTemplateKey& key, FunctionDefinitionSymbol* functionDefinitionSymbol, 
    otava::ast::Node* functionDefinitionNode)
{
    functionTemplateMap[key] = functionDefinitionSymbol;
    functionDefinitionNodes.push_back(std::unique_ptr<otava::ast::Node>(functionDefinitionNode));
}

std::expected<FunctionSymbol*, int> InstantiateFunctionTemplate(FunctionSymbol* functionTemplate, 
    const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, const soul::ast::SourcePos& sourcePos, Context* context)
{
    auto fname = functionTemplate->FullName();
    auto sfname = util::ToUtf8(*fname);
    //std::cout << ">instantiate " << *sfname << "\n";
    FunctionTemplateRepository* functionTemplateRepository = context->GetBoundCompileUnit()->GetFunctionTemplateRepository();
    std::vector<TypeSymbol*> templateArgumentTypes;
    TemplateDeclarationSymbol* templateDeclaration = functionTemplate->ParentTemplateDeclaration();
    for (TemplateParameterSymbol* templateParameter : templateDeclaration->TemplateParameters())
    {
        auto it = templateParameterMap.find(templateParameter);
        if (it != templateParameterMap.cend())
        {
            TypeSymbol* templateArgumentType = it->second;
            templateArgumentTypes.push_back(templateArgumentType);
        }
        else
        {
            return Error("template parameter type not found", sourcePos, context);
        }
    }
    FunctionTemplateKey key(functionTemplate, templateArgumentTypes);
    FunctionDefinitionSymbol* functionDefinitionSymbol = functionTemplateRepository->GetFunctionDefinition(key);
    if (functionDefinitionSymbol)
    {
        return functionDefinitionSymbol;
    }
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    std::expected<otava::ast::Node*, int> n = context->GetSymbolTable()->GetNode(functionTemplate);
    if (!n) return std::unexpected<int>(n.error());
    otava::ast::Node* node = *n;
    n = node->Clone();
    if (!n) return std::unexpected<int>(n.error());
    node = *n;
    if (node->IsFunctionDefinitionNode())
    {
        otava::ast::FunctionDefinitionNode* functionDefinitionNode = static_cast<otava::ast::FunctionDefinitionNode*>(node);
        int arity = templateDeclaration->Arity();
        int argCount = templateArgumentTypes.size();
        if (argCount > arity)
        {
            std::expected<std::string, int> name = util::ToUtf8(functionTemplate->Name());
            if (!name) return std::unexpected<int>(name.error());
            return Error("otava.symbols.function_templates: wrong number of template args for instantiating function template '" + *name + "'", 
                node->GetSourcePos(), context);
        }
        InstantiationScope instantiationScope(functionTemplate->Parent()->GetScope());
        std::expected<Scope*, int> nrv = context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context);
        if (!nrv) return std::unexpected<int>(nrv.error());
        std::expected<bool, int> prv = instantiationScope.PushParentScope(*nrv);
        if (!prv) return std::unexpected<int>(prv.error());
        prv = instantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
        if (!prv) return std::unexpected<int>(prv.error());
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
                    std::expected<TypeSymbol*, int> trv = ResolveType(defaultTemplateArgNode, DeclarationFlags::none, context);
                    if (!trv) return std::unexpected<int>(trv.error());
                    templateArg = *trv;
                    std::expected<bool, int> erv = context->GetSymbolTable()->EndScope();
                    if (!erv) return std::unexpected<int>(erv.error());
                }
                else
                {
                    return Error("otava.symbols.function_templates: template parameter " + std::to_string(i) + " has no default type argument", 
                        node->GetSourcePos(), context);
                }
            }
            else
            {
                templateArg = templateArgumentTypes[i];
            }
            BoundTemplateParameterSymbol* boundTemplateParameter = new BoundTemplateParameterSymbol(templateParameter->Name());
            boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
            boundTemplateParameter->SetBoundSymbol(templateArg);
            boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
            instantiationScope.Install(boundTemplateParameter, context);
        }
        context->GetSymbolTable()->BeginScope(&instantiationScope);
        Instantiator instantiator(context, &instantiationScope);
        FunctionSymbol* specialization = nullptr;
        context->PushSetFlag(ContextFlags::instantiateFunctionTemplate | ContextFlags::saveDeclarations | ContextFlags::dontBind);
        instantiator.SetFunctionNode(functionDefinitionNode);
        functionDefinitionNode->Accept(instantiator);
        if (!instantiator)
        {
            std::string specializationFullName;
            if (specialization)
            {
                std::expected<std::u32string, int> fname = specialization->FullName();
                if (!fname) return std::unexpected<int>(fname.error());
                std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                if (!sfname) return std::unexpected<int>(sfname.error());
                specializationFullName = *sfname;
            }
            return Error("otava.symbols.function_templates: error instantiating specialization '" + specializationFullName +
                "': " + util::GetErrorMessage(instantiator.Error()), node->GetSourcePos(), context);
        }
        specialization = instantiator.GetSpecialization();
        context->RemoveSpecialization(functionDefinitionNode);
        if (specialization && specialization->IsFunctionDefinitionSymbol())
        {
            specialization->SetSpecialization();
            FunctionDefinitionSymbol* functionDefinition = static_cast<FunctionDefinitionSymbol*>(specialization);
            functionDefinition->SetFlag(FunctionSymbolFlags::fixedIrName);
            if (!context->InstantiationIrName().empty())
            {
                functionDefinition->SetFixedIrName(context->InstantiationIrName());
                context->SetInstantiationIrName(std::string());
            }
            else
            {
                functionDefinition->SetCompileUnitId(context->GetBoundCompileUnit()->Id());
            }
            auto fn = functionDefinition->FullName();
            auto sfn = util::ToUtf8(*fn);
            //std::cout << ">>instantiate " << *sfname << "\n";
            std::expected<std::string, int> irv = functionDefinition->IrName(context);
            if (!irv) return std::unexpected<int>(irv.error());
            std::string irName = *irv;
            functionTemplateRepository->AddFunctionDefinition(key, functionDefinition, node);
            context->PushBoundFunction(new BoundFunctionNode(functionDefinition, sourcePos));
            std::expected<FunctionDefinitionSymbol*, int> fdef = BindFunction(functionDefinitionNode, functionDefinition, context);
            if (!fdef)
            {
                std::string specializationFullName;
                if (specialization)
                {
                    std::expected<std::u32string, int> fname = specialization->FullName();
                    if (!fname) return std::unexpected<int>(fname.error());
                    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                    if (!sfname) return std::unexpected<int>(sfname.error());
                    specializationFullName = *sfname;
                }
                return Error("otava.symbols.function_templates: error instantiating specialization '" + specializationFullName +
                    "': " + util::GetErrorMessage(fdef.error()), node->GetSourcePos(), context);
            }
            functionDefinition = *fdef;
            specialization = functionDefinition;
            context->PopFlags();
            if (functionDefinition->IsBound())
            {
                std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
                if (!rv) return std::unexpected<int>(rv.error());
            }
            context->PopBoundFunction();
            functionDefinition->GetScope()->ClearParentScopes();
            //std::cout << "<instantiate " << *sfname << "\n";
        }
        else
        {
            return Error("otava.symbols.function_templates: function definition symbol expected", node->GetSourcePos(), context);
        }
        std::expected<bool, int> erv = context->GetSymbolTable()->EndScope();
        if (!erv) return std::unexpected<int>(erv.error());
        prv = instantiationScope.PopParentScope();
        if (!prv)  return std::unexpected<int>(prv.error());
        prv = instantiationScope.PopParentScope();
        if (!prv)  return std::unexpected<int>(prv.error());
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
        for (const auto& boundTemplateParameter : boundTemplateParameters)
        {
            context->GetSymbolTable()->UnmapType(boundTemplateParameter.get());
        }
        specialization->SetSkip();
        return std::expected<FunctionSymbol*, int>(specialization);
    }
    else
    {
        std::expected<bool, int> erv = context->GetInstantiationQueue()->EnqueueInstantiationRequest(functionTemplate, templateParameterMap);
        if (!erv) return std::unexpected<int>(erv.error());
        int arity = templateDeclaration->Arity();
        int argCount = templateArgumentTypes.size();
        if (argCount > arity)
        {
            std::expected<std::string, int> name = util::ToUtf8(functionTemplate->Name());
            return Error("otava.symbols.function_templates: wrong number of template args for instantiating function template '" + *name + "'", 
                node->GetSourcePos(), context);
        }
        InstantiationScope instantiationScope(functionTemplate->Parent()->GetScope());
        std::expected<Scope*, int> nrv = context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context);
        if (!nrv) return std::unexpected<int>(nrv.error());
        std::expected<bool, int> prv = instantiationScope.PushParentScope(*nrv);
        if (!prv)  return std::unexpected<int>(prv.error());
        prv = instantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
        if (!prv)  return std::unexpected<int>(prv.error());
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
                    std::expected<TypeSymbol*, int> trv = ResolveType(defaultTemplateArgNode, DeclarationFlags::none, context);
                    if (!trv) return std::unexpected<int>(trv.error());
                    templateArg = *trv;
                    std::expected<bool, int> erv = context->GetSymbolTable()->EndScope();
                    if (!erv) return std::unexpected<int>(erv.error());
                }
                else
                {
                    return Error("otava.symbols.function_templates: template parameter " + std::to_string(i) + " has no default type argument", 
                        node->GetSourcePos(), context);
                }
            }
            else
            {
                templateArg = templateArgumentTypes[i];
            }
            BoundTemplateParameterSymbol* boundTemplateParameter = new BoundTemplateParameterSymbol(templateParameter->Name());
            boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
            boundTemplateParameter->SetBoundSymbol(templateArg);
            boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
            instantiationScope.Install(boundTemplateParameter, context);
        }
        context->GetSymbolTable()->BeginScope(&instantiationScope);
        Instantiator instantiator(context, &instantiationScope);
        FunctionSymbol* specialization = nullptr;
        context->PushSetFlag(ContextFlags::instantiateFunctionTemplate | ContextFlags::saveDeclarations | ContextFlags::dontBind);
        instantiator.SetFunctionNode(node);
        node->Accept(instantiator);
        if (!instantiator)
        {
            std::string specializationFullName;
            if (specialization)
            {
                std::expected<std::u32string, int> fname = specialization->FullName();
                if (!fname) return std::unexpected<int>(fname.error());
                std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                if (!sfname) return std::unexpected<int>(sfname.error());
                specializationFullName = *sfname;
            }
            return Error("otava.symbols.function_templates: error instantiating specialization '" + specializationFullName +
                "': " + util::GetErrorMessage(instantiator.Error()), node->GetSourcePos(), context);
        }
        specialization = instantiator.GetSpecialization();
        context->RemoveSpecialization(node);
        if (specialization)
        {
            specialization->SetSpecialization();
            specialization->SetFlag(FunctionSymbolFlags::fixedIrName);
            if (functionTemplate->IsExplicitSpecializationDeclaration())
            {
                std::expected<Symbol*, int> lrv = functionTemplate->Parent()->GetScope()->GetNamespaceScope()->Lookup(specialization->GroupName(),
                    SymbolGroupKind::functionSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::none);
                if (!lrv) return std::unexpected<int>(lrv.error());
                Symbol* symbol = *lrv;
                if (symbol && symbol->IsFunctionGroupSymbol())
                {
                    FunctionGroupSymbol* functionGroup = static_cast<FunctionGroupSymbol*>(symbol);
                    FunctionSymbol* functionSymbol = functionGroup->GetMatchingSpecialization(specialization, context);
                    if (functionSymbol)
                    {
                        std::expected<std::string, int> irv = functionSymbol->IrName(context);
                        if (!irv) return std::unexpected<int>(irv.error());
                        std::string irName = *irv;
                        specialization->SetFixedIrName(irName);
                    }
                }
            }
            std::expected<std::string, int> irv = specialization->IrName(context);
            if (!irv) return std::unexpected<int>(irv.error());
            std::string irName = *irv;
            specialization->GetScope()->ClearParentScopes();
        }
        else
        {
            return Error("otava.symbols.function_templates: function symbol expected", node->GetSourcePos(), context);
        }
        context->PopFlags();
        erv = context->GetSymbolTable()->EndScope();
        if (!erv) return std::unexpected<int>(erv.error());
        prv = instantiationScope.PopParentScope();
        if (!prv)  return std::unexpected<int>(prv.error());
        prv = instantiationScope.PopParentScope();
        if (!prv)  return std::unexpected<int>(prv.error());
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
        for (const auto& boundTemplateParameter : boundTemplateParameters)
        {
            context->GetSymbolTable()->UnmapType(boundTemplateParameter.get());
        }
        specialization->SetSkip();
        return std::expected<FunctionSymbol*, int>(specialization);
    }
    return std::expected<FunctionSymbol*, int>(nullptr);
}

} // namespace otava::symbols
