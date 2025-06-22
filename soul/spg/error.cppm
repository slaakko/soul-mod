// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.error;

import std.core;
import soul.ast.spg;

export namespace soul::spg::error {

void ThrowRuleNameNotUnique(const std::string& fileName, soul::ast::spg::RuleParser* rule);

} // namespace soul::spg::error
