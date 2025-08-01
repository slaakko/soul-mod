// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.file.parsers;

import util;
import soul.lexer;
import soul.lex.spg;
import soul.spg.spg.file.parser;
import soul.spg.parser.file.parser;
import soul.spg.parsers.rules;

namespace soul::spg {

std::unique_ptr<soul::ast::spg::SpgFile> ParseSpgFile(const std::string& spgFilePath, soul::lexer::FileMap& fileMap, bool verbose)
{
    std::filesystem::path p = spgFilePath;
    if (!std::filesystem::exists(p))
    {
        throw std::runtime_error("SPG file '" + spgFilePath + "' not found");
    }
    if (verbose)
    {
        std::cout << "> " << spgFilePath << std::endl;
    }
    std::int32_t file = fileMap.MapFile(spgFilePath);
    std::string spgFileContent = util::ReadFile(spgFilePath);
    std::u32string content = util::ToUtf32(spgFileContent);
    auto lexer = soul::lex::spg::MakeLexer(content.c_str(), content.c_str() + content.length(), spgFilePath);
    lexer.SetRuleNameMapPtr(soul::spg::parsers::rules::GetRuleNameMapPtr());
    lexer.SetFile(file);
    using LexerType = decltype(lexer);
    auto vars = static_cast<typename LexerType::VariableClassType*>(lexer.GetVariables());
    vars->matchFilePath = true;
    std::unique_ptr<soul::ast::spg::SpgFile> spgFile = soul::spg::spg::file::parser::SpgFileParser<LexerType>::Parse(lexer);
    fileMap.AddFileContent(file, std::move(content), std::move(lexer.GetLineStartIndeces()));
    return spgFile;
}

std::unique_ptr<soul::ast::spg::ParserFile> ParseParserFile(const std::string& parserFilePath, const soul::ast::SourcePos& sourcePos, soul::lexer::FileMap& fileMap, 
    bool verbose, bool external)
{
    std::filesystem::path p = parserFilePath;
    if (!std::filesystem::exists(p))
    {
        std::string errorMessage = soul::lexer::MakeMessage("error", "parser file '" + parserFilePath + "' not found", sourcePos, fileMap);
        throw std::runtime_error(errorMessage);
    }
    if (verbose)
    {
        std::cout << "> " << parserFilePath << std::endl;
    }
    std::int32_t file = fileMap.MapFile(parserFilePath);
    std::string parserFileContent = util::ReadFile(parserFilePath);
    std::u32string content = util::ToUtf32(parserFileContent);
    auto lexer = soul::lex::spg::MakeLexer(content.c_str(), content.c_str() + content.length(), parserFilePath);
    lexer.SetRuleNameMapPtr(soul::spg::parsers::rules::GetRuleNameMapPtr());
    lexer.SetFile(file);
    using LexerType = decltype(lexer);
    std::unique_ptr<soul::ast::spg::ParserFile> parserFile = soul::spg::parser::file::parser::ParserFileParser<LexerType>::Parse(lexer);
    fileMap.AddFileContent(file, std::move(content), std::move(lexer.GetLineStartIndeces()));
    if (external)
    {
        parserFile->SetExternal();
    }
    return parserFile;
}

} // namespace soul::spg
