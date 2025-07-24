// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.parsing.util;

import std;
import soul_expected.ast.cpp;
import soul_expected.ast.spg;
import soul_expected.ast.source.pos;
import soul_expected.spg.nonterminal.info;

export namespace soul_expected::spg::parsing::util {

bool IsGetNode(const soul_expected::ast::cpp::IdExprNode& node);
bool IsGetNode(const soul_expected::ast::cpp::TypeNameNode& node);
bool IsContainedBySwitchStatment(const soul_expected::ast::cpp::IdExprNode& node);
bool IsContainedBySwitchStatment(const soul_expected::ast::cpp::TypeNameNode& node);
bool IsListParserNonterminal(const NonterminalInfo& info);
void CountNonterminals(soul_expected::ast::cpp::CompoundStatementNode* code, std::vector<NonterminalInfo>& nonterminalInfos);
soul_expected::ast::spg::Parser* MakeParserFromStrLiteral(const soul_expected::ast::SourcePos& sourcePos, const std::u32string& str);

} // namespace soul_expected::spg
