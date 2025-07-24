// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.first.set.computer;

import soul_expected.ast.spg;
import std;

export namespace soul_expected::spg {

std::expected<bool, int> ComputeFirstSets(soul_expected::ast::spg::SpgFile* spgFile, bool verbose);

} // namespace soul_expected::spg
