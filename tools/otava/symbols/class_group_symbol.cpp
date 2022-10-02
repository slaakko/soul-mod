// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.class_group.symbol;

import otava.symbols.classes;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.symbol.table;

namespace otava::symbols {

ClassGroupSymbol::ClassGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::classGroupSymbol, name_)
{
}

bool ClassGroupSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
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

void ClassGroupSymbol::AddClass(ClassTypeSymbol* classTypeSymbol)
{
    classes.push_back(classTypeSymbol);
}

Symbol* ClassGroupSymbol::GetSingleSymbol() 
{
    if (classes.size() == 1)
    {
        return classes.front();
    }
    else if (forwardDeclarations.size() == 1)
    {
        return forwardDeclarations.front();
    }
    else
    {
        return this;
    }
}

ClassTypeSymbol* ClassGroupSymbol::GetClass(int arity) const
{
    for (const auto& classTypeSymbol : classes)
    {
        if (classTypeSymbol->Arity() == arity)
        {
            return classTypeSymbol;
        }
    }
    return nullptr;
}

void ClassGroupSymbol::AddForwardDeclaration(ForwardClassDeclarationSymbol* forwardDeclaration)
{
    forwardDeclarations.push_back(forwardDeclaration);
}

ForwardClassDeclarationSymbol* ClassGroupSymbol::GetForwardDeclaration(int arity) const
{
    for (const auto& forwardDeclaration : forwardDeclarations)
    {
        if (forwardDeclaration->Arity() == arity)
        {
            return forwardDeclaration;
        }
    }
    return nullptr;
}

void ClassGroupSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    uint32_t count = classes.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (ClassTypeSymbol* cls : classes)
    {
        writer.GetBinaryStreamWriter().Write(cls->Id());
    }
}

void ClassGroupSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < count; ++i)
    {
        util::uuid classId;
        reader.GetBinaryStreamReader().ReadUuid(classId);
        classIds.push_back(classId);
    }
}

void ClassGroupSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    for (const auto& classId : classIds)
    {
        ClassTypeSymbol* cls = symbolTable.GetClass(classId);
        classes.push_back(cls);
    }
}

void ClassGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ClassGroupSymbol::Merge(ClassGroupSymbol* that)
{
    for (const auto& cls : that->classes)
    {
        if (std::find(classes.cbegin(), classes.cend(), cls) == classes.end())
        {
            classes.push_back(cls);
        }
    }
    for (const auto& fwd : that->forwardDeclarations)
    {
        if (std::find(forwardDeclarations.cbegin(), forwardDeclarations.cend(), fwd) == forwardDeclarations.end())
        {
            forwardDeclarations.push_back(fwd);
        }
    }
}

} // namespace otava::symbols
