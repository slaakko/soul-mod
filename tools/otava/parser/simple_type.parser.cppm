
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/parser/simple_type.parser' using soul parser generator spg version 5.0.0

export module otava.parser.simple.type;

import std;
import soul.lexer;
import soul.parser;
import otava.symbols.context;

export namespace otava::parser::simple::type {

template<typename LexerT>
struct SimpleTypeParser
{
    static soul::parser::Match SimpleType(LexerT& lexer);
};

} // namespace otava::parser::simple::type
