// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.variable.group.symbol;

import soul.cpp20.symbols.variable.symbol;

namespace soul::cpp20::symbols {

VariableGroupSymbol::VariableGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::variableGroupSymbol, name_)
{
}

bool VariableGroupSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
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

Symbol* VariableGroupSymbol::GetSingleSymbol() 
{
    if (variables.size() == 1)
    {
        return variables.front();
    }
    else
    {
        return this;
    }
}

void VariableGroupSymbol::AddVariable(VariableSymbol* variableSymbol)
{
    variables.push_back(variableSymbol);
}

VariableSymbol* VariableGroupSymbol::GetVariable(int arity) const
{
    for (const auto& variable : variables)
    {
        if (variable->Arity() == arity)
        {
            return variable;
        }
    }
    return nullptr;
}

} // namespace soul::cpp20::symbols
