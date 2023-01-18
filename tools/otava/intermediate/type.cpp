// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.type;

import otava.intermediate.context;
import otava.intermediate.error;
import otava.intermediate.visitor;
import otava.intermediate.value;
import otava.intermediate.data;
import util;

namespace otava::intermediate {

Type::Type(const SourcePos& sourcePos_, TypeKind kind_, int32_t id_) : sourcePos(sourcePos_), kind(kind_), id(id_), defaultValue(nullptr)
{
}

Type::~Type()
{
}

bool Type::IsBytePtrType() const
{
    if (IsPointerType())
    {
        const PointerType* pointerType = static_cast<const PointerType*>(this);
        if (pointerType->PointerCount() == 1 && pointerType->BaseType()->IsByteType())
        {
            return true;
        }
    }
    return false;
}

bool Type::IsFunctionPtrType() const
{
    if (IsPointerType())
    {
        const PointerType* pointerType = static_cast<const PointerType*>(this);
        if (pointerType->PointerCount() == 1 && pointerType->BaseType()->IsFunctionType())
        {
            return true;
        }
    }
    return false;
}

bool Type::IsIntegerType() const
{
    switch (id)
    {
        case sbyteTypeId:
        case byteTypeId:
        case shortTypeId:
        case ushortTypeId:
        case intTypeId:
        case uintTypeId:
        case longTypeId:
        case ulongTypeId:
        {
            return true;
        }
        default:
        {
            return false;
        }
    }
}

bool Type::IsUnsignedType() const
{
    switch (id)
    {
        case byteTypeId:
        case ushortTypeId:
        case uintTypeId:
        case ulongTypeId:
        {
            return true;
        }
        default:
        {
            return false;
        }
    }
}

bool Type::IsFloatingPointType() const
{
    switch (id)
    {
        case floatTypeId:
        case doubleTypeId:
        {
            return true;
        }
        default:
        {
            return false;
        }
    }
}

bool Type::IsAggregateType() const
{
    switch (kind)
    {
        case TypeKind::structureType:
        case TypeKind::arrayType:
        case TypeKind::functionType:
        {
            return true;
        }
    }
    return false;
}

void Type::ReplaceForwardReference(FwdDeclaredStructureType* fwdDeclaredType, StructureType* structureType, Context* context)
{
}

Type* Type::AddPointer(Context* context) const
{
    if (IsPointerType())
    {
        const PointerType* pointerType = static_cast<const PointerType*>(this);
        return context->GetTypes().MakePointerType(GetSourcePos(), GetBaseTypeId(pointerType->Id()), GetPointerCount(pointerType->Id()) + 1, context);
    }
    else
    {
        return context->GetTypes().MakePointerType(GetSourcePos(), Id(), 1, context);
    }
}

Type* Type::RemovePointer(const SourcePos& sourcePos, Context* context) const
{
    if (IsPointerType())
    {
        const PointerType* pointerType = static_cast<const PointerType*>(this);
        return pointerType->BaseType();
    }
    else
    {
        Error("pointer type expected", sourcePos, context);
    }
    return nullptr;
}

StructureType* Type::GetStructurePointeeType(const SourcePos& sourcePos, Context* context) const
{
    Type* pointeeType = RemovePointer(sourcePos, context);
    if (pointeeType)
    {
        if (pointeeType->IsStructureType())
        {
            return static_cast<StructureType*>(pointeeType);
        }
        else
        {
            Error("structure type expected", sourcePos, context);
        }
    }
    else
    {
        Error("pointer type expected", sourcePos, context);
    }
    return nullptr;
}

ArrayType* Type::GetArrayPointeeType(const SourcePos& sourcePos, Context* context) const
{
    Type* pointeeType = RemovePointer(sourcePos, context);
    if (pointeeType)
    {
        if (pointeeType->IsArrayType())
        {
            return static_cast<ArrayType*>(pointeeType);
        }
        else
        {
            Error("array type expected", sourcePos, context);
        }
    }
    else
    {
        Error("pointer type expected", sourcePos, context);
    }
    return nullptr;
}

void Type::Add(Types* types, Context* context)
{
}

void Type::Resolve(Types* types, Context* context)
{
}

TypeRef Type::GetTypeRef() 
{
    TypeRef typeRef = MakeTypeRef(SourcePos(), id, GetPointerCount(id));
    typeRef.SetType(this);
    return typeRef;
}

void Type::WriteDeclaration(util::CodeFormatter& formatter)
{
    formatter.Write(Name());
    formatter.Write(" = type ");
}

void Type::SetDefaultValue(Value* defaultValue_)
{
    defaultValue = defaultValue_;
}

VoidType::VoidType() : Type(SourcePos(), TypeKind::fundamentalType, voidTypeId)
{
}

BoolType::BoolType() : Type(SourcePos(), TypeKind::fundamentalType, boolTypeId)
{
}

Value* BoolType::MakeDefaultValue(Context& context) const
{
    return context.GetFalseValue();
}

SByteType::SByteType() : Type(SourcePos(), TypeKind::fundamentalType, sbyteTypeId)
{
}

Value* SByteType::MakeDefaultValue(Context& context) const
{
    return context.GetSByteValue(0);
}

ByteType::ByteType() : Type(SourcePos(), TypeKind::fundamentalType, byteTypeId)
{
}

Value* ByteType::MakeDefaultValue(Context& context) const
{
    return context.GetByteValue(0);
}

ShortType::ShortType() : Type(SourcePos(), TypeKind::fundamentalType, shortTypeId)
{
}

Value* ShortType::MakeDefaultValue(Context& context) const
{
    return context.GetShortValue(0);
}

UShortType::UShortType() : Type(SourcePos(), TypeKind::fundamentalType, ushortTypeId)
{
}

Value* UShortType::MakeDefaultValue(Context& context) const
{
    return context.GetUShortValue(0);
}

IntType::IntType() : Type(SourcePos(), TypeKind::fundamentalType, intTypeId)
{
}

Value* IntType::MakeDefaultValue(Context& context) const
{
    return context.GetIntValue(0);
}

UIntType::UIntType() : Type(SourcePos(), TypeKind::fundamentalType, uintTypeId)
{
}

Value* UIntType::MakeDefaultValue(Context& context) const
{
    return context.GetUIntValue(0);
}

LongType::LongType() : Type(SourcePos(), TypeKind::fundamentalType, longTypeId)
{
}

Value* LongType::MakeDefaultValue(Context& context) const
{
    return context.GetLongValue(0);
}

ULongType::ULongType() : Type(SourcePos(), TypeKind::fundamentalType, ulongTypeId)
{
}

Value* ULongType::MakeDefaultValue(Context& context) const
{
    return context.GetULongValue(0);
}

FloatType::FloatType() : Type(SourcePos(), TypeKind::fundamentalType, floatTypeId)
{
}

Value* FloatType::MakeDefaultValue(Context& context) const
{
    return context.GetFloatValue(0.0f);
}

DoubleType::DoubleType() : Type(SourcePos(), TypeKind::fundamentalType, doubleTypeId)
{
}

Value* DoubleType::MakeDefaultValue(Context& context) const
{
    return context.GetDoubleValue(0.0);
}

TypeRef::TypeRef() : sourcePos(), id(-1), type(nullptr)
{
}

TypeRef::TypeRef(const SourcePos& sourcePos_, int32_t id_) : sourcePos(sourcePos_), id(id_), type(nullptr)
{
}

void TypeRef::Write(util::CodeFormatter& formatter)
{
    formatter.Write(type->Name());
}

bool operator<(const TypeRef& left, const TypeRef& right)
{
    return left.GetType() < right.GetType();
}

StructureType::StructureType(const SourcePos& sourcePos_, int32_t typeId_, const std::vector<TypeRef>& fieldTypeRefs_) :
    Type(sourcePos_, TypeKind::structureType, typeId_), fieldTypeRefs(fieldTypeRefs_), sizeAndOffsetsComputed(false), size()
{
}

void StructureType::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void StructureType::Add(Types* types, Context* context)
{
    types->Add(this, context);
}

void StructureType::Resolve(Types* types, Context* context)
{
    for (auto& typeRef : fieldTypeRefs)
    {
        types->ResolveType(typeRef, context);
    }
}

bool StructureType::IsWeakType() const
{
    int n = FieldCount();
    for (int i = 0; i < n; ++i)
    {
        Type* type = FieldType(i);
        if (type->IsStructureType() || type->IsArrayType() || type->IsFunctionType())
        {
            return false;
        }
    }
    return true;
}

int64_t StructureType::Size() const
{
    if (!sizeAndOffsetsComputed)
    {
        ComputeSizeAndOffsets();
    }
    return size;
}

void StructureType::ComputeSizeAndOffsets() const
{
    int64_t offset = 0;
    int n = FieldCount();
    for (int i = 0; i < n; ++i)
    {
        Type* fieldType = FieldType(i);
        int64_t memberOffset = offset;
        if (i > 0)
        {
            int64_t alignment = fieldType->Alignment();
            if (!(offset > 0))
            {
                throw std::runtime_error("structure type: invalid offset");
            }
            memberOffset = alignment * ((offset - 1) / alignment + 1);
        }
        fieldOffsets.push_back(memberOffset);
        offset = memberOffset + fieldType->Size();
    }
    if (n == 0)
    {
        size = 8;
    }
    else
    {
        size = 8 * ((offset - 1) / 8 + 1);
    }
    sizeAndOffsetsComputed = true;
}

int64_t StructureType::GetFieldOffset(int64_t index) const
{
    if (!sizeAndOffsetsComputed)
    {
        ComputeSizeAndOffsets();
    }
    return fieldOffsets[index];
}

void StructureType::WriteDeclaration(util::CodeFormatter& formatter)
{
    Type::WriteDeclaration(formatter);
    formatter.Write("{ ");
    bool first = true;
    for (auto& fieldTypeRef : fieldTypeRefs)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter.Write(", ");
        }
        fieldTypeRef.Write(formatter);
    }
    formatter.Write(" }");
}

void StructureType::ResolveForwardReferences(const util::uuid& uuid, Context* context)
{
    FwdDeclaredStructureType* fwdDeclaredType = context->GetFwdDeclaredStructureType(uuid, -1);
    int n = FieldCount();
    for (int i = 0; i < n; ++i)
    {
        Type* fieldType = FieldType(i);
        fieldType->ReplaceForwardReference(fwdDeclaredType, this, context);
    }
}

Value* StructureType::MakeDefaultValue(Context& context) const
{
    std::vector<Value*> fieldValues;
    int n = FieldCount();
    for (int i = 0; i < n; ++i)
    {
        Type* type = FieldType(i);
        fieldValues.push_back(type->MakeDefaultValue(context));
    }
    return context.MakeStructureValue(soul::ast::SourcePos(), fieldValues);
}

FwdDeclaredStructureType::FwdDeclaredStructureType(const util::uuid& uuid_, int32_t typeId_) :
    Type(soul::ast::SourcePos(), TypeKind::fwdDeclaredStructureType, typeId_), uuid(uuid_)
{
}

void FwdDeclaredStructureType::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ArrayType::ArrayType(const SourcePos& sourcePos_, int32_t typeId_, int64_t elementCount_, const TypeRef& elementTypeRef_) :
    Type(sourcePos_, TypeKind::arrayType, typeId_), elementCount(elementCount_), elementTypeRef(elementTypeRef_)
{
}

otava::assembly::DataInst ArrayType::DataInstruction() const
{
    return ElementType()->DataInstruction();
}

void ArrayType::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ArrayType::Add(Types* types, Context* context)
{
    types->Add(this, context);
}

void ArrayType::Resolve(Types* types, Context* context)
{
    types->ResolveType(elementTypeRef, context);
}

int64_t ArrayType::Size() const
{
    return util::Align(elementCount * ElementType()->Size(), 8);
}

bool ArrayType::IsWeakType() const
{
    Type* elementType = ElementType();
    if (elementType->IsStructureType() || elementType->IsArrayType() || elementType->IsFunctionType())
    {
        return false;
    }
    return true;
}

void ArrayType::WriteDeclaration(util::CodeFormatter& formatter)
{
    Type::WriteDeclaration(formatter);
    formatter.Write("[");
    formatter.Write(std::to_string(elementCount));
    formatter.Write(" x ");
    elementTypeRef.Write(formatter);
    formatter.Write("]");
}

Value* ArrayType::MakeDefaultValue(Context& context) const
{
    std::vector<Value*> elements;
    return context.MakeArrayValue(soul::ast::SourcePos(), elements);
}

FunctionType::FunctionType(const SourcePos& sourcePos_, int32_t typeId_, const TypeRef& returnTypeRef_, const std::vector<TypeRef>& paramTypeRefs_) :
    Type(sourcePos_, TypeKind::functionType, typeId_), returnTypeRef(returnTypeRef_), paramTypeRefs(paramTypeRefs_)
{
}

void FunctionType::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FunctionType::Add(Types* types, Context* context)
{
    types->Add(this, context);
}

void FunctionType::Resolve(Types* types, Context* context)
{
    types->ResolveType(returnTypeRef, context);
    for (auto& paramTypeRef : paramTypeRefs)
    {
        types->ResolveType(paramTypeRef, context);
    }
}

bool FunctionType::IsWeakType() const
{
    Type* returnType = ReturnType();
    if (returnType->IsStructureType() || returnType->IsArrayType() || returnType->IsFunctionType())
    {
        return false;
    }
    int n = Arity();
    for (int i = 0; i < n; ++i)
    {
        Type* paramType = ParamType(i);
        if (paramType->IsStructureType() || paramType->IsArrayType() || paramType->IsFunctionType())
        {
            return false;
        }
    }
    return true;
}

void FunctionType::WriteDeclaration(util::CodeFormatter& formatter)
{
    Type::WriteDeclaration(formatter);
    formatter.Write("function ");
    returnTypeRef.Write(formatter);
    formatter.Write("(");
    bool first = true;
    for (auto& paramTypeRef : paramTypeRefs)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            formatter.Write(", ");
        }
        paramTypeRef.Write(formatter);
    }
    formatter.Write(")");
}

PointerType::PointerType(const SourcePos& sourcePos_, int32_t typeId_, int8_t pointerCount_, int32_t baseTypeId_) :
    Type(sourcePos_, TypeKind::pointerType, typeId_), pointerCount(pointerCount_), baseTypeRef(sourcePos_, baseTypeId_)
{
}

std::string PointerType::Name() const
{
    return baseTypeRef.GetType()->Name() + "*";
}

void PointerType::ReplaceForwardReference(FwdDeclaredStructureType* fwdDeclaredType, StructureType* structureType, Context* context)
{
    if (BaseType() == fwdDeclaredType)
    {
        baseTypeRef = TypeRef(SourcePos(), structureType->Id());
        context->GetTypes().ResolveType(baseTypeRef, context);
    }
}

Type* GetElemType(Value* ptr, Value* index, const SourcePos& sourcePos, Context* context)
{
    Type* type = ptr->GetType();
    if (type->IsPointerType())
    {
        PointerType* ptrType = static_cast<PointerType*>(type);
        Type* aggregateType = ptrType->BaseType();
        if (aggregateType->IsStructureType())
        {
            if (index->IsLongValue())
            {
                int64_t idx = static_cast<LongValue*>(index)->GetValue();
                StructureType* structureType = static_cast<StructureType*>(aggregateType);
                return context->MakePtrType(structureType->FieldType(static_cast<int>(idx)));
            }
            else
            {
                Error("long valued index expected", sourcePos, context);
            }
        }
        else if (aggregateType->IsArrayType())
        {
            ArrayType* arrayType = static_cast<ArrayType*>(aggregateType);
            return context->MakePtrType(arrayType->ElementType());
        }
        else
        {
            Error("structure or array type expected", sourcePos, context);
        }
    }
    else
    {
        Error("pointer type expected", sourcePos, context);
    }
    return nullptr;
}

Types::Types() : context(nullptr), nextTypeId(userTypeId)
{
}

void Types::Init()
{
    boolType.SetDefaultValue(context->GetFalseValue());
    sbyteType.SetDefaultValue(context->GetSByteValue(0));
    byteType.SetDefaultValue(context->GetByteValue(0));
    shortType.SetDefaultValue(context->GetShortValue(0));
    ushortType.SetDefaultValue(context->GetUShortValue(0));
    intType.SetDefaultValue(context->GetIntValue(0));
    uintType.SetDefaultValue(context->GetUIntValue(0));
    longType.SetDefaultValue(context->GetLongValue(0));
    ulongType.SetDefaultValue(context->GetULongValue(0));
    floatType.SetDefaultValue(context->GetFloatValue(0.0f));
    doubleType.SetDefaultValue(context->GetDoubleValue(0.0));
}

void Types::Write(util::CodeFormatter& formatter)
{
    if (types.empty()) return;
    formatter.WriteLine("types");
    formatter.WriteLine("{");
    formatter.IncIndent();
    for (const auto& type : types)
    {
        if (type->IsFwdDeclaredStructureType()) continue;
        if (type->IsAggregateType())
        {
            type->WriteDeclaration(formatter);
            formatter.WriteLine();
        }
    }
    formatter.DecIndent();
    formatter.WriteLine("}");
    formatter.WriteLine();
}

StructureType* Types::GetStructureType(const SourcePos& sourcePos, int32_t typeId, const std::vector<TypeRef>& fieldTypeRefs)
{
    std::vector<int32_t> fieldTypeIds;
    for (const auto& fieldTypeRef : fieldTypeRefs)
    {
        fieldTypeIds.push_back(fieldTypeRef.Id());
    }
    auto it = structureTypeMap.find(fieldTypeIds);
    if (it != structureTypeMap.cend())
    {
        StructureType* structureType = it->second;
        typeMap[typeId] = structureType;
        return structureType;
    }
    StructureType* structureType = new StructureType(sourcePos, typeId, fieldTypeRefs);
    types.push_back(std::unique_ptr<Type>(structureType));
    structureTypeMap[fieldTypeIds] = structureType;
    Map(structureType);
    return structureType;
}

ArrayType* Types::GetArrayType(const SourcePos& sourcePos, int32_t typeId, int64_t size, const TypeRef& elementTypeRef)
{
    auto key = std::make_pair(size, elementTypeRef.Id());
    auto it = arrayTypeMap.find(key);
    if (it != arrayTypeMap.cend())
    {
        ArrayType* arrayType = it->second;
        typeMap[typeId] = arrayType;
        return arrayType;
    }
    ArrayType* arrayType = new ArrayType(sourcePos, typeId, size, elementTypeRef);
    types.push_back(std::unique_ptr<Type>(arrayType));
    arrayTypeMap[key] = arrayType;
    Map(arrayType);
    return arrayType;
}

FunctionType* Types::GetFunctionType(const SourcePos& sourcePos, int32_t typeId, const TypeRef& returnTypeRef, const std::vector<TypeRef>& paramTypeRefs)
{
    int32_t returnTypeId = returnTypeRef.Id();
    std::vector<int32_t> paramTypeIds;
    for (const auto& paramTypeRef : paramTypeRefs)
    {
        paramTypeIds.push_back(paramTypeRef.Id());
    }
    auto key = std::make_pair(returnTypeId, paramTypeIds);
    auto it = functionTypeMap.find(key);
    if (it != functionTypeMap.cend())
    {
        FunctionType* functionType = it->second;
        typeMap[typeId] = functionType;
        return functionType;
    }
    FunctionType* functionType = new FunctionType(sourcePos, typeId, returnTypeRef, paramTypeRefs);
    types.push_back(std::unique_ptr<Type>(functionType));
    functionTypeMap[key] = functionType;
    Map(functionType);
    return functionType;
}

FwdDeclaredStructureType* Types::GetFwdDeclaredStructureType(const util::uuid& uuid, int32_t typeId)
{
    auto it = fwdDeclaredStructureTypes.find(uuid);
    if (it != fwdDeclaredStructureTypes.cend())
    {
        return it->second;
    }
    else
    {
        FwdDeclaredStructureType* fwdDeclaredType = new FwdDeclaredStructureType(uuid, typeId);
        fwdDeclaredStructureTypes[uuid] = fwdDeclaredType;
        types.push_back(std::unique_ptr<Type>(fwdDeclaredType));
        Map(fwdDeclaredType);
        return fwdDeclaredType;
    }
}

void Types::Add(Type* type, Context* context)
{
    Map(type);
    declaredTypes.push_back(type);
}

Type* Types::Get(int32_t id) const
{
    if (IsFundamentalTypeId(id))
    {
        return GetFundamentalType(id);
    }
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

Type* Types::GetFundamentalType(int32_t id) const
{
    switch (id)
    {
        case voidTypeId: return const_cast<VoidType*>(&voidType);
        case boolTypeId: return const_cast<BoolType*>(&boolType);
        case sbyteTypeId: return const_cast<SByteType*>(&sbyteType);
        case byteTypeId: return const_cast<ByteType*>(&byteType);
        case shortTypeId: return const_cast<ShortType*>(&shortType);
        case ushortTypeId: return const_cast<UShortType*>(&ushortType);
        case intTypeId: return const_cast<IntType*>(&intType);
        case uintTypeId: return const_cast<UIntType*>(&uintType);
        case longTypeId: return const_cast<LongType*>(&longType);
        case ulongTypeId: return const_cast<ULongType*>(&ulongType);
        case floatTypeId: return const_cast<FloatType*>(&floatType);
        case doubleTypeId: return const_cast<DoubleType*>(&doubleType);
    }
    return nullptr;
}

void Types::Map(Type* type)
{
    typeMap[type->Id()] = type;
}

void Types::VisitTypeDeclarations(Visitor& visitor)
{
    for (Type* declaredType : declaredTypes)
    {
        declaredType->Accept(visitor);
    }
}

PointerType* Types::MakePointerType(const SourcePos& sourcePos, int32_t baseTypeId, int8_t pointerCount, Context* context)
{
    auto it = pointerTypeMap.find(std::make_pair(baseTypeId, pointerCount));
    if (it != pointerTypeMap.cend())
    {
        return it->second;
    }
    PointerType* type = nullptr;
    if (pointerCount > 1)
    {
        type = new PointerType(sourcePos, MakePointerTypeId(baseTypeId, pointerCount), pointerCount, MakePointerTypeId(baseTypeId, pointerCount - 1));
        type->SetDefaultValue(context->GetNullValue(sourcePos, type));
    }
    else if (pointerCount == 1)
    {
        type = new PointerType(sourcePos, MakePointerTypeId(baseTypeId, pointerCount), pointerCount, baseTypeId);
        type->SetDefaultValue(context->GetNullValue(sourcePos, type));
    }
    else
    {
        Error("pointer count > 0 expected", sourcePos, context);
    }
    ResolveType(type->BaseTypeRef(), context);
    types.push_back(std::unique_ptr<Type>(type));
    Map(type);
    pointerTypeMap[std::make_pair(baseTypeId, pointerCount)] = type;
    return type;
}

void Types::Resolve(Context* context)
{
    for (const auto& type : types)
    {
        type->Add(this, context);
    }
    std::vector<Type*> toResolve;
    for (const auto& type : types)
    {
        toResolve.push_back(type.get());
    }
    for (Type* type : toResolve)
    {
        type->Resolve(this, context);
    }
}

void Types::ResolveType(TypeRef& typeRef, Context* context)
{
    Type* type = Get(typeRef.Id());
    if (!type)
    {
        if (IsPointerTypeId(typeRef.Id()))
        {
            type = MakePointerType(typeRef.GetSourcePos(), GetBaseTypeId(typeRef.Id()), GetPointerCount(typeRef.Id()), context);
        }
    }
    if (!type)
    {
        Error("error resolving type: type id " + std::to_string(typeRef.Id()) + " not found", typeRef.GetSourcePos(), context);
    }
    typeRef.SetType(type);
}

} // otava::intermediate
