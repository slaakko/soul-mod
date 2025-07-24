// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.spg.optimizer;

import std;
import soul_expected.ast.spg;
import soul_expected.lexer.file.map;

export namespace soul_expected::spg {

std::expected<std::unique_ptr<soul_expected::ast::spg::SpgFile>, int> Optimize(soul_expected::ast::spg::SpgFile* spgFile, bool verbose, bool xml, 
    soul_expected::lexer::FileMap& fileMap);

} // namespace soul_expected::spg
