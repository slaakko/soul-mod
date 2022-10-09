// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.variable.symbol;

import std.core;
import otava.symbols.symbol;
import otava.ast.node;

export namespace otava::symbols {

class TypeSymbol;
class Value;

class VariableSymbol : public Symbol
{
public:
    VariableSymbol(const std::u32string& name_);
    virtual int Arity() const { return 0; }
    std::string SymbolKindStr() const override { return "variable symbol"; }
    std::string SymbolDocKindStr() const override { return "variable"; }
    TypeSymbol* GetDeclaredType() const { return declaredType; }
    void SetDeclaredType(TypeSymbol* declaredType_) { declaredType = declaredType_; }
    TypeSymbol* GetInitializerType() const { return initializerType; }
    void SetInitializerType(TypeSymbol* initializerType_);
    TypeSymbol* GetType() const;
    Value* GetValue() const { return value; }
    void SetValue(Value* value_) { value = value_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    TypeSymbol* declaredType;
    util::uuid declaredTypeId;
    TypeSymbol* initializerType;
    util::uuid initializerTypeId;
    Value* value;
    util::uuid valueId;
};

struct VariableLess
{
    bool operator()(VariableSymbol* left, VariableSymbol* right) const;
};

} // namespace otava::symbols