
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/literal.parser' using soul parser generator spg version 4.0.0

export module soul.cpp20.parser.literal;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::literal {

template<typename Lexer>
struct LiteralParser
{
    static soul::parser::Match Literal(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match UserDefinedLiteral(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match UdSuffix(Lexer& lexer);
    static soul::parser::Match LiteralOperatorId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match StringLiteral(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::literal
