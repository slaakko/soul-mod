// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.spg.token.parser;

import std.core;
import soul.lexer;

export namespace soul::spg::token::parser {

template<typename Char>
char32_t ParseCharLiteral(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    return char32_t(); // todo
}

template<typename Char>
std::u32string ParseStringLiteral(const std::string& fileName, const soul::lexer::Token<Char, soul::lexer::LexerBase<Char>>& token)
{
    return std::u32string(); // todo
}

} // namespace soul::spg
