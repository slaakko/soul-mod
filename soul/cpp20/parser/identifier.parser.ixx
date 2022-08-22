
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/identifier.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.identifier;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::identifier {

template<typename Lexer>
struct IdentifierParser
{
    static soul::parser::Match Identifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match UnqualifiedId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match QualifiedId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Template(Lexer& lexer);
    static soul::parser::Match NestedNameSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match IdentifierList(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeIdentifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeIdentifierUnchecked(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeIdentifierChecked(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Unnamed(Lexer& lexer);
};

} // namespace soul::cpp20::parser::identifier
