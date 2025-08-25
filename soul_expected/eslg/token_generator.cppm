// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.slg.token.generator;

import std;
import soul_expected.ast.slg;
import soul_expected.ast.common;

export namespace soul_expected::slg {

std::expected<bool, int> GenerateTokenModule(soul_expected::ast::common::TokenFile* tokenFile, bool verbose);

} // namespace soul_expect::slg
