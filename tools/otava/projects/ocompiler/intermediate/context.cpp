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

std::expected<std::string, int> Context::ErrorLines(const soul::ast::LineColLen& lineColLen)
{
    if (lineColLen.IsValid())
    {
        std::expected<std::u32string, int> frv = fileMap.GetFileLine(fileId, lineColLen.line);
        if (!frv) return std::unexpected<int>(frv.error());
        std::expected<std::string, int> rv = util::ToUtf8(*frv);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorLines = std::move(*rv);
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

void Context::AddStructureType(const soul::ast::Span& span, std::int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs, MetadataRef* mdRef)
{
    types.AddStructureType(span, typeId, fieldTypeRefs, mdRef);
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

std::expected<GlobalVariable*, int> Context::GetGlobalVariableForString(otava::intermediate::Value* stringValue, Type* charType)
{
    return data.GetGlobalVariableForString(stringValue, charType);
}

std::expected<bool, int> Context::ResolveTypes()
{
    return types.Resolve(this);
}

std::expected<bool, int> Context::ResolveType(TypeRef& typeRef)
{
    return types.ResolveType(typeRef, this);
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

Value* Context::GetLongValue(std::int64_t value)
{ 
    return data.GetLongValue(value, types); 
}

Value* Context::GetUShortValue(std::uint16_t value)
{ 
    return data.GetUShortValue(value, types); 
}

Value* Context::GetUIntValue(std::uint32_t value)
{ 
    return data.GetUIntValue(value, types); 
}

Value* Context::GetIntegerValue(Type* type, std::int64_t value)
{
    return data.GetIntegerValue(type, value, types);
}

Value* Context::GetFloatingValue(Type* type, double value) 
{ 
    return data.GetFloatingValue(type, value, types); 
}

Value* Context::MakeSymbolValue(const soul::ast::Span& span, Type* type, const std::string& symbol)
{ 
    return data.MakeSymbolValue(span, type, symbol); 
}

Value* Context::MakeStringValue(const soul::ast::Span& span, const std::string& value, bool crop)
{
    return data.MakeStringValue(span, value, crop);
}

Value* Context::MakeStructureValue(const soul::ast::Span& span, const std::vector<Value*>& fieldValues, StructureType* structureType)
{
    return data.MakeStructureValue(span, fieldValues, structureType);
}

Value* Context::MakeArrayValue(const soul::ast::Span& span, const std::vector<Value*>& elements, ArrayType* arrayType)
{
    return data.MakeArrayValue(span, elements, arrayType);
}

Value* Context::MakeStringArrayValue(const soul::ast::Span& span, char prefix, const std::vector<Value*>& elements)
{
    return data.MakeStringArrayValue(span, prefix, elements);
}

std::expected<Function*, int> Context::AddFunctionDefinition(const soul::ast::Span& span, Type* type, const std::string& functionId, bool inline_, 
    bool linkOnce, bool createEntry, otava::intermediate::MetadataRef* metadataRef)
{
    if (type->IsPointerType())
    {
        std::expected<Type*, int> rv = type->RemovePointer(span, this);
        if (!rv) return std::unexpected<int>(rv.error());
        type = *rv;
    }
    if (type->IsFunctionType())
    {
        FunctionType* functionType = static_cast<FunctionType*>(type);
        return code.AddFunctionDefinition(span, functionType, functionId, inline_, linkOnce, createEntry, metadataRef);
    }
    else
    {
        return Error("error adding function '" + functionId + "' definition: invalid type '" + type->Name() + "': function type expected", span, this);
    }
}

std::expected<Function*, int> Context::AddFunctionDeclaration(const soul::ast::Span& span, Type* type, const std::string& functionId)
{
    if (type->IsPointerType())
    {
        std::expected<Type*, int> rv = type->RemovePointer(span, this);
        if (!rv) return std::unexpected<int>(rv.error());
        type = *rv;
    }
    if (type->IsFunctionType())
    {
        FunctionType* functionType = static_cast<FunctionType*>(type);
        return code.AddFunctionDeclaration(span, functionType, functionId);
    }
    else
    {
        return Error("error adding function '" + functionId + "' declaration: invalid type '" + type->Name() + "': function type expected", span, this);
    }
}

Instruction* Context::CreateNot(Value* arg)
{
    Instruction* inst = new NotInstruction(soul::ast::Span(), MakeRegValue(arg->GetType()), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateNeg(Value* arg)
{
    Instruction* inst = new NegInstruction(soul::ast::Span(), MakeRegValue(arg->GetType()), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateAdd(Value* left, Value* right)
{
    Instruction* inst = new AddInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateSub(Value* left, Value* right)
{
    Instruction* inst = new SubInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateMul(Value* left, Value* right)
{
    Instruction* inst = new MulInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateDiv(Value* left, Value* right)
{
    Instruction* inst = new DivInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateMod(Value* left, Value* right)
{
    Instruction* inst = new ModInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateAnd(Value* left, Value* right)
{
    Instruction* inst = new AndInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateOr(Value* left, Value* right)
{
    Instruction* inst = new OrInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateXor(Value* left, Value* right)
{
    Instruction* inst = new XorInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateShl(Value* left, Value* right)
{
    Instruction* inst = new ShlInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateShr(Value* left, Value* right)
{
    Instruction* inst = new ShrInstruction(soul::ast::Span(), MakeRegValue(left->GetType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateEqual(Value* left, Value* right)
{
    Instruction* inst = new EqualInstruction(soul::ast::Span(), MakeRegValue(GetBoolType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateLess(Value* left, Value* right)
{
    Instruction* inst = new LessInstruction(soul::ast::Span(), MakeRegValue(GetBoolType()), left, right);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateSignExtend(Value* arg, Type* destType)
{
    Instruction* inst = new SignExtendInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateZeroExtend(Value* arg, Type* destType)
{
    Instruction* inst = new ZeroExtendInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateFloatingPointExtend(Value* arg, Type* destType)
{
    Instruction* inst = new FloatingPointExtendInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateTruncate(Value* arg, Type* destType)
{
    Instruction* inst = new TruncateInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateBitcast(Value* arg, Type* destType)
{
    Instruction* inst = new BitcastInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateIntToFloat(Value* arg, Type* destType)
{
    Instruction* inst = new IntToFloatInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateFloatToInt(Value* arg, Type* destType)
{
    Instruction* inst = new FloatToIntInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateIntToPtr(Value* arg, Type* destType)
{
    Instruction* inst = new IntToPtrInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreatePtrToInt(Value* arg, Type* destType)
{
    Instruction* inst = new PtrToIntInstruction(soul::ast::Span(), MakeRegValue(destType), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateParam(Type* type)
{
    Instruction* inst = new ParamInstruction(soul::ast::Span(), MakeRegValue(type));
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

std::expected<Instruction*, int> Context::CreateLocal(Type* type)
{
    std::expected<Type*, int> rv = MakePtrType(type);
    if (!rv) return std::unexpected<int>(rv.error());
    Type* ptrType = *rv;
    Instruction* inst = new LocalInstruction(soul::ast::Span(), MakeRegValue(ptrType), type);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return std::expected<Instruction*, int>(inst);
}

std::expected<Instruction*, int> Context::CreateLocalInEntryBlock(Type* type)
{
    std::expected<Type*, int> rv = MakePtrType(type);
    if (!rv) return std::unexpected<int>(rv.error());
    Type* ptrType = *rv;
    Instruction* inst = new LocalInstruction(soul::ast::Span(), MakeRegValue(ptrType), type);
    AddLineInfo(inst);
    BasicBlock* entryBlock = code.CurrentFunction()->GetBasicBlock(0);
    entryBlock->DoAddInstruction(inst);
    return std::expected<Instruction*, int>(inst);
}

std::expected<Instruction*, int> Context::CreateLoad(Value* ptr)
{
    std::expected<Type*, int> rv = ptr->GetType()->RemovePointer(soul::ast::Span(), this);
    if (!rv) return std::unexpected<int>(rv.error());
    Type* type = *rv;
    Instruction* inst = new LoadInstruction(soul::ast::Span(), MakeRegValue(type), ptr);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return std::expected<Instruction*, int>(inst);
}

Instruction* Context::CreateStore(Value* value, Value* ptr)
{
    Instruction* inst = new StoreInstruction(soul::ast::Span(), value, ptr);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateArg(Value* arg)
{
    Instruction* inst = new ArgInstruction(soul::ast::Span(), arg);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateElemAddr(Value* ptr, Value* index, Type* type)
{
    Instruction* inst = new ElemAddrInstruction(soul::ast::Span(), MakeRegValue(type), ptr, index);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreatePtrOffset(Value* ptr, Value* offset)
{
    Instruction* inst = new PtrOffsetInstruction(soul::ast::Span(), MakeRegValue(ptr->GetType()), ptr, offset);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreatePtrDiff(Value* leftPtr, Value* rightPtr)
{
    Instruction* inst = new PtrDiffInstruction(soul::ast::Span(), MakeRegValue(GetLongType()), leftPtr, rightPtr);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

std::expected<Instruction*, int> Context::CreateCall(Value* callee)
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
            if (currentBasicBlock)
            {
                currentBasicBlock->DoAddInstruction(inst);
            }
            return std::expected<Instruction*, int>(inst);
        }
        else
        {
            Instruction* inst = new FunctionCallInstruction(soul::ast::Span(), MakeRegValue(returnType), callee);
            AddLineInfo(inst);
            if (currentBasicBlock)
            {
                currentBasicBlock->DoAddInstruction(inst);
            }
            return std::expected<Instruction*, int>(inst);
        }
    }
    else
    {
        return Error("invalid call", callee->Span(), this);
    }
}

Instruction* Context::CreateRet(Value* value)
{
    Instruction* inst = new RetInstruction(soul::ast::Span(), value);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateJump(BasicBlock* dest)
{
    JmpInstruction* inst = new JmpInstruction(soul::ast::Span(), dest->Id());
    inst->SetTargetBasicBlock(dest);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateBranch(Value* cond, BasicBlock* trueDest, BasicBlock* falseDest)
{
    BranchInstruction* inst = new BranchInstruction(soul::ast::Span(), cond, trueDest->Id(), falseDest->Id());
    inst->SetTrueTargetBasicBlock(trueDest);
    inst->SetFalseTargetBasicBlock(falseDest);
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

SwitchInstruction* Context::CreateSwitch(Value* cond, BasicBlock* defaultDest)
{
    SwitchInstruction* inst = new SwitchInstruction(soul::ast::Span(), cond, defaultDest->Id());
    AddLineInfo(inst);
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
    return inst;
}

Instruction* Context::CreateNop()
{
    Instruction* inst = new NoOperationInstruction(soul::ast::Span());
    if (currentBasicBlock)
    {
        currentBasicBlock->DoAddInstruction(inst);
    }
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

std::expected<bool, int> Context::WriteFile()
{
    return compileUnit.Write();
}

} // otava::intermediate
