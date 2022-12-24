// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.conversion.table;

import std.core;

export namespace otava::symbols {

class Context;
class TypeSymbol;
class FunctionSymbol;

struct ConversionTableEntry
{
    ConversionTableEntry(TypeSymbol* paramType_, TypeSymbol* argType_);
    TypeSymbol* paramType;
    TypeSymbol* argType;
};

struct ConversionTableEntryEqual
{
    bool operator()(const ConversionTableEntry& left, const ConversionTableEntry& right) const;
};

struct ConversionTableEntryHash
{
    size_t operator()(const ConversionTableEntry& entry) const;
};

class ConversionTable
{
public:
    void Import(const ConversionTable& that);
    void AddConversion(FunctionSymbol* conversion);
    FunctionSymbol* GetConversion(TypeSymbol* paramType, TypeSymbol* argType, Context* context) const;
    void Make();
private:
    std::vector<FunctionSymbol*> conversionFunctions;
    std::unordered_map<ConversionTableEntry, FunctionSymbol*, ConversionTableEntryHash, ConversionTableEntryEqual> conversionMap;
};

} // otava::symbols
