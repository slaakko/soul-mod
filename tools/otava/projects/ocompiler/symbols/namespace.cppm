// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.namespaces;

import std;
import otava.ast.node;
import otava.symbols.container.symbol;
import otava.symbols.context;

export namespace otava::symbols {

class SymbolTable;

class NamespaceSymbol : public ContainerSymbol
{
public:
    NamespaceSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "namespace symbol"; }
    std::string SymbolDocKindStr() const override { return "namespace"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    std::expected<bool, int> Import(NamespaceSymbol* that, Context* context);
    void Accept(Visitor& visitor) override;
    bool ContainsSymbols() const;
};

std::expected<bool, int> BeginNamespace(otava::ast::Node* node, Context* context);
std::expected<bool, int> EndNamespace(otava::ast::Node* node, int level, Context* context);

struct NamespaceLess
{
    bool operator()(NamespaceSymbol* left, NamespaceSymbol* right) const;
};

} // namespace otava::symbols
