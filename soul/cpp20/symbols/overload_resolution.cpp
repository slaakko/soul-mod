// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.overload.resolution;

import soul.cpp20.symbols.bound.tree;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.function.group.symbol;
import soul.cpp20.symbols.function.symbol;
import soul.cpp20.symbols.operation.repository;
import soul.cpp20.symbols.symbol.table;
import util.unicode;

namespace soul::cpp20::symbols {

FunctionSymbol* SelectBestMatchingFunction(const std::vector<FunctionSymbol*>& viableFunctions, const std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::vector<FunctionSymbol*> matchingFunctions;
    for (FunctionSymbol* viableFunction : viableFunctions)
    {
        int n = viableFunction->Arity();
        if (n != args.size())
        {
            ThrowException("wrong arity", sourcePos, context);
        }
        bool match = true;
        for (int i = 0; i < n; ++i)
        {
            TypeSymbol* type = viableFunction->MemFunParameters()[i]->GetType();
            BoundExpressionNode* arg = args[i].get();
            if (!arg)
            {
                return nullptr; // TODO
                ThrowException("no matching function found for function call", sourcePos, context);
            }
            if (arg->GetType() != type)
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            matchingFunctions.push_back(viableFunction);
        }
    }
    if (matchingFunctions.size() == 1)
    {
        return matchingFunctions.front();
    }
    else if (matchingFunctions.size() > 1)
    {
        // todo SORT
        return matchingFunctions.front();
    }
    else
    {
        return nullptr; // TODO
        ThrowException("no matching function found for function call", sourcePos, context);
    }
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::vector<FunctionSymbol*> viableFunctions;
    std::unique_ptr<BoundFunctionCallNode> operationFunctionCall = context->GetOperationRepository()->GetOperation(groupName, args);
    if (operationFunctionCall)
    {
        return operationFunctionCall;
    }
    context->GetSymbolTable()->CollectViableFunctions(scope, groupName, args.size(), viableFunctions, context);
    FunctionSymbol* bestMatch = SelectBestMatchingFunction(viableFunctions, args, sourcePos, context);
    if (bestMatch)
    {
        std::unique_ptr<BoundFunctionCallNode> boundFunctionCall(new BoundFunctionCallNode(bestMatch));
        for (auto& arg : args)
        {
            boundFunctionCall->AddArgument(arg.release());
        }
        return boundFunctionCall;
    }
    else
    {
        return std::unique_ptr<BoundFunctionCallNode>();
    }
}

} // namespace soul::cpp20::symbols
