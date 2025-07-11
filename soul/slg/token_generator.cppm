// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.token.generator;

import std;
import soul.ast.slg;
import soul.common.module_map;

export namespace soul::slg {

void GenerateTokenModule(soul::ast::slg::TokenFile* tokenFile, bool verbose, soul::common::ModuleMap& moduleMap, bool ppstyle);

} // namespace soul::slg
