
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/optimized_parser/enum.parser' using soul parser generator spg version 4.1.0

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
    static soul::parser::Match EnumName(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match EnumSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match EnumHead(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match EnumKey(Lexer& lexer);
    static soul::parser::Match EnumHeadName(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match EnumBase(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match EnumeratorList(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container);
    static soul::parser::Match EnumeratorDefinition(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Enumerator(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match OpaqueEnumDeclaration(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ElaboratedEnumSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::enums
