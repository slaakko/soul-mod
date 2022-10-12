// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.data;

import otava.intermediate.value;
import util.code.formatter;
import std.core;

export namespace otava::intermediate::data {}

export namespace otava::intermediate {

class Context;
class Data;
class Function;
class GlobalVariable;
class Type;
class Types;

class BoolValue : public ConstantValue
{
public:
    BoolValue(bool value_, Type* type_);
    bool GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    bool value;
};

class SByteValue : public ConstantValue
{
public:
    SByteValue(int8_t value_, Type* type_);
    int8_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    int8_t value;
};

class ByteValue : public ConstantValue
{
public:
    ByteValue(uint8_t value_, Type* type_);
    uint8_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    uint8_t value;
};

class ShortValue : public ConstantValue
{
public:
    ShortValue(int16_t value_, Type* type_);
    int16_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    int16_t value;
};

class UShortValue : public ConstantValue
{
public:
    UShortValue(uint16_t value_, Type* type_);
    uint16_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    uint16_t value;
};

class IntValue : public ConstantValue
{
public:
    IntValue(int32_t value_, Type* type_);
    int32_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    int32_t value;
};

class UIntValue : public ConstantValue
{
public:
    UIntValue(uint32_t value_, Type* type_);
    uint32_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    uint32_t value;
};

class LongValue : public ConstantValue
{
public:
    LongValue(int64_t value_, Type* type_);
    int64_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    int64_t value;
};

class ULongValue : public ConstantValue
{
public:
    ULongValue(uint64_t value_, Type* type_);
    uint64_t GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    uint64_t value;
};

class FloatValue : public ConstantValue
{
public:
    FloatValue(float value_, Type* type_);
    float GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    float value;
};

class DoubleValue : public ConstantValue
{
public:
    DoubleValue(double value_, Type* type_);
    double GetValue() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    double value;
};

class NullValue : public ConstantValue
{
public:
    NullValue(Type* type_);
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
};

class AddressValue : public ConstantValue
{
public:
    AddressValue(const SourcePos& sourcePos_, GlobalVariable* globalVariable_, Type* type);
    GlobalVariable* Value() const { return globalVariable; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    GlobalVariable* globalVariable;
};

class ArrayValue : public ConstantValue
{
public:
    ArrayValue(const SourcePos& sourcePos_, const std::vector<ConstantValue*>& elements_);
    const std::vector<ConstantValue*>& Elements() const { return elements; }
    void SetType(Type* type) override;
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::vector<ConstantValue*> elements;
};

class StructureValue : public ConstantValue
{
public:
    StructureValue(const SourcePos& sourcePos_, const std::vector<ConstantValue*>& fieldValues_);
    const std::vector<ConstantValue*>& FieldValues() const { return fieldValues; }
    void SetType(Type* type) override;
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::vector<ConstantValue*> fieldValues;
};

class StringValue : public ConstantValue
{
public:
    StringValue(const SourcePos& sourcePos_, const std::string& value_);
    const std::string& Value() const { return value; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::string value;
};

class StringArrayValue : public ConstantValue
{
public:
    StringArrayValue(const SourcePos& sourcePos_, char prefix_, const std::vector<ConstantValue*>& strings_);
    char Prefix() const { return prefix; }
    const std::vector<ConstantValue*>& Strings() const { return strings; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    char prefix;
    std::vector<ConstantValue*> strings;
};

class ConversionValue : public ConstantValue
{
public:
    ConversionValue(const SourcePos& sourcePos_, Type* type_, ConstantValue* from_);
    ConstantValue* From() const { return from; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    ConstantValue* from;
};

class ClsIdValue : public ConstantValue
{
public:
    ClsIdValue(const SourcePos& sourcePos_, Type* type_, const std::string& typeId_);
    const std::string& TypeId() const { return typeId; }
    void Accept(Visitor& visitor) override;
    std::string ToString() const override;
private:
    std::string typeId;
};

class SymbolValue : public ConstantValue
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
    GlobalVariable(const SourcePos& sourcePos_, Type* type_, const std::string& name_, ConstantValue* initializer_, bool once_);
    void Write(util::CodeFormatter& formatter);
    virtual void Accept(Visitor& visitor);
    const std::string& Name() const { return name; }
    ConstantValue* Initializer() const { return initializer; }
    bool Once() const { return once; }
    std::string ToString() const override { return name; }
private:
    std::string name;
    ConstantValue* initializer;
    bool once;
};

template<class T>
class ConstantValueMap
{
public:
    ConstantValueMap();
    ConstantValue* Get(const T& value, Data* data, const Types& types);
private:
    std::map<T, ConstantValue*> valueMap;
};

class Data
{
public:
    Data();
    void Write(util::CodeFormatter& formatter);
    Context* GetContext() const { return context; }
    void SetContext(Context* context_) { context = context_; }
    void AddGlobalVariable(const SourcePos& sourcePos, Type* type, const std::string& variableName, ConstantValue* initializer, bool once, Context* context);
    ConstantValue* GetTrueValue(const Types& types);
    ConstantValue* GetFalseValue(const Types& types);
    ConstantValue* GetSByteValue(int8_t value, const Types& types);
    ConstantValue* GetByteValue(uint8_t value, const Types& types);
    ConstantValue* GetShortValue(int16_t value, const Types& types);
    ConstantValue* GetUShortValue(uint16_t value, const Types& types);
    ConstantValue* GetIntValue(int32_t value, const Types& types);
    ConstantValue* GetUIntValue(uint32_t value, const Types& types);
    ConstantValue* GetLongValue(int64_t value, const Types& types);
    ConstantValue* GetULongValue(uint64_t value, const Types& types);
    ConstantValue* GetIntegerValue(Type* type, int64_t value, const Types& types);
    ConstantValue* GetFloatValue(float value, const Types& types);
    ConstantValue* GetDoubleValue(double value, const Types& types);
    ConstantValue* GetFloatingValue(Type* type, double value, const Types& types);
    ConstantValue* GetNullValue(Type* type);
    ConstantValue* MakeValue(int8_t value, const Types& types);
    ConstantValue* MakeValue(uint8_t value, const Types& types);
    ConstantValue* MakeValue(int16_t value, const Types& types);
    ConstantValue* MakeValue(uint16_t value, const Types& types);
    ConstantValue* MakeValue(int32_t value, const Types& types);
    ConstantValue* MakeValue(uint32_t value, const Types& types);
    ConstantValue* MakeValue(int64_t value, const Types& types);
    ConstantValue* MakeValue(uint64_t value, const Types& types);
    ConstantValue* MakeValue(float value, const Types& types);
    ConstantValue* MakeValue(double value, const Types& types);
    ConstantValue* MakeArrayValue(const SourcePos& sourcePos, const std::vector<ConstantValue*>& elements);
    ConstantValue* MakeStructureValue(const SourcePos& sourcePos, const std::vector<ConstantValue*>& fieldValues);
    ConstantValue* MakeStringValue(const SourcePos& sourcePos, const std::string& value);
    ConstantValue* MakeStringArrayValue(const SourcePos& sourcePos, char prefix, const std::vector<ConstantValue*>& strings);
    ConstantValue* MakeConversionValue(const SourcePos& sourcePos, Type* type, ConstantValue* from);
    ConstantValue* MakeClsIdValue(const SourcePos& sourcePos, Type* type, const std::string& clsIdStr);
    ConstantValue* MakeSymbolValue(const SourcePos& sourcePos, Type* type, const std::string& symbol);
    ConstantValue* MakeNumericLiteral(const SourcePos& sourcePos, Type* type, const std::string& strValue, const Types& types, Context* context);
    ConstantValue* MakeAddressLiteral(const SourcePos& sourcePos, Type* type, const std::string& id, Context* context);
    void VisitGlobalVariables(Visitor& visitor);
private:
    Context* context;
    std::vector<std::unique_ptr<Value>> values;
    std::vector<GlobalVariable*> globalVariables;
    std::map<std::string, GlobalVariable*> globalVariableMap;
    std::unique_ptr<BoolValue> trueValue;
    std::unique_ptr<BoolValue> falseValue;
    ConstantValueMap<int8_t> sbyteValueMap;
    ConstantValueMap<uint8_t> byteValueMap;
    ConstantValueMap<int16_t> shortValueMap;
    ConstantValueMap<uint16_t> ushortValueMap;
    ConstantValueMap<int32_t> intValueMap;
    ConstantValueMap<uint32_t> uintValueMap;
    ConstantValueMap<int64_t> longValueMap;
    ConstantValueMap<uint64_t> ulongValueMap;
    ConstantValueMap<float> floatValueMap;
    ConstantValueMap<double> doubleValueMap;
    std::map<Type*, NullValue*> nullValueMap;
};

template<class T>
ConstantValueMap<T>::ConstantValueMap()
{
}

template<class T>
ConstantValue* ConstantValueMap<T>::Get(const T& value, Data* data, const Types& types)
{
    auto it = valueMap.find(value);
    if (it != valueMap.cend())
    {
        return it->second;
    }
    else
    {
        ConstantValue* constantValue = data->MakeValue(value, types);
        valueMap[value] = constantValue;
        return constantValue;
    }
}

} // otava::intermediate
