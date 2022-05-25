// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.ast.spg;

import util;

namespace soul::ast::spg {

File::File(FileKind kind_, const std::string& filePath_) : kind(kind_), filePath(filePath_)
{
}

SpgFileDeclaration::~SpgFileDeclaration()
{
}

SpgFile::SpgFile(const std::string& filePath_, const std::string& projectName_) : File(FileKind::spgFile, filePath_), projectName(projectName_)
{
}

void SpgFile::AddDeclaration(SpgFileDeclaration* declaration)
{
    declarations.push_back(std::unique_ptr<SpgFileDeclaration>(declaration));
}

ParserFile::ParserFile(const std::string& filePath_) : File(FileKind::parserFile, filePath_)
{
}

} // namespace soul::ast::spg
