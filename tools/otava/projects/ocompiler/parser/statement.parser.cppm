
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/statement.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.statement;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

export namespace otava::parser::statement {

template<typename LexerT>
struct StatementParser
{
    static std::expected<soul::parser::Match, int> Statement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> LabeledStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> CompoundStatementUnguarded(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RBraceNext(LexerT& lexer);
    static std::expected<soul::parser::Match, int> CompoundStatementGuarded(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> CompoundStatementSaved(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> CompoundStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> SelectionStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> IfStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> SwitchStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> IterationStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> WhileStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DoStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> RangeForStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ForRangeDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ForRangeInitializer(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ForStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> JumpStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> BreakStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ContinueStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ReturnStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> CoroutineReturnStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> GotoStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ExpressionStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DeclarationStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> InitStatement(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Condition(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::statement
