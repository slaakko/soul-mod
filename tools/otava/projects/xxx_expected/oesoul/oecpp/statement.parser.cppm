
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/osoul/ocpp/statement.parser' using soul parser generator ospg version 5.0.0

export module soul.cpp.statement.parser;

import std;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

export namespace soul::cpp::statement::parser {

template<typename LexerT>
struct StatementParser
{
    static std::expected<soul::parser::Match, int> Statement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> LabeledStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> EmptyStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> CompoundStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> SelectionStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> IfStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> SwitchStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> IterationStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> WhileStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> DoStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> RangeForStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ForRangeDeclaration(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ForStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ForInitStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> JumpStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> BreakStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ContinueStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ReturnStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> GotoStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> DeclarationStatement(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> Condition(LexerT& lexer, soul::ast::cpp::Context* context);
    static std::expected<soul::parser::Match, int> ExpressionStatement(LexerT& lexer, soul::ast::cpp::Context* context);
};

} // namespace soul::cpp::statement::parser
