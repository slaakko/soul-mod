
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/translation_unit.parser' using soul parser generator spg version 4.0.0

export module soul.cpp20.parser.translation.unit;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;
import soul.cpp20.ast;

using namespace soul::cpp20::symbols::context;
using namespace soul::cpp20::ast;

export namespace soul::cpp20::parser::translation::unit {

template<typename Lexer>
struct TranslationUnitParser
{
    static std::unique_ptr<soul::cpp20::ast::Node> Parse(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TranslationUnit(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ModuleUnit(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::translation::unit
