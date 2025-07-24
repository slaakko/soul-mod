
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/test/cpp_test/expression.parser' using soul parser generator espg version 5.0.0

export module soul_expected.cpp.expression.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.cpp;

using namespace soul_expected::ast::cpp;

export namespace soul_expected::cpp::expression::parser {

template<typename LexerT>
struct ExpressionParser
{
    static std::expected<soul_expected::parser::Match, int> Expression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ConstantExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> AssignmentExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> AssignmentOp(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ConditionalExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> LogicalOrExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> LogicalAndExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> InclusiveOrExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ExclusiveOrExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> AndExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> EqualityExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> EqOp(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> RelationalExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> RelOp(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ShiftExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ShiftOp(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> AdditiveExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> AddOp(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> MultiplicativeExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> MulOp(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> PmExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> PmOp(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> CastExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> UnaryExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> UnaryOperator(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> PostfixExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> PostCastExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ExpressionList(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::cpp::Node* owner);
    static std::expected<soul_expected::parser::Match, int> PrimaryExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> IdExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> TypeSpecifierOrTypeName(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> NewExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> NewPlacement(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::cpp::Node* owner);
    static std::expected<soul_expected::parser::Match, int> NewTypeId(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> NewDeclarator(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> NewInitializer(LexerT& lexer, soul_expected::ast::cpp::Context* context, soul_expected::ast::cpp::Node* owner);
    static std::expected<soul_expected::parser::Match, int> DirectNewDeclarator(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> DeleteExpression(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> OperatorFunctionId(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Operator(LexerT& lexer, soul_expected::ast::cpp::Context* context);
};

} // namespace soul_expected::cpp::expression::parser
