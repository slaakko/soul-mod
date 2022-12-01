// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.literal;

import std.core;
import otava.assembly.value;

export namespace otava::assembly {

class UniqueLiteral;

class Literal : public Value
{
public:
    Literal(int64_t value_, int size_);
    int64_t GetValue() const { return value; }
    friend class UniqueLiteral;
private:
    int64_t value;
    int size;
};

class UniqueLiteral : public Literal
{
public:
    UniqueLiteral(int64_t value_, int size_);
    void SetValue(int64_t value_);
    std::string ToString() const override;
};

} // namespace otava::assembly
