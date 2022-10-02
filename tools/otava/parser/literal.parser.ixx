
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/literal.parser' using soul parser generator spg version 4.1.0

export module otava.parser.literal;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::literal {

template<typename Lexer>
struct LiteralParser
{
    static soul::parser::Match Literal(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match UserDefinedLiteral(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match UdSuffix(Lexer& lexer);
    static soul::parser::Match LiteralOperatorId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match StringLiteral(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::literal
