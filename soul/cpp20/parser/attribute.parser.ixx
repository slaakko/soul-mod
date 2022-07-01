
// this file has been automatically generated from 'C:/work/soul-mod/soul/cpp20/parser/attribute.parser' using soul parser generator spg version 4.0.0

export module soul.cpp20.parser.attribute;

import std.core;
import soul.lexer;
import soul.parser;
import soul.cpp20.symbols.context;

using namespace soul::cpp20::symbols::context;

export namespace soul::cpp20::parser::attribute {

template<typename Lexer>
struct AttributeParser
{
    static soul::parser::Match AttributeSpecifierSeq(Lexer& lexer, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::parser::attribute
