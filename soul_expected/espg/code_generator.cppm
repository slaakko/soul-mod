// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.code.generator;

import std;
import soul_expected.ast.spg;
import soul_expected.lexer.file.map;

export namespace soul_expected::spg {

std::expected<bool, int> GenerateCode(soul_expected::ast::spg::SpgFile* spgFile, bool verbose, bool noDebugSupport, const std::string& version, 
    soul_expected::lexer::FileMap& fileMap);

} // namespace soul_expected::spg
