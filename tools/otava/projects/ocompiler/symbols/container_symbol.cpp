// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.container.symbol;

import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.type.symbol;
import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.variable.symbol;
import otava.symbols.conversion.table;
import otava.symbols.function.group.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.alias.group.symbol;
import otava.symbols.error;
import otava.symbols.concepts;
import soul.xml.dom;
import util.unicode;

namespace otava::symbols {

ContainerSymbol::ContainerSymbol(SymbolKind kind_, const std::u32string& name_) : Symbol(kind_, name_)
{
    scope.SetContainerSymbol(this);
}

ContainerSymbol::ContainerSymbol(SymbolKind kind_, const util::uuid& id_, const std::u32string& name_) : Symbol(kind_, id_, name_)
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
        scope.Install(symbol, context);
    }
    members.push_back(std::unique_ptr<Symbol>(symbol));
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
    else if (symbol->IsVariableSymbol())
    {
        VariableSymbol* variable = static_cast<VariableSymbol*>(symbol);
        context->GetSymbolTable()->MapVariable(variable);
    }
    else if (symbol->IsFunctionGroupSymbol())
    {
        FunctionGroupSymbol* functionGroup = static_cast<FunctionGroupSymbol*>(symbol);
        context->GetSymbolTable()->MapFunctionGroup(functionGroup);
    }
    else if (symbol->IsClassGroupSymbol())
    {
        ClassGroupSymbol* classGroup = static_cast<ClassGroupSymbol*>(symbol);
        context->GetSymbolTable()->MapClassGroup(classGroup);
    }
    else if (symbol->IsAliasGroupSymbol())
    {
        AliasGroupSymbol* aliasGroup = static_cast<AliasGroupSymbol*>(symbol);
        context->GetSymbolTable()->MapAliasGroup(aliasGroup);
    }
    else if (symbol->IsConceptSymbol())
    {
        ConceptSymbol* cncp = static_cast<ConceptSymbol*>(symbol);
        context->GetSymbolTable()->MapConcept(cncp);
    }
    else if (symbol->IsTypenameConstraintSymbol())
    {
        context->GetSymbolTable()->SetTypenameConstraintSymbol(symbol);
    }
    else if (symbol->IsErrorTypeSymbol())
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
    for (std::vector<std::unique_ptr<Symbol>>::iterator i = members.begin(); i != members.end(); ++i)
    {
        if (i->get() == symbol)
        {
            symbol = i->release();
            members.erase(i);
            return std::unique_ptr<Symbol>(symbol);
        }
    }
    return std::unique_ptr<Symbol>();
}

std::expected<bool, int> ContainerSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    std::uint32_t count = static_cast<std::uint32_t>(members.size());
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    if (!rv) return rv;
    for (const auto& symbol : members)
    {
        rv = writer.Write(symbol.get());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ContainerSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::int32_t count = static_cast<std::int32_t>(*urv);
    for (std::int32_t i = 0; i < count; ++i)
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* symbol = *srv;
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
            std::expected<std::string, int> name = util::ToUtf8(Name());
            if (!name) return std::unexpected<int>(name.error());
            return std::unexpected<int>(util::AllocateError("ContainerSymbol::read: '" + *name + "': null symbol read"));
        }
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ContainerSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    for (const auto& symbol : members)
    {
        rv = symbol->Resolve(symbolTable, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<soul::xml::Element*, int> ContainerSymbol::ToXml() const
{
    std::expected<soul::xml::Element*, int> rv = Symbol::ToXml();
    if (!rv) return rv;
    soul::xml::Element* element = *rv;
    for (const auto& symbol : members)
    {
        rv = symbol->ToXml();
        if (!rv) return rv;
        soul::xml::Element* child = *rv;
        std::expected<bool, int> arv = element->AppendChild(child);
        if (!arv) return std::unexpected<int>(arv.error());
    }
    return std::expected<soul::xml::Element*, int>(element);
}

} // namespace otava::symbols
