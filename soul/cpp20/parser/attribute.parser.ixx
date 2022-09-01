
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/attribute.parser' using soul parser generator spg version 4.1.0

export module soul.cpp20.parser.attribute;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::attribute {

template<typename Lexer>
struct AttributeParser
{
    static soul::parser::Match AttributeSpecifierSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AttributeSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AttributeList(Lexer& lexer, soul::cpp20::symbols::Context* context, soul::cpp20::ast::Node* container);
    static soul::parser::Match AttributeUsingPrefix(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AttributeNamespace(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match Attribute(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AttributeToken(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AttributeScopedToken(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AttributeArgumentClause(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match BalancedTokenSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match BalancedToken(Lexer& lexer, soul::cpp20::symbols::Context* context);
    static soul::parser::Match AlignmentSpecifier(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::attribute
