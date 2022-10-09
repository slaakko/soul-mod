// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.alias.group.symbol;

import otava.symbols.alias.type.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.symbol.table;

namespace otava::symbols {

AliasGroupSymbol::AliasGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::aliasGroupSymbol, name_)
{
}

bool AliasGroupSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope: 
        case ScopeKind::templateDeclarationScope: 
        case ScopeKind::classScope: 
        case ScopeKind::blockScope: 
        {
            return true;
        }
    }
    return false;
}

Symbol* AliasGroupSymbol::GetSingleSymbol() 
{
    if (aliasTypeSymbols.size() == 1)
    {
        return aliasTypeSymbols.front();
    }
    else
    {
        return this;
    }
}

void AliasGroupSymbol::AddAliasTypeSymbol(AliasTypeSymbol* aliasTypeSymbol)
{
    aliasTypeSymbols.push_back(aliasTypeSymbol);
}

AliasTypeSymbol* AliasGroupSymbol::GetAliasTypeSymbol(int arity) const
{
    for (const auto& aliasTypeSymbol : aliasTypeSymbols)
    {
        if (aliasTypeSymbol->Arity() == arity)
        {
            return aliasTypeSymbol;
        }
    }
    return nullptr;
}

void AliasGroupSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    uint32_t count = aliasTypeSymbols.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (AliasTypeSymbol* aliasType : aliasTypeSymbols)
    {
        writer.GetBinaryStreamWriter().Write(aliasType->Id());
    }
}

void AliasGroupSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < count; ++i)
    {
        util::uuid aliasTypeId;
        reader.GetBinaryStreamReader().ReadUuid(aliasTypeId);
        aliasTypeIds.push_back(aliasTypeId);
    }
}

void AliasGroupSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    for (const auto& aliasTypeId : aliasTypeIds)
    {
        AliasTypeSymbol* aliasType = symbolTable.GetAliasType(aliasTypeId);
        aliasTypeSymbols.push_back(aliasType);
    }
}

void AliasGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AliasGroupSymbol::Merge(AliasGroupSymbol* that)
{
    for (const auto& aliasType : that->aliasTypeSymbols)
    {
        if (std::find(aliasTypeSymbols.cbegin(), aliasTypeSymbols.cend(), aliasType) == aliasTypeSymbols.end())
        {
            aliasTypeSymbols.push_back(aliasType);
        }
    }
}

} // namespace otava::symbols