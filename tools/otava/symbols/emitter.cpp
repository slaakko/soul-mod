// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module otava.symbols.emitter;

import otava.intermediate.register_allocator;
import otava.intermediate.metadata;
import otava.intermediate.code;
import otava.intermediate.compile.unit;
import otava.intermediate.instruction;
import otava.intermediate.function;
import otava.intermediate.type;
import otava.intermediate.reference_resolver;

namespace otava::symbols {

Emitter::Emitter() : context(new otava::intermediate::Context()), stack(new IrValueStack())
{
}

Emitter::~Emitter()
{
    delete context;
    delete stack;
}

void Emitter::SetFilePath(const std::string& filePath)
{
    context->SetFilePath(filePath);
}

const std::string& Emitter::FilePath() const
{
    return context->FilePath();
}

void Emitter::Emit()
{
    context->WriteFile();
}

void Emitter::SetCompileUnitInfo(const std::string& compileUnitId, const std::string& sourceFilePath)
{
    context->SetCompileUnitInfo(compileUnitId, sourceFilePath);
}

otava::intermediate::Context* Emitter::GetIntermediateContext()
{
    return context;
}

void Emitter::ResolveReferences()
{
    otava::intermediate::ResolveReferences(*context);
}

void Emitter::CreateFunction(const std::string& name, otava::intermediate::Type* type, bool once)
{
    otava::intermediate::Function* function = context->AddFunctionDefinition(soul::ast::SourcePos(), type, name, once, nullptr);
    context->SetCurrentFunction(function);
}

otava::intermediate::Function* Emitter::GetOrInsertFunction(const std::string& name, otava::intermediate::FunctionType* functionType)
{
    return context->GetOrInsertFunction(name, functionType);
}

otava::intermediate::BasicBlock* Emitter::CreateBasicBlock()
{
    return context->CurrentFunction()->CreateBasicBlock();
}

void Emitter::SetCurrentBasicBlock(otava::intermediate::BasicBlock* bb)
{
    context->SetCurrentBasicBlock(bb);
}

otava::intermediate::Type* Emitter::MakeStructureType(const std::vector<otava::intermediate::Type*>& elementTypes)
{
    std::vector< otava::intermediate::TypeRef> fieldTypeRefs;
    for (const auto& elementType : elementTypes)
    {
        fieldTypeRefs.push_back(elementType->GetTypeRef());
    }
    return context->GetStructureType(soul::ast::SourcePos(), context->NextTypeId(), fieldTypeRefs);
}

otava::intermediate::Type* Emitter::MakeFunctionType(otava::intermediate::Type* returnType, const std::vector<otava::intermediate::Type*>& paramTypes)
{
    otava::intermediate::TypeRef returnTypeRef = returnType->GetTypeRef();
    std::vector<otava::intermediate::TypeRef> paramTypeRefs;
    for (const auto& paramType : paramTypes)
    {
        paramTypeRefs.push_back(paramType->GetTypeRef());
    }
    return context->GetFunctionType(soul::ast::SourcePos(), context->NextTypeId(), returnTypeRef, paramTypeRefs);
}

otava::intermediate::Type* Emitter::MakeArrayType(int64_t size, otava::intermediate::Type* elementType)
{
    otava::intermediate::TypeRef elementTypeRef = elementType->GetTypeRef();
    return context->GetArrayType(soul::ast::SourcePos(), context->NextTypeId(), size, elementTypeRef);
}

otava::intermediate::Type* Emitter::GetVoidType()
{
    return context->GetVoidType();
}

otava::intermediate::Type* Emitter::GetBoolType()
{
    return context->GetBoolType();
}

otava::intermediate::Type* Emitter::GetSByteType()
{
    return context->GetSByteType();
}

otava::intermediate::Type* Emitter::GetByteType()
{
    return context->GetByteType();
}

otava::intermediate::Type* Emitter::GetShortType()
{
    return context->GetShortType();
}

otava::intermediate::Type* Emitter::GetUShortType()
{
    return context->GetUShortType();
}

otava::intermediate::Type* Emitter::GetIntType()
{
    return context->GetIntType();
}

otava::intermediate::Type* Emitter::GetUIntType()
{
    return context->GetUIntType();
}

otava::intermediate::Type* Emitter::GetLongType()
{
    return context->GetLongType();
}

otava::intermediate::Type* Emitter::GetULongType()
{
    return context->GetULongType();
}

otava::intermediate::Type* Emitter::GetFloatType()
{
    return context->GetFloatType();
}

otava::intermediate::Type* Emitter::GetDoubleType()
{
    return context->GetDoubleType();
}

otava::intermediate::Type* Emitter::MakePtrType(otava::intermediate::Type* baseType)
{
    return context->MakePtrType(baseType);
}

otava::intermediate::Value* Emitter::EmitBool(bool value)
{
    if (value)
    {
        return context->GetTrueValue();
    }
    else
    {
        return context->GetFalseValue();
    }
}

otava::intermediate::Value* Emitter::EmitSByte(int8_t value)
{
    return context->GetSByteValue(value);
}

otava::intermediate::Value* Emitter::EmitByte(uint8_t value)
{
    return context->GetByteValue(value);
}

otava::intermediate::Value* Emitter::EmitShort(int16_t value)
{
    return context->GetShortValue(value);
}

otava::intermediate::Value* Emitter::EmitUShort(uint16_t value)
{
    return context->GetUShortValue(value);
}

otava::intermediate::Value* Emitter::EmitInt(int32_t value)
{
    return context->GetIntValue(value);
}

otava::intermediate::Value* Emitter::EmitUInt(uint32_t value)
{
    return context->GetUIntValue(value);
}

otava::intermediate::Value* Emitter::EmitLong(int64_t value)
{
    return context->GetLongValue(value);
}

otava::intermediate::Value* Emitter::EmitULong(uint64_t value)
{
    return context->GetULongValue(value);
}

otava::intermediate::Value* Emitter::EmitIntegerValue(otava::intermediate::Type* type, int64_t value)
{
    return context->GetIntegerValue(type, value);
}

otava::intermediate::Value* Emitter::EmitFloat(float value)
{
    return context->GetFloatValue(value);
}

otava::intermediate::Value* Emitter::EmitDouble(double value)
{
    return context->GetDoubleValue(value);
}

otava::intermediate::Value* Emitter::EmitFloatingValue(otava::intermediate::Type* type, double value)
{
    return context->GetFloatingValue(type, value);
}

otava::intermediate::Value* Emitter::EmitNull(otava::intermediate::Type* type)
{
    return context->GetNullValue(otava::intermediate::SourcePos(), type);
}

otava::intermediate::Value* Emitter::EmitArrayValue(const std::vector<otava::intermediate::Value*>& elements)
{
    return context->MakeArrayValue(otava::intermediate::SourcePos(), elements);
}

otava::intermediate::Value* Emitter::EmitStructureValue(const std::vector<otava::intermediate::Value*>& fieldValues)
{
    return context->MakeStructureValue(otava::intermediate::SourcePos(), fieldValues);
}

otava::intermediate::Value* Emitter::EmitStringValue(const std::string& value)
{
    return context->MakeStringValue(otava::intermediate::SourcePos(), value);
}

otava::intermediate::Value* Emitter::EmitConversionValue(otava::intermediate::Type* type, otava::intermediate::Value* from)
{
    return context->MakeConversionValue(otava::intermediate::SourcePos(), type, from);
}

void Emitter::EmitGlobalVariable(otava::intermediate::Type* type, const std::string& variableName, otava::intermediate::Value* initializer)
{
    context->AddGlobalVariable(otava::intermediate::SourcePos(), type, variableName, initializer, false);
}

otava::intermediate::Value* Emitter::EmitNot(otava::intermediate::Value* value)
{
    return context->CreateNot(value);
}

otava::intermediate::Value* Emitter::EmitNeg(otava::intermediate::Value* value)
{
    return context->CreateNeg(value);
}

otava::intermediate::Value* Emitter::EmitAdd(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateAdd(left, right);
}

otava::intermediate::Value* Emitter::EmitSub(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateSub(left, right);
}

otava::intermediate::Value* Emitter::EmitMul(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateMul(left, right);
}

otava::intermediate::Value* Emitter::EmitDiv(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateDiv(left, right);
}

otava::intermediate::Value* Emitter::EmitMod(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateMod(left, right);
}

otava::intermediate::Value* Emitter::EmitAnd(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateAnd(left, right);
}

otava::intermediate::Value* Emitter::EmitOr(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateOr(left, right);
}

otava::intermediate::Value* Emitter::EmitXor(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateXor(left, right);
}

otava::intermediate::Value* Emitter::EmitShl(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateShl(left, right);
}

otava::intermediate::Value* Emitter::EmitShr(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateShr(left, right);
}

otava::intermediate::Value* Emitter::EmitEqual(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateEqual(left, right);
}

otava::intermediate::Value* Emitter::EmitLess(otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return context->CreateLess(left, right);
}

otava::intermediate::Value* Emitter::EmitSignExtend(otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return context->CreateSignExtend(value, destType);
}

otava::intermediate::Value* Emitter::EmitZeroExtend(otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return context->CreateZeroExtend(value, destType);
}

otava::intermediate::Value* Emitter::EmitTruncate(otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return context->CreateTruncate(value, destType);
}

otava::intermediate::Value* Emitter::EmitBitcast(otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return context->CreateBitcast(value, destType);
}

otava::intermediate::Value* Emitter::EmitIntToFloat(otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return context->CreateIntToFloat(value, destType);
}

otava::intermediate::Value* Emitter::EmitFloatToInt(otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return context->CreateFloatToInt(value, destType);
}

otava::intermediate::Value* Emitter::EmitIntToPtr(otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return context->CreateIntToPtr(value, destType);
}

otava::intermediate::Value* Emitter::EmitPtrToInt(otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return context->CreatePtrToInt(value, destType);
}

otava::intermediate::Value* Emitter::EmitParam(otava::intermediate::Type* type)
{
    return context->CreateParam(type);
}

otava::intermediate::Value* Emitter::EmitLocal(otava::intermediate::Type* type)
{
    return context->CreateLocal(type);
}

otava::intermediate::Value* Emitter::EmitLoad(otava::intermediate::Value* value)
{
    return context->CreateLoad(value);
}

void Emitter::EmitStore(otava::intermediate::Value* value, otava::intermediate::Value* ptr)
{
    context->CreateStore(value, ptr);
}

otava::intermediate::Value* Emitter::EmitArg(otava::intermediate::Value* value)
{
    return context->CreateArg(value);
}

otava::intermediate::Value* Emitter::EmitElemAddr(otava::intermediate::Value* ptr, otava::intermediate::Value* index)
{
    return context->CreateElemAddr(ptr, index);
}

otava::intermediate::Value* Emitter::EmitPtrOffset(otava::intermediate::Value* ptr, otava::intermediate::Value* offset)
{
    return context->CreatePtrOffset(ptr, offset);
}

otava::intermediate::Value* Emitter::EmitPtrDiff(otava::intermediate::Value* leftPtr, otava::intermediate::Value* rightPtr)
{
    return context->CreatePtrDiff(leftPtr, rightPtr);
}

otava::intermediate::Value* Emitter::EmitCall(otava::intermediate::Value* function, const std::vector<otava::intermediate::Value*>& args)
{
    int32_t n = args.size();
    for (int32_t i = 0; i < n; ++i)
    {
        otava::intermediate::Value* arg = args[i];
        context->CreateArg(arg);
    }
    return context->CreateCall(function);
}

otava::intermediate::Value* Emitter::EmitRet(otava::intermediate::Value* value)
{
    return context->CreateRet(value);
}

otava::intermediate::Value* Emitter::EmitRetVoid()
{
    return context->CreateRet(nullptr);
}

otava::intermediate::Value* Emitter::GetParam(int index) const
{
    return context->CurrentFunction()->GetParam(index);
}

void Emitter::EmitJump(otava::intermediate::BasicBlock* dest)
{
    context->CreateJump(dest);
}

void Emitter::EmitBranch(otava::intermediate::Value* cond, otava::intermediate::BasicBlock* trueDest, otava::intermediate::BasicBlock* falseDest)
{
    context->CreateBranch(cond, trueDest, falseDest);
}

otava::intermediate::SwitchInstruction* Emitter::EmitSwitch(otava::intermediate::Value* cond, otava::intermediate::BasicBlock* defaultDest)
{
    return context->CreateSwitch(cond, defaultDest);
}

void Emitter::EmitTrap(const std::vector<otava::intermediate::Value*>& args)
{
    context->CreateTrap(args);
}

void Emitter::EmitNop()
{
    context->CreateNop();
}

otava::intermediate::Type* Emitter::GetType(const util::uuid& id) const
{
    auto it = typeMap.find(id);
    if (it != typeMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void Emitter::SetType(const util::uuid& id, otava::intermediate::Type* type)
{
    typeMap[id] = type;
}

otava::intermediate::Value* Emitter::GetIrObject(void* symbol) const
{
    auto it = irObjectMap.find(symbol);
    if (it != irObjectMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void Emitter::SetIrObject(void* symbol, otava::intermediate::Value* irObject)
{
    irObjectMap[symbol] = irObject;
}

} // namespace otava::symbols
