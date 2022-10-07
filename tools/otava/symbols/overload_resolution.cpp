// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.overload.resolution;

import otava.symbols.bound.tree;
import otava.symbols.bound.tree.visitor;
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

class GroupNameResolver : public DefaultBoundTreeVisitor
{
public:
    void Visit(BoundFunctionGroupNode& node) override;
    void Visit(BoundTypeNode& node) override;
    const std::u32string& GetGroupName() const { return groupName; }
private:
    std::u32string groupName;
};

void GroupNameResolver::Visit(BoundFunctionGroupNode& node)
{
    groupName = node.GetFunctionGroupSymbol()->Name();
}

void GroupNameResolver::Visit(BoundTypeNode& node)
{
    groupName = U"@conversion";
}

std::u32string GetGroupName(BoundExpressionNode* node)
{
    GroupNameResolver resolver;
    node->Accept(resolver);
    return resolver.GetGroupName();
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

FunctionSymbol* SelectBestMatchingFunction(const std::vector<FunctionSymbol*>& viableFunctions, const std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
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
        return functionMatches.front().function;
    }
    else if (functionMatches.size() > 1)
    {
        std::sort(functionMatches.begin(), functionMatches.end(), BetterFunctionMatch());
        if (BetterFunctionMatch()(functionMatches[0], functionMatches[1]))
        {
            return functionMatches.front().function;
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
        return std::unique_ptr<BoundFunctionCallNode>(); // TODO
    }
}

} // namespace otava::symbols
