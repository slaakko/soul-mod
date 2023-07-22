
// this file has been automatically generated from 'C:/work/soul-mod/examples/minilang/type.parser' using soul parser generator spg version 5.0.0

export module minilang.parser.type;

import std.core;
import soul.lexer;
import soul.parser;

export namespace minilang::parser::type {

template<typename LexerT>
struct TypeParser
{
    static soul::parser::Match Type(LexerT& lexer);
};

} // namespace minilang::parser::type
