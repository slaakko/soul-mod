// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.literal;

import std;
import otava.assembly.value;

export namespace otava::assembly {

class UniqueLiteral;

class Literal : public Value
{
public:
    Literal(std::int64_t value_, int size_);
    std::int64_t GetValue() const { return value; }
    friend class UniqueLiteral;
private:
    std::int64_t value;
    int size;
};

class UniqueLiteral : public Literal
{
public:
    UniqueLiteral(std::int64_t value_, int size_);
    void SetValue(std::int64_t value_);
    std::string ToString() const override;
};

} // namespace otava::assembly
