// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.code.generator;

import std.core;
import soul.ast.spg;

export namespace soul::spg {

void GenerateCode(soul::ast::spg::SpgFile* spgFile, bool verbose, bool noDebugSupport, const std::string& version);

} // namespace soul::spg
