// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.context;

import std.core;
import soul.ast.source.pos;
import soul.lexer.base;
import soul.lexer.file.map;
import otava.assembly.context;

export namespace otava::intermediate::context {}

export namespace otava::intermediate {

class CompileUnit;
class Types;
class Data;
class Code;
class Metadata;
class MetadataRef;
class Type;
class TypeRef;
class Value;
class Function;
class StructureType;
class ArrayType;
class FunctionType;
class MetadataStruct;
class MetadataBool;
class MetadataLong;
class MetadataString;
class BasicBlock;
class Instruction;
class SwitchInstruction;
class Value;
class RegValue;

using SourcePos = soul::ast::SourcePos;

class Context
{
public:
    Context();
    void WriteFile();
    CompileUnit& GetCompileUnit() { return *compileUnit; }
    Types& GetTypes() { return *types; }
    Data& GetData() { return *data; }
    Code& GetCode() { return *code; }
    Metadata& GetMetadata() { return *metadata; }
    void SetFilePath(const std::string& filePath_);
    const std::string& FilePath() const;
    std::string ErrorLines(const SourcePos& sourcePos);
    void SetCompileUnitInfo(const std::string& compileUnitId, MetadataRef* mdRef);
    void SetCompileUnitInfo(const std::string& compileUnitId_, const std::string& sourceFilePath);
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
    StructureType* GetStructureType(const SourcePos& sourcePos, int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs);
    ArrayType* GetArrayType(const SourcePos& sourcePos, int32_t typeId, int64_t size, const TypeRef& elementTypeRef);
    FunctionType* GetFunctionType(const SourcePos& sourcePos, int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs);
    void AddGlobalVariable(const SourcePos& sourcePos, Type* type, const std::string& variableName, Value* initializer, bool once);
    void ResolveTypes();
    void ValidateData();
    void ResolveType(TypeRef& typeRef);
    Value* GetTrueValue();
    Value* GetFalseValue();
    Value* GetBooleanLiteral(const SourcePos& sourcePos, Type* type, bool value);
    Value* GetSByteValue(int8_t value);
    Value* GetByteValue(uint8_t value);
    Value* GetShortValue(int16_t value);
    Value* GetUShortValue(uint16_t value);
    Value* GetIntValue(int32_t value);
    Value* GetUIntValue(uint32_t value);
    Value* GetLongValue(int64_t value);
    Value* GetULongValue(uint64_t value);
    Value* GetIntegerValue(Type* type, int64_t value);
    Value* GetFloatValue(float value);
    Value* GetDoubleValue(double value);
    Value* GetFloatingValue(Type* type, double value);
    Value* GetNullValue(const SourcePos& sourcePos, Type* type);
    Value* MakeArrayValue(const SourcePos& sourcePos, const std::vector<Value*>& elements);
    Value* MakeStructureValue(const SourcePos& sourcePos, const std::vector<Value*>& fieldValues);
    Value* MakeStringValue(const SourcePos& sourcePos, const std::string& value);
    Value* MakeStringArrayValue(const SourcePos& sourcePos, char prefix, const std::vector<Value*>& strings);
    Value* MakeConversionValue(const SourcePos& sourcePos, Type* type, Value* from);
    Value* MakeClsIdValue(const SourcePos& sourcePos, Type* type, const std::string& clsIdStr);
    Value* MakeSymbolValue(const SourcePos& sourcePos, Type* type, const std::string& symbol);
    Value* MakeNumericLiteral(const SourcePos& sourcePos, Type* type, const std::string& strValue);
    Value* MakeAddressLiteral(const SourcePos& sourcePos, Type* type, const std::string& id);
    Function* CurrentFunction() const;
    void SetCurrentFunction(Function* function);
    Function* GetOrInsertFunction(const std::string& functionId, FunctionType* functionType);
    Function* AddFunctionDefinition(const SourcePos& sourcePos, Type* type, const std::string& functionId, bool once, MetadataRef* metadataRef);
    Function* AddFunctionDeclaration(const SourcePos& sourcePos, Type* type, const std::string& functionId);
    MetadataStruct* AddMetadataStruct(const SourcePos& sourcePos, int32_t id, Context* context);
    MetadataBool* CreateMetadataBool(bool value);
    MetadataLong* CreateMetadataLong(int64_t value);
    MetadataString* CreateMetadataString(const std::string& value);
    MetadataRef* CreateMetadataRef(const SourcePos& sourcePos, int32_t nodeId);
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
    Instruction* CreateTruncate(Value* arg, Type* destType);
    Instruction* CreateBitcast(Value* arg, Type* destType);
    Instruction* CreateIntToFloat(Value* arg, Type* destType);
    Instruction* CreateFloatToInt(Value* arg, Type* destType);
    Instruction* CreateIntToPtr(Value* arg, Type* destType);
    Instruction* CreatePtrToInt(Value* arg, Type* destType);
    Instruction* CreateParam(Type* type);
    Instruction* CreateLocal(Type* type);
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
    Instruction* CreateTrap(const std::vector<Value*>& args);
    Instruction* CreateNop();
    soul::lexer::FileMap& GetFileMap() { return fileMap; }
    int32_t NextTypeId();
    void AddLineInfo(Instruction* inst);
    otava::assembly::Context& AssemblyContext() { return assemblyContext; }
private:
    RegValue* MakeRegValue(Type* type);
    std::unique_ptr<CompileUnit> compileUnit;
    std::unique_ptr<Types> types;
    std::unique_ptr<Data> data;
    std::unique_ptr<Code> code;
    std::unique_ptr<Metadata> metadata;
    BasicBlock* currentBasicBlock;
    int currentLineNumber;
    std::map<int, MetadataRef*> lineNumberInfoMap;
    soul::lexer::FileMap fileMap;
    otava::assembly::Context assemblyContext;
};

} // otava::intermediate

