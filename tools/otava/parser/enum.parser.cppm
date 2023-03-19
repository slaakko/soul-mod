
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/enum.parser' using soul parser generator spg version 4.1.0

export module otava.parser.enums;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::enums {

template<typename Lexer>
struct EnumParser
{
    static soul::parser::Match EnumName(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match EnumSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match EnumHead(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match EnumKey(Lexer& lexer);
    static soul::parser::Match EnumHeadName(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match EnumBase(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match EnumeratorList(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static soul::parser::Match EnumeratorDefinition(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Enumerator(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match OpaqueEnumDeclaration(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match ElaboratedEnumSpecifier(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::enums
