// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.type;

import otava.assembly.data;
import std;
import soul.ast.source.pos;
import util.code.formatter;
import util.uuid;

export namespace otava::intermediate::type {}

export namespace otava::intermediate {

using SourcePos = soul::ast::SourcePos;

class Context;
class Types;
class Visitor;
class ArrayType;
class StructureType;
class FwdDeclaredStructureType;
class TypeRef;
class Value;

const std::int32_t voidTypeId = 0;
const std::int32_t boolTypeId = 1;
const std::int32_t sbyteTypeId = 2;
const std::int32_t byteTypeId = 3;
const std::int32_t shortTypeId = 4;
const std::int32_t ushortTypeId = 5;
const std::int32_t intTypeId = 6;
const std::int32_t uintTypeId = 7;
const std::int32_t longTypeId = 8;
const std::int32_t ulongTypeId = 9;
const std::int32_t floatTypeId = 10;
const std::int32_t doubleTypeId = 11;
const std::int32_t userTypeId = 12;
const std::int32_t pointerTypeId = std::int32_t(1) << 31;

constexpr bool IsFundamentalTypeId(std::int32_t typeId) { return typeId >= 0 && typeId < userTypeId; }
constexpr bool IsPointerTypeId(std::int32_t typeId) { return (typeId & pointerTypeId) != 0; }

inline std::int32_t MakeUserTypeId(const std::string& typeIdStr)
{
    return userTypeId + std::stoi(typeIdStr.substr(2));
}

constexpr std::int32_t MakeUserTypeId(std::int32_t typeId)
{
    return typeId - userTypeId;
}

constexpr std::int32_t MakePointerTypeId(std::int32_t baseTypeId, std::int8_t pointerCount)
{
    return pointerTypeId | (std::int32_t(pointerCount) << (32 - 8)) | baseTypeId;
}

constexpr std::int32_t MakeTypeId(std::int32_t baseTypeId, std::int32_t pointerCount)
{
    if (pointerCount == 0)
    {
        return baseTypeId;
    }
    else
    {
        return MakePointerTypeId(baseTypeId, pointerCount);
    }
}

constexpr std::int32_t GetBaseTypeId(std::int32_t typeId)
{
    return typeId & (~(pointerTypeId | (std::int32_t(0x7F) << (32 - 8))) | 0x00FFFFFF);
}

constexpr std::int8_t GetPointerCount(std::int32_t typeId)
{
    return (typeId & (std::int32_t(0x7F) << (32 - 8))) >> (32 - 8);
}

enum class TypeKind : int
{
    fundamentalType, structureType, arrayType, functionType, pointerType, fwdDeclaredStructureType
};

class Type
{
public:
    Type(const SourcePos& sourcePos_, TypeKind kind_, std::int32_t id_);
    virtual ~Type();
    virtual void Accept(Visitor& visitor) {}
    virtual std::int64_t Size() const = 0;
    virtual std::int64_t Alignment() const = 0;
    virtual otava::assembly::DataInst DataInstruction() const { return otava::assembly::DataInst::DB; }
    TypeKind Kind() const { return kind; }
    bool IsFundamentalType() const { return kind == TypeKind::fundamentalType; }
    bool IsVoidType() const { return id == voidTypeId; }
    bool IsBooleanType() const { return id == boolTypeId; }
    bool IsCompoundType() const { return !IsFundamentalType(); }
    bool IsArithmeticType() const { return IsIntegerType() || IsFloatingPointType(); }
    bool IsIntegerType() const;
    bool IsUnsignedType() const;
    bool IsFloatingPointType() const;
    bool IsFloatType() const { return id == floatTypeId; }
    bool IsByteType() const { return id == byteTypeId; }
    bool IsDoubleType() const { return id == doubleTypeId; }
    bool IsPointerType() const { return kind == TypeKind::pointerType; }
    bool IsAggregateType() const;
    bool IsFwdDeclaredStructureType() const { return kind == TypeKind::fwdDeclaredStructureType; }
    virtual void ReplaceForwardReference(FwdDeclaredStructureType* fwdDeclaredType, StructureType* structureType, Context* context);
    Type* AddPointer(Context* context) const;
    Type* RemovePointer(const SourcePos& sourcePos, Context* context) const;
    virtual std::string Name() const = 0;
    bool IsStructureType() const { return kind == TypeKind::structureType; }
    StructureType* GetStructurePointeeType(const SourcePos& sourcePos, Context* context) const;
    ArrayType* GetArrayPointeeType(const SourcePos& sourcePos, Context* context) const;
    bool IsArrayType() const { return kind == TypeKind::arrayType; }
    bool IsFunctionType() const { return kind == TypeKind::functionType; }
    bool IsFunctionPtrType() const;
    bool IsBytePtrType() const;
    virtual Type* BaseType() const { return const_cast<Type*>(this); }
    virtual bool IsWeakType() const { return true; }
    virtual void Add(Types* types, Context* context);
    virtual void Resolve(Types* types, Context* context);
    const SourcePos& GetSourcePos() const { return sourcePos; }
    std::int32_t Id() const { return id; }
    TypeRef GetTypeRef();
    virtual void WriteDeclaration(util::CodeFormatter& formatter);
    Value* DefaultValue() { return defaultValue; }
    void SetDefaultValue(Value* defaultValue_);
    virtual Value* MakeDefaultValue(Context& context) const { return nullptr; }
private:
    Value* defaultValue;
    SourcePos sourcePos;
    TypeKind kind;
    std::int32_t id;
};

class VoidType : public Type
{
public:
    VoidType();
    std::string Name() const override { return "void"; }
    std::int64_t Size() const override { return -1; }
    std::int64_t Alignment() const override { return -1; }
};

class BoolType : public Type
{
public:
    BoolType();
    std::string Name() const override { return "bool"; }
    std::int64_t Size() const override { return 1; }
    std::int64_t Alignment() const override { return 1; }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DB; }
    Value* MakeDefaultValue(Context& context) const override;
};

class SByteType : public Type
{
public:
    SByteType();
    std::string Name() const override { return "sbyte"; }
    std::int64_t Size() const override { return 1; }
    std::int64_t Alignment() const override { return 1; }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DB; }
    Value* MakeDefaultValue(Context& context) const override;
};

class ByteType : public Type
{
public:
    ByteType();
    std::string Name() const override { return "byte"; }
    std::int64_t Size() const override { return 1; }
    std::int64_t Alignment() const override { return 1; }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DB; }
    Value* MakeDefaultValue(Context& context) const override;
};

class ShortType : public Type
{
public:
    ShortType();
    std::string Name() const override { return "short"; }
    std::int64_t Size() const override { return 2; }
    std::int64_t Alignment() const override { return 2; }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DW; }
    Value* MakeDefaultValue(Context& context) const override;
};

class UShortType : public Type
{
public:
    UShortType();
    std::string Name() const override { return "ushort"; }
    std::int64_t Size() const override { return 2; }
    std::int64_t Alignment() const override { return 2; }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DW; }
    Value* MakeDefaultValue(Context& context) const override;
};

class IntType : public Type
{
public:
    IntType();
    std::string Name() const override { return "int"; }
    std::int64_t Size() const override { return 4; }
    std::int64_t Alignment() const override { return 4; }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DD; }
    Value* MakeDefaultValue(Context& context) const override;
};

class UIntType : public Type
{
public:
    UIntType();
    std::string Name() const override { return "uint"; }
    std::int64_t Size() const override { return 4; }
    std::int64_t Alignment() const override { return 4; }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DD; }
    Value* MakeDefaultValue(Context& context) const override;
};

class LongType : public Type
{
public:
    LongType();
    std::string Name() const override { return "long"; }
    std::int64_t Size() const override { return 8; }
    std::int64_t Alignment() const override { return 8; }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DQ; }
    Value* MakeDefaultValue(Context& context) const override;
};

class ULongType : public Type
{
public:
    ULongType();
    std::string Name() const override { return "ulong"; }
    std::int64_t Size() const override { return 8; }
    std::int64_t Alignment() const override { return 8; }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DQ; }
    Value* MakeDefaultValue(Context& context) const override;
};

class FloatType : public Type
{
public:
    FloatType();
    std::string Name() const override { return "float"; }
    std::int64_t Size() const override { return 4; }
    std::int64_t Alignment() const override { return 4; }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DD; }
    Value* MakeDefaultValue(Context& context) const override;
};

class DoubleType : public Type
{
public:
    DoubleType();
    std::string Name() const override { return "double"; }
    std::int64_t Size() const override { return 8; }
    std::int64_t Alignment() const override { return 8; }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DQ; }
    Value* MakeDefaultValue(Context& context) const override;
};

class TypeRef
{
public:
    TypeRef();
    TypeRef(const SourcePos& sourcePos_, std::int32_t id_);
    const SourcePos& GetSourcePos() const { return sourcePos; }
    std::int32_t Id() const { return id; }
    void SetType(Type* type_) { type = type_; }
    Type* GetType() const { return type; }
    void Write(util::CodeFormatter& formatter);
private:
    SourcePos sourcePos;
    std::int32_t id;
    Type* type;
};

bool operator<(const TypeRef& left, const TypeRef& right);

inline TypeRef MakeTypeRef(const SourcePos& sourcePos, std::int32_t baseTypeId, std::int32_t pointerCount)
{
    return TypeRef(sourcePos, MakeTypeId(baseTypeId, pointerCount));
}

class StructureType : public Type
{
public:
    StructureType(const SourcePos& sourcePos_, std::int32_t typeId_, const std::vector<TypeRef>& fieldTypeRefs_);
    void Accept(Visitor& visitor) override;
    void Add(Types* types, Context* context) override;
    void Resolve(Types* types, Context* context) override;
    std::int64_t Size() const override;
    std::int64_t Alignment() const override { return 8; }
    std::string Name() const override { return "$T" + std::to_string(MakeUserTypeId(Id())); }
    bool IsWeakType() const override;
    int FieldCount() const { return fieldTypeRefs.size(); }
    const std::vector<TypeRef>& FieldTypeRefs() const { return fieldTypeRefs; }
    Type* FieldType(int i) const { return fieldTypeRefs[i].GetType(); }
    std::int64_t GetFieldOffset(std::int64_t index) const;
    void WriteDeclaration(util::CodeFormatter& formatter) override;
    void ReplaceForwardReference(FwdDeclaredStructureType* fwdDeclaredType, StructureType* structureType, Context* context) override;
    Value* MakeDefaultValue(Context& context) const override;
private:
    void ComputeSizeAndOffsets() const;
    std::vector<TypeRef> fieldTypeRefs;
    mutable bool sizeAndOffsetsComputed;
    mutable std::int64_t size;
    mutable std::vector<std::int64_t> fieldOffsets;
};

class FwdDeclaredStructureType : public Type
{
public:
    FwdDeclaredStructureType(const util::uuid& id_, std::int32_t typeId_);
    void Accept(Visitor& visitor) override;
    std::int64_t Size() const override { return -1; }
    std::int64_t Alignment() const override { return -1; }
    std::string Name() const override { return "FWD_DECLARED_STRUCTURE_TYPE"; }
    const util::uuid& Id() const { return id; }
private:
    util::uuid id;
};

class ArrayType : public Type
{
public:
    ArrayType(const SourcePos& sourcePos_, std::int32_t typeId_, std::int64_t elementCount_, const TypeRef& elementTypeRef_);
    void Accept(Visitor& visitor) override;
    void Add(Types* types, Context* context) override;
    void Resolve(Types* types, Context* context) override;
    std::int64_t Size() const override;
    std::int64_t Alignment() const override { return 8; }
    otava::assembly::DataInst DataInstruction() const override;
    std::string Name() const override { return "$T" + std::to_string(MakeUserTypeId(Id())); }
    bool IsWeakType() const override;
    std::int64_t ElementCount() const { return elementCount; }
    const TypeRef& ElementTypeRef() const { return elementTypeRef; }
    Type* ElementType() const { return elementTypeRef.GetType(); }
    void WriteDeclaration(util::CodeFormatter& formatter) override;
    Value* MakeDefaultValue(Context& context) const override;
private:
    std::int64_t elementCount;
    TypeRef elementTypeRef;
};

class FunctionType : public Type
{
public:
    FunctionType(const SourcePos& sourcePos_, std::int32_t typeId_, const TypeRef& returnTypeRef_, const std::vector<TypeRef>& paramTypeRefs_);
    void Accept(Visitor& visitor) override;
    void Add(Types* types, Context* context) override;
    void Resolve(Types* types, Context* context) override;
    bool IsWeakType() const override;
    int Arity() const { return paramTypeRefs.size(); }
    std::int64_t Size() const override { return 8; }
    std::int64_t Alignment() const override { return 8; }
    std::string Name() const override { return "$T" + std::to_string(MakeUserTypeId(Id())); }
    const TypeRef& ReturnTypeRef() const { return returnTypeRef; }
    Type* ReturnType() const { return returnTypeRef.GetType(); }
    const std::vector<TypeRef>& ParamTypeRefs() const { return paramTypeRefs; }
    Type* ParamType(int index) const { return paramTypeRefs[index].GetType(); }
    void WriteDeclaration(util::CodeFormatter& formatter) override;
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DQ; }
private:
    TypeRef returnTypeRef;
    std::vector<TypeRef> paramTypeRefs;
};

class PointerType : public Type
{
public:
    PointerType(const SourcePos& sourcePos_, std::int32_t typeId_, std::int8_t pointerCount_, std::int32_t baseTypeId_);
    std::string Name() const override;
    std::int64_t Size() const override { return 8; }
    std::int64_t Alignment() const override { return 8; }
    std::int8_t PointerCount() const { return pointerCount; }
    const TypeRef& BaseTypeRef() const { return baseTypeRef; }
    TypeRef& BaseTypeRef() { return baseTypeRef; }
    Type* BaseType() const override { return baseTypeRef.GetType(); }
    otava::assembly::DataInst DataInstruction() const override { return otava::assembly::DataInst::DQ; }
    void ReplaceForwardReference(FwdDeclaredStructureType* fwdDeclaredType, StructureType* structureType, Context* context) override;
    Value* MakeDefaultValue(Context& context) const override;
private:
    std::int8_t pointerCount;
    TypeRef baseTypeRef;
};

Type* GetElemType(Value* ptr, Value* index, const SourcePos& sourcePos, Context* context);

class Types
{
public:
    Types();
    void Init();
    void Write(util::CodeFormatter& formatter);
    Context* GetContext() const { return context; }
    void SetContext(Context* context_) { context = context_; }
    StructureType* GetStructureType(const SourcePos& sourcePos, std::int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs);
    ArrayType* GetArrayType(const SourcePos& sourcePos, std::int32_t typeId, std::int64_t size, const TypeRef& elementTypeRef);
    FunctionType* GetFunctionType(const SourcePos& sourcePos, std::int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs);
    FwdDeclaredStructureType* GetFwdDeclaredStructureType(const util::uuid& id);
    FwdDeclaredStructureType* MakeFwdDeclaredStructureType(const util::uuid& id, std::int32_t typeId);
    void AddFwdDependentType(FwdDeclaredStructureType* fwdType, Type* type);
    void ResolveForwardReferences(const util::uuid& id, StructureType* structureType);
    void Resolve(Context* context);
    void ResolveType(TypeRef& typeRef, Context* context);
    void Add(Type* type, Context* context);
    Type* Get(std::int32_t id) const;
    void Map(Type* type);
    void VisitTypeDeclarations(Visitor& visitor);
    VoidType* GetVoidType() const { return const_cast<VoidType*>(&voidType); }
    BoolType* GetBoolType() const { return const_cast<BoolType*>(&boolType); }
    SByteType* GetSByteType() const { return const_cast<SByteType*>(&sbyteType); }
    ByteType* GetByteType() const { return const_cast<ByteType*>(&byteType); }
    ShortType* GetShortType() const { return const_cast<ShortType*>(&shortType); }
    UShortType* GetUShortType() const { return const_cast<UShortType*>(&ushortType); }
    IntType* GetIntType() const { return const_cast<IntType*>(&intType); }
    UIntType* GetUIntType() const { return const_cast<UIntType*>(&uintType); }
    LongType* GetLongType() const { return const_cast<LongType*>(&longType); }
    ULongType* GetULongType() const { return const_cast<ULongType*>(&ulongType); }
    FloatType* GetFloatType() const { return const_cast<FloatType*>(&floatType); }
    DoubleType* GetDoubleType() const { return const_cast<DoubleType*>(&doubleType); }
    PointerType* MakePointerType(const SourcePos& sourcePos, std::int32_t baseTypeId, std::int8_t pointerCount, Context* context);
    std::int32_t NextTypeId() { return nextTypeId++; }
private:
    Type* GetFundamentalType(std::int32_t id) const;
    Context* context;
    std::vector<std::unique_ptr<Type>> types;
    std::vector<Type*> declaredTypes;
    std::map<std::int32_t, Type*> typeMap;
    std::map<std::pair<std::int32_t, std::int8_t>, PointerType*> pointerTypeMap;
    std::map<std::vector<std::int32_t>, StructureType*> structureTypeMap;
    std::map<std::pair<std::int64_t, std::int32_t>, ArrayType*> arrayTypeMap;
    std::map<std::pair<std::int32_t, std::vector<std::int32_t>>, FunctionType*> functionTypeMap;
    std::map<util::uuid, FwdDeclaredStructureType*> fwdDeclaredStructureTypes;
    std::map<util::uuid, std::vector<Type*>> fwdDeclarationMap;
    VoidType voidType;
    BoolType boolType;
    SByteType sbyteType;
    ByteType byteType;
    ShortType shortType;
    UShortType ushortType;
    IntType intType;
    UIntType uintType;
    LongType longType;
    ULongType ulongType;
    FloatType floatType;
    DoubleType doubleType;
    std::int32_t nextTypeId;
};

} // otava::intermediate
