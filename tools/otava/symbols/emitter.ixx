// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.emitter;

import std.core;
import otava.intermediate.context;
import otava.intermediate.data;
import otava.intermediate.type;
import otava.intermediate.function;
import otava.symbols.ir_value_stack;
import util.uuid;

export namespace otava::symbols {

class Emitter
{
public:
    Emitter();
    ~Emitter();
    void SetFilePath(const std::string& filePath);
    const std::string& FilePath() const { return context->FilePath(); }
    void SetCompileUnitInfo(const std::string& compileUnitId, const std::string& sourceFilePath);
    void Emit();
    void CreateFunction(const std::string& name, otava::intermediate::Type* type, bool once);
    otava::intermediate::Type* MakeFunctionType(otava::intermediate::Type* returnType, const std::vector<otava::intermediate::Type*>& paramTypes);
    otava::intermediate::Type* GetVoidType();
    otava::intermediate::Type* GetBoolType();
    otava::intermediate::Type* GetSByteType();
    otava::intermediate::Type* GetByteType();
    otava::intermediate::Type* GetShortType();
    otava::intermediate::Type* GetUShortType();
    otava::intermediate::Type* GetIntType();
    otava::intermediate::Type* GetUIntType();
    otava::intermediate::Type* GetLongType();
    otava::intermediate::Type* GetULongType();
    otava::intermediate::Type* GetFloatType();
    otava::intermediate::Type* GetDoubleType();
    otava::intermediate::Type* MakePtrType(otava::intermediate::Type* baseType);
    otava::intermediate::Value* EmitBool(bool value);
    otava::intermediate::Value* EmitSByte(int8_t value);
    otava::intermediate::Value* EmitByte(uint8_t value);
    otava::intermediate::Value* EmitShort(int16_t value);
    otava::intermediate::Value* EmitUShort(uint16_t value);
    otava::intermediate::Value* EmitInt(int32_t value);
    otava::intermediate::Value* EmitUInt(uint32_t value);
    otava::intermediate::Value* EmitLong(int64_t value);
    otava::intermediate::Value* EmitULong(uint64_t value);
    otava::intermediate::Value* EmitFloat(float value);
    otava::intermediate::Value* EmitDouble(double value);
    otava::intermediate::Value* EmitNull(otava::intermediate::Type* type);
    otava::intermediate::Value* EmitNot(otava::intermediate::Value* value);
    otava::intermediate::Value* EmitNeg(otava::intermediate::Value* value);
    otava::intermediate::Value* EmitAdd(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitSub(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitMul(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitDiv(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitMod(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitAnd(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitOr(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitXor(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitShl(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitShr(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitEqual(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitLess(otava::intermediate::Value* left, otava::intermediate::Value* right);
    otava::intermediate::Value* EmitSignExtend(otava::intermediate::Value* value, otava::intermediate::Type* destType);
    otava::intermediate::Value* EmitZeroExtend(otava::intermediate::Value* value, otava::intermediate::Type* destType);
    otava::intermediate::Value* EmitTruncate(otava::intermediate::Value* value, otava::intermediate::Type* destType);
    otava::intermediate::Value* EmitBitcast(otava::intermediate::Value* value, otava::intermediate::Type* destType);
    otava::intermediate::Value* EmitIntToFloat(otava::intermediate::Value* value, otava::intermediate::Type* destType);
    otava::intermediate::Value* EmitFloatToInt(otava::intermediate::Value* value, otava::intermediate::Type* destType);
    otava::intermediate::Value* EmitIntToPtr(otava::intermediate::Value* value, otava::intermediate::Type* destType);
    otava::intermediate::Value* EmitPtrToInt(otava::intermediate::Value* value, otava::intermediate::Type* destType);
    otava::intermediate::Value* EmitParam(otava::intermediate::Type* type);
    otava::intermediate::Value* EmitLocal(otava::intermediate::Type* type);
    otava::intermediate::Value* EmitLoad(otava::intermediate::Value* value);
    void EmitStore(otava::intermediate::Value* value, otava::intermediate::Value* ptr);
    otava::intermediate::Value* EmitArg(otava::intermediate::Value* value);
    otava::intermediate::Value* EmitElemAddr(otava::intermediate::Value* ptr, otava::intermediate::Value* value);
    otava::intermediate::Value* EmitPtrOffset(otava::intermediate::Value* ptr, otava::intermediate::Value* offset);
    otava::intermediate::Value* EmitPtrDiff(otava::intermediate::Value* leftPtr, otava::intermediate::Value* rightPtr);
    otava::intermediate::Value* EmitCall(otava::intermediate::Value* function);
    otava::intermediate::Value* EmitRet(otava::intermediate::Value* value);
    void EmitJump(otava::intermediate::BasicBlock* dest);
    void EmitBranch(otava::intermediate::Value* cond, otava::intermediate::BasicBlock* trueDest, otava::intermediate::BasicBlock* falseDest);
    otava::intermediate::SwitchInstruction* EmitSwitch(otava::intermediate::Value* cond, otava::intermediate::BasicBlock* defaultDest);
    void EmitTrap(const std::vector<otava::intermediate::Value*>& args);
    void EmitNop();
    otava::intermediate::Type* GetType(const util::uuid& id);
    void SetType(const util::uuid& id, otava::intermediate::Type* type);
    IrValueStack& Stack() { return *stack; }
private:
    otava::intermediate::Context* context;
    IrValueStack* stack;
    std::map<util::uuid, otava::intermediate::Type*> typeMap;
};

} // namespace otava::symbols
