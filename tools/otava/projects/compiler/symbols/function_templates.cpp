// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.function.templates;

import otava.symbols.context;
import otava.symbols.bound.tree;
import otava.symbols.function.group.symbol;
import otava.symbols.exception;
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

FunctionTemplateKey::FunctionTemplateKey() : functionTemplate(nullptr), templateArgumentTypes()
{
}

FunctionTemplateKey::FunctionTemplateKey(FunctionSymbol* functionTemplate_, const std::vector<TypeSymbol*>& templateArgumentTypes_) :
    functionTemplate(functionTemplate_), templateArgumentTypes(templateArgumentTypes_)
{
}

bool FunctionTemplateKeyLess::operator()(const FunctionTemplateKey& left, const FunctionTemplateKey& right) const noexcept
{
    if (left.functionTemplate < right.functionTemplate) return true;
    if (left.functionTemplate > right.functionTemplate) return false;
    return left.templateArgumentTypes < right.templateArgumentTypes;
}

FunctionTemplateRepository::FunctionTemplateRepository()
{
}

FunctionDefinitionSymbol* FunctionTemplateRepository::GetFunctionDefinition(const FunctionTemplateKey& key) const noexcept
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

void FunctionTemplateRepository::AddFunctionDefinition(const FunctionTemplateKey& key, FunctionDefinitionSymbol* functionDefinitionSymbol, otava::ast::Node* functionDefinitionNode)
{
    functionTemplateMap[key] = functionDefinitionSymbol;
    functionDefinitionNodes.push_back(std::unique_ptr<otava::ast::Node>(functionDefinitionNode));
}

FunctionSymbol* InstantiateFunctionTemplate(FunctionSymbol* functionTemplate,
    const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, const soul::ast::SourcePos& sourcePos, Context* context)
{
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
            ThrowException("template parameter type not found", sourcePos, context);
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
    otava::ast::Node* node = context->GetSymbolTable()->GetNode(functionTemplate)->Clone();
    if (node->IsFunctionDefinitionNode())
    {
        otava::ast::FunctionDefinitionNode* functionDefinitionNode = static_cast<otava::ast::FunctionDefinitionNode*>(node);
        int arity = templateDeclaration->Arity();
        int argCount = templateArgumentTypes.size();
        if (argCount > arity)
        {
            ThrowException("otava.symbols.function_templates: wrong number of template args for instantiating function template '" +
                util::ToUtf8(functionTemplate->Name()) + "'",
                node->GetSourcePos(),
                context);
        }
        InstantiationScope instantiationScope(functionTemplate->Parent()->GetScope());
        instantiationScope.PushParentScope(context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context));
        instantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
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
                }
                else
                {
                    ThrowException("otava.symbols.function_templates: template parameter " +
                        std::to_string(i) + " has no default type argument", node->GetSourcePos(), context);
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
        try
        {
            context->PushSetFlag(ContextFlags::instantiateFunctionTemplate | ContextFlags::saveDeclarations | ContextFlags::dontBind);
            instantiator.SetFunctionNode(functionDefinitionNode);
            functionDefinitionNode->Accept(instantiator);
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
                std::string irName = functionDefinition->IrName(context);
                functionDefinition->SetParent(functionTemplate->GetScope()->GetNamespaceScope()->GetSymbol());
                functionTemplateRepository->AddFunctionDefinition(key, functionDefinition, node);
                context->PushBoundFunction(new BoundFunctionNode(functionDefinition, sourcePos));
                functionDefinition = BindFunction(functionDefinitionNode, functionDefinition, context);
                specialization = functionDefinition;
                context->PopFlags();
                if (functionDefinition->IsBound())
                {
                    context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
                }
                context->PopBoundFunction();
                functionDefinition->GetScope()->ClearParentScopes();
            }
            else
            {
                ThrowException("otava.symbols.function_templates: function definition symbol expected", node->GetSourcePos(), context);
            }
        }
        catch (const std::exception& ex)
        {
            std::string specializationFullName;
            if (specialization)
            {
                specializationFullName = util::ToUtf8(specialization->FullName());
            }
            ThrowException("otava.symbols.function_templates: error instantiating specialization '" + specializationFullName +
                "': " + std::string(ex.what()), node->GetSourcePos(), context);
        }
        context->GetSymbolTable()->EndScope();
        instantiationScope.PopParentScope();
        instantiationScope.PopParentScope();
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
        for (const auto& boundTemplateParameter : boundTemplateParameters)
        {
            context->GetSymbolTable()->UnmapType(boundTemplateParameter.get());
        }
        specialization->SetSkip();
        return specialization;
    }
    else
    {
        context->GetInstantiationQueue()->EnqueueInstantiationRequest(functionTemplate, templateParameterMap);
        int arity = templateDeclaration->Arity();
        int argCount = templateArgumentTypes.size();
        if (argCount > arity)
        {
            ThrowException("otava.symbols.function_templates: wrong number of template args for instantiating function template '" +
                util::ToUtf8(functionTemplate->Name()) + "'",
                node->GetSourcePos(),
                context);
        }
        InstantiationScope instantiationScope(functionTemplate->Parent()->GetScope());
        instantiationScope.PushParentScope(context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context));
        instantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
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
                }
                else
                {
                    ThrowException("otava.symbols.function_templates: template parameter " +
                        std::to_string(i) + " has no default type argument", node->GetSourcePos(), context);
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
        try
        {
            context->PushSetFlag(ContextFlags::instantiateFunctionTemplate | ContextFlags::saveDeclarations | ContextFlags::dontBind);
            instantiator.SetFunctionNode(node);
            node->Accept(instantiator);
            specialization = instantiator.GetSpecialization();
            specialization->SetParent(functionTemplate->GetScope()->GetNamespaceScope()->GetSymbol());
            context->RemoveSpecialization(node);
            if (specialization)
            {
                specialization->SetSpecialization();
                specialization->SetFlag(FunctionSymbolFlags::fixedIrName);
                if (functionTemplate->IsExplicitSpecializationDeclaration())
                {
                    Symbol* symbol = functionTemplate->Parent()->GetScope()->GetNamespaceScope()->Lookup(specialization->GroupName(),
                        SymbolGroupKind::functionSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::none);
                    if (symbol && symbol->IsFunctionGroupSymbol())
                    {
                        FunctionGroupSymbol* functionGroup = static_cast<FunctionGroupSymbol*>(symbol);
                        FunctionSymbol* functionSymbol = functionGroup->GetMatchingSpecialization(specialization, context);
                        if (functionSymbol)
                        {
                            specialization->SetFixedIrName(functionSymbol->IrName(context));
                        }
                    }
                }
                std::string irName = specialization->IrName(context);
                specialization->GetScope()->ClearParentScopes();
            }
            else
            {
                ThrowException("otava.symbols.function_templates: function symbol expected", node->GetSourcePos(), context);
            }
            context->PopFlags();
        }
        catch (const std::exception& ex)
        {
            std::string specializationName;
            if (specialization)
            {
                specializationName = util::ToUtf8(specialization->Name());
            }
            ThrowException("otava.symbols.function_templates: error instantiating specialization '" + specializationName +
                "': " + std::string(ex.what()), node->GetSourcePos(), context);
        }
        context->GetSymbolTable()->EndScope();
        instantiationScope.PopParentScope();
        instantiationScope.PopParentScope();
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
        for (const auto& boundTemplateParameter : boundTemplateParameters)
        {
            context->GetSymbolTable()->UnmapType(boundTemplateParameter.get());
        }
        specialization->SetSkip();
        return specialization;
    }
    return nullptr;
}

} // namespace otava::symbols
