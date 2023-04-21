// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.file.parsers;

import std.core;
import soul.ast.slg;

export namespace soul::slg {

std::unique_ptr<soul::ast::slg::TokenFile> ParseTokenFile(const std::string& tokenFilePath, bool external);
std::unique_ptr<soul::ast::slg::KeywordFile> ParseKeywordFile(const std::string& keywordFilePath);
std::unique_ptr<soul::ast::slg::ExpressionFile> ParseExpressionFile(const std::string& expressionFilePath);
std::unique_ptr<soul::ast::slg::LexerFile> ParseLexerFile(const std::string& lexerFilePath);
std::unique_ptr<soul::ast::slg::SlgFile> ParseSlgFile(const std::string& slgFilePath);

} // namespace soul::slg
