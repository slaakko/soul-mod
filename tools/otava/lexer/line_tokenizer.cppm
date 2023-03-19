export module soul.cpp20.lexer.line_tokenizer;

import std.core;
import soul.lexer;

export namespace soul::cpp20::lexer {

using Token = soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>;
    
std::vector<Token> TokenizeLine(const std::string& line, std::u32string& lineContent);

} // namespace soul::cpp20::lexer
