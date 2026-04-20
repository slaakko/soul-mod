module soul.spg.code.generator;

import soul.spg.code.generator.visitor;

namespace soul::spg {

void GenerateCode(soul::ast::spg::SpgFile* spgFile, bool verbose, bool noDebugSupport, const std::string& version, soul::lexer::FileMap& fileMap)
{
    CodeGeneratorVisitor visitor(spgFile, verbose, noDebugSupport, version, fileMap);
    spgFile->Accept(visitor);
}

} // namespace soul::spg
