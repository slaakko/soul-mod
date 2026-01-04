// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.literal;

import otava.assembly.value;
import std;

export namespace otava::assembly {

const int maxAssemblyLineLength = 128;

class IntegerLiteral : public Value
{
public:
    IntegerLiteral(std::int64_t value_, int size_);
    inline std::int64_t GetValue() const { return value; }
private:
    std::int64_t value;
    int size;
};

class FloatLiteral : public Value
{
public:
    FloatLiteral(float value_);
    inline float GetValue() const { return value; }
private:
    float value;
};

class DoubleLiteral : public Value
{
public:
    DoubleLiteral(double value_);
    inline double GetValue() const { return value; }
private:
    double value;
};

class StringLiteral : public Value
{
public:
    StringLiteral(const std::string& value_);
    bool CanSplit() const override { return true; }
    Value* Split(int length) override;
    inline bool IsEmpty() const override { return value.empty(); }
    inline const std::string& GetValue() const { return value; }
private:
    std::string value;
};

} // namespace otava::assembly
