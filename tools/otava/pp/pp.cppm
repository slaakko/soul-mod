// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.pp;

import otava.lexer;
import soul.lexer;

export namespace otava::pp {

using Lexer = soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>;
using Token = Lexer::TokenType;

void PreprocessPPLine(Lexer& lexer, Token& token);

} // namespace soul::cpp20::pp
