// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.file.parsers;

import std;
import soul.ast.slg;
import soul.ast.common;
import soul.lexer;

export namespace soul::slg {

std::expected<std::unique_ptr<soul::ast::common::TokenFile>, int> ParseTokenFile(const std::string& tokenFilePath, bool external,
    soul::lexer::FileMap& fileMap);
std::expected<std::unique_ptr<soul::ast::slg::KeywordFile>, int> ParseKeywordFile(const std::string& keywordFilePath, soul::lexer::FileMap& fileMap);
std::expected<std::unique_ptr<soul::ast::slg::ExpressionFile>, int> ParseExpressionFile(const std::string& expressionFilePath,
    soul::lexer::FileMap& fileMap);
std::expected<std::unique_ptr<soul::ast::slg::LexerFile>, int> ParseLexerFile(const std::string& lexerFilePath, soul::lexer::FileMap& fileMap);
std::expected<std::unique_ptr<soul::ast::slg::SlgFile>, int> ParseSlgFile(const std::string& slgFilePath, soul::lexer::FileMap& fileMap);

} // namespace soul::slg
