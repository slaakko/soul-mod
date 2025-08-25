// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.spg.file.parsers;

import util_expected;
import soul_expected.ast.cpp;
import soul_expected.lexer;
import soul_expected.lex.spg;
import soul_expected.spg.spg.file.parser;
import soul_expected.spg.parser.file.parser;
import soul_expected.spg.parsers.rules;
import soul_expected.common.token.file.parser;
import common_expected.parser.rules;

namespace soul_expected::spg {

std::expected<std::unique_ptr<soul_expected::ast::spg::SpgFile>, int> ParseSpgFile(const std::string& spgFilePath, soul_expected::lexer::FileMap& fileMap, bool verbose)
{
    std::filesystem::path p = spgFilePath;
    if (!std::filesystem::exists(p))
    {
        return std::unexpected<int>(util::AllocateError("SPG file '" + spgFilePath + "' not found"));
    }
    if (verbose)
    {
        std::cout << "> " << spgFilePath << std::endl;
    }
    std::int32_t file = fileMap.MapFile(spgFilePath);
    std::expected<std::string, int> frv = util::ReadFile(spgFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string spgFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(spgFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = soul_expected::lex::spg::MakeLexer(content.c_str(), content.c_str() + content.length(), spgFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto lexer = std::move(*rv);
    lexer.SetRuleNameMapPtr(soul_expected::spg::parsers::rules::GetRuleNameMapPtr());
    lexer.SetFile(file);
    using LexerType = decltype(lexer);
    auto vars = static_cast<typename LexerType::VariableClassType*>(lexer.GetVariables());
    vars->matchFilePath = true;
    std::expected<std::unique_ptr<soul_expected::ast::spg::SpgFile>, int> spgFileRv = soul_expected::spg::spg::file::parser::SpgFileParser<LexerType>::Parse(lexer);
    if (!spgFileRv) return spgFileRv;
    fileMap.AddFileContent(file, std::move(content), std::move(lexer.GetLineStartIndeces()));
    return spgFileRv;
}

std::expected<std::unique_ptr<soul_expected::ast::spg::ParserFile>, int>  ParseParserFile(const std::string& parserFilePath, const soul_expected::ast::SourcePos& sourcePos, 
    soul_expected::lexer::FileMap& fileMap, bool verbose, bool external)
{
    std::filesystem::path p = parserFilePath;
    if (!std::filesystem::exists(p))
    {
        std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "parser file '" + parserFilePath + "' not found", sourcePos, fileMap);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = std::move(*rv);
        return std::unexpected<int>(util::AllocateError(errorMessage));
    }
    if (verbose)
    {
        std::cout << "> " << parserFilePath << std::endl;
    }
    std::int32_t file = fileMap.MapFile(parserFilePath);
    std::expected<std::string, int> frv = util::ReadFile(parserFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string parserFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(parserFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = soul_expected::lex::spg::MakeLexer(content.c_str(), content.c_str() + content.length(), parserFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto lexer = std::move(*rv);
    lexer.SetRuleNameMapPtr(soul_expected::spg::parsers::rules::GetRuleNameMapPtr());
    lexer.SetFile(file);
    using LexerType = decltype(lexer);
    soul_expected::ast::cpp::Context context;
    std::expected<std::unique_ptr<soul_expected::ast::spg::ParserFile>, int> parserFileRv =
        soul_expected::spg::parser::file::parser::ParserFileParser<LexerType>::Parse(lexer, &context);
    if (!parserFileRv) return parserFileRv;
    std::unique_ptr<soul_expected::ast::spg::ParserFile> parserFile = std::move(*parserFileRv);
    fileMap.AddFileContent(file, std::move(content), std::move(lexer.GetLineStartIndeces()));
    if (external)
    {
        parserFile->SetExternal();
    }
    return std::expected<std::unique_ptr<soul_expected::ast::spg::ParserFile>, int>(std::move(parserFile));
}

std::expected<std::unique_ptr<soul_expected::ast::common::TokenFile>, int> ParseTokenFile(const std::string& tokenFilePath, const soul_expected::ast::SourcePos& sourcePos, 
    bool verbose, bool external, soul_expected::lexer::FileMap& fileMap)
{
    std::filesystem::path p = tokenFilePath;
    if (!std::filesystem::exists(p))
    {
        std::expected<std::string, int> rv = soul_expected::lexer::MakeMessage("error", "token file '" + tokenFilePath + "' not found", sourcePos, fileMap);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = std::move(*rv);
        return std::unexpected<int>(util::AllocateError(errorMessage));
    }
    if (verbose)
    {
        std::cout << "> " << tokenFilePath << std::endl;
    }
    std::int32_t file = fileMap.MapFile(tokenFilePath);
    std::expected<std::string, int> frv = util::ReadFile(tokenFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string tokenFileContent = std::move(*frv);
    std::expected<std::u32string, int> crv = util::ToUtf32(tokenFileContent);
    if (!crv) return std::unexpected<int>(crv.error());
    std::u32string content = std::move(*crv);
    auto rv = soul_expected::lex::spg::MakeLexer(content.c_str(), content.c_str() + content.length(), tokenFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto lexer = std::move(*rv);
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
    fileMap.AddFileContent(file, std::move(content), std::move(lexer.GetLineStartIndeces()));
    return std::expected<std::unique_ptr<soul_expected::ast::common::TokenFile>, int>(std::move(tokenFile));
}


} // namespace soul_expected::spg
