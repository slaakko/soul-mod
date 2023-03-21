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
    int Arity() const { return 0; }
    std::string SymbolKindStr() const override { return "variable symbol"; }
    std::string SymbolDocKindStr() const override { return "variable"; }
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    TypeSymbol* GetDeclaredType() const { return declaredType; }
    void SetDeclaredType(TypeSymbol* declaredType_) { declaredType = declaredType_; }
    TypeSymbol* GetInitializerType() const { return initializerType; }
    void SetInitializerType(TypeSymbol* initializerType_);
    TypeSymbol* GetType() const;
    TypeSymbol* GetReferredType() const;
    Value* GetValue() const { return value; }
    void SetValue(Value* value_) { value = value_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    bool IsLocalVariable() const;
    bool IsMemberVariable() const;
    bool IsGlobalVariable() const;
    bool IsStatic() const;
    int32_t LayoutIndex() const { return layoutIndex; }
    void SetLayoutIndex(int32_t layoutIndex_) { layoutIndex = layoutIndex_; }
    std::string IrName(Context* context) const;
    int32_t Index() const { return index; }
    void SetIndex(int32_t index_) { index = index_; }
    VariableSymbol* Final() { if (global) return global; else return this; }
    void SetGlobal(VariableSymbol* global_) { global = global_; }
private:
    TypeSymbol* declaredType;
    util::uuid declaredTypeId;
    TypeSymbol* initializerType;
    util::uuid initializerTypeId;
    Value* value;
    util::uuid valueId;
    int32_t layoutIndex;
    int32_t index;
    VariableSymbol* global;
};

struct VariableLess
{
    bool operator()(VariableSymbol* left, VariableSymbol* right) const;
};

void SetDeclaredVariableType(VariableSymbol* variable, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
