// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.spg.nonterminal.info;

namespace soul_expected::spg {

NonterminalInfo::NonterminalInfo(soul_expected::ast::spg::NonterminalParser* nonterminalParser_, bool ptrType_) : 
    nonterminalParser(nonterminalParser_), ptrType(ptrType_), count(0)
{
}

} // namespace soul_expected::spg
