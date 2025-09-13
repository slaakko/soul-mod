// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.optimizer;

import std;
import soul.ast.spg;
import soul.lexer.file.map;

export namespace soul::spg {

std::expected<std::unique_ptr<soul::ast::spg::SpgFile>, int> Optimize(soul::ast::spg::SpgFile* spgFile, bool verbose, bool xml,
    soul::lexer::FileMap& fileMap);

} // namespace soul::spg
