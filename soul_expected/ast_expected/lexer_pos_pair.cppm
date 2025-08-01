// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.ast.lexer.pos.pair;

import std;

export namespace soul_expected::ast::lexer::pos::pair {

struct LexerPosPair
{
    inline LexerPosPair() : start(-1), end(-1) {}
    inline LexerPosPair(std::int64_t start_, std::int64_t end_) { start = start_; end = end_; }
    inline bool IsValid() const { return start != -1 && end != -1; }
    std::int64_t start;
    std::int64_t end;
};

} // namespace soul_expected::ast::lexer::pos::pair
