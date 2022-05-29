// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.parser.generator;

import util;
import soul.spg.file.parsers;
import soul.spg.linking;
import soul.spg.code.generator;

namespace soul::spg {

void GenerateParsers(soul::ast::spg::SpgFile* spgFile, soul::lexer::FileMap& fileMap, bool verbose, bool noDebugSupport, const std::string& version)
{
    std::cout << "generating parsers for project '" << spgFile->ProjectName() << "'..." << std::endl;
    std::string root = util::Path::GetDirectoryName(spgFile->FilePath());
    for (const auto& declaration : spgFile->Declarations())
    {
        switch (declaration->GetFileKind())
        {
            case soul::ast::spg::FileKind::parserFile:
            {
                soul::ast::spg::ParserFileDeclaration* parserFileDeclaration = static_cast<soul::ast::spg::ParserFileDeclaration*>(declaration.get());
                std::string parserFilePath = util::GetFullPath(util::Path::Combine(root, parserFileDeclaration->FilePath()));
                std::unique_ptr<soul::ast::spg::ParserFile> parserFile = soul::spg::ParseParserFile(parserFilePath, parserFileDeclaration->GetSourcePos(), 
                    fileMap, verbose, parserFileDeclaration->External());
                spgFile->AddParserFile(parserFile.release());
                break;
            }
        }
    }
    Link(spgFile, verbose, fileMap);
    GenerateCode(spgFile, verbose, noDebugSupport, version, fileMap);
    std::cout << "parsers for project '" << spgFile->ProjectName() << "' generated successfully." << std::endl;
}

} // namespace soul::spg
