
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/identifier.parser' using soul parser generator spg version 4.1.0

export module minilang.parser.identifier;

import std.core;
import soul.lexer;
import soul.parser;

export namespace minilang::parser::identifier {

template<typename LexerT>
struct IdentifierParser
{
    static soul::parser::Match Identifier(LexerT& lexer);
};

} // namespace minilang::parser::identifier
