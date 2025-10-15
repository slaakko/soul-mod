// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.enum_group.symbol;

import otava.symbols.enums;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.symbol.table;
import otava.symbols.visitor;
import otava.ast.error;

namespace otava::symbols {

EnumGroupSymbol::EnumGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::enumGroupSymbol, name_), enumType(nullptr), forwardDeclaration(nullptr), enumTypeId(),
    fwdDeclId()
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
        return this;
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

void EnumGroupSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    Symbol::Resolve(symbolTable, context);
    if (enumTypeId != util::nil_uuid())
    {
        TypeSymbol* type = symbolTable.GetType(enumTypeId);
        if (type && type->IsEnumeratedTypeSymbol())
        {
            enumType = static_cast<EnumeratedTypeSymbol*>(type);
        }
        else
        {
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("enum group symbol: enum type expected");
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
            otava::ast::SetExceptionThrown();
            throw std::runtime_error("enum group symbol: enum forward declaration expected");
        }
    }
}

void EnumGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void EnumGroupSymbol::Merge(EnumGroupSymbol* that)
{
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