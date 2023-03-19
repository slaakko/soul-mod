// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.block;

import std.core;
import otava.ast.node;
import soul.ast.source.pos;
import otava.symbols.container.symbol;

export namespace otava::symbols {

class BlockSymbol : public ContainerSymbol
{
public:
    BlockSymbol();
    ~BlockSymbol();
    std::string SymbolKindStr() const override { return "block symbol"; }
    std::string SymbolDocKindStr() const override { return "block"; }
    void Accept(Visitor& visitor) override;
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::vector<VariableSymbol*> localVariables;
};

class Context;

BlockSymbol* BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context);
void EndBlock(Context* context);
void RemoveBlock(Context* context);
void MapNode(otava::ast::Node* node, Context* context);

} // namespace otava::symbols
