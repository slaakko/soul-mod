// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.code.modifier;

import std;
import soul.ast.cpp;
import soul.ast.common;
import soul.ast.slg;
import soul.lexer;

export namespace soul::slg {

void ModifyCode(soul::ast::cpp::CompoundStatementNode* code, soul::ast::common::TokenMap& tokenMap, soul::ast::slg::LexerFile* lexerFile, soul::lexer::FileMap& fileMap);

} // namespce soul::slg
