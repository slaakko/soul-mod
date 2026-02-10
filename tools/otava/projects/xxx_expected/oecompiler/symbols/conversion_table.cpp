// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.conversion.table;

import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.type.symbol;
import otava.symbols.type_compare;
import otava.symbols.symbol.table;
import otava.symbols.modules;
import util.unicode;

namespace otava::symbols {

ConversionTableEntry::ConversionTableEntry(TypeSymbol* paramType_, TypeSymbol* argType_) : key(), paramType(paramType_), argType(argType_), error(0)
{
    std::expected<std::u32string, int> fname = paramType->FullName();
    if (!fname)
    {
        error = fname.error();
        return;
    }
    std::u32string combinedName = *fname;
    fname = argType->FullName();
    if (!fname)
    {
        error = fname.error();
        return;
    }
    combinedName.append(1, '.').append(*fname);
    key = combinedName;
}

bool ConversionTableEntryEqual::operator()(const ConversionTableEntry& left, const ConversionTableEntry& right) const
{
    return TypesEqual(left.paramType, right.paramType, nullptr) && TypesEqual(left.argType, right.argType, nullptr);
}

size_t ConversionTableEntryHash::operator()(const ConversionTableEntry& entry) const
{
    size_t hashCode = std::hash<std::u32string>()(entry.key);
    return hashCode;
}

ConversionTable::ConversionTable(SymbolTable* symbolTable_) : symbolTable(symbolTable_), conversionMap()
{
}

void ConversionTable::Import(const ConversionTable& that)
{
    for (const auto& p : that.conversionMap)
    {
        ConversionTableEntry entry = p.first;
        conversionMap[entry] = p.second;
    }
}

std::expected<bool, int> ConversionTable::AddConversion(FunctionSymbol* conversion)
{
    if (conversion->ConversionParamType() && conversion->ConversionArgType())
    {
        ConversionTableEntry entry(conversion->ConversionParamType(), conversion->ConversionArgType());
        if (entry.error) return std::unexpected<int>(entry.error);
        conversionMap[entry] = conversion;
    }
    else
    {
        conversionFunctions.push_back(conversion);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ConversionTable::Make()
{
    for (FunctionSymbol* conversion : conversionFunctions)
    {
        ConversionTableEntry entry(conversion->ConversionParamType(), conversion->ConversionArgType());
        if (entry.error) return std::unexpected<int>(entry.error);
        conversionMap[entry] = conversion;
    }
    return std::expected<bool, int>(true);
}

std::expected<FunctionSymbol*, int> ConversionTable::GetConversion(TypeSymbol* paramType, TypeSymbol* argType, Context* context) const
{
    std::expected<TypeSymbol*, int> pt = paramType->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* paramPlainType = *pt;
    std::expected<TypeSymbol*, int> pa = argType->PlainType(context);
    if (!pa) return std::unexpected<int>(pa.error());
    TypeSymbol* argPlainType = *pa;;
    ConversionTableEntry entry(paramPlainType, argPlainType);
    if (entry.error) return std::unexpected<int>(entry.error);
    auto it = conversionMap.find(entry);
    if (it != conversionMap.end())
    {
        return std::expected<FunctionSymbol*, int>(it->second);
    }
    else
    {
        return std::expected<FunctionSymbol*, int>(nullptr);
    }
}

} // otava::symbols
