// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module soul.cpp20.symbols.enum_group.symbol;

import soul.cpp20.symbols.enums;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.visitor;

namespace soul::cpp20::symbols {

EnumGroupSymbol::EnumGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::enumGroupSymbol, name_), enumType(nullptr), forwardDeclaration(nullptr)
{
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
        return nullptr;
    }
}

void EnumGroupSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    if (enumType)
    {
        writer.GetBinaryStreamWriter().Write(enumType->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
    if (forwardDeclaration)
    {
        writer.GetBinaryStreamWriter().Write(forwardDeclaration->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
}

void EnumGroupSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(enumTypeId);
    reader.GetBinaryStreamReader().ReadUuid(fwdDeclId);
}

void EnumGroupSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    if (enumTypeId != util::nil_uuid())
    {
        TypeSymbol* type = symbolTable.GetType(enumTypeId);
        if (type->IsEnumeratedTypeSymbol())
        {
            enumType = static_cast<EnumeratedTypeSymbol*>(type);
        }
        else
        {
            throw std::runtime_error("enum type expected");
        }
    }
    if (fwdDeclId != util::nil_uuid())
    {
        TypeSymbol* type = symbolTable.GetType(enumTypeId);
        if (type->IsForwardEnumDeclarationSymbol())
        {
            forwardDeclaration = static_cast<ForwardEnumDeclarationSymbol*>(type);
        }
        else
        {
            throw std::runtime_error("enum forward declaration expected");
        }
    }
}

void EnumGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}


} // soul::cpp20::symbols