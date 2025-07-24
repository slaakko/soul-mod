// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.linking;

import std;
import soul_expected.ast.spg;
import soul_expected.lexer.file.map;

export namespace soul_expected::spg {

std::expected<bool, int> Link(soul_expected::ast::spg::SpgFile* spgFile, bool verbose, soul_expected::lexer::FileMap& fileMap);

} // namespace soul_expected::spg
