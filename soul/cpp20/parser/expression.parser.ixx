
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/expression.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.expression;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;
import soul.cpp20.ast;

using namespace soul::cpp20::symbols::context;
using namespace soul::cpp20::ast;

export namespace soul::cpp20::parser::expression {

template<typename Lexer>
struct ExpressionParser
{
    static soul::parser::Match Expression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ConstantExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AssignmentExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AssignmentOp(Lexer& lexer);
    static soul::parser::Match ConditionalExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match YieldExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ThrowExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match LogicalOrExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match LogicalAndExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match InclusiveOrExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ExclusiveOrExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AndExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match EqualityExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match EqualityOp(Lexer& lexer);
    static soul::parser::Match RelationalExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match RelationalOp(Lexer& lexer, bool rejectRAngle);
    static soul::parser::Match CompareExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ShiftExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ShiftOp(Lexer& lexer);
    static soul::parser::Match AdditiveExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AdditiveOp(Lexer& lexer);
    static soul::parser::Match MultiplicativeExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match MultiplicativeOp(Lexer& lexer);
    static soul::parser::Match PmExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match PmOp(Lexer& lexer);
    static soul::parser::Match CastExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match UnaryExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match UnaryOp(Lexer& lexer);
    static soul::parser::Match AwaitExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match SizeOfExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AlignOfExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NoexceptEpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NewExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NewPlacement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NewInitializer(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NewTypeId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NewDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match NoPtrNewDeclarator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DeleteExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match PostfixExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match CppCastExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeIdExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match IntrinsicInvokeExpr(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match PrimaryExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match FoldExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match FoldOp(Lexer& lexer);
    static soul::parser::Match ParenthesizedExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DotOp(Lexer& lexer);
    static soul::parser::Match ArrowOp(Lexer& lexer);
    static soul::parser::Match IdExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match IdExpr(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ExpressionList(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container);
};

} // namespace soul::cpp20::parser::expression
