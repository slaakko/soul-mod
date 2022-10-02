
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/type.parser' using soul parser generator spg version 4.1.0

export module otava.parser.type;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::type {

template<typename Lexer>
struct TypeParser
{
    static soul::parser::Match TypeSpecifierSeq(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeSpecifierSeqReset(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DefiningTypeId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DefiningTypeSpecifierSeq(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DefiningTypeSpecifierReset(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DefiningTypeSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ElaboratedTypeSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match SimpleTypeSpecifierReset(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match SimpleTypeSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeName(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypenameSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match DeclTypeSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match PlaceholderTypeSpecifier(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::type
