
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/type.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.type;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::type {

template<typename Lexer>
struct TypeParser
{
    static soul::parser::Match TypeSpecifierSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeSpecifierSeqReset(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DefiningTypeId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DefiningTypeSpecifierSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DefiningTypeSpecifierReset(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DefiningTypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match ElaboratedTypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match SimpleTypeSpecifierReset(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match SimpleTypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeName(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypeId(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match TypenameSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match DeclTypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match PlaceholderTypeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::type
