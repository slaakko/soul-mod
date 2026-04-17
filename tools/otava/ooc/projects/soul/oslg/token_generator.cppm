// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.token.generator;

import std;
import soul.ast.slg;
import soul.ast.common;

export namespace soul::slg {

void GenerateTokenModule(soul::ast::common::TokenFile* tokenFile, bool verbose);

} // namespace soul::slg
