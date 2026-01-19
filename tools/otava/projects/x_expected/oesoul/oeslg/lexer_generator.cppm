// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.lexer.generator;

import std;
import soul.ast.slg;
import soul.lexer;

export namespace soul::slg {

std::expected<bool, int> GenerateLexer(soul::ast::slg::SlgFile* slgFile, soul::lexer::FileMap& fileMap, bool verbose, bool debug);

} // namespace soul::slg
