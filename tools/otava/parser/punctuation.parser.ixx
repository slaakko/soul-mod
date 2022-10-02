
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/punctuation.parser' using soul parser generator spg version 4.1.0

export module otava.parser.punctuation;

import std.core;
import soul.lexer;
import soul.parser;

export namespace otava::parser::punctuation {

template<typename Lexer>
struct PunctuationParser
{
    static soul::parser::Match Semicolon(Lexer& lexer);
    static soul::parser::Match Comma(Lexer& lexer);
    static soul::parser::Match Quest(Lexer& lexer);
    static soul::parser::Match Colon(Lexer& lexer);
    static soul::parser::Match ColonColon(Lexer& lexer);
    static soul::parser::Match Ellipsis(Lexer& lexer);
    static soul::parser::Match LParen(Lexer& lexer);
    static soul::parser::Match RParen(Lexer& lexer);
    static soul::parser::Match LBracket(Lexer& lexer);
    static soul::parser::Match RBracket(Lexer& lexer);
    static soul::parser::Match LBrace(Lexer& lexer);
    static soul::parser::Match RBrace(Lexer& lexer);
    static soul::parser::Match Assign(Lexer& lexer);
};

} // namespace otava::parser::punctuation
