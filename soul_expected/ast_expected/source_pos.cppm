// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.ast.source.pos;

import std;

export namespace soul_expected::ast {

struct SourcePos
{
    inline SourcePos() : pos(-1), file(-1), line(0), col(0) {}
    inline SourcePos(int line_, int col_) : pos(-1), file(-1), line(line_), col(col_) {}
    inline SourcePos(int file_, int line_, int col_) : pos(-1), file(file_), line(line_), col(col_) {}
    inline SourcePos(std::int64_t pos_, int line_, int col_) : pos(pos_), file(-1), line(line_), col(col_) {}
    inline SourcePos(std::int64_t pos_, int file_, int line_, int col_) : pos(pos_), file(file_), line(line_), col(col_) {}
    inline bool IsValid() const { return line != 0; }
    std::int64_t pos;
    int file;
    int line;
    int col;
};

inline bool operator==(const SourcePos& left, const SourcePos& right)
{
    return left.file == right.file && left.line == right.line && left.col == right.col;
}

inline bool operator<(const SourcePos& left, const SourcePos& right)
{
    if (left.file < right.file) return true;
    if (left.file > right.file) return false;
    if (left.line < right.line) return true;
    if (left.line > right.line) return false;
    return left.col < right.col;
}

std::string ToString(const SourcePos& sourcePos);

} // namespace soul_expected::ast

export namespace soul_expected::ast::source::pos {

} // namespace soul_expected::ast::source::pos
