// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================
module;
#include <boost/uuid/uuid.hpp>

module otava.symbols.enums;

import util;
import otava.ast;
import otava.symbols.context;
import otava.symbols.emitter;
import otava.symbols.exception;
import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.scope.resolver;
import otava.symbols.type.resolver;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.value;
import otava.symbols.visitor;
import otava.symbols.evaluator;
import otava.symbols.fundamental.type.symbol;

namespace otava::symbols {

EnumeratedTypeSymbol::EnumeratedTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::enumTypeSymbol, name_), underlyingType(nullptr), kind(EnumTypeKind::enum_),
    underlyingTypeId()
{
    GetScope()->SetKind(ScopeKind::enumerationScope);
}

bool EnumeratedTypeSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope:
        case ScopeKind::classScope:
        {
            return true;
        }
    }
    return false;

}

void EnumeratedTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(kind));
    bool hasUnderlyingType = underlyingType != nullptr;
    writer.GetBinaryStreamWriter().Write(hasUnderlyingType);
    if (hasUnderlyingType)
    {
        writer.GetBinaryStreamWriter().Write(underlyingType->Id());
    }
}

void EnumeratedTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    kind = static_cast<EnumTypeKind>(reader.GetBinaryStreamReader().ReadByte());
    bool hasUnderlyingType = reader.GetBinaryStreamReader().ReadBool();
    if (hasUnderlyingType)
    {
        reader.GetBinaryStreamReader().ReadUuid(underlyingTypeId);
    }
}

void EnumeratedTypeSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    if (underlyingTypeId != util::nil_uuid())
    {
        underlyingType = symbolTable.GetType(underlyingTypeId);
    }
}

void EnumeratedTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

otava::intermediate::Type* EnumeratedTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (underlyingType)
    {
        return underlyingType->IrType(emitter, sourcePos, context);
    }
    else
    {
        return emitter.GetIntType();
    }
}

ForwardEnumDeclarationSymbol::ForwardEnumDeclarationSymbol(const std::u32string& name_) : 
    TypeSymbol(SymbolKind::forwardEnumDeclarationSymbol, name_), 
    underlyingType(nullptr), 
    enumTypeKind(EnumTypeKind::enum_),
    enumTypeSymbol(),
    enumTypeSymbolId(),
    underlyingTypeId()
{
    GetScope()->SetKind(ScopeKind::enumerationScope);
}

bool ForwardEnumDeclarationSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope:
        case ScopeKind::classScope:
        {
            return true;
        }
    }
    return false;
}

void ForwardEnumDeclarationSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ForwardEnumDeclarationSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(enumTypeKind));
    bool hasUnderlyingType = underlyingType != nullptr;
    writer.GetBinaryStreamWriter().Write(hasUnderlyingType);
    if (hasUnderlyingType)
    {
        writer.GetBinaryStreamWriter().Write(underlyingType->Id());
    }
    writer.GetBinaryStreamWriter().Write(enumTypeSymbol != nullptr);
    if (enumTypeSymbol)
    {
        writer.GetBinaryStreamWriter().Write(enumTypeSymbol->Id());
    }
}

void ForwardEnumDeclarationSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    enumTypeKind = static_cast<EnumTypeKind>(reader.GetBinaryStreamReader().ReadByte());
    bool hasUnderlyingType = reader.GetBinaryStreamReader().ReadBool();
    if (hasUnderlyingType)
    {
        reader.GetBinaryStreamReader().ReadUuid(underlyingTypeId);
    }
    bool hasEnumType = reader.GetBinaryStreamReader().ReadBool();
    if (hasEnumType)
    {
        reader.GetBinaryStreamReader().ReadUuid(enumTypeSymbolId);
    }
}

void ForwardEnumDeclarationSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    if (underlyingTypeId != util::nil_uuid())
    {
        underlyingType = symbolTable.GetType(underlyingTypeId);
    }
    if (enumTypeSymbolId != util::nil_uuid())
    {
        TypeSymbol* type = symbolTable.GetType(enumTypeSymbolId);
        if (type->IsEnumeratedTypeSymbol())
        {
            enumTypeSymbol = static_cast<EnumeratedTypeSymbol*>(type);
        }
        else
        {
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("otava.symbols.enums: enum type expected");
        }
    }
}

EnumConstantSymbol::EnumConstantSymbol(const std::u32string& name_) : Symbol(SymbolKind::enumConstantSymbol, name_), value(), valueId()
{
}

bool EnumConstantSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    return scopeKind == ScopeKind::enumerationScope;
}

void EnumConstantSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(value->Id());
}

void EnumConstantSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(valueId);
}

void EnumConstantSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
    value = evaluationContext->GetValue(valueId);
}

void EnumConstantSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EnumeratedTypeSymbol* EnumConstantSymbol::GetType() const
{
    const Symbol* parent = Parent();
    if (parent && parent->IsEnumeratedTypeSymbol())
    {
        return const_cast<EnumeratedTypeSymbol*>(static_cast<const EnumeratedTypeSymbol*>(parent));
    }
    return nullptr;
}

bool EnumTypeLess::operator()(EnumeratedTypeSymbol* left, EnumeratedTypeSymbol* right) const
{
    return left->Name() < right->Name();
}

class EnumCreator : public otava::ast::DefaultVisitor
{
public:
    EnumCreator(Context* context_, bool createEnumeratedType_, bool createEnumerators_);
    void Visit(otava::ast::EnumSpecifierNode& node) override;
    void Visit(otava::ast::EnumHeadNode& node) override;
    void Visit(otava::ast::EnumBaseNode& node) override;
    void Visit(otava::ast::EnumClassNode& node) override;
    void Visit(otava::ast::EnumStructNode& node) override;
    void Visit(otava::ast::EnumNode& node) override;
    void Visit(otava::ast::EnumeratorDefinitionNode& node) override;
    void Visit(otava::ast::EnumeratorNode& node) override;
    void Visit(otava::ast::ElaboratedEnumSpecifierNode& node) override;
    void Visit(otava::ast::OpaqueEnumDeclarationNode& node) override;
    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::UnnamedNode& node) override;
private:
    Context* context;
    EnumTypeKind enumTypeKind;
    TypeSymbol* underlyingType;
    Scope* scope;
    Value* value;
    int64_t prevValue;
    bool first;
    bool createEnumeratedType;
    bool createEnumerators;
    bool opaque;
};

EnumCreator::EnumCreator(Context* context_, bool createEnumeratedType_, bool createEnumerators_) :
    context(context_), 
    enumTypeKind(EnumTypeKind::enum_), 
    underlyingType(nullptr), 
    scope(context->GetSymbolTable()->CurrentScope()),
    value(nullptr),
    prevValue(0),
    first(false),
    createEnumeratedType(createEnumeratedType_),
    createEnumerators(createEnumerators_),
    opaque(false)
{
}

void EnumCreator::Visit(otava::ast::EnumSpecifierNode& node)
{
    if (createEnumeratedType)
    {
        node.EnumHead()->Accept(*this);
    }
    else if (createEnumerators)
    {
        first = true;
        VisitListContent(node);
    }
}

void EnumCreator::Visit(otava::ast::EnumHeadNode& node)
{
    node.EnumKey()->Accept(*this);
    if (node.EnumBase())
    {
        node.EnumBase()->Accept(*this);
    }
    node.EnumHeadName()->Accept(*this);
}

void EnumCreator::Visit(otava::ast::EnumBaseNode& node)
{
    underlyingType = ResolveType(node.Child(), DeclarationFlags::none, context);
}

void EnumCreator::Visit(otava::ast::EnumClassNode& node)
{
    enumTypeKind = EnumTypeKind::enumClass;
}

void EnumCreator::Visit(otava::ast::EnumStructNode& node)
{
    enumTypeKind = EnumTypeKind::enumStruct;
}

void EnumCreator::Visit(otava::ast::EnumNode& node)
{
    enumTypeKind = EnumTypeKind::enum_;
}

void EnumCreator::Visit(otava::ast::EnumeratorDefinitionNode& node)
{
    if (node.Value())
    {
        value = Evaluate(node.Value(), context);
        if (value && value->IsIntegerValue())
        {
            IntegerValue* integerValue = static_cast<IntegerValue*>(value);
            prevValue = integerValue->GetValue();
        }
        if (first)
        {
            first = false;
        }
    }
    else
    {
        if (first)
        {
            value = context->GetEvaluationContext()->GetIntegerValue(0, util::ToUtf32(std::to_string(0)), 
                context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType));
            prevValue = 0;
            first = false;
        }
        else
        {
            value = context->GetEvaluationContext()->GetIntegerValue(prevValue + 1, util::ToUtf32(std::to_string(prevValue + 1)),
                context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType));
            ++prevValue;
        }
    }
    node.Enumerator()->Accept(*this);
}

void EnumCreator::Visit(otava::ast::EnumeratorNode& node)
{
    node.Identifier()->Accept(*this);
}

void EnumCreator::Visit(otava::ast::ElaboratedEnumSpecifierNode& node)
{
    opaque = true;
    node.Child()->Accept(*this);
    opaque = false;
}

void EnumCreator::Visit(otava::ast::OpaqueEnumDeclarationNode& node)
{
    opaque = true;
    node.EnumKey()->Accept(*this);
    if (node.EnumBase())
    {
        node.EnumBase()->Accept(*this);
    }
    node.EnumHeadName()->Accept(*this);
    opaque = false;
}

void EnumCreator::Visit(otava::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void EnumCreator::Visit(otava::ast::IdentifierNode& node)
{
    if (createEnumeratedType)
    {
        context->GetSymbolTable()->BeginScope(scope);
        if (opaque)
        {
            context->GetSymbolTable()->AddForwardEnumDeclaration(node.Str(), enumTypeKind, underlyingType, &node, context);
        }
        else
        {
            context->GetSymbolTable()->BeginEnumeratedType(node.Str(), enumTypeKind, underlyingType, &node, context);
        }
    }
    if (createEnumerators)
    {
        context->GetSymbolTable()->AddEnumerator(node.Str(), value, &node, context);
    }
}

void EnumCreator::Visit(otava::ast::UnnamedNode& node)
{
    context->GetSymbolTable()->BeginScope(scope);
    context->GetSymbolTable()->BeginEnumeratedType(std::u32string(), enumTypeKind, underlyingType, &node, context);
}

void BeginEnumType(otava::ast::Node* node, Context* context)
{
    EnumCreator creator(context, true, false);
    node->Accept(creator);
}

void AddEnumerators(otava::ast::Node* node, Context* context)
{
    EnumCreator creator(context, false, true);
    node->Accept(creator);
}

void EndEnumType(otava::ast::Node* node, Context* context)
{
    if (!context->GetSymbolTable()->CurrentScope()->GetSymbol()->IsEnumeratedTypeSymbol())
    {
        ThrowException("cpp20.symbols.enums: EndEnumeratedType(): enum scope expected", node->GetSourcePos(), context);
    }
    context->GetSymbolTable()->EndEnumeratedType();
    context->GetSymbolTable()->EndScope();
}

void ProcessEnumForwardDeclaration(otava::ast::Node* node, Context* context)
{
    EnumCreator creator(context, true, false);
    node->Accept(creator);
    context->GetSymbolTable()->EndScope();
}

} // namespace otava::symbols
