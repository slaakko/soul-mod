
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/parser/identifier.parser' using soul parser generator spg version 4.1.0

export module otava.parser.identifier;

import std.core;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

using namespace otava::symbols::context;

export namespace otava::parser::identifier {

template<typename Lexer>
struct IdentifierParser
{
    static soul::parser::Match Identifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match UnqualifiedId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match QualifiedId(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Template(Lexer& lexer);
    static soul::parser::Match NestedNameSpecifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match IdentifierList(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeIdentifier(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeIdentifierUnchecked(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match TypeIdentifierChecked(Lexer& lexer, otava::symbols::Context* context);
    static soul::parser::Match Unnamed(Lexer& lexer);
};

} // namespace otava::parser::identifier
