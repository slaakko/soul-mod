// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================
module;
#include <boost/uuid/uuid.hpp>

module soul.cpp20.symbols.enums;

import util;
import soul.cpp20.ast;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.modules;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.scope.resolver;
import soul.cpp20.symbols.type.resolver;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.value;
import soul.cpp20.symbols.visitor;
import soul.cpp20.symbols.evaluator;

namespace soul::cpp20::symbols {

EnumeratedTypeSymbol::EnumeratedTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::enumTypeSymbol, name_), underlyingType(nullptr), kind(EnumTypeKind::enum_)
{
    GetScope()->SetKind(ScopeKind::enumerationScope);
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

EnumConstantSymbol::EnumConstantSymbol(const std::u32string& name_) : Symbol(SymbolKind::enumConstantSymbol, name_)
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

bool EnumTypeLess::operator()(EnumeratedTypeSymbol* left, EnumeratedTypeSymbol* right) const
{
    return left->Name() < right->Name();
}

class EnumCreator : public soul::cpp20::ast::DefaultVisitor
{
public:
    EnumCreator(Context* context_, bool createEnumeratedType_, bool createEnumerators_);
    void Visit(soul::cpp20::ast::EnumSpecifierNode& node) override;
    void Visit(soul::cpp20::ast::EnumHeadNode& node) override;
    void Visit(soul::cpp20::ast::EnumBaseNode& node) override;
    void Visit(soul::cpp20::ast::EnumClassNode& node) override;
    void Visit(soul::cpp20::ast::EnumStructNode& node) override;
    void Visit(soul::cpp20::ast::EnumNode& node) override;
    void Visit(soul::cpp20::ast::EnumeratorDefinitionNode& node) override;
    void Visit(soul::cpp20::ast::EnumeratorNode& node) override;
    void Visit(soul::cpp20::ast::ElaboratedEnumSpecifierNode& node) override;
    void Visit(soul::cpp20::ast::OpaqueEnumDeclarationNode& node) override;
    void Visit(soul::cpp20::ast::QualifiedIdNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
    void Visit(soul::cpp20::ast::UnnamedNode& node) override;
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
    createEnumerators(createEnumerators_)
{
}

void EnumCreator::Visit(soul::cpp20::ast::EnumSpecifierNode& node)
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

void EnumCreator::Visit(soul::cpp20::ast::EnumHeadNode& node)
{
    node.EnumKey()->Accept(*this);
    if (node.EnumBase())
    {
        node.EnumBase()->Accept(*this);
    }
    node.EnumHeadName()->Accept(*this);
}

void EnumCreator::Visit(soul::cpp20::ast::EnumBaseNode& node)
{
    underlyingType = ResolveType(node.Child(), DeclarationFlags::none, context);
}

void EnumCreator::Visit(soul::cpp20::ast::EnumClassNode& node)
{
    enumTypeKind = EnumTypeKind::enumClass;
}

void EnumCreator::Visit(soul::cpp20::ast::EnumStructNode& node)
{
    enumTypeKind = EnumTypeKind::enumStruct;
}

void EnumCreator::Visit(soul::cpp20::ast::EnumNode& node)
{
    enumTypeKind = EnumTypeKind::enum_;
}

void EnumCreator::Visit(soul::cpp20::ast::EnumeratorDefinitionNode& node)
{
    if (node.Value())
    {
        value = Evaluate(node.Value(), context);
        if (value->IsIntegerValue())
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
            value = context->GetEvaluationContext()->GetIntegerValue(0, util::ToUtf32(std::to_string(0)));
            prevValue = 0;
            first = false;
        }
        else
        {
            value = context->GetEvaluationContext()->GetIntegerValue(prevValue + 1, util::ToUtf32(std::to_string(prevValue + 1)));
            ++prevValue;
        }
    }
    node.Enumerator()->Accept(*this);
}

void EnumCreator::Visit(soul::cpp20::ast::EnumeratorNode& node)
{
    node.Identifier()->Accept(*this);
}

void EnumCreator::Visit(soul::cpp20::ast::ElaboratedEnumSpecifierNode& node)
{
    node.Child()->Accept(*this);
}

void EnumCreator::Visit(soul::cpp20::ast::OpaqueEnumDeclarationNode& node)
{
    node.EnumKey()->Accept(*this);
    if (node.EnumBase())
    {
        node.EnumBase()->Accept(*this);
    }
    node.EnumHeadName()->Accept(*this);
}

void EnumCreator::Visit(soul::cpp20::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void EnumCreator::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    if (createEnumeratedType)
    {
        context->GetSymbolTable()->BeginScope(scope);
        context->GetSymbolTable()->BeginEnumeratedType(node.Str(), enumTypeKind, underlyingType, &node, context);
    }
    if (createEnumerators)
    {
        context->GetSymbolTable()->AddEnumerator(node.Str(), value, &node, context);
    }
}

void EnumCreator::Visit(soul::cpp20::ast::UnnamedNode& node)
{
    context->GetSymbolTable()->BeginScope(scope);
    context->GetSymbolTable()->BeginEnumeratedType(std::u32string(), enumTypeKind, underlyingType, &node, context);
}

void BeginEnumType(soul::cpp20::ast::Node* node, Context* context)
{
    EnumCreator creator(context, true, false);
    node->Accept(creator);
}

void AddEnumerators(soul::cpp20::ast::Node* node, Context* context)
{
    EnumCreator creator(context, false, true);
    node->Accept(creator);
}

void EndEnumType(soul::cpp20::ast::Node* node, Context* context)
{
    if (!context->GetSymbolTable()->CurrentScope()->GetSymbol()->IsEnumeratedTypeSymbol())
    {
        ThrowException("cpp20.symbols.enums: EndEnumeratedType(): enum scope expected", node->GetSourcePos(), context);
    }
    context->GetSymbolTable()->EndEnumeratedType();
    context->GetSymbolTable()->EndScope();
}

} // namespace soul::cpp20::symbols
