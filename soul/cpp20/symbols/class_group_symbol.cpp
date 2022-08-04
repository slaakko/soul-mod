// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.class_group.symbol;

import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.symbol.table;

namespace soul::cpp20::symbols {

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

} // namespace soul::cpp20::symbols
