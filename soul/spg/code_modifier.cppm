// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.code.modifier;

import std;
import soul.spg.nonterminal.info;
import soul.ast.cpp;
import soul.lexer.file.map;

export namespace soul::spg {

void ModifyCode(soul::ast::cpp::CompoundStatementNode* code, bool ptrType, const std::string& nonterminalName, const std::vector<NonterminalInfo>& nonterminalInfos,
    soul::ast::cpp::TypeIdNode* returnType, bool noDebugSupport, const std::string& currentRuleName, soul::lexer::FileMap& fileMap);

} // namespace soul::spg
