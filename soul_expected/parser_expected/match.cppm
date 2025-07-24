// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.parser.match;

import std;

export namespace soul_expected::parser {

struct Match
{
    Match(bool hit_) : hit(hit_), value(nullptr) {}
    Match(bool hit_, void* value_) : hit(hit_), value(value_) {}
    bool hit;
    void* value;
};

} // namespace soul_expected::parser;
