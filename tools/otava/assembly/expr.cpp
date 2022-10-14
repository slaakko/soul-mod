// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.expr;

namespace otava::assembly {

std::string MakeBinaryExprStr(Value* left, Value* right, Operator op)
{
    switch (op)
    {
        case Operator::add:
        {
            return left->Name() + "+" + right->Name();
        }
        case Operator::sub:
        {
            return left->Name() + "-" + right->Name();
        }
        case Operator::mul:
        {
            return left->Name() + "*" + right->Name();
        }
    }
    return std::string();
}

UnaryExpr::UnaryExpr(Value* value_, const std::string& str_) : Value(str_), value(value_)
{
}

BinaryExpr::BinaryExpr(Value* left_, Value* right_, Operator op_) : Value(MakeBinaryExprStr(left_, right_, op_)), left(left_), right(right_), op(op_)
{
}

Content::Content(Value* value_) : UnaryExpr(value_, "[" + value_->Name() + "]")
{
}

std::string SizePrefixStr(int size, Value* value)
{
    switch (size)
    {
        case 1: return "byte ptr " + value->Name();
        case 2: return "word ptr " + value->Name();
        case 4: return "dword ptr " + value->Name();
        case 8: return "qword ptr " + value->Name();
    }
    return std::string();
}

SizePrefix::SizePrefix(int size_, Value* value_) : UnaryExpr(value_, SizePrefixStr(size_, value_)), size(size_)
{
}

} // namespace otava::assembly
