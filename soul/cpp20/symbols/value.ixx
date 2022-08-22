// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.value;

import std.core;
import soul.cpp20.symbols.symbol;

export namespace soul::cpp20::symbols {

class BoolValue;
class EvaluationContext;

enum class ValueKind : int32_t
{
    none, boolValue, integerValue, floatingValue, nullPtrValue, symbolValue, invokeValue
};

ValueKind CommonValueKind(ValueKind left, ValueKind right);

class Value : public Symbol
{
public:
    Value(SymbolKind symbolKind_, const std::u32string& rep_);
    bool IsBoolValue() const { return GetValueKind() == ValueKind::boolValue; }
    bool IsIntegerValue() const { return GetValueKind() == ValueKind::integerValue; }
    bool IsFloatingValue() const { return GetValueKind() == ValueKind::floatingValue; }
    bool IsNullPtrValue() const { return GetValueKind() == ValueKind::nullPtrValue; }
    bool IsSymbolValue() const { return GetValueKind() == ValueKind::symbolValue; }
    bool IsInvokeValue() const { return GetValueKind() == ValueKind::invokeValue; }
    virtual BoolValue* ToBoolValue(EvaluationContext& context) = 0;
    virtual Value* Convert(ValueKind kind, EvaluationContext& context) = 0;
    ValueKind GetValueKind() const;
    const std::u32string& Rep() const { return Name(); }
    virtual std::u32string ToString() const { return Rep(); }
};

class BoolValue : public Value
{
public:
    BoolValue();
    BoolValue(const std::u32string& rep_);
    BoolValue(bool value_, const std::u32string& rep_);
    std::string SymbolKindStr() const override { return "bool value"; }
    std::string SymbolDocKindStr() const override { return "bool_value"; }
    bool GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override { return this; }
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
private:
    bool value;
};

class IntegerValue : public Value
{
public:
    IntegerValue();
    IntegerValue(const std::u32string& rep_);
    IntegerValue(int64_t value_, const std::u32string& rep_);
    std::string SymbolKindStr() const override { return "integer value"; }
    std::string SymbolDocKindStr() const override { return "integer_value"; }
    int64_t GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
private:
    int64_t value;
};

class FloatingValue : public Value
{
public:
    FloatingValue();
    FloatingValue(const std::u32string& rep_);
    FloatingValue(double value_, const std::u32string& rep_);
    std::string SymbolKindStr() const override { return "floating value"; }
    std::string SymbolDocKindStr() const override { return "floating_value"; }
    double GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
private:
    double value;
};

class NullPtrValue : public Value
{
public:
    NullPtrValue();
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    std::string SymbolKindStr() const override { return "nullptr value"; }
    std::string SymbolDocKindStr() const override { return "nullptr_value"; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
};

class SymbolValue : public Value
{
public:
    SymbolValue();
    SymbolValue(Symbol* symbol_);
    Symbol* GetSymbol() const { return symbol; }
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    std::string SymbolKindStr() const override { return "symbol value"; }
    std::string SymbolDocKindStr() const override { return "symbol_value"; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    void Resolve(SymbolTable& symbolTable) override;
    std::u32string ToString() const override;
private:
    Symbol* symbol;
    util::uuid symbolId;
};

class InvokeValue : public Value
{
public:
    InvokeValue();
    InvokeValue(Value* subject_);
    Value* Subject() const { return subject; }
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    std::string SymbolKindStr() const override { return "invoke value"; }
    std::string SymbolDocKindStr() const override { return "invoke_value"; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    void Resolve(SymbolTable& symbolTable) override;
    std::u32string ToString() const override;
private:
    Value* subject;
    util::uuid subjectId;
};

class EvaluationContext
{
public:
    EvaluationContext();
    void Write(Writer& writer);
    void Read(Reader& reader);
    BoolValue* GetBoolValue(bool value);
    IntegerValue* GetIntegerValue(int64_t value, const std::u32string& rep);
    FloatingValue* GetFloatingValue(double value, const std::u32string& rep);
    NullPtrValue* GetNullPtrValue() { return &nullPtrValue; }
    SymbolValue* GetSymbolValue(Symbol* symbol);
    InvokeValue* GetInvokeValue(Value* subject);
    Value* GetValue(const util::uuid& valueId) const;
    void Resolve(SymbolTable& symbolTable);
private:
    void MapValue(Value* value);
    BoolValue trueValue;
    BoolValue falseValue;
    NullPtrValue nullPtrValue;
    std::map<std::pair<int64_t, std::u32string>, IntegerValue*> integerValueMap;
    std::map<std::pair<double, std::u32string>, FloatingValue*> floatingValueMap;
    std::map<Symbol*, SymbolValue*> symbolValueMap;
    std::map<Value*, InvokeValue*> invokeMap;
    std::vector<std::unique_ptr<Value>> values;
    std::map<util::uuid, Value*> valueMap;
};

} // namespace soul::cpp20::symbols

