// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.namespaces;

import soul.cpp20.ast.node;
import soul.cpp20.symbols.container.symbol;

export namespace soul::cpp20::symbols {

class SymbolTable;

class NamespaceSymbol : public ContainerSymbol
{
public:
    NamespaceSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "namespace symbol"; }
    std::string SymbolDocKindStr() const override { return "namespace"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    void Import(NamespaceSymbol* that, Context* context);
    void Accept(Visitor& visitor) override;
    SymbolTable* GetSymbolTable() override;
    void SetSymbolTable(SymbolTable* symbolTable_) { symbolTable = symbolTable_; }
    bool ContainsSymbols() const;
private:
    SymbolTable* symbolTable;
};

void BeginNamespace(soul::cpp20::ast::Node* node, Context* context);
void EndNamespace(soul::cpp20::ast::Node* node, int level, Context* context);

struct NamespaceLess
{
    bool operator()(NamespaceSymbol* left, NamespaceSymbol* right) const;
};

} // namespace soul::cpp20::symbols
