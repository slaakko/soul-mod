
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/simple_type.parser' using soul parser generator spg version 4.1.0

export module otava.parser.simple.type;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::simple::type {

template<typename Lexer>
struct SimpleTypeParser
{
    static soul::parser::Match SimpleType(Lexer& lexer);
};

} // namespace otava::parser::simple::type
