// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.nonterminal.info;

namespace soul::spg {

NonterminalInfo::NonterminalInfo(soul::ast::spg::NonterminalParser* nonterminalParser_, bool ptrType_) : nonterminalParser(nonterminalParser_), ptrType(ptrType_), count(0)
{
}

} // namespace soul::spg
