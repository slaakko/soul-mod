// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.alias.type.symbol;

import soul.cpp20.symbols.context;
import soul.cpp20.symbols.type.resolver;
import soul.cpp20.symbols.symbol.table;

namespace soul::cpp20::symbols {

AliasTypeSymbol::AliasTypeSymbol(const std::u32string& name_, TypeSymbol* referredType_) : TypeSymbol(SymbolKind::aliasTypeSymbol, name_), referredType(referredType_)
{
}

class AliasDeclarationProcessor : public soul::cpp20::ast::DefaultVisitor
{
public:
    AliasDeclarationProcessor(Context* context_);
    void Visit(soul::cpp20::ast::AliasDeclarationNode& node);
    soul::cpp20::ast::Node* GetIdNode() const { return idNode; }
    TypeSymbol* GetType() const { return type; }
private:
    Context* context;
    soul::cpp20::ast::Node* idNode;
    TypeSymbol* type;
};

AliasDeclarationProcessor::AliasDeclarationProcessor(Context* context_) : context(context_), idNode(nullptr), type(nullptr)
{
}

void AliasDeclarationProcessor::Visit(soul::cpp20::ast::AliasDeclarationNode& node)
{
    idNode = node.Identifier();
    type = ResolveType(node.DefiningTypeId(), context);
}

void ProcessAliasDeclaration(soul::cpp20::ast::Node* aliasDeclarationNode, Context* context)
{
    AliasDeclarationProcessor processor(context);
    aliasDeclarationNode->Accept(processor);
    soul::cpp20::ast::Node* idNode = processor.GetIdNode();
    TypeSymbol* type = processor.GetType();
    context->GetSymbolTable()->AddAliasType(idNode, type, context);
}

} // namespace soul::cpp20::symbols
