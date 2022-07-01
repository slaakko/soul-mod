// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.function.group.symbol;

import soul.cpp20.symbols.function.symbol;

namespace soul::cpp20::symbols {

FunctionGroupSymbol::FunctionGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::functionGroupSymbol, name_)
{
}

bool FunctionGroupSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope: 
        case ScopeKind::templateDeclarationScope: 
        case ScopeKind::classScope: 
        {
            return true;
        }
    }
    return false;
}

Symbol* FunctionGroupSymbol::GetSingleSymbol() 
{
    if (functions.size() == 1)
    {
        return functions.front();
    }
    else
    {
        return this;
    }
}

void FunctionGroupSymbol::AddFunction(FunctionSymbol* function)
{
    functions.push_back(function);
}

} // namespace soul::cpp20::symbols
