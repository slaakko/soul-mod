
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/expression.parser' using soul parser generator spg version 4.1.0

export module minilang.parser.expression;

import std.core;
import soul.lexer;
import soul.parser;
import minilang.ast;

using namespace minilang::ast;

export namespace minilang::parser::expression {

template<typename LexerT>
struct ExpressionParser
{
    static soul::parser::Match Expression(LexerT& lexer);
    static soul::parser::Match PrimaryExpression(LexerT& lexer);
    static soul::parser::Match PostfixExpression(LexerT& lexer);
    static soul::parser::Match ExpressionList(LexerT& lexer, minilang::ast::Node* owner);
    static soul::parser::Match UnaryExpression(LexerT& lexer);
    static soul::parser::Match UnaryOperator(LexerT& lexer);
    static soul::parser::Match MultiplicativeExpression(LexerT& lexer);
    static soul::parser::Match MultiplicativeOperator(LexerT& lexer);
    static soul::parser::Match AdditiveExpression(LexerT& lexer);
    static soul::parser::Match AdditiveOperator(LexerT& lexer);
    static soul::parser::Match RelationalExpression(LexerT& lexer);
    static soul::parser::Match RelationalOperator(LexerT& lexer);
    static soul::parser::Match EqualityExpression(LexerT& lexer);
    static soul::parser::Match EqualityOperator(LexerT& lexer);
};

} // namespace minilang::parser::expression
