
// this file has been automatically generated from 'C:/work/soul-mod/soul/re/re.parser' using soul parser generator spg version 4.1.0

export module soul.re.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.re;

using namespace soul::ast::re;

export namespace soul::re::parser {

template<typename Lexer>
struct RegExParser
{
    static soul::ast::re::Nfa Parse(Lexer& lexer, soul::ast::re::LexerContext* lexerContext);
    static soul::parser::Match RegularExpression(Lexer& lexer, soul::ast::re::LexerContext* lexerContext);
    static soul::parser::Match Alternative(Lexer& lexer, soul::ast::re::LexerContext* lexerContext);
    static soul::parser::Match Catenation(Lexer& lexer, soul::ast::re::LexerContext* lexerContext);
    static soul::parser::Match Repetition(Lexer& lexer, soul::ast::re::LexerContext* lexerContext);
    static soul::parser::Match Primary(Lexer& lexer, soul::ast::re::LexerContext* lexerContext);
    static soul::parser::Match Class(Lexer& lexer, soul::ast::re::LexerContext* lexerContext);
    static soul::parser::Match Range(Lexer& lexer, soul::ast::re::LexerContext* lexerContext);
    static soul::parser::Match Char(Lexer& lexer);
    static soul::parser::Match ExpressionReference(Lexer& lexer);
};

} // namespace soul::re::parser
