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
    uint32_t fdCount = definitions.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(fdCount);
    for (FunctionDefinitionSymbol* definition : definitions)
    {
        writer.GetBinaryStreamWriter().Write(definition->Id());
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
    uint32_t fdCount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < fdCount; ++i)
    {
        util::uuid functionDefinitionId;
        reader.GetBinaryStreamReader().ReadUuid(functionDefinitionId);
        functionDefinitionIds.push_back(functionDefinitionId);
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
    for (const auto& functionDefinitionId : functionDefinitionIds)
    {
        FunctionDefinitionSymbol* functionDefinition = symbolTable.GetFunctionDefinition(functionDefinitionId);
        definitions.push_back(functionDefinition);
    }
}

void FunctionGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FunctionGroupSymbol::Merge(FunctionGroupSymbol* that)
{
    for (const auto& function : that->functions)
    {
        if (std::find(functions.cbegin(), functions.cend(), function) == functions.end())
        {
            functions.push_back(function);
        }
    }
}

FunctionSymbol* FunctionGroupSymbol::ResolveFunction(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers) const
{
    for (const auto& function : functions)
    {
        if (function->Arity() == parameterTypes.size())
        {
            bool found = qualifiers == function->Qualifiers();
            if (found)
            {
                for (int i = 0; i < function->Arity(); ++i)
                {
                    if (function->Parameters()[i]->GetType() != parameterTypes[i])
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    return function;
                }
            }
        }
    }
    return nullptr;
}

FunctionDefinitionSymbol* FunctionGroupSymbol::GetFunctionDefinition(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers) const
{
    for (const auto& functionDefinition : definitions)
    {
        if (functionDefinition->Arity() == parameterTypes.size())
        {
            bool found = qualifiers == functionDefinition->Qualifiers();
            if (found)
            {
                for (int i = 0; i < functionDefinition->Arity(); ++i)
                {
                    if (functionDefinition->Parameters()[i]->GetType() != parameterTypes[i])
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    return functionDefinition;
                }
            }
        }
    }
    return nullptr;
}

void FunctionGroupSymbol::AddFunctionDefinition(FunctionDefinitionSymbol* definition_)
{
    definitions.push_back(definition_);
}

void FunctionGroupSymbol::CollectViableFunctions(int arity, std::vector<FunctionSymbol*>& viableFunctions)
{
    for (const auto& function : functions)
    {
        if (function->Arity() == arity)
        {
            viableFunctions.push_back(function);
        }
    }
    for (const auto& functionDefinition : definitions)
    {
        if (functionDefinition->Arity() == arity)
        {
            viableFunctions.push_back(functionDefinition);
        }
    }
}

} // namespace soul::cpp20::symbols
