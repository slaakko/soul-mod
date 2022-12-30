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
import otava.symbols.templates;

namespace otava::symbols {

AliasTypeSymbol::AliasTypeSymbol(const std::u32string& name_) : 
    TypeSymbol(SymbolKind::aliasTypeSymbol, name_), referredType(nullptr), referredTypeId(util::nil_uuid())
{
}

AliasTypeSymbol::AliasTypeSymbol(const std::u32string& name_, SymbolKind kind_) : 
    TypeSymbol(kind_, name_), referredType(nullptr), referredTypeId(util::nil_uuid())
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
    referredType = symbolTable.GetTypeNothrow(referredTypeId);
}

void AliasTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TemplateDeclarationSymbol* AliasTypeSymbol::ParentTemplateDeclaration()
{
    Symbol* parentSymbol = Parent();
    if (parentSymbol->IsTemplateDeclarationSymbol())
    {
        return static_cast<TemplateDeclarationSymbol*>(parentSymbol);
    }
    return nullptr;
}

int AliasTypeSymbol::Arity() 
{
    TemplateDeclarationSymbol* templateDeclaration = ParentTemplateDeclaration();
    if (templateDeclaration)
    {
        return templateDeclaration->Arity();
    }
    else
    {
        return 0;
    }
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
    while (type->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(type);
        type = aliasType->ReferredType();
    }
}

void ProcessAliasDeclaration(otava::ast::Node* aliasDeclarationNode, Context* context)
{
    bool instantiate = context->GetFlag(ContextFlags::instantiateAliasTypeTemplate);
    if (instantiate)
    {
        context->PushResetFlag(ContextFlags::instantiateAliasTypeTemplate);
    }
    AliasTypeSymbol* aliasType = context->GetAliasType();
    AliasDeclarationProcessor processor(context);
    aliasDeclarationNode->Accept(processor);
    otava::ast::Node* idNode = processor.GetIdNode();
    TypeSymbol* type = processor.GetType();
    if (instantiate)
    {
        if (!aliasType->ReferredType())
        {
            aliasType->SetReferredType(type);
        }
    }
    else
    {
        context->GetSymbolTable()->AddAliasType(idNode, aliasDeclarationNode, type, context);
    }
    if (instantiate)
    {
        context->PopFlags();
    }
}

bool AliasTypeLess::operator()(AliasTypeSymbol* left, AliasTypeSymbol* right) const
{
    return left->Name() < right->Name();
}

} // namespace otava::symbols
