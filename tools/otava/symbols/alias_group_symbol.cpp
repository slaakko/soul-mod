// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.alias.group.symbol;

import otava.symbols.alias.type.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.symbol.table;
import otava.symbols.type_compare;

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

void AliasGroupSymbol::AddAliasTypeSymbol(AliasTypeSymbol* aliasTypeSymbol, Context* context)
{
    if (std::find(aliasTypeSymbols.begin(), aliasTypeSymbols.end(), aliasTypeSymbol) == aliasTypeSymbols.end() &&
        std::find_if(aliasTypeSymbols.begin(), aliasTypeSymbols.end(), 
            [&](AliasTypeSymbol* symbol) { return TypesEqual(symbol->ReferredType(), aliasTypeSymbol->ReferredType(), context); }) == aliasTypeSymbols.end())
    {
        aliasTypeSymbol->SetGroup(this);
        aliasTypeSymbols.push_back(aliasTypeSymbol);
    }
}

AliasTypeSymbol* AliasGroupSymbol::GetAliasTypeSymbol(int arity) const
{
    for (AliasTypeSymbol* aliasTypeSymbol : aliasTypeSymbols)
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
    std::uint32_t count = aliasTypeSymbols.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (AliasTypeSymbol* aliasType : aliasTypeSymbols)
    {
        writer.GetBinaryStreamWriter().Write(aliasType->Id());
    }
}

void AliasGroupSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    std::uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < count; ++i)
    {
        util::uuid aliasTypeId;
        reader.GetBinaryStreamReader().ReadUuid(aliasTypeId);
        aliasTypeIds.push_back(aliasTypeId);
    }
}

void AliasGroupSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    Symbol::Resolve(symbolTable, context);
    for (const auto& aliasTypeId : aliasTypeIds)
    {
        AliasTypeSymbol* aliasType = symbolTable.GetAliasType(aliasTypeId);
        AddAliasTypeSymbol(aliasType, context);
    }
}

void AliasGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AliasGroupSymbol::Merge(AliasGroupSymbol* that, Context* context)
{
    for (AliasTypeSymbol* aliasType : that->aliasTypeSymbols)
    {
        AddAliasTypeSymbol(aliasType, context);
    }
}

struct ViableAliasTypeGreater
{
    bool operator()(const std::pair<AliasTypeSymbol*, int>& left, const std::pair<AliasTypeSymbol*, int>& right) const
    {
        return left.second > right.second;
    }
};
    
AliasTypeSymbol* AliasGroupSymbol::GetBestMatchingAliasType(const std::vector<Symbol*>& templateArgs, Context* context) const
{
    std::vector<std::pair<AliasTypeSymbol*, int>> viableAliasTypes;
    int arity = templateArgs.size();
    for (AliasTypeSymbol* alias : aliasTypeSymbols)
    {
        if (alias->Arity() == arity)
        {
            bool added = false;
            if (arity == 1)
            {
                if (templateArgs[0]->IsTypeSymbol())
                {
                    TypeSymbol* templateArgType = static_cast<TypeSymbol*>(templateArgs[0]);
                    if (TypesEqual(alias->ReferredType(), templateArgType, context))
                    {
                        viableAliasTypes.push_back(std::make_pair(alias, 1));
                        added = true;
                    }
                }
            }
            if (!added)
            {
                viableAliasTypes.push_back(std::make_pair(alias, 0));
            }
        }
    }
    std::sort(viableAliasTypes.begin(), viableAliasTypes.end(), ViableAliasTypeGreater());
    if (!viableAliasTypes.empty())
    {
        return viableAliasTypes[0].first;
    }
    return nullptr;
}

void AliasGroupSymbol::RemoveAliasType(AliasTypeSymbol* aliasType)
{
    aliasTypeSymbols.erase(std::remove(aliasTypeSymbols.begin(), aliasTypeSymbols.end(), aliasType), aliasTypeSymbols.end());
}

} // namespace otava::symbols
