// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.parser.value;

import std;

export namespace soul::parser {

template<class T>
struct Value
{
    inline Value(const T& value_) : value(value_) {}
    T value;
};

} // namespace soul::parser
