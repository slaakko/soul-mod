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

namespace context {}

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
    CompileUnit& GetCompileUnit() { return compileUnit; }
    Types& GetTypes() { return types; }
    Data& GetData() { return data; }
    Code& GetCode() { return code; }
    Metadata& GetMetadata() { return metadata; }
    void SetFilePath(const std::string& filePath_);
    const std::string& FilePath() const;
    void SetFileId(std::int32_t fileId_) { fileId = fileId_; }
    std::int32_t FileId() const { return fileId; }
    std::string ErrorLines(const soul::ast::LineColLen& lineColLen);
    void SetCompileUnitInfo(const std::string& compileUnitId, MetadataRef* mdRef);
    void SetCompileUnitInfo(const std::string& compileUnitId_, const std::string& sourceFilePath);
    void AddStructureType(const soul::ast::Span& span, std::int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs);
    void AddArrayType(const soul::ast::Span& span, std::int32_t typeId, std::int64_t size, const TypeRef& elementTypeRef);
    void AddFunctionType(const soul::ast::Span& span, std::int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs);
    GlobalVariable* AddGlobalVariable(const soul::ast::Span& span, Type* type, const std::string& variableName, Value* initializer);
    GlobalVariable* GetGlobalVariableForString(otava::intermediate::Value* stringValue);
    void ResolveTypes();
    void ResolveData();
    void ResolveType(TypeRef& typeRef);
    Value* GetBoolValue(bool value);
    Value* GetTrueValue();
    Value* GetFalseValue();
    Value* GetBooleanLiteral(const soul::ast::Span& span, Type* type, bool value);
    Value* GetSByteValue(std::int8_t value);
    Value* GetByteValue(std::uint8_t value);
    Value* GetShortValue(std::int16_t value);
    Value* GetUShortValue(std::uint16_t value);
    Value* GetIntValue(std::int32_t value);
    Value* GetUIntValue(std::uint32_t value);
    Value* GetLongValue(std::int64_t value);
    Value* GetULongValue(std::uint64_t value);
    Value* GetIntegerValue(Type* type, std::int64_t value);
    Value* GetFloatValue(float value);
    Value* GetDoubleValue(double value);
    Value* GetFloatingValue(Type* type, double value);
    Value* GetNullValue(const soul::ast::Span& span, Type* type);
    Value* MakeArrayValue(const soul::ast::Span& span, const std::vector<Value*>& elements, ArrayType* arrayType);
    Value* MakeStructureValue(const soul::ast::Span& span, const std::vector<Value*>& fieldValues, StructureType* structureType);
    Value* MakeStringValue(const soul::ast::Span& span, const std::string& value, bool crop);
    Value* MakeStringArrayValue(const soul::ast::Span& span, char prefix, const std::vector<Value*>& elements);
    Value* MakeConversionValue(const soul::ast::Span& span, Type* type, Value* from);
    Value* MakeClsIdValue(const soul::ast::Span& span, Type* type, const std::string& clsIdStr);
    Value* MakeSymbolValue(const soul::ast::Span& span, Type* type, const std::string& symbol);
    Value* MakeIntegerLiteral(const soul::ast::Span& span, Type* type, const std::string& strValue);
    Value* MakeAddressLiteral(const soul::ast::Span& span, Type* type, const std::string& id, bool resolve);
    Type* GetVoidType();
    Type* GetBoolType();
    Type* GetSByteType();
    Type* GetByteType();
    Type* GetShortType();
    Type* GetUShortType();
    Type* GetIntType();
    Type* GetUIntType();
    Type* GetLongType();
    Type* GetULongType();
    Type* GetFloatType();
    Type* GetDoubleType();
    Type* MakePtrType(Type* baseType);
    StructureType* GetStructureType(const soul::ast::Span& span, std::int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs);
    FwdDeclaredStructureType* GetFwdDeclaredStructureType(const util::uuid& id);
    FwdDeclaredStructureType* MakeFwdDeclaredStructureType(const util::uuid& id, std::int32_t typeId);
    void AddFwdDependentType(FwdDeclaredStructureType* fwdType, Type* type);
    void ResolveForwardReferences(const util::uuid& id, StructureType* structureType);
    ArrayType* GetArrayType(const soul::ast::Span& span, std::int32_t typeId, std::int64_t size, const TypeRef& elementTypeRef);
    FunctionType* GetFunctionType(const soul::ast::Span& span, std::int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs);
    Function* CurrentFunction() const;
    void SetCurrentFunction(Function* function);
    Function* GetOrInsertFunction(const std::string& functionId, FunctionType* functionType);
    Function* AddFunctionDefinition(const soul::ast::Span& span, Type* type, const std::string& functionId, bool inline_, bool linkOnce,
        otava::intermediate::MetadataRef* metadataRef);
    Function* AddFunctionDeclaration(const soul::ast::Span& span, Type* type, const std::string& functionId);
    MetadataStruct* AddMetadataStruct(const soul::ast::Span& span, std::int32_t id);
    MetadataBool* CreateMetadataBool(bool value);
    MetadataLong* CreateMetadataLong(std::int64_t value);
    MetadataString* CreateMetadataString(const std::string& value, bool crop);
    MetadataRef* CreateMetadataRef(const soul::ast::Span& span, std::int32_t nodeId);
    MetadataStruct* CreateMetadataStruct();
    void ResolveMetadataReferences();
    void SetCurrentBasicBlock(BasicBlock* bb);
    BasicBlock* CreateBasicBlock();
    void SetCurrentLineNumber(int lineNumber);
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
    Instruction* CreateElemAddr(Value* ptr, Value* index);
    Instruction* CreatePtrOffset(Value* ptr, Value* offset);
    Instruction* CreatePtrDiff(Value* leftPtr, Value* rightPtr);
    Instruction* CreateCall(Value* function);
    Instruction* CreateRet(Value* value);
    Instruction* CreateJump(BasicBlock* dest);
    Instruction* CreateBranch(Value* cond, BasicBlock* trueDest, BasicBlock* falseDest);
    SwitchInstruction* CreateSwitch(Value* cond, BasicBlock* defaultDest);
    Instruction* CreateNop();
    soul::lexer::FileMap& GetFileMap() { return fileMap; }
    std::int32_t NextTypeId();
    std::string GetNextStringValueId();
    otava::assembly::Context* AssemblyContext() { return &assemblyContext; }
    void WriteFile();
    void SetInlineDepth(int inlineDepth_) { inlineDepth = inlineDepth_; }
    int InlineDepth() const { return inlineDepth; }
    void SetMaxArithmeticOptimizationCount(int maxArithmeticOptimizationCount_) { maxArithmeticOptimizationCount = maxArithmeticOptimizationCount_; }
    int MaxArithmeticOptimizationCount() const { return maxArithmeticOptimizationCount; }
    void SetContextFlag(ContextFlags flag) { flags = flags | flag; }
    bool GetContextFlag(ContextFlags flag) const { return (flags & flag) != ContextFlags::none; }
    int FunctionsInlined() const { return functionsInlined; }
    void IncFunctionsInlined() { ++functionsInlined; }
    int TotalFunctions() const { return totalFunctions; }
    void IncTotalFunctions() { ++totalFunctions; }
    void AddLineInfo(Instruction* inst);
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
    int functionsInlined;
    int totalFunctions;
};

} // otava::intermediate
