
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/rex_expected/rex.parser' using soul parser generator espg version 5.0.0

export module soul_expected.rex.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.rex.context;
import soul_expected.rex.nfa;

using namespace soul_expected::rex::context;
using namespace soul_expected::rex::nfa;

export namespace soul_expected::rex::parser {

template<typename LexerT>
struct RexParser
{
    static std::expected<soul_expected::rex::nfa::Nfa, int> Parse(LexerT& lexer, soul_expected::rex::context::Context* context);
    static std::expected<soul_expected::parser::Match, int> RegularExpression(LexerT& lexer, soul_expected::rex::context::Context* context);
    static std::expected<soul_expected::parser::Match, int> Alternative(LexerT& lexer, soul_expected::rex::context::Context* context);
    static std::expected<soul_expected::parser::Match, int> Catenation(LexerT& lexer, soul_expected::rex::context::Context* context);
    static std::expected<soul_expected::parser::Match, int> Repetition(LexerT& lexer, soul_expected::rex::context::Context* context);
    static std::expected<soul_expected::parser::Match, int> Primary(LexerT& lexer, soul_expected::rex::context::Context* context);
    static std::expected<soul_expected::parser::Match, int> Class(LexerT& lexer, soul_expected::rex::context::Context* context);
    static std::expected<soul_expected::parser::Match, int> Range(LexerT& lexer, soul_expected::rex::context::Context* context);
    static std::expected<soul_expected::parser::Match, int> Char(LexerT& lexer);
};

} // namespace soul_expected::rex::parser
