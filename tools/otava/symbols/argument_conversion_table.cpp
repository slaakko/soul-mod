// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.argument.conversion.table;

import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.classes;
import otava.symbols.class_templates;
import otava.symbols.conversion.table;
import otava.symbols.function.symbol;
import otava.symbols.type_compare;
import otava.symbols.fundamental.type.conversion;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.emitter;
import otava.symbols.array.type.symbol;
import otava.symbols.enums;
import otava.symbols.overload.resolution;
import otava.symbols.type_compare;
import otava.symbols.type.symbol;
import otava.intermediate.value;

namespace otava::symbols {

class IdentityConversion : public FunctionSymbol
{
public:
    IdentityConversion(TypeSymbol* type_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return type; }
    TypeSymbol* ConversionArgType() const override { return type; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    int32_t ConversionDistance() const override { return 255; }
    bool IsIdentityConversion() const override { return true; }
private:
    TypeSymbol* type;
};

IdentityConversion::IdentityConversion(TypeSymbol* type_, Context* context) : FunctionSymbol(U"@conversion"), type(type_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", type);
    AddParameter(arg, soul::ast::SourcePos(), context);
    SetReturnType(type, context);
}

void IdentityConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
}

class IdentityArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* IdentityArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (TypesEqual(argType->PlainType(context), paramType->PlainType(context)))
    {
        return new IdentityConversion(argType, context);
    }
    return nullptr;
}

class DerivedToBaseConversion : public FunctionSymbol
{
public:
    DerivedToBaseConversion(TypeSymbol* derivedTypePtr_, TypeSymbol* baseTypePtr_, int distance_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsDerivedToBaseConversion() const override { return true; }    
    TypeSymbol* ConversionParamType() const override { return baseTypePtr; }
    TypeSymbol* ConversionArgType() const override { return derivedTypePtr; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    int32_t ConversionDistance() const override { return distance; }
private:
    TypeSymbol* derivedTypePtr;
    TypeSymbol* baseTypePtr;
    int distance;
};

DerivedToBaseConversion::DerivedToBaseConversion(TypeSymbol* derivedTypePtr_, TypeSymbol* baseTypePtr_, int distance_, Context* context) :
    FunctionSymbol(U"@conversion"), derivedTypePtr(derivedTypePtr_), baseTypePtr(baseTypePtr_), distance(distance_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", derivedTypePtr);
    AddParameter(arg, soul::ast::SourcePos(), context);
    SetReturnType(baseTypePtr, context);
}

void DerivedToBaseConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitBitcast(value, baseTypePtr->IrType(emitter, sourcePos, context)));
}

class DerivedToBaseArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* DerivedToBaseArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    int distance = 0;
    if (paramType->PointerCount() == 1 && argType->PointerCount() == 1 && argType->GetBaseType()->HasBaseClass(paramType->GetBaseType(), distance))
    {
        return new DerivedToBaseConversion(argType, paramType, distance, context);
    }
    if (argType->GetBaseType()->HasBaseClass(paramType->GetBaseType(), distance))
    {
        if (paramType->IsReferenceType())
        {
            argumentMatch.preConversionFlags = OperationFlags::addr;
        }
        return new DerivedToBaseConversion(argType, paramType, distance, context);
    }
    return nullptr;
}

class BaseToDerivedConversion : public FunctionSymbol
{
public:
    BaseToDerivedConversion(TypeSymbol* baseTypePtr_, TypeSymbol* derivedTypePtr_, int distance_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return derivedTypePtr; }
    TypeSymbol* ConversionArgType() const override { return baseTypePtr; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    int32_t ConversionDistance() const override { return distance; }
private:
    TypeSymbol* baseTypePtr;
    TypeSymbol* derivedTypePtr;
    int distance;
};

BaseToDerivedConversion::BaseToDerivedConversion(TypeSymbol* baseTypePtr_, TypeSymbol* derivedTypePtr_, int distance_, Context* context) :
    FunctionSymbol(U"@conversion"), baseTypePtr(baseTypePtr_), derivedTypePtr(derivedTypePtr_), distance(distance_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", baseTypePtr);
    AddParameter(arg, soul::ast::SourcePos(), context);
    SetReturnType(derivedTypePtr, context);
}

void BaseToDerivedConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitBitcast(value, derivedTypePtr->IrType(emitter, sourcePos, context)));
}

class BaseToDerivedArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* BaseToDerivedArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    int distance = 0;
    if (paramType->PointerCount() == 1 && argType->PointerCount() == 1 && paramType->GetBaseType()->HasBaseClass(argType->GetBaseType(), distance))
    {
        distance += 100;
        return new BaseToDerivedConversion(argType, paramType, distance, context);
    }
    return nullptr;
}

class NullPtrToPtrConversion : public FunctionSymbol
{
public:
    NullPtrToPtrConversion(TypeSymbol* argType_, TypeSymbol* pointerType_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return pointerType; }
    TypeSymbol* ConversionArgType() const override { return argType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    int32_t ConversionDistance() const override { return 1; }
private:
    TypeSymbol* argType;
    TypeSymbol* pointerType;
};

NullPtrToPtrConversion::NullPtrToPtrConversion(TypeSymbol* argType_, TypeSymbol* pointerType_, Context* context) : 
    FunctionSymbol(U"@conversion"), argType(argType_), pointerType(pointerType_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", argType);
    AddParameter(arg, soul::ast::SourcePos(), context);
    SetReturnType(pointerType, context);
}

void NullPtrToPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitBitcast(value, pointerType->IrType(emitter, sourcePos, context)));
}

class NullPtrToPtrArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* NullPtrToPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (argType->IsNullPtrType() && paramType->IsPointerType())
    {
        return new NullPtrToPtrConversion(argType, paramType, context);
    }
    return nullptr;
}

class VoidPtrToPtrConversion : public FunctionSymbol
{
public:
    VoidPtrToPtrConversion(TypeSymbol* voidPtrType_, TypeSymbol* targetPointerType_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return targetPointerType; }
    TypeSymbol* ConversionArgType() const override { return voidPtrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    int32_t ConversionDistance() const override { return 255; }
private:
    TypeSymbol* voidPtrType;
    TypeSymbol* targetPointerType;
};

VoidPtrToPtrConversion::VoidPtrToPtrConversion(TypeSymbol* voidPtrType_, TypeSymbol* targetPointerType_, Context* context) :
    FunctionSymbol(U"@conversion"), voidPtrType(voidPtrType_), targetPointerType(targetPointerType_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", voidPtrType);
    AddParameter(arg, soul::ast::SourcePos(), context);
    SetReturnType(targetPointerType, context);
}

void VoidPtrToPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitBitcast(value, targetPointerType->IrType(emitter, sourcePos, context)));
}

class VoidPtrToPtrArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* VoidPtrToPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (argType->IsPointerType() && argType->PointerCount() == 1 && argType->GetBaseType()->IsVoidType() && paramType->IsPointerType())
    {
        return new VoidPtrToPtrConversion(argType, paramType, context);
    }
    return nullptr;
}

class PtrToVoidPtrConversion : public FunctionSymbol
{
public:
    PtrToVoidPtrConversion(TypeSymbol* ptrType_, TypeSymbol* voidPtrType_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return voidPtrType; }
    TypeSymbol* ConversionArgType() const override { return ptrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    int32_t ConversionDistance() const override { return 10; }
private:
    TypeSymbol* ptrType;
    TypeSymbol* voidPtrType;
};

PtrToVoidPtrConversion::PtrToVoidPtrConversion(TypeSymbol* ptrType_, TypeSymbol* voidPtrType_, Context* context) :
    FunctionSymbol(U"@conversion"), ptrType(ptrType_), voidPtrType(voidPtrType_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", ptrType);
    AddParameter(arg, soul::ast::SourcePos(), context);
    SetReturnType(voidPtrType, context);
}

void PtrToVoidPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitBitcast(value, voidPtrType->IrType(emitter, sourcePos, context)));
}

class PtrToVoidPtrArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* PtrToVoidPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (argType->IsPointerType() && paramType->IsPointerType() && paramType->PointerCount() == 1 && paramType->GetBaseType()->IsVoidType())
    {
        return new PtrToVoidPtrConversion(argType, paramType, context);
    }
    return nullptr;
}

class PtrToPtrConversion : public FunctionSymbol
{
public:
    PtrToPtrConversion(TypeSymbol* sourcePtrType_, TypeSymbol* targetPtrType_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return targetPtrType; }
    TypeSymbol* ConversionArgType() const override { return sourcePtrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    int32_t ConversionDistance() const override { return 255; }
private:
    TypeSymbol* sourcePtrType;
    TypeSymbol* targetPtrType;
};

PtrToPtrConversion::PtrToPtrConversion(TypeSymbol* sourcePtrType_, TypeSymbol* targetPtrType_, Context* context) : 
    FunctionSymbol(U"@conversion"), sourcePtrType(sourcePtrType_), targetPtrType(targetPtrType_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", sourcePtrType);
    AddParameter(arg, soul::ast::SourcePos(), context);
    SetReturnType(targetPtrType, context);
}

void PtrToPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitBitcast(value, targetPtrType->IrType(emitter, sourcePos, context)));
}

class ReinterpretCastArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* ReinterpretCastArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (context->GetFlag(ContextFlags::reinterpretCast))
    {
        if (argType->IsPointerType() && paramType->IsPointerType() && argType->PointerCount() == 1 && paramType->PointerCount() == 1)
        {
            return new PtrToPtrConversion(argType, paramType, context);
        }
    }
    return nullptr;
}

class VoidPtrToUInt64Conversion : public FunctionSymbol
{
public:
    VoidPtrToUInt64Conversion(TypeSymbol* ptrType_, TypeSymbol* uint64Type_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return uint64Type; }
    TypeSymbol* ConversionArgType() const override { return ptrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    int32_t ConversionDistance() const override { return 255; }
private:
    TypeSymbol* ptrType;
    TypeSymbol* uint64Type;
};

VoidPtrToUInt64Conversion::VoidPtrToUInt64Conversion(TypeSymbol* ptrType_, TypeSymbol* uint64Type_, Context* context) :
    FunctionSymbol(U"@conversion"), ptrType(ptrType_), uint64Type(uint64Type_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", ptrType);
    AddParameter(arg, soul::ast::SourcePos(), context);
    SetReturnType(uint64Type, context);
}

void VoidPtrToUInt64Conversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitPtrToInt(value, uint64Type->IrType(emitter, sourcePos, context)));
}

class VoidPtrToUInt64ArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* VoidPtrToUInt64ArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol* uint64Type = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::unsignedLongLongIntType);
    if (argType->IsVoidPtrType() && TypesEqual(paramType, uint64Type))
    {
        return new VoidPtrToUInt64Conversion(argType, paramType, context);
    }
    return nullptr;
}

class UInt64ToVoidPtrConversion : public FunctionSymbol
{
public:
    UInt64ToVoidPtrConversion(TypeSymbol* uint64Type_, TypeSymbol* ptrType_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return ptrType; }
    TypeSymbol* ConversionArgType() const override { return uint64Type; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    int32_t ConversionDistance() const override { return 255; }
private:
    TypeSymbol* uint64Type;
    TypeSymbol* ptrType;
};

UInt64ToVoidPtrConversion::UInt64ToVoidPtrConversion(TypeSymbol* uint64Type_, TypeSymbol* ptrType_, Context* context) :
    FunctionSymbol(U"@conversion"), uint64Type(uint64Type), ptrType(ptrType_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", uint64Type);
    AddParameter(arg, soul::ast::SourcePos(), nullptr);
    SetReturnType(ptrType, context);
}

void UInt64ToVoidPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitIntToPtr(value, ptrType->IrType(emitter, sourcePos, context)));
}

class UInt64ToVoidPtrArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* UInt64ToVoidPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol* uint64Type = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::unsignedLongLongIntType);
    if (TypesEqual(argType, uint64Type) && paramType->IsVoidPtrType())
    {
        return new UInt64ToVoidPtrConversion(argType, paramType, context);
    }
    return nullptr;
}

class PtrToBooleanConversion : public FunctionSymbol
{
public:
    PtrToBooleanConversion(TypeSymbol* ptrType_, TypeSymbol* boolType_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return boolType; }
    TypeSymbol* ConversionArgType() const override { return ptrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    int32_t ConversionDistance() const override { return 1; }
private:
    TypeSymbol* ptrType;
    TypeSymbol* boolType;
};

PtrToBooleanConversion::PtrToBooleanConversion(TypeSymbol* ptrType_, TypeSymbol* boolType_, Context* context) :
    FunctionSymbol(U"@conversion"), ptrType(ptrType_), boolType(boolType_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", ptrType);
    AddParameter(arg, soul::ast::SourcePos(), nullptr);
    SetReturnType(boolType, context);
}

void PtrToBooleanConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    otava::intermediate::Type* irType = static_cast<otava::intermediate::Type*>(ptrType->IrType(emitter, sourcePos, context));
    otava::intermediate::Value* defaultValue = irType->DefaultValue();
    otava::intermediate::Value* equal = emitter.EmitEqual(value, defaultValue);
    otava::intermediate::Value* notEqual = emitter.EmitNot(equal);
    emitter.Stack().Push(notEqual);
}

class PtrToBooleanArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* PtrToBooleanArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::boolType);
    if (argType->IsPointerType() && TypesEqual(paramType, boolType))
    {
        return new PtrToBooleanConversion(argType, paramType, context);
    }
    return nullptr;
}

class ArrayToPtrConversion : public FunctionSymbol
{
public:
    ArrayToPtrConversion(ArrayTypeSymbol* arrayType_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return elementPtrType; }
    TypeSymbol* ConversionArgType() const override { return arrayPtrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    int32_t ConversionDistance() const override { return 1; }
private:
    ArrayTypeSymbol* arrayType;
    TypeSymbol* arrayPtrType;
    TypeSymbol* elementPtrType;
};

ArrayToPtrConversion::ArrayToPtrConversion(ArrayTypeSymbol* arrayType_, Context* context) : 
    FunctionSymbol(U"@conversion"), arrayType(arrayType_), arrayPtrType(arrayType->AddPointer(context)), elementPtrType(arrayType->ElementType()->AddPointer(context))
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", arrayType->AddPointer(context));
    AddParameter(arg, soul::ast::SourcePos(), nullptr);
    SetReturnType(elementPtrType, context);
}

void ArrayToPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* arrayPtr = emitter.Stack().Pop();
    otava::intermediate::Value* elemAddr = emitter.EmitElemAddr(arrayPtr, emitter.EmitLong(0));
    emitter.Stack().Push(elemAddr);
}

class ArrayToPtrArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* ArrayToPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    bool addAddr = false;
    if (argType->IsArrayTypeSymbol())
    {
        addAddr = true;
        argType = argType->AddPointer(context);
    }
    if (argType->RemovePointer(context)->IsArrayTypeSymbol())
    {
        ArrayTypeSymbol* arrayType = static_cast<ArrayTypeSymbol*>(argType->RemovePointer(context));
        TypeSymbol* elementType = arrayType->ElementType()->AddPointer(context);
        if (TypesEqual(paramType->RemoveConst(context), elementType))
        {
            if (addAddr)
            {
                argumentMatch.preConversionFlags = OperationFlags::addr;
            }
            return new ArrayToPtrConversion(arrayType, context);
        }
        else 
        {
            if (arg && functionMatch.function)
            {
                FunctionMatch tempFunctionMatch;
                tempFunctionMatch = functionMatch;
                if (FindTemplateParameterMatch(elementType, paramType, arg, tempFunctionMatch, sourcePos, context))
                {
                    if (addAddr)
                    {
                        argumentMatch.preConversionFlags = OperationFlags::addr;
                    }
                    return new ArrayToPtrConversion(arrayType, context);
                }
                else if (FindClassTemplateMatch(elementType, paramType, arg, tempFunctionMatch, sourcePos, context))
                {
                    if (addAddr)
                    {
                        argumentMatch.preConversionFlags = OperationFlags::addr;
                    }
                    return new ArrayToPtrConversion(arrayType, context);
                }
                else if (FindClassTemplateSpecializationMatch(elementType, paramType, arg, tempFunctionMatch, sourcePos, context))
                {
                    if (addAddr)
                    {
                        argumentMatch.preConversionFlags = OperationFlags::addr;
                    }
                    return new ArrayToPtrConversion(arrayType, context);
                }
            }
        }
    }
    return nullptr;
}

class EnumTypeToUnderlyingTypeConversion : public FunctionSymbol
{
public:
    EnumTypeToUnderlyingTypeConversion(EnumeratedTypeSymbol* enumType_, TypeSymbol* underlyingType_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return underlyingType; }
    TypeSymbol* ConversionArgType() const override { return enumType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    int32_t ConversionDistance() const override { return 100; }
private:
    EnumeratedTypeSymbol* enumType;
    TypeSymbol* underlyingType;
};

EnumTypeToUnderlyingTypeConversion::EnumTypeToUnderlyingTypeConversion(EnumeratedTypeSymbol* enumType_, TypeSymbol* underlyingType_, Context* context) : 
    FunctionSymbol(U"@conversion"), enumType(enumType_), underlyingType(underlyingType_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", enumType);
    AddParameter(arg, soul::ast::SourcePos(), context);
    SetReturnType(underlyingType, context);
}

void EnumTypeToUnderlyingTypeConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitBitcast(value, underlyingType->IrType(emitter, sourcePos, context)));
}

class EnumTypeToUnderlyingTypeArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* EnumTypeToUnderlyingTypeArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (argType->IsEnumeratedTypeSymbol())
    {
        EnumeratedTypeSymbol* enumType = static_cast<EnumeratedTypeSymbol*>(argType);
        TypeSymbol* underlyingType = enumType->UnderlyingType();
        if (!underlyingType)
        {
            underlyingType = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType);
        }
        underlyingType = underlyingType->DirectType(context)->FinalType(sourcePos, context);
        if (TypesEqual(paramType, underlyingType))
        {
            return new EnumTypeToUnderlyingTypeConversion(enumType, underlyingType, context);
        }
    }
    return nullptr;
}

class UnderlyingTypeToEnumTypeConversion : public FunctionSymbol
{
public:
    UnderlyingTypeToEnumTypeConversion(EnumeratedTypeSymbol* enumType_, TypeSymbol* underlyingType_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return enumType; }
    TypeSymbol* ConversionArgType() const override { return underlyingType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    int32_t ConversionDistance() const override { return 255; }
private:
    EnumeratedTypeSymbol* enumType;
    TypeSymbol* underlyingType;
};

UnderlyingTypeToEnumTypeConversion::UnderlyingTypeToEnumTypeConversion(EnumeratedTypeSymbol* enumType_, TypeSymbol* underlyingType_, Context* context) : 
    FunctionSymbol(U"@conversion"), enumType(enumType_), underlyingType(underlyingType_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", underlyingType);
    AddParameter(arg, soul::ast::SourcePos(), context);
    SetReturnType(enumType, context);
}

void UnderlyingTypeToEnumTypeConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitBitcast(value, enumType->IrType(emitter, sourcePos, context)));
}

class UnderlyingTypeEnumTypeToArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, 
        const soul::ast::SourcePos& sourcePos, Context* context) override;
};

FunctionSymbol* UnderlyingTypeEnumTypeToArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (paramType->IsEnumeratedTypeSymbol())
    {
        EnumeratedTypeSymbol* enumType = static_cast<EnumeratedTypeSymbol*>(paramType);
        TypeSymbol* underlyingType = enumType->UnderlyingType();
        if (!underlyingType)
        {
            underlyingType = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType);
        }
        underlyingType = underlyingType->DirectType(context)->FinalType(sourcePos, context);
        if (TypesEqual(argType, underlyingType))
        {
            return new UnderlyingTypeToEnumTypeConversion(enumType, underlyingType, context);
        }
    }
    return nullptr;
}

ArgumentConversionTable::ArgumentConversionTable()
{
    AddArgumentConversion(new IdentityArgumentConversion());
    AddArgumentConversion(new DerivedToBaseArgumentConversion());
    AddArgumentConversion(new BaseToDerivedArgumentConversion());
    AddArgumentConversion(new NullPtrToPtrArgumentConversion());
    AddArgumentConversion(new VoidPtrToPtrArgumentConversion());
    AddArgumentConversion(new PtrToVoidPtrArgumentConversion());
    AddArgumentConversion(new ReinterpretCastArgumentConversion());
    AddArgumentConversion(new VoidPtrToUInt64ArgumentConversion());
    AddArgumentConversion(new UInt64ToVoidPtrArgumentConversion());
    AddArgumentConversion(new PtrToBooleanArgumentConversion());
    AddArgumentConversion(new ArrayToPtrArgumentConversion());
    AddArgumentConversion(new EnumTypeToUnderlyingTypeArgumentConversion());
    AddArgumentConversion(new UnderlyingTypeEnumTypeToArgumentConversion());
}

void ArgumentConversionTable::AddArgumentConversion(ArgumentConversion* argumentConversion)
{
    argumentConversions.push_back(std::unique_ptr<ArgumentConversion>(argumentConversion));
}

FunctionSymbol* ArgumentConversionTable::GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ArgumentMatch argumentMatch;
    FunctionMatch functionMatch;
    return GetArgumentConversion(paramType, argType, nullptr, sourcePos, argumentMatch, functionMatch, context);
}

FunctionSymbol* ArgumentConversionTable::GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    const soul::ast::SourcePos& sourcePos, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, Context* context)
{
    FunctionSymbol* conversion = nullptr; 
    if (!TypesEqual(paramType, argType))
    {
        conversion = context->GetSymbolTable()->GetConversionTable().GetConversion(paramType, argType, context);
        if (conversion)
        {
            if (conversion->ConversionArgType()->IsReferenceType() && !argType->IsReferenceType() || conversion->ConversionArgType()->IsClassTypeSymbol())
            {
                argumentMatch.preConversionFlags = OperationFlags::addr;
            }
            else if (!conversion->ConversionArgType()->IsReferenceType() && argType->IsReferenceType())
            {
                argumentMatch.preConversionFlags = OperationFlags::deref;
            }
        }
    }
    if (conversion)
    {
        return conversion;
    }
    if (argType->PlainType(context)->IsClassTypeSymbol())
    {
        ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(argType->GetBaseType());
        if (classType->IsClassTemplateSpecializationSymbol())
        {
            ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(classType);
            TypeSymbol* classTemplateSymbol = specialization->ClassTemplate();
            if (classTemplateSymbol->IsClassTypeSymbol())
            {
                ClassTypeSymbol* classTemplate = static_cast<ClassTypeSymbol*>(classTemplateSymbol);
                FunctionSymbol* conversionFunction = classTemplate->GetConversionFunction(paramType);
                if (conversionFunction)
                {
                    std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
                    FunctionSymbol* instantiatedConversionFunction = InstantiateMemFnOfClassTemplate(conversionFunction, specialization, templateParameterMap, sourcePos, context);
                    return instantiatedConversionFunction;
                }
            }
        }
        else
        {
            FunctionSymbol* conversionFunction = classType->GetConversionFunction(paramType);
            if (conversionFunction)
            {
                return conversionFunction;
            }
        }
    }
    for (const auto& argumentConversion : argumentConversions)
    {
        FunctionSymbol* conversionFunction = argumentConversion->Get(paramType, argType, arg, argumentMatch, functionMatch, sourcePos, context);
        if (conversionFunction)
        {
            conversionFunctions.push_back(std::unique_ptr<FunctionSymbol>(conversionFunction));
            return conversionFunction;
        }
    }
    return nullptr;
}

} // namespace otava::symbols

