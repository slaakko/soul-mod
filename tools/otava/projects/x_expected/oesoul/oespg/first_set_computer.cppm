// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.first.set.computer;

import soul.ast.spg;
import std;

export namespace soul::spg {

std::expected<bool, int> ComputeFirstSets(soul::ast::spg::SpgFile* spgFile, bool verbose);

} // namespace soul::spg
