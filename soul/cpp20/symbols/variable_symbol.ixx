// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.variable.symbol;

import std.core;
import soul.cpp20.symbols.symbol;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

class TypeSymbol;
class Value;

class VariableSymbol : public Symbol
{
public:
    VariableSymbol(const std::u32string& name_);
    virtual int Arity() const { return 0; }
    std::string SymbolKindStr() const override { return "variable symbol"; }
    std::string SymbolDocKindStr() const override { return "variable"; }
    TypeSymbol* GetType() const { return type; }
    void SetType(TypeSymbol* type_) { type = type_; }
    Value* GetValue() const { return value; }
    void SetValue(Value* value_) { value = value_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    TypeSymbol* type;
    util::uuid typeId;
    Value* value;
    util::uuid valueId;
};

struct VariableLess
{
    bool operator()(VariableSymbol* left, VariableSymbol* right) const;
};

} // namespace soul::cpp20::symbols
