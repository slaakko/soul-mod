
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/simple_type.parser' using soul parser generator spg version 4.0.0

export module soul.cpp20.parser.simple.type;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::simple::type {

template<typename Lexer>
struct SimpleTypeParser
{
    static soul::parser::Match SimpleType(Lexer& lexer);
};

} // namespace soul::cpp20::parser::simple::type
