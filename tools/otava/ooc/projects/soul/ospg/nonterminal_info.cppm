// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.nonterminal.info;

import std;
import soul.ast.spg;
import soul.ast.source.pos;

export namespace soul::spg {

struct NonterminalInfo
{
    NonterminalInfo(soul::ast::spg::NonterminalParser* nonterminalParser_, bool ptrType_);
    soul::ast::spg::NonterminalParser* nonterminalParser;
    bool ptrType;
    int count;
    std::vector<soul::ast::SourcePos> sourcePositions;
};

} // namespace soul::spg
