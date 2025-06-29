// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.context;

import std;
import otava.assembly.reg;
import otava.assembly.value;

export namespace otava::assembly {

enum class Operator;
class UniqueLiteral;

class Context
{
public:
    Context();
    RegisterPool& GetRegisterPool() { return *registerPool; }
    void ResetRegisterPool();
    Register* GetLocalReg(std::int64_t size);
    Register* GetGlobalReg(std::int64_t size, RegisterGroupKind regGroupKind);
    Value* MakeLiteral(std::int64_t value, std::int64_t size);
    UniqueLiteral* MakeUniqueLiteral(std::int64_t value, std::int64_t size);
    Value* MakeContent(Value* value);
    Value* MakeSizePrefix(std::int64_t size, Value* value);
    Value* MakeBinaryExpr(Value* left, Value* right, Operator op);
    Value* MakeSymbol(const std::string& name);
private:
    Registers registers;
    std::unique_ptr<RegisterPool> registerPool;
    std::vector<std::unique_ptr<Value>> values;
    std::map<std::pair<std::int64_t, int>, Value*> literalValueMap;
    std::map<Value*, Value*> contentValueMap;
    std::map<std::pair<int, Value*>, Value*> sizePrefixValueMap;
    std::map<std::pair<std::pair<Value*, Value*>, Operator>, Value*> binaryExprValueMap;
    std::map<std::string, Value*> symbolValueMap;
};

} // namespace otava::assembly

