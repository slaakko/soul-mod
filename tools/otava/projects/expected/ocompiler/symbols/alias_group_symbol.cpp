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

std::string AliasGroupSymbol::SymbolKindStr() const 
{
    return "alias group symbol"; 
}

std::string AliasGroupSymbol::SymbolDocKindStr() const 
{ 
    return "alias_group"; 
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
        Symbol* sym = aliasTypeSymbols.front();
        return sym;
    }
    else
    {
        return this;
    }
}

struct ReferredTypeEqual
{
    ReferredTypeEqual(AliasTypeSymbol* aliasTypeSymbol_, Context* context_) : aliasTypeSymbol(aliasTypeSymbol_), context(context_) {}
    inline bool operator()(AliasTypeSymbol* symbol) const
    {
        return TypesEqual(symbol->ReferredType(), aliasTypeSymbol->ReferredType(), context);
    }
    AliasTypeSymbol* aliasTypeSymbol;
    Context* context;
};

void AliasGroupSymbol::AddAliasTypeSymbol(AliasTypeSymbol* aliasTypeSymbol, Context* context)
{
    ReferredTypeEqual referredTypeEqual(aliasTypeSymbol, context);
    if (std::find(aliasTypeSymbols.begin(), aliasTypeSymbols.end(), aliasTypeSymbol) == aliasTypeSymbols.end() &&
        std::find_if(aliasTypeSymbols.begin(), aliasTypeSymbols.end(), referredTypeEqual) == aliasTypeSymbols.end())
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

std::expected<bool, int> AliasGroupSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    std::uint32_t count = aliasTypeSymbols.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    if (!rv) return rv;
    for (AliasTypeSymbol* aliasType : aliasTypeSymbols)
    {
        rv = writer.GetBinaryStreamWriter().Write(aliasType->Id());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AliasGroupSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> countRv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!countRv) return std::unexpected<int>(countRv.error());
    std::int32_t count = static_cast<std::int32_t>(*countRv);
    for (std::int32_t i = 0; i < count; ++i)
    {
        util::uuid aliasTypeId;
        rv = reader.GetBinaryStreamReader().ReadUuid(aliasTypeId);
        if (!rv) return rv;
        aliasTypeIds.push_back(aliasTypeId);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AliasGroupSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    for (const auto& aliasTypeId : aliasTypeIds)
    {
        std::expected<AliasTypeSymbol*, int> a = symbolTable.GetAliasType(aliasTypeId);
        if (!a) return std::unexpected<int>(a.error());
        AliasTypeSymbol* aliasType = *a;
        AddAliasTypeSymbol(aliasType, context);
    }
    return std::expected<bool, int>(true);
}

void AliasGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AliasGroupSymbol::Merge(AliasGroupSymbol* that, Context* context)
{
    if (this == that) return;
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
