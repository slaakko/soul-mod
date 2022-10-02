
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/module_dependency.parser' using soul parser generator spg version 4.1.0

export module otava.parser.module_dependency;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

using namespace otava::symbols::context;
using namespace otava::ast;

export namespace otava::parser::module_dependency {

template<typename Lexer>
struct ModuleDependencyParser
{
    static std::unique_ptr<otava::ast::Node> Parse(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ModuleUnit(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match GlobalModuleFragment(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DeclarationSeq(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Declaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ExportImportDeclaration(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::module_dependency
