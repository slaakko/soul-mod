// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.argument.conversion.table;

import std.core;

export namespace otava::symbols {

class Context;
class FunctionSymbol;
class TypeSymbol;

class ArgumentConversion
{
public:
    virtual FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context) = 0;
};

class ArgumentConversionTable
{
public:
    ArgumentConversionTable();
    void AddArgumentConversion(ArgumentConversion* argumentConversion);
    FunctionSymbol* GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, Context* context);
private:
    std::vector<std::unique_ptr<ArgumentConversion>> argumentConversions;
    std::vector<std::unique_ptr<FunctionSymbol>> conversionFunctions;
};

} // namespace otava::symbols