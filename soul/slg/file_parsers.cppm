// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.file.parsers;

import std;
import soul.ast.slg;
import soul.ast.common;
import soul.lexer.file.map;

export namespace soul::slg {

std::unique_ptr<soul::ast::common::TokenFile> ParseTokenFile(const std::string& tokenFilePath, bool external, soul::lexer::FileMap& fileMap);
std::unique_ptr<soul::ast::slg::KeywordFile> ParseKeywordFile(const std::string& keywordFilePath, soul::lexer::FileMap& fileMap);
std::unique_ptr<soul::ast::slg::ExpressionFile> ParseExpressionFile(const std::string& expressionFilePath, soul::lexer::FileMap& fileMap);
std::unique_ptr<soul::ast::slg::LexerFile> ParseLexerFile(const std::string& lexerFilePath, soul::lexer::FileMap& fileMap);
std::unique_ptr<soul::ast::slg::SlgFile> ParseSlgFile(const std::string& slgFilePath, soul::lexer::FileMap& fileMap);

} // namespace soul::slg
