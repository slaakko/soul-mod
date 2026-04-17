import std;
import util;
import string_parser.lexer;
import string_parser.parser;

std::vector<std::string> ParseStringList(const std::string& text)
{
    std::u32string s = util::ToUtf8(text);
    soul::lexer::Lexer<string_lexer<char32_t>, char32_t> lxr = string_parser::lexer::MakeLexer(s.c_str(), s.c_str() + s.length(), "<text>");
    std::vector<std::string> stringList = string_parser::parser::string_parser< soul::lexer::Lexer<string_lexer<char32_t>, char32_t>>::Parse(lxr);
    return stringList;
}
