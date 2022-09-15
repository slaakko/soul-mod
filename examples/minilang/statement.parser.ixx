
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/statement.parser' using soul parser generator spg version 4.1.0

export module minilang.parser.statement;

import std.core;
import soul.lexer;
import soul.parser;

export namespace minilang::parser::statement {

template<typename Lexer>
struct StatementParser
{
    static soul::parser::Match Statement(Lexer& lexer);
    static soul::parser::Match IfStatement(Lexer& lexer);
    static soul::parser::Match WhileStatement(Lexer& lexer);
    static soul::parser::Match ReturnStatement(Lexer& lexer);
    static soul::parser::Match CompoundStatement(Lexer& lexer);
    static soul::parser::Match ConstructionStatement(Lexer& lexer);
    static soul::parser::Match AssignmentStatement(Lexer& lexer);
};

} // namespace minilang::parser::statement
