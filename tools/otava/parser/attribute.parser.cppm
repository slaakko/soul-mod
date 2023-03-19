
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/attribute.parser' using soul parser generator spg version 4.1.0

export module otava.parser.attribute;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::attribute {

template<typename Lexer>
struct AttributeParser
{
    static soul::parser::Match AttributeSpecifierSeq(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeList(Lexer& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static soul::parser::Match AttributeUsingPrefix(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeNamespace(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Attribute(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeToken(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeScopedToken(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeArgumentClause(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match BalancedTokenSeq(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match BalancedToken(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match AlignmentSpecifier(Lexer& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::attribute
