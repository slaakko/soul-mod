// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.visitor;

import soul.cpp20.symbols.alias.group.symbol;
import soul.cpp20.symbols.alias.type.symbol;
import soul.cpp20.symbols.block;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.symbols.concept_group.symbol;
import soul.cpp20.symbols.concepts;
import soul.cpp20.symbols.container.symbol;
import soul.cpp20.symbols.class_group.symbol;
import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.fundamental.type.symbol;
import soul.cpp20.symbols.function.group.symbol;
import soul.cpp20.symbols.function.symbol;
import soul.cpp20.symbols.modules;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.specialization;
import soul.cpp20.symbols.templates;
import soul.cpp20.symbols.type.symbol;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.variable.group.symbol;
import soul.cpp20.symbols.variable.symbol;

namespace soul::cpp20::symbols {

Visitor::Visitor() : visitContainer(true)
{
}

void Visitor::VisitContainer(ContainerSymbol& symbol)
{
    if (!visitContainer) return;
    for (const auto& symbol : symbol.Symbols())
    {
        symbol->Accept(*this);
    }
}

void DefaultVisitor::Visit(Module& module)
{
    if (!module.ExportedModules().empty())
    {
        BeginVisitExports();
        for (Module* exportedModule : module.ExportedModules())
        {
            exportedModule->Accept(*this);
        }
        EndVisitExports();
    }
    if (!module.ImportedModules().empty())
    {
        BeginVisitImports();
        for (Module* importedModule : module.ImportedModules())
        {
            importedModule->Accept(*this);
        }
        EndVisitImports();
    }
    module.GetSymbolTable()->Accept(*this);
}

void DefaultVisitor::Visit(SymbolTable& symbolTable)
{
    symbolTable.GlobalNs()->Accept(*this);
}

void DefaultVisitor::Visit(NamespaceSymbol& symbol)
{
    VisitContainer(symbol);
}

void DefaultVisitor::Visit(AliasGroupSymbol& symbol)
{
    for (const auto& symbol : symbol.AliasTypeSymbols())
    {
        symbol->Accept(*this);
    }
}

void DefaultVisitor::Visit(AliasTypeSymbol& symbol)
{
    SetVisitContainer(false);
    symbol.ReferredType()->Accept(*this);
    SetVisitContainer(true);
}

void DefaultVisitor::Visit(BlockSymbol& symbol)
{
    VisitContainer(symbol);
}

void DefaultVisitor::Visit(ClassGroupSymbol& symbol)
{
    for (const auto& symbol : symbol.Classes())
    {
        symbol->Accept(*this);
    }
}

void DefaultVisitor::Visit(ClassTypeSymbol& symbol)
{
    VisitContainer(symbol);
}

void DefaultVisitor::Visit(CompoundTypeSymbol& symbol)
{
    SetVisitContainer(false);
    symbol.BaseType()->Accept(*this);
    SetVisitContainer(true);
}

void DefaultVisitor::Visit(ConceptGroupSymbol& symbol)
{
    for (const auto& symbol : symbol.Concepts())
    {
        symbol->Accept(*this);
    }
}

void DefaultVisitor::Visit(FunctionGroupSymbol& symbol)
{
    for (const auto& symbol : symbol.Functions())
    {
        symbol->Accept(*this);
    }
}

void DefaultVisitor::Visit(FunctionSymbol& symbol)
{
    VisitContainer(symbol);
    if (symbol.ReturnType())
    {
        SetVisitContainer(false);
        symbol.ReturnType()->Accept(*this);
        SetVisitContainer(true);
    }
}

void DefaultVisitor::Visit(SpecializationSymbol& symbol)
{
    VisitContainer(symbol);
    SetVisitContainer(false);
    symbol.ClassTemplate()->Accept(*this);
    for (const auto& templateArg : symbol.TemplateArguments())
    {
        templateArg->Accept(*this);
    }
    SetVisitContainer(true);
}

void DefaultVisitor::Visit(TemplateParameterSymbol& symbol)
{
    symbol.Constraint()->Accept(*this);
}

void DefaultVisitor::Visit(TemplateDeclarationSymbol& symbol)
{
    VisitContainer(symbol);
}

void DefaultVisitor::Visit(VariableGroupSymbol& symbol)
{
    for (const auto& variable : symbol.Variables())
    {
        variable->Accept(*this);
    }
}

void DefaultVisitor::Visit(VariableSymbol& symbol)
{
    SetVisitContainer(false);
    symbol.GetType()->Accept(*this);
    SetVisitContainer(true);
}

} // namespace soul::cpp20::symbols
