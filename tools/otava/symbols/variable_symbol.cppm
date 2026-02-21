// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.variable.symbol;

import std;
import otava.symbols.symbol;
import otava.ast.node;

export namespace otava::symbols {

class TypeSymbol;
class Value;

class VariableSymbol : public Symbol
{
public:
    VariableSymbol(const std::u32string& name_);
    inline int Arity() const noexcept { return 0; }
    std::string SymbolKindStr() const override { return "variable symbol"; }
    std::string SymbolDocKindStr() const override { return "variable"; }
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    inline TypeSymbol* GetDeclaredType() const noexcept { return declaredType; }
    inline void SetDeclaredType(TypeSymbol* declaredType_) noexcept { declaredType = declaredType_; }
    inline TypeSymbol* GetInitializerType() const noexcept { return initializerType; }
    void SetInitializerType(TypeSymbol* initializerType_) noexcept;
    TypeSymbol* GetType() const noexcept;
    TypeSymbol* GetReferredType() const noexcept;
    inline Value* GetValue() const noexcept { return value; }
    inline void SetValue(Value* value_) noexcept { value = value_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    bool IsLocalVariable() const noexcept;
    bool IsMemberVariable() const noexcept;
    bool IsGlobalVariable() const noexcept;
    bool IsStatic() const noexcept;
    inline std::int32_t LayoutIndex() const noexcept { return layoutIndex; }
    inline void SetLayoutIndex(std::int32_t layoutIndex_) noexcept { layoutIndex = layoutIndex_; }
    std::string IrName(Context* context) const;
    inline std::int32_t Index() const noexcept { return index; }
    inline void SetIndex(std::int32_t index_) noexcept { index = index_; }
    inline VariableSymbol* Final() noexcept { if (global) return global; else return this; }
    inline void SetGlobal(VariableSymbol* global_) noexcept { global = global_; }
    inline void SetLevel(int level_) noexcept { level = level_; }
    inline int Level() const noexcept { return level; }
    inline bool FoundFromParent() const noexcept { return foundFromParent; }
    inline void SetFoundFromParent() noexcept { foundFromParent = true; }
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
    int level;
    bool foundFromParent;
};

struct VariableLess
{
    bool operator()(VariableSymbol* left, VariableSymbol* right) const noexcept;
};

void SetDeclaredVariableType(VariableSymbol* variable, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
