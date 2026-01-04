
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/parser/identifier.parser' using soul parser generator ospg version 5.0.0

export module otava.parser.identifier;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

export namespace otava::parser::identifier {

template<typename LexerT>
struct IdentifierParser
{
    static std::expected<soul::parser::Match, int> Identifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> UnqualifiedId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> QualifiedId(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Template(LexerT& lexer);
    static std::expected<soul::parser::Match, int> NestedNameSpecifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> IdentifierList(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeIdentifier(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeIdentifierUnchecked(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> TypeIdentifierChecked(LexerT& lexer, otava::symbols::Context* context);
    static std::expected<soul::parser::Match, int> Unnamed(LexerT& lexer);
};

} // namespace otava::parser::identifier
