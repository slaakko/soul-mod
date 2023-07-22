// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.spg.pp.style.code.generator;

import soul.spg.pp.style.code.generator.visitor;

namespace soul::spg {

void GeneratePPCode(soul::ast::spg::SpgFile* spgFile, bool verbose, bool noDebugSupport, const std::string& version, soul::lexer::FileMap& fileMap, soul::common::ModuleMap& moduleMap)
{
    moduleMap.MapModule("soul.lexer", "../lexer/lexer.hpp");
    moduleMap.MapModule("soul.parser", "../parser/parser.hpp");
    moduleMap.MapModule("soul.lexer.trivial", "../lexer/trivial_lexer.hpp");
    moduleMap.MapModule("util", "../util/util.hpp");
    moduleMap.MapModule("soul.ast.spg", "../ast/spg.hpp");
    PPStyleCodeGeneratorVisitor visitor(spgFile, verbose, noDebugSupport, version, fileMap, moduleMap);
    spgFile->Accept(visitor);
}

} // namespace soul::spg
