
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/optimized_parser/module.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.modules;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::modules {

template<typename Lexer>
struct ModuleParser
{
    static soul::parser::Match ModuleDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ModuleName(Lexer& lexer);
    static soul::parser::Match ExportDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ImportDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ModulePartition(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ExportKeyword(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ImportKeyword(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ModuleKeyword(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match GlobalModuleFragment(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match PrivateModuleFragment(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match HeaderName(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::modules
