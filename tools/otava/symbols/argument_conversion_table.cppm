// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.argument.conversion.table;

import std.core;
import soul.ast.source.pos;

export namespace otava::symbols {

class BoundExpressionNode;
class Context;
class FunctionSymbol;
class TypeSymbol;

struct ArgumentMatch;
struct FunctionMatch;

class ArgumentConversion
{
public:
    virtual FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
        const soul::ast::SourcePos& sourcePos, Context* context) = 0;
};

class ArgumentConversionTable
{
public:
    ArgumentConversionTable();
    void AddArgumentConversion(ArgumentConversion* argumentConversion);
    FunctionSymbol* GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, const soul::ast::SourcePos& sourcePos, Context* context);
    FunctionSymbol* GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, const soul::ast::SourcePos& sourcePos, ArgumentMatch& argumentMatch,
        FunctionMatch& functionMatch, Context* context);
private:
    std::vector<std::unique_ptr<ArgumentConversion>> argumentConversions;
    std::vector<std::unique_ptr<FunctionSymbol>> conversionFunctions;
};

} // namespace otava::symbols
