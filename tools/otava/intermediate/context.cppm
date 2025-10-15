// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.context;

import otava.assembly;
import otava.intermediate.compile_unit;
import otava.intermediate.types;
import otava.intermediate.data;
import otava.intermediate.code;
import otava.intermediate.metadata;
import soul.lexer;
import soul.ast.span;
import util;
import std;

export namespace otava::intermediate {

enum class ContextFlags : int
{
    none = 0, debug = 1 << 0
};

constexpr ContextFlags operator|(ContextFlags left, ContextFlags right)
{
    return ContextFlags(int(left) | int(right));
}

constexpr ContextFlags operator&(ContextFlags left, ContextFlags right)
{
    return ContextFlags(int(left) & int(right));
}

constexpr ContextFlags operator~(ContextFlags flags)
{
    return ContextFlags(~int(flags));
}

class Context
{
public:
    Context();
    inline CompileUnit& GetCompileUnit() { return compileUnit; }
    inline Types& GetTypes() { return types; }
    inline Data& GetData() { return data; }
    inline Code& GetCode() { return code; }
    inline Metadata& GetMetadata() { return metadata; }
    void SetFilePath(const std::string& filePath_);
    const std::string& FilePath() const;
    inline void SetFileId(std::int32_t fileId_) { fileId = fileId_; }
    inline std::int32_t FileId() const { return fileId; }
    std::string ErrorLines(const soul::ast::LineColLen& lineColLen);
    void SetCompileUnitInfo(const std::string& compileUnitId, MetadataRef* mdRef);
    void SetCompileUnitInfo(const std::string& compileUnitId_, const std::string& sourceFilePath);
    void AddStructureType(const soul::ast::Span& span, std::int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs, MetadataRef* mdRef);
    void AddArrayType(const soul::ast::Span& span, std::int32_t typeId, std::int64_t size, const TypeRef& elementTypeRef);
    void AddFunctionType(const soul::ast::Span& span, std::int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs);
    GlobalVariable* AddGlobalVariable(const soul::ast::Span& span, Type* type, const std::string& variableName, Value* initializer);
    GlobalVariable* GetGlobalVariableForString(otava::intermediate::Value* stringValue, Type* charType);
    void ResolveTypes();
    inline void ResolveData() { data.ResolveAddressValues(); }
    void ResolveType(TypeRef& typeRef);
    inline Value* GetBoolValue(bool value) { if (value) return GetTrueValue(); else return GetFalseValue(); }
    inline Value* GetTrueValue() { return data.GetTrueValue(types); }
    inline Value* GetFalseValue() { return data.GetFalseValue(types); }
    Value* GetBooleanLiteral(const soul::ast::Span& span, Type* type, bool value);
    inline Value* GetSByteValue(std::int8_t value) { return data.GetSByteValue(value, types); }
    inline Value* GetByteValue(std::uint8_t value) { return data.GetByteValue(value, types); }
    inline Value* GetShortValue(std::int16_t value) { return data.GetShortValue(value, types); }
    inline Value* GetUShortValue(std::uint16_t value) { return data.GetUShortValue(value, types); }
    inline Value* GetIntValue(std::int32_t value) { return data.GetIntValue(value, types); }
    inline Value* GetUIntValue(std::uint32_t value) { return data.GetUIntValue(value, types); }
    inline Value* GetLongValue(std::int64_t value) { return data.GetLongValue(value, types); }
    inline Value* GetULongValue(std::uint64_t value) { return data.GetULongValue(value, types); }
    inline Value* GetIntegerValue(Type* type, std::int64_t value) { return data.GetIntegerValue(type, value, types); }
    inline Value* GetFloatValue(float value) { return data.GetFloatValue(value, types); }
    inline Value* GetDoubleValue(double value) { return data.GetDoubleValue(value, types); }
    inline Value* GetFloatingValue(Type* type, double value) { return data.GetFloatingValue(type, value, types); }
    Value* GetNullValue(const soul::ast::Span& span, Type* type);
    inline Value* MakeArrayValue(const soul::ast::Span& span, const std::vector<Value*>& elements, ArrayType* arrayType) 
    { 
        return data.MakeArrayValue(span, elements, arrayType); 
    }
    inline Value* MakeStructureValue(const soul::ast::Span& span, const std::vector<Value*>& fieldValues, StructureType* structureType)
    {
        return data.MakeStructureValue(span, fieldValues, structureType);
    }
    inline Value* MakeStringValue(const soul::ast::Span& span, const std::string& value, bool crop)
    {
        return data.MakeStringValue(span, value, crop);
    }
    inline Value* MakeStringArrayValue(const soul::ast::Span& span, char prefix, const std::vector<Value*>& elements)
    {
        return data.MakeStringArrayValue(span, prefix, elements);
    }
    inline Value* MakeConversionValue(const soul::ast::Span& span, Type* type, Value* from) { return data.MakeConversionValue(span, type, from); }
    inline Value* MakeClsIdValue(const soul::ast::Span& span, Type* type, const std::string& clsIdStr) { return data.MakeClsIdValue(span, type, clsIdStr); }
    inline Value* MakeSymbolValue(const soul::ast::Span& span, Type* type, const std::string& symbol) { return data.MakeSymbolValue(span, type, symbol); }
    inline Value* MakeIntegerLiteral(const soul::ast::Span& span, Type* type, const std::string& strValue) 
    { 
        return data.MakeIntegerLiteral(span, type, strValue, types); 
    }
    inline Value* MakeAddressLiteral(const soul::ast::Span& span, Type* type, const std::string& id, bool resolve)
    {
        return data.MakeAddressLiteral(span, type, id, resolve);
    }
    inline Type* GetVoidType() { return types.GetVoidType(); }
    inline Type* GetBoolType() { return types.GetBoolType(); }
    inline Type* GetSByteType() { return types.GetSByteType(); }
    inline Type* GetByteType() { return types.GetByteType(); }
    inline Type* GetShortType() { return types.GetShortType(); }
    inline Type* GetUShortType() { return types.GetUShortType(); }
    inline Type* GetIntType() { return types.GetIntType(); }
    inline Type* GetUIntType() { return types.GetUIntType(); }
    inline Type* GetLongType() { return types.GetLongType(); }
    inline Type* GetULongType() { return types.GetULongType(); }
    inline Type* GetFloatType() { return types.GetFloatType(); }
    inline Type* GetDoubleType() { return types.GetDoubleType(); }
    inline Type* MakePtrType(Type* baseType) { return types.MakePtrType(baseType); }
    inline StructureType* GetStructureType(const soul::ast::Span& span, std::int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs)
    {
        return types.GetStructureType(span, typeId, fieldTypeRefs);
    }
    inline FwdDeclaredStructureType* GetFwdDeclaredStructureType(const util::uuid& id)
    {
        return types.GetFwdDeclaredStructureType(id);
    }
    inline FwdDeclaredStructureType* MakeFwdDeclaredStructureType(const util::uuid& id, std::int32_t typeId, const std::string& comment)
    {
        return types.MakeFwdDeclaredStructureType(id, typeId, comment);
    }
    inline void AddFwdDependentType(FwdDeclaredStructureType* fwdType, Type* type) { types.AddFwdDependentType(fwdType, type); }
    inline void ResolveForwardReferences(const util::uuid& id, StructureType* structureType) { types.ResolveForwardReferences(id, structureType); }
    inline ArrayType* GetArrayType(const soul::ast::Span& span, std::int32_t typeId, std::int64_t size, const TypeRef& elementTypeRef)
    {
        return types.GetArrayType(span, typeId, size, elementTypeRef);
    }
    inline FunctionType* GetFunctionType(const soul::ast::Span& span, std::int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs)
    {
        return types.GetFunctionType(span, typeId, returnTypeRef, paramTypeRefs);
    }
    inline Function* CurrentFunction() const { return code.CurrentFunction(); }
    inline void SetCurrentFunction(Function* function) { code.SetCurrentFunction(function); }
    inline Function* GetOrInsertFunction(const std::string& functionId, FunctionType* functionType)
    {
        return code.GetOrInsertFunction(functionId, functionType);
    }
    Function* AddFunctionDefinition(const soul::ast::Span& span, Type* type, const std::string& functionId, bool inline_, bool linkOnce, bool createEntry,
        otava::intermediate::MetadataRef* metadataRef);
    Function* AddFunctionDeclaration(const soul::ast::Span& span, Type* type, const std::string& functionId);
    inline MetadataStruct* AddMetadataStruct(const soul::ast::Span& span, std::int32_t id)
    {
        return metadata.AddMetadataStruct(span, id);
    }
    inline MetadataBool* CreateMetadataBool(bool value) { return metadata.CreateMetadataBool(value); }
    inline MetadataLong* CreateMetadataLong(std::int64_t value) { return metadata.CreateMetadataLong(value); }
    inline MetadataString* CreateMetadataString(const std::string& value, bool crop) { return metadata.CreateMetadataString(value, crop); }
    inline MetadataRef* CreateMetadataRef(const soul::ast::Span& span, std::int32_t nodeId) { return metadata.CreateMetadataRef(span, nodeId); }
    inline MetadataStruct* CreateMetadataStruct() { return metadata.CreateMetadataStruct(); }
    inline void ResolveMetadataReferences() { metadata.ResolveMetadataReferences(); }
    inline void SetCurrentBasicBlock(BasicBlock* bb) { currentBasicBlock = bb; }
    inline BasicBlock* CreateBasicBlock() { return CurrentFunction()->CreateBasicBlock(); }
    inline void SetCurrentLineNumber(int lineNumber) 
    {
        if (lineNumber != -1)
        {
            currentLineNumber = lineNumber;
        }
    }
    Instruction* CreateNot(Value* arg);
    Instruction* CreateNeg(Value* arg);
    Instruction* CreateAdd(Value* left, Value* right);
    Instruction* CreateSub(Value* left, Value* right);
    Instruction* CreateMul(Value* left, Value* right);
    Instruction* CreateDiv(Value* left, Value* right);
    Instruction* CreateMod(Value* left, Value* right);
    Instruction* CreateAnd(Value* left, Value* right);
    Instruction* CreateOr(Value* left, Value* right);
    Instruction* CreateXor(Value* left, Value* right);
    Instruction* CreateShl(Value* left, Value* right);
    Instruction* CreateShr(Value* left, Value* right);
    Instruction* CreateEqual(Value* left, Value* right);
    Instruction* CreateLess(Value* left, Value* right);
    Instruction* CreateSignExtend(Value* arg, Type* destType);
    Instruction* CreateZeroExtend(Value* arg, Type* destType);
    Instruction* CreateFloatingPointExtend(Value* arg, Type* destType);
    Instruction* CreateTruncate(Value* arg, Type* destType);
    Instruction* CreateBitcast(Value* arg, Type* destType);
    Instruction* CreateIntToFloat(Value* arg, Type* destType);
    Instruction* CreateFloatToInt(Value* arg, Type* destType);
    Instruction* CreateIntToPtr(Value* arg, Type* destType);
    Instruction* CreatePtrToInt(Value* arg, Type* destType);
    Instruction* CreateParam(Type* type);
    Instruction* CreateLocal(Type* type);
    Instruction* CreateLocalInEntryBlock(Type* type);
    Instruction* CreateLoad(Value* ptr);
    Instruction* CreateStore(Value* value, Value* ptr);
    Instruction* CreateArg(Value* arg);
    Instruction* CreateElemAddr(Value* ptr, Value* index, Type* type);
    Instruction* CreatePtrOffset(Value* ptr, Value* offset);
    Instruction* CreatePtrDiff(Value* leftPtr, Value* rightPtr);
    Instruction* CreateCall(Value* function);
    Instruction* CreateRet(Value* value);
    Instruction* CreateJump(BasicBlock* dest);
    Instruction* CreateBranch(Value* cond, BasicBlock* trueDest, BasicBlock* falseDest);
    SwitchInstruction* CreateSwitch(Value* cond, BasicBlock* defaultDest);
    Instruction* CreateNop();
    inline soul::lexer::FileMap& GetFileMap() { return fileMap; }
    inline std::int32_t NextTypeId() { return types.NextTypeId(); }
    inline std::string GetNextStringValueId() { return data.GetNextStringValueId(); }
    inline otava::assembly::Context* AssemblyContext() { return &assemblyContext; }
    void WriteFile();
    inline void SetInlineDepth(int inlineDepth_) { inlineDepth = inlineDepth_; }
    inline int InlineDepth() const { return inlineDepth; }
    inline void SetMaxArithmeticOptimizationCount(int maxArithmeticOptimizationCount_) { maxArithmeticOptimizationCount = maxArithmeticOptimizationCount_; }
    inline int MaxArithmeticOptimizationCount() const { return maxArithmeticOptimizationCount; }
    inline void SetContextFlag(ContextFlags flag) { flags = flags | flag; }
    inline bool GetContextFlag(ContextFlags flag) const { return (flags & flag) != ContextFlags::none; }
    inline int TotalFunctions() const { return totalFunctions; }
    inline void IncTotalFunctions() { ++totalFunctions; }
    void AddLineInfo(Instruction* inst);
    inline void IncInlinedFunctionCalls() { ++inlinedFunctionCalls; }
    inline int InlinedFunctionCalls() const { return inlinedFunctionCalls; }
    inline int FunctionsInlined() const { return functionsInlined; }
    inline void IncFunctionsInlined() { ++functionsInlined; }
private:
    RegValue* MakeRegValue(Type* type);
    CompileUnit compileUnit;
    Types types;
    Data data;
    Code code;
    Metadata metadata;
    BasicBlock* currentBasicBlock;
    int currentLineNumber;
    std::map<int, MetadataRef*> lineNumberInfoMap;
    soul::lexer::FileMap fileMap;
    std::int32_t fileId;
    otava::assembly::Context assemblyContext;
    int inlineDepth;
    int maxArithmeticOptimizationCount;
    std::unique_ptr<otava::intermediate::MetadataRef> metadataRef;
    ContextFlags flags;
    int inlinedFunctionCalls;
    int functionsInlined;
    int totalFunctions;
};

} // otava::intermediate
