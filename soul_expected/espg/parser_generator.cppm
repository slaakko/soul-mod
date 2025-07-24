// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.parser.generator;

import std;
import soul_expected.lexer.file.map;
import soul_expected.ast.spg;

export namespace soul_expected::spg {

std::expected<bool, int> GenerateParsers(soul_expected::ast::spg::SpgFile* spgFile, soul_expected::lexer::FileMap& fileMap, bool verbose, 
    bool noDebugSupport, bool optimize, bool xml, const std::string& version);

} // namespace soul_expected::spg
