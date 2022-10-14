// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.context;

import otava.assembly.literal;
import otava.assembly.expr;
import otava.assembly.symbol;

namespace otava::assembly {

Context::Context() : registers(), registerPool(registers)
{
}

Register* Context::GetLocalReg(int size)
{
    RegisterGroup* regGroup = registerPool.GetLocalRegisterGroup();
    return regGroup->GetReg(size);
}

Register* Context::GetGlobalReg(int size, RegisterGroupKind regGroupKind)
{
    RegisterGroup* regGroup = registerPool.GetGlobalRegisterGroup(regGroupKind);
    return regGroup->GetReg(size);
}

Value* Context::MakeLiteral(int64_t value)
{
    auto it = literalValueMap.find(value);
    if (it != literalValueMap.cend())
    {
        return it->second;
    }
    else
    {
        Value* literal = new Literal(value);
        values.push_back(std::unique_ptr<Value>(literal));
        literalValueMap[value] = literal;
        return literal;
    }
}

Value* Context::MakeContent(Value* value)
{
    auto it = contentValueMap.find(value);
    if (it != contentValueMap.cend())
    {
        return it->second;
    }
    else
    {
        Value* content = new Content(value);
        values.push_back(std::unique_ptr<Value>(content));
        contentValueMap[value] = content;
        return content;
    }
}

Value* Context::MakeSizePrefix(int size, Value* value)
{
    auto key = std::make_pair(size, value);
    auto it = sizePrefixValueMap.find(key);
    if (it != sizePrefixValueMap.cend())
    {
        return it->second;
    }
    else
    {
        Value* sizePrefix = new SizePrefix(size, value);
        values.push_back(std::unique_ptr<Value>(sizePrefix));
        sizePrefixValueMap[key] = sizePrefix;
        return sizePrefix;
    }
}

Value* Context::MakeBinaryExpr(Value* left, Value* right, Operator op)
{
    auto key = std::make_pair(std::make_pair(left, right), op);
    auto it = binaryExprValueMap.find(key);
    if (it != binaryExprValueMap.cend())
    {
        return it->second;
    }
    else
    {
        Value* value = new BinaryExpr(left, right, op);
        values.push_back(std::unique_ptr<Value>(value));
        binaryExprValueMap[key] = value;
        return value;
    }
}

Value* Context::MakeSymbol(const std::string& name)
{
    auto it = symbolValueMap.find(name);
    if (it != symbolValueMap.cend())
    {
        return it->second;
    }
    else
    {
        Value* value = new Symbol(name);
        values.push_back(std::unique_ptr<Value>(value));
        symbolValueMap[name] = value;
        return value;
    }
}

} // namespace otava::assembly
