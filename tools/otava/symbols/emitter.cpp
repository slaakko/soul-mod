// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.emitter;

import otava.symbols.bound.tree;
import otava.intermediate;

namespace otava::symbols {

Emitter::Emitter() : context(new otava::intermediate::Context()), stack(new IrValueStack()), retValue(nullptr)
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

otava::intermediate::Function* Emitter::CreateFunction(const std::string& name, otava::intermediate::Type* type, bool inline_, bool once)
{
    otava::intermediate::Function* function = context->AddFunctionDefinition(soul::ast::Span(), type, name, inline_, once, nullptr);
    context->SetCurrentFunction(function);
    return function;
}

void Emitter::SetRegNumbers()
{
    context->CurrentFunction()->SetNumbers();
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
    return context->GetStructureType(soul::ast::Span(), context->NextTypeId(), fieldTypeRefs);
}

otava::intermediate::Type* Emitter::MakeFunctionType(otava::intermediate::Type* returnType, const std::vector<otava::intermediate::Type*>& paramTypes)
{
    otava::intermediate::TypeRef returnTypeRef = returnType->GetTypeRef();
    std::vector<otava::intermediate::TypeRef> paramTypeRefs;
    for (const auto& paramType : paramTypes)
    {
        paramTypeRefs.push_back(paramType->GetTypeRef());
    }
    return context->GetFunctionType(soul::ast::Span(), context->NextTypeId(), returnTypeRef, paramTypeRefs);
}

otava::intermediate::Type* Emitter::MakeArrayType(std::int64_t size, otava::intermediate::Type* elementType)
{
    otava::intermediate::TypeRef elementTypeRef = elementType->GetTypeRef();
    return context->GetArrayType(soul::ast::Span(), context->NextTypeId(), size, elementTypeRef);
}

otava::intermediate::Type* Emitter::MakeFwdDeclaredStructureType(const util::uuid& id)
{
    return context->MakeFwdDeclaredStructureType(id, context->NextTypeId());
}

otava::intermediate::Type* Emitter::GetOrInsertFwdDeclaredStructureType(const util::uuid& id)
{
    otava::intermediate::Type* type = context->GetFwdDeclaredStructureType(id);
    if (type)
    {
        return type;
    }
    else
    {
        return MakeFwdDeclaredStructureType(id);
    }
}

void Emitter::ResolveForwardReferences(const util::uuid& id, otava::intermediate::StructureType* structureType)
{
    context->ResolveForwardReferences(id, structureType);
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

otava::intermediate::Value* Emitter::EmitSByte(std::int8_t value)
{
    return context->GetSByteValue(value);
}

otava::intermediate::Value* Emitter::EmitByte(std::uint8_t value)
{
    return context->GetByteValue(value);
}

otava::intermediate::Value* Emitter::EmitShort(std::int16_t value)
{
    return context->GetShortValue(value);
}

otava::intermediate::Value* Emitter::EmitUShort(std::uint16_t value)
{
    return context->GetUShortValue(value);
}

otava::intermediate::Value* Emitter::EmitInt(std::int32_t value)
{
    return context->GetIntValue(value);
}

otava::intermediate::Value* Emitter::EmitUInt(std::uint32_t value)
{
    return context->GetUIntValue(value);
}

otava::intermediate::Value* Emitter::EmitLong(std::int64_t value)
{
    return context->GetLongValue(value);
}

otava::intermediate::Value* Emitter::EmitULong(std::uint64_t value)
{
    return context->GetULongValue(value);
}

otava::intermediate::Value* Emitter::EmitIntegerValue(otava::intermediate::Type* type, std::int64_t value)
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
    return context->GetNullValue(soul::ast::Span(), type);
}

otava::intermediate::Value* Emitter::EmitArrayValue(const std::vector<otava::intermediate::Value*>& elements, otava::intermediate::ArrayType* arrayType)
{
    return context->MakeArrayValue(soul::ast::Span(), elements, arrayType);
}

otava::intermediate::Value* Emitter::EmitStructureValue(const std::vector<otava::intermediate::Value*>& fieldValues, otava::intermediate::StructureType* structureType)
{
    return context->MakeStructureValue(soul::ast::Span(), fieldValues, structureType);
}

otava::intermediate::Value* Emitter::EmitStringValue(const std::string& value)
{
    otava::intermediate::Value* stringValue = context->MakeStringValue(soul::ast::Span(), value, false);
    otava::intermediate::GlobalVariable* globalVar = context->GetGlobalVariableForString(stringValue);
    return globalVar;
}

otava::intermediate::Value* Emitter::EmitConversionValue(otava::intermediate::Type* type, otava::intermediate::Value* from)
{
    return context->MakeConversionValue(soul::ast::Span(), type, from);
}

otava::intermediate::Value* Emitter::EmitGlobalVariable(otava::intermediate::Type* type, const std::string& variableName, otava::intermediate::Value* initializer)
{
    return context->AddGlobalVariable(soul::ast::Span(), context->MakePtrType(type), variableName, initializer);
}

otava::intermediate::Value* Emitter::EmitSymbolValue(otava::intermediate::Type* type, const std::string& symbol)
{
    return context->MakeSymbolValue(soul::ast::Span(), type, symbol);
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

otava::intermediate::Value* Emitter::EmitFPExtend(otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return context->CreateFloatingPointExtend(value, destType);
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

otava::intermediate::Value* Emitter::EmitLocalInEntryBlock(otava::intermediate::Type* type)
{
    return context->CreateLocalInEntryBlock(type);
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
    std::int32_t n = args.size();
    for (std::int32_t i = 0; i < n; ++i)
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

otava::intermediate::Value* Emitter::GetVTabVariable(void* cls) const
{
    auto it = vtabVariableMap.find(cls);
    if (it != vtabVariableMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

void Emitter::SetVTabVariable(void* cls, otava::intermediate::Value* vtabVariable)
{
    vtabVariableMap[cls] = vtabVariable;
}

} // namespace otava::symbols
