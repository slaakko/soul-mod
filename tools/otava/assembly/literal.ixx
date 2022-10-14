// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.literal;

import std.core;
import otava.assembly.value;

export namespace otava::assembly {

class Literal : public Value
{
public:
    Literal(int64_t value_);
    int64_t GetValue() const { return value; }
private:
    int64_t value;
};

} // namespace otava::assembly
