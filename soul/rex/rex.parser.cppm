
// this file has been automatically generated from 'C:/work/soul-mod/soul/rex/rex.parser' using soul parser generator spg version 4.1.0

export module soul.rex.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.rex.context;
import soul.rex.nfa;

using namespace soul::rex::context;
using namespace soul::rex::nfa;

export namespace soul::rex::parser {

template<typename Lexer>
struct RexParser
{
    static soul::rex::nfa::Nfa Parse(Lexer& lexer, soul::rex::context::Context* context);
    static soul::parser::Match RegularExpression(Lexer& lexer, soul::rex::context::Context* context);
    static soul::parser::Match Alternative(Lexer& lexer, soul::rex::context::Context* context);
    static soul::parser::Match Catenation(Lexer& lexer, soul::rex::context::Context* context);
    static soul::parser::Match Repetition(Lexer& lexer, soul::rex::context::Context* context);
    static soul::parser::Match Primary(Lexer& lexer, soul::rex::context::Context* context);
    static soul::parser::Match Class(Lexer& lexer, soul::rex::context::Context* context);
    static soul::parser::Match Range(Lexer& lexer, soul::rex::context::Context* context);
    static soul::parser::Match Char(Lexer& lexer);
};

} // namespace soul::rex::parser
