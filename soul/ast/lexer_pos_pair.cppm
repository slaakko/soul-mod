// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.ast.lexer.pos.pair;

import std;

export namespace soul::ast::lexer::pos::pair {

struct LexerPosPair
{
    LexerPosPair() : start(-1), end(-1) {}
    LexerPosPair(std::int64_t start_, std::int64_t end_) { start = start_; end = end_; }
    bool IsValid() const { return start != -1 && end != -1; }
    std::int64_t start;
    std::int64_t end;
};

} // namespace soul::ast::lexer::pos::pair
