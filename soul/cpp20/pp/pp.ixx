// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.pp;

import soul.cpp20.lexer;
import soul.lexer;

export namespace soul::cpp20::pp {

using Lexer = soul::lexer::Lexer<soul::cpp20::lexer::Cpp20Lexer<char32_t>, char32_t>;
using Token = Lexer::TokenType;

void PreprocessPPLine(Lexer& lexer, Token& token);

} // namespace soul::cpp20::pp
