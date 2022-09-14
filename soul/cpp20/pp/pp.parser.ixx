
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/pp/pp.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.pp.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.pp.state;

using namespace soul::cpp20::pp::state;

export namespace soul::cpp20::pp::parser {

template<typename Lexer>
struct PPParser
{
    static void Parse(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match PPLIne(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match PPCommand(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match IfCommand(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match ElifCommand(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match IfdefCommand(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match IfndefCommand(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match ElseCommand(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match EndifCommand(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match DefineCommand(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match UndefCommand(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match IncludeCommand(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match Header(Lexer& lexer);
    static soul::parser::Match Expression(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match LogicalOrExpr(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match LogicalAndExpr(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match InclusiveOrExpression(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match ExclusiveOrExpression(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match AndExpression(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match EqualityExpression(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match RelationalExpression(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match ShiftExpression(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match AdditiveExpression(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match MultiplicativeExpression(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match UnaryExpression(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match PrimaryExpr(Lexer& lexer, soul::cpp20::pp::state::State* state);
    static soul::parser::Match DefinedExpr(Lexer& lexer, soul::cpp20::pp::state::State* state);
};

} // namespace soul::cpp20::pp::parser
