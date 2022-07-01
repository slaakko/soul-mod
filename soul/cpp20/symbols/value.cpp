// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.value;

import util.unicode;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.reader;

namespace soul::cpp20::symbols {

Value::Value(SymbolKind symbolKind_, const std::u32string& rep_) : Symbol(symbolKind_, rep_)
{
}

ValueKind Value::GetValueKind() const
{
    switch (Kind())
    {
        case SymbolKind::boolValueSymbol:
        {
            return ValueKind::boolValue;
        }
        case SymbolKind::integerValueSymbol:
        {
            return ValueKind::integerValue;
        }
        case SymbolKind::floatingValueSymbol:
        {
            return ValueKind::floatingValue;
        }
    }
    return ValueKind::none;
}

BoolValue::BoolValue() : Value(SymbolKind::boolValueSymbol, std::u32string(U"false")), value(false)
{
}

BoolValue::BoolValue(const std::u32string& rep_) : Value(SymbolKind::boolValueSymbol, rep_), value(false)
{
}

BoolValue::BoolValue(bool value_, const std::u32string& rep_) : Value(SymbolKind::boolValueSymbol, rep_), value(value_)
{
}

Value* BoolValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::boolValue: return this;
        case ValueKind::integerValue: return context.GetIntegerValue(static_cast<int64_t>(value), util::ToUtf32(std::to_string(value)));
        case ValueKind::floatingValue: return context.GetFloatingValue(static_cast<double>(value), util::ToUtf32(std::to_string(value)));
    }
    return this;
}

void BoolValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(value);
}

void BoolValue::Read(Reader& reader)
{
    Value::Read(reader);
    value = reader.GetBinaryStreamReader().ReadBool();
}

IntegerValue::IntegerValue() : Value(SymbolKind::integerValueSymbol, std::u32string(U"0")), value(0)
{
}

IntegerValue::IntegerValue(const std::u32string& rep_) : Value(SymbolKind::integerValueSymbol, rep_), value(0)
{
}

IntegerValue::IntegerValue(int64_t value_, const std::u32string& rep_) : Value(SymbolKind::integerValueSymbol, rep_), value(value_)
{
}

BoolValue* IntegerValue::ToBoolValue(EvaluationContext& context)
{
    if (value) return context.GetBoolValue(true); else return context.GetBoolValue(false);
}

Value* IntegerValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::boolValue: return ToBoolValue(context);
        case ValueKind::integerValue: return this;
        case ValueKind::floatingValue: return context.GetFloatingValue(static_cast<double>(value), util::ToUtf32(std::to_string(value)));
    }
    return this;
}

void IntegerValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(value);
}

void IntegerValue::Read(Reader& reader)
{
    Value::Read(reader);
    value = reader.GetBinaryStreamReader().ReadLong();
}

FloatingValue::FloatingValue() : Value(SymbolKind::floatingValueSymbol, std::u32string(U"0.0")), value(0.0)
{
}

FloatingValue::FloatingValue(const std::u32string& rep_) : Value(SymbolKind::floatingValueSymbol, rep_), value(0.0)
{
}

FloatingValue::FloatingValue(double value_, const std::u32string& rep_) : Value(SymbolKind::floatingValueSymbol, rep_), value(value_)
{
}

BoolValue* FloatingValue::ToBoolValue(EvaluationContext& context)
{
    if (value) return context.GetBoolValue(true); else return context.GetBoolValue(false);
}

Value* FloatingValue::Convert(ValueKind kind, EvaluationContext& context) 
{
    switch (kind)
    {
        case ValueKind::boolValue: return ToBoolValue(context);
        case ValueKind::integerValue: return context.GetIntegerValue(static_cast<int64_t>(value), util::ToUtf32(std::to_string(value)));
        case ValueKind::floatingValue: return this;
    }
    return this;
}

void FloatingValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(value);
}

void FloatingValue::Read(Reader& reader)
{
    Value::Read(reader);
    value = reader.GetBinaryStreamReader().ReadDouble();
}

EvaluationContext::EvaluationContext() : trueValue(true, U"true"), falseValue(false, U"false")
{
}

void EvaluationContext::Init()
{
    integerValueMap.clear();
    floatingValueMap.clear();
    values.clear();
}

EvaluationContext& EvaluationContext::Instance()
{
    static EvaluationContext instance;
    return instance;
}

BoolValue* EvaluationContext::GetBoolValue(bool value)
{
    if (value) return &trueValue; else return &falseValue;
}

IntegerValue* EvaluationContext::GetIntegerValue(int64_t value, const std::u32string& rep)
{
    auto it = integerValueMap.find(std::make_pair(value, rep));
    if (it != integerValueMap.cend())
    {
        return it->second;
    }
    else
    {
        IntegerValue* integerValue = new IntegerValue(value, rep);
        integerValueMap[std::make_pair(value, rep)] = integerValue;
        values.push_back(std::unique_ptr<Value>(integerValue));
        return integerValue;
    }
}

FloatingValue* EvaluationContext::GetFloatingValue(double value, const std::u32string& rep)
{
    auto it = floatingValueMap.find(std::make_pair(value, rep));
    if (it != floatingValueMap.cend())
    {
        return it->second;
    }
    else
    {
        FloatingValue* floatingValue = new FloatingValue(value, rep);
        floatingValueMap[std::make_pair(value, rep)] = floatingValue;
        values.push_back(std::unique_ptr<Value>(floatingValue));
        return floatingValue;
    }
}

void EvaluationContext::Write(Writer& writer)
{
    uint32_t count = values.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (uint32_t i = 0; i < count; ++i)
    {
        Symbol* value = values[i].get();
        writer.Write(value);
    }
}

void EvaluationContext::Read(Reader& reader)
{
    uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < count; ++i)
    {
        Symbol* symbol = reader.ReadSymbol();
        if (symbol->IsIntegerValueSymbol())
        {
            IntegerValue* integerValue = static_cast<IntegerValue*>(symbol);
            integerValueMap[std::make_pair(integerValue->GetValue(), integerValue->Rep())] = integerValue;
        }
        else if (symbol->IsFloatingValueSymbol())
        {
            FloatingValue* floatingValue = static_cast<FloatingValue*>(symbol);
            floatingValueMap[std::make_pair(floatingValue->GetValue(), floatingValue->Rep())] = floatingValue;
        }
    }
}

EvaluationContext& GetEvaluationContext()
{
    return EvaluationContext::Instance();
}

} // namespace soul::cpp20::symbols
