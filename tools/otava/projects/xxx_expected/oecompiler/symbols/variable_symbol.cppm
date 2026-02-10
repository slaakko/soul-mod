// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.variable.symbol;

import std;
import otava.symbols.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.context;
import otava.symbols.value;
import otava.ast.node;

export namespace otava::symbols {

class TypeSymbol;
class Value;

class VariableSymbol : public Symbol
{
public:
    VariableSymbol(const std::u32string& name_);
    inline int Arity() const { return 0; }
    std::string SymbolKindStr() const override { return "variable symbol"; }
    std::string SymbolDocKindStr() const override { return "variable"; }
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    TypeSymbol* GetDeclaredType() const { return declaredType; }
    void SetDeclaredType(TypeSymbol* declaredType_) { declaredType = declaredType_; }
    TypeSymbol* GetInitializerType() const { return initializerType; }
    void SetInitializerType(TypeSymbol* initializerType_);
    TypeSymbol* GetType() const;
    TypeSymbol* GetReferredType() const;
    inline Value* GetValue() const { return value; }
    inline void SetValue(Value* value_) { value = value_; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    bool IsLocalVariable() const;
    bool IsMemberVariable() const;
    bool IsGlobalVariable() const;
    bool IsStatic() const;
    inline std::int32_t LayoutIndex() const { return layoutIndex; }
    inline void SetLayoutIndex(std::int32_t layoutIndex_) { layoutIndex = layoutIndex_; }
    std::expected<std::string, int> IrName(Context* context) const override;
    inline std::int32_t Index() const { return index; }
    inline void SetIndex(std::int32_t index_) { index = index_; }
    inline VariableSymbol* Final() { if (global) return global; else return this; }
    inline void SetGlobal(VariableSymbol* global_) { global = global_; }
private:
    TypeSymbol* declaredType;
    util::uuid declaredTypeId;
    TypeSymbol* initializerType;
    util::uuid initializerTypeId;
    Value* value;
    util::uuid valueId;
    std::int32_t layoutIndex;
    std::int32_t index;
    VariableSymbol* global;
};

struct VariableLess
{
    bool operator()(VariableSymbol* left, VariableSymbol* right) const;
};

std::expected<bool, int> SetDeclaredVariableType(VariableSymbol* variable, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
