
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/expression.parser' using soul parser generator spg version 4.1.0

export module otava.parser.expression;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

using namespace otava::symbols::context;
using namespace otava::ast;

export namespace otava::parser::expression {

template<typename Lexer>
struct ExpressionParser
{
    static soul::parser::Match Expression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ConstantExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AssignmentExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AssignmentOp(Lexer& lexer);
    static soul::parser::Match ConditionalExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match YieldExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ThrowExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match LogicalOrExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match LogicalAndExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match InclusiveOrExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ExclusiveOrExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AndExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match EqualityExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match EqualityOp(Lexer& lexer);
    static soul::parser::Match RelationalExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RelationalOp(Lexer& lexer, bool rejectRAngle);
    static soul::parser::Match CompareExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ShiftExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ShiftOp(Lexer& lexer);
    static soul::parser::Match AdditiveExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AdditiveOp(Lexer& lexer);
    static soul::parser::Match MultiplicativeExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match MultiplicativeOp(Lexer& lexer);
    static soul::parser::Match PmExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match PmOp(Lexer& lexer);
    static soul::parser::Match CastExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match UnaryExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match UnaryOp(Lexer& lexer);
    static soul::parser::Match AwaitExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match SizeOfExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AlignOfExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NoexceptEpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NewExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NewPlacement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NewInitializer(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NewTypeId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NewDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match NoPtrNewDeclarator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DeleteExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match PostfixExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match CppCastExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeIdExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match IntrinsicInvokeExpr(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match PrimaryExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match FoldExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match FoldOp(Lexer& lexer);
    static soul::parser::Match ParenthesizedExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DotOp(Lexer& lexer);
    static soul::parser::Match ArrowOp(Lexer& lexer);
    static soul::parser::Match IdExpression(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match IdExpr(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ExpressionList(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* container);
};

} // namespace otava::parser::expression
