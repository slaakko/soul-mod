// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.context;

import otava.assembly.literal;
import otava.assembly.expr;
import otava.assembly.symbol;

namespace otava::assembly {

void CheckSize(int64_t size, const std::string& message)
{
    if (size < 1 || size > 8)
    {
        throw std::runtime_error(message);
    }
}

Context::Context() : registers(), registerPool(new RegisterPool(registers))
{
}

void Context::ResetRegisterPool()
{
    registerPool.reset(new RegisterPool(registers));
}

Register* Context::GetLocalReg(int64_t size)
{
    CheckSize(size, "otava.assembly.GetLocalReg: invalid size");
    RegisterGroup* regGroup = registerPool->GetLocalRegisterGroup();
    return regGroup->GetReg(static_cast<int>(size));
}

Register* Context::GetGlobalReg(int64_t size, RegisterGroupKind regGroupKind)
{
    CheckSize(size, "otava.assembly.GetGlobalReg: invalid size");
    RegisterGroup* regGroup = registerPool->GetGlobalRegisterGroup(regGroupKind);
    return regGroup->GetReg(static_cast<int>(size));
}

Value* Context::MakeLiteral(int64_t value, int64_t size)
{
    auto key = std::make_pair(value, static_cast<int>(size));
    auto it = literalValueMap.find(key);
    if (it != literalValueMap.cend())
    {
        return it->second;
    }
    else
    {
        Value* literal = new Literal(value, static_cast<int>(size));
        values.push_back(std::unique_ptr<Value>(literal));
        literalValueMap[key] = literal;
        return literal;
    }
}

UniqueLiteral* Context::MakeUniqueLiteral(int64_t value, int64_t size)
{
    UniqueLiteral* literal = new UniqueLiteral(value, static_cast<int>(size));
    values.push_back(std::unique_ptr<Value>(literal));
    return literal;
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

Value* Context::MakeSizePrefix(int64_t size, Value* value)
{
    CheckSize(size, "otava.assembly.MakeSizePrefix: invalid size");
    auto key = std::make_pair(static_cast<int>(size), value);
    auto it = sizePrefixValueMap.find(key);
    if (it != sizePrefixValueMap.cend())
    {
        return it->second;
    }
    else
    {
        Value* sizePrefix = new SizePrefix(static_cast<int>(size), value);
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
