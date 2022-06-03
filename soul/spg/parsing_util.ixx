// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.parsing.util;

import std.core;
import soul.ast.cpp;
import soul.ast.spg;
import soul.ast.source.pos;
import soul.spg.nonterminal.info;

export namespace soul::spg::parsing::util {

bool IsGetNode(const soul::ast::cpp::IdExprNode& node);
bool IsContainedBySwitchStatment(const soul::ast::cpp::IdExprNode& node);
bool IsListParserNonterminal(const NonterminalInfo& info);
void CountNonterminals(soul::ast::cpp::CompoundStatementNode* code, std::vector<NonterminalInfo>& nonterminalInfos);
soul::ast::spg::Parser* MakeParserFromStrLiteral(const soul::ast::SourcePos& sourcePos, const std::u32string& str);

} // namespace soul::spg
