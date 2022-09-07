// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.container.symbol;

import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.fundamental.type.symbol;
import soul.cpp20.symbols.function.symbol;
import soul.cpp20.symbols.type.symbol;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.variable.symbol;

namespace soul::cpp20::symbols {

ContainerSymbol::ContainerSymbol(SymbolKind kind_, const std::u32string& name_) : Symbol(kind_, name_)
{
    scope.SetContainerSymbol(this);
}

void ContainerSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    symbol->SetParent(this);
    Scope* childScope = symbol->GetScope();
    if (childScope)
    {
        childScope->AddParentScope(&scope);
    }
    if (symbol->CanInstall())
    {
        scope.Install(symbol);
    }
    symbols.push_back(std::unique_ptr<Symbol>(symbol));
    if (symbol->IsTypeSymbol())
    {
        TypeSymbol* typeSymbol = static_cast<TypeSymbol*>(symbol);
        context->GetSymbolTable()->MapType(typeSymbol);
    }
    if (symbol->IsFundamentalTypeSymbol())
    {
        FundamentalTypeSymbol* fundamentalTypeSymbol = static_cast<FundamentalTypeSymbol*>(symbol);
        context->GetSymbolTable()->MapFundamentalType(fundamentalTypeSymbol);
    }
    if (symbol->IsFunctionSymbol())
    {
        FunctionSymbol* function = static_cast<FunctionSymbol*>(symbol);
        context->GetSymbolTable()->MapFunction(function);
    }
    if (symbol->IsFunctionDefinitionSymbol())
    {
        FunctionDefinitionSymbol* functionDefinition = static_cast<FunctionDefinitionSymbol*>(symbol);
        context->GetSymbolTable()->MapFunctionDefinition(functionDefinition);
    }
    if (symbol->IsVariableSymbol())
    {
        VariableSymbol* variable = static_cast<VariableSymbol*>(symbol);
        context->GetSymbolTable()->MapVariable(variable);
    }
    if (symbol->IsTypenameConstraintSymbol())
    {
        context->GetSymbolTable()->SetTypenameConstraintSymbol(symbol);
    }
    if (symbol->IsErrorTypeSymbol())
    {
        ErrorTypeSymbol* errorSymbol = static_cast<ErrorTypeSymbol*>(symbol);
        context->GetSymbolTable()->SetErrorTypeSymbol(errorSymbol);
    }
}

std::unique_ptr<Symbol> ContainerSymbol::RemoveSymbol(Symbol* symbol)
{
    if (symbol->CanInstall())
    {
        scope.Uninstall(symbol);
    }
    for (std::vector<std::unique_ptr<Symbol>>::iterator i = symbols.begin(); i != symbols.end(); ++i)
    {
        if (i->get() == symbol)
        {
            symbol = i->release();
            symbols.erase(i);
            return std::unique_ptr<Symbol>(symbol);
        }
    }
    return std::unique_ptr<Symbol>();
}

void ContainerSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    uint32_t count = symbols.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (uint32_t i = 0; i < count; ++i)
    {
        Symbol* symbol = symbols[i].get();
        writer.Write(symbol);
    }
}

void ContainerSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < count; ++i)
    {
        Symbol* symbol = reader.ReadSymbol();
        AddSymbol(symbol, soul::ast::SourcePos(), reader.GetContext());
    }
}

void ContainerSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    for (const auto& symbol : symbols)
    {
        symbol->Resolve(symbolTable);
    }
}

} // namespace soul::cpp20::symbols
