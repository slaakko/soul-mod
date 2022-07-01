
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/module_dependency.parser' using soul parser generator spg version 4.0.0

export module soul.cpp20.parser.module_dependency;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;
import soul.cpp20.ast;

using namespace soul::cpp20::symbols::context;
using namespace soul::cpp20::ast;

export namespace soul::cpp20::parser::module_dependency {

template<typename Lexer>
struct ModuleDependencyParser
{
    static std::unique_ptr<soul::cpp20::ast::Node> Parse(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ModuleUnit(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match GlobalModuleFragment(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DeclarationSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Declaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ExportImportDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::module_dependency
