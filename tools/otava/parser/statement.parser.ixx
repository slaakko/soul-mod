
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/statement.parser' using soul parser generator spg version 4.1.0

export module otava.parser.statement;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::statement {

template<typename Lexer>
struct StatementParser
{
    static soul::parser::Match Statement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match LabeledStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match CompoundStatementUnguarded(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RBraceNext(Lexer& lexer);
    static soul::parser::Match CompoundStatementGuarded(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match CompoundStatementSaved(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match CompoundStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match SelectionStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match IfStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match SwitchStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match IterationStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match WhileStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DoStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match RangeForStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ForRangeDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ForRangeInitializer(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ForStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match JumpStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match BreakStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ContinueStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ReturnStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match CoroutineReturnStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match GotoStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TryStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match HandlerSeq(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Handler(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ExceptionDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ExpressionStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DeclarationStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match InitStatement(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Condition(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::statement
