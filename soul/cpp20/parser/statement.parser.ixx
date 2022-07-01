
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/statement.parser' using soul parser generator spg version 4.0.0

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
    static soul::parser::Match CompoundStatement(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match HandlerSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::statement
