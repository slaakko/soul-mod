// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.alias.type.symbol;

import util;
import otava.symbols.context;
import otava.symbols.type.resolver;
import otava.symbols.symbol.table;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.alias.group.symbol;
import otava.symbols.modules;
import otava.symbols.expression.binder;

namespace otava::symbols {

AliasTypeSymbol::AliasTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::aliasTypeSymbol, name_), referredType(nullptr), referredTypeId(util::nil_uuid()), group(nullptr)
{
}

AliasTypeSymbol::AliasTypeSymbol(const std::u32string& name_, SymbolKind kind_) :
    TypeSymbol(kind_, name_), referredType(nullptr), referredTypeId(util::nil_uuid()), group(nullptr)
{
}

AliasTypeSymbol::AliasTypeSymbol(const std::u32string& name_, TypeSymbol* referredType_) :
    TypeSymbol(SymbolKind::aliasTypeSymbol, name_), referredType(referredType_), referredTypeId(util::nil_uuid()), group(nullptr)
{
}

std::expected<bool, int> AliasTypeSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(referredType->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AliasTypeSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(referredTypeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AliasTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    referredType = symbolTable.GetTypeNoThrow(referredTypeId);
    return std::expected<bool, int>(true);
}

void AliasTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

bool AliasTypeSymbol::IsExportSymbol(Context* context) const
{
    return TypeSymbol::IsExportSymbol(context);
}

bool AliasTypeSymbol::IsExportMapSymbol(Context* context) const
{
    return false;
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

std::expected<TypeSymbol*, int> AliasTypeSymbol::DirectType(Context* context)
{
    return referredType->DirectType(context);
}

std::expected<otava::intermediate::Type*, int> AliasTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<TypeSymbol*, int> dt = DirectType(context);
    if (!dt) return std::unexpected<int>(dt.error());
    TypeSymbol* directType = *dt;
    return directType->IrType(emitter, sourcePos, context);
}

std::expected<soul::xml::Element*, int> AliasTypeSymbol::ToXml() const
{
    std::expected<soul::xml::Element*, int> rv = TypeSymbol::ToXml();
    if (!rv) return rv;
    soul::xml::Element* element = *rv;
    if (group)
    {
        element->SetAttribute("groupId", util::ToString(group->Id()));
    }
    return std::expected<soul::xml::Element*, int>(element);
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
    if (!Valid()) return;
    context->PushSetFlag(ContextFlags::processingAliasDeclation);
    idNode = node.Identifier();
    std::expected<TypeSymbol*, int> rv = ResolveType(node.DefiningTypeId(), DeclarationFlags::none, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    type = *rv;
    while (type->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(type);
        type = aliasType->ReferredType();
    }
    context->PopFlags();
}

std::expected<bool, int> ProcessAliasDeclaration(otava::ast::Node* aliasDeclarationNode, Context* context)
{
    bool instantiate = context->GetFlag(ContextFlags::instantiateAliasTypeTemplate);
    if (instantiate)
    {
        context->PushResetFlag(ContextFlags::instantiateAliasTypeTemplate);
    }
    AliasTypeSymbol* aliasType = context->GetAliasType();
    AliasDeclarationProcessor processor(context);
    aliasDeclarationNode->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    otava::ast::Node* idNode = processor.GetIdNode();
    TypeSymbol* type = processor.GetType();
    if (instantiate)
    {
        if (!aliasType->ReferredType())
        {
            aliasType->SetReferredType(type);
        }
        context->GetSymbolTable()->MapNode(aliasDeclarationNode, aliasType);
    }
    else
    {
        std::expected<AliasTypeSymbol*, int> a = context->GetSymbolTable()->AddAliasType(idNode, aliasDeclarationNode, type, context);
        if (!a) return std::unexpected<int>(a.error());
    }
    if (instantiate)
    {
        context->PopFlags();
    }
    return std::expected<bool, int>(true);
}

bool AliasTypeLess::operator()(AliasTypeSymbol* left, AliasTypeSymbol* right) const
{
    return left->Name() < right->Name();
}

std::expected<bool, int> AddTemporaryTypeAlias(otava::ast::Node* aliasDeclarationNode, Context* context)
{
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    if (aliasDeclarationNode->IsAliasDeclarationNode())
    {
        otava::ast::AliasDeclarationNode* alias = static_cast<otava::ast::AliasDeclarationNode*>(aliasDeclarationNode);
        otava::ast::Node* idNode = alias->Identifier();
        std::expected<AliasTypeSymbol*, int> a = context->GetSymbolTable()->AddAliasType(idNode, aliasDeclarationNode, GenericTypeSymbol::Instance(), context);
        if (!a) return std::unexpected<int>(a.error());
        AliasTypeSymbol* temporaryAlias = *a;
        context->AddTemporaryAliasType(temporaryAlias);
    }
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> RemoveTemporaryAliasTypeSymbols(Context* context)
{
    for (AliasTypeSymbol* temporaryAlias : context->TemporaryAliasTypes())
    {
        temporaryAlias->Group()->RemoveAliasType(temporaryAlias);
        Scope* scope = temporaryAlias->Parent()->GetScope()->SymbolScope();
        if (scope->IsContainerScope())
        {
            std::expected<std::unique_ptr<Symbol>, int> rv = scope->RemoveSymbol(temporaryAlias);
            if (!rv) return std::unexpected<int>(rv.error());
        }
    }
    context->ClearTemporaryAliasTypes();
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
