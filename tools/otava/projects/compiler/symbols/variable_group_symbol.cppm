// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.variable.group.symbol;

import std;
import otava.symbols.symbol;
import otava.symbols.context;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.symbol.table;

export namespace otava::symbols {

class VariableSymbol;

class VariableGroupSymbol : public Symbol
{
public:
    VariableGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "variable group symbol"; }
    std::string SymbolDocKindStr() const override { return "variable_group"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    Symbol* GetSingleSymbol() noexcept override;
    void AddVariable(VariableSymbol* variableSymbol);
    VariableSymbol* GetVariable(int arity) const noexcept;
    inline const std::vector<VariableSymbol*>& Variables() const noexcept { return variables; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    void Merge(VariableGroupSymbol* that);
private:
    std::vector<VariableSymbol*> variables;
    std::vector<util::uuid> variableIds;
};

} // namespace otava::symbols
