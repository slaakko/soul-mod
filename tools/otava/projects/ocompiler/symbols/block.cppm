// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.block;

import std;
import otava.ast.node;
import soul.ast.source.pos;
import otava.symbols.container.symbol;
import otava.symbols.classes;
import otava.symbols.context;
import otava.symbols.symbol.table;

export namespace otava::symbols {

class BlockSymbol : public ContainerSymbol
{
public:
    BlockSymbol();
    ~BlockSymbol();
    std::string SymbolKindStr() const override { return "block symbol"; }
    std::string SymbolDocKindStr() const override { return "block"; }
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::vector<VariableSymbol*> localVariables;
};

class Context;

std::expected<BlockSymbol*, int> BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context);
std::expected<bool, int> EndBlock(Context* context);
std::expected<bool, int> RemoveBlock(Context* context);
void MapNode(otava::ast::Node* node, Context* context);

} // namespace otava::symbols
