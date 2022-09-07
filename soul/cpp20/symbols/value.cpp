// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module soul.cpp20.symbols.value;

import util.unicode;
import soul.cpp20.symbols.enums;
import soul.cpp20.symbols.modules;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.visitor;
import soul.cpp20.ast.error;

namespace soul::cpp20::symbols {

ValueKind CommonValueKind(ValueKind left, ValueKind right) 
{
    switch (left)
    {
        case ValueKind::boolValue:
        {
            return ValueKind::boolValue;
        }
        case ValueKind::integerValue:
        {
            switch (right)
            {
                case ValueKind::integerValue:
                {
                    return ValueKind::integerValue;
                }
                case ValueKind::floatingValue:
                {
                    return ValueKind::floatingValue;
                }
                case ValueKind::boolValue:
                {
                    return ValueKind::boolValue;
                }
                case ValueKind::symbolValue:
                {
                    return ValueKind::integerValue;
                }
                default:
                {
                    return ValueKind::none;
                }
            }
            break;
        }
        case ValueKind::floatingValue:
        {
            switch (right)
            {
                case ValueKind::integerValue:
                case ValueKind::floatingValue:
                {
                    return ValueKind::floatingValue;
                }
                case ValueKind::boolValue:
                {
                    return ValueKind::boolValue;
                }
                default:
                {
                    return ValueKind::none;
                }
            }
        }
        case ValueKind::symbolValue:
        {
            switch (right)
            {
                case ValueKind::integerValue:
                {
                    return ValueKind::integerValue;
                }
                case ValueKind::symbolValue:
                {
                    return ValueKind::integerValue;
                }
                default:
                {
                    return ValueKind::none;
                }
            }
        }
    }
    return ValueKind::none;
}

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
        case SymbolKind::nullPtrValueSymbol:
        {
            return ValueKind::nullPtrValue;
        }
        case SymbolKind::symbolValueSymbol:
        {
            return ValueKind::symbolValue;
        }
        case SymbolKind::invokeValueSymbol:
        {
            return ValueKind::invokeValue;
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

void BoolValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
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

void IntegerValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
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

void FloatingValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NullPtrValue::NullPtrValue() : Value(SymbolKind::nullPtrValueSymbol, U"nullptr")
{
}

BoolValue* NullPtrValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

Value* NullPtrValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::boolValue: return ToBoolValue(context);
    }
    return this;
}

void NullPtrValue::Write(Writer& writer)
{
    Value::Write(writer);
}

void NullPtrValue::Read(Reader& reader)
{
    Value::Read(reader);
}

void NullPtrValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SymbolValue::SymbolValue() : Value(SymbolKind::symbolValueSymbol, std::u32string()), symbol(nullptr)
{
}

SymbolValue::SymbolValue(Symbol* symbol_) : Value(SymbolKind::symbolValueSymbol, std::u32string()), symbol(symbol_)
{
}

Value* SymbolValue::Convert(ValueKind kind, EvaluationContext& context)
{
    switch (kind)
    {
        case ValueKind::integerValue: 
        {
            switch (symbol->Kind())
            {
                case SymbolKind::enumConstantSymbol:
                {
                    EnumConstantSymbol* enumConstantSymbol = static_cast<EnumConstantSymbol*>(symbol);
                    Value* value = enumConstantSymbol->GetValue();
                    switch (value->GetValueKind())
                    {
                        case ValueKind::integerValue:
                        {
                            IntegerValue* integerValue = static_cast<IntegerValue*>(value);
                            return context.GetIntegerValue(integerValue->GetValue(), enumConstantSymbol->Name());
                        }
                        case ValueKind::boolValue:
                        {
                            BoolValue* boolValue = static_cast<BoolValue*>(value);
                            return context.GetIntegerValue(static_cast<int64_t>(boolValue->GetValue()), enumConstantSymbol->Name());
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
    return this;
}

BoolValue* SymbolValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

void SymbolValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(symbol->Id());
}

void SymbolValue::Read(Reader& reader)
{
    Value::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(symbolId);
}

void SymbolValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void SymbolValue::Resolve(SymbolTable& symbolTable)
{
    Value::Resolve(symbolTable);
    symbol = soul::cpp20::symbols::GetSymbol(symbolId);
}

std::u32string SymbolValue::ToString() const
{
    return symbol->Name();
}

InvokeValue::InvokeValue() : Value(SymbolKind::invokeValueSymbol, std::u32string()), subject(nullptr)
{
}

InvokeValue::InvokeValue(Value* subject_) : Value(SymbolKind::invokeValueSymbol, std::u32string()), subject(subject_)
{
}

Value* InvokeValue::Convert(ValueKind kind, EvaluationContext& context)
{
    return this;
}

BoolValue* InvokeValue::ToBoolValue(EvaluationContext& context)
{
    return context.GetBoolValue(false);
}

void InvokeValue::Write(Writer& writer)
{
    Value::Write(writer);
    writer.GetBinaryStreamWriter().Write(subject->Id());
}

void InvokeValue::Read(Reader& reader)
{
    Value::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(subjectId);
}

void InvokeValue::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void InvokeValue::Resolve(SymbolTable& symbolTable)
{
    Value::Resolve(symbolTable);
    EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
    subject = evaluationContext->GetValue(subjectId);
}

std::u32string InvokeValue::ToString() const
{
    return subject->ToString() + U"()";
}

EvaluationContext::EvaluationContext() : trueValue(true, U"true"), falseValue(false, U"false"), nullPtrValue()
{
    MapValue(&nullPtrValue);
    MapValue(&trueValue);
    MapValue(&falseValue);
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
        MapValue(integerValue);
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
        MapValue(floatingValue);
        return floatingValue;
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

void EvaluationContext::Write(Writer& writer)
{
    trueValue.Write(writer);
    falseValue.Write(writer);
    nullPtrValue.Write(writer);
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
    trueValue.Read(reader);
    falseValue.Read(reader);
    nullPtrValue.Read(reader);
    MapValue(&nullPtrValue);
    MapValue(&trueValue);
    MapValue(&falseValue);
    uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < count; ++i)
    {
        Symbol* symbol = reader.ReadSymbol();
        if (symbol->IsValueSymbol())
        {
            Value* value = static_cast<Value*>(symbol);
            values.push_back(std::unique_ptr<Value>(value));
            MapValue(value);
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
        else
        {
            soul::cpp20::ast::SetExceptionThrown();
            throw std::runtime_error("soul.cpp20.symbols.value: value symbol expected");
        }
    }
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

void EvaluationContext::Resolve(SymbolTable& symbolTable)
{
    for (const auto& value : values)
    {
        value->Resolve(symbolTable);
    }
}

} // namespace soul::cpp20::symbols
