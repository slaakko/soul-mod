
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/expression.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.expression;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::expression {

template<typename LexerT>
struct ExpressionParser
{
    static std::expected<soul::parser::Match, int> Expression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ConstantExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AssignmentExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AssignmentOp(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ConditionalExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> YieldExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> LogicalOrExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> LogicalAndExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> InclusiveOrExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ExclusiveOrExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AndExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> EqualityExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> EqualityOp(LexerT& lexer);
    static std::expected<soul::parser::Match, int> RelationalExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RelationalOp(LexerT& lexer, bool rejectRAngle);
    static std::expected<soul::parser::Match, int> CompareExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ShiftExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ShiftOp(LexerT& lexer);
    static std::expected<soul::parser::Match, int> AdditiveExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AdditiveOp(LexerT& lexer);
    static std::expected<soul::parser::Match, int> MultiplicativeExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> MultiplicativeOp(LexerT& lexer);
    static std::expected<soul::parser::Match, int> PmExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> PmOp(LexerT& lexer);
    static std::expected<soul::parser::Match, int> CastExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> UnaryExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> UnaryOp(LexerT& lexer);
    static std::expected<soul::parser::Match, int> AwaitExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> SizeOfExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AlignOfExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NoexceptEpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NewExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NewPlacement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NewInitializer(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NewTypeId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NewDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> NoPtrNewDeclarator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DeleteExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> PostfixExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> CppCastExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeIdExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> IntrinsicInvokeExpr(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> PrimaryExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> FoldExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> FoldOp(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ParenthesizedExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DotOp(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ArrowOp(LexerT& lexer);
    static std::expected<soul::parser::Match, int> IdExpression(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> IdExpr(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ExpressionList(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container);
};

} // namespace otava::parser::expression
