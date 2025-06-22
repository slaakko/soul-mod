// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.value;

import std.core;
import otava.intermediate.data;

namespace otava::intermediate {

const char* valueKindStr[]
{
    "boolValue", "sbyteValue", "byteValue", "shortValue", "ushortValue", "intValue", "uintValue", "longValue", "ulongValue", "floatValue", "doubleValue", "nullValue",
    "addressValue",
    "arrayValue", "structureValue", "stringValue", "stringArrayValue", "conversionValue", "clsIdValue", "symbolValue",
    "globalVariable",
    "regValue",
    "instruction"
};

Value::Value(const SourcePos& sourcePos_, ValueKind kind_, Type* type_) : sourcePos(sourcePos_), kind(kind_), type(type_)
{
}

Value::~Value()
{
}

bool Value::IsIntegerValue() const
{
    switch (kind)
    {
    case ValueKind::sbyteValue:
    case ValueKind::byteValue:
    case ValueKind::shortValue:
    case ValueKind::ushortValue:
    case ValueKind::intValue:
    case ValueKind::uintValue:
    case ValueKind::longValue:
    case ValueKind::ulongValue:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }
}

std::int64_t Value::GetIntegerValue() const
{
    switch (kind)
    {
    case ValueKind::sbyteValue:
    {
        const SByteValue* sbyteValue = static_cast<const SByteValue*>(this);
        return sbyteValue->GetValue();
    }
    case ValueKind::byteValue:
    {
        const ByteValue* byteValue = static_cast<const ByteValue*>(this);
        return byteValue->GetValue();
    }
    case ValueKind::shortValue:
    {
        const ShortValue* shortValue = static_cast<const ShortValue*>(this);
        return shortValue->GetValue();
    }
    case ValueKind::ushortValue:
    {
        const UShortValue* ushortValue = static_cast<const UShortValue*>(this);
        return ushortValue->GetValue();
    }
    case ValueKind::intValue:
    {
        const IntValue* intValue = static_cast<const IntValue*>(this);
        return intValue->GetValue();
    }
    case ValueKind::uintValue:
    {
        const UIntValue* uintValue = static_cast<const UIntValue*>(this);
        return uintValue->GetValue();
    }
    case ValueKind::longValue:
    {
        const LongValue* longValue = static_cast<const LongValue*>(this);
        return longValue->GetValue();
    }
    case ValueKind::ulongValue:
    {
        const ULongValue* ulongValue = static_cast<const ULongValue*>(this);
        return static_cast<std::int64_t>(ulongValue->GetValue());
    }
    default:
    {
        return -1;
    }
    }
}

void Value::SetType(Type* type_)
{
    if (!type)
    {
        type = type_;
    }
}

std::string Value::KindStr() const
{
    return valueKindStr[static_cast<int>(kind)];
}

} // namespace otava::intermediate
