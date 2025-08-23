// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.file.parsers;

import std;
import soul.ast.slg;
import soul.ast.common;

export namespace soul::slg {

std::unique_ptr<soul::ast::common::TokenFile> ParseTokenFile(const std::string& tokenFilePath, bool external);
std::unique_ptr<soul::ast::slg::KeywordFile> ParseKeywordFile(const std::string& keywordFilePath);
std::unique_ptr<soul::ast::slg::ExpressionFile> ParseExpressionFile(const std::string& expressionFilePath);
std::unique_ptr<soul::ast::slg::LexerFile> ParseLexerFile(const std::string& lexerFilePath);
std::unique_ptr<soul::ast::slg::SlgFile> ParseSlgFile(const std::string& slgFilePath);

} // namespace soul::slg
