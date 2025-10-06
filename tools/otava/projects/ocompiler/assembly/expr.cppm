// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.expr;

import otava.assembly.value;
import std;

export namespace otava::assembly {

enum class Operator
{
    add, sub, mul
};

class UnaryExpr : public Value
{
public:
    UnaryExpr(ValueKind kind_, Value* value_, const std::string& str_);
    inline Value* GetValue() const { return value; }
private:
    Value* value;
};

class BinaryExpr : public Value
{
public:
    BinaryExpr(Value* left_, Value* right_, Operator op_);
    inline Value* Left() { return left; }
    inline Value* Right() { return right; }
    inline Operator Op() const { return op; }
    std::string ToString() const override;
private:
    Value* left;
    Value* right;
    Operator op;
};

class Content : public UnaryExpr
{
public:
    Content(Value* value_);
    std::string ToString() const override;
};

class SizePrefix : public UnaryExpr
{
public:
    SizePrefix(int size_, Value* value_);
    inline int Size() const { return size; }
    std::string ToString() const override;
private:
    int size;
};

} // namespace otava::assembly
