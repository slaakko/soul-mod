// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.file.parsers;

import util;
import soul.lexer;
import soul.parser;
import soul.lex.slg;
import soul.slg.token.file.parser;
import soul.slg.keyword.file.parser;
import soul.slg.expression.file.parser;
import soul.slg.lexer.file.parser;
import soul.slg.slg.file.parser;

namespace soul::slg {

using namespace util;
using namespace soul::lex::slg;
using namespace soul::slg::token::file::parser;
using namespace soul::slg::keyword::file::parser;
using namespace soul::slg::expression::file::parser;
using namespace soul::slg::lexer::file::parser;
using namespace soul::slg::slg::file::parser;

std::unique_ptr<soul::ast::slg::TokenFile> ParseTokenFile(const std::string& tokenFilePath, bool external)
{
    std::string tokenFileContent = ReadFile(tokenFilePath);
    std::u32string content = ToUtf32(tokenFileContent);
    auto lexer = MakeLexer(content.c_str(), content.c_str() + content.length(), tokenFilePath);
    using LexerType = decltype(lexer);
    std::unique_ptr<soul::ast::slg::TokenFile> tokenFile = TokenFileParser<LexerType>::Parse(lexer);
    if (external)
    {
        tokenFile->SetExternal();
    }
    return tokenFile;
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

std::unique_ptr<soul::ast::slg::LexerFile> ParseLexerFile(const std::string& lexerFilePath)
{
    std::string lexerFileContent = ReadFile(lexerFilePath);
    std::u32string content = ToUtf32(lexerFileContent);
    auto lexer = MakeLexer(content.c_str(), content.c_str() + content.length(), lexerFilePath);
    using LexerType = decltype(lexer);
    return LexerFileParser<LexerType>::Parse(lexer);
}

std::unique_ptr<soul::ast::slg::SlgFile> ParseSlgFile(const std::string& slgFilePath)
{
    std::string slgFileContent = ReadFile(slgFilePath);
    std::u32string content = ToUtf32(slgFileContent);
    auto lexer = MakeLexer(content.c_str(), content.c_str() + content.length(), slgFilePath);
    using LexerType = decltype(lexer);
    auto vars = static_cast<LexerType::VariableClassType*>(lexer.GetVariables());
    vars->matchFilePath = true;
    return SlgFileParser<LexerType>::Parse(lexer);
}

} // namespace soul::slg
