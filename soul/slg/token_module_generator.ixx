// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.token.module.generator;

import std.core;
import soul.ast.slg;

export namespace soul::slg {

std::string ToNamespaceName(const std::string& qualifiedId);
void GenerateTokenModule(soul::ast::slg::TokenFile* tokenFile, bool verbose);

} // namespace soul::slg
