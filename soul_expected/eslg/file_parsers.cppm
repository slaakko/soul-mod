// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.slg.file.parsers;

import std;
import soul_expected.ast.slg;
import soul_expected.ast.common;
import soul_expected.lexer;

export namespace soul_expected::slg {

std::expected<std::unique_ptr<soul_expected::ast::common::TokenFile>, int> ParseTokenFile(const std::string& tokenFilePath, bool external, 
    soul_expected::lexer::FileMap& fileMap);
std::expected<std::unique_ptr<soul_expected::ast::slg::KeywordFile>, int> ParseKeywordFile(const std::string& keywordFilePath, soul_expected::lexer::FileMap& fileMap);
std::expected<std::unique_ptr<soul_expected::ast::slg::ExpressionFile>, int> ParseExpressionFile(const std::string& expressionFilePath, 
    soul_expected::lexer::FileMap& fileMap);
std::expected<std::unique_ptr<soul_expected::ast::slg::LexerFile>, int> ParseLexerFile(const std::string& lexerFilePath, soul_expected::lexer::FileMap& fileMap);
std::expected<std::unique_ptr<soul_expected::ast::slg::SlgFile>, int> ParseSlgFile(const std::string& slgFilePath, soul_expected::lexer::FileMap& fileMap);

} // namespace soul_expected::slg
