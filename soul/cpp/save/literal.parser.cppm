
// this file has been automatically generated from 'D:/work/soul-mod/soul/cpp/literal.parser' using soul parser generator spg version 5.0.0

export module soul.cpp.literal.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

using namespace soul::ast::cpp;

export namespace soul::cpp::literal::parser {

template<typename LexerT>
struct LiteralParser
{
    static soul::parser::Match Literal(LexerT& lexer);
};

} // namespace soul::cpp::literal::parser
