// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.slg.file.parsers;

import util_expected;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.lex.slg;
import soul_expected.ast.cpp;
import soul_expected.cpp.token;
import soul_expected.slg.keyword.file.parser;
import soul_expected.slg.expression.file.parser;
import soul_expected.slg.lexer.file.parser;
import soul_expected.slg.slg.file.parser;
import soul_expected.slg.parsers.rules;
import soul_expected.common.token.file.parser;
import common_expected.parser.rules;

namespace soul_expected::slg {

using namespace soul_expected::cpp::token;
using namespace soul_expected::lex::slg;
using namespace soul_expected::slg::keyword::file::parser;
using namespace soul_expected::slg::expression::file::parser;
using namespace soul_expected::slg::lexer::file::parser;
using namespace soul_expected::slg::slg::file::parser;

std::expected<std::unique_ptr<soul_expected::ast::common::TokenFile>, int> ParseTokenFile(const std::string& tokenFilePath, bool external, 
    soul_expected::lexer::FileMap& fileMap)
{
    int file = fileMap.MapFile(tokenFilePath);
    std::expected<std::string, int> frv = util::ReadFile(tokenFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string tokenFileContent = std::move(*frv);
    std::expected<std::u32string, int> crv = util::ToUtf32(tokenFileContent);
    if (!crv) return std::unexpected<int>(crv.error());
    std::u32string content = std::move(*crv);
    auto rv = MakeLexer(content.c_str(), content.c_str() + content.length(), tokenFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto lexer = std::move(*rv);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(common_expected::parser::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    std::expected<std::unique_ptr<soul_expected::ast::common::TokenFile>, int> tokenFileRv = soul_expected::common::token::file::parser::TokenFileParser<LexerType>::Parse(
        lexer);
    if (!tokenFileRv) return tokenFileRv;
    std::unique_ptr<soul_expected::ast::common::TokenFile> tokenFile = std::move(*tokenFileRv);
    if (external)
    {
        tokenFile->SetExternal();
    }
    fileMap.AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    return std::expected<std::unique_ptr<soul_expected::ast::common::TokenFile>, int>(std::move(tokenFile));
}

std::expected<std::unique_ptr<soul_expected::ast::slg::KeywordFile>, int> ParseKeywordFile(const std::string& keywordFilePath, soul_expected::lexer::FileMap& fileMap)
{
    int file = fileMap.MapFile(keywordFilePath);
    std::expected<std::string, int> frv = util::ReadFile(keywordFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string keywordFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(keywordFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = MakeLexer(content.c_str(), content.c_str() + content.length(), keywordFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto lexer = std::move(*rv);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(soul_expected::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    auto prv = KeywordFileParser<LexerType>::Parse(lexer);
    if (!prv) return prv;
    fileMap.AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    return prv;
}

std::expected<std::unique_ptr<soul_expected::ast::slg::ExpressionFile>, int> ParseExpressionFile(const std::string& expressionFilePath, 
    soul_expected::lexer::FileMap& fileMap)
{
    int file = fileMap.MapFile(expressionFilePath);
    std::expected<std::string, int> frv = util::ReadFile(expressionFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string expressionFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(expressionFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = MakeLexer(content.c_str(), content.c_str() + content.length(), expressionFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto lexer = std::move(*rv);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(soul_expected::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    auto prv = ExpressionFileParser<LexerType>::Parse(lexer);
    if (!prv) return prv;
    fileMap.AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    return prv;
}

std::expected<std::unique_ptr<soul_expected::ast::slg::LexerFile>, int> ParseLexerFile(const std::string& lexerFilePath, soul_expected::lexer::FileMap& fileMap)
{
    int file = fileMap.MapFile(lexerFilePath);
    std::expected<std::string, int> frv = util::ReadFile(lexerFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string lexerFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(lexerFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = MakeLexer(content.c_str(), content.c_str() + content.length(), lexerFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto lexer = std::move(*rv);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(soul_expected::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    soul_expected::ast::cpp::Context context;
    auto prv = LexerFileParser<LexerType>::Parse(lexer, &context);
    if (!prv) return prv;
    fileMap.AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    return prv;
}

std::expected<std::unique_ptr<soul_expected::ast::slg::SlgFile>, int> ParseSlgFile(const std::string& slgFilePath, soul_expected::lexer::FileMap& fileMap)
{
    int file = fileMap.MapFile(slgFilePath);
    std::expected<std::string, int> frv = util::ReadFile(slgFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string slgFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(slgFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = MakeLexer(content.c_str(), content.c_str() + content.length(), slgFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto lexer = std::move(*rv);
    lexer.SetFile(file);
    lexer.SetRuleNameMapPtr(soul_expected::slg::parsers::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    auto vars = static_cast<typename LexerType::VariableClassType*>(lexer.GetVariables());
    vars->matchFilePath = true;
    auto prv = SlgFileParser<LexerType>::Parse(lexer);
    if (!prv) return prv;
    fileMap.AddFileContent(file, std::move(content), lexer.GetLineStartIndeces());
    return prv;
}

} // namespace soul_expected::slg
