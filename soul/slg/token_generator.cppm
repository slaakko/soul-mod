// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.token.generator;

import std.core;
import soul.ast.slg;

export namespace soul::slg {

void GenerateTokenModule(soul::ast::slg::TokenFile* tokenFile, bool verbose);

} // namespace soul::slg
