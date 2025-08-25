// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.slg.lexer.generator;

import std;
import soul_expected.ast.slg;
import soul_expected.lexer;

export namespace soul_expected::slg {

std::expected<bool, int> GenerateLexer(soul_expected::ast::slg::SlgFile* slgFile, soul_expected::lexer::FileMap& fileMap, bool verbose, bool debug);

} // namespace soul_expected::slg
