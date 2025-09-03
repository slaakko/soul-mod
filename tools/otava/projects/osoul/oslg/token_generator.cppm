// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.token.generator;

import std;
import soul.ast.slg;
import soul.ast.common;

export namespace soul::slg {

std::expected<bool, int> GenerateTokenModule(soul::ast::common::TokenFile* tokenFile, bool verbose);

} // namespace soul_expect::slg
