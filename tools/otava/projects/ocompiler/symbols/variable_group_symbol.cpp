// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.variable.group.symbol;

import otava.symbols.variable.symbol;
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
    for (VariableSymbol* variable : variables)
    {
        if (variable->Arity() == arity)
        {
            return variable;
        }
    }
    return nullptr;
}

std::expected<bool, int> VariableGroupSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    std::uint32_t count = variables.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    if (!rv) return rv;
    for (VariableSymbol* variable : variables)
    {
        rv = writer.GetBinaryStreamWriter().Write(variable->Id());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> VariableGroupSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t count = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(count); ++i)
    {
        util::uuid variableId;
        rv = reader.GetBinaryStreamReader().ReadUuid(variableId);
        if (!rv) return rv;
        variableIds.push_back(variableId);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> VariableGroupSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    for (const auto& variableId : variableIds)
    {
        std::expected<VariableSymbol*, int> v = symbolTable.GetVariable(variableId);
        if (!v) return std::unexpected<int>(v.error());
        VariableSymbol* variable = *v;
        AddVariable(variable);
    }
    return std::expected<bool, int>(true);
}

void VariableGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void VariableGroupSymbol::Merge(VariableGroupSymbol* that)
{
    for (VariableSymbol* variable : that->variables)
    {
        if (std::find(variables.cbegin(), variables.cend(), variable) == variables.end())
        {
            variables.push_back(variable);
        }
    }
}

} // namespace otava::symbols
