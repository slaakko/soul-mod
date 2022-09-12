
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp/statement.parser' using soul parser generator spg version 4.1.0

export module soul.cpp.statement.parser;

import std.core;
import soul.lexer;
import soul.parser;
import soul.ast.cpp;

using namespace soul::ast::cpp;

export namespace soul::cpp::statement::parser {

template<typename Lexer>
struct StatementParser
{
    static soul::parser::Match Statement(Lexer& lexer);
    static soul::parser::Match LabeledStatement(Lexer& lexer);
    static soul::parser::Match EmptyStatement(Lexer& lexer);
    static soul::parser::Match CompoundStatement(Lexer& lexer);
    static soul::parser::Match SelectionStatement(Lexer& lexer);
    static soul::parser::Match IfStatement(Lexer& lexer);
    static soul::parser::Match SwitchStatement(Lexer& lexer);
    static soul::parser::Match IterationStatement(Lexer& lexer);
    static soul::parser::Match WhileStatement(Lexer& lexer);
    static soul::parser::Match DoStatement(Lexer& lexer);
    static soul::parser::Match RangeForStatement(Lexer& lexer);
    static soul::parser::Match ForRangeDeclaration(Lexer& lexer);
    static soul::parser::Match ForStatement(Lexer& lexer);
    static soul::parser::Match ForInitStatement(Lexer& lexer);
    static soul::parser::Match JumpStatement(Lexer& lexer);
    static soul::parser::Match BreakStatement(Lexer& lexer);
    static soul::parser::Match ContinueStatement(Lexer& lexer);
    static soul::parser::Match ReturnStatement(Lexer& lexer);
    static soul::parser::Match GotoStatement(Lexer& lexer);
    static soul::parser::Match DeclarationStatement(Lexer& lexer);
    static soul::parser::Match Condition(Lexer& lexer);
    static soul::parser::Match TryStatement(Lexer& lexer);
    static soul::parser::Match HandlerSeq(Lexer& lexer, soul::ast::cpp::TryStatementNode* tryStatement);
    static soul::parser::Match Handler(Lexer& lexer);
    static soul::parser::Match ExceptionDeclaration(Lexer& lexer);
    static soul::parser::Match ExpressionStatement(Lexer& lexer);
};

} // namespace soul::cpp::statement::parser
