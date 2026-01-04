// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.visitor;

import otava.symbols.alias.group.symbol;
import otava.symbols.alias.type.symbol;
import otava.symbols.alias.type.templates;
import otava.symbols.block;
import otava.symbols.compound.type.symbol;
import otava.symbols.concept_group.symbol;
import otava.symbols.concepts;
import otava.symbols.container.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.classes;
import otava.symbols.class_templates;
import otava.symbols.inline_functions;
import otava.symbols.enums;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.modules;
import otava.symbols.namespaces;
import otava.symbols.templates;
import otava.symbols.type.symbol;
import otava.symbols.symbol.table;
import otava.symbols.variable.group.symbol;
import otava.symbols.variable.symbol;

namespace otava::symbols {

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

void DefaultVisitor::Visit(AliasTypeSymbol& symbol)
{
    SetVisitContainer(false);
    symbol.ReferredType()->Accept(*this);
    SetVisitContainer(true);
}

void DefaultVisitor::Visit(AliasTypeTemplateSpecializationSymbol& symbol)
{
    SetVisitContainer(false);
    symbol.ReferredType()->Accept(*this);
    SetVisitContainer(true);
}

void DefaultVisitor::Visit(BlockSymbol& symbol)
{
    VisitContainer(symbol);
}

void DefaultVisitor::Visit(ClassTypeSymbol& symbol)
{
    VisitContainer(symbol);
}

void DefaultVisitor::Visit(EnumeratedTypeSymbol& symbol)
{
    VisitContainer(symbol);
}

void DefaultVisitor::Visit(CompoundTypeSymbol& symbol)
{
    SetVisitContainer(false);
    symbol.BaseType()->Accept(*this);
    SetVisitContainer(true);
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

void DefaultVisitor::Visit(ClassTemplateSpecializationSymbol& symbol)
{
    VisitContainer(symbol);
    SetVisitContainer(false);
    symbol.ClassTemplate()->Accept(*this);
    for (Symbol* templateArg : symbol.TemplateArguments())
    {
        templateArg->Accept(*this);
    }
    SetVisitContainer(true);
}

void DefaultVisitor::Visit(TemplateParameterSymbol& symbol)
{
    if (symbol.Constraint())
    {
        symbol.Constraint()->Accept(*this);
    }
    if (symbol.GetParameterSymbol())
    {
        symbol.GetParameterSymbol()->Accept(*this);
    }
}

void DefaultVisitor::Visit(TemplateDeclarationSymbol& symbol)
{
    VisitContainer(symbol);
}

void DefaultVisitor::Visit(VariableSymbol& symbol)
{
    SetVisitContainer(false);
    symbol.GetDeclaredType()->Accept(*this);
    SetVisitContainer(true);
}

} // namespace otava::symbols
