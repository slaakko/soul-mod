// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.lexer.lexing.util;

import std;
import soul_expected.lexer.token;
import soul_expected.lexer.base;

export namespace soul_expected::lexer {

template<typename Char>
inline bool NoWhiteSpaceBetweenTokens(const soul_expected::lexer::Token<Char, LexerBase<Char>>& left, const soul_expected::lexer::Token<Char, LexerBase<Char>>& right)
{
    if (left.match.end == right.match.begin) return true;
    return false;
}

} // namespace soul_expected::lexer
