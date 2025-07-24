// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.parser.value;

import std;

export namespace soul_expected::parser {

template<class T>
struct Value
{
    Value(const T& value_) : value(value_) {}
    T value;
};

} // namespace soul_expected::parser
