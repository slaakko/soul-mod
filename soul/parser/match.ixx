// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.parser.match;

export namespace soul {

struct Match
{
    Match(bool hit_) : hit(hit_), value(nullptr) {}
    Match(bool hit_, void* value_) : hit(hit_), value(value_) {}
    bool hit;
    void* value;
};

} // namespace parser;
