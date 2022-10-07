// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.conversion.table;

import std.core;

export namespace otava::symbols {

class TypeSymbol;
class FunctionSymbol;

struct ConversionTableEntry
{
    ConversionTableEntry(TypeSymbol* paramType_, TypeSymbol* argType_);
    TypeSymbol* paramType;
    TypeSymbol* argType;
};

struct ConversionTableEntryLess
{
    bool operator()(const ConversionTableEntry& left, const ConversionTableEntry& right) const
    {
        if (left.paramType < right.paramType) return true;
        if (left.paramType > right.paramType) return false;
        return left.argType < right.argType;
    }
};

class ConversionTable
{
public:
    void Import(const ConversionTable& that);
    void AddConversion(FunctionSymbol* conversion);
    FunctionSymbol* GetConversion(TypeSymbol* paramType, TypeSymbol* argType) const;
private:
    std::map<ConversionTableEntry, FunctionSymbol*, ConversionTableEntryLess> conversionMap;
};

} // otava::symbols
