// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.source.pos;

import std.core;

export namespace soul::lexer {

struct SourcePos
{
    SourcePos() : pos(-1), line(0), col(0) {}
    SourcePos(int line_, int col_) : pos(-1), line(line_), col(col_) {}
    SourcePos(int64_t pos_, int line_, int col_) : pos(pos_), line(line_), col(col_) {}
    bool IsValid() const { return line != 0; }
    int64_t pos;
    int line;
    int col;
};

inline bool operator==(const SourcePos& left, const SourcePos& right)
{
    return left.line == right.line && left.col == right.col;
}

inline bool operator<(const SourcePos& left, const SourcePos& right)
{
    if (left.line < right.line) return true;
    if (left.line > right.line) return false;
    return left.col < right.col;
}

} // namespace soul::lexer
