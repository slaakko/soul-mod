// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.block;

import std.core;
import soul.cpp20.ast.node;
import soul.ast.source.pos;
import soul.cpp20.symbols.container.symbol;

export namespace soul::cpp20::symbols {

class BlockSymbol : public ContainerSymbol
{
public:
    BlockSymbol();
    std::string SymbolKindStr() const override { return "block symbol"; }
    std::string SymbolDocKindStr() const override { return "block"; }
    void Accept(Visitor& visitor) override;
};

class Context;

void BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context);
void EndBlock(Context* context);
void RemoveBlock(Context* context);
void MapNode(soul::cpp20::ast::Node* node, Context* context);

} // namespace soul::cpp20::symbols
