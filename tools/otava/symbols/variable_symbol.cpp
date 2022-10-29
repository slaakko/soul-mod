// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module otava.symbols.variable.symbol;

import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.alias.type.symbol;
import otava.symbols.type.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.value;
import otava.symbols.visitor;

namespace otava::symbols {

VariableSymbol::VariableSymbol(const std::u32string& name_) : 
    Symbol(SymbolKind::variableSymbol, name_), 
    declaredType(nullptr),
    declaredTypeId(util::nil_uuid()),
    initializerType(nullptr),
    initializerTypeId(util::nil_uuid()),
    value(nullptr),
    valueId(util::nil_uuid()),
    layoutIndex(-1)
{
}

void VariableSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(declaredType->Id());
    if (initializerType)
    {
        writer.GetBinaryStreamWriter().Write(initializerType->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
    bool hasValue = value != nullptr;
    writer.GetBinaryStreamWriter().Write(hasValue);
    if (hasValue)
    {
        writer.GetBinaryStreamWriter().Write(value->Id());
    }
    writer.GetBinaryStreamWriter().Write(layoutIndex);
}

void VariableSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(declaredTypeId);
    reader.GetBinaryStreamReader().ReadUuid(initializerTypeId);
    bool hasValue = reader.GetBinaryStreamReader().ReadBool();
    if (hasValue)
    {
        reader.GetBinaryStreamReader().ReadUuid(valueId);
    }
    layoutIndex = reader.GetBinaryStreamReader().ReadInt();
}

void VariableSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    declaredType = symbolTable.GetType(declaredTypeId);
    if (initializerTypeId != util::nil_uuid())
    {
        initializerType = symbolTable.GetType(initializerTypeId);
    }
    if (valueId != util::nil_uuid())
    {
        EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
        value = evaluationContext->GetValue(valueId);
    }
}

void VariableSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

bool VariableSymbol::IsLocalVariable() const
{
    return Parent()->IsFunctionSymbol() || Parent()->IsBlockSymbol();
}

bool VariableSymbol::IsMemberVariable() const
{
    return Parent()->IsClassTypeSymbol();
}

bool VariableSymbol::IsGlobalVariable() const
{
    return Parent()->IsNamespaceSymbol();
}

void VariableSymbol::SetInitializerType(TypeSymbol* initializerType_)
{
    initializerType = initializerType_;
}

TypeSymbol* VariableSymbol::GetType() const
{
    if (declaredType->IsAutoTypeSymbol())
    {
        return initializerType;
    }
    else
    {
        return declaredType;
    }
}

TypeSymbol* VariableSymbol::GetReferredType() const
{
    TypeSymbol* referredType = GetType();
    while (referredType->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(referredType);
        referredType = aliasType->ReferredType();
    }
    return referredType;
}

bool VariableLess::operator()(VariableSymbol* left, VariableSymbol* right) const
{
    return left->Name() < right->Name();
}

} // namespace otava::symbols
