// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.argument.conversion.table;

import std;
import otava.symbols.container.symbol;
import otava.symbols.function.symbol;
import otava.symbols.context;

import soul.ast.source.pos;

export namespace otava::symbols {

class BoundExpressionNode;
class Context;
class TypeSymbol;

struct ArgumentMatch;
struct FunctionMatch;

class ArgumentConversion
{
public:
    virtual std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) = 0;
};

class ArgumentConversionTable
{
public:
    ArgumentConversionTable();
    void AddArgumentConversion(ArgumentConversion* argumentConversion);
    std::expected<FunctionSymbol*, int> GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<FunctionSymbol*, int> GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, const soul::ast::SourcePos& sourcePos, 
        ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, Context* context);
private:
    std::vector<std::unique_ptr<ArgumentConversion>> argumentConversions;
    std::vector<std::unique_ptr<FunctionSymbol>> conversionFunctions;
};

} // namespace otava::symbols
