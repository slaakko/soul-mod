// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.slg.lexer.generator;

import util;
import soul.slg.file.parsers;
import soul.slg.token.module.generator;

namespace soul::slg {

void GenerateLexer(soul::ast::slg::SlgFile* slgFile, soul::ast::slg::LexerFile* lexerFile, bool verbose)
{
    // todo
}

void GenerateLexer(soul::ast::slg::SlgFile* slgFile, bool verbose)
{
    std::string filePath = util::GetFullPath(slgFile->FilePath());
    std::string dir = util::Path::GetDirectoryName(filePath);
    for (const auto& declaration : slgFile->Declarations())
    {
        switch (declaration->Kind())
        {
            case soul::ast::slg::SlgFileDeclarationKind::tokenFileDeclaration:
            {
                std::string tokenFilePath = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (verbose)
                {
                    std::cout << "> " << tokenFilePath << std::endl;
                }
                std::unique_ptr<soul::ast::slg::TokenFile> tokenFile = ParseTokenFile(tokenFilePath);
                GenerateTokenModule(tokenFile.get(), verbose);
                slgFile->AddTokenFile(tokenFile.release());
                break;
            }
            case soul::ast::slg::SlgFileDeclarationKind::keywordFileDeclaration:
            {
                std::string keywordFilePath = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (verbose)
                {
                    std::cout << "> " << keywordFilePath << std::endl;
                }
                std::unique_ptr<soul::ast::slg::KeywordFile> keywordFile = ParseKeywordFile(keywordFilePath);
                slgFile->AddKeywordFile(keywordFile.release());
                break;
            }
            case soul::ast::slg::SlgFileDeclarationKind::expressionFileDeclaration:
            {
                std::string expressionFilePath = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (verbose)
                {
                    std::cout << "> " << expressionFilePath << std::endl;
                }
                std::unique_ptr<soul::ast::slg::ExpressionFile> expressionFile = ParseExpressionFile(expressionFilePath);
                slgFile->AddExpressionFile(expressionFile.release());
                break;
            }
            case soul::ast::slg::SlgFileDeclarationKind::lexerFileDeclararation:
            {
                std::string lexerFilePath = util::GetFullPath(util::Path::Combine(dir, declaration->FilePath()));
                if (verbose)
                {
                    std::cout << "> " << lexerFilePath << std::endl;
                }
                std::unique_ptr<soul::ast::slg::LexerFile> lexerFile = ParseLexerFile(lexerFilePath);
                slgFile->AddLexerFile(lexerFile.release());
                break;
            }
        }
    }
    for (const auto& lexerFile : slgFile->LexerFiles())
    {
        GenerateLexer(slgFile, lexerFile.get(), verbose);
    }
}

} // namespace soul::slg
