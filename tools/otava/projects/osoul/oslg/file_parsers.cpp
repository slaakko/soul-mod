// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.file.parsers;

import util;
import soul.lexer;
import soul.parser;
import soul.lex.slg;
import soul.ast.cpp;
import soul.cpp.token;
import soul.slg.keyword.file.parser;
import soul.slg.expression.file.parser;
import soul.slg.lexer.file.parser;
import soul.slg.slg.file.parser;
import soul.slg.parsers.rules;
import soul.common.token.file.parser;
import common.parser.rules;

namespace soul::slg {

std::expected<std::unique_ptr<soul::ast::common::TokenFile>, int> ParseTokenFile(const std::string& tokenFilePath, bool external,
    soul::lexer::FileMap& fileMap)
{
    int file = fileMap.MapFile(tokenFilePath);
    std::expected<std::string, int> frv = util::ReadFile(tokenFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string tokenFileContent = std::move(*frv);
    std::expected<std::u32string, int> crv = util::ToUtf32(tokenFileContent);
    if (!crv) return std::unexpected<int>(crv.error());
    std::u32string content = std::move(*crv);
    auto rv = soul::lex::slg::MakeLexer(content.c_str(), content.c_str() + content.length(), tokenFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto& lexer = std::move(*rv);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(::common::parser::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    std::expected<std::unique_ptr<soul::ast::common::TokenFile>, int> tokenFileRv = soul::common::token::file::parser::TokenFileParser<LexerType>::Parse(lexer);
    if (!tokenFileRv) return tokenFileRv;
    std::unique_ptr<soul::ast::common::TokenFile> tokenFile = std::move(*tokenFileRv);
    if (external)
    {
        tokenFile->SetExternal();
    }
    fileMap.AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    return std::expected<std::unique_ptr<soul::ast::common::TokenFile>, int>(std::move(tokenFile));
}

std::expected<std::unique_ptr<soul::ast::slg::KeywordFile>, int> ParseKeywordFile(const std::string& keywordFilePath, soul::lexer::FileMap& fileMap)
{
    int file = fileMap.MapFile(keywordFilePath);
    std::expected<std::string, int> frv = util::ReadFile(keywordFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string keywordFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(keywordFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = soul::lex::slg::MakeLexer(content.c_str(), content.c_str() + content.length(), keywordFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto& lexer = std::move(*rv);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(soul::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    auto prv = soul::slg::keyword::file::parser::KeywordFileParser<LexerType>::Parse(lexer);
    if (!prv) return prv;
    fileMap.AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    return prv;
}

std::expected<std::unique_ptr<soul::ast::slg::ExpressionFile>, int> ParseExpressionFile(const std::string& expressionFilePath,
    soul::lexer::FileMap& fileMap)
{
    int file = fileMap.MapFile(expressionFilePath);
    std::expected<std::string, int> frv = util::ReadFile(expressionFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string expressionFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(expressionFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = soul::lex::slg::MakeLexer(content.c_str(), content.c_str() + content.length(), expressionFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto& lexer = std::move(*rv);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(soul::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    auto prv = soul::slg::expression::file::parser::ExpressionFileParser<LexerType>::Parse(lexer);
    if (!prv) return prv;
    fileMap.AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    return prv;
}

std::expected<std::unique_ptr<soul::ast::slg::LexerFile>, int> ParseLexerFile(const std::string& lexerFilePath, soul::lexer::FileMap& fileMap)
{
    int file = fileMap.MapFile(lexerFilePath);
    std::expected<std::string, int> frv = util::ReadFile(lexerFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string lexerFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(lexerFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = soul::lex::slg::MakeLexer(content.c_str(), content.c_str() + content.length(), lexerFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto& lexer = std::move(*rv);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(soul::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    soul::ast::cpp::Context context;
    auto prv = soul::slg::lexer::file::parser::LexerFileParser<LexerType>::Parse(lexer, &context);
    if (!prv) return prv;
    fileMap.AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    return prv;
}

std::expected<std::unique_ptr<soul::ast::slg::SlgFile>, int> ParseSlgFile(const std::string& slgFilePath, soul::lexer::FileMap& fileMap)
{
    int file = fileMap.MapFile(slgFilePath);
    std::expected<std::string, int> frv = util::ReadFile(slgFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string slgFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(slgFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = soul::lex::slg::MakeLexer(content.c_str(), content.c_str() + content.length(), slgFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto& lexer = std::move(*rv);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(soul::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    auto vars = static_cast<soul::lexer::Lexer<soul::lex::slg::SlgLexer<char32_t>, char32_t>::VariableClassType*>(lexer.GetVariables());
    vars->matchFilePath = true;
    auto prv = soul::slg::slg::file::parser::SlgFileParser<LexerType>::Parse(lexer);
    if (!prv) return prv;
    fileMap.AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    return prv;
}

} // namespace soul::slg
