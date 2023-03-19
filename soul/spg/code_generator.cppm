// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.code.generator;

import std.core;
import soul.ast.spg;
import soul.lexer.file.map;

export namespace soul::spg {

void GenerateCode(soul::ast::spg::SpgFile* spgFile, bool verbose, bool noDebugSupport, const std::string& version, soul::lexer::FileMap& fileMap);

} // namespace soul::spg
