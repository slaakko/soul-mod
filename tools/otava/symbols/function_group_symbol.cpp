// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.function.group.symbol;

import otava.symbols.function.symbol;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.symbol.table;
import otava.symbols.type.symbol;

namespace otava::symbols {

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
        case ScopeKind::enumerationScope:
        case ScopeKind::arrayScope:
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

FunctionDefinitionSymbol* FunctionGroupSymbol::GetSingleDefinition()
{
    if (definitions.size() == 1)
    {
        return definitions.front();
    }
    else
    {
        return nullptr;
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
        if (functionDefinition)
        {
            definitions.push_back(functionDefinition);
        }
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
    for (const auto& definition : that->definitions)
    {
        if (std::find(definitions.cbegin(), definitions.cend(), definition) == definitions.end())
        {
            definitions.push_back(definition);
        }
    }
}

FunctionSymbol* FunctionGroupSymbol::ResolveFunction(const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers) const
{
    for (const auto& function : functions)
    {
        if (function->Arity() == parameterTypes.size())
        {
            bool found = (qualifiers & FunctionQualifiers::isConst) == (function->Qualifiers() & FunctionQualifiers::isConst);
            if (found)
            {
                for (int i = 0; i < function->Arity(); ++i)
                {
                    if (!TypesEqual(function->Parameters()[i]->GetType(), parameterTypes[i]))
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
                    if (!TypesEqual(functionDefinition->Parameters()[i]->GetType(), parameterTypes[i]))
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

void FunctionGroupSymbol::CollectViableFunctions(int arity, std::vector<FunctionSymbol*>& viableFunctions, Context* context)
{
    for (const auto& function : functions)
    {
        if (arity >= function->MinMemFunArity(context) && arity <= function->MemFunArity(context))
        {
            if (std::find(viableFunctions.begin(), viableFunctions.end(), function) == viableFunctions.end())
            {
                viableFunctions.push_back(function);
            }
        }
    }
    for (const auto& functionDefinition : definitions)
    {
        if (arity >= functionDefinition->MinMemFunArity(context) && arity <= functionDefinition->MemFunArity(context))
        {
            if (std::find(viableFunctions.begin(), viableFunctions.end(), functionDefinition) == viableFunctions.end())
            {
                viableFunctions.push_back(functionDefinition);
            }
        }
    }
}

} // namespace otava::symbols
