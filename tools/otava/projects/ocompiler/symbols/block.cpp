// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.block;

import otava.symbols.context;
import otava.symbols.visitor;
import otava.symbols.symbol.table;
import otava.symbols.variable.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;

namespace otava::symbols {

BlockSymbol::BlockSymbol() : ContainerSymbol(SymbolKind::blockSymbol, std::u32string())
{
    GetScope()->SetKind(ScopeKind::blockScope);
}

BlockSymbol::~BlockSymbol()
{
    FunctionSymbol* function = ParentFunction();
    if (function)
    {
        for (VariableSymbol* variable : localVariables)
        {
            function->RemoveLocalVariable(variable);
        }
    }
}

void BlockSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BlockSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ContainerSymbol::AddSymbol(symbol, sourcePos, context);
    if (symbol->IsVariableSymbol())
    {
        VariableSymbol* variable = static_cast<VariableSymbol*>(symbol);
        if (variable->IsLocalVariable())
        {
            localVariables.push_back(variable);
            FunctionSymbol* function = ParentFunction();
            if (function)
            {
                function->AddLocalVariable(variable);
            }
        }
    }
}

BlockSymbol* BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context)
{
    return context->GetSymbolTable()->BeginBlock(sourcePos, context);
}

void EndBlock(Context* context)
{
    context->GetSymbolTable()->EndBlock(context);
}

void RemoveBlock(Context* context)
{
    context->GetSymbolTable()->RemoveBlock();
}

void MapNode(otava::ast::Node* node, Context* context)
{
    context->GetSymbolTable()->MapNode(node);
}

} // namespace otava::symbols
