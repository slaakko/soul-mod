// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.pp.style.code.generator;

import soul.ast.spg;
import soul.lexer.file.map;
import soul.common.module_map;
import std;

export namespace soul::spg {

void GeneratePPCode(soul::ast::spg::SpgFile* spgFile, bool verbose, bool noDebugSupport, const std::string& version, soul::lexer::FileMap& fileMap, soul::common::ModuleMap& moduleMap);

} // namespace soul::spg
