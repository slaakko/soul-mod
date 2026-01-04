// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.pp;

import otava.lexer;
import soul.lexer;

export namespace otava::pp {

void PreprocessPPLine(soul::lexer::Lexer<otava::lexer::OtavaLexer<char32_t>, char32_t>* lxr, 
    const soul::lexer::Token<char32_t, soul::lexer::LexerBase<char32_t>>* token);

} // namespace otava::pp
