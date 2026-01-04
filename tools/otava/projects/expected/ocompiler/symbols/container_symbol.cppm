// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.container.symbol;

import std;
import otava.symbols.symbol;
import otava.symbols.scope;

export namespace otava::symbols {

class ContainerSymbol : public Symbol
{
public:
    ContainerSymbol(SymbolKind kind_, const std::u32string& name_);
    ContainerSymbol(SymbolKind kind_, const util::uuid& id_, const std::u32string& name_);
    Scope* GetScope() override { return &scope; }
    std::expected<bool, int> AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<std::unique_ptr<Symbol>, int> RemoveSymbol(Symbol* symbol) override;
    inline const std::vector<std::unique_ptr<Symbol>>& Symbols() const { return members; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    std::expected<soul::xml::Element*, int> ToXml() const override;
private:
    std::vector<std::unique_ptr<Symbol>> members;
    ContainerScope scope;
};

} // namespace otava::symbols
