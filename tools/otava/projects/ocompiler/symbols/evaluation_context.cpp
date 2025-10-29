// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.evaluation_context;

namespace otava::symbols {

EvaluationContext::EvaluationContext(SymbolTable& symbolTable_) :
    initialized(false),
    symbolTable(symbolTable_),
    trueValue(true, U"true", nullptr),
    falseValue(false, U"false", nullptr),
    nullPtrValue(nullptr)
{
    MapValue(&nullPtrValue);
    MapValue(&trueValue);
    MapValue(&falseValue);
}

void EvaluationContext::Init()
{
    if (initialized) return;
    initialized = true;
    trueValue.SetType(symbolTable.GetFundamentalType(FundamentalTypeKind::boolType));
    falseValue.SetType(symbolTable.GetFundamentalType(FundamentalTypeKind::boolType));
    nullPtrValue.SetType(symbolTable.GetFundamentalType(FundamentalTypeKind::nullPtrType));
}

BoolValue* EvaluationContext::GetBoolValue(bool value)
{
    if (value) return &trueValue; else return &falseValue;
}

IntegerValue* EvaluationContext::GetIntegerValue(std::int64_t value, const std::u32string& rep, TypeSymbol* type)
{
    auto it = integerValueMap.find(std::make_pair(std::make_pair(value, rep), type));
    if (it != integerValueMap.cend())
    {
        return it->second;
    }
    else
    {
        IntegerValue* integerValue = new IntegerValue(value, rep, type);
        integerValueMap[std::make_pair(std::make_pair(value, rep), type)] = integerValue;
        values.push_back(std::unique_ptr<Value>(integerValue));
        MapValue(integerValue);
        return integerValue;
    }
}

FloatingValue* EvaluationContext::GetFloatingValue(double value, const std::u32string& rep, TypeSymbol* type)
{
    auto it = floatingValueMap.find(std::make_pair(std::make_pair(value, rep), type));
    if (it != floatingValueMap.cend())
    {
        return it->second;
    }
    else
    {
        FloatingValue* floatingValue = new FloatingValue(value, rep, type);
        floatingValueMap[std::make_pair(std::make_pair(value, rep), type)] = floatingValue;
        values.push_back(std::unique_ptr<Value>(floatingValue));
        MapValue(floatingValue);
        return floatingValue;
    }
}

StringValue* EvaluationContext::GetStringValue(const std::string& value, TypeSymbol* type)
{
    auto it = stringValueMap.find(std::make_pair(value, type));
    if (it != stringValueMap.cend())
    {
        return it->second;
    }
    else
    {
        StringValue* stringValue = new StringValue(value, type);
        stringValueMap[std::make_pair(value, type)] = stringValue;
        values.push_back(std::unique_ptr<Value>(stringValue));
        MapValue(stringValue);
        return stringValue;
    }
}

CharValue* EvaluationContext::GetCharValue(char32_t value, TypeSymbol* type)
{
    auto it = charValueMap.find(std::make_pair(value, type));
    if (it != charValueMap.cend())
    {
        return it->second;
    }
    else
    {
        CharValue* charValue = new CharValue(value, type);
        charValueMap[std::make_pair(value, type)] = charValue;
        values.push_back(std::unique_ptr<Value>(charValue));
        MapValue(charValue);
        return charValue;
    }
}

SymbolValue* EvaluationContext::GetSymbolValue(Symbol* symbol)
{
    auto it = symbolValueMap.find(symbol);
    if (it != symbolValueMap.cend())
    {
        return it->second;
    }
    else
    {
        SymbolValue* symbolValue = new SymbolValue(symbol);
        symbolValueMap[symbol] = symbolValue;
        values.push_back(std::unique_ptr<Value>(symbolValue));
        MapValue(symbolValue);
        return symbolValue;
    }
}

InvokeValue* EvaluationContext::GetInvokeValue(Value* subject)
{
    auto it = invokeMap.find(subject);
    if (it != invokeMap.cend())
    {
        return it->second;
    }
    else
    {
        InvokeValue* invokeValue = new InvokeValue(subject);
        invokeMap[subject] = invokeValue;
        values.push_back(std::unique_ptr<Value>(invokeValue));
        MapValue(invokeValue);
        return invokeValue;
    }
}

ArrayValue* EvaluationContext::GetArrayValue(TypeSymbol* type)
{
    ArrayValue* arrayValue = new ArrayValue(type);
    values.push_back(std::unique_ptr<Value>(arrayValue));
    return arrayValue;
}

StructureValue* EvaluationContext::GetStructureValue(TypeSymbol* type)
{
    StructureValue* structureValue = new StructureValue(type);
    values.push_back(std::unique_ptr<Value>(structureValue));
    return structureValue;
}

void EvaluationContext::AddValue(Value* value)
{
    values.push_back(std::unique_ptr<Value>(value));
}

std::expected<bool, int> EvaluationContext::Write(Writer& writer, Context* context)
{
    std::expected<bool, int> rv = trueValue.Write(writer);
    if (!rv) return rv;
    rv = falseValue.Write(writer);
    if (!rv) return rv;
    rv = nullPtrValue.Write(writer);
    if (!rv) return rv;
    std::vector<Symbol*> exportValues;
    for (const auto& value : values)
    {
        if (value->IsExportSymbol(context))
        {
            exportValues.push_back(value.get());
        }
    }
    std::uint32_t count = exportValues.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    if (!rv) return rv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(count); ++i)
    {
        Symbol* value = exportValues[i];
        rv = writer.Write(value);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EvaluationContext::Read(Reader& reader)
{
    readingEvaluationContext = true;
    std::expected<bool, int> rv = trueValue.Read(reader);
    if (!rv) return rv;
    rv = falseValue.Read(reader);
    if (!rv) return rv;
    rv = nullPtrValue.Read(reader);
    if (!rv) return rv;
    MapValue(&nullPtrValue);
    MapValue(&trueValue);
    MapValue(&falseValue);
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t count = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(count); ++i)
    {
        std::expected<Symbol*, int> s = reader.ReadSymbol();
        if (!s) return std::unexpected<int>(s.error());
        Symbol* symbol = *s;
        if (symbol->IsValueSymbol())
        {
            Value* value = static_cast<Value*>(symbol);
            values.push_back(std::unique_ptr<Value>(value));
            MapValue(value);
            if (symbol->IsIntegerValueSymbol())
            {
                IntegerValue* integerValue = static_cast<IntegerValue*>(symbol);
                integerValueMap[std::make_pair(std::make_pair(integerValue->GetValue(), integerValue->Rep()), integerValue->GetType())] = integerValue;
            }
            else if (symbol->IsFloatingValueSymbol())
            {
                FloatingValue* floatingValue = static_cast<FloatingValue*>(symbol);
                floatingValueMap[std::make_pair(std::make_pair(floatingValue->GetValue(), floatingValue->Rep()), floatingValue->GetType())] = floatingValue;
            }
            else if (symbol->IsStringValueSymbol())
            {
                StringValue* stringValue = static_cast<StringValue*>(symbol);
                stringValueMap[std::make_pair(stringValue->GetValue(), stringValue->GetType())] = stringValue;
            }
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("otava.symbols.value: value symbol expected"));
        }
    }
    readingEvaluationContext = false;
    return std::expected<bool, int>(true);
}

Value* EvaluationContext::GetValue(const util::uuid& valueId) const
{
    auto it = valueMap.find(valueId);
    if (it != valueMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void EvaluationContext::MapValue(Value* value)
{
    valueMap[value->Id()] = value;
}

std::expected<bool, int> EvaluationContext::Resolve(SymbolTable& symbolTable, Context* context)
{
    for (const auto& value : values)
    {
        std::expected<bool, int> rv = value->Resolve(symbolTable, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
