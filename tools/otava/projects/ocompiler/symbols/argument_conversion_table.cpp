// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.argument.conversion.table;

import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.classes;
import otava.symbols.class_templates;
import otava.symbols.conversion.table;
import otava.symbols.error;
import otava.symbols.function.type.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.operation.repository;
import otava.symbols.type_compare;
import otava.symbols.fundamental.type.conversion;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.emitter;
import otava.symbols.array.type.symbol;
import otava.symbols.enums;
import otava.symbols.overload.resolution;
import otava.symbols.type_compare;
import otava.symbols.type.symbol;
import otava.intermediate.data;
import util;

namespace otava::symbols {

class IdentityConversion : public FunctionSymbol
{
public:
    IdentityConversion(TypeSymbol* type_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return type; }
    TypeSymbol* ConversionArgType() const override { return type; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    std::int32_t ConversionDistance() const override { return 0; }
    bool IsIdentityConversion() const override { return true; }
private:
    TypeSymbol* type;
};

IdentityConversion::IdentityConversion(TypeSymbol* type_, Context* context) : FunctionSymbol(U"@conversion"), type(type_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", type);
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(type, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> IdentityConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    return std::expected<bool, int>(true);
}

class IdentityArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> IdentityArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch,
    FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<TypeSymbol*, int> pa = argType->PlainType(context);
    if (!pa) return std::unexpected<int>(pa.error());
    std::expected<TypeSymbol*, int> pp = paramType->PlainType(context);
    if (!pp) return std::unexpected<int>(pp.error());
    if (TypesEqual(*pa, *pp, context))
    {
        FunctionSymbol* fn = new IdentityConversion(argType, context);
        if (!fn->Valid())
        {
            return std::unexpected<int>(fn->GetError());
        }
        return std::expected<FunctionSymbol*, int>(fn);
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class DerivedToBaseConversion : public FunctionSymbol
{
public:
    DerivedToBaseConversion(TypeSymbol* derivedTypePtr_, TypeSymbol* baseTypePtr_, int distance_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsDerivedToBaseConversion() const override { return true; }
    TypeSymbol* ConversionParamType() const override { return baseTypePtr; }
    TypeSymbol* ConversionArgType() const override { return derivedTypePtr; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    std::int32_t ConversionDistance() const override { return distance; }
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
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(baseTypePtr, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> DerivedToBaseConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    ClassTypeSymbol* derivedClassType = nullptr;
    ClassTypeSymbol* baseClassType = nullptr;
    if (derivedTypePtr->GetBaseType()->IsClassTypeSymbol() && baseTypePtr->GetBaseType()->IsClassTypeSymbol())
    {
        derivedClassType = static_cast<ClassTypeSymbol*>(derivedTypePtr->GetBaseType());
        baseClassType = static_cast<ClassTypeSymbol*>(baseTypePtr->GetBaseType());
    }
    else
    {
        return Error("class pointer types expected", sourcePos, context);
    }
    std::expected<std::int64_t, int> p = Delta(derivedClassType, baseClassType, emitter, context);
    if (!p)
    {
        return Error("classes have no inheritance relationship", sourcePos, context);
    }
    std::int64_t delta = *p;
    otava::intermediate::Value* classPtr = emitter.Stack().Pop();
    otava::intermediate::Value* deltaValue = emitter.EmitLong(delta);
    std::expected<otava::intermediate::Type*, int> irv = baseTypePtr->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    std::expected<otava::intermediate::Value*, int> crv = emitter.EmitClassPtrConversion(classPtr, deltaValue, *irv);
    if (crv) return std::unexpected<int>(crv.error());
    emitter.Stack().Push(*crv);
    return std::expected<bool, int>(true);
}

class DerivedToBaseArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int>  DerivedToBaseArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    int distance = 0;
    if ((paramType->PointerCount() == 1 && argType->PointerCount() == 1 ||
        paramType->IsReferenceType() && paramType->PointerCount() == 0 && argType->IsReferenceType() && argType->PointerCount() == 0) &&
        argType->GetBaseType()->HasBaseClass(paramType->GetBaseType(), distance, context))
    {
        FunctionSymbol* fn = new DerivedToBaseConversion(argType, paramType, distance, context);
        return std::expected<FunctionSymbol*, int>(fn);
    }
    if (argType->GetBaseType()->HasBaseClass(paramType->GetBaseType(), distance, context))
    {
        if (paramType->IsReferenceType())
        {
            argumentMatch.preConversionFlags = OperationFlags::addr;
        }
        FunctionSymbol* fn = new DerivedToBaseConversion(argType, paramType, distance, context);
        if (!fn->Valid())
        {
            return std::unexpected<int>(fn->GetError());
        }
        return std::expected<FunctionSymbol*, int>(fn);
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class BaseToDerivedConversion : public FunctionSymbol
{
public:
    BaseToDerivedConversion(TypeSymbol* baseTypePtr_, TypeSymbol* derivedTypePtr_, int distance_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return derivedTypePtr; }
    TypeSymbol* ConversionArgType() const override { return baseTypePtr; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    std::int32_t ConversionDistance() const override { return distance; }
private:
    TypeSymbol* baseTypePtr;
    TypeSymbol* derivedTypePtr;
    int distance;
};

BaseToDerivedConversion::BaseToDerivedConversion(TypeSymbol* baseTypePtr_, TypeSymbol* derivedTypePtr_, int distance_, Context* context) :
    FunctionSymbol(U"@conversion"), baseTypePtr(baseTypePtr_), derivedTypePtr(derivedTypePtr_), distance(distance_)
{
    SetConversion();
    SetConversionKind(ConversionKind::explicitConversion);
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", baseTypePtr);
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(derivedTypePtr, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> BaseToDerivedConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    ClassTypeSymbol* baseClassType = nullptr;
    ClassTypeSymbol* derivedClassType = nullptr;
    if (baseTypePtr->GetBaseType()->IsClassTypeSymbol() && derivedTypePtr->GetBaseType()->IsClassTypeSymbol())
    {
        baseClassType = static_cast<ClassTypeSymbol*>(baseTypePtr->GetBaseType());
        derivedClassType = static_cast<ClassTypeSymbol*>(derivedTypePtr->GetBaseType());
    }
    else
    {
        return Error("class pointer types expected", sourcePos, context);
    }
    std::expected<std::int64_t, int> p = Delta(baseClassType, derivedClassType, emitter, context);
    if (!p)
    {
        return Error("classes have no inheritance relationship", sourcePos, context);
    }
    std::int64_t delta = *p;
    otava::intermediate::Value* classPtr = emitter.Stack().Pop();
    otava::intermediate::Value* deltaValue = emitter.EmitLong(delta);
    std::expected<otava::intermediate::Type*, int> irv = derivedTypePtr->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    std::expected<otava::intermediate::Value*, int> crv = emitter.EmitClassPtrConversion(classPtr, deltaValue, *irv);
    if (!crv) return std::unexpected<int>(crv.error());
    emitter.Stack().Push(*crv);
    return std::expected<bool, int>(true);
}

class BaseToDerivedArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int>  Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> BaseToDerivedArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    int distance = 0;
    if ((paramType->PointerCount() == 1 && argType->PointerCount() == 1 ||
        paramType->IsReferenceType() && paramType->PointerCount() == 0 &&
        argType->IsReferenceType() && argType->PointerCount() == 0) &&
        paramType->GetBaseType()->HasBaseClass(argType->GetBaseType(), distance, context))
    {
        distance += 100;
        FunctionSymbol* fn = new BaseToDerivedConversion(argType, paramType, distance, context);
        if (!fn->Valid())
        {
            return std::unexpected<int>(fn->GetError());
        }
        return std::expected<FunctionSymbol*, int>(fn);
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class NullPtrToPtrConversion : public FunctionSymbol
{
public:
    NullPtrToPtrConversion(TypeSymbol* argType_, TypeSymbol* pointerType_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return pointerType; }
    TypeSymbol* ConversionArgType() const override { return argType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    std::int32_t ConversionDistance() const override { return 1; }
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
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(pointerType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> NullPtrToPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    std::expected<otava::intermediate::Type*, int> irv = pointerType->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    emitter.Stack().Push(emitter.EmitBitcast(value, *irv));
    return std::expected<bool, int>(true);
}

class NullPtrToPtrArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int>  NullPtrToPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (argType->IsNullPtrType() && paramType->IsPointerType())
    {
        FunctionSymbol* fn = new NullPtrToPtrConversion(argType, paramType, context);
        if (!fn->Valid())
        {
            return std::unexpected<int>(fn->GetError());
        }
        return std::expected<FunctionSymbol*, int>(fn);
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class VoidPtrToPtrConversion : public FunctionSymbol
{
public:
    VoidPtrToPtrConversion(TypeSymbol* voidPtrType_, TypeSymbol* targetPointerType_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return targetPointerType; }
    TypeSymbol* ConversionArgType() const override { return voidPtrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    std::int32_t ConversionDistance() const override { return 255; }
private:
    TypeSymbol* voidPtrType;
    TypeSymbol* targetPointerType;
};

VoidPtrToPtrConversion::VoidPtrToPtrConversion(TypeSymbol* voidPtrType_, TypeSymbol* targetPointerType_, Context* context) :
    FunctionSymbol(U"@conversion"), voidPtrType(voidPtrType_), targetPointerType(targetPointerType_)
{
    SetConversion();
    SetConversionKind(ConversionKind::explicitConversion);
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", voidPtrType);
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(targetPointerType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> VoidPtrToPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    std::expected<otava::intermediate::Type*, int> irv = targetPointerType->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    emitter.Stack().Push(emitter.EmitBitcast(value, *irv));
    return std::expected<bool, int>(true);
}

class VoidPtrToPtrArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> VoidPtrToPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (argType->IsPointerType() && argType->PointerCount() == 1 && argType->GetBaseType()->IsVoidType() && paramType->IsPointerType())
    {
        FunctionSymbol* fn = new VoidPtrToPtrConversion(argType, paramType, context);
        if (!fn->Valid())
        {
            return std::unexpected<int>(fn->GetError());
        }
        return std::expected<FunctionSymbol*, int>(fn);
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class PtrToVoidPtrConversion : public FunctionSymbol
{
public:
    PtrToVoidPtrConversion(TypeSymbol* ptrType_, TypeSymbol* voidPtrType_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return voidPtrType; }
    TypeSymbol* ConversionArgType() const override { return ptrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    std::int32_t ConversionDistance() const override { return 10; }
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
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(voidPtrType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> PtrToVoidPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    std::expected<otava::intermediate::Type*, int> irv = voidPtrType->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    emitter.Stack().Push(emitter.EmitBitcast(value, *irv));
    return std::expected<bool, int>(true);
}

class PtrToVoidPtrArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> PtrToVoidPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (argType->IsPointerType() && paramType->IsPointerType() && paramType->PointerCount() == 1 && paramType->GetBaseType()->IsVoidType())
    {
        FunctionSymbol* fn = new PtrToVoidPtrConversion(argType, paramType, context);
        if (!fn->Valid())
        {
            return std::unexpected<int>(fn->GetError());
        }
        return std::expected<FunctionSymbol*, int>(fn);
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class PtrToPtrConversion : public FunctionSymbol
{
public:
    PtrToPtrConversion(TypeSymbol* sourcePtrType_, TypeSymbol* targetPtrType_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return targetPtrType; }
    TypeSymbol* ConversionArgType() const override { return sourcePtrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    std::int32_t ConversionDistance() const override { return 255; }
private:
    TypeSymbol* sourcePtrType;
    TypeSymbol* targetPtrType;
};

PtrToPtrConversion::PtrToPtrConversion(TypeSymbol* sourcePtrType_, TypeSymbol* targetPtrType_, Context* context) :
    FunctionSymbol(U"@conversion"), sourcePtrType(sourcePtrType_), targetPtrType(targetPtrType_)
{
    SetConversion();
    SetConversionKind(ConversionKind::explicitConversion);
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", sourcePtrType);
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(targetPtrType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> PtrToPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    std::expected<otava::intermediate::Type*, int> irv = targetPtrType->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    emitter.Stack().Push(emitter.EmitBitcast(value, *irv));
    return std::expected<bool, int>(true);
}

class ReinterpretCastArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> ReinterpretCastArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (context->GetFlag(ContextFlags::reinterpretCast))
    {
        if (argType->IsPointerType() && paramType->IsPointerType() && argType->PointerCount() == 1 && paramType->PointerCount() == 1)
        {
            FunctionSymbol* fn = new PtrToPtrConversion(argType, paramType, context);
            if (!fn->Valid())
            {
                return std::unexpected<int>(fn->GetError());
            }
            return std::expected<FunctionSymbol*, int>(fn);
        }
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class VoidPtrToUInt64Conversion : public FunctionSymbol
{
public:
    VoidPtrToUInt64Conversion(TypeSymbol* ptrType_, TypeSymbol* uint64Type_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return uint64Type; }
    TypeSymbol* ConversionArgType() const override { return ptrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    std::int32_t ConversionDistance() const override { return 255; }
private:
    TypeSymbol* ptrType;
    TypeSymbol* uint64Type;
};

VoidPtrToUInt64Conversion::VoidPtrToUInt64Conversion(TypeSymbol* ptrType_, TypeSymbol* uint64Type_, Context* context) :
    FunctionSymbol(U"@conversion"), ptrType(ptrType_), uint64Type(uint64Type_)
{
    SetConversion();
    SetConversionKind(ConversionKind::explicitConversion);
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", ptrType);
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(uint64Type, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> VoidPtrToUInt64Conversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    std::expected<otava::intermediate::Type*, int> irv = uint64Type->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    emitter.Stack().Push(emitter.EmitPtrToInt(value, *irv));
    return std::expected<bool, int>(true);
}

class VoidPtrToUInt64ArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> VoidPtrToUInt64ArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<TypeSymbol*, int> rv = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::unsignedLongLongIntType);
    if (!rv) return std::unexpected<int>(rv.error());
    TypeSymbol* uint64Type = *rv;
    std::expected<TypeSymbol*, int> pa = argType->PlainType(context);
    if (!pa) return std::unexpected<int>(pa.error());
    TypeSymbol* plainArgType = *pa;
    std::expected<TypeSymbol*, int> pp = paramType->PlainType(context);
    if (!pp) return std::unexpected<int>(pp.error());
    if (plainArgType->IsVoidPtrType() && TypesEqual(*pp, uint64Type, context))
    {
        FunctionSymbol* fn = new VoidPtrToUInt64Conversion(argType, paramType, context);
        if (!fn->Valid())
        {
            return std::unexpected<int>(fn->GetError());
        }
        return std::expected<FunctionSymbol*, int>(fn);
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class UInt64ToVoidPtrConversion : public FunctionSymbol
{
public:
    UInt64ToVoidPtrConversion(TypeSymbol* uint64Type_, TypeSymbol* ptrType_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return ptrType; }
    TypeSymbol* ConversionArgType() const override { return uint64Type; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    std::int32_t ConversionDistance() const override { return 255; }
private:
    TypeSymbol* uint64Type;
    TypeSymbol* ptrType;
};

UInt64ToVoidPtrConversion::UInt64ToVoidPtrConversion(TypeSymbol* uint64Type_, TypeSymbol* ptrType_, Context* context) :
    FunctionSymbol(U"@conversion"), uint64Type(uint64Type), ptrType(ptrType_)
{
    SetConversion();
    SetConversionKind(ConversionKind::explicitConversion);
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", uint64Type);
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), nullptr);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(ptrType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> UInt64ToVoidPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    std::expected<otava::intermediate::Type*, int> irv = ptrType->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    emitter.Stack().Push(emitter.EmitIntToPtr(value, *irv));
    return std::expected<bool, int>(true);
}

class UInt64ToVoidPtrArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> UInt64ToVoidPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<TypeSymbol*, int> rv = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::unsignedLongLongIntType);
    if (!rv) return std::unexpected<int>(rv.error());
    TypeSymbol* uint64Type = *rv;
    if (TypesEqual(argType, uint64Type, context) && paramType->IsVoidPtrType())
    {
        FunctionSymbol* fn = new UInt64ToVoidPtrConversion(argType, paramType, context);
        if (!fn->Valid())
        {
            return std::unexpected<int>(fn->GetError());
        }
        return std::expected<FunctionSymbol*, int>(fn);
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class PtrToBooleanConversion : public FunctionSymbol
{
public:
    PtrToBooleanConversion(TypeSymbol* ptrType_, TypeSymbol* boolType_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return boolType; }
    TypeSymbol* ConversionArgType() const override { return ptrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    std::int32_t ConversionDistance() const override { return 1; }
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
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), nullptr);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(boolType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> PtrToBooleanConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    std::expected<otava::intermediate::Type*, int> irv = ptrType->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    otava::intermediate::Type* irType = *irv;
    otava::intermediate::Value* defaultValue = irType->DefaultValue();
    otava::intermediate::Value* equal = emitter.EmitEqual(value, defaultValue);
    otava::intermediate::Value* notEqual = emitter.EmitNot(equal);
    emitter.Stack().Push(notEqual);
    return std::expected<bool, int>(true);
}

class PtrToBooleanArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> PtrToBooleanArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (context->GetFlag(ContextFlags::skipFirstPtrToBooleanConversion) && context->ArgIndex() == 0)
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    std::expected<TypeSymbol*, int> rv = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::boolType);
    if (!rv) return std::unexpected<int>(rv.error());
    TypeSymbol* boolType = *rv;
    if (argType->IsPointerType() && TypesEqual(paramType, boolType, context))
    {
        FunctionSymbol* fn = new PtrToBooleanConversion(argType, paramType, context);
        if (!fn->Valid())
        {
            return std::unexpected<int>(fn->GetError());
        }
        return std::expected<FunctionSymbol*, int>(fn);
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class ArrayToPtrConversion : public FunctionSymbol
{
public:
    ArrayToPtrConversion(ArrayTypeSymbol* arrayType_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return elementPtrType; }
    TypeSymbol* ConversionArgType() const override { return arrayPtrType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    std::int32_t ConversionDistance() const override { return 1; }
private:
    ArrayTypeSymbol* arrayType;
    TypeSymbol* arrayPtrType;
    TypeSymbol* elementPtrType;
};

ArrayToPtrConversion::ArrayToPtrConversion(ArrayTypeSymbol* arrayType_, Context* context) :
    FunctionSymbol(U"@conversion"), arrayType(arrayType_), arrayPtrType(nullptr), elementPtrType(nullptr)
{
    std::expected<TypeSymbol*, int> pt = arrayType->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    arrayPtrType = *pt;
    pt = arrayType->ElementType()->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", arrayPtrType);
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), nullptr);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    elementPtrType = *pt;
    rv = SetReturnType(elementPtrType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> ArrayToPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* arrayPtr = emitter.Stack().Pop();
    std::expected<otava::intermediate::Value*, int> rv = emitter.EmitElemAddr(arrayPtr, emitter.EmitLong(0));
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* elemAddr = *rv;
    emitter.Stack().Push(elemAddr);
    return std::expected<bool, int>(true);
}

class ArrayToPtrArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> ArrayToPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    bool addAddr = false;
    if (argType->IsArrayTypeSymbol())
    {
        addAddr = true;
        std::expected<TypeSymbol*, int> rv = argType->AddPointer(context);
        if (!rv) return std::unexpected<int>(rv.error());
        argType = *rv;
    }
    std::expected<TypeSymbol*, int> pt = argType->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* type = *pt;
    if (type->IsArrayTypeSymbol())
    {
        ArrayTypeSymbol* arrayType = static_cast<ArrayTypeSymbol*>(type);
        pt = arrayType->ElementType()->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* elementType = *pt;
        pt = paramType->RemoveConst(context);
        if (!pt) return std::unexpected<int>(pt.error());
        if (TypesEqual(*pt, elementType, context))
        {
            if (addAddr)
            {
                argumentMatch.preConversionFlags = OperationFlags::addr;
            }
            FunctionSymbol* fn = new ArrayToPtrConversion(arrayType, context);
            if (!fn->Valid())
            {
                return std::unexpected<int>(fn->GetError());
            }
            return std::expected<FunctionSymbol*, int>(fn);
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
                    FunctionSymbol* fn = new ArrayToPtrConversion(arrayType, context);
                    if (!fn->Valid())
                    {
                        return std::unexpected<int>(fn->GetError());
                    }
                    return std::expected<FunctionSymbol*, int>(fn);
                }
                else if (FindClassTemplateMatch(elementType, paramType, arg, tempFunctionMatch, sourcePos, context))
                {
                    if (addAddr)
                    {
                        argumentMatch.preConversionFlags = OperationFlags::addr;
                    }
                    FunctionSymbol* fn = new ArrayToPtrConversion(arrayType, context);
                    if (!fn->Valid())
                    {
                        return std::unexpected<int>(fn->GetError());
                    }
                    return std::expected<FunctionSymbol*, int>(fn);
                }
                else if (FindClassTemplateSpecializationMatch(elementType, paramType, arg, tempFunctionMatch, sourcePos, context))
                {
                    if (addAddr)
                    {
                        argumentMatch.preConversionFlags = OperationFlags::addr;
                    }
                    FunctionSymbol* fn = new ArrayToPtrConversion(arrayType, context);
                    if (!fn->Valid())
                    {
                        return std::unexpected<int>(fn->GetError());
                    }
                    return std::expected<FunctionSymbol*, int>(fn);
                }
            }
        }
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class EnumTypeToUnderlyingTypeConversion : public FunctionSymbol
{
public:
    EnumTypeToUnderlyingTypeConversion(EnumeratedTypeSymbol* enumType_, TypeSymbol* underlyingType_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return underlyingType; }
    TypeSymbol* ConversionArgType() const override { return enumType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    std::int32_t ConversionDistance() const override { return 100; }
private:
    EnumeratedTypeSymbol* enumType;
    TypeSymbol* underlyingType;
};

EnumTypeToUnderlyingTypeConversion::EnumTypeToUnderlyingTypeConversion(EnumeratedTypeSymbol* enumType_, TypeSymbol* underlyingType_, Context* context) :
    FunctionSymbol(U"@conversion"), enumType(enumType_), underlyingType(underlyingType_)
{
    SetConversion();
    SetAccess(Access::public_);
    SetConversionKind(ConversionKind::explicitConversion);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", enumType);
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(underlyingType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> EnumTypeToUnderlyingTypeConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    std::expected<otava::intermediate::Type*, int> irv = underlyingType->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    emitter.Stack().Push(emitter.EmitBitcast(value, *irv));
    return std::expected<bool, int>(true);
}

class EnumTypeToUnderlyingTypeArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> EnumTypeToUnderlyingTypeArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (argType->IsEnumeratedTypeSymbol())
    {
        EnumeratedTypeSymbol* enumType = static_cast<EnumeratedTypeSymbol*>(argType);
        TypeSymbol* underlyingType = enumType->UnderlyingType();
        if (!underlyingType)
        {
            std::expected<TypeSymbol*, int> rv = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType);
            if (!rv) return std::unexpected<int>(rv.error());
            underlyingType = *rv;
        }
        std::expected<TypeSymbol*, int> dt = underlyingType->DirectType(context);
        if (!dt) return std::unexpected<int>(dt.error());
        TypeSymbol* directType = *dt;
        std::expected<TypeSymbol*, int> rv = directType->FinalType(sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        underlyingType = *rv;
        if (TypesEqual(paramType, underlyingType, context))
        {
            FunctionSymbol* fn = new EnumTypeToUnderlyingTypeConversion(enumType, underlyingType, context);
            if (!fn->Valid())
            {
                return std::unexpected<int>(fn->GetError());
            }
            return std::expected<FunctionSymbol*, int>(fn);
        }
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class UnderlyingTypeToEnumTypeConversion : public FunctionSymbol
{
public:
    UnderlyingTypeToEnumTypeConversion(EnumeratedTypeSymbol* enumType_, TypeSymbol* underlyingType_, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return enumType; }
    TypeSymbol* ConversionArgType() const override { return underlyingType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::explicitConversion; }
    std::int32_t ConversionDistance() const override { return 255; }
private:
    EnumeratedTypeSymbol* enumType;
    TypeSymbol* underlyingType;
};

UnderlyingTypeToEnumTypeConversion::UnderlyingTypeToEnumTypeConversion(EnumeratedTypeSymbol* enumType_, TypeSymbol* underlyingType_, Context* context) :
    FunctionSymbol(U"@conversion"), enumType(enumType_), underlyingType(underlyingType_)
{
    SetConversion();
    SetAccess(Access::public_);
    SetConversionKind(ConversionKind::explicitConversion);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", underlyingType);
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(enumType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> UnderlyingTypeToEnumTypeConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    std::expected<otava::intermediate::Type*, int> irv = enumType->IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    emitter.Stack().Push(emitter.EmitBitcast(value, *irv));
    return std::expected<bool, int>(true);
}

class UnderlyingTypeEnumTypeToArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> UnderlyingTypeEnumTypeToArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (paramType->IsEnumeratedTypeSymbol())
    {
        EnumeratedTypeSymbol* enumType = static_cast<EnumeratedTypeSymbol*>(paramType);
        TypeSymbol* underlyingType = enumType->UnderlyingType();
        if (!underlyingType)
        {
            std::expected<TypeSymbol*, int> rv = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::intType);
            if (!rv) return std::unexpected<int>(rv.error());
            underlyingType = *rv;
        }
        std::expected<TypeSymbol*, int> dt = underlyingType->DirectType(context);
        if (!dt) return std::unexpected<int>(dt.error());
        TypeSymbol* directType = *dt;
        std::expected<TypeSymbol*, int> rv = directType->FinalType(sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        underlyingType = *rv;
        if (TypesEqual(argType, underlyingType, context))
        {
            FunctionSymbol* fn = new UnderlyingTypeToEnumTypeConversion(enumType, underlyingType, context);
            if (!fn->Valid())
            {
                return std::unexpected<int>(fn->GetError());
            }
            return std::expected<FunctionSymbol*, int>(fn);
        }
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

class FunctionToFunctionPtrConversion : public FunctionSymbol
{
public:
    FunctionToFunctionPtrConversion(TypeSymbol* functionPtrType_, FunctionSymbol* function_, int32_t distance_, Context* context);
    TypeSymbol* ConversionParamType() const override { return functionPtrType; }
    TypeSymbol* ConversionArgType() const override { return functionType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    std::int32_t ConversionDistance() const override { return distance; }
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* functionPtrType;
    TypeSymbol* functionType;
    FunctionSymbol* function;
    std::int32_t distance;
};

FunctionToFunctionPtrConversion::FunctionToFunctionPtrConversion(TypeSymbol* functionPtrType_, FunctionSymbol* function_, int32_t distance_, Context* context) :
    FunctionSymbol(U"@conversion"), functionPtrType(functionPtrType_), functionType(function_->GetFunctionType(context)), function(function_), distance(distance_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", functionType);
    std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(functionPtrType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> FunctionToFunctionPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    std::expected<std::string, int> is = function->IrName(context);
    if (!is) return std::unexpected<int>(is.error());
    std::expected<std::string, int> rv = util::ToUtf8(*is);
    if (!rv) return std::unexpected<int>(rv.error());
    std::string irName = std::move(*rv);
    std::expected<otava::intermediate::Type*, int> trv = function->IrType(emitter, sourcePos, context);
    if (trv) return std::unexpected<int>(trv.error());
    otava::intermediate::Type* irType = *trv;
    std::expected<otava::intermediate::Function*, int> frv = emitter.GetOrInsertFunction(irName, static_cast<otava::intermediate::FunctionType*>(irType));
    if (!frv) return std::unexpected<int>(frv.error());
    otava::intermediate::Function* fn = *frv;
    emitter.Stack().Push(fn);
    return std::expected<bool, int>(true);
};

class FunctionToFunctionPtrArgumentConversion : public ArgumentConversion
{
public:
    std::expected<FunctionSymbol*, int> Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, ArgumentMatch& argumentMatch, 
        FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

std::expected<FunctionSymbol*, int> FunctionToFunctionPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg, 
    ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (paramType->IsFunctionPtrType() && argType->IsFunctionGroupTypeSymbol())
    {
        FunctionTypeSymbol* functionType = static_cast<FunctionTypeSymbol*>(paramType->GetBaseType());
        FunctionGroupTypeSymbol* functionGroupType = static_cast<FunctionGroupTypeSymbol*>(argType);
        FunctionGroupSymbol* functionGroup = functionGroupType->FunctionGroup();
        for (FunctionSymbol* functionSymbol : functionGroup->Functions())
        {
            int n = functionType->ParameterTypes().size();
            if (functionSymbol->Parameters().size() == n)
            {
                bool found = true;
                for (int i = 0; i < n; ++i)
                {
                    auto t = functionType->ParameterTypes()[i]->DirectType(context);
                    if (!t) return std::unexpected<int>(t.error());
                    TypeSymbol* leftType = *t;
                    t = leftType->FinalType(sourcePos, context);
                    if (!t) return std::unexpected<int>(t.error());
                    leftType = *t;
                    t = functionSymbol->Parameters()[i]->GetType()->DirectType(context);
                    TypeSymbol* rightType = *t;
                    t = rightType->FinalType(sourcePos, context);
                    if (!t) return std::unexpected<int>(t.error());
                    rightType = *t;
                    std::expected<FunctionSymbol*, int> rv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                        leftType, rightType, sourcePos, context);
                    if (!rv) return rv;
                    FunctionSymbol* conversion = *rv;
                    if (!conversion)
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    auto t = functionType->ReturnType()->DirectType(context);
                    if (!t) return std::unexpected<int>(t.error());
                    TypeSymbol* leftType = *t;
                    t = leftType->FinalType(sourcePos, context);
                    if (!t) return std::unexpected<int>(t.error());
                    leftType = *t;
                    t = functionSymbol->ReturnType()->DirectType(context);
                    TypeSymbol* rightType = *t;
                    t = rightType->FinalType(sourcePos, context);
                    if (!t) return std::unexpected<int>(t.error());
                    rightType = *t;
                    std::expected<FunctionSymbol*, int> rv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                        leftType, rightType, sourcePos, context);
                    if (!rv) return rv;
                    FunctionSymbol* conversion = *rv;
                    if (conversion)
                    {
                        FunctionSymbol* fn = new FunctionToFunctionPtrConversion(paramType, functionSymbol, 1 + conversion->ConversionDistance(), context);
                        if (!fn->Valid())
                        {
                            return std::unexpected<int>(fn->GetError());
                        }
                        return std::expected<FunctionSymbol*, int>(fn);
                    }
                }
            }
        }
        for (FunctionSymbol* functionDefinitionSymbol : functionGroup->Definitions())
        {
            int n = functionType->ParameterTypes().size();
            if (functionDefinitionSymbol->Parameters().size() == n)
            {
                bool found = true;
                for (int i = 0; i < n; ++i)
                {
                    auto t = functionType->ParameterTypes()[i]->DirectType(context);
                    if (!t) return std::unexpected<int>(t.error());
                    TypeSymbol* leftType = *t;
                    t = leftType->FinalType(sourcePos, context);
                    if (!t) return std::unexpected<int>(t.error());
                    leftType = *t;
                    t = functionDefinitionSymbol->Parameters()[i]->GetType()->DirectType(context);
                    TypeSymbol* rightType = *t;
                    t = rightType->FinalType(sourcePos, context);
                    if (!t) return std::unexpected<int>(t.error());
                    rightType = *t;
                    std::expected<FunctionSymbol*, int> rv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                        leftType, rightType, sourcePos, context);
                    if (!rv) return rv;
                    FunctionSymbol* conversion = *rv;
                    if (!conversion)
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    auto t = functionType->ReturnType()->DirectType(context);
                    if (!t) return std::unexpected<int>(t.error());
                    TypeSymbol* leftType = *t;
                    t = leftType->FinalType(sourcePos, context);
                    if (!t) return std::unexpected<int>(t.error());
                    leftType = *t;
                    t = functionDefinitionSymbol->ReturnType()->DirectType(context);
                    TypeSymbol* rightType = *t;
                    t = rightType->FinalType(sourcePos, context);
                    if (!t) return std::unexpected<int>(t.error());
                    rightType = *t;
                    std::expected<FunctionSymbol*, int> rv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                        leftType, rightType, sourcePos, context);
                    if (!rv) return rv;
                    FunctionSymbol* conversion = *rv;
                    if (conversion)
                    {
                        if (functionDefinitionSymbol->IsTemplate())
                        {
                            std::expected<FunctionSymbol*, int> fdef = InstantiateFunctionTemplate(functionDefinitionSymbol, functionMatch.templateParameterMap, 
                                sourcePos, context);
                            if (!fdef) return std::unexpected<int>(fdef.error());
                            functionDefinitionSymbol = *fdef;
                        }
                        FunctionSymbol* fn = new FunctionToFunctionPtrConversion(paramType, functionDefinitionSymbol, 1 + conversion->ConversionDistance(), context);
                        if (!fn->Valid())
                        {
                            return std::unexpected<int>(fn->GetError());
                        }
                        return std::expected<FunctionSymbol*, int>(fn);
                    }
                }
            }
        }
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
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
    AddArgumentConversion(new FunctionToFunctionPtrArgumentConversion());
}

void ArgumentConversionTable::AddArgumentConversion(ArgumentConversion* argumentConversion)
{
    argumentConversions.push_back(std::unique_ptr<ArgumentConversion>(argumentConversion));
}

std::expected<FunctionSymbol*, int> ArgumentConversionTable::GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, const soul::ast::SourcePos& sourcePos,
    Context* context)
{
    ArgumentMatch argumentMatch;
    FunctionMatch functionMatch;
    return GetArgumentConversion(paramType, argType, nullptr, sourcePos, argumentMatch, functionMatch, context);
}

std::expected<FunctionSymbol*, int> ArgumentConversionTable::GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, BoundExpressionNode* arg,
    const soul::ast::SourcePos& sourcePos, ArgumentMatch& argumentMatch, FunctionMatch& functionMatch, Context* context)
{
    FunctionSymbol* conversion = nullptr;
    if (!TypesEqual(paramType, argType, context))
    {
        std::expected<FunctionSymbol*, int> rv = context->GetSymbolTable()->GetConversionTable().GetConversion(paramType, argType, context);
        if (!rv) return rv;
        conversion = *rv;
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
        return std::expected<FunctionSymbol*, int>(conversion);
    }
    std::expected<TypeSymbol*, int> pa = argType->PlainType(context);
    if (!pa) return std::unexpected<int>(pa.error());
    TypeSymbol* plainArgType = *pa;
    if (plainArgType->IsClassTypeSymbol())
    {
        ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(argType->GetBaseType());
        if (classType->IsClassTemplateSpecializationSymbol())
        {
            ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(classType);
            TypeSymbol* classTemplateSymbol = specialization->ClassTemplate();
            if (classTemplateSymbol->IsClassTypeSymbol())
            {
                ClassTypeSymbol* classTemplate = static_cast<ClassTypeSymbol*>(classTemplateSymbol);
                FunctionSymbol* conversionFunction = classTemplate->GetConversionFunction(paramType, context);
                if (conversionFunction)
                {
                    std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
                    std::expected<FunctionSymbol*, int> rv = InstantiateMemFnOfClassTemplate(conversionFunction, specialization, templateParameterMap, sourcePos, context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    FunctionSymbol* instantiatedConversionFunction = *rv;
                    return std::expected<FunctionSymbol*, int>(instantiatedConversionFunction);
                }
            }
        }
        else
        {
            FunctionSymbol* conversionFunction = classType->GetConversionFunction(paramType, context);
            if (conversionFunction)
            {
                return std::expected<FunctionSymbol*, int>(conversionFunction);
            }
        }
    }
    for (const auto& argumentConversion : argumentConversions)
    {
        std::expected<FunctionSymbol*, int> rv = argumentConversion->Get(paramType, argType, arg, argumentMatch, functionMatch, sourcePos, context);
        if (!rv) return rv;
        FunctionSymbol* conversionFunction = *rv;
        if (conversionFunction)
        {
            conversionFunctions.push_back(std::unique_ptr<FunctionSymbol>(conversionFunction));
            return std::expected<FunctionSymbol*, int>(conversionFunction);
        }
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

} // namespace otava::symbols

