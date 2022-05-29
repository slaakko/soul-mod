
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp/literal_parser.parser' using soul parser generator spg version 4.0.0

export module soul.cpp.literal.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

using namespace soul::ast::cpp;

export namespace soul::cpp::literal::parser {

template<typename Lexer>
struct LiteralParser
{
    static soul::parser::Match Literal(Lexer& lexer);
};

} // namespace soul::cpp::literal::parser
