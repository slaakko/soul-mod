// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.function.templates;

import otava.symbols.context;
import otava.symbols.bound.tree;
import otava.symbols.function.symbol;
import otava.symbols.templates;
import otava.symbols.exception;
import otava.symbols.symbol.table;
import otava.symbols.declaration;
import otava.symbols.type.resolver;
import otava.symbols.instantiator;
import otava.symbols.statement.binder;
import otava.ast.function;
import util.unicode;

namespace otava::symbols {

FunctionTemplateKey::FunctionTemplateKey(FunctionSymbol* functionTemplate_, const std::vector<TypeSymbol*>& templateArgumentTypes_) :
    functionTemplate(functionTemplate_), templateArgumentTypes(templateArgumentTypes_)
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

void FunctionTemplateRepository::AddFunctionDefinition(const FunctionTemplateKey& key, FunctionDefinitionSymbol* functionDefinitionSymbol, otava::ast::Node* functionDefinitionNode)
{
    functionTemplateMap[key] = functionDefinitionSymbol;
    functionDefinitionNodes.push_back(std::unique_ptr<otava::ast::Node>(functionDefinitionNode));
}

FunctionDefinitionSymbol* InstantiateFunctionTemplate(FunctionSymbol* functionTemplate, const std::map<TemplateParameterSymbol*, TypeSymbol*>& templateParameterMap,
    const soul::ast::SourcePos& sourcePos, Context* context)
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
                    ThrowException("otava.symbols.function_templates: template parameter " + std::to_string(i) + " has no default type argument", node->GetSourcePos(), context);
                }
            }
            else
            {
                templateArg = templateArgumentTypes[i];
            }
            BoundTemplateParameterSymbol* boundTemplateParameter(new BoundTemplateParameterSymbol(templateParameter->Name()));
            boundTemplateParameter->SetTemplateParameterSymbol(templateParameter);
            boundTemplateParameter->SetBoundSymbol(templateArg);
            boundTemplateParameters.push_back(std::unique_ptr<BoundTemplateParameterSymbol>(boundTemplateParameter));
            instantiationScope.Install(boundTemplateParameter);
        }
        context->GetSymbolTable()->BeginScope(&instantiationScope);
        Instantiator instantiator(context, &instantiationScope);
        FunctionDefinitionSymbol* specialization = nullptr;
        try
        {
            context->PushSetFlag(ContextFlags::instantiateFunctionTemplate | ContextFlags::saveDeclarations | ContextFlags::dontBind);
            context->SetFunctionDefinitionNode(functionDefinitionNode);
            functionDefinitionNode->Accept(instantiator);
            specialization = context->GetSpecialization();
            context->PushBoundFunction(new BoundFunctionNode(specialization, sourcePos));
            BindFunction(functionDefinitionNode, specialization, context);
            context->PopFlags();
            if (specialization->IsBound())
            {
                context->GetBoundCompileUnit()->AddBoundNode(context->ReleaseBoundFunction());
            }
            context->PopBoundFunction();
            specialization->GetScope()->ClearParentScopes();
        }
        catch (const std::exception& ex)
        {
            ThrowException("otava.symbols.function_templates: error instantiating specialization '" +
                util::ToUtf8(specialization->FullName()) + "': " + std::string(ex.what()), node->GetSourcePos(), context);
        }
        context->GetSymbolTable()->EndScope();
        functionTemplateRepository->AddFunctionDefinition(key, specialization, node);
        return specialization;
    }
    else
    {
        ThrowException("function definition node expected", sourcePos, context);
    }
    return nullptr;
}

} // namespace otava::symbols
