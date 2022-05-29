// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.file.parsers;

import std.filesystem;
import util;
import soul.lex.spg;
import soul.spg.spg.file.parser;
import soul.spg.parser.file.parser;

namespace soul::spg {

std::unique_ptr<soul::ast::spg::SpgFile> ParseSpgFile(const std::string& spgFilePath, soul::lexer::FileMap& fileMap, bool verbose)
{
    if (!std::filesystem::exists(spgFilePath))
    {
        throw std::runtime_error("SPG file '" + spgFilePath + "' not found");
    }
    if (verbose)
    {
        std::cout << "> " << spgFilePath << std::endl;
    }
    int file = fileMap.AddFilePath(spgFilePath);
    std::string spgFileContent = util::ReadFile(spgFilePath);
    std::u32string content = util::ToUtf32(spgFileContent);
    auto lexer = soul::lex::spg::MakeLexer(content.c_str(), content.c_str() + content.length(), spgFilePath);
    using LexerType = decltype(lexer);
    lexer.SetFile(file);
    auto vars = static_cast<LexerType::VariableClassType*>(lexer.GetVariables());
    vars->matchFilePath = true;
    std::unique_ptr<soul::ast::spg::SpgFile> spgFile = soul::spg::spg::file::parser::SpgFileParser<LexerType>::Parse(lexer);
    fileMap.AddFileContent(std::move(content), std::move(lexer.GetLineStartIndeces()));
    return spgFile;
}

std::unique_ptr<soul::ast::spg::ParserFile> ParseParserFile(const std::string& parserFilePath, const soul::ast::SourcePos& sourcePos, soul::lexer::FileMap& fileMap, 
    bool verbose, bool external)
{
    if (!std::filesystem::exists(parserFilePath))
    {
        std::string errorMessage = soul::lexer::MakeMessage("error", "parser file '" + parserFilePath + "' not found", sourcePos, fileMap);
        throw std::runtime_error(errorMessage);
    }
    if (verbose)
    {
        std::cout << "> " << parserFilePath << std::endl;
    }
    int file = fileMap.AddFilePath(parserFilePath);
    std::string parserFileContent = util::ReadFile(parserFilePath);
    std::u32string content = util::ToUtf32(parserFileContent);
    auto lexer = soul::lex::spg::MakeLexer(content.c_str(), content.c_str() + content.length(), parserFilePath);
    using LexerType = decltype(lexer);
    lexer.SetFile(file);
    std::unique_ptr<soul::ast::spg::ParserFile> parserFile = soul::spg::parser::file::parser::ParserFileParser<LexerType>::Parse(lexer);
    fileMap.AddFileContent(std::move(content), std::move(lexer.GetLineStartIndeces()));
    if (external)
    {
        parserFile->SetExternal();
    }
    return parserFile;
}

} // namespace soul::spg
