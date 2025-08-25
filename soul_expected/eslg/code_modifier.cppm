// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.slg.code.modifier;

import std;
import soul_expected.ast.cpp;
import soul_expected.ast.common;
import soul_expected.ast.slg;
import soul_expected.lexer;

export namespace soul_expected::slg {

std::expected<bool, int> ModifyCode(
    soul_expected::ast::cpp::CompoundStatementNode* code, soul_expected::ast::common::TokenMap& tokenMap, soul_expected::ast::slg::LexerFile* lexerFile, 
    soul_expected::lexer::FileMap& fileMap);

} // namespce soul::slg
