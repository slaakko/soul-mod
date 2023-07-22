
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp/statement.parser' using soul parser generator spg version 5.0.0

export module soul.cpp.statement.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

using namespace soul::ast::cpp;

export namespace soul::cpp::statement::parser {

template<typename LexerT>
struct StatementParser
{
    static soul::parser::Match Statement(LexerT& lexer);
    static soul::parser::Match LabeledStatement(LexerT& lexer);
    static soul::parser::Match EmptyStatement(LexerT& lexer);
    static soul::parser::Match CompoundStatement(LexerT& lexer);
    static soul::parser::Match SelectionStatement(LexerT& lexer);
    static soul::parser::Match IfStatement(LexerT& lexer);
    static soul::parser::Match SwitchStatement(LexerT& lexer);
    static soul::parser::Match IterationStatement(LexerT& lexer);
    static soul::parser::Match WhileStatement(LexerT& lexer);
    static soul::parser::Match DoStatement(LexerT& lexer);
    static soul::parser::Match RangeForStatement(LexerT& lexer);
    static soul::parser::Match ForRangeDeclaration(LexerT& lexer);
    static soul::parser::Match ForStatement(LexerT& lexer);
    static soul::parser::Match ForInitStatement(LexerT& lexer);
    static soul::parser::Match JumpStatement(LexerT& lexer);
    static soul::parser::Match BreakStatement(LexerT& lexer);
    static soul::parser::Match ContinueStatement(LexerT& lexer);
    static soul::parser::Match ReturnStatement(LexerT& lexer);
    static soul::parser::Match GotoStatement(LexerT& lexer);
    static soul::parser::Match DeclarationStatement(LexerT& lexer);
    static soul::parser::Match Condition(LexerT& lexer);
    static soul::parser::Match TryStatement(LexerT& lexer);
    static soul::parser::Match HandlerSeq(LexerT& lexer, soul::ast::cpp::TryStatementNode* tryStatement);
    static soul::parser::Match Handler(LexerT& lexer);
    static soul::parser::Match ExceptionDeclaration(LexerT& lexer);
    static soul::parser::Match ExpressionStatement(LexerT& lexer);
};

} // namespace soul::cpp::statement::parser
