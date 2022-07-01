// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.class_group.symbol;

import soul.cpp20.symbols.classes;

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

} // namespace soul::cpp20::symbols
