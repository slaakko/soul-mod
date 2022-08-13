// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.namespaces;

import soul.cpp20.ast.node;
import soul.cpp20.symbols.container.symbol;

export namespace soul::cpp20::symbols {

class NamespaceSymbol : public ContainerSymbol
{
public:
    NamespaceSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "namespace symbol"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    void Import(NamespaceSymbol* that, Context* context);
    void Accept(Visitor& visitor) override;
};

void BeginNamespace(soul::cpp20::ast::Node* node, Context* context);
void EndNamespace(int level, Context* context);

} // namespace soul::cpp20::symbols
