// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.data;

import otava.intermediate.value;
import util.code.formatter;
import std;

export namespace otava::intermediate::data {}

export namespace otava::intermediate {

class Context;
class Data;
class Function;
class GlobalVariable;
class Type;
class Types;

class BoolValue : public Value
{
public:
    BoolValue(bool value_, Type* type_);
    bool GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    bool value;
};

class SByteValue : public Value
{
public:
    SByteValue(std::int8_t value_, Type* type_);
    std::int8_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::int8_t value;
};

class ByteValue : public Value
{
public:
    ByteValue(std::uint8_t value_, Type* type_);
    std::uint8_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::uint8_t value;
};

class ShortValue : public Value
{
public:
    ShortValue(std::int16_t value_, Type* type_);
    std::int16_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::int16_t value;
};

class UShortValue : public Value
{
public:
    UShortValue(std::uint16_t value_, Type* type_);
    std::uint16_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::uint16_t value;
};

class IntValue : public Value
{
public:
    IntValue(std::int32_t value_, Type* type_);
    std::int32_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::int32_t value;
};

class UIntValue : public Value
{
public:
    UIntValue(std::uint32_t value_, Type* type_);
    std::uint32_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::uint32_t value;
};

class LongValue : public Value
{
public:
    LongValue(std::int64_t value_, Type* type_);
    std::int64_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::int64_t value;
};

class ULongValue : public Value
{
public:
    ULongValue(std::uint64_t value_, Type* type_);
    std::uint64_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::uint64_t value;
};

class FloatValue : public Value
{
public:
    FloatValue(float value_, Type* type_);
    float GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    float value;
};

class DoubleValue : public Value
{
public:
    DoubleValue(double value_, Type* type_);
    double GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    double value;
};

class NullValue : public Value
{
public:
    NullValue(Type* type_);
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
};

class AddressValue : public Value
{
public:
    AddressValue(const SourcePos& sourcePos_, GlobalVariable* globalVariable_, Type* type);
    GlobalVariable* GetValue() const { return globalVariable; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    GlobalVariable* globalVariable;
};

class ArrayValue : public Value
{
public:
    ArrayValue(const SourcePos& sourcePos_, const std::vector<Value*>& elements_);
    const std::vector<Value*>& Elements() const { return elements; }
    void SetType(Type* type) override;
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::vector<Value*> elements;
};

class StructureValue : public Value
{
public:
    StructureValue(const SourcePos& sourcePos_, const std::vector<Value*>& fieldValues_);
    const std::vector<Value*>& FieldValues() const { return fieldValues; }
    void SetType(Type* type) override;
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::vector<Value*> fieldValues;
};

class StringValue : public Value
{
public:
    StringValue(const SourcePos& sourcePos_, const std::string& value_);
    const std::string& GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::string value;
};

class StringArrayValue : public Value
{
public:
    StringArrayValue(const SourcePos& sourcePos_, char prefix_, const std::vector<Value*>& strings_);
    char Prefix() const { return prefix; }
    const std::vector<Value*>& Strings() const { return strings; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    char prefix;
    std::vector<Value*> strings;
};

class ConversionValue : public Value
{
public:
    ConversionValue(const SourcePos& sourcePos_, Type* type_, Value* from_);
    Value* From() const { return from; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    Value* from;
};

class ClsIdValue : public Value
{
public:
    ClsIdValue(const SourcePos& sourcePos_, Type* type_, const std::string& typeId_);
    const std::string& TypeId() const { return typeId; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::string typeId;
};

class SymbolValue : public Value
{
public:
    SymbolValue(const SourcePos& sourcePos_, Type* type_, const std::string& symbol_);
    const std::string& Symbol() const { return symbol; }
    Function* GetFunction() const { return function; }
    void SetFunction(Function* function_) { function = function_; }
    GlobalVariable* GetGlobalVariable() const { return globalVariable; }
    void SetGlobalVariable(GlobalVariable* globalVariable_) { globalVariable = globalVariable_; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::string symbol;
    Function* function;
    GlobalVariable* globalVariable;
};

class GlobalVariable : public Value
{
public:
    GlobalVariable(const SourcePos& sourcePos_, Type* type_, Type* globalType_, const std::string& name_, Value* initializer_, bool once_);
    void Write(util::CodeFormatter& formatter);
    virtual void Accept(Visitor& visitor);
    const std::string& Name() const { return name; }
    Value* Initializer() const { return initializer; }
    bool Once() const { return once; }
    std::string ToString() const override { return name; }
    Type* GlobalType() const { return globalType; }
private:
    Type* globalType;
    std::string name;
    Value* initializer;
    bool once;
};

template<class T>
class ValueMap
{
public:
    ValueMap();
    Value* Get(const T& value, Data* data, const Types& types);
private:
    std::map<T, Value*> valueMap;
};

class Data
{
public:
    Data();
    void Write(util::CodeFormatter& formatter);
    Context* GetContext() const { return context; }
    void SetContext(Context* context_) { context = context_; }
    GlobalVariable* AddGlobalVariable(const SourcePos& sourcePos, Type* type, Type* globalType, const std::string& variableName, Value* initializer, bool once, Context* context);
    GlobalVariable* GetGlobalVariableForString(Value* stringValue);
    Value* GetTrueValue(const Types& types);
    Value* GetFalseValue(const Types& types);
    Value* GetSByteValue(std::int8_t value, const Types& types);
    Value* GetByteValue(std::uint8_t value, const Types& types);
    Value* GetShortValue(std::int16_t value, const Types& types);
    Value* GetUShortValue(std::uint16_t value, const Types& types);
    Value* GetIntValue(std::int32_t value, const Types& types);
    Value* GetUIntValue(std::uint32_t value, const Types& types);
    Value* GetLongValue(std::int64_t value, const Types& types);
    Value* GetULongValue(std::uint64_t value, const Types& types);
    Value* GetIntegerValue(Type* type, std::int64_t value, const Types& types);
    Value* GetFloatValue(float value, const Types& types);
    Value* GetDoubleValue(double value, const Types& types);
    Value* GetFloatingValue(Type* type, double value, const Types& types);
    Value* GetNullValue(Type* type);
    Value* MakeValue(std::int8_t value, const Types& types);
    Value* MakeValue(std::uint8_t value, const Types& types);
    Value* MakeValue(std::int16_t value, const Types& types);
    Value* MakeValue(std::uint16_t value, const Types& types);
    Value* MakeValue(std::int32_t value, const Types& types);
    Value* MakeValue(std::uint32_t value, const Types& types);
    Value* MakeValue(std::int64_t value, const Types& types);
    Value* MakeValue(std::uint64_t value, const Types& types);
    Value* MakeValue(float value, const Types& types);
    Value* MakeValue(double value, const Types& types);
    Value* MakeArrayValue(const SourcePos& sourcePos, const std::vector<Value*>& elements);
    Value* MakeStructureValue(const SourcePos& sourcePos, const std::vector<Value*>& fieldValues);
    Value* MakeStringValue(const SourcePos& sourcePos, const std::string& value);
    Value* MakeStringArrayValue(const SourcePos& sourcePos, char prefix, const std::vector<Value*>& strings);
    Value* MakeConversionValue(const SourcePos& sourcePos, Type* type, Value* from);
    Value* MakeClsIdValue(const SourcePos& sourcePos, Type* type, const std::string& clsIdStr);
    Value* MakeSymbolValue(const SourcePos& sourcePos, Type* type, const std::string& symbol);
    Value* MakeNumericLiteral(const SourcePos& sourcePos, Type* type, const std::string& strValue, const Types& types, Context* context);
    Value* MakeAddressLiteral(const SourcePos& sourcePos, Type* type, const std::string& id, Context* context);
    void VisitGlobalVariables(Visitor& visitor);
    std::string GetNextStringValueId();
private:
    Context* context;
    std::vector<std::unique_ptr<Value>> values;
    std::vector<GlobalVariable*> globalVariables;
    std::map<std::string, GlobalVariable*> globalVariableMap;
    std::map<Value*, GlobalVariable*> globalStringVariableMap;
    std::unique_ptr<BoolValue> trueValue;
    std::unique_ptr<BoolValue> falseValue;
    ValueMap<std::int8_t> sbyteValueMap;
    ValueMap<std::uint8_t> byteValueMap;
    ValueMap<std::int16_t> shortValueMap;
    ValueMap<std::uint16_t> ushortValueMap;
    ValueMap<std::int32_t> intValueMap;
    ValueMap<std::uint32_t> uintValueMap;
    ValueMap<std::int64_t> longValueMap;
    ValueMap<std::uint64_t> ulongValueMap;
    ValueMap<float> floatValueMap;
    ValueMap<double> doubleValueMap;
    std::map<Type*, NullValue*> nullValueMap;
    std::map<std::string, StringValue*> stringValueMap;
    std::int32_t nextStringValueId;
};

template<class T>
ValueMap<T>::ValueMap()
{
}

template<class T>
Value* ValueMap<T>::Get(const T& value, Data* data, const Types& types)
{
    auto it = valueMap.find(value);
    if (it != valueMap.cend())
    {
        return it->second;
    }
    else
    {
        Value* constantValue = data->MakeValue(value, types);
        valueMap[value] = constantValue;
        return constantValue;
    }
}

} // otava::intermediate
