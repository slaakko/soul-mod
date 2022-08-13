// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.function.group.symbol;

import soul.cpp20.symbols.function.symbol;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.visitor;
import soul.cpp20.symbols.symbol.table;

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

void FunctionGroupSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    uint32_t count = functions.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (FunctionSymbol* function : functions)
    {
        writer.GetBinaryStreamWriter().Write(function->Id());
    }
}

void FunctionGroupSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < count; ++i)
    {
        util::uuid functionId;
        reader.GetBinaryStreamReader().ReadUuid(functionId);
        functionIds.push_back(functionId);
    }
}

void FunctionGroupSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    for (const auto& functionId : functionIds)
    {
        FunctionSymbol* function = symbolTable.GetFunction(functionId);
        functions.push_back(function);
    }
}

void FunctionGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace soul::cpp20::symbols
