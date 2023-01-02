// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.context;

import otava.intermediate.basic.block;
import otava.intermediate.compile.unit;
import otava.intermediate.code;
import otava.intermediate.data;
import otava.intermediate.error;
import otava.intermediate.function;
import otava.intermediate.type;
import otava.intermediate.instruction;
import otava.intermediate.metadata;
import otava.intermediate.register_allocator;
import util;

namespace otava::intermediate {

Context::Context() : 
    compileUnit(new CompileUnit()), types(new Types()), data(new Data()), code(new Code()), metadata(new Metadata()), currentBasicBlock(nullptr), currentLineNumber(0)
{
    compileUnit->SetContext(this);
    types->SetContext(this);
    types->Init();
    data->SetContext(this);
    code->SetContext(this);
    metadata->SetContext(this);
}

void Context::WriteFile()
{
    compileUnit->Write();
}

void Context::SetFilePath(const std::string& filePath_)
{
    compileUnit->SetFilePath(filePath_);
}

const std::string& Context::FilePath() const
{
    return compileUnit->FilePath();
}

std::string Context::ErrorLines(const SourcePos& sourcePos)
{
    if (fileMap.HasFileContent(sourcePos.file))
    {
        std::string lines = util::ToUtf8(fileMap.GetFileLine(sourcePos.file, sourcePos.line)).append("\n").append(sourcePos.col - 1, ' ').append(1, '^');
        return lines;
    }
    return std::string();
}

void Context::SetCompileUnitInfo(const std::string& compileUnitId, MetadataRef* mdRef)
{
    compileUnit->SetInfo(compileUnitId, mdRef);
}

void Context::SetCompileUnitInfo(const std::string& compileUnitId_, const std::string& sourceFilePath)
{
    MetadataStruct* sourceFileStruct = metadata->CreateMetadataStruct(this);
    sourceFileStruct->AddItem("nodeType", metadata->CreateMetadataLong(fileInfoNodeType));
    sourceFileStruct->AddItem("sourceFileName", metadata->CreateMetadataString(sourceFilePath));
    MetadataRef* sourceFileNameRef = metadata->CreateMetadataRef(SourcePos(), sourceFileStruct->Id());
    compileUnit->SetInfo(compileUnitId_, sourceFileNameRef);
}

Type* Context::GetVoidType()
{
    return types->GetVoidType();
}

Type* Context::GetBoolType()
{
    return types->GetBoolType();
}

Type* Context::GetSByteType()
{
    return types->GetSByteType();
}

Type* Context::GetByteType()
{
    return types->GetByteType();
}

Type* Context::GetShortType()
{
    return types->GetShortType();
}

Type* Context::GetUShortType()
{
    return types->GetUShortType();
}

Type* Context::GetIntType()
{
    return types->GetIntType();
}

Type* Context::GetUIntType()
{
    return types->GetUIntType();
}

Type* Context::GetLongType()
{
    return types->GetLongType();
}

Type* Context::GetULongType()
{
    return types->GetULongType();
}

Type* Context::GetFloatType()
{
    return types->GetFloatType();
}

Type* Context::GetDoubleType()
{
    return types->GetDoubleType();
}

Type* Context::MakePtrType(Type* baseType)
{
    return baseType->AddPointer(this);
}

StructureType* Context::GetStructureType(const SourcePos& sourcePos, int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs)
{
    return types->GetStructureType(sourcePos, typeId, fieldTypeRefs);
}

ArrayType* Context::GetArrayType(const SourcePos& sourcePos, int32_t typeId, int64_t size, const TypeRef& elementTypeRef)
{
    return types->GetArrayType(sourcePos, typeId, size, elementTypeRef);
}

FunctionType* Context::GetFunctionType(const SourcePos& sourcePos, int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs)
{
    return types->GetFunctionType(sourcePos, typeId, returnTypeRef, paramTypeRefs);
}

GlobalVariable* Context::AddGlobalVariable(const SourcePos& sourcePos, Type* type, const std::string& variableName, Value* initializer, bool once)
{
    return data->AddGlobalVariable(sourcePos, type, variableName, initializer, once, this);
}

GlobalVariable* Context::GetGlobalVariableForString(otava::intermediate::Value* stringValue)
{
    return data->GetGlobalVariableForString(stringValue);
}

void Context::ResolveTypes()
{
    types->Resolve(this);
}

void Context::ResolveType(TypeRef& typeRef)
{
    types->ResolveType(typeRef, this);
}

Value* Context::GetTrueValue()
{
    return data->GetTrueValue(*types);
}

Value* Context::GetFalseValue()
{
    return data->GetFalseValue(*types);
}

Value* Context::GetBooleanLiteral(const SourcePos& sourcePos, Type* type, bool value)
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
        Error("error making literal value: Boolean type expected", sourcePos, this);
    }
    return nullptr;
}

Value* Context::GetSByteValue(int8_t value)
{
    return data->GetSByteValue(value, *types);
}

Value* Context::GetByteValue(uint8_t value)
{
    return data->GetByteValue(value, *types);
}

Value* Context::GetShortValue(int16_t value)
{
    return data->GetShortValue(value, *types);
}

Value* Context::GetUShortValue(uint16_t value)
{
    return data->GetUShortValue(value, *types);
}

Value* Context::GetIntValue(int32_t value)
{
    return data->GetIntValue(value, *types);
}

Value* Context::GetUIntValue(uint32_t value)
{
    return data->GetUIntValue(value, *types);
}

Value* Context::GetLongValue(int64_t value)
{
    return data->GetLongValue(value, *types);
}

Value* Context::GetULongValue(uint64_t value)
{
    return data->GetULongValue(value, *types);
}

Value* Context::GetIntegerValue(Type* type, int64_t value)
{
    return data->GetIntegerValue(type, value, *types);
}

Value* Context::GetFloatValue(float value)
{
    return data->GetFloatValue(value, *types);
}

Value* Context::GetDoubleValue(double value)
{
    return data->GetDoubleValue(value, *types);
}

Value* Context::GetFloatingValue(Type* type, double value)
{
    return data->GetFloatingValue(type, value, *types);
}

Value* Context::GetNullValue(const SourcePos& sourcePos, Type* type)
{
    if (type->IsPointerType())
    {
        return data->GetNullValue(type);
    }
    else
    {
        Error("error making null literal value: pointer type expected", sourcePos, this);
    }
    return nullptr;
}

Value* Context::MakeArrayValue(const SourcePos& sourcePos, const std::vector<Value*>& elements)
{
    return data->MakeArrayValue(sourcePos, elements);
}

Value* Context::MakeStructureValue(const SourcePos& sourcePos, const std::vector<Value*>& fieldValues)
{
    return data->MakeStructureValue(sourcePos, fieldValues);
}

Value* Context::MakeStringValue(const SourcePos& sourcePos, const std::string& value)
{
    return data->MakeStringValue(sourcePos, value);
}

Value* Context::MakeStringArrayValue(const SourcePos& sourcePos, char prefix, const std::vector<Value*>& strings)
{
    return data->MakeStringArrayValue(sourcePos, prefix, strings);
}

Value* Context::MakeConversionValue(const SourcePos& sourcePos, Type* type, Value* from)
{
    return data->MakeConversionValue(sourcePos, type, from);
}

Value* Context::MakeClsIdValue(const SourcePos& sourcePos, Type* type, const std::string& clsIdStr)
{
    return data->MakeClsIdValue(sourcePos, type, clsIdStr);
}

Value* Context::MakeSymbolValue(const SourcePos& sourcePos, Type* type, const std::string& symbol)
{
    return data->MakeSymbolValue(sourcePos, type, symbol);
}

Value* Context::MakeNumericLiteral(const SourcePos& sourcePos, Type* type, const std::string& strValue)
{
    return data->MakeNumericLiteral(sourcePos, type, strValue, *types, this);
}

Value* Context::MakeAddressLiteral(const SourcePos& sourcePos, Type* type, const std::string& id)
{
    return data->MakeAddressLiteral(sourcePos, type, id, this);
}

Function* Context::CurrentFunction() const
{
    return code->CurrentFunction();
}

int32_t Context::NextTypeId()
{
    return types->NextTypeId();
}

std::string Context::GetNextStringValueId()
{
    return data->GetNextStringValueId();
}

void Context::ValidateData()
{
    // todo
}

Function* Context::AddFunctionDefinition(const SourcePos& sourcePos, Type* type, const std::string& functionId, bool once, MetadataRef* metadataRef)
{
    if (type->IsFunctionType())
    {
        FunctionType* functionType = static_cast<FunctionType*>(type);
        return code->AddFunctionDefinition(sourcePos, functionType, functionId, once, metadataRef, this);
    }
    else
    {
        Error("error adding function '" + functionId + "' definition: invalid type '" + type->Name() + "': function type expected", sourcePos, this);
    }
    return nullptr;
}

Function* Context::AddFunctionDeclaration(const SourcePos& sourcePos, Type* type, const std::string& functionId)
{
    if (type->IsFunctionType())
    {
        FunctionType* functionType = static_cast<FunctionType*>(type);
        return code->AddFunctionDeclaration(sourcePos, functionType, functionId);
    }
    else
    {
        Error("error adding function '" + functionId + "' declaration: invalid type '" + type->Name() + "': function type expected", sourcePos, this);
    }
    return nullptr;
}

MetadataStruct* Context::AddMetadataStruct(const SourcePos& sourcePos, int32_t id, Context* context)
{
    return metadata->AddMetadataStruct(sourcePos, id, context);
}

MetadataStruct* Context::CreateMetadataStruct()
{
    return metadata->CreateMetadataStruct(this);
}

MetadataBool* Context::CreateMetadataBool(bool value)
{
    return metadata->CreateMetadataBool(value);
}

MetadataLong* Context::CreateMetadataLong(int64_t value)
{
    return metadata->CreateMetadataLong(value);
}

MetadataString* Context::CreateMetadataString(const std::string& value)
{
    return metadata->CreateMetadataString(value);
}

MetadataRef* Context::CreateMetadataRef(const SourcePos& sourcePos, int32_t nodeId)
{
    return metadata->CreateMetadataRef(sourcePos, nodeId);
}

void Context::ResolveMetadataReferences()
{
    metadata->ResolveMetadataReferences(this);
}

void Context::SetCurrentFunction(Function* fn)
{
    code->SetCurrentFunction(fn);
}

Function* Context::GetOrInsertFunction(const std::string& functionId, FunctionType* functionType)
{
    return code->GetOrInsertFunction(functionId, functionType);
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

void Context::AddLineInfo(Instruction* inst)
{
    if (currentLineNumber != 0 && !inst->IsNoOperation())
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
            lineNumberInfo = CreateMetadataRef(SourcePos(), lineNumberStruct->Id());
            lineNumberInfoMap[currentLineNumber] = lineNumberInfo;
        }
        inst->SetMetadataRef(lineNumberInfo);
    }
}

RegValue* Context::MakeRegValue(Type* type)
{
    Function* currentFunction = CurrentFunction();
    RegValue* regValue = currentFunction->MakeRegValue(SourcePos(), type, currentFunction->NextRegNumber(), this);
    return regValue;
}

Instruction* Context::CreateNot(Value* arg)
{
    Instruction* inst = new NotInstruction(SourcePos(), MakeRegValue(arg->GetType()), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateNeg(Value* arg)
{
    Instruction* inst = new NegInstruction(SourcePos(), MakeRegValue(arg->GetType()), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateAdd(Value* left, Value* right)
{
    Instruction* inst = new AddInstruction(SourcePos(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateSub(Value* left, Value* right)
{
    Instruction* inst = new SubInstruction(SourcePos(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateMul(Value* left, Value* right)
{
    Instruction* inst = new MulInstruction(SourcePos(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateDiv(Value* left, Value* right)
{
    Instruction* inst = new DivInstruction(SourcePos(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateMod(Value* left, Value* right)
{
    Instruction* inst = new ModInstruction(SourcePos(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateAnd(Value* left, Value* right)
{
    Instruction* inst = new AndInstruction(SourcePos(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateOr(Value* left, Value* right)
{
    Instruction* inst = new OrInstruction(SourcePos(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateXor(Value* left, Value* right)
{
    Instruction* inst = new XorInstruction(SourcePos(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateShl(Value* left, Value* right)
{
    Instruction* inst = new ShlInstruction(SourcePos(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateShr(Value* left, Value* right)
{
    Instruction* inst = new ShrInstruction(SourcePos(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateEqual(Value* left, Value* right)
{
    Instruction* inst = new EqualInstruction(SourcePos(), MakeRegValue(GetBoolType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateLess(Value* left, Value* right)
{
    Instruction* inst = new LessInstruction(SourcePos(), MakeRegValue(GetBoolType()), left, right);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateSignExtend(Value* arg, Type* destType)
{
    Instruction* inst = new SignExtendInstruction(SourcePos(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateZeroExtend(Value* arg, Type* destType)
{
    Instruction* inst = new ZeroExtendInstruction(SourcePos(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateTruncate(Value* arg, Type* destType)
{
    Instruction* inst = new TruncateInstruction(SourcePos(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateBitcast(Value* arg, Type* destType)
{
    Instruction* inst = new BitcastInstruction(SourcePos(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateIntToFloat(Value* arg, Type* destType)
{
    Instruction* inst = new IntToFloatInstruction(SourcePos(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateFloatToInt(Value* arg, Type* destType)
{
    Instruction* inst = new FloatToIntInstruction(SourcePos(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateIntToPtr(Value* arg, Type* destType)
{
    Instruction* inst = new IntToPtrInstruction(SourcePos(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreatePtrToInt(Value* arg, Type* destType)
{
    Instruction* inst = new PtrToIntInstruction(SourcePos(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateParam(Type* type)
{
    Instruction* inst = new ParamInstruction(SourcePos(), MakeRegValue(type));
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateLocal(Type* type)
{
    Type* ptrType = MakePtrType(type);
    Instruction* inst = new LocalInstruction(SourcePos(), MakeRegValue(ptrType), type);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateLoad(Value* ptr)
{
    Instruction* inst = new LoadInstruction(SourcePos(), MakeRegValue(ptr->GetType()->RemovePointer(SourcePos(), this)), ptr);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateStore(Value* value, Value* ptr)
{
    Instruction* inst = new StoreInstruction(SourcePos(), value, ptr);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateArg(Value* arg)
{
    Instruction* inst = new ArgInstruction(SourcePos(), arg);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateElemAddr(Value* ptr, Value* index) 
{
    Instruction* inst = new ElemAddrInstruction(SourcePos(), MakeRegValue(GetElemType(ptr, index, SourcePos(), this)), ptr, index);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreatePtrOffset(Value* ptr, Value* offset)
{
    Instruction* inst = new PtrOffsetInstruction(SourcePos(), MakeRegValue(ptr->GetType()), ptr, offset);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreatePtrDiff(Value* leftPtr, Value* rightPtr)
{
    Instruction* inst = new PtrDiffInstruction(SourcePos(), MakeRegValue(GetLongType()), leftPtr, rightPtr);
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
            Instruction* inst = new ProcedureCallInstruction(SourcePos(), callee);
            AddLineInfo(inst);
            currentBasicBlock->AddInstruction(inst);
            return inst;
        }
        else
        {
            Instruction* inst = new FunctionCallInstruction(SourcePos(), MakeRegValue(returnType), callee);
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
    Instruction* inst = new RetInstruction(SourcePos(), value);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateJump(BasicBlock* dest)
{
    Instruction* inst = new JmpInstruction(SourcePos(), dest->Id());
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateBranch(Value* cond, BasicBlock* trueDest, BasicBlock* falseDest)
{
    Instruction* inst = new BranchInstruction(SourcePos(), cond, trueDest->Id(), falseDest->Id());
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

SwitchInstruction* Context::CreateSwitch(Value* cond, BasicBlock* defaultDest)
{
    SwitchInstruction* inst = new SwitchInstruction(SourcePos(), cond, defaultDest->Id());
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateTrap(const std::vector<Value*>& args)
{
    Value* b0 = nullptr;
    Value* b1 = nullptr;
    Value* b2 = nullptr;
    int n = args.size();
    for (int i = 0; i < n; ++i)
    {
        Value* arg = args[i];
        if (i == 0)
        {
            b0 = arg;
        }
        else if (i == 1)
        {
            b1 = arg;
        }
        else if (i == 2)
        {
            b2 = arg;
        }
        else
        {
            CreateArg(arg);
        }
    }
    Instruction* inst = new TrapInstruction(SourcePos(), MakeRegValue(GetLongType()), b0, b1, b2);
    AddLineInfo(inst);
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

Instruction* Context::CreateNop()
{
    Instruction* inst = new NoOperationInstruction(SourcePos());
    currentBasicBlock->AddInstruction(inst);
    return inst;
}

} // otava::intermediate
