// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.overload.resolution;

import std.core;
import soul.ast.source.pos;
import otava.symbols.templates;
import otava.symbols.template_param_compare;
import otava.symbols.scope;

export namespace otava::symbols {

class BoundFunctionCallNode;
class BoundExpressionNode;
class Context;
class Exception;

enum class OverloadResolutionFlags : int32_t
{
    none = 0, dontInstantiate = 1 << 0, dontSearchArgumentScopes = 1 << 1
};

constexpr OverloadResolutionFlags operator|(OverloadResolutionFlags left, OverloadResolutionFlags right)
{
    return OverloadResolutionFlags(int32_t(left) | int32_t(right));
}

constexpr OverloadResolutionFlags operator&(OverloadResolutionFlags left, OverloadResolutionFlags right)
{
    return OverloadResolutionFlags(int32_t(left) & int32_t(right));
}

constexpr OverloadResolutionFlags operator~(OverloadResolutionFlags flags)
{
    return OverloadResolutionFlags(~int32_t(flags));
}

class FunctionSymbol;
class ClassTemplateSpecializationSymbol;
enum class ConversionKind : int32_t;
enum class OperationFlags : int32_t;

struct ArgumentMatch
{
    ArgumentMatch();
    FunctionSymbol* conversionFun;
    ConversionKind conversionKind;
    int32_t distance;
    int32_t fundamentalTypeDistance;
    OperationFlags preConversionFlags;
    OperationFlags postConversionFlags;
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
};

struct BetterFunctionMatch
{
    bool operator()(const std::unique_ptr<FunctionMatch>& left, const std::unique_ptr<FunctionMatch>& right) const;
    bool operator()(const FunctionMatch& left, const FunctionMatch& right) const;
};

bool FindTemplateParameterMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos,
    Context* context);

bool FindClassTemplateMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context);
    
bool FindClassTemplateSpecializationMatch(TypeSymbol* argType, TypeSymbol* paramType, BoundExpressionNode* arg, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context);

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs,
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex, FunctionMatch& functionMatch, 
    OverloadResolutionFlags flags);

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex, OverloadResolutionFlags flags);

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex, FunctionMatch& functionMatch);

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex);

std::unique_ptr<BoundFunctionCallNode> ResolveOverloadThrow(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context, OverloadResolutionFlags flags);

std::unique_ptr<BoundFunctionCallNode> ResolveOverloadThrow(Scope* scope, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
    std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
