
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/punctuation.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.punctuation;

import std;
import soul.lexer;
import soul.parser;

export namespace otava::parser::punctuation {

template<typename LexerT>
struct PunctuationParser
{
    static std::expected<soul::parser::Match, int> Semicolon(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Comma(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Quest(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Colon(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ColonColon(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Ellipsis(LexerT& lexer);
    static std::expected<soul::parser::Match, int> LParen(LexerT& lexer);
    static std::expected<soul::parser::Match, int> RParen(LexerT& lexer);
    static std::expected<soul::parser::Match, int> LBracket(LexerT& lexer);
    static std::expected<soul::parser::Match, int> RBracket(LexerT& lexer);
    static std::expected<soul::parser::Match, int> LBrace(LexerT& lexer);
    static std::expected<soul::parser::Match, int> RBrace(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Assign(LexerT& lexer);
};

} // namespace otava::parser::punctuation
