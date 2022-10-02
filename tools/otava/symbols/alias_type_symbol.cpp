// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.alias.type.symbol;

import otava.symbols.context;
import otava.symbols.type.resolver;
import otava.symbols.symbol.table;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;

namespace otava::symbols {

AliasTypeSymbol::AliasTypeSymbol(const std::u32string& name_) : 
    TypeSymbol(SymbolKind::aliasTypeSymbol, name_), referredType(nullptr), referredTypeId(util::nil_uuid())
{
}

AliasTypeSymbol::AliasTypeSymbol(const std::u32string& name_, TypeSymbol* referredType_) : 
    TypeSymbol(SymbolKind::aliasTypeSymbol, name_), referredType(referredType_), referredTypeId(util::nil_uuid())
{
}

void AliasTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(referredType->Id());
}

void AliasTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(referredTypeId);
}

void AliasTypeSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    referredType = symbolTable.GetType(referredTypeId);
}

void AliasTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

class AliasDeclarationProcessor : public otava::ast::DefaultVisitor
{
public:
    AliasDeclarationProcessor(Context* context_);
    void Visit(otava::ast::AliasDeclarationNode& node);
    otava::ast::Node* GetIdNode() const { return idNode; }
    TypeSymbol* GetType() const { return type; }
private:
    Context* context;
    otava::ast::Node* idNode;
    TypeSymbol* type;
};

AliasDeclarationProcessor::AliasDeclarationProcessor(Context* context_) : context(context_), idNode(nullptr), type(nullptr)
{
}

void AliasDeclarationProcessor::Visit(otava::ast::AliasDeclarationNode& node)
{
    idNode = node.Identifier();
    type = ResolveType(node.DefiningTypeId(), DeclarationFlags::none, context);
}

void ProcessAliasDeclaration(otava::ast::Node* aliasDeclarationNode, Context* context)
{
    AliasDeclarationProcessor processor(context);
    aliasDeclarationNode->Accept(processor);
    otava::ast::Node* idNode = processor.GetIdNode();
    TypeSymbol* type = processor.GetType();
    context->GetSymbolTable()->AddAliasType(idNode, type, context);
}

bool AliasTypeLess::operator()(AliasTypeSymbol* left, AliasTypeSymbol* right) const
{
    return left->Name() < right->Name();
}

} // namespace otava::symbols
