
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp/identifier_parser.parser' using soul parser generator spg version 4.0.0

export module soul.cpp.identifier.par;

import std.core;
import soul.lexer;
import soul.parser;

export namespace soul::cpp::identifier::par {

template<typename Lexer>
struct CppIdentifierParser
{
    static soul::parser::Match CppIdentifier(Lexer& lexer);
    static soul::parser::Match QualifiedCppId(Lexer& lexer);
};

} // namespace soul::cpp::identifier::par
