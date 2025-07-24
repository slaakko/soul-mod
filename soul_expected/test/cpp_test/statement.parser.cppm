
// this file has been automatically generated from 'D:/work/soul-mod/soul_expected/test/cpp_test/statement.parser' using soul parser generator espg version 5.0.0

export module soul_expected.cpp.statement.parser;

import std;
import soul_expected.lexer;
import soul_expected.parser;
import soul_expected.ast.cpp;

using namespace soul_expected::ast::cpp;

export namespace soul_expected::cpp::statement::parser {

template<typename LexerT>
struct StatementParser
{
    static std::expected<soul_expected::parser::Match, int> Statement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> LabeledStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> EmptyStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> CompoundStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> SelectionStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> IfStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> SwitchStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> IterationStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> WhileStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> DoStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> RangeForStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ForRangeDeclaration(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ForStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ForInitStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> JumpStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> BreakStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ContinueStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ReturnStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> GotoStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> DeclarationStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> Condition(LexerT& lexer, soul_expected::ast::cpp::Context* context);
    static std::expected<soul_expected::parser::Match, int> ExpressionStatement(LexerT& lexer, soul_expected::ast::cpp::Context* context);
};

} // namespace soul_expected::cpp::statement::parser
