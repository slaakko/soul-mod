// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.xpath.token.parser;

import std.core;
import soul.lexer.token;
import soul.lexer.base;

export namespace soul::xml::xpath::token::parser {

template<typename Char>
std::string ParseDQString(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    return std::string();
}

template<typename Char>
std::string ParseSQString(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    return std::string();
}

} // namespace soul::xml::xpath::token::parser
