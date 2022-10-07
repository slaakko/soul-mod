// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.conversion.table;

import otava.symbols.function.symbol;

namespace otava::symbols {

ConversionTableEntry::ConversionTableEntry(TypeSymbol* paramType_, TypeSymbol* argType_) : paramType(paramType_), argType(argType_)
{
}

void ConversionTable::Import(const ConversionTable& that)
{
    for (const auto& p : that.conversionMap)
    {
        const ConversionTableEntry& entry = p.first;
        conversionMap[entry] = p.second;
    }
}

void ConversionTable::AddConversion(FunctionSymbol* conversion)
{
    ConversionTableEntry entry(conversion->ConversionParamType(), conversion->ConversionArgType());
    conversionMap.erase(entry);
    conversionMap.insert(std::make_pair(entry, conversion));
}

FunctionSymbol* ConversionTable::GetConversion(TypeSymbol* paramType, TypeSymbol* argType) const
{
    TypeSymbol* paramPlainType = paramType->PlainType();
    TypeSymbol* argPlainType = argType->PlainType();
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
