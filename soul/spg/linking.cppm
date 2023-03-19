// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.linking;

import std.core;
import soul.ast.spg;
import soul.lexer.file.map;

export namespace soul::spg {

void Link(soul::ast::spg::SpgFile* spgFile, bool verbose, soul::lexer::FileMap& fileMap);

} // namespace soul::spg
