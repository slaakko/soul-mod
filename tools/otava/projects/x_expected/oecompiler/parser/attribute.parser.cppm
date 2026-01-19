
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/attribute.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.attribute;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::attribute {

template<typename LexerT>
struct AttributeParser
{
    static std::expected<soul::parser::Match, int> AttributeSpecifierSeq(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AttributeSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AttributeList(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static std::expected<soul::parser::Match, int> AttributeUsingPrefix(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AttributeNamespace(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Attribute(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AttributeToken(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AttributeScopedToken(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AttributeArgumentClause(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> BalancedTokenSeq(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> BalancedToken(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> AlignmentSpecifier(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::attribute
