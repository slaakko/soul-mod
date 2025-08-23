
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ocpp/expression.parser' using soul parser generator oespg version 5.0.0

export module soul.cpp.expression.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

using namespace soul::ast::cpp;

export namespace soul::cpp::expression::parser {

template<typename LexerT>
struct ExpressionParser
{
    static std::expected<soul::parser::Match, int> Expression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ConstantExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> AssignmentExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> AssignmentOp(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ConditionalExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> LogicalOrExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> LogicalAndExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> InclusiveOrExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ExclusiveOrExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> AndExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> EqualityExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> EqOp(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> RelationalExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> RelOp(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ShiftExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ShiftOp(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> AdditiveExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> AddOp(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> MultiplicativeExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> MulOp(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> PmExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> PmOp(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> CastExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> UnaryExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> UnaryOperator(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> PostfixExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> PostCastExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ExpressionList(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::cpp::Node* owner);
    static std::expected<soul::parser::Match, int> PrimaryExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> IdExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> TypeSpecifierOrTypeName(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> NewExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> NewPlacement(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::cpp::Node* owner);
    static std::expected<soul::parser::Match, int> NewTypeId(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> NewDeclarator(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> NewInitializer(LexerT& lexer, soul::ast::cpp::Context* context, soul::ast::cpp::Node* owner);
    static std::expected<soul::parser::Match, int> DirectNewDeclarator(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> DeleteExpression(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> OperatorFunctionId(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Operator(LexerT& lexer, soul::ast::cpp::Context* context);
};

} // namespace soul::cpp::expression::parser
