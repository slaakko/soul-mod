// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.ast.span;

import util_expected;
import std;

export namespace soul_expected::ast {

export namespace span {}

struct Span
{
    inline Span() : pos(-1), len(-1) {}
    inline Span(int pos_, int len_) : pos(pos_), len(len_) {}
    inline bool IsValid() const { return pos != -1; }
    inline bool Contains(int pos_) const { return pos_ >= pos && pos_ < pos + len; }
    void Union(const Span& that);
    int pos;
    int len;
};

constexpr bool operator==(const Span& left, const Span& right)
{
    return left.pos == right.pos && left.len == right.len;
}

constexpr bool operator!= (const Span& left, const Span& right)
{
    return !(left == right);
}

struct FullSpan
{
    inline FullSpan() : moduleId(util::nil_uuid()), fileIndex(-1), span() {}
    inline FullSpan(const util::uuid& moduleId_, int fileIndex_, const Span& span_) : moduleId(moduleId_), fileIndex(fileIndex_), span(span_) {}
    inline bool IsValid() const { return !moduleId.is_nil() && fileIndex != -1 && span.IsValid(); }
    util::uuid moduleId;
    int fileIndex;
    Span span;
};

inline bool operator==(const FullSpan& left, const FullSpan& right)
{
    return left.moduleId == right.moduleId && left.fileIndex == right.fileIndex && left.span == right.span;
}

inline bool operator!= (const FullSpan& left, const FullSpan& right)
{
    return !(left == right);
}

struct LineColLen
{
    inline LineColLen() : line(0), col(0), len(0) {}
    inline LineColLen(int line_, int col_) : line(line_), col(col_), len(0) {}
    inline LineColLen(int line_, int col_, int len_) : line(line_), col(col_), len(len_) {}
    inline bool IsValid() const { return line != 0; }
    int line;
    int col;
    int len;
};

bool operator==(const LineColLen& left, const LineColLen& right);
inline bool operator!=(const LineColLen& left, const LineColLen& right) { return !(left == right); }
bool operator<(const LineColLen& left, const LineColLen& right);

LineColLen SpanToLineColLen(const Span& span, const std::vector<int>& lineStarts);
int LineColLenToPos(const LineColLen& lineColLen, const std::vector<int>& lineStarts);

} // namespace soul_expected::ast
