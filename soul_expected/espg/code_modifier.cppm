// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.code.modifier;

import std;
import soul_expected.spg.nonterminal.info;
import soul_expected.ast.cpp;
import soul_expected.lexer.file.map;

export namespace soul_expected::spg {

std::expected<bool, int> ModifyCode(soul_expected::ast::cpp::CompoundStatementNode* code, bool ptrType, const std::string& nonterminalName,
    const std::vector<NonterminalInfo>& nonterminalInfos,
    soul_expected::ast::cpp::TypeIdNode* returnType, bool noDebugSupport, const std::string& currentRuleName, soul_expected::lexer::FileMap& fileMap);

} // namespace soul_expected::spg
