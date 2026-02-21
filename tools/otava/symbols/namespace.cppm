// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.namespaces;

import std;
import otava.ast.node;
import otava.symbols.container.symbol;

export namespace otava::symbols {

class NamespaceSymbol : public ContainerSymbol
{
public:
    NamespaceSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "namespace symbol"; }
    std::string SymbolDocKindStr() const override { return "namespace"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    void Import(NamespaceSymbol* that, Context* context);
    void Accept(Visitor& visitor) override;
    bool ContainsSymbols() const noexcept;
};

void BeginNamespace(otava::ast::Node* node, Context* context);
void EndNamespace(otava::ast::Node* node, int level, Context* context);

struct NamespaceLess
{
    bool operator()(NamespaceSymbol* left, NamespaceSymbol* right) const noexcept;
};

} // namespace otava::symbols
