// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.value;

import std;
import soul.ast.source.pos;

export namespace otava::intermediate {

using SourcePos = soul::ast::SourcePos;

class Type;
class Visitor;

enum class ValueKind
{
    boolValue, sbyteValue, byteValue, shortValue, ushortValue, intValue, uintValue, longValue, ulongValue, floatValue, doubleValue, nullValue, addressValue,
    arrayValue, structureValue, stringValue, stringArrayValue, conversionValue, clsIdValue, symbolValue,
    globalVariable,
    regValue,
    instruction,
    function
};

class Value
{
public:
    Value(const SourcePos& sourcePos_, ValueKind kind_, Type* type_);
    virtual ~Value();
    bool IsRegValue() const { return kind == ValueKind::regValue; }
    bool IsInstruction() const { return kind == ValueKind::instruction; }
    bool IsSymbolValue() const { return kind == ValueKind::symbolValue; }
    bool IsAddressValue() const { return kind == ValueKind::addressValue; }
    bool IsGlobalVariable() const { return kind == ValueKind::globalVariable; }
    bool IsIntegerValue() const;
    bool IsAggregateValue() const { return kind == ValueKind::arrayValue || kind == ValueKind::structureValue; }
    bool IsArrayValue() const { return kind == ValueKind::arrayValue; }
    bool IsStringValue() const { return kind == ValueKind::stringValue; }
    bool IsLongValue() const { return kind == ValueKind::longValue; }
    std::int64_t GetIntegerValue() const;
    const SourcePos& GetSourcePos() const { return sourcePos; }
    ValueKind Kind() const { return kind; }
    std::string KindStr() const;
    Type* GetType() const { return type; }
    virtual void SetType(Type* type_);
    virtual std::string ToString() const { return std::string(); }
    virtual void Accept(Visitor& visitor) {}
private:
    SourcePos sourcePos;
    ValueKind kind;
    Type* type;
};

} // namespace value
