// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.parser.match;

import std;

export namespace soul::parser {

struct Match
{
    inline Match() noexcept : hit(false), value(nullptr) {}
    inline Match(bool hit_) noexcept : hit(hit_), value(nullptr) {}
    inline Match(bool hit_, void* value_) noexcept : hit(hit_), value(value_) {}
    bool hit;
    void* value;
};

} // namespace soul::parser;
