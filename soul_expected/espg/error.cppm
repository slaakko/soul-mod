// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.error;

import std;
import soul_expected.ast.spg;

export namespace soul_expected::spg::error {

int RuleNameNotUnique(const std::string& fileName, soul_expected::ast::spg::RuleParser* rule);

} // namespace soul_expected::spg::error
