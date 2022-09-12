
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp/expression.parser' using soul parser generator spg version 4.1.0

export module soul.cpp.expression.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

using namespace soul::ast::cpp;

export namespace soul::cpp::expression::parser {

template<typename Lexer>
struct ExpressionParser
{
    static soul::parser::Match Expression(Lexer& lexer);
    static soul::parser::Match ConstantExpression(Lexer& lexer);
    static soul::parser::Match AssignmentExpression(Lexer& lexer);
    static soul::parser::Match AssignmentOp(Lexer& lexer);
    static soul::parser::Match ConditionalExpression(Lexer& lexer);
    static soul::parser::Match ThrowExpression(Lexer& lexer);
    static soul::parser::Match LogicalOrExpression(Lexer& lexer);
    static soul::parser::Match LogicalAndExpression(Lexer& lexer);
    static soul::parser::Match InclusiveOrExpression(Lexer& lexer);
    static soul::parser::Match ExclusiveOrExpression(Lexer& lexer);
    static soul::parser::Match AndExpression(Lexer& lexer);
    static soul::parser::Match EqualityExpression(Lexer& lexer);
    static soul::parser::Match EqOp(Lexer& lexer);
    static soul::parser::Match RelationalExpression(Lexer& lexer);
    static soul::parser::Match RelOp(Lexer& lexer);
    static soul::parser::Match ShiftExpression(Lexer& lexer);
    static soul::parser::Match ShiftOp(Lexer& lexer);
    static soul::parser::Match AdditiveExpression(Lexer& lexer);
    static soul::parser::Match AddOp(Lexer& lexer);
    static soul::parser::Match MultiplicativeExpression(Lexer& lexer);
    static soul::parser::Match MulOp(Lexer& lexer);
    static soul::parser::Match PmExpression(Lexer& lexer);
    static soul::parser::Match PmOp(Lexer& lexer);
    static soul::parser::Match CastExpression(Lexer& lexer);
    static soul::parser::Match UnaryExpression(Lexer& lexer);
    static soul::parser::Match UnaryOperator(Lexer& lexer);
    static soul::parser::Match PostfixExpression(Lexer& lexer);
    static soul::parser::Match PostCastExpression(Lexer& lexer);
    static soul::parser::Match ExpressionList(Lexer& lexer, soul::ast::cpp::Node* owner);
    static soul::parser::Match PrimaryExpression(Lexer& lexer);
    static soul::parser::Match IdExpression(Lexer& lexer);
    static soul::parser::Match TypeSpecifierOrTypeName(Lexer& lexer);
    static soul::parser::Match NewExpression(Lexer& lexer);
    static soul::parser::Match NewPlacement(Lexer& lexer, soul::ast::cpp::Node* owner);
    static soul::parser::Match NewTypeId(Lexer& lexer);
    static soul::parser::Match NewDeclarator(Lexer& lexer);
    static soul::parser::Match NewInitializer(Lexer& lexer, soul::ast::cpp::Node* owner);
    static soul::parser::Match DirectNewDeclarator(Lexer& lexer);
    static soul::parser::Match DeleteExpression(Lexer& lexer);
    static soul::parser::Match OperatorFunctionId(Lexer& lexer);
    static soul::parser::Match Operator(Lexer& lexer);
};

} // namespace soul::cpp::expression::parser
