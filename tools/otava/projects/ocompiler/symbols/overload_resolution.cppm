// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.overload.resolution;

import std;
import soul.ast.source.pos;
import otava.symbols.context;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.bound.tree;
import otava.symbols.templates;
import otava.symbols.type.symbol;
import otava.symbols.template_param_compare;
import otava.symbols.scope;

export namespace otava::symbols {

class BoundFunctionCallNode;
class BoundExpressionNode;
class Context;

enum class OverloadResolutionFlags : std::int32_t
{
    none = 0, dontInstantiate = 1 << 0, dontSearchArgumentScopes = 1 << 1, noMemberFunctions = 1 << 2
};

constexpr OverloadResolutionFlags operator|(OverloadResolutionFlags left, OverloadResolutionFlags right)
{
    return OverloadResolutionFlags(std::int32_t(left) | std::int32_t(right));
}

constexpr OverloadResolutionFlags operator&(OverloadResolutionFlags left, OverloadResolutionFlags right)
{
    return OverloadResolutionFlags(std::int32_t(left) & std::int32_t(right));
}

constexpr OverloadResolutionFlags operator~(OverloadResolutionFlags flags)
{
    return OverloadResolutionFlags(~std::int32_t(flags));
}

class FunctionSymbol;
class ClassTemplateSpecializationSymbol;

struct ArgumentMatch
{
    ArgumentMatch();
    FunctionSymbol* conversionFun;
    ConversionKind conversionKind;
    std::int32_t distance;
    std::int32_t fundamentalTypeDistance;
    OperationFlags preConversionFlags;
    OperationFlags postConversionFlags;
    int32_t value;
};

struct FunctionMatch
{
    FunctionMatch();
    FunctionMatch(FunctionSymbol* function_, Context* context_);
    FunctionMatch& operator=(const FunctionMatch& that);
    FunctionSymbol* function;
    Context* context;
    std::vector<ArgumentMatch> argumentMatches;
    int numConversions;
    int numQualifyingConversions;
    std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
    ClassTemplateSpecializationSymbol* specialization;
    std::vector<std::unique_ptr<BoundExpressionNode>> defaultArgs;
    std::string warning;
};

struct BetterFunctionMatch
{
    inline bool operator()(const std::unique_ptr<FunctionMatch>& left, const std::unique_ptr<FunctionMatch>& right) const { return BetterFunctionMatch()(*left, *right); }
    bool operator()(const FunctionMatch& left, const FunctionMatch& right) const;
};

std::expected<bool, int> FindTemplateParameterMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch, 
    const soul::ast::SourcePos& sourcePos, Context* context);

std::expected<bool, int> FindClassTemplateMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context);

std::expected<bool, int> FindClassTemplateSpecializationMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context);

std::expected<BoundExpressionNode*, int> MakeLvalueExpression(BoundExpressionNode* arg, const soul::ast::SourcePos& sourcePos, Context* context);

std::expected<std::unique_ptr<BoundFunctionCallNode>, int> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs,
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, FunctionMatch& functionMatch,
    OverloadResolutionFlags flags);

std::expected<std::unique_ptr<BoundFunctionCallNode>, int>  ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs,
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, OverloadResolutionFlags flags);

std::expected<std::unique_ptr<BoundFunctionCallNode>, int> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs,
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, FunctionMatch& functionMatch);

std::expected<std::unique_ptr<BoundFunctionCallNode>, int> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs,
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
