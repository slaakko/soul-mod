// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.context;

import otava.intermediate.compile_unit;
import otava.intermediate.error;
import otava.intermediate.lexer;
import util;

namespace otava::intermediate {

Context::Context() : 
    compileUnit(), inlineDepth(4), maxArithmeticOptimizationCount(8), flags(ContextFlags::none), functionsInlined(0), totalFunctions(0), currentBasicBlock(nullptr),
    currentLineNumber(0)
{
    compileUnit.SetContext(this);
    types.SetContext(this);
    types.Init();
    data.SetContext(this);
    code.SetContext(this);
    metadata.SetContext(this);
}

void Context::SetFilePath(const std::string& filePath_)
{
    compileUnit.SetFilePath(filePath_);
}

const std::string& Context::FilePath() const
{
    return compileUnit.FilePath();
}

std::string Context::ErrorLines(const soul::ast::LineColLen& lineColLen)
{
    if (lineColLen.IsValid())
    {
        std::string errorLines = util::ToUtf8(fileMap.GetFileLine(fileId, lineColLen.line));
        errorLines.append("\n").append(lineColLen.col - 1, ' ').append(lineColLen.len, '^').append("\n");
        return errorLines;
    }
    else
    {
        return std::string();
    }
}

void Context::SetCompileUnitInfo(const std::string& compileUnitId, MetadataRef* mdRef)
{
    compileUnit.SetInfo(compileUnitId, mdRef);
}

void Context::SetCompileUnitInfo(const std::string& compileUnitId_, const std::string& sourceFilePath)
{
    MetadataStruct* sourceFileStruct = metadata.CreateMetadataStruct();
    sourceFileStruct->AddItem("nodeType", metadata.CreateMetadataLong(fileInfoNodeType));
    sourceFileStruct->AddItem("sourceFileName", metadata.CreateMetadataString(sourceFilePath, false));
    MetadataRef* sourceFileNameRef = metadata.CreateMetadataRef(soul::ast::Span(), sourceFileStruct->Id());
    compileUnit.SetInfo(compileUnitId_, sourceFileNameRef);
}

void Context::AddStructureType(const soul::ast::Span& span, std::int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs)
{
    types.AddStructureType(span, typeId, fieldTypeRefs);
}

void Context::AddArrayType(const soul::ast::Span& span, std::int32_t typeId, std::int64_t size, const TypeRef& elementTypeRef)
{
    types.AddArrayType(span, typeId, size, elementTypeRef);
}

void Context::AddFunctionType(const soul::ast::Span& span, std::int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs)
{
    types.AddFunctionType(span, typeId, returnTypeRef, paramTypeRefs);
}

GlobalVariable* Context::AddGlobalVariable(const soul::ast::Span& span, Type* type, const std::string& variableName, Value* initializer)
{
    return data.AddGlobalVariable(span, type, variableName, initializer, this);
}

GlobalVariable* Context::GetGlobalVariableForString(otava::intermediate::Value* stringValue)
{
    return data.GetGlobalVariableForString(stringValue);
}

void Context::ResolveTypes()
{
    types.Resolve(this);
}

void Context::ResolveType(TypeRef& typeRef)
{
    types.ResolveType(typeRef, this);
}

Value* Context::GetBoolValue(bool value)
{
    if (value) return GetTrueValue(); else return GetFalseValue();
}

Value* Context::GetTrueValue()
{
    return data.GetTrueValue(types);
}

Value* Context::GetFalseValue()
{
    return data.GetFalseValue(types);
}

Value* Context::GetBooleanLiteral(const soul::ast::Span& span, Type* type, bool value)
{
    if (type->IsBooleanType())
    {
        if (value)
        {
            return GetTrueValue();
        }
        else
        {
            return GetFalseValue();
        }
    }
    else
    {
        Error("error making literal value: Boolean type expected", span, this);
    }
    return nullptr;
}

Value* Context::GetSByteValue(std::int8_t value)
{
    return data.GetSByteValue(value, types);
}

Value* Context::GetByteValue(std::uint8_t value)
{
    return data.GetByteValue(value, types);
}

Value* Context::GetShortValue(std::int16_t value)
{
    return data.GetShortValue(value, types);
}

Value* Context::GetUShortValue(std::uint16_t value)
{
    return data.GetUShortValue(value, types);
}

Value* Context::GetIntValue(std::int32_t value)
{
    return data.GetIntValue(value, types);
}

Value* Context::GetUIntValue(std::uint32_t value)
{
    return data.GetUIntValue(value, types);
}

Value* Context::GetLongValue(std::int64_t value)
{
    return data.GetLongValue(value, types);
}

Value* Context::GetULongValue(std::uint64_t value)
{
    return data.GetULongValue(value, types);
}

Value* Context::GetIntegerValue(Type* type, std::int64_t value)
{
    return data.GetIntegerValue(type, value, types);
}

Value* Context::GetFloatValue(float value)
{
    return data.GetFloatValue(value, types);
}

Value* Context::GetDoubleValue(double value)
{
    return data.GetDoubleValue(value, types);
}

Value* Context::GetFloatingValue(Type* type, double value)
{
    return data.GetFloatingValue(type, value, types);
}

Value* Context::GetNullValue(const soul::ast::Span& span, Type* type)
{
    if (type->IsPointerType())
    {
        return data.GetNullValue(type);
    }
    else
    {
        Error("error making null literal value: pointer type expected", span, this);
    }
    return nullptr;
}

Value* Context::MakeArrayValue(const soul::ast::Span& span, const std::vector<Value*>& elements, ArrayType* arrayType)
{
    return data.MakeArrayValue(span, elements, arrayType);
}

Value* Context::MakeStructureValue(const soul::ast::Span& span, const std::vector<Value*>& fieldValues, StructureType* structureType)
{
    return data.MakeStructureValue(span, fieldValues, structureType);
}

Value* Context::MakeStringValue(const soul::ast::Span& span, const std::string& value, bool crop)
{
    return data.MakeStringValue(span, value, crop);
}

Value* Context::MakeStringArrayValue(const soul::ast::Span& span, char prefix, const std::vector<Value*>& elements)
{
    return data.MakeStringArrayValue(span, prefix, elements);
}

Value* Context::MakeConversionValue(const soul::ast::Span& span, Type* type, Value* from)
{
    return data.MakeConversionValue(span, type, from);
}

Value* Context::MakeClsIdValue(const soul::ast::Span& span, Type* type, const std::string& clsIdStr)
{
    return data.MakeClsIdValue(span, type, clsIdStr);
}

Value* Context::MakeSymbolValue(const soul::ast::Span& span, Type* type, const std::string& symbol)
{
    return data.MakeSymbolValue(span, type, symbol);
}

Value* Context::MakeIntegerLiteral(const soul::ast::Span& span, Type* type, const std::string& strValue)
{
    return data.MakeIntegerLiteral(span, type, strValue, types, this);
}

Value* Context::MakeAddressLiteral(const soul::ast::Span& span, Type* type, const std::string& id, bool resolve)
{
    return data.MakeAddressLiteral(span, type, id, this, resolve);
}

Type* Context::GetVoidType()
{
    return types.GetVoidType();
}

Type* Context::GetBoolType()
{
    return types.GetBoolType();
}

Type* Context::GetSByteType()
{
    return types.GetSByteType();
}

Type* Context::GetByteType()
{
    return types.GetByteType();
}

Type* Context::GetShortType()
{
    return types.GetShortType();
}

Type* Context::GetUShortType()
{
    return types.GetUShortType();
}

Type* Context::GetIntType()
{
    return types.GetIntType();
}

Type* Context::GetUIntType()
{
    return types.GetUIntType();
}

Type* Context::GetLongType()
{
    return types.GetLongType();
}

Type* Context::GetULongType()
{
    return types.GetULongType();
}

Type* Context::GetFloatType()
{
    return types.GetFloatType();
}

Type* Context::GetDoubleType()
{
    return types.GetDoubleType();
}

Type* Context::MakePtrType(Type* baseType)
{
    return baseType->AddPointer(this);
}

StructureType* Context::GetStructureType(const soul::ast::Span& span, std::int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs)
{
    return types.GetStructureType(span, typeId, fieldTypeRefs);
}

FwdDeclaredStructureType* Context::GetFwdDeclaredStructureType(const util::uuid& id)
{
    return types.GetFwdDeclaredStructureType(id);
}

FwdDeclaredStructureType* Context::MakeFwdDeclaredStructureType(const util::uuid& id, std::int32_t typeId)
{
    return types.MakeFwdDeclaredStructureType(id, typeId);
}

void Context::AddFwdDependentType(FwdDeclaredStructureType* fwdType, Type* type)
{
    types.AddFwdDependentType(fwdType, type);
}

void Context::ResolveForwardReferences(const util::uuid& id, StructureType* structureType)
{
    types.ResolveForwardReferences(id, structureType);
}

ArrayType* Context::GetArrayType(const soul::ast::Span& span, std::int32_t typeId, std::int64_t size, const TypeRef& elementTypeRef)
{
    return types.GetArrayType(span, typeId, size, elementTypeRef);
}

FunctionType* Context::GetFunctionType(const soul::ast::Span& span, std::int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs)
{
    return types.GetFunctionType(span, typeId, returnTypeRef, paramTypeRefs);
}

Function* Context::CurrentFunction() const
{
    return code.CurrentFunction();
}

std::int32_t Context::NextTypeId()
{
    return types.NextTypeId();
}

std::string Context::GetNextStringValueId()
{
    return data.GetNextStringValueId();
}

void Context::ResolveData()
{
    data.ResolveAddressValues();
}

void Context::SetCurrentFunction(Function* function)
{
    code.SetCurrentFunction(function);
}

Function* Context::GetOrInsertFunction(const std::string& functionId, FunctionType* functionType)
{
    return code.GetOrInsertFunction(functionId, functionType);
}

Function* Context::AddFunctionDefinition(const soul::ast::Span& span, Type* type, const std::string& functionId, bool inline_, bool linkOnce,
    otava::intermediate::MetadataRef* metadataRef)
{
    if (type->IsPointerType())
    {
        type = type->RemovePointer(span, this);
    }
    if (type->IsFunctionType())
    {
        FunctionType* functionType = static_cast<FunctionType*>(type);
        return code.AddFunctionDefinition(span, functionType, functionId, inline_, linkOnce, metadataRef);
    }
    else
    {
        Error("error adding function '" + functionId + "' definition: invalid type '" + type->Name() + "': function type expected", span, this);
    }
    return nullptr;
}

Function* Context::AddFunctionDeclaration(const soul::ast::Span& span, Type* type, const std::string& functionId)
{
    if (type->IsPointerType())
    {
        type = type->RemovePointer(span, this);
    }
    if (type->IsFunctionType())
    {
        FunctionType* functionType = static_cast<FunctionType*>(type);
        return code.AddFunctionDeclaration(span, functionType, functionId);
    }
    else
    {
        Error("error adding function '" + functionId + "' declaration: invalid type '" + type->Name() + "': function type expected", span, this);
    }
    return nullptr;
}

MetadataStruct* Context::AddMetadataStruct(const soul::ast::Span& span, std::int32_t id)
{
    return metadata.AddMetadataStruct(span, id);
}

MetadataBool* Context::CreateMetadataBool(bool value)
{
    return metadata.CreateMetadataBool(value);
}

MetadataLong* Context::CreateMetadataLong(std::int64_t value)
{
    return metadata.CreateMetadataLong(value);
}

MetadataString* Context::CreateMetadataString(const std::string& value, bool crop)
{
    return metadata.CreateMetadataString(value, crop);
}

MetadataRef* Context::CreateMetadataRef(const soul::ast::Span& span, std::int32_t nodeId)
{
    return metadata.CreateMetadataRef(span, nodeId);
}

MetadataStruct* Context::CreateMetadataStruct()
{
    return metadata.CreateMetadataStruct();
}

void Context::ResolveMetadataReferences()
{
    metadata.ResolveMetadataReferences();
}

void Context::SetCurrentBasicBlock(BasicBlock* bb)
{
    currentBasicBlock = bb;
}

BasicBlock* Context::CreateBasicBlock()
{
    return CurrentFunction()->CreateBasicBlock();
}

void Context::SetCurrentLineNumber(int lineNumber)
{
    if (lineNumber != -1)
    {
        currentLineNumber = lineNumber;
    }
}

Instruction* Context::CreateNot(Value* arg)
{
    Instruction* inst = new NotInstruction(soul::ast::Span(), MakeRegValue(arg->GetType()), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateNeg(Value* arg)
{
    Instruction* inst = new NegInstruction(soul::ast::Span(), MakeRegValue(arg->GetType()), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateAdd(Value* left, Value* right)
{
    Instruction* inst = new AddInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateSub(Value* left, Value* right)
{
    Instruction* inst = new SubInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateMul(Value* left, Value* right)
{
    Instruction* inst = new MulInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateDiv(Value* left, Value* right)
{
    Instruction* inst = new DivInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateMod(Value* left, Value* right)
{
    Instruction* inst = new ModInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateAnd(Value* left, Value* right)
{
    Instruction* inst = new AndInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateOr(Value* left, Value* right)
{
    Instruction* inst = new OrInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateXor(Value* left, Value* right)
{
    Instruction* inst = new XorInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateShl(Value* left, Value* right)
{
    Instruction* inst = new ShlInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateShr(Value* left, Value* right)
{
    Instruction* inst = new ShrInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateEqual(Value* left, Value* right)
{
    Instruction* inst = new EqualInstruction(soul::ast::Span(), MakeRegValue(GetBoolType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateLess(Value* left, Value* right)
{
    Instruction* inst = new LessInstruction(soul::ast::Span(), MakeRegValue(GetBoolType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateSignExtend(Value* arg, Type* destType)
{
    Instruction* inst = new SignExtendInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateZeroExtend(Value* arg, Type* destType)
{
    Instruction* inst = new ZeroExtendInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateFloatingPointExtend(Value* arg, Type* destType)
{
    Instruction* inst = new FloatingPointExtendInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateTruncate(Value* arg, Type* destType)
{
    Instruction* inst = new TruncateInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateBitcast(Value* arg, Type* destType)
{
    Instruction* inst = new BitcastInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateIntToFloat(Value* arg, Type* destType)
{
    Instruction* inst = new IntToFloatInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateFloatToInt(Value* arg, Type* destType)
{
    Instruction* inst = new FloatToIntInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateIntToPtr(Value* arg, Type* destType)
{
    Instruction* inst = new IntToPtrInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreatePtrToInt(Value* arg, Type* destType)
{
    Instruction* inst = new PtrToIntInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateParam(Type* type)
{
    Instruction* inst = new ParamInstruction(soul::ast::Span(), MakeRegValue(type));
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateLocal(Type* type)
{
    Type* ptrType = MakePtrType(type);
    Instruction* inst = new LocalInstruction(soul::ast::Span(), MakeRegValue(ptrType), type);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateLocalInEntryBlock(Type* type)
{
    Type* ptrType = MakePtrType(type);
    Instruction* inst = new LocalInstruction(soul::ast::Span(), MakeRegValue(ptrType), type);
    AddLineInfo(inst);
    BasicBlock* entryBlock = code.CurrentFunction()->GetBasicBlock(0);
    entryBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateLoad(Value* ptr)
{
    Instruction* inst = new LoadInstruction(soul::ast::Span(), MakeRegValue(ptr->GetType()->RemovePointer(soul::ast::Span(), this)), ptr);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateStore(Value* value, Value* ptr)
{
    Instruction* inst = new StoreInstruction(soul::ast::Span(), value, ptr);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateArg(Value* arg)
{
    Instruction* inst = new ArgInstruction(soul::ast::Span(), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateElemAddr(Value* ptr, Value* index)
{
    Instruction* inst = new ElemAddrInstruction(soul::ast::Span(), MakeRegValue(GetElemType(ptr, index, soul::ast::Span(), this)), ptr, index);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreatePtrOffset(Value* ptr, Value* offset)
{
    Instruction* inst = new PtrOffsetInstruction(soul::ast::Span(), MakeRegValue(ptr->GetType()), ptr, offset);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreatePtrDiff(Value* leftPtr, Value* rightPtr)
{
    Instruction* inst = new PtrDiffInstruction(soul::ast::Span(), MakeRegValue(GetLongType()), leftPtr, rightPtr);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateCall(Value* callee)
{
    Type* type = callee->GetType();
    if (type->IsFunctionPtrType())
    {
        PointerType* ptrType = static_cast<PointerType*>(type);
        type = ptrType->BaseType();
    }
    if (type->IsFunctionType())
    {
        FunctionType* functionType = static_cast<FunctionType*>(type);
        Type* returnType = functionType->ReturnType();
        if (returnType->IsVoidType())
        {
            Instruction* inst = new ProcedureCallInstruction(soul::ast::Span(), callee);
            AddLineInfo(inst);
            currentBasicBlock->AddInstruction(inst);
            return inst;
        }
        else
        {
            Instruction* inst = new FunctionCallInstruction(soul::ast::Span(), MakeRegValue(returnType), callee);
            AddLineInfo(inst);
            currentBasicBlock->AddInstruction(inst);
            return inst;
        }
    }
    else
    {

        throw std::runtime_error("invalid call");
    }
}

Instruction* Context::CreateRet(Value* value)
{
    Instruction* inst = new RetInstruction(soul::ast::Span(), value);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateJump(BasicBlock* dest)
{
    Instruction* inst = new JmpInstruction(soul::ast::Span(), dest->Id());
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateBranch(Value* cond, BasicBlock* trueDest, BasicBlock* falseDest)
{
    Instruction* inst = new BranchInstruction(soul::ast::Span(), cond, trueDest->Id(), falseDest->Id());
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

SwitchInstruction* Context::CreateSwitch(Value* cond, BasicBlock* defaultDest)
{
    SwitchInstruction* inst = new SwitchInstruction(soul::ast::Span(), cond, defaultDest->Id());
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateNop()
{
    Instruction* inst = new NoOperationInstruction(soul::ast::Span());
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

void Context::AddLineInfo(Instruction* inst)
{
    if (currentLineNumber != 0 && !inst->IsNopInstruction())
    {
        MetadataRef* lineNumberInfo = nullptr;
        auto it = lineNumberInfoMap.find(currentLineNumber);
        if (it != lineNumberInfoMap.cend())
        {
            lineNumberInfo = it->second;
        }
        else
        {
            MetadataStruct* lineNumberStruct = CreateMetadataStruct();
            lineNumberStruct->AddItem("nodeType", CreateMetadataLong(lineInfoNodeType));
            lineNumberStruct->AddItem("line", CreateMetadataLong(currentLineNumber));
            lineNumberInfo = CreateMetadataRef(soul::ast::Span(), lineNumberStruct->Id());
            lineNumberInfoMap[currentLineNumber] = lineNumberInfo;
        }
        inst->SetMetadataRef(lineNumberInfo);
    }
}

RegValue* Context::MakeRegValue(Type* type)
{
    Function* currentFunction = CurrentFunction();
    RegValue* regValue = currentFunction->MakeRegValue(soul::ast::Span(), type, currentFunction->NextRegNumber(), this);
    return regValue;
}

void Context::WriteFile()
{
    compileUnit.Write();
}

} // otava::intermediate
