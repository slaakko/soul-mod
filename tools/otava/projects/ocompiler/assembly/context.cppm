// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.context;

import otava.assembly.reg;
import otava.assembly.expr;
import std;

export namespace otava::assembly {

class IntegerLiteral;
class Symbol;
class Macro;
class Function;
class File;
class Value;

class Context
{
public:
    Context();
    inline void SetFile(File* file_) { file = file_; }
    inline File* GetFile() const { return file; }
    inline RegisterPool* GetRegisterPool() { return registerPool.get(); }
    void ResetRegisterPool();
    inline void SetCurrentFunction(Function* function) { currentFunction = function; }
    std::expected<Register*, int> GetLocalReg(std::int64_t size);
    std::expected<Register*, int> GetGlobalReg(std::int64_t size, RegisterGroupKind regGroupKind);
    std::expected<Register*, int> GetGlobalReg(std::int64_t size, RegisterGroupKind regGroupKind, bool used);
    IntegerLiteral* MakeIntegerLiteral(std::int64_t value, int size);
    std::expected<Value*, int> MakeFloatLiteralSymbol(float value);
    std::expected<Value*, int> MakeDoubleLiteralSymbol(double value);
    Symbol* MakeSymbol(const std::string& symbolName);
    Macro* MakeMacro(const std::string& name);
    Value* MakeContent(Value* value);
    std::expected<Value*, int> MakeSizePrefix(std::int64_t size, Value* value);
    Value* MakeBinaryExpr(Value* left, Value* right, Operator op);
    inline int GetNextJumpTabLabelId() { return jumpTabLabelCounter++; }
private:
    Registers registers;
    File* file;
    std::unique_ptr<RegisterPool> registerPool;
    std::vector<std::unique_ptr<Value>> values;
    Function* currentFunction;
    int floatingLiteralCounter;
    int jumpTabLabelCounter;
};

} // otava::assembly
