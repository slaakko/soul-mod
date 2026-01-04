
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/enum.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.enums;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;
import otava.ast;

export namespace otava::parser::enums {

template<typename LexerT>
struct EnumParser
{
    static std::expected<soul::parser::Match, int> EnumName(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> EnumSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> EnumHead(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> EnumKey(LexerT& lexer);
    static std::expected<soul::parser::Match, int> EnumHeadName(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> EnumBase(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> EnumeratorList(LexerT& lexer, otava::symbols::Context* context, otava::ast::Node* container);
    static std::expected<soul::parser::Match, int> EnumeratorDefinition(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Enumerator(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> OpaqueEnumDeclaration(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ElaboratedEnumSpecifier(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::enums
