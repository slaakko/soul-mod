// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.lexer.span;

import std.core;

export namespace soul::lexer {

struct Span
{
    Span() : fileIndex(-1), line(-1), start(-1), end(-1) {}
    Span(int fileIndex_, int line_, int start_) : fileIndex(fileIndex_), line(line_), start(start_), end(start) {}
    Span(int fileIndex_, int line_, int start_, int end_) : fileIndex(fileIndex_), line(line_), start(start_), end(end_) {}
    bool Valid() const { return fileIndex != -1 && line != -1 && start != -1 && end != -1; }
    int fileIndex;
    int line;
    int start;
    int end;
};

inline bool operator==(const Span& left, const Span& right)
{
    return left.fileIndex == right.fileIndex && left.line == right.line && left.start == right.start && left.end == right.end;
}

} // namespace soul::lexer
