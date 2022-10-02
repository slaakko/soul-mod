
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/pp/pp.parser' using soul parser generator spg version 4.1.0

export module otava.pp.parser;

import std.core;
import soul.lexer;
import soul.parser;
import otava.pp.state;

using namespace otava::pp::state;

export namespace otava::pp::parser {

template<typename Lexer>
struct PPParser
{
    static void Parse(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match PPLIne(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match PPCommand(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match IfCommand(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match ElifCommand(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match IfdefCommand(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match IfndefCommand(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match ElseCommand(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match EndifCommand(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match DefineCommand(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match UndefCommand(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match IncludeCommand(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match Header(Lexer& lexer);
    static soul::parser::Match Expression(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match LogicalOrExpr(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match LogicalAndExpr(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match InclusiveOrExpression(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match ExclusiveOrExpression(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match AndExpression(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match EqualityExpression(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match RelationalExpression(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match ShiftExpression(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match AdditiveExpression(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match MultiplicativeExpression(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match UnaryExpression(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match PrimaryExpr(Lexer& lexer, otava::pp::state::State* state);
    static soul::parser::Match DefinedExpr(Lexer& lexer, otava::pp::state::State* state);
};

} // namespace otava::pp::parser
