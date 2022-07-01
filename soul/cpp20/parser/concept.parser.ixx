
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/concept.parser' using soul parser generator spg version 4.0.0

export module soul.cpp20.parser.concepts;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::concepts {

template<typename Lexer>
struct ConceptParser
{
    static soul::parser::Match RequiresClause(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ConstraintLogicalOrExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match RequiresExpression(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeConstraint(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::concepts
