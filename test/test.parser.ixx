
// this file has been automatically generated from 'C:/work/soul-mod/test/test.parser' using soul parser generator spg version 4.1.0

export module test.parser;

import std.core;
import soul.lexer;
import soul.parser;

export namespace test::parser {

template<typename Lexer>
struct TestParser
{
    static int Parse(Lexer& lexer);
    static soul::parser::Match ClassKey(Lexer& lexer);
};

} // namespace test::parser
