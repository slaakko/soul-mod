// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.linking;

import std;
import soul.ast.spg;
import soul.lexer.file.map;

export namespace soul::spg {

void Link(soul::ast::spg::SpgFile* spgFile, bool verbose, soul::lexer::FileMap& fileMap);

} // namespace soul::spg
