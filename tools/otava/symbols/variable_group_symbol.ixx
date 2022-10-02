// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.variable.group.symbol;

import std.core;
import otava.symbols.symbol;
import otava.symbols.match;

export namespace otava::symbols {

class VariableSymbol;

class VariableGroupSymbol : public Symbol
{
public:
    VariableGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "variable group symbol"; }
    std::string SymbolDocKindStr() const override { return "variable_group"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddVariable(VariableSymbol* variableSymbol);
    VariableSymbol* GetVariable(int arity) const;
    const std::vector<VariableSymbol*>& Variables() const { return variables; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    void Merge(VariableGroupSymbol* that);
private:
    std::vector<VariableSymbol*> variables;
    std::vector<util::uuid> variableIds;
};

} // namespace otava::symbols
