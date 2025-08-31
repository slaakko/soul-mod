
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ore/re.parser' using soul parser generator ospg version 5.0.0

export module soul.re.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.re;

export namespace soul::re::parser {

template<typename LexerT>
struct RegExParser
{
    static std::expected<soul::ast::re::Nfa, int> Parse(LexerT& lexer, soul::ast::re::LexerContext* lexerContext);
    static std::expected<soul::parser::Match, int> RegularExpression(LexerT& lexer, soul::ast::re::LexerContext* lexerContext);
    static std::expected<soul::parser::Match, int> Alternative(LexerT& lexer, soul::ast::re::LexerContext* lexerContext);
    static std::expected<soul::parser::Match, int> Catenation(LexerT& lexer, soul::ast::re::LexerContext* lexerContext);
    static std::expected<soul::parser::Match, int> Repetition(LexerT& lexer, soul::ast::re::LexerContext* lexerContext);
    static std::expected<soul::parser::Match, int> Primary(LexerT& lexer, soul::ast::re::LexerContext* lexerContext);
    static std::expected<soul::parser::Match, int> Class(LexerT& lexer, soul::ast::re::LexerContext* lexerContext);
    static std::expected<soul::parser::Match, int> Range(LexerT& lexer, soul::ast::re::LexerContext* lexerContext);
    static std::expected<soul::parser::Match, int> Char(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ExpressionReference(LexerT& lexer);
};

} // namespace soul::re::parser
