// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.container.symbol;

import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.function.symbol;
import otava.symbols.type.symbol;
import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.variable.symbol;
import otava.symbols.conversion.table;
import otava.symbols.function.group.symbol;
import otava.symbols.exception;
import otava.symbols.concepts;
import util.unicode;

namespace otava::symbols {

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
        if (function->IsConversion())
        {
            context->GetSymbolTable()->GetConversionTable().AddConversion(function);
        }
    }
    if (symbol->IsFunctionDefinitionSymbol())
    {
        FunctionDefinitionSymbol* functionDefinition = static_cast<FunctionDefinitionSymbol*>(symbol);
        context->GetSymbolTable()->MapFunctionDefinition(functionDefinition);
        if (functionDefinition->IsConversion())
        {
            context->GetSymbolTable()->GetConversionTable().AddConversion(functionDefinition);
        }
    }
    if (symbol->IsVariableSymbol())
    {
        VariableSymbol* variable = static_cast<VariableSymbol*>(symbol);
        context->GetSymbolTable()->MapVariable(variable);
    }
    if (symbol->IsFunctionGroupSymbol())
    {
        FunctionGroupSymbol* functionGroup = static_cast<FunctionGroupSymbol*>(symbol);
        context->GetSymbolTable()->MapFunctionGroup(functionGroup);
    }
    if (symbol->IsConceptSymbol())
    {
        ConceptSymbol* cncp = static_cast<ConceptSymbol*>(symbol);
        context->GetSymbolTable()->MapConcept(cncp);
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
        if (symbol)
        {
            AddSymbol(symbol, soul::ast::SourcePos(), reader.GetContext());
            if (symbol->IsFunctionDefinitionSymbol())
            {
                FunctionDefinitionSymbol* functionDefinition = static_cast<FunctionDefinitionSymbol*>(symbol);
                Context* context = reader.GetContext();
                context->GetFunctionDefinitionSymbolSet()->AddFunctionDefinitionSymbol(functionDefinition);
            }
        }
        else
        {
            SetExceptionThrown();
            throw std::runtime_error("ContainerSymbol::read: '" + util::ToUtf8(Name()) + "': null symbol read");
        }
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

} // namespace otava::symbols
