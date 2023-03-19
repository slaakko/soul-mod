// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.optimizer;

import std.core;
import soul.ast.spg;
import soul.lexer.file.map;

export namespace soul::spg {

std::unique_ptr<soul::ast::spg::SpgFile> Optimize(soul::ast::spg::SpgFile* spgFile, bool verbose, bool xml, soul::lexer::FileMap& fileMap);

} // namespace soul::spg

