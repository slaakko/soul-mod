// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.block;

import otava.symbols.context;
import otava.symbols.visitor;
import otava.symbols.symbol.table;

namespace otava::symbols {

BlockSymbol::BlockSymbol() : ContainerSymbol(SymbolKind::blockSymbol, std::u32string())
{
    GetScope()->SetKind(ScopeKind::blockScope);
}

void BlockSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context)
{
    context->GetSymbolTable()->BeginBlock(sourcePos, context);
}

void EndBlock(Context* context)
{
    context->GetSymbolTable()->EndBlock();
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
