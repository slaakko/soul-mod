// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.conversion.table;

import std.core;

export namespace otava::symbols {

class Context;
class TypeSymbol;
class FunctionSymbol;
class SymbolTable;

struct ConversionTableEntry
{
    ConversionTableEntry(TypeSymbol* paramType_, TypeSymbol* argType_);
    std::u32string key;
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
    ConversionTable(SymbolTable* symbolTable_);
    void Import(const ConversionTable& that);
    void AddConversion(FunctionSymbol* conversion);
    FunctionSymbol* GetConversion(TypeSymbol* paramType, TypeSymbol* argType, Context* context) const;
    void Make();
private:
    SymbolTable* symbolTable;
    std::vector<FunctionSymbol*> conversionFunctions;
    std::unordered_map<ConversionTableEntry, FunctionSymbol*, ConversionTableEntryHash, ConversionTableEntryEqual> conversionMap;
};

} // otava::symbols
