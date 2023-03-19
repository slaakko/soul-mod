
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/module.parser' using soul parser generator spg version 4.1.0

export module otava.parser.modules;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::modules {

template<typename Lexer>
struct ModuleParser
{
    static soul::parser::Match ModuleDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ModuleName(Lexer& lexer);
    static soul::parser::Match ExportDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ImportDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ModulePartition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ExportKeyword(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ImportKeyword(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ModuleKeyword(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match GlobalModuleFragment(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match PrivateModuleFragment(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match HeaderName(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::modules
