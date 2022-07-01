
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/enum.parser' using soul parser generator spg version 4.0.0

export module soul.cpp20.parser.enums;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::enums {

template<typename Lexer>
struct EnumParser
{
    static soul::parser::Match EnumSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match OpaqueEnumDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ElaboratedEnumSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::enums
