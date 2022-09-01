// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.container.symbol;

import std.core;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.scope;

export namespace soul::cpp20::symbols {

class ContainerSymbol : public Symbol
{
public:
    ContainerSymbol(SymbolKind kind_, const std::u32string& name_);
    Scope* GetScope() override { return &scope; }
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::unique_ptr<Symbol> RemoveSymbol(Symbol* symbol) override;
    const std::vector<std::unique_ptr<Symbol>>& Symbols() const { return symbols; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
private:
    std::vector<std::unique_ptr<Symbol>> symbols;
    ContainerScope scope;
};

} // namespace soul::cpp20::symbols
