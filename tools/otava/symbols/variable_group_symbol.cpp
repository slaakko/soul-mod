// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.variable.group.symbol;

import otava.symbols.variable.symbol;
import otava.symbols.symbol.table;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;

namespace otava::symbols {

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
    if (std::find(variables.begin(), variables.end(), variableSymbol) == variables.end())
    {
        variables.push_back(variableSymbol);
    }
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

void VariableGroupSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    uint32_t count = variables.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (VariableSymbol* variable : variables)
    {
        writer.GetBinaryStreamWriter().Write(variable->Id());
    }
}

void VariableGroupSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < count; ++i)
    {
        util::uuid variableId;
        reader.GetBinaryStreamReader().ReadUuid(variableId);
        variableIds.push_back(variableId);
    }
}

void VariableGroupSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    for (const auto& variableId : variableIds)
    {
        VariableSymbol* variable = symbolTable.GetVariable(variableId);
        AddVariable(variable);
    }
}

void VariableGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void VariableGroupSymbol::Merge(VariableGroupSymbol* that)
{
    for (const auto& variable : that->variables)
    {
        if (std::find(variables.cbegin(), variables.cend(), variable) == variables.end())
        {
            variables.push_back(variable);
        }
    }
}

} // namespace otava::symbols
