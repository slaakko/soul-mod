// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.parser.generator;

import std.core;
import soul.lexer.file.map;
import soul.ast.spg;

export namespace soul::spg {

void GenerateParsers(soul::ast::spg::SpgFile* spgFile, soul::lexer::FileMap& fileMap, bool verbose, bool noDebugSupport, const std::string& version);

} // namespace soul::spg
