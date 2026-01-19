// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.file.parsers;

import util;
import soul.lexer;
import soul.parser;
import soul.lex.slg;
import soul.cpp.token;
import soul.common.token.file.parser;
import soul.slg.keyword.file.parser;
import soul.slg.expression.file.parser;
import soul.slg.lexer.file.parser;
import soul.slg.slg.file.parser;

namespace soul::slg {

std::unique_ptr<soul::ast::common::TokenFile> ParseTokenFile(const std::string& tokenFilePath, bool external, soul::lexer::FileMap& fileMap)
{
    std::int32_t file = fileMap.MapFile(tokenFilePath);
    std::string tokenFileContent = util::ReadFile(tokenFilePath);
    std::u32string content = util::ToUtf32(tokenFileContent);
    auto lxr = soul::lex::slg::MakeLexer(content.c_str(), content.c_str() + content.length(), tokenFilePath);
    lxr.SetFile(file);
    //lxr.SetRuleNameMapPtr(soul::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lxr);
    std::unique_ptr<soul::ast::common::TokenFile> tokenFile = soul::common::token::file::parser::TokenFileParser<LexerType>::Parse(lxr);
    if (external)
    {
        tokenFile->SetExternal();
    }
    fileMap.AddFileContent(file, std::move(content), std::move(lxr.GetLineStartIndeces()));
    return tokenFile;
}

std::unique_ptr<soul::ast::slg::KeywordFile> ParseKeywordFile(const std::string& keywordFilePath, soul::lexer::FileMap& fileMap)
{
    std::int32_t file = fileMap.MapFile(keywordFilePath);
    std::string keywordFileContent = util::ReadFile(keywordFilePath);
    std::u32string content = util::ToUtf32(keywordFileContent);
    auto lxr = soul::lex::slg::MakeLexer(content.c_str(), content.c_str() + content.length(), keywordFilePath);
    lxr.SetFile(file);
    //lxr.SetRuleNameMapPtr(soul::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lxr);
    std::unique_ptr<soul::ast::slg::KeywordFile> keywordFile = soul::slg::keyword::file::parser::KeywordFileParser<LexerType>::Parse(lxr);
    fileMap.AddFileContent(file, std::move(content), std::move(lxr.GetLineStartIndeces()));
    return keywordFile;
}

std::unique_ptr<soul::ast::slg::ExpressionFile> ParseExpressionFile(const std::string& expressionFilePath, soul::lexer::FileMap& fileMap)
{
    std::int32_t file = fileMap.MapFile(expressionFilePath);
    std::string expressionFileContent = util::ReadFile(expressionFilePath);
    std::u32string content = util::ToUtf32(expressionFileContent);
    auto lxr = soul::lex::slg::MakeLexer(content.c_str(), content.c_str() + content.length(), expressionFilePath);
    lxr.SetFile(file);
    //lxr.SetRuleNameMapPtr(soul::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lxr);
    std::unique_ptr<soul::ast::slg::ExpressionFile> expressionFile = soul::slg::expression::file::parser::ExpressionFileParser<LexerType>::Parse(lxr);
    fileMap.AddFileContent(file, std::move(content), std::move(lxr.GetLineStartIndeces()));
    return expressionFile;
}

std::unique_ptr<soul::ast::slg::LexerFile> ParseLexerFile(const std::string& lexerFilePath, soul::lexer::FileMap& fileMap)
{
    std::int32_t file = fileMap.MapFile(lexerFilePath);
    std::string lexerFileContent = util::ReadFile(lexerFilePath);
    std::u32string content = util::ToUtf32(lexerFileContent);
    auto lxr = soul::lex::slg::MakeLexer(content.c_str(), content.c_str() + content.length(), lexerFilePath);
    lxr.SetFile(file);
    //lxr.SetRuleNameMapPtr(soul::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lxr);
    std::unique_ptr<soul::ast::slg::LexerFile> lexerFile = soul::slg::lexer::file::parser::LexerFileParser<LexerType>::Parse(lxr);
    fileMap.AddFileContent(file, std::move(content), std::move(lxr.GetLineStartIndeces()));
    return lexerFile;
}

std::unique_ptr<soul::ast::slg::SlgFile> ParseSlgFile(const std::string& slgFilePath, soul::lexer::FileMap& fileMap)
{
    std::int32_t file = fileMap.MapFile(slgFilePath);
    std::string slgFileContent = util::ReadFile(slgFilePath);
    std::u32string content = util::ToUtf32(slgFileContent);
    auto lxr = soul::lex::slg::MakeLexer(content.c_str(), content.c_str() + content.length(), slgFilePath);
    lxr.SetFile(file);
    //lxr.SetRuleNameMapPtr(soul::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lxr);
    auto vars = static_cast<soul::lexer::Lexer<soul::lex::slg::SlgLexer<char32_t>, char32_t>::VariableClassType*>(lxr.GetVariables());
    vars->matchFilePath = true;
    std::unique_ptr<soul::ast::slg::SlgFile> slgFile = soul::slg::slg::file::parser::SlgFileParser<LexerType>::Parse(lxr);
    fileMap.AddFileContent(file, std::move(content), std::move(lxr.GetLineStartIndeces()));
    return slgFile;
}

} // namespace soul::slg
