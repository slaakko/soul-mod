// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.slg.lexer.generator;

import std;
import soul.ast.slg;
import soul.lexer;

export namespace soul::slg {

void GenerateLexer(soul::ast::slg::SlgFile* slgFile, bool verbose, soul::lexer::FileMap& fileMap, bool debug);

} // namespace soul::slg
