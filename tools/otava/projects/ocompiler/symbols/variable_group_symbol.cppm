// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.variable.group.symbol;

import std;
import otava.symbols.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.context;
import otava.symbols.symbol.table;

export namespace otava::symbols {

class VariableSymbol;

class VariableGroupSymbol : public Symbol
{
public:
    VariableGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddVariable(VariableSymbol* variableSymbol);
    VariableSymbol* GetVariable(int arity) const;
    inline const std::vector<VariableSymbol*>& Variables() const { return variables; }
    inline bool Empty() const { return variables.empty(); }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    void Merge(VariableGroupSymbol* that);
private:
    std::vector<VariableSymbol*> variables;
    std::vector<util::uuid> variableIds;
};

} // namespace otava::symbols
