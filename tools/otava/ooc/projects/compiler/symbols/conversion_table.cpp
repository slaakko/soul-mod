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

ConversionTableEntry::ConversionTableEntry(TypeSymbol* paramType_, TypeSymbol* argType_) : key(), paramType(paramType_), argType(argType_)
{
    std::u32string combinedName = paramType->FullName();
    combinedName.append(1, '.').append(argType->FullName());
    key = combinedName;
}

bool ConversionTableEntryEqual::operator()(const ConversionTableEntry& left, const ConversionTableEntry& right) const noexcept
{
    return TypesEqual(left.paramType, right.paramType, nullptr) && TypesEqual(left.argType, right.argType, nullptr);
}

size_t ConversionTableEntryHash::operator()(const ConversionTableEntry& entry) const noexcept
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

void ConversionTable::AddConversion(FunctionSymbol* conversion)
{
    if (conversion->ConversionParamType() && conversion->ConversionArgType())
    {
        ConversionTableEntry entry(conversion->ConversionParamType(), conversion->ConversionArgType());
        conversionMap[entry] = conversion;
    }
    else
    {
        conversionFunctions.push_back(conversion);
    }
}

void ConversionTable::Make()
{
    for (auto* conversion : conversionFunctions)
    {
        ConversionTableEntry entry(conversion->ConversionParamType(), conversion->ConversionArgType());
        conversionMap[entry] = conversion;
    }
}

FunctionSymbol* ConversionTable::GetConversion(TypeSymbol* paramType, TypeSymbol* argType, Context* context) const
{
    TypeSymbol* paramPlainType = paramType->PlainType(context);
    TypeSymbol* argPlainType = argType->PlainType(context);
    ConversionTableEntry entry(paramPlainType, argPlainType);
    auto it = conversionMap.find(entry);
    if (it != conversionMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

} // otava::symbols
