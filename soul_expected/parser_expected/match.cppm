// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.parser.match;

import std;

export namespace soul_expected::parser {

struct Match
{
    inline Match(bool hit_) : hit(hit_), value(nullptr) {}
    inline Match(bool hit_, void* value_) : hit(hit_), value(value_) {}
    bool hit;
    void* value;
};

} // namespace soul_expected::parser;
