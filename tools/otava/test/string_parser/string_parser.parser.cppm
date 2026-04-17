
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/test/string_parser/string_parser.parser' using soul parser generator ospg version 5.0.0

export module string_parser.parser;

import std;
import soul.lexer;
import soul.parser;

export namespace string_parser::parser {

template<typename LexerT>
struct str_parser
{
    static std::vector<std::string> Parse(LexerT& lexer);
    static soul::parser::Match names(LexerT& lexer);
    static soul::parser::Match name(LexerT& lexer);
};

} // namespace string_parser::parser
