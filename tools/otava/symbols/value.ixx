// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.value;

import std.core;
import otava.intermediate.value;
import otava.symbols.symbol;

export namespace otava::symbols {

class BoolValue;
class Emitter;
class EvaluationContext;
class TypeSymbol;

enum class ValueKind : int32_t
{
    none, boolValue, integerValue, floatingValue, nullPtrValue, stringValue, charValue, symbolValue, invokeValue
};

ValueKind CommonValueKind(ValueKind left, ValueKind right);

class Value : public Symbol
{
public:
    Value(SymbolKind symbolKind_, const std::u32string& rep_, TypeSymbol* type_);
    bool IsBoolValue() const { return GetValueKind() == ValueKind::boolValue; }
    bool IsIntegerValue() const { return GetValueKind() == ValueKind::integerValue; }
    bool IsFloatingValue() const { return GetValueKind() == ValueKind::floatingValue; }
    bool IsStringValue() const { return GetValueKind() == ValueKind::stringValue; }
    bool IsCharValue() const { return GetValueKind() == ValueKind::charValue; }
    bool IsNullPtrValue() const { return GetValueKind() == ValueKind::nullPtrValue; }
    bool IsSymbolValue() const { return GetValueKind() == ValueKind::symbolValue; }
    bool IsInvokeValue() const { return GetValueKind() == ValueKind::invokeValue; }
    virtual BoolValue* ToBoolValue(EvaluationContext& context) = 0;
    virtual Value* Convert(ValueKind kind, EvaluationContext& context) = 0;
    virtual otava::intermediate::Value* IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context);
    ValueKind GetValueKind() const;
    const std::u32string& Rep() const { return Name(); }
    virtual std::u32string ToString() const { return Rep(); }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    TypeSymbol* GetType() const { return type; }
    void SetType(TypeSymbol* type_) { type = type_; }
private:
    TypeSymbol* type;
    util::uuid typeId;
};

class BoolValue : public Value
{
public:
    BoolValue(TypeSymbol* type_);
    BoolValue(const std::u32string& rep_, TypeSymbol* type_);
    BoolValue(bool value_, const std::u32string& rep_, TypeSymbol* type_);
    std::string SymbolKindStr() const override { return "bool value"; }
    std::string SymbolDocKindStr() const override { return "bool_value"; }
    bool GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override { return this; }
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    otava::intermediate::Value* IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    bool value;
};

class IntegerValue : public Value
{
public:
    IntegerValue(TypeSymbol* type_);
    IntegerValue(const std::u32string& rep_, TypeSymbol* type_);
    IntegerValue(int64_t value_, const std::u32string& rep_, TypeSymbol* type_);
    std::string SymbolKindStr() const override { return "integer value"; }
    std::string SymbolDocKindStr() const override { return "integer_value"; }
    int64_t GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    otava::intermediate::Value* IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    int64_t value;
};

class FloatingValue : public Value
{
public:
    FloatingValue(TypeSymbol* type_);
    FloatingValue(const std::u32string& rep_, TypeSymbol* type_);
    FloatingValue(double value_, const std::u32string& rep_, TypeSymbol* type_);
    std::string SymbolKindStr() const override { return "floating value"; }
    std::string SymbolDocKindStr() const override { return "floating_value"; }
    double GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    otava::intermediate::Value* IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    double value;
};

class NullPtrValue : public Value
{
public:
    NullPtrValue(TypeSymbol* type_);
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    std::string SymbolKindStr() const override { return "nullptr value"; }
    std::string SymbolDocKindStr() const override { return "nullptr_value"; }
    otava::intermediate::Value* IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
};

class StringValue : public Value
{
public:
    StringValue(TypeSymbol* type_);
    StringValue(const std::string& value_, TypeSymbol* type_);
    const std::string & GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    std::string SymbolKindStr() const override { return "string value"; }
    std::string SymbolDocKindStr() const override { return "string_value"; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    otava::intermediate::Value* IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::string value;
};

class CharValue : public Value
{
public:
    CharValue(TypeSymbol* type_);
    CharValue(char32_t value_, TypeSymbol* type_);
    char32_t GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    Value* Convert(ValueKind kind, EvaluationContext& context) override;
    std::string SymbolKindStr() const override { return "char value"; }
    std::string SymbolDocKindStr() const override { return "char_value"; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    otava::intermediate::Value* IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    char32_t value;
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
    EvaluationContext(SymbolTable& symbolTable_);
    void Init();
    void Write(Writer& writer);
    void Read(Reader& reader);
    BoolValue* GetBoolValue(bool value);
    IntegerValue* GetIntegerValue(int64_t value, const std::u32string& rep, TypeSymbol* type);
    FloatingValue* GetFloatingValue(double value, const std::u32string& rep, TypeSymbol* type);
    NullPtrValue* GetNullPtrValue() { return &nullPtrValue; }
    StringValue* GetStringValue(const std::string& value, TypeSymbol* type);
    CharValue* GetCharValue(char32_t value, TypeSymbol* type);
    SymbolValue* GetSymbolValue(Symbol* symbol);
    InvokeValue* GetInvokeValue(Value* subject);
    Value* GetValue(const util::uuid& valueId) const;
    void Resolve(SymbolTable& symbolTable);
    SymbolTable& GetSymbolTable() { return symbolTable; }
private:
    void MapValue(Value* value);
    bool initialized;
    SymbolTable& symbolTable;
    BoolValue trueValue;
    BoolValue falseValue;
    NullPtrValue nullPtrValue;
    std::map<std::pair<std::pair<int64_t, std::u32string>, TypeSymbol*>, IntegerValue*> integerValueMap;
    std::map<std::pair<std::pair<double, std::u32string>, TypeSymbol*>, FloatingValue*> floatingValueMap;
    std::map<std::pair<std::string, TypeSymbol*>, StringValue*> stringValueMap;
    std::map<std::pair<char32_t, TypeSymbol*>, CharValue*> charValueMap;
    std::map<Symbol*, SymbolValue*> symbolValueMap;
    std::map<Value*, InvokeValue*> invokeMap;
    std::vector<std::unique_ptr<Value>> values;
    std::map<util::uuid, Value*> valueMap;
};

} // namespace otava::symbols

