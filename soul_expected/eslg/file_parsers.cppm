// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.slg.file.parsers;

import std;
import soul_expected.ast.slg;

export namespace soul_expected::slg {

std::expected<std::unique_ptr<soul_expected::ast::slg::TokenFile>, int> ParseTokenFile(const std::string& tokenFilePath, bool external);
std::expected<std::unique_ptr<soul_expected::ast::slg::KeywordFile>, int> ParseKeywordFile(const std::string& keywordFilePath);
std::expected<std::unique_ptr<soul_expected::ast::slg::ExpressionFile>, int> ParseExpressionFile(const std::string& expressionFilePath);
std::expected<std::unique_ptr<soul_expected::ast::slg::LexerFile>, int> ParseLexerFile(const std::string& lexerFilePath);
std::expected<std::unique_ptr<soul_expected::ast::slg::SlgFile>, int> ParseSlgFile(const std::string& slgFilePath);

} // namespace soul_expected::slg
