// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.argument.conversion.table;

import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.conversion.table;
import otava.symbols.function.symbol;
import otava.symbols.type.symbol;
import otava.symbols.fundamental.type.conversion;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.emitter;
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
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context) override;
};

FunctionSymbol* IdentityArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context)
{
    if (TypesEqual(argType->PlainType(), paramType->PlainType()))
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
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context) override;
};

FunctionSymbol* DerivedToBaseArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context)
{
    int distance = 0;
    if (paramType->PointerCount() == 1 && argType->PointerCount() == 1 && argType->GetBaseType()->HasBaseClass(paramType->GetBaseType(), distance))
    {
        return new DerivedToBaseConversion(argType, paramType, distance, context);
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
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context) override;
};

FunctionSymbol* NullPtrToPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context)
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
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context) override;
};

FunctionSymbol* VoidPtrToPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context)
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
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context) override;
};

FunctionSymbol* PtrToVoidPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context)
{
    if (argType->IsPointerType() && paramType->IsPointerType() && paramType->PointerCount() == 1 && paramType->GetBaseType()->IsVoidType())
    {
        return new PtrToVoidPtrConversion(argType, paramType, context);
    }
    return nullptr;
}

class PtrToUInt64Conversion : public FunctionSymbol
{
public:
    PtrToUInt64Conversion(TypeSymbol* ptrType_, TypeSymbol* uint64Type_, Context* context);
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

PtrToUInt64Conversion::PtrToUInt64Conversion(TypeSymbol* ptrType_, TypeSymbol* uint64Type_, Context* context) :
    FunctionSymbol(U"@conversion"), ptrType(ptrType_), uint64Type(uint64Type_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", ptrType);
    AddParameter(arg, soul::ast::SourcePos(), context);
    SetReturnType(uint64Type, context);
}

void PtrToUInt64Conversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitPtrToInt(value, uint64Type->IrType(emitter, sourcePos, context)));
}

class PtrToUInt64ArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context) override;
};

FunctionSymbol* PtrToUInt64ArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context)
{
    TypeSymbol* uint64Type = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::unsignedLongLongIntType);
    if (argType->IsPointerType() && TypesEqual(paramType, uint64Type))
    {
        return new PtrToUInt64Conversion(argType, paramType, context);
    }
    return nullptr;
}

class UInt64ToPtrConversion : public FunctionSymbol
{
public:
    UInt64ToPtrConversion(TypeSymbol* uint64Type_, TypeSymbol* ptrType_, Context* context);
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

UInt64ToPtrConversion::UInt64ToPtrConversion(TypeSymbol* uint64Type_, TypeSymbol* ptrType_, Context* context) : 
    FunctionSymbol(U"@conversion"), uint64Type(uint64Type), ptrType(ptrType_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", uint64Type);
    AddParameter(arg, soul::ast::SourcePos(), nullptr);
    SetReturnType(ptrType, context);
}

void UInt64ToPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitIntToPtr(value, ptrType->IrType(emitter, sourcePos, context)));
}

class UInt64ToPtrArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context) override;
};

FunctionSymbol* UInt64ToPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context)
{
    TypeSymbol* uint64Type = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::unsignedLongLongIntType);
    if (TypesEqual(argType, uint64Type) && paramType->IsPointerType())
    {
        return new UInt64ToPtrConversion(argType, paramType, context);
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
    otava::intermediate::Type* irType = static_cast<otava::intermediate::Type*>(GetIrType(emitter, ptrType, sourcePos, context));
    otava::intermediate::Value* defaultValue = irType->DefaultValue();
    otava::intermediate::Value* equal = emitter.EmitEqual(value, defaultValue);
    otava::intermediate::Value* notEqual = emitter.EmitNot(equal);
    emitter.Stack().Push(notEqual);
}

class PtrToBooleanArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context) override;
};

FunctionSymbol* PtrToBooleanArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context)
{
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::boolType);
    if (argType->IsPointerType() && TypesEqual(paramType, boolType))
    {
        return new PtrToBooleanConversion(argType, paramType, context);
    }
    return nullptr;
}

ArgumentConversionTable::ArgumentConversionTable()
{
    AddArgumentConversion(new IdentityArgumentConversion());
    AddArgumentConversion(new DerivedToBaseArgumentConversion());
    AddArgumentConversion(new NullPtrToPtrArgumentConversion());
    AddArgumentConversion(new VoidPtrToPtrArgumentConversion());
    AddArgumentConversion(new PtrToVoidPtrArgumentConversion());
    AddArgumentConversion(new PtrToUInt64ArgumentConversion());
    AddArgumentConversion(new UInt64ToPtrArgumentConversion());
    AddArgumentConversion(new PtrToBooleanArgumentConversion());
}

void ArgumentConversionTable::AddArgumentConversion(ArgumentConversion* argumentConversion)
{
    argumentConversions.push_back(std::unique_ptr<ArgumentConversion>(argumentConversion));
}

FunctionSymbol* ArgumentConversionTable::GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, Context* context)
{
    FunctionSymbol* conversion = context->GetSymbolTable()->GetConversionTable().GetConversion(paramType, argType);
    if (conversion)
    {
        return conversion;
    }
    for (const auto& argumentConversion : argumentConversions)
    {
        FunctionSymbol* conversionFunction = argumentConversion->Get(paramType, argType, context);
        if (conversionFunction)
        {
            conversionFunctions.push_back(std::unique_ptr<FunctionSymbol>(conversionFunction));
            return conversionFunction;
        }
    }
    return nullptr;
}

} // namespace otava::symbols

