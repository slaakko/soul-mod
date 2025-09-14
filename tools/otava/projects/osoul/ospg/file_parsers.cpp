// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.file.parsers;

import util;
import soul.ast.cpp;
import soul.lexer;
import soul.lex.spg;
import soul.spg.spg.file.parser;
import soul.spg.parser.file.parser;
import osoul.spg.parsers.rules;
import soul.common.token.file.parser;
import common.parser.rules;

namespace soul::spg {

std::expected<std::unique_ptr<soul::ast::spg::SpgFile>, int> ParseSpgFile(const std::string& spgFilePath, soul::lexer::FileMap& fileMap, bool verbose)
{
    std::filesystem::path p = spgFilePath;
    if (!std::filesystem::exists(p))
    {
        return std::unexpected<int>(util::AllocateError("SPG file '" + spgFilePath + "' not found"));
    }
    if (verbose)
    {
        std::cout << "> " << spgFilePath << "\n";
    }
    std::int32_t file = fileMap.MapFile(spgFilePath);
    std::expected<std::string, int> frv = util::ReadFile(spgFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string spgFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(spgFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = soul::lex::spg::MakeLexer(content.c_str(), content.c_str() + content.length(), spgFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto& lexer = std::move(*rv);
    lexer.SetRuleNameMapPtr(osoul::spg::parsers::rules::GetRuleNameMapPtr());
    lexer.SetFile(file);
    using LexerType = decltype(lexer);
    auto vars = static_cast<soul::lexer::Lexer<soul::lex::spg::SpgLexer<char32_t>, char32_t>::VariableClassType*>(lexer.GetVariables());
    vars->matchFilePath = true;
    std::expected<std::unique_ptr<soul::ast::spg::SpgFile>, int> spgFileRv = soul::spg::spg::file::parser::SpgFileParser<LexerType>::Parse(lexer);
    if (!spgFileRv) return spgFileRv;

    fileMap.AddFileContent(file, std::move(content), std::move(lexer.GetLineStartIndeces()));
    return spgFileRv;
}

std::expected<std::unique_ptr<soul::ast::spg::ParserFile>, int>  ParseParserFile(const std::string& parserFilePath, const soul::ast::SourcePos& sourcePos,
    soul::lexer::FileMap& fileMap, bool verbose, bool external)
{
    std::filesystem::path p = parserFilePath;
    if (!std::filesystem::exists(p))
    {
        std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "parser file '" + parserFilePath + "' not found", sourcePos, fileMap);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = std::move(*rv);
        return std::unexpected<int>(util::AllocateError(errorMessage));
    }
    if (verbose)
    {
        std::cout << "> " << parserFilePath << "\n";
    }
    std::int32_t file = fileMap.MapFile(parserFilePath);
    std::expected<std::string, int> frv = util::ReadFile(parserFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string parserFileContent = std::move(*frv);
    std::expected<std::u32string, int> urv = util::ToUtf32(parserFileContent);
    if (!urv) return std::unexpected<int>(urv.error());
    std::u32string content = std::move(*urv);
    auto rv = soul::lex::spg::MakeLexer(content.c_str(), content.c_str() + content.length(), parserFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto& lexer = std::move(*rv);
    lexer.SetRuleNameMapPtr(osoul::spg::parsers::rules::GetRuleNameMapPtr());
    lexer.SetFile(file);
    using LexerType = decltype(lexer);
    soul::ast::cpp::Context context;
    std::expected<std::unique_ptr<soul::ast::spg::ParserFile>, int> parserFileRv =
        soul::spg::parser::file::parser::ParserFileParser<LexerType>::Parse(lexer, &context);
    if (!parserFileRv) return parserFileRv;
    std::unique_ptr<soul::ast::spg::ParserFile> parserFile = std::move(*parserFileRv);
    fileMap.AddFileContent(file, std::move(content), std::move(lexer.GetLineStartIndeces()));
    if (external)
    {
        parserFile->SetExternal();
    }
    return std::expected<std::unique_ptr<soul::ast::spg::ParserFile>, int>(std::move(parserFile));
}

std::expected<std::unique_ptr<soul::ast::common::TokenFile>, int> ParseTokenFile(const std::string& tokenFilePath, const soul::ast::SourcePos& sourcePos,
    bool verbose, bool external, soul::lexer::FileMap& fileMap)
{
    std::filesystem::path p = tokenFilePath;
    if (!std::filesystem::exists(p))
    {
        std::expected<std::string, int> rv = soul::lexer::MakeMessage("error", "token file '" + tokenFilePath + "' not found", sourcePos, fileMap);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorMessage = std::move(*rv);
        return std::unexpected<int>(util::AllocateError(errorMessage));
    }
    if (verbose)
    {
        std::cout << "> " << tokenFilePath << "\n";
    }
    std::int32_t file = fileMap.MapFile(tokenFilePath);
    std::expected<std::string, int> frv = util::ReadFile(tokenFilePath);
    if (!frv) return std::unexpected<int>(frv.error());
    std::string tokenFileContent = std::move(*frv);
    std::expected<std::u32string, int> crv = util::ToUtf32(tokenFileContent);
    if (!crv) return std::unexpected<int>(crv.error());
    std::u32string content = std::move(*crv);
    auto rv = soul::lex::spg::MakeLexer(content.c_str(), content.c_str() + content.length(), tokenFilePath);
    if (!rv) return std::unexpected<int>(rv.error());
    auto& lexer = std::move(*rv);
    lexer.SetRuleNameMapPtr(::common::parser::rules::GetRuleNameMapPtr());
    using LexerType = decltype(lexer);
    std::expected<std::unique_ptr<soul::ast::common::TokenFile>, int> tokenFileRv = soul::common::token::file::parser::TokenFileParser<LexerType>::Parse(
        lexer);
    if (!tokenFileRv) return tokenFileRv;
    std::unique_ptr<soul::ast::common::TokenFile> tokenFile = std::move(*tokenFileRv);
    if (external)
    {
        tokenFile->SetExternal();
    }
    fileMap.AddFileContent(file, std::move(content), std::move(lexer.GetLineStartIndeces()));
    return std::expected<std::unique_ptr<soul::ast::common::TokenFile>, int>(std::move(tokenFile));
}

} // namespace soul::spg
