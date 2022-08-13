// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.block;

import soul.cpp20.symbols.context;
import soul.cpp20.symbols.visitor;
import soul.cpp20.symbols.symbol.table;

namespace soul::cpp20::symbols {

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

void MapNode(soul::cpp20::ast::Node* node, Context* context)
{
    context->GetSymbolTable()->MapNode(node);
}

} // namespace soul::cpp20::symbols
