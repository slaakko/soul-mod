// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.file.parsers;

import util;
import soul.slg.lex;
import soul.slg.token.file.par;
import soul.slg.keyword.file.par;
import soul.slg.expression.file.par;

namespace soul::slg {

using namespace util;
using namespace soul::slg::lex;
using namespace soul::slg::token::file::par;
using namespace soul::slg::keyword::file::par;
using namespace soul::slg::expression::file::par;

std::unique_ptr<soul::ast::slg::TokenFile> ParseTokenFile(const std::string& tokenFilePath)
{
    std::string tokenFileContent = ReadFile(tokenFilePath);
    std::u32string content = ToUtf32(tokenFileContent);
    auto lexer = MakeLexer(content.c_str(), content.c_str() + content.length(), tokenFilePath);
    using LexerType = decltype(lexer);
    return TokenFileParser<LexerType>::Parse(lexer);
}

std::unique_ptr<soul::ast::slg::KeywordFile> ParseKeywordFile(const std::string& keywordFilePath)
{
    std::string keywordFileContent = ReadFile(keywordFilePath);
    std::u32string content = ToUtf32(keywordFileContent);
    auto lexer = MakeLexer(content.c_str(), content.c_str() + content.length(), keywordFilePath);
    using LexerType = decltype(lexer);
    return KeywordFileParser<LexerType>::Parse(lexer);
}

std::unique_ptr<soul::ast::slg::ExpressionFile> ParseExpressionFile(const std::string& expressionFilePath)
{
    std::string expressionFileContent = ReadFile(expressionFilePath);
    std::u32string content = ToUtf32(expressionFileContent);
    auto lexer = MakeLexer(content.c_str(), content.c_str() + content.length(), expressionFilePath);
    using LexerType = decltype(lexer);
    return ExpressionFileParser<LexerType>::Parse(lexer);
}

} // namespace soul::slg
