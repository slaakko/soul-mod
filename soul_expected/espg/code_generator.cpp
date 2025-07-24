// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.spg.code.generator;

import soul_expected.spg.code.generator.visitor;

namespace soul_expected::spg {

std::expected<bool, int> GenerateCode(soul_expected::ast::spg::SpgFile* spgFile, bool verbose, bool noDebugSupport, const std::string& version, 
    soul_expected::lexer::FileMap& fileMap)
{
    CodeGeneratorVisitor visitor(spgFile, verbose, noDebugSupport, version, fileMap);
    spgFile->Accept(visitor);
    if (!visitor) return std::unexpected<int>(visitor.Error());
    return std::expected<bool, int>(true);
}

} // namespace soul_expected::spg
