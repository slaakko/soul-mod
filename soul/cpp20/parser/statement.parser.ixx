
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/statement.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.statement;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::statement {

template<typename Lexer>
struct StatementParser
{
    static soul::parser::Match Statement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match LabeledStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match CompoundStatementUnguarded(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match CompoundStatementGuarded(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match CompoundStatementSaved(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match CompoundStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match SelectionStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match IfStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match SwitchStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match IterationStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match WhileStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DoStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match RangeForStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ForRangeDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ForRangeInitializer(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ForStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match JumpStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match BreakStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ContinueStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ReturnStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match CoroutineReturnStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match GotoStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TryStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match HandlerSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Handler(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ExceptionDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DeclarationStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ExpressionStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match InitStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Condition(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::statement
