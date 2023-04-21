
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/statement.parser' using soul parser generator spg version 4.1.0

export module minilang.parser.statement;

import std.core;
import soul.lexer;
import soul.parser;

export namespace minilang::parser::statement {

template<typename LexerT>
struct StatementParser
{
    static soul::parser::Match Statement(LexerT& lexer);
    static soul::parser::Match IfStatement(LexerT& lexer);
    static soul::parser::Match WhileStatement(LexerT& lexer);
    static soul::parser::Match ReturnStatement(LexerT& lexer);
    static soul::parser::Match CompoundStatement(LexerT& lexer);
    static soul::parser::Match ConstructionStatement(LexerT& lexer);
    static soul::parser::Match AssignmentStatement(LexerT& lexer);
};

} // namespace minilang::parser::statement
