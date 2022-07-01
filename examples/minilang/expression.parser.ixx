
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/expression.parser' using soul parser generator spg version 4.0.0

export module minilang.parser.expression;

import std.core;
import soul.lexer;
import soul.parser;
import minilang.ast;

using namespace minilang::ast;

export namespace minilang::parser::expression {

template<typename Lexer>
struct ExpressionParser
{
    static soul::parser::Match Expression(Lexer& lexer);
    static soul::parser::Match PrimaryExpression(Lexer& lexer);
    static soul::parser::Match PostfixExpression(Lexer& lexer);
    static soul::parser::Match ExpressionList(Lexer& lexer, minilang::ast::Node* owner);
    static soul::parser::Match UnaryExpression(Lexer& lexer);
    static soul::parser::Match UnaryOperator(Lexer& lexer);
    static soul::parser::Match MultiplicativeExpression(Lexer& lexer);
    static soul::parser::Match MultiplicativeOperator(Lexer& lexer);
    static soul::parser::Match AdditiveExpression(Lexer& lexer);
    static soul::parser::Match AdditiveOperator(Lexer& lexer);
    static soul::parser::Match RelationalExpression(Lexer& lexer);
    static soul::parser::Match RelationalOperator(Lexer& lexer);
    static soul::parser::Match EqualityExpression(Lexer& lexer);
    static soul::parser::Match EqualityOperator(Lexer& lexer);
};

} // namespace minilang::parser::expression
