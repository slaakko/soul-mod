
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/type.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.type;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

export namespace otava::parser::type {

template<typename LexerT>
struct TypeParser
{
    static std::expected<soul::parser::Match, int> TypeSpecifierSeq(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeSpecifierSeqReset(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DefiningTypeId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DefiningTypeSpecifierSeq(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DefiningTypeSpecifierReset(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DefiningTypeSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> ElaboratedTypeSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> SimpleTypeSpecifierReset(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> SimpleTypeSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeName(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypenameSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> DeclTypeSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> PlaceholderTypeSpecifier(LexerT& lexer, otava::symbols::Context* context);
};

} // namespace otava::parser::type
