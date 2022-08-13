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
    none, boolValue, integerValue, floatingValue
};

ValueKind CommonValueKind(ValueKind left, ValueKind right);

class Value : public Symbol
{
public:
    Value(SymbolKind symbolKind_, const std::u32string& rep_);
    virtual BoolValue* ToBoolValue(EvaluationContext& context) = 0;
    virtual Value* Convert(ValueKind kind, EvaluationContext& context) = 0;
    ValueKind GetValueKind() const;
    const std::u32string& Rep() const { return Name(); }
};

class BoolValue : public Value
{
public:
    BoolValue();
    BoolValue(const std::u32string& rep_);
    BoolValue(bool value_, const std::u32string& rep_);
    std::string SymbolKindStr() const override { return "bool value"; }
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
    double GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
private:
    double value;
};

class EvaluationContext
{
public:
    EvaluationContext();
    void Init();
    void Write(Writer& writer);
    void Read(Reader& reader);
    BoolValue* GetBoolValue(bool value);
    IntegerValue* GetIntegerValue(int64_t value, const std::u32string& rep);
    FloatingValue* GetFloatingValue(double value, const std::u32string& rep);
private:
    BoolValue trueValue;
    BoolValue falseValue;
    std::map<std::pair<int64_t, std::u32string>, IntegerValue*> integerValueMap;
    std::map<std::pair<double, std::u32string>, FloatingValue*> floatingValueMap;
    std::vector<std::unique_ptr<Value>> values;
};

void SetEvaluationContext(EvaluationContext* evalationContext);
EvaluationContext& GetEvaluationContext();

} // namespace soul::cpp20::symbols
