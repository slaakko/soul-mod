// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.value;

import std;
import otava.intermediate.data;
import otava.symbols.symbol.table;
import otava.symbols.symbol;

export namespace otava::symbols {

class BoolValue;
class Emitter;
class EvaluationContext;
class TypeSymbol;
class Context;

enum class ValueKind : std::int32_t
{
    none, boolValue, integerValue, floatingValue, nullPtrValue, stringValue, charValue, symbolValue, invokeValue, arrayValue
};

ValueKind CommonValueKind(ValueKind left, ValueKind right);

bool readingEvaluationContext = false;
bool cloning = false;

class Value : public Symbol
{
public:
    Value(SymbolKind symbolKind_, const std::u32string& rep_, TypeSymbol* type_);
    inline bool IsBoolValue() const { return GetValueKind() == ValueKind::boolValue; }
    inline bool IsIntegerValue() const { return GetValueKind() == ValueKind::integerValue; }
    inline bool IsFloatingValue() const { return GetValueKind() == ValueKind::floatingValue; }
    inline bool IsStringValue() const { return GetValueKind() == ValueKind::stringValue; }
    inline bool IsCharValue() const { return GetValueKind() == ValueKind::charValue; }
    inline bool IsNullPtrValue() const { return GetValueKind() == ValueKind::nullPtrValue; }
    inline bool IsSymbolValue() const { return GetValueKind() == ValueKind::symbolValue; }
    inline bool IsInvokeValue() const { return GetValueKind() == ValueKind::invokeValue; }
    inline bool IsArrayValue() const { return GetValueKind() == ValueKind::arrayValue; }
    virtual BoolValue* ToBoolValue(EvaluationContext& context) = 0;
    virtual std::expected<Value*, int> Convert(ValueKind kind, EvaluationContext& context) = 0;
    virtual std::expected<otava::intermediate::Value*, int> IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context);
    ValueKind GetValueKind() const;
    const std::u32string& Rep() const { return Name(); }
    virtual std::u32string ToString() const { return Rep(); }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    TypeSymbol* GetType() const { return type; }
    virtual Value* Clone() const = 0;
private:
    TypeSymbol* type;
    util::uuid typeId;
    friend class EvaluationContext;
    friend std::unique_ptr<Value> CloneAndSetType(Value* value, TypeSymbol* type);
    void SetType(TypeSymbol* type_) { type = type_; }
};

std::unique_ptr<Value> CloneAndSetType(Value* value, TypeSymbol* type); 

class BoolValue : public Value
{
public:
    BoolValue(TypeSymbol* type_);
    BoolValue(const std::u32string& rep_, TypeSymbol* type_);
    BoolValue(bool value_, const std::u32string& rep_, TypeSymbol* type_);
    std::string SymbolKindStr() const override { return "bool value"; }
    std::string SymbolDocKindStr() const override { return "bool_value"; }
    inline bool GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override { return this; }
    std::expected<Value*, int> Convert(ValueKind kind, EvaluationContext& context) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    std::expected<otava::intermediate::Value*, int> IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    Value* Clone() const override { return new BoolValue(value, Rep(), GetType()); }
private:
    bool value;
};

class IntegerValue : public Value
{
public:
    IntegerValue(TypeSymbol* type_);
    IntegerValue(const std::u32string& rep_, TypeSymbol* type_);
    IntegerValue(std::int64_t value_, const std::u32string& rep_, TypeSymbol* type_);
    std::string SymbolKindStr() const override { return "integer value"; }
    std::string SymbolDocKindStr() const override { return "integer_value"; }
    std::int64_t GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    std::expected<Value*, int> Convert(ValueKind kind, EvaluationContext& context) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    std::expected<otava::intermediate::Value*, int> IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    Value* Clone() const override { return new IntegerValue(value, Rep(), GetType()); }
private:
    std::int64_t value;
};

class FloatingValue : public Value
{
public:
    FloatingValue(TypeSymbol* type_);
    FloatingValue(const std::u32string& rep_, TypeSymbol* type_);
    FloatingValue(double value_, const std::u32string& rep_, TypeSymbol* type_);
    std::string SymbolKindStr() const override { return "floating value"; }
    std::string SymbolDocKindStr() const override { return "floating_value"; }
    inline double GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    std::expected<Value*, int> Convert(ValueKind kind, EvaluationContext& context) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    std::expected<otava::intermediate::Value*, int> IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    Value* Clone() const override { return new FloatingValue(value, Rep(), GetType()); }
private:
    double value;
};

class NullPtrValue : public Value
{
public:
    NullPtrValue(TypeSymbol* type_);
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    std::expected<Value*, int> Convert(ValueKind kind, EvaluationContext& context) override;
    std::string SymbolKindStr() const override { return "nullptr value"; }
    std::string SymbolDocKindStr() const override { return "nullptr_value"; }
    std::expected<otava::intermediate::Value*, int> IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    Value* Clone() const override { return new NullPtrValue(GetType()); }
};

class StringValue : public Value
{
public:
    StringValue(TypeSymbol* type_);
    StringValue(const std::string& value_, TypeSymbol* type_);
    inline const std::string& GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    std::expected<Value*, int> Convert(ValueKind kind, EvaluationContext& context) override;
    std::string SymbolKindStr() const override { return "string value"; }
    std::string SymbolDocKindStr() const override { return "string_value"; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    std::expected<otava::intermediate::Value*, int> IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    Value* Clone() const override { return new StringValue(value, GetType()); }
private:
    std::string value;
};

class CharValue : public Value
{
public:
    CharValue(TypeSymbol* type_);
    CharValue(char32_t value_, TypeSymbol* type_);
    inline char32_t GetValue() const { return value; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    std::expected<Value*, int> Convert(ValueKind kind, EvaluationContext& context) override;
    std::string SymbolKindStr() const override { return "char value"; }
    std::string SymbolDocKindStr() const override { return "char_value"; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    std::expected<otava::intermediate::Value*, int> IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    Value* Clone() const override { return new CharValue(value, GetType()); }
private:
    char32_t value;
};

class SymbolValue : public Value
{
public:
    SymbolValue();
    SymbolValue(Symbol* symbol_);
    inline Symbol* GetSymbol() const { return symbol; }
    std::expected<Value*, int> Convert(ValueKind kind, EvaluationContext& context) override;
    std::string SymbolKindStr() const override { return "symbol value"; }
    std::string SymbolDocKindStr() const override { return "symbol_value"; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    bool IsExportSymbol(Context* context) const override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    std::u32string ToString() const override;
    std::expected<otava::intermediate::Value*, int> IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    Value* Clone() const override { return new SymbolValue(symbol); }
private:
    Symbol* symbol;
    util::uuid symbolId;
};

class InvokeValue : public Value
{
public:
    InvokeValue();
    InvokeValue(Value* subject_);
    inline Value* Subject() const { return subject; }
    std::expected<Value*, int> Convert(ValueKind kind, EvaluationContext& context) override;
    std::string SymbolKindStr() const override { return "invoke value"; }
    std::string SymbolDocKindStr() const override { return "invoke_value"; }
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    bool IsExportSymbol(Context* context) const override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    std::u32string ToString() const override;
    Value* Clone() const override { return new InvokeValue(subject->Clone()); }
private:
    Value* subject;
    util::uuid subjectId;
};

class ArrayValue : public Value
{
public:
    ArrayValue(TypeSymbol* type_);
    void AddElementValue(Value* elementValue);
    std::string SymbolKindStr() const override { return "array value"; }
    std::string SymbolDocKindStr() const override { return "array_value"; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    std::expected<Value*, int> Convert(ValueKind kind, EvaluationContext& context) override;
    std::expected<otava::intermediate::Value*, int> IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    Value* Clone() const override;
private:
    std::vector<Value*> elementValues;
};

class StructureValue : public Value
{
public:
    StructureValue(TypeSymbol* type_);
    void AddFieldValue(Value* fieldValue);
    std::string SymbolKindStr() const override { return "array value"; }
    std::string SymbolDocKindStr() const override { return "array_value"; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    BoolValue* ToBoolValue(EvaluationContext& context) override;
    std::expected<Value*, int> Convert(ValueKind kind, EvaluationContext& context) override;
    std::expected<otava::intermediate::Value*, int> IrValue(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    Value* Clone() const override;
private:
    std::vector<Value*> fieldValues;
};

} // namespace otava::symbols
