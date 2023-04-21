
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/attribute.parser' using soul parser generator spg version 4.1.0

export module otava.parser.attribute;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::attribute {

template<typename LexerT>
struct AttributeParser
{
    static soul::parser::Match AttributeSpecifierSeq(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeList(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static soul::parser::Match AttributeUsingPrefix(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeNamespace(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match Attribute(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeToken(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeScopedToken(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match AttributeArgumentClause(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match BalancedTokenSeq(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match BalancedToken(LexerT& lexer, otava::symbols::Context* context);
    static soul::parser::Match AlignmentSpecifier(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::attribute
