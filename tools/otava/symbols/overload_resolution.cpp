// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.overload.resolution;

import otava.symbols.bound.tree;
import otava.symbols.bound.node;
import otava.symbols.context;
import otava.symbols.exception;
import otava.symbols.function.group.symbol;
import otava.symbols.function.symbol;
import otava.symbols.match;
import otava.symbols.operation.repository;
import otava.symbols.symbol.table;
import otava.symbols.conversion.table;
import util.unicode;

namespace otava::symbols {

std::unique_ptr<BoundFunctionCallNode> CreateBoundFunctionCall(const FunctionMatch& functionMatch, std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos)
{
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall(new BoundFunctionCallNode(functionMatch.function, sourcePos));
    int n = args.size();
    for (int i = 0; i < n; ++i)
    {
        BoundExpressionNode* arg = args[i].release();
        const ArgumentMatch& argumentMatch = functionMatch.argumentMatches[i];
        if (argumentMatch.conversionFun)
        {
            arg = new BoundConversionNode(arg, argumentMatch.conversionFun, sourcePos);
        }
        boundFunctionCall->AddArgument(arg);
    }
    return boundFunctionCall;
}

bool FindQualificationConversion(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch, ArgumentMatch& argumentMatch)
{
    return false;
}

bool FindConversions(FunctionMatch& functionMatch, const std::vector<std::unique_ptr<BoundExpressionNode>>& args, Context* context)
{
    int arity = args.size();
    int n = std::min(arity, functionMatch.function->Arity());
    for (int i = 0; i < n; ++i)
    {
        BoundExpressionNode* arg = args[i].get();
        TypeSymbol* argType = arg->GetType();
        ParameterSymbol* parameter = functionMatch.function->Parameters()[i];
        TypeSymbol* paramType = parameter->GetType();
        if (argType == paramType)
        {
            functionMatch.argumentMatches.push_back(ArgumentMatch());
        }
        else
        {
            bool qualificationConversionMatch = false;
            ArgumentMatch argumentMatch;
            if (argType->PlainType() == paramType->PlainType())
            {
                qualificationConversionMatch = FindQualificationConversion(argType, paramType, arg, functionMatch, argumentMatch);
                if (qualificationConversionMatch)
                {
                    functionMatch.argumentMatches.push_back(argumentMatch);
                }
            }
            if (!qualificationConversionMatch)
            {
                FunctionSymbol* conversionFun = context->GetSymbolTable()->GetConversionTable().GetConversion(paramType, argType);
                if (conversionFun)
                {
                    argumentMatch.conversionFun = conversionFun;
                    ++functionMatch.numConversions;
                    continue;
                }
                return false;
            }
        }
    }
    return true;
}

FunctionMatch SelectBestMatchingFunction(const std::vector<FunctionSymbol*>& viableFunctions, const std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::vector<FunctionMatch> functionMatches;
    for (FunctionSymbol* viableFunction : viableFunctions)
    {
        FunctionMatch functionMatch(viableFunction);
        if (FindConversions(functionMatch, args, context))
        {
            functionMatches.push_back(functionMatch);
        }
    }
    if (functionMatches.size() == 1)
    {
        return functionMatches.front();
    }
    else if (functionMatches.size() > 1)
    {
        std::sort(functionMatches.begin(), functionMatches.end(), BetterFunctionMatch());
        if (BetterFunctionMatch()(functionMatches[0], functionMatches[1]))
        {
            return functionMatches.front();
        }
        else
        {
            ThrowException("ambiguous function call", sourcePos, context);
        }
    }
    else
    {
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
    FunctionMatch bestMatch = SelectBestMatchingFunction(viableFunctions, args, sourcePos, context);
    std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = CreateBoundFunctionCall(bestMatch, args, sourcePos);
    return boundFunctionCall;
}

} // namespace otava::symbols
