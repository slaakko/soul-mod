// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.types;

import otava.intermediate.error;
import otava.assembly;
import soul.ast.span;
import util;
import std;

export namespace otava::intermediate {

class Value;
class Context;
class Types;
class TypeRef;
class Visitor;
class ArrayType;
class StructureType;
class FwdDeclaredStructureType;
class MetadataRef;

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
const std::int32_t pointerTypeId = static_cast<std::int32_t>(1) << 31;

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
        return MakePointerTypeId(baseTypeId, static_cast<std::int8_t>(pointerCount));
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
    fundamentalType, structureType, fwdDeclaredStructureType, arrayType, functionType, pointerType
};

class Type
{
public:
    Type(const soul::ast::Span& span_, TypeKind kind_, std::int32_t id_);
    virtual ~Type();
    virtual void Accept(Visitor& visitor) {}
    virtual std::int64_t Size() const = 0;
    virtual std::int64_t Alignment() const = 0;
    virtual otava::assembly::OpCode DataOpCode() const { return otava::assembly::OpCode::DB; }
    inline TypeKind Kind() const { return kind; }
    inline bool IsFundamentalType() const { return kind == TypeKind::fundamentalType; }
    inline bool IsVoidType() const { return id == voidTypeId; }
    inline bool IsBooleanType() const { return id == boolTypeId; }
    inline bool IsLongType() const { return id == longTypeId; }
    inline bool IsCompoundType() const { return !IsFundamentalType(); }
    inline bool IsArithmeticType() const { return IsIntegerType() || IsFloatingPointType(); }
    bool IsIntegerType() const;
    bool IsUnsignedType() const;
    bool IsSignedType() const;
    bool IsFloatingPointType() const;
    inline bool IsFloatType() const { return id == floatTypeId; }
    inline bool IsDoubleType() const { return id == doubleTypeId; }
    inline bool IsPointerType() const { return kind == TypeKind::pointerType; }
    std::expected<Type*, int> AddPointer(Context* context) const;
    std::expected<Type*, int> RemovePointer(const soul::ast::Span& span, Context* context) const;
    inline bool IsFwdDeclaredStructureType() const { return kind == TypeKind::fwdDeclaredStructureType; }
    virtual void ReplaceForwardReference(FwdDeclaredStructureType* fwdDeclaredType, StructureType* structureType, Context* context);
    inline std::int32_t NextTypeId() { return nextTypeId++; }
    virtual std::string Name() const = 0;
    inline bool IsStructureType() const { return kind == TypeKind::structureType; }
    std::expected<StructureType*, int> GetStructurePointeeType(const soul::ast::Span& span, Context* context) const;
    std::expected<ArrayType*, int> GetArrayPointeeType(const soul::ast::Span& span, Context* context) const;
    inline bool IsArrayType() const { return kind == TypeKind::arrayType; }
    inline bool IsFunctionType() const { return kind == TypeKind::functionType; }
    bool IsFunctionPtrType() const;
    virtual bool IsWeakType() const { return true; }
    virtual std::expected<bool, int> Add(Types* types, Context* context);
    virtual std::expected<bool, int> Resolve(Types* types, Context* context);
    inline const soul::ast::Span& Span() const { return span; }
    inline std::int32_t Id() const { return id; }
    void Write(util::CodeFormatter& formatter);
    virtual void WriteDeclaration(util::CodeFormatter& formatter);
    inline Value* DefaultValue() { return defaultValue; }
    inline void SetDefaultValue(Value* defaultValue_) { defaultValue = defaultValue_; }
    virtual Value* MakeDefaultValue(Context& context) const { return nullptr; }
    TypeRef GetTypeRef();
    virtual Type* BaseType() const { return const_cast<Type*>(this); }
    virtual void IncCount();
private:
    soul::ast::Span span;
    TypeKind kind;
    std::int32_t id;
    Value* defaultValue;
    std::int32_t nextTypeId;
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
    Value* MakeDefaultValue(Context& context) const override;
};

class SByteType : public Type
{
public:
    SByteType();
    std::string Name() const override { return "sbyte"; }
    std::int64_t Size() const override { return 1; }
    std::int64_t Alignment() const override { return 1; }
    Value* MakeDefaultValue(Context& context) const override;
};

class ByteType : public Type
{
public:
    ByteType();
    std::string Name() const override { return "byte"; }
    std::int64_t Size() const override { return 1; }
    std::int64_t Alignment() const override { return 1; }
    Value* MakeDefaultValue(Context& context) const override;
};

class ShortType : public Type
{
public:
    ShortType();
    std::string Name() const override { return "short"; }
    std::int64_t Size() const override { return 2; }
    std::int64_t Alignment() const override { return 2; }
    otava::assembly::OpCode DataOpCode() const override { return otava::assembly::OpCode::DW; }
    Value* MakeDefaultValue(Context& context) const override;
};

class UShortType : public Type
{
public:
    UShortType();
    std::string Name() const override { return "ushort"; }
    std::int64_t Size() const override { return 2; }
    std::int64_t Alignment() const override { return 2; }
    otava::assembly::OpCode DataOpCode() const override { return otava::assembly::OpCode::DW; }
    Value* MakeDefaultValue(Context& context) const override;
};

class IntType : public Type
{
public:
    IntType();
    std::string Name() const override { return "int"; }
    std::int64_t Size() const override { return 4; }
    std::int64_t Alignment() const override { return 4; }
    otava::assembly::OpCode DataOpCode() const override { return otava::assembly::OpCode::DD; }
    Value* MakeDefaultValue(Context& context) const override;
};

class UIntType : public Type
{
public:
    UIntType();
    std::string Name() const override { return "uint"; }
    std::int64_t Size() const override { return 4; }
    std::int64_t Alignment() const override { return 4; }
    otava::assembly::OpCode DataOpCode() const override { return otava::assembly::OpCode::DD; }
    Value* MakeDefaultValue(Context& context) const override;
};

class LongType : public Type
{
public:
    LongType();
    std::string Name() const override { return "long"; }
    std::int64_t Size() const override { return 8; }
    std::int64_t Alignment() const override { return 8; }
    otava::assembly::OpCode DataOpCode() const override { return otava::assembly::OpCode::DQ; }
    Value* MakeDefaultValue(Context& context) const override;
};

class ULongType : public Type
{
public:
    ULongType();
    std::string Name() const override { return "ulong"; }
    std::int64_t Size() const override { return 8; }
    std::int64_t Alignment() const override { return 8; }
    otava::assembly::OpCode DataOpCode() const override { return otava::assembly::OpCode::DQ; }
    Value* MakeDefaultValue(Context& context) const override;
};

class FloatType : public Type
{
public:
    FloatType();
    std::string Name() const override { return "float"; }
    std::int64_t Size() const override { return 4; }
    std::int64_t Alignment() const override { return 4; }
    otava::assembly::OpCode DataOpCode() const override { return otava::assembly::OpCode::REAL4; }
    Value* MakeDefaultValue(Context& context) const override;
};

class DoubleType : public Type
{
public:
    DoubleType();
    std::string Name() const override { return "double"; }
    std::int64_t Size() const override { return 8; }
    std::int64_t Alignment() const override { return 8; }
    otava::assembly::OpCode DataOpCode() const override { return otava::assembly::OpCode::REAL8; }
    Value* MakeDefaultValue(Context& context) const override;
};

class TypeRef
{
public:
    TypeRef();
    TypeRef(const soul::ast::Span& span_, std::int32_t id_);
    inline const soul::ast::Span& Span() const { return span; }
    inline std::int32_t Id() const { return id; }
    inline void SetType(Type* type_) { type = type_; }
    inline Type* GetType() const { return type; }
private:
    soul::ast::Span span;
    std::int32_t id;
    Type* type;
};

inline TypeRef MakeTypeRef(const soul::ast::Span& span, std::int32_t baseTypeId, std::int32_t pointerCount)
{
    return TypeRef(span, MakeTypeId(baseTypeId, pointerCount));
}

class StructureType : public Type
{
public:
    StructureType(const soul::ast::Span& span_, std::int32_t typeId_, const std::vector<TypeRef>& fieldTypeRefs_);
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Add(Types* types, Context* context) override;
    std::expected<bool, int> Resolve(Types* types, Context* context) override;
    std::int64_t Size() const override;
    std::int64_t Alignment() const override { return 8; }
    std::string Name() const override { return "$T" + std::to_string(Id() - userTypeId); }
    bool IsWeakType() const override;
    inline int FieldCount() const { return fieldTypeRefs.size(); }
    inline const std::vector<TypeRef>& FieldTypeRefs() const { return fieldTypeRefs; }
    Type* FieldType(int i) const;
    std::int64_t GetFieldOffset(std::int64_t index) const;
    void WriteDeclaration(util::CodeFormatter& formatter) override;
    std::expected<bool, int> ReplaceForwardReference(FwdDeclaredStructureType* fwdDeclaredType, StructureType* structureType, Context* context) override;
    Value* MakeDefaultValue(Context& context) const override;
    inline const std::string& Comment() const { return comment; }
    void SetComment(const std::string& comment_);
    inline void SetMetadataRef(MetadataRef* metadataRef_) { metadataRef = metadataRef_; }
    inline MetadataRef* GetMetadataRef() const { return metadataRef; }
    void ResolveComment();
private:
    void ComputeSizeAndOffsets() const;
    std::vector<TypeRef> fieldTypeRefs;
    mutable bool sizeAndOffsetsComputed;
    mutable std::int64_t size;
    mutable std::vector<std::int64_t> fieldOffsets;
    MetadataRef* metadataRef;
    std::string comment;
};

class FwdDeclaredStructureType : public Type
{
public:
    FwdDeclaredStructureType(const util::uuid& id_, std::int32_t typeId_);
    void Accept(Visitor& visitor) override;
    std::int64_t Size() const override { return -1; }
    std::int64_t Alignment() const override { return -1; }
    std::string Name() const override { return "FWD_DECLARED_STRUCTURE_TYPE"; }
    inline const util::uuid& Id() const { return id; }
    inline const std::string& Comment() const { return comment; }
    void SetComment(const std::string& comment_);
private:
    util::uuid id;
    std::string comment;
};

class ArrayType : public Type
{
public:
    ArrayType(const soul::ast::Span& span_, std::int32_t typeId_, std::int64_t elementCount_, const TypeRef& elementTypeRef_);
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Add(Types* types, Context* context) override;
    std::expected<bool, int> Resolve(Types* types, Context* context) override;
    std::int64_t Size() const override;
    std::int64_t Alignment() const override { return 8; }
    std::string Name() const override { return "$T" + std::to_string(Id() - userTypeId); }
    bool IsWeakType() const override;
    inline std::int64_t ElementCount() const { return elementCount; }
    inline const TypeRef& ElementTypeRef() const { return elementTypeRef; }
    inline Type* ElementType() const { return elementTypeRef.GetType(); }
    void WriteDeclaration(util::CodeFormatter& formatter) override;
    Value* MakeDefaultValue(Context& context) const override;
private:
    std::int64_t elementCount;
    TypeRef elementTypeRef;
};

class FunctionType : public Type
{
public:
    FunctionType(const soul::ast::Span& span_, std::int32_t typeId_, const TypeRef& returnTypeRef_, const std::vector<TypeRef>& paramTypeRefs_);
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Add(Types* types, Context* context) override;
    std::expected<bool, int> Resolve(Types* types, Context* context) override;
    bool IsWeakType() const override;
    inline int Arity() const { return paramTypeRefs.size(); }
    std::int64_t Size() const override { return 8; }
    std::int64_t Alignment() const override { return 8; }
    std::string Name() const override { return "$T" + std::to_string(Id() - userTypeId); }
    inline const TypeRef& ReturnTypeRef() const { return returnTypeRef; }
    inline Type* ReturnType() const { return returnTypeRef.GetType(); }
    inline const std::vector<TypeRef>& ParamTypeRefs() const { return paramTypeRefs; }
    inline Type* ParamType(int index) const { return paramTypeRefs[index].GetType(); }
    void WriteDeclaration(util::CodeFormatter& formatter) override;
    bool IsUnaryOperationType() const;
private:
    TypeRef returnTypeRef;
    std::vector<TypeRef> paramTypeRefs;
};

class PointerType : public Type
{
public:
    PointerType(const soul::ast::Span& span_, std::int32_t typeId_, std::int8_t pointerCount_, std::int32_t baseTypeId_);
    std::string Name() const override;
    std::int64_t Size() const override { return 8; }
    std::int64_t Alignment() const override { return 8; }
    inline std::int8_t PointerCount() const { return pointerCount; }
    inline const TypeRef& BaseTypeRef() const { return baseTypeRef; }
    inline TypeRef& BaseTypeRef() { return baseTypeRef; }
    inline Type* BaseType() const override { return baseTypeRef.GetType(); }
    Value* MakeDefaultValue(Context& context) const override;
    void ReplaceForwardReference(FwdDeclaredStructureType* fwdDeclaredType, StructureType* structureType, Context* context) override;
private:
    std::int8_t pointerCount;
    TypeRef baseTypeRef;
};

std::expected<Type*, int> GetElemType(Value* ptr, Value* index, const soul::ast::Span& span, Context* context);

class Types
{
public:
    Types();
    Types(const Types&) = delete;
    void Init();
    Types& operator=(const Types&) = delete;
    inline Context* GetContext() const { return context; }
    inline void SetContext(Context* context_) { context = context_; }
    void AddStructureType(const soul::ast::Span& span, std::int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs, MetadataRef* mdRef);
    void AddArrayType(const soul::ast::Span& span, std::int32_t typeId, std::int64_t size, const TypeRef& elementTypeRef);
    void AddFunctionType(const soul::ast::Span& span, std::int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs);
    void Resolve(Context* context);
    std::expected<bool, int> ResolveType(TypeRef& typeRef, Context* context);
    std::expected<bool, int> Add(Type* type, Context* context);
    Type* Get(std::int32_t id) const;
    void Map(Type* type);
    void VisitTypeDeclarations(Visitor& visitor);
    inline VoidType* GetVoidType() const { return const_cast<VoidType*>(&voidType); }
    inline BoolType* GetBoolType() const { return const_cast<BoolType*>(&boolType); }
    inline SByteType* GetSByteType() const { return const_cast<SByteType*>(&sbyteType); }
    inline ByteType* GetByteType() const { return const_cast<ByteType*>(&byteType); }
    inline ShortType* GetShortType() const { return const_cast<ShortType*>(&shortType); }
    inline UShortType* GetUShortType() const { return const_cast<UShortType*>(&ushortType); }
    inline IntType* GetIntType() const { return const_cast<IntType*>(&intType); }
    inline UIntType* GetUIntType() const { return const_cast<UIntType*>(&uintType); }
    inline LongType* GetLongType() const { return const_cast<LongType*>(&longType); }
    inline ULongType* GetULongType() const { return const_cast<ULongType*>(&ulongType); }
    inline FloatType* GetFloatType() const { return const_cast<FloatType*>(&floatType); }
    inline DoubleType* GetDoubleType() const { return const_cast<DoubleType*>(&doubleType); }
    std::expected<PointerType*, int> MakePointerType(const soul::ast::Span& span, std::int32_t baseTypeId, std::int8_t pointerCount, Context* context);
    std::expected<Type*, int> MakePtrType(Type* baseType);
    StructureType* GetStructureType(const soul::ast::Span& span, std::int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs);
    ArrayType* GetArrayType(const soul::ast::Span& span, std::int32_t typeId, std::int64_t size, const TypeRef& elementTypeRef);
    FunctionType* GetFunctionType(const soul::ast::Span& span, std::int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs);
    FwdDeclaredStructureType* GetFwdDeclaredStructureType(const util::uuid& id);
    FwdDeclaredStructureType* MakeFwdDeclaredStructureType(const util::uuid& id, std::int32_t typeId, const std::string& comment);
    void AddFwdDependentType(FwdDeclaredStructureType* fwdType, Type* type);
    void ResolveForwardReferences(const util::uuid& id, StructureType* structureType);
    void ResolveComments();
    inline std::int32_t NextTypeId() { return nextTypeId++; }
    void Write(util::CodeFormatter& formatter);
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
    int32_t nextTypeId;
};

} // otava::intermediate
