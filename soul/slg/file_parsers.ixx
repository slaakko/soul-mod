// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.file.parsers;

import std.core;
import soul.ast.slg;

export namespace soul::slg {

std::unique_ptr<soul::ast::slg::TokenFile> ParseTokenFile(const std::string& tokenFilePath);
std::unique_ptr<soul::ast::slg::KeywordFile> ParseKeywordFile(const std::string& keywordFilePath);
std::unique_ptr<soul::ast::slg::ExpressionFile> ParseExpressionFile(const std::string& expressionFilePath);

} // namespace soul::slg
