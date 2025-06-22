// =================================
// Copyright (c) 2025 Seppo Laakko
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

TypeSymbol* AliasTypeSymbol::DirectType(Context* context)
{
    return referredType->DirectType(context);
}

otava::intermediate::Type* AliasTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return DirectType(context)->IrType(emitter, sourcePos, context);
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

void AddTemporaryTypeAlias(otava::ast::Node* aliasDeclarationNode, Context* context)
{
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    if (aliasDeclarationNode->IsAliasDeclarationNode())
    {
        otava::ast::Node* idNode = static_cast<otava::ast::AliasDeclarationNode*>(aliasDeclarationNode)->Identifier();
        AliasTypeSymbol* temporaryAlias = context->GetSymbolTable()->AddAliasType(idNode, aliasDeclarationNode, GenericTypeSymbol::Instance(), context);
        context->AddTemporaryAliasType(temporaryAlias);
    }
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
}

void RemoveTemporaryAliasTypeSymbols(Context* context)
{
    for (const auto& temporaryAlias : context->TemporaryAliasTypes())
    {
        temporaryAlias->Group()->RemoveAliasType(temporaryAlias);
        Scope* scope = temporaryAlias->Parent()->GetScope()->SymbolScope();
        if (scope->IsContainerScope())
        {
            scope->RemoveSymbol(temporaryAlias);
        }
    }
    context->ClearTemporaryAliasTypes();
}

} // namespace otava::symbols
