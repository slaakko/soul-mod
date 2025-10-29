// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.evaluation_context;

import std;
import otava.intermediate.data;
import otava.symbols.symbol.table;
import otava.symbols.symbol;
import otava.symbols.value;

export namespace otava::symbols {

class EvaluationContext
{
public:
    EvaluationContext(SymbolTable& symbolTable_);
    void Init();
    std::expected<bool, int> Write(Writer& writer, Context* context);
    std::expected<bool, int> Read(Reader& reader);
    BoolValue* GetBoolValue(bool value);
    IntegerValue* GetIntegerValue(std::int64_t value, const std::u32string& rep, TypeSymbol* type);
    FloatingValue* GetFloatingValue(double value, const std::u32string& rep, TypeSymbol* type);
    NullPtrValue* GetNullPtrValue() { return &nullPtrValue; }
    StringValue* GetStringValue(const std::string& value, TypeSymbol* type);
    CharValue* GetCharValue(char32_t value, TypeSymbol* type);
    SymbolValue* GetSymbolValue(Symbol* symbol);
    InvokeValue* GetInvokeValue(Value* subject);
    ArrayValue* GetArrayValue(TypeSymbol* type);
    StructureValue* GetStructureValue(TypeSymbol* type);
    Value* GetValue(const util::uuid& valueId) const;
    void AddValue(Value* value);
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context);
    SymbolTable& GetSymbolTable() { return symbolTable; }
private:
    void MapValue(Value* value);
    bool initialized;
    SymbolTable& symbolTable;
    BoolValue trueValue;
    BoolValue falseValue;
    NullPtrValue nullPtrValue;
    std::map<std::pair<std::pair<std::int64_t, std::u32string>, TypeSymbol*>, IntegerValue*> integerValueMap;
    std::map<std::pair<std::pair<double, std::u32string>, TypeSymbol*>, FloatingValue*> floatingValueMap;
    std::map<std::pair<std::string, TypeSymbol*>, StringValue*> stringValueMap;
    std::map<std::pair<char32_t, TypeSymbol*>, CharValue*> charValueMap;
    std::map<Symbol*, SymbolValue*> symbolValueMap;
    std::map<Value*, InvokeValue*> invokeMap;
    std::vector<std::unique_ptr<Value>> values;
    std::map<util::uuid, Value*> valueMap;
};

} // namespace otava::symbols
