// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.enum_group.symbol;

import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.visitor;

namespace otava::symbols {

EnumGroupSymbol::EnumGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::enumGroupSymbol, name_), enumType(nullptr), forwardDeclaration(nullptr), enumTypeId(),
    fwdDeclId()
{
}

std::string EnumGroupSymbol::SymbolKindStr() const 
{ 
    return "enum group symbol"; 
}

std::string EnumGroupSymbol::SymbolDocKindStr() const 
{ 
    return "enum_group"; 
}

bool EnumGroupSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
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

Symbol* EnumGroupSymbol::GetSingleSymbol()
{
    if (enumType)
    {
        return enumType;
    }
    else if (forwardDeclaration)
    {
        return forwardDeclaration;
    }
    else
    {
        return this;
    }
}

std::expected<bool, int> EnumGroupSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    if (enumType)
    {
        rv = writer.GetBinaryStreamWriter().Write(enumType->Id());
        if (!rv) return rv;
    }
    else
    {
        rv = writer.GetBinaryStreamWriter().Write(util::nil_uuid());
        if (!rv) return rv;
    }
    if (forwardDeclaration)
    {
        rv = writer.GetBinaryStreamWriter().Write(forwardDeclaration->Id());
        if (!rv) return rv;
    }
    else
    {
        rv = writer.GetBinaryStreamWriter().Write(util::nil_uuid());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumGroupSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(fwdDeclId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumGroupSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    if (enumTypeId != util::nil_uuid())
    {
        TypeSymbol* type = symbolTable.GetType(enumTypeId);
        if (type && type->IsEnumeratedTypeSymbol())
        {
            enumType = static_cast<EnumeratedTypeSymbol*>(type);
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("enum group symbol: enum type expected"));
        }
    }
    if (fwdDeclId != util::nil_uuid())
    {
        TypeSymbol* type = symbolTable.GetType(fwdDeclId);
        if (type && type->IsForwardEnumDeclarationSymbol())
        {
            forwardDeclaration = static_cast<ForwardEnumDeclarationSymbol*>(type);
        }
        else
        {
            return std::unexpected<int>(util::AllocateError("enum group symbol: enum forward declaration expected"));
        }
    }
    return std::expected<bool, int>(true);
}

void EnumGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void EnumGroupSymbol::Merge(EnumGroupSymbol* that)
{
    if (this == that) return;
    if (!enumType && that->enumType)
    {
        enumType = that->enumType;
    }
    if (!forwardDeclaration && that->forwardDeclaration)
    {
        forwardDeclaration = that->forwardDeclaration;
    }
}

} // otava::symbols