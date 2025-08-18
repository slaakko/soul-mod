// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.inline_functions;

import otava.symbols.context;
import otava.symbols.bound.tree;
import otava.symbols.function.symbol;
import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.function.templates;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
import otava.symbols.instantiator;
import otava.symbols.exception;
import otava.symbols.statement.binder;
import otava.ast;
import util;

namespace otava::symbols {

InlineFunctionRepository::InlineFunctionRepository()
{
}

void InlineFunctionRepository::AddInlineFunction(FunctionSymbol* fn, FunctionSymbol* inlineFn)
{
    inlineFunctionMap[fn] = inlineFn;
}

FunctionSymbol* InlineFunctionRepository::GetInlineFunction(FunctionSymbol* fn) const
{
    auto it = inlineFunctionMap.find(fn);
    if (it != inlineFunctionMap.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

FunctionSymbol* InstantiateInlineFunction(FunctionSymbol* fn, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (fn->IsGenerated()) return fn;
    InlineFunctionRepository* inlineFunctionRepository = context->GetBoundCompileUnit()->GetInlineFunctionRepository();
    FunctionSymbol* inlineFn = inlineFunctionRepository->GetInlineFunction(fn);
    if (inlineFn)
    {
        return inlineFn;
    }
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    otava::ast::Node* node = context->GetSymbolTable()->GetNode(fn)->Clone();
    if (node->IsFunctionDefinitionNode())
    {
        otava::ast::FunctionDefinitionNode* functionDefinitionNode = static_cast<otava::ast::FunctionDefinitionNode*>(node);
        InstantiationScope instantiationScope(fn->Parent()->GetScope());
        instantiationScope.PushParentScope(context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context));
        instantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
        context->GetSymbolTable()->BeginScope(&instantiationScope);
        Instantiator instantiator(context, &instantiationScope);
        FunctionSymbol* inlineFn = nullptr;
        try
        {
            context->PushSetFlag(ContextFlags::instantiateInlineFunction | ContextFlags::saveDeclarations | ContextFlags::dontBind);
            instantiator.SetFunctionNode(functionDefinitionNode);
            functionDefinitionNode->Accept(instantiator);
            inlineFn = instantiator.GetSpecialization();
            context->RemoveSpecialization(functionDefinitionNode);
            if (inlineFn && inlineFn->IsFunctionDefinitionSymbol())
            {
                inlineFn->SetSpecialization();
                FunctionDefinitionSymbol* functionDefinition = static_cast<FunctionDefinitionSymbol*>(inlineFn);
                functionDefinition->SetFlag(FunctionSymbolFlags::fixedIrName);
                functionDefinition->SetCompileUnitId(context->GetBoundCompileUnit()->Id());
                functionDefinition->SetParent(fn->Parent());
                std::string irName = functionDefinition->IrName(context);
                inlineFunctionRepository->AddInlineFunction(fn, inlineFn);
                context->PushBoundFunction(new BoundFunctionNode(functionDefinition, sourcePos));
                functionDefinition = BindFunction(functionDefinitionNode, functionDefinition, context);
                inlineFn = functionDefinition;
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
                ThrowException("otava.symbols.inline_functions: function definition symbol expected", node->GetSourcePos(), context);
            }
        }
        catch (const std::exception& ex)
        {
            std::string inlineFunctionFullName;
            if (inlineFn)
            {
                inlineFunctionFullName = util::ToUtf8(inlineFn->FullName());
            }
            ThrowException("otava.symbols.inline_functions: error instantiating inline function '" + inlineFunctionFullName +
                "': " + std::string(ex.what()), node->GetSourcePos(), context);
        }
        context->GetSymbolTable()->EndScope();
        instantiationScope.PopParentScope();
        instantiationScope.PopParentScope();
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
        return inlineFn;
    }
    else
    {
        // todo
        int x = 0;
    }
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    return fn;
}

} // namespace otava::symbols
