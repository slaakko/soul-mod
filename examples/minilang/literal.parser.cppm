
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/literal.parser' using soul parser generator spg version 5.0.0

export module minilang.parser.literal;

import std.core;
import soul.lexer;
import soul.parser;

export namespace minilang::parser::literal {

template<typename LexerT>
struct LiteralParser
{
    static soul::parser::Match Literal(LexerT& lexer);
    static soul::parser::Match BooleanLiteral(LexerT& lexer);
    static soul::parser::Match IntegerLiteral(LexerT& lexer);
};

} // namespace minilang::parser::literal
