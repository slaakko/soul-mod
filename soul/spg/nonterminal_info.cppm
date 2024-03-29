// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.nonterminal.info;

import std.core;
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
