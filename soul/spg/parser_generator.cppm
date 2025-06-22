// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.parser.generator;

import std;
import soul.lexer.file.map;
import soul.ast.spg;
import soul.common.module_map;

export namespace soul::spg {

void GenerateParsers(soul::ast::spg::SpgFile* spgFile, soul::lexer::FileMap& fileMap, bool verbose, bool noDebugSupport, bool optimize, bool xml, bool ppstyle, 
    const std::string& version, soul::common::ModuleMap& moduleMap);

} // namespace soul::spg
