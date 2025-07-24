// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.nonterminal.info;

import std;
import soul_expected.ast.spg;
import soul_expected.ast.source.pos;

export namespace soul_expected::spg {

struct NonterminalInfo
{
    NonterminalInfo(soul_expected::ast::spg::NonterminalParser* nonterminalParser_, bool ptrType_);
    soul_expected::ast::spg::NonterminalParser* nonterminalParser;
    bool ptrType;
    int count;
    std::vector<soul_expected::ast::SourcePos> sourcePositions;
};

} // namespace soul_expected::spg
