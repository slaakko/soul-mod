// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.inline_functions;

import otava.symbols.context;
import otava.symbols.bound.tree;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.function.templates;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
import otava.symbols.instantiator;
import otava.symbols.error;
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

std::expected<FunctionSymbol*, int> InstantiateInlineFunction(FunctionSymbol* fn, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (fn->IsGenerated()) return std::expected<FunctionSymbol*, int>(fn);
    InlineFunctionRepository* inlineFunctionRepository = context->GetBoundCompileUnit()->GetInlineFunctionRepository();
    FunctionSymbol* inlineFn = inlineFunctionRepository->GetInlineFunction(fn);
    if (inlineFn)
    {
        return std::expected<FunctionSymbol*, int>(inlineFn);
    }
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    otava::ast::Node* node = context->GetSymbolTable()->GetNodeNothrow(fn);
    if (node)
    {
        std::expected<otava::ast::Node*, int> c = node->Clone();
        if (!c) return std::unexpected<int>(c.error());
        node = *c;
    }
    else
    {
        std::expected<std::u32string, int> fname = fn->FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        std::cout << "warning: function '" << *sfname + "' not inlined because node not found" << "\n";
        return std::expected<FunctionSymbol*, int>(fn);
    }
    if (node->IsFunctionDefinitionNode())
    {
        otava::ast::FunctionDefinitionNode* functionDefinitionNode = static_cast<otava::ast::FunctionDefinitionNode*>(node);
        InstantiationScope instantiationScope(fn->Parent()->GetScope());
        std::expected<Scope*, int> nrv = context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context);
        if (!nrv) return std::unexpected<int>(nrv.error());
        std::expected<bool, int> prv = instantiationScope.PushParentScope(*nrv);
        if (!prv) return std::unexpected<int>(prv.error());
        prv = instantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
        if (!prv) return std::unexpected<int>(prv.error());
        context->GetSymbolTable()->BeginScope(&instantiationScope);
        Instantiator instantiator(context, &instantiationScope);
        FunctionSymbol* inlineFn = nullptr;
        context->PushSetFlag(ContextFlags::instantiateInlineFunction | ContextFlags::saveDeclarations | ContextFlags::dontBind);
        instantiator.SetFunctionNode(functionDefinitionNode);
        functionDefinitionNode->Accept(instantiator);
        if (!instantiator)
        {
            std::string inlineFunctionFullName;
            if (inlineFn)
            {
                std::expected<std::u32string, int> fname = inlineFn->FullName();
                if (!fname) return std::unexpected<int>(fname.error());
                std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                if (!sfname) return std::unexpected<int>(sfname.error());
                inlineFunctionFullName = *sfname;
            }
            return Error("otava.symbols.inline_functions: error instantiating inline function '" + inlineFunctionFullName +
                "': " + util::GetErrorMessage(instantiator.Error()), node->GetSourcePos(), context);
        }
        inlineFn = instantiator.GetSpecialization();
        context->RemoveSpecialization(functionDefinitionNode);
        if (inlineFn && inlineFn->IsFunctionDefinitionSymbol())
        {
            inlineFn->SetSpecialization();
            FunctionDefinitionSymbol* functionDefinition = static_cast<FunctionDefinitionSymbol*>(inlineFn);
            functionDefinition->SetFlag(FunctionSymbolFlags::fixedIrName);
            functionDefinition->SetCompileUnitId(context->GetBoundCompileUnit()->Id());
            functionDefinition->SetParent(fn->Parent());
            std::expected<std::string, int> irv = functionDefinition->IrName(context);;
            if (!irv) return std::unexpected<int>(irv.error());
            std::string irName = *irv;
            inlineFunctionRepository->AddInlineFunction(fn, inlineFn);
            context->PushBoundFunction(new BoundFunctionNode(functionDefinition, sourcePos));
            std::expected<FunctionDefinitionSymbol*, int> rv = BindFunction(functionDefinitionNode, functionDefinition, context);
            if (!rv)
            {
                std::string inlineFunctionFullName;
                if (inlineFn)
                {
                    std::expected<std::u32string, int> fname = inlineFn->FullName();
                    if (!fname) return std::unexpected<int>(fname.error());
                    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                    if (!sfname) return std::unexpected<int>(sfname.error());
                    inlineFunctionFullName = *sfname;
                }
                return Error("otava.symbols.inline_functions: error instantiating inline function '" + inlineFunctionFullName +
                    "': " + util::GetErrorMessage(rv.error()), node->GetSourcePos(), context);
            }
            functionDefinition = *rv;
            inlineFn = functionDefinition;
            context->PopFlags();
            if (functionDefinition->IsBound())
            {
                std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
                if (!rv) return std::unexpected<int>(rv.error());
            }
            context->PopBoundFunction();
            functionDefinition->GetScope()->ClearParentScopes();
        }
        else
        {
            return Error("otava.symbols.inline_functions: function definition symbol expected", node->GetSourcePos(), context);
        }
        std::expected<bool, int> erv = context->GetSymbolTable()->EndScope();
        if (!erv) return std::unexpected<int>(erv.error());
        prv = instantiationScope.PopParentScope();
        if (!prv) return std::unexpected<int>(prv.error());
        prv = instantiationScope.PopParentScope();
        if (!prv) return std::unexpected<int>(prv.error());
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
        return inlineFn;
    }
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    return fn;
}

} // namespace otava::symbols
