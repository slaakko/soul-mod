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
    for (const auto& conversion : conversionFunctions)
    {
        ConversionTableEntry entry(conversion->ConversionParamType(), conversion->ConversionArgType());
        conversionMap[entry] = conversion;
    }
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