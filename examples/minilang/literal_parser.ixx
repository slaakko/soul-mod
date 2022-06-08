
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/literal_parser.parser' using soul parser generator spg version 4.0.0

export module minilang.parser.literal;

import std.core;
import soul.lexer;
import soul.parser;

export namespace minilang::parser::literal {

template<typename Lexer>
struct LiteralParser
{
    static soul::parser::Match Literal(Lexer& lexer);
    static soul::parser::Match BooleanLiteral(Lexer& lexer);
    static soul::parser::Match IntegerLiteral(Lexer& lexer);
};

} // namespace minilang::parser::literal
