
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/pp/pp.parser' using soul parser generator ospg version 5.0.0

export module otava.pp.parser;

import std;
import soul.lexer;
import soul.parser;
import otava.pp.state;

export namespace otava::pp::parser {

template<typename LexerT>
struct PPParser
{
    static std::expected<bool, int> Parse(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> PPLIne(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> PPCommand(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> IfCommand(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> ElifCommand(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> IfdefCommand(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> IfndefCommand(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> ElseCommand(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> EndifCommand(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> DefineCommand(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> UndefCommand(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> IncludeCommand(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> PragmaCommand(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> Header(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Expression(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> LogicalOrExpr(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> LogicalAndExpr(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> InclusiveOrExpression(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> ExclusiveOrExpression(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> AndExpression(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> EqualityExpression(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> RelationalExpression(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> ShiftExpression(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> AdditiveExpression(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> MultiplicativeExpression(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> UnaryExpression(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> PrimaryExpr(LexerT& lexer, otava::pp::state::State* state);
    static std::expected<soul::parser::Match, int> DefinedExpr(LexerT& lexer, otava::pp::state::State* state);
};

} // namespace otava::pp::parser
