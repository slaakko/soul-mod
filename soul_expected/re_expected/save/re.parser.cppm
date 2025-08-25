
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/re_expected/re.parser' using soul parser generator espg version 5.0.0

export module soul_expected.re.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.re;

using namespace soul_expected::ast::re;

export namespace soul_expected::re::parser {

template<typename LexerT>
struct RegExParser
{
    static std::expected<soul_expected::ast::re::Nfa, int> Parse(LexerT& lexer, soul_expected::ast::re::LexerContext* lexerContext);
    static std::expected<soul_expected::parser::Match, int> RegularExpression(LexerT& lexer, soul_expected::ast::re::LexerContext* lexerContext);
    static std::expected<soul_expected::parser::Match, int> Alternative(LexerT& lexer, soul_expected::ast::re::LexerContext* lexerContext);
    static std::expected<soul_expected::parser::Match, int> Catenation(LexerT& lexer, soul_expected::ast::re::LexerContext* lexerContext);
    static std::expected<soul_expected::parser::Match, int> Repetition(LexerT& lexer, soul_expected::ast::re::LexerContext* lexerContext);
    static std::expected<soul_expected::parser::Match, int> Primary(LexerT& lexer, soul_expected::ast::re::LexerContext* lexerContext);
    static std::expected<soul_expected::parser::Match, int> Class(LexerT& lexer, soul_expected::ast::re::LexerContext* lexerContext);
    static std::expected<soul_expected::parser::Match, int> Range(LexerT& lexer, soul_expected::ast::re::LexerContext* lexerContext);
    static std::expected<soul_expected::parser::Match, int> Char(LexerT& lexer);
    static std::expected<soul_expected::parser::Match, int> ExpressionReference(LexerT& lexer);
};

} // namespace soul_expected::re::parser
