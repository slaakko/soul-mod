// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.operation.repository;

import otava.symbols.type.symbol;
import otava.symbols.bound.tree;
import otava.symbols.bound.tree.visitor;
import otava.symbols.class_group.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.function.type.symbol;
import otava.symbols.context;
import otava.symbols.emitter;
import otava.symbols.argument.conversion.table;
import otava.symbols.symbol.table;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.classes;
import otava.symbols.overload.resolution;
import otava.symbols.error;
import otava.symbols.expression.binder;
import otava.symbols.type_compare;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.ast.expression;
import util.unicode;
import util.sha1;

namespace otava::symbols {

class PointerDefaultCtor : public FunctionSymbol
{
public:
    PointerDefaultCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context);
    TypeSymbol* Type() const { return type; }
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

PointerDefaultCtor::PointerDefaultCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> PointerDefaultCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & OperationFlags::defaultInit) != OperationFlags::none)
    {
        std::expected<otava::intermediate::Type*, int> irv = type->IrType(emitter, sourcePos, context);
        if (!irv) return std::unexpected<int>(irv.error());
        otava::intermediate::Type* irType = *irv;
        emitter.Stack().Push(irType->DefaultValue());
        OperationFlags storeFlags = OperationFlags::none;
        if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
        {
            storeFlags = storeFlags | OperationFlags::deref;
        }
        std::expected<bool, int> rv = args[0]->Store(emitter, storeFlags, sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

class PointerDefaultCtorOperation : public Operation
{
public:
    PointerDefaultCtorOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
        Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerDefaultCtorOperation::PointerDefaultCtorOperation() : Operation(U"@constructor", 1)
{
}

std::expected<FunctionSymbol*, int> PointerDefaultCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    if (type->IsReferenceType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    std::expected<TypeSymbol*, int> pt = type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* pointerType = *pt;
    auto it = functionMap.find(pointerType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    PointerDefaultCtor* function = new PointerDefaultCtor(pointerType, sourcePos, context);
    if (!function->Valid()) return std::unexpected<int>(function->GetError());
    functionMap[pointerType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class PointerCopyCtor : public FunctionSymbol
{
public:
    PointerCopyCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context);
    TypeSymbol* Type() const { return type; }
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

PointerCopyCtor::PointerCopyCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    rv = AddParameter(thatParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> PointerCopyCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    if ((flags & OperationFlags::dup) != OperationFlags::none)
    {
        emitter.Stack().Dup();
    }
    OperationFlags storeFlags = OperationFlags::none;
    if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
    {
        storeFlags = storeFlags | OperationFlags::deref;
    }
    rv = args[0]->Store(emitter, storeFlags, sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

class PointerCopyCtorOperation : public Operation
{
public:
    PointerCopyCtorOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
        Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerCopyCtorOperation::PointerCopyCtorOperation() : Operation(U"@constructor", 2)
{
}

std::expected<FunctionSymbol*, int> PointerCopyCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    if (type->IsReferenceType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    std::expected<TypeSymbol*, int> pt = type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* pointerType = *pt;
    pt = pointerType->AddRValueRef(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* rvalueRefType = *pt;
    if (TypesEqual(args[1]->GetType(), rvalueRefType, context)) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    auto it = functionMap.find(pointerType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    PointerCopyCtor* function = new PointerCopyCtor(pointerType, sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    functionMap[pointerType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class PointerMoveCtor : public FunctionSymbol
{
public:
    PointerMoveCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context);
    TypeSymbol* Type() const { return type; }
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

PointerMoveCtor::PointerMoveCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = type->AddRValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* rvalueRefType = *pt;
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", rvalueRefType);
    rv = AddParameter(thatParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> PointerMoveCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* rvalueRefValue = emitter.Stack().Pop();
    std::expected<otava::intermediate::Instruction*, int> lrv = emitter.EmitLoad(rvalueRefValue);
    if (!lrv) return std::unexpected<int>(lrv.error());
    emitter.Stack().Push(*lrv);
    OperationFlags storeFlags = OperationFlags::none;
    if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
    {
        storeFlags = storeFlags | OperationFlags::deref;
    }
    rv = args[0]->Store(emitter, storeFlags, sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

class PointerMoveCtorOperation : public Operation
{
public:
    PointerMoveCtorOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerMoveCtorOperation::PointerMoveCtorOperation() : Operation(U"@constructor", 2)
{
}

std::expected<FunctionSymbol*, int> PointerMoveCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos,
    Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    if (type->IsReferenceType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    std::expected<TypeSymbol*, int> pt = type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* pointerType = *pt;
    pt = pointerType->AddRValueRef(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* rvalueRefType = *pt;
    if (!TypesEqual(args[1]->GetType(), rvalueRefType, context) && !args[1]->BindToRvalueRef())
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    auto it = functionMap.find(pointerType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    PointerMoveCtor* function = new PointerMoveCtor(pointerType, sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    functionMap[pointerType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class PointerCopyAssignment : public FunctionSymbol
{
public:
    PointerCopyAssignment(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context);
    TypeSymbol* Type() const { return type; }
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
    bool IsPointerCopyAssignment() const override { return true; }
private:
    TypeSymbol* type;
};

PointerCopyAssignment::PointerCopyAssignment(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"operator="), type(type_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    rv = AddParameter(thatParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = type->AddLValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* lvalueRefType = *pt;
    rv = SetReturnType(lvalueRefType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> PointerCopyAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    rv = args[0]->Store(emitter, OperationFlags::setPtr, sourcePos, context);
    if (!rv) return rv;
    emitter.Stack().Push(context->Ptr());
    return std::expected<bool, int>(true);
}

class PointerCopyAssignmentOperation : public Operation
{
public:
    PointerCopyAssignmentOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerCopyAssignmentOperation::PointerCopyAssignmentOperation() : Operation(U"operator=", 2)
{
}

std::expected<FunctionSymbol*, int> PointerCopyAssignmentOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    std::expected<TypeSymbol*, int> pt = type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* t = *pt;
    pt = t->RemoveReference(context);
    if (!pt) return std::unexpected<int>(pt.error());
    t = *pt;
    TypeSymbol* pointerType = t;
    pt = pointerType->AddRValueRef(context);
    if (!pt) return std::unexpected<int>(pt.error());
    t = *pt;
    if (TypesEqual(args[1]->GetType(), t, context) || args[1]->BindToRvalueRef())
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    auto it = functionMap.find(pointerType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    PointerCopyAssignment* function = new PointerCopyAssignment(pointerType, sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    functionMap[pointerType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class PointerMoveAssignment : public FunctionSymbol
{
public:
    PointerMoveAssignment(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context);
    TypeSymbol* Type() const { return type; }
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, const soul::ast::SourcePos& sourcePos, 
        Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

PointerMoveAssignment::PointerMoveAssignment(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"operator="), type(type_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = type->AddRValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* rvalueRefType = *pt;
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", rvalueRefType);
    rv = AddParameter(thatParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = type->AddLValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* lvalueRefType = *pt;
    rv = SetReturnType(lvalueRefType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> PointerMoveAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* refValue = emitter.Stack().Pop();
    std::expected<otava::intermediate::Instruction*, int> lrv = emitter.EmitLoad(refValue);
    if (!lrv) return std::unexpected<int>(lrv.error());
    emitter.Stack().Push(*lrv);
    rv = args[0]->Store(emitter, OperationFlags::setPtr, sourcePos, context);
    if (!rv) return rv;
    emitter.Stack().Push(context->Ptr());
    return std::expected<bool, int>(true);
}

class PointerMoveAssignmentOperation : public Operation
{
public:
    PointerMoveAssignmentOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerMoveAssignmentOperation::PointerMoveAssignmentOperation() : Operation(U"operator=", 2)
{
}

std::expected<FunctionSymbol*, int> PointerMoveAssignmentOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    std::expected<TypeSymbol*, int> pt = type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* tp = *pt;
    pt = tp->RemoveReference(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* pointerType = *pt;
    pt = pointerType->AddRValueRef(context);
    if (!pt) return std::unexpected<int>(pt.error());
    tp = *pt;
    if (!TypesEqual(args[1]->GetType(), tp, context) && !args[1]->BindToRvalueRef())
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    auto it = functionMap.find(pointerType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    PointerMoveAssignment* function = new PointerMoveAssignment(pointerType, sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    functionMap[pointerType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class PointerPlusOffset : public FunctionSymbol
{
public:
    PointerPlusOffset(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, const soul::ast::SourcePos& sourcePos, 
        Context* context) override;
private:
    TypeSymbol* pointerType;
    TypeSymbol* longLongIntType;
};

PointerPlusOffset::PointerPlusOffset(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"operator+"), pointerType(pointerType_), longLongIntType(longLongIntType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", pointerType);
    std::expected<bool, int> rv = AddParameter(leftParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", longLongIntType);
    rv = AddParameter(rightParam, sourcePos, context);
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

std::expected<bool, int> PointerPlusOffset::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* left = emitter.Stack().Pop();
    rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitPtrOffset(left, right));
    return std::expected<bool, int>(true);
}

class PointerPlusOffsetOperation : public Operation
{
public:
    PointerPlusOffsetOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerPlusOffsetOperation::PointerPlusOffsetOperation() : Operation(U"operator+", 2)
{
}

std::expected<FunctionSymbol*, int> PointerPlusOffsetOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    if (context->GetFlag(ContextFlags::noPtrOps)) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    std::expected<TypeSymbol*, int> pt = args[0]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* leftType = *pt;
    if (!leftType->IsPointerType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    TypeSymbol* rightType = args[1]->GetType();
    pt = rightType->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* rightPlainType = *pt;
    if (!rightPlainType->IsIntegralType())
    {
        if (!context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            rightType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context))
        {
            return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
        }
    }
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    PointerPlusOffset* function = new PointerPlusOffset(leftType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class OffsetPlusPointer : public FunctionSymbol
{
public:
    OffsetPlusPointer(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    TypeSymbol* pointerType;
    TypeSymbol* longLongIntType;
};

OffsetPlusPointer::OffsetPlusPointer(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"operator+"), pointerType(pointerType_), longLongIntType(longLongIntType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", longLongIntType);
    std::expected<bool, int> rv = AddParameter(leftParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", pointerType);
    rv = AddParameter(rightParam, sourcePos, context);
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

std::expected<bool, int> OffsetPlusPointer::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* left = emitter.Stack().Pop();
    rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitPtrOffset(right, left));
    return std::expected<bool, int>(true);
}

class OffsetPlusPointerOperation : public Operation
{
public:
    OffsetPlusPointerOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

OffsetPlusPointerOperation::OffsetPlusPointerOperation() : Operation(U"operator+", 2)
{
}

std::expected<FunctionSymbol*, int> OffsetPlusPointerOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    TypeSymbol* leftType = args[0]->GetType();
    std::expected<TypeSymbol*, int> pt = leftType->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* leftPlainType = *pt;
    if (!leftPlainType->IsIntegralType())
    {
        if (!context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            leftType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context))
        {
            return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
        }
    }
    pt = args[1]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* rightType = *pt;
    if (!rightType->IsPointerType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    OffsetPlusPointer* function = new OffsetPlusPointer(rightType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class PointerMinusOffset : public FunctionSymbol
{
public:
    PointerMinusOffset(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    TypeSymbol* pointerType;
    TypeSymbol* longLongIntType;
};

PointerMinusOffset::PointerMinusOffset(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"operator-"), pointerType(pointerType_), longLongIntType(longLongIntType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", pointerType);
    std::expected<bool, int> rv = AddParameter(leftParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", longLongIntType);
    rv = AddParameter(rightParam, sourcePos, context);
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

std::expected<bool, int> PointerMinusOffset::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* left = emitter.Stack().Pop();
    rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* right = emitter.Stack().Pop();
    otava::intermediate::Value* offset = emitter.EmitNeg(right);
    emitter.Stack().Push(emitter.EmitPtrOffset(left, offset));
    return std::expected<bool, int>(true);
}

class PointerMinusOffsetOperation : public Operation
{
public:
    PointerMinusOffsetOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerMinusOffsetOperation::PointerMinusOffsetOperation() : Operation(U"operator-", 2)
{
}

std::expected<FunctionSymbol*, int> PointerMinusOffsetOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (context->GetFlag(ContextFlags::noPtrOps)) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    std::expected<TypeSymbol*, int> pt = args[0]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* leftType = *pt;
    if (!leftType->IsPointerType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    TypeSymbol* rightType = args[1]->GetType();
    pt = rightType->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* rightPlainType = *pt;
    if (!rightPlainType->IsIntegralType())
    {
        if (!context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            rightType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context))
        {
            return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
        }
    }
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    PointerMinusOffset* function = new PointerMinusOffset(leftType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, 
        context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class PointerMinusPointer : public FunctionSymbol
{
public:
    PointerMinusPointer(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    TypeSymbol* pointerType;
    TypeSymbol* longLongIntType;
};

PointerMinusPointer::PointerMinusPointer(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"operator-"), pointerType(pointerType_), longLongIntType(longLongIntType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", pointerType);
    std::expected<bool, int> rv = AddParameter(leftParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", pointerType);
    rv = AddParameter(rightParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    rv = SetReturnType(longLongIntType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> PointerMinusPointer::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* left = emitter.Stack().Pop();
    rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitPtrDiff(left, right));
    return std::expected<bool, int>(true);
}

class PointerMinusPointerOperation : public Operation
{
public:
    PointerMinusPointerOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerMinusPointerOperation::PointerMinusPointerOperation() : Operation(U"operator-", 2)
{
}

std::expected<FunctionSymbol*, int> PointerMinusPointerOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<TypeSymbol*, int> pt = args[0]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* leftType = *pt;
    if (!leftType->IsPointerType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    pt = args[1]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* rightType = *pt;
    if (!rightType->IsPointerType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    std::expected<TypeSymbol*, int> trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType);
    if (!trv) return std::unexpected<int>(trv.error());
    PointerMinusPointer* function = new PointerMinusPointer(leftType, *trv, sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class PointerEqual : public FunctionSymbol
{
public:
    PointerEqual(TypeSymbol* pointerType_, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    TypeSymbol* pointerType;
};

PointerEqual::PointerEqual(TypeSymbol* pointerType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"operator=="), pointerType(pointerType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", pointerType);
    std::expected<bool, int> rv = AddParameter(leftParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", pointerType);
    rv = AddParameter(rightParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::expected<TypeSymbol*, int> trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    if (!trv)
    {
        SetError(trv.error());
        return;
    }
    TypeSymbol* boolType = *trv;
    rv = SetReturnType(boolType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> PointerEqual::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* left = emitter.Stack().Pop();
    rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitEqual(left, right));
    return std::expected<bool, int>(true);
}

class PointerEqualOperation : public Operation
{
public:
    PointerEqualOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerEqualOperation::PointerEqualOperation() : Operation(U"operator==", 2)
{
}

std::expected<FunctionSymbol*, int> PointerEqualOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<TypeSymbol*, int> pt = args[0]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* leftType = *pt;
    if (!leftType->IsPointerType() && !leftType->IsNullPtrType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    pt = args[1]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* rightType = *pt;
    if (!rightType->IsPointerType() && !rightType->IsNullPtrType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    PointerEqual* function = new PointerEqual(leftType, sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class PointerLess : public FunctionSymbol
{
public:
    PointerLess(TypeSymbol* pointerType_, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    TypeSymbol* pointerType;
};

PointerLess::PointerLess(TypeSymbol* pointerType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"operator<"), pointerType(pointerType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", pointerType);
    std::expected<bool, int> rv = AddParameter(leftParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", pointerType);
    rv = AddParameter(rightParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::expected<TypeSymbol*, int> trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    if (!trv)
    {
        SetError(trv.error());
        return;
    }
    TypeSymbol* boolType = *trv;
    rv = SetReturnType(boolType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> PointerLess::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* left = emitter.Stack().Pop();
    rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLess(left, right));
    return std::expected<bool, int>(true);
}

class PointerLessOperation : public Operation
{
public:
    PointerLessOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerLessOperation::PointerLessOperation() : Operation(U"operator<", 2)
{
}

std::expected<FunctionSymbol*, int> PointerLessOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    std::expected<TypeSymbol*, int> pt = args[0]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* leftType = *pt;
    if (!leftType->IsPointerType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    pt = args[1]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* rightType = *pt;
    if (!rightType->IsPointerType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    PointerLess* function = new PointerLess(leftType, sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class PointerArrow : public FunctionSymbol
{
public:
    PointerArrow(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

PointerArrow::PointerArrow(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"operator->"), type(type_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* operandParam = new ParameterSymbol(U"operand", ptrType);
    std::expected<bool, int> rv = AddParameter(operandParam, sourcePos, context);
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

std::expected<bool, int> PointerArrow::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    return args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
}

class PointerArrowOperation : public Operation
{
public:
    PointerArrowOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerArrowOperation::PointerArrowOperation() : Operation(U"operator->", 1)
{
}

std::expected<FunctionSymbol*, int> PointerArrowOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    TypeSymbol* operandType = args[0]->GetType();
    if (operandType->PointerCount() <= 1) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    std::expected<TypeSymbol*, int> pt = operandType->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* type = *pt;
    auto it = functionMap.find(type);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    PointerArrow* function = new PointerArrow(type, sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    functionMap[type] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

class CopyRef : public FunctionSymbol
{
public:
    CopyRef(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

CopyRef::CopyRef(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    rv = AddParameter(thatParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error()); 
        return;
    }
}

std::expected<bool, int> CopyRef::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    rv = args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

class CopyRefOperation : public Operation
{
public:
    CopyRefOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

CopyRefOperation::CopyRefOperation() : Operation(U"@constructor", 2)
{
}

std::expected<FunctionSymbol*, int> CopyRefOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol* arg0Type = args[0]->GetType();
    if (arg0Type->PointerCount() != 1) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    std::expected<TypeSymbol*, int> pt = arg0Type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* type = *pt;
    if (!type->IsReferenceType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    TypeSymbol* argType = args[1]->GetType();
    if (!argType->IsReferenceType()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    auto it = functionMap.find(type);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    CopyRef* copyRef = new CopyRef(type, sourcePos, context);
    if (!copyRef->Valid())
    {
        return std::unexpected<int>(copyRef->GetError());
    }
    functionMap[type] = copyRef;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(copyRef)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(copyRef));
}

class ClassDefaultCtor : public FunctionDefinitionSymbol
{
public:
    ClassDefaultCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, Context* context);
    ClassTypeSymbol* ClassType() const { return classType; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassDefaultCtor::ClassDefaultCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionDefinitionSymbol(U"@class_default_ctor"), classType(classType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetGenerated();
    SetParent(classType);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> frv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType);
    if (!frv)
    {
        SetError(frv.error());
        return;
    }
    TypeSymbol* voidType = *frv;
    std::expected<bool, int> rv = SetReturnType(voidType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::expected<std::u32string, int> fname = classType->FullName();
    if (!fname)
    {
        SetError(fname.error());
        return;
    }
    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
    if (!sfname)
    {
        SetError(sfname.error()); 
        return;
    }
    std::string digestSource = *sfname;
    std::expected<std::string, int> irv = classType->IrName(context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    digestSource.append(1, '.').append(*irv);
    digestSource.append(context->GetBoundCompileUnit()->Id());
    std::expected<std::string, int> groupName = util::ToUtf8(classType->Group()->Name());
    if (!groupName)
    {
        SetError(groupName.error());
        return;
    }
    irName = "default_ctor_" + *groupName + "_" + util::GetSha1MessageDigest(digestSource);
    SetFixedIrName(irName);
}

class ClassDefaultCtorOperation : public Operation
{
public:
    ClassDefaultCtorOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<bool, int> GenerateImplementation(ClassDefaultCtor* classDefaultCtor, const soul::ast::SourcePos& sourcePos, Context* context);
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

ClassDefaultCtorOperation::ClassDefaultCtorOperation() : Operation(U"@constructor", 1)
{
}

std::expected<FunctionSymbol*, int> ClassDefaultCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    std::expected<TypeSymbol*, int> pt = type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* tp = *pt;
    pt = tp->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* plainType = *pt;
    if (type->PointerCount() != 1 || !plainType->IsClassTypeSymbol()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(type->GetBaseType());
    if (classType->IsClassTemplateSpecializationSymbol() && context->GetFlag(ContextFlags::ignoreClassTemplateSpecializations))
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    FunctionSymbol* defaultCtor = classType->GetFunctionByIndex(defaultCtorIndex);
    if (defaultCtor)
    {
        return std::expected<FunctionSymbol*, int>(defaultCtor);
    }
    if (classType->HasUserDefinedConstructor()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    auto it = functionMap.find(static_cast<TypeSymbol*>(classType));
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    ClassDefaultCtor* function = new ClassDefaultCtor(classType, sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    function->SetParent(classType);
    std::expected<bool, int> rv = GenerateImplementation(function, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    functionMap[classType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

std::expected<bool, int> ClassDefaultCtorOperation::GenerateImplementation(ClassDefaultCtor* classDefaultCtor, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ClassTypeSymbol* classType = classDefaultCtor->ClassType();
    if (!classType->ObjectLayoutComputed())
    {
        std::expected<bool, int> rv = classType->MakeObjectLayout(sourcePos, context);
        if (!rv) return rv;
    }
    std::unique_ptr<BoundFunctionNode> boundFunction(new BoundFunctionNode(classDefaultCtor, sourcePos));
    boundFunction->SetBody(new BoundCompoundStatementNode(sourcePos));
    context->PushBoundFunction(boundFunction.release());
    int nb = classType->BaseClasses().size();
    for (int i = 0; i < nb; ++i)
    {
        TypeSymbol* baseClass = classType->BaseClasses()[i];
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::expected<ParameterSymbol*, int> tp = classDefaultCtor->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, *rrv);
        std::expected<TypeSymbol*, int> pt = baseClass->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* baseClassPtrType = *pt;
        std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            baseClassPtrType, thisPtr->GetType(), sourcePos, context);
        if (!arv) return std::unexpected<int>(arv.error());
        FunctionSymbol* conversion = *arv;
        if (conversion)
        {
            std::vector<TypeSymbol*> templateArgs;
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(
                context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
            if (!orv) return std::unexpected<int>(orv.error());
            std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = std::move(*orv);
            BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
            std::expected<bool, int> rv = expressionStatement->SetExpr(boundFunctionCall.release(), sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
            context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
        }
        else
        {
            return Error("base class conversion not found", sourcePos, context);
        }
    }
    if (classType->IsPolymorphic())
    {
        std::vector<ClassTypeSymbol*> vptrHolderClasses = classType->VPtrHolderClasses();
        if (vptrHolderClasses.empty())
        {
            std::expected<std::u32string, int> fname = classType->FullName();
            if (!fname) return std::unexpected<int>(fname.error());
            std::expected<std::string, int> sfname = util::ToUtf8(*fname);
            if (!sfname) return std::unexpected<int>(sfname.error());
            return Error("no vptr holder classes for the class '" + *sfname + "'", sourcePos, context);
        }
        for (ClassTypeSymbol* vptrHolderClass : vptrHolderClasses)
        {
            if (vptrHolderClass != classType)
            {
                std::expected<ParameterSymbol*, int> tp = classDefaultCtor->ThisParam(context);
                if (!tp) return std::unexpected<int>(tp.error());
                ParameterSymbol* thisParam = *tp;
                std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
                if (!rrv) return std::unexpected<int>(rrv.error());
                BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, *rrv);
                std::expected<TypeSymbol*, int> pt = vptrHolderClass->AddPointer(context);
                if (!pt) return std::unexpected<int>(pt.error());
                std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    *pt, thisPtr->GetType(), sourcePos, context);
                if (!arv) return std::unexpected<int>(arv.error());
                FunctionSymbol* conversion = *arv;
                if (conversion)
                {
                    BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr, conversion, sourcePos);
                    BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtrConverted, classType, vptrHolderClass, sourcePos);
                    context->GetBoundFunction()->Body()->AddStatement(setVPtrStatement);
                }
                else
                {
                    return Error("vptr holder class conversion not found", sourcePos, context);
                }
            }
            else
            {
                std::expected<ParameterSymbol*, int> tp = classDefaultCtor->ThisParam(context);
                if (!tp) return std::unexpected<int>(tp.error());
                ParameterSymbol* thisParam = *tp;
                std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
                if (!rrv) return std::unexpected<int>(rrv.error());
                BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, *rrv);
                BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtr, classType, classType, sourcePos);
                context->GetBoundFunction()->Body()->AddStatement(setVPtrStatement);
            }
        }
    }
    int n = classType->MemberVariables().size();
    for (int i = 0; i < n; ++i)
    {
        VariableSymbol* memberVariableSymbol = classType->MemberVariables()[i];
        BoundVariableNode* boundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        std::expected<ParameterSymbol*, int> tp = classDefaultCtor->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
        boundMemberVariable->SetThisPtr(new BoundParameterNode(thisParam, sourcePos, *rrv));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::vector<TypeSymbol*> templateArgs;
        std::expected<TypeSymbol*, int> pt = boundMemberVariable->GetType()->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* ptrType = *pt;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundMemberVariable, sourcePos, ptrType)));
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(classType->GetScope(), U"@constructor", templateArgs, args, sourcePos, context);
        if (!orv) return std::unexpected<int>(orv.error());
        std::unique_ptr<BoundFunctionCallNode> memberConstructorCall = std::move(*orv);
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        std::expected<bool, int> rv = expressionStatement->SetExpr(memberConstructorCall.release(), sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
    }
    if (!context->GetFlag(ContextFlags::leaveBoundFunction))
    {
        std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
        if (!rv) return std::unexpected<int>(rv.error());
        context->PopBoundFunction();
    }
    if (classType->TotalMemberCount() <= inlineClassOperationsThreshold)
    {
        classDefaultCtor->SetInline();
    }
    return std::expected<bool, int>(true);
}

std::expected<FunctionDefinitionSymbol*, int> GenerateClassDefaultCtor(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::unique_ptr<ClassDefaultCtor> defaultCtor(new ClassDefaultCtor(classType, sourcePos, context));
    if (!defaultCtor->Valid())
    {
        return std::unexpected<int>(defaultCtor->GetError());
    }
    ClassDefaultCtorOperation operation;
    context->PushSetFlag(ContextFlags::leaveBoundFunction);
    std::expected<bool, int> rv = operation.GenerateImplementation(defaultCtor.get(), sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    context->PopFlags();
    return std::expected<FunctionDefinitionSymbol*, int>(static_cast<FunctionDefinitionSymbol*>(defaultCtor.release()));
}

class ClassCopyCtor : public FunctionDefinitionSymbol
{
public:
    ClassCopyCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, Context* context);
    ~ClassCopyCtor();
    ClassTypeSymbol* ClassType() const { return classType; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassCopyCtor::ClassCopyCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionDefinitionSymbol(U"@class_copy_ctor"), classType(classType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetGenerated();
    SetAccess(Access::public_);
    SetParent(classType);
    std::expected<ParameterSymbol*, int> tp = ThisParam(context);
    if (!tp)
    {
        SetError(tp.error());
        return;
    }
    ParameterSymbol* thisParam = *tp;
    std::expected<TypeSymbol*, int> pt = classType->AddConst(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* type = *pt;
    pt = type->AddLValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    type = *pt;
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    std::expected<bool, int> rv = AddParameter(thatParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::expected<TypeSymbol*, int> frv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType);
    if (!frv)
    {
        SetError(frv.error());
        return;
    }
    TypeSymbol* voidType = *frv;
    rv = SetReturnType(voidType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::expected<std::u32string, int> fname = classType->FullName();
    if (!fname)
    {
        SetError(fname.error());
        return;
    }
    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
    if (!sfname)
    {
        SetError(sfname.error());
        return;
    }
    std::string digestSource = *sfname;
    std::expected<std::string, int> irv = classType->IrName(context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    digestSource.append(1, '.').append(*irv);
    digestSource.append(context->GetBoundCompileUnit()->Id());
    std::expected<std::string, int> groupName = util::ToUtf8(classType->Group()->Name());
    if (!groupName)
    {
        SetError(groupName.error());
        return;
    }
    irName = "copy_ctor_" + *groupName + "_" + util::GetSha1MessageDigest(digestSource);
    SetFixedIrName(irName);
}

ClassCopyCtor::~ClassCopyCtor()
{
    if (classType && classType->CopyCtor() == this)
    {
        classType->ResetCopyCtor();
    }
}

class ClassCopyCtorOperation : public Operation
{
public:
    ClassCopyCtorOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<bool, int> GenerateImplementation(ClassCopyCtor* classCopyCtor, const soul::ast::SourcePos& sourcePos, Context* context);
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

ClassCopyCtorOperation::ClassCopyCtorOperation() : Operation(U"@constructor", 2)
{
}

std::expected<FunctionSymbol*, int> ClassCopyCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    std::expected<TypeSymbol*, int> pt = type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* tp = *pt;
    pt = tp->RemoveConst(context);
    if (!pt) return std::unexpected<int>(pt.error());
    tp = *pt;
    if (type->PointerCount() != 1 || !tp->IsClassTypeSymbol()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    pt = args[1]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* plainType = *pt;
    if (!plainType->IsClassTypeSymbol()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(type->GetBaseType());
    if (classType->IsClassTemplateSpecializationSymbol() && context->GetFlag(ContextFlags::ignoreClassTemplateSpecializations))
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    pt = classType->AddRValueRef(context);
    if (!pt) return std::unexpected<int>(pt.error());
    tp = *pt;
    if (TypesEqual(args[1]->GetType(), tp, context) || args[1]->BindToRvalueRef())
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    int distance = 0;
    if (!TypesEqual(args[1]->GetType()->GetBaseType(), classType, context) && !args[1]->GetType()->GetBaseType()->HasBaseClass(classType, distance, context))
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    FunctionSymbol* copyCtor = classType->GetFunctionByIndex(copyCtorIndex);
    if (copyCtor)
    {
        return std::expected<FunctionSymbol*, int>(copyCtor);
    }
    auto it = functionMap.find(static_cast<TypeSymbol*>(classType));
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    ClassCopyCtor* function = new ClassCopyCtor(classType, sourcePos, context);
    function->SetParent(classType);
    std::expected<bool, int> rv = GenerateImplementation(function, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    functionMap[classType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

std::expected<bool, int> ClassCopyCtorOperation::GenerateImplementation(ClassCopyCtor* classCopyCtor, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ClassTypeSymbol* classType = classCopyCtor->ClassType();
    if (!classType->ObjectLayoutComputed())
    {
        std::expected<bool, int> rv = classType->MakeObjectLayout(sourcePos, context);
        if (!rv) return rv;
    }
    std::unique_ptr<BoundFunctionNode> boundFunction(new BoundFunctionNode(classCopyCtor, sourcePos));
    boundFunction->SetBody(new BoundCompoundStatementNode(sourcePos));
    context->PushBoundFunction(boundFunction.release());
    int nb = classType->BaseClasses().size();
    for (int i = 0; i < nb; ++i)
    {
        TypeSymbol* baseClass = classType->BaseClasses()[i];
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::expected<ParameterSymbol*, int> tp = classCopyCtor->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, *rrv);
        std::expected<TypeSymbol*, int> pt = baseClass->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            *pt, thisPtr->GetType(), sourcePos, context);
        if (!arv) return std::unexpected<int>(arv.error());
        FunctionSymbol* conversion = *arv;
        if (conversion)
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            ParameterSymbol* thatParam = classCopyCtor->MemFunParameters(context)[1];
            if (!classCopyCtor->Valid()) return std::unexpected<int>(classCopyCtor->GetError());
            pt = baseClass->AddConst(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* tp = *pt;
            pt = tp->AddLValueRef(context);
            if (!pt) return std::unexpected<int>(pt.error());
            tp = *pt;
            arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(tp, thatParam->GetType(), sourcePos, context);
            if (!arv) return std::unexpected<int>(arv.error());
            FunctionSymbol* thatConversion = *arv;
            if (thatConversion)
            {
                BoundExpressionNode* thatPtr = new BoundParameterNode(thatParam, sourcePos, thatParam->GetType());
                args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thatPtr, thatConversion, sourcePos)));
                std::vector<TypeSymbol*> templateArgs;
                std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(
                    context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
                if (!orv) return std::unexpected<int>(orv.error());
                std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = std::move(*orv);
                BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
                std::expected<bool, int> rv = expressionStatement->SetExpr(boundFunctionCall.release(), sourcePos, context);
                if (!rv) return std::unexpected<int>(rv.error());
                context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
            }
            else
            {
                return Error("base class conversion not found", sourcePos, context);
            }
        }
        else
        {
            return Error("base class conversion not found", sourcePos, context);
        }
    }
    if (classType->IsPolymorphic())
    {
        std::vector<ClassTypeSymbol*> vptrHolderClasses = classType->VPtrHolderClasses();
        if (vptrHolderClasses.empty())
        {
            std::expected<std::u32string, int> fname = classType->FullName();
            if (!fname) return std::unexpected<int>(fname.error());
            std::expected<std::string, int> sfname = util::ToUtf8(*fname);
            if (!sfname) return std::unexpected<int>(sfname.error());
            return Error("no vptr holder classes for the class '" + *sfname + "'", sourcePos, context);
        }
        for (ClassTypeSymbol* vptrHolderClass : vptrHolderClasses)
        {
            if (vptrHolderClass != classType)
            {
                std::expected<ParameterSymbol*, int> tp = classCopyCtor->ThisParam(context);
                if (!tp) return std::unexpected<int>(tp.error());
                ParameterSymbol* thisParam = *tp;
                std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
                if (!rrv) return std::unexpected<int>(rrv.error());
                BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, *rrv);
                std::expected<TypeSymbol*, int> pt = vptrHolderClass->AddPointer(context);
                if (!pt) return std::unexpected<int>(pt.error());
                std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    *pt, thisPtr->GetType(), sourcePos, context);
                if (!arv) return std::unexpected<int>(arv.error());
                FunctionSymbol* conversion = *arv;
                if (conversion)
                {
                    BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr, conversion, sourcePos);
                    BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtrConverted, classType, vptrHolderClass, sourcePos);
                    context->GetBoundFunction()->Body()->AddStatement(setVPtrStatement);
                }
                else
                {
                    return Error("vptr holder class conversion not found", sourcePos, context);
                }
            }
            else
            {
                std::expected<ParameterSymbol*, int> tp = classCopyCtor->ThisParam(context);
                if (!tp) return std::unexpected<int>(tp.error());
                ParameterSymbol* thisParam = *tp;
                std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
                if (!rrv) return std::unexpected<int>(rrv.error());
                BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, *rrv);
                BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtr, classType, classType, sourcePos);
                context->GetBoundFunction()->Body()->AddStatement(setVPtrStatement);
            }
        }
    }
    int n = classType->MemberVariables().size();
    for (int i = 0; i < n; ++i)
    {
        VariableSymbol* memberVariableSymbol = classType->MemberVariables()[i];
        BoundVariableNode* boundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        std::expected<ParameterSymbol*, int> tp = classCopyCtor->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        boundMemberVariable->SetThisPtr(new BoundParameterNode(thisParam, sourcePos, *rrv));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::expected<TypeSymbol*, int> pt = boundMemberVariable->GetType()->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* ptrType = *pt;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundMemberVariable, sourcePos, ptrType)));
        ParameterSymbol* thatParam = classCopyCtor->MemFunParameters(context)[1];
        if (!classCopyCtor->Valid()) return std::unexpected<int>(classCopyCtor->GetError());
        BoundVariableNode* thatBoundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        rrv = thatParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        pt = thatParam->GetType()->RemoveReference(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* type = *pt;
        pt = type->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        type = *pt;
        thatBoundMemberVariable->SetThisPtr(new BoundRefToPtrNode(new BoundParameterNode(thatParam, sourcePos, *rrv), sourcePos, type));
        args.push_back(std::unique_ptr<BoundExpressionNode>(thatBoundMemberVariable));
        std::vector<TypeSymbol*> templateArgs;
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(classType->GetScope(), U"@constructor", templateArgs, args, sourcePos, context);
        if (!orv) return std::unexpected<int>(orv.error());
        std::unique_ptr<BoundFunctionCallNode> memberConstructorCall = std::move(*orv);
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        std::expected<bool, int> rv = expressionStatement->SetExpr(memberConstructorCall.release(), sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
    }
    if (!context->GetFlag(ContextFlags::leaveBoundFunction))
    {
        std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
        if (!rv) return std::unexpected<int>(rv.error());
        context->PopBoundFunction();
    }
    if (classType->TotalMemberCount() <= inlineClassOperationsThreshold)
    {
        classCopyCtor->SetInline();
    }
    return std::expected<bool, int>(true);
}

std::expected<FunctionDefinitionSymbol*, int> GenerateClassCopyCtor(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::unique_ptr<ClassCopyCtor> copyCtor(new ClassCopyCtor(classType, sourcePos, context));
    if (!copyCtor->Valid())
    {
        return std::unexpected<int>(copyCtor->GetError());
    }
    ClassCopyCtorOperation operation;
    context->PushSetFlag(ContextFlags::leaveBoundFunction);
    std::expected<bool, int> rv = operation.GenerateImplementation(copyCtor.get(), sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    context->PopFlags();
    return std::expected<FunctionDefinitionSymbol*, int>(static_cast<FunctionDefinitionSymbol*>(copyCtor.release()));
}

class ClassMoveCtor : public FunctionDefinitionSymbol
{
public:
    ClassMoveCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, Context* context);
    ClassTypeSymbol* ClassType() const { return classType; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassMoveCtor::ClassMoveCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionDefinitionSymbol(U"@class_move_ctor"), classType(classType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetGenerated();
    SetAccess(Access::public_);
    SetParent(classType);
    std::expected<ParameterSymbol*, int> tp = ThisParam(context);
    if (!tp)
    {
        SetError(tp.error());
        return;
    }
    ParameterSymbol* thisParam = *tp;
    std::expected<TypeSymbol*, int> pt = classType->AddRValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* type = *pt;
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    std::expected<bool, int> rv = AddParameter(thatParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::expected<TypeSymbol*, int> trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType);
    if (!trv)
    {
        SetError(trv.error());
        return;
    }
    rv = SetReturnType(*trv, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::expected<std::u32string, int> fname = classType->FullName();
    if (!fname)
    {
        SetError(fname.error());
        return;
    }
    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
    if (!sfname)
    {
        SetError(sfname.error());
        return;
    }
    std::string digestSource = *sfname;
    std::expected<std::string, int> irv = classType->IrName(context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    digestSource.append(1, '.').append(*irv);
    digestSource.append(context->GetBoundCompileUnit()->Id());
    std::expected<std::string, int> groupName = util::ToUtf8(classType->Group()->Name());
    if (!groupName)
    {
        SetError(groupName.error());
        return;
    }
    irName = "move_ctor_" + *groupName + "_" + util::GetSha1MessageDigest(digestSource);
    SetFixedIrName(irName);
}

class ClassMoveCtorOperation : public Operation
{
public:
    ClassMoveCtorOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<bool, int> GenerateImplementation(ClassMoveCtor* classMoveCtor, const soul::ast::SourcePos& sourcePos, Context* context);
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

ClassMoveCtorOperation::ClassMoveCtorOperation() : Operation(U"@constructor", 2)
{
}

std::expected<FunctionSymbol*, int> ClassMoveCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    std::expected<TypeSymbol*, int> pt = type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* tp = *pt;
    pt = tp->RemoveConst(context);
    if (!pt) return std::unexpected<int>(pt.error());
    tp = *pt;
    if (type->PointerCount() != 1 || !tp->IsClassTypeSymbol()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    pt = args[1]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* plainType = *pt;
    if (!plainType->IsClassTypeSymbol()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(type->GetBaseType());
    if (classType->IsClassTemplateSpecializationSymbol() && context->GetFlag(ContextFlags::ignoreClassTemplateSpecializations))
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    pt = classType->AddRValueRef(context);
    if (!pt) return std::unexpected<int>(pt.error());
    tp = *pt;
    if (!TypesEqual(args[1]->GetType(), tp, context) && !args[1]->BindToRvalueRef())
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    int distance = 0;
    if (!TypesEqual(args[1]->GetType()->GetBaseType(), classType, context) && !args[1]->GetType()->GetBaseType()->HasBaseClass(classType, distance, context))
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    FunctionSymbol* moveCtor = classType->GetFunctionByIndex(moveCtorIndex);
    if (moveCtor)
    {
        return std::expected<FunctionSymbol*, int>(moveCtor);
    }
    auto it = functionMap.find(static_cast<TypeSymbol*>(classType));
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    ClassMoveCtor* function = new ClassMoveCtor(classType, sourcePos, context);
    function->SetParent(classType);
    std::expected<bool, int> rv = GenerateImplementation(function, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    functionMap[classType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

std::expected<bool, int> ClassMoveCtorOperation::GenerateImplementation(ClassMoveCtor* classMoveCtor, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ClassTypeSymbol* classType = classMoveCtor->ClassType();
    if (!classType->ObjectLayoutComputed())
    {
        std::expected<bool, int> rv = classType->MakeObjectLayout(sourcePos, context);
        if (!rv) return rv;
    }
    std::unique_ptr<BoundFunctionNode> boundFunction(new BoundFunctionNode(classMoveCtor, sourcePos));
    boundFunction->SetBody(new BoundCompoundStatementNode(sourcePos));
    context->PushBoundFunction(boundFunction.release());
    int nb = classType->BaseClasses().size();
    for (int i = 0; i < nb; ++i)
    {
        TypeSymbol* baseClass = classType->BaseClasses()[i];
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::expected<ParameterSymbol*, int> tp = classMoveCtor->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, *rrv);
        std::expected<TypeSymbol*, int> pt = baseClass->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* type = *pt;
        std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            type, thisPtr->GetType(), sourcePos, context);
        if (!arv) return std::unexpected<int>(arv.error());
        FunctionSymbol* conversion = *arv;
        if (conversion)
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            ParameterSymbol* thatParam = classMoveCtor->MemFunParameters(context)[1];
            if (!classMoveCtor->Valid()) return std::unexpected<int>(classMoveCtor->GetError());
            std::expected<TypeSymbol*, int> pt = baseClass->AddRValueRef(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* tp = *pt;
            arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(tp, thatParam->GetType(), sourcePos, context);
            if (!arv) return std::unexpected<int>(arv.error());
            FunctionSymbol* thatParamConversion = *arv;
            if (thatParamConversion)
            {
                BoundExpressionNode* thatPtr = new BoundParameterNode(thatParam, sourcePos, thatParam->GetType());
                args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thatPtr, thatParamConversion, sourcePos)));
                std::vector<TypeSymbol*> templateArgs;
                std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(
                    context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
                if (!orv) return std::unexpected<int>(orv.error());
                std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = std::move(*orv);
                BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
                std::expected<bool, int> rv = expressionStatement->SetExpr(boundFunctionCall.release(), sourcePos, context);
                if (!rv) return std::unexpected<int>(rv.error());
                context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
            }
            else
            {
                return Error("base class conversion not found", sourcePos, context);
            }
        }
        else
        {
            return Error("base class conversion not found", sourcePos, context);
        }
    }
    if (classType->IsPolymorphic())
    {
        std::vector<ClassTypeSymbol*> vptrHolderClasses = classType->VPtrHolderClasses();
        if (vptrHolderClasses.empty())
        {
            std::expected<std::u32string, int> fname = classType->FullName();
            if (!fname) return std::unexpected<int>(fname.error());
            std::expected<std::string, int> sfname = util::ToUtf8(*fname);
            if (!sfname) return std::unexpected<int>(sfname.error());
            return Error("no vptr holder classes for the class '" + *sfname + "'", sourcePos, context);
        }
        for (ClassTypeSymbol* vptrHolderClass : vptrHolderClasses)
        {
            if (vptrHolderClass != classType)
            {
                std::expected<ParameterSymbol*, int> tp = classMoveCtor->ThisParam(context);
                if (!tp) return std::unexpected<int>(tp.error());
                ParameterSymbol* thisParam = *tp;
                std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
                if (!rrv) return std::unexpected<int>(rrv.error());
                BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, *rrv);
                std::expected<TypeSymbol*, int> pt = vptrHolderClass->AddPointer(context);
                if (!pt) return std::unexpected<int>(pt.error());
                TypeSymbol* ptrType = *pt;
                std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    ptrType, thisPtr->GetType(), sourcePos, context);
                if (!arv) return std::unexpected<int>(arv.error());
                FunctionSymbol* conversion = *arv;
                if (conversion)
                {
                    BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr, conversion, sourcePos);
                    BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtrConverted, classType, vptrHolderClass, sourcePos);
                    context->GetBoundFunction()->Body()->AddStatement(setVPtrStatement);
                }
                else
                {
                    return Error("vptr holder class conversion not found", sourcePos, context);
                }
            }
            else
            {
                std::expected<ParameterSymbol*, int> tp = classMoveCtor->ThisParam(context);
                if (!tp) return std::unexpected<int>(tp.error());
                ParameterSymbol* thisParam = *tp;
                std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
                if (!rrv) return std::unexpected<int>(rrv.error());
                BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, *rrv);
                BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtr, classType, classType, sourcePos);
                context->GetBoundFunction()->Body()->AddStatement(setVPtrStatement);
            }
        }
    }
    int n = classType->MemberVariables().size();
    for (int i = 0; i < n; ++i)
    {
        VariableSymbol* memberVariableSymbol = classType->MemberVariables()[i];
        BoundVariableNode* boundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        std::expected<ParameterSymbol*, int> tp = classMoveCtor->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        boundMemberVariable->SetThisPtr(new BoundParameterNode(thisParam, sourcePos, *rrv));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::vector<TypeSymbol*> templateArgs;
        std::expected<TypeSymbol*, int> pt = boundMemberVariable->GetType()->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* ptrType = *pt;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundMemberVariable, sourcePos, ptrType)));
        ParameterSymbol* thatParam = classMoveCtor->MemFunParameters(context)[1];
        if (!classMoveCtor->Valid()) return std::unexpected<int>(classMoveCtor->GetError());
        BoundVariableNode* thatBoundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        rrv = thatParam->GetReferredType(context);
        pt = thatParam->GetType()->RemoveReference(context);
        if (!pt) return std::unexpected<int>(pt.error());
        ptrType = *pt;
        pt = ptrType->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        ptrType = *pt;
        thatBoundMemberVariable->SetThisPtr(new BoundRefToPtrNode(new BoundParameterNode(thatParam, sourcePos, *rrv), sourcePos, ptrType));
        if (thatBoundMemberVariable->GetType()->IsFunctionPtrType())
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(thatBoundMemberVariable));
        }
        else
        {
            std::vector<std::unique_ptr<BoundExpressionNode>> moveArgs;
            moveArgs.push_back(std::unique_ptr<BoundExpressionNode>(thatBoundMemberVariable));
            std::expected<Scope*, int> nrv = context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context);
            if (!nrv) return std::unexpected<int>(nrv.error());
            Scope* stdScope = *nrv;
            std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(
                stdScope, U"move", templateArgs, moveArgs, sourcePos, context);
            if (!orv) return std::unexpected<int>(orv.error());
            std::unique_ptr<BoundFunctionCallNode> moveThat(std::move(*orv));
            args.push_back(std::unique_ptr<BoundExpressionNode>(moveThat.release()));
        }
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(classType->GetScope(), U"@constructor", templateArgs, args, sourcePos, context);
        if (!orv) return std::unexpected<int>(orv.error());
        std::unique_ptr<BoundFunctionCallNode> memberConstructorCall = std::move(*orv);
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        std::expected<bool, int> rv = expressionStatement->SetExpr(memberConstructorCall.release(), sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
    }
    if (!context->GetFlag(ContextFlags::leaveBoundFunction))
    {
        std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
        if (!rv) return std::unexpected<int>(rv.error());
        context->PopBoundFunction();
    }
    if (classType->TotalMemberCount() <= inlineClassOperationsThreshold)
    {
        classMoveCtor->SetInline();
    }
    return std::expected<bool, int>(true);
}

std::expected<FunctionDefinitionSymbol*, int> GenerateClassMoveCtor(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::unique_ptr<ClassMoveCtor> classMoveCtor(new ClassMoveCtor(classType, sourcePos, context));;
    if (!classMoveCtor->Valid())
    {
        return std::unexpected<int>(classMoveCtor->GetError());
    }
    ClassMoveCtorOperation operation;
    context->PushSetFlag(ContextFlags::leaveBoundFunction);
    std::expected<bool, int> rv = operation.GenerateImplementation(classMoveCtor.get(), sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    context->PopFlags();
    return std::expected<FunctionDefinitionSymbol*, int>(static_cast<FunctionDefinitionSymbol*>(classMoveCtor.release()));
}

class ClassCopyAssignment : public FunctionDefinitionSymbol
{
public:
    ClassCopyAssignment(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, Context* context);
    ClassTypeSymbol* ClassType() const { return classType; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassCopyAssignment::ClassCopyAssignment(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionDefinitionSymbol(U"operator="), classType(classType_)
{
    SetFunctionKind(FunctionKind::special);
    SetGenerated();
    SetAccess(Access::public_);
    SetParent(classType);
    std::expected<ParameterSymbol*, int> tp = ThisParam(context);
    if (!tp)
    {
        SetError(tp.error());
        return;
    }
    ParameterSymbol* thisParam = *tp;
    std::expected<TypeSymbol*, int> pt = classType->AddConst(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* type = *pt;
    pt = type->AddLValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    type = *pt;
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    std::expected<bool, int> rv = AddParameter(thatParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = classType->AddLValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    type = *pt;
    rv = SetReturnType(type, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::expected<std::u32string, int> fname = classType->FullName();
    if (!fname)
    {
        SetError(fname.error());
        return;
    }
    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
    if (!sfname)
    {
        SetError(sfname.error());
        return;
    }
    std::string digestSource = *sfname;
    std::expected<std::string, int> irv = classType->IrName(context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    digestSource.append(1, '.').append(*irv);
    digestSource.append(context->GetBoundCompileUnit()->Id());
    std::expected<std::string, int> groupName = util::ToUtf8(classType->Group()->Name());
    if (!groupName)
    {
        SetError(groupName.error());
        return;
    }
    irName = "copy_assignment_" + *groupName + "_" + util::GetSha1MessageDigest(digestSource);
    SetFixedIrName(irName);
}

class ClassCopyAssignmentOperation : public Operation
{
public:
    ClassCopyAssignmentOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<bool, int> GenerateImplementation(ClassCopyAssignment* classCopyAssignment, const soul::ast::SourcePos& sourcePos, Context* context);
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

ClassCopyAssignmentOperation::ClassCopyAssignmentOperation() : Operation(U"operator=", 2)
{
}

std::expected<FunctionSymbol*, int> ClassCopyAssignmentOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    std::expected<TypeSymbol*, int> pt = type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* tp = *pt;
    pt = tp->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* plainType = *pt;
    if (type->PointerCount() != 1 || !plainType->IsClassTypeSymbol()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    pt = args[1]->GetType()->PlainType(context);
    TypeSymbol* rightPlainType = *pt;
    if (!rightPlainType->IsClassTypeSymbol()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    pt = type->GetBaseType();
    if (!pt) return std::unexpected<int>(pt.error());
    tp = *pt;
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(tp);
    if (classType->IsClassTemplateSpecializationSymbol() && context->GetFlag(ContextFlags::ignoreClassTemplateSpecializations))
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    pt = classType->AddRValueRef(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* rvalueRefType = *pt;
    if (TypesEqual(args[1]->GetType(), rvalueRefType, context) || args[1]->BindToRvalueRef())
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    FunctionSymbol* copyAssignment = classType->GetFunctionByIndex(copyAssignmentIndex);
    if (copyAssignment)
    {
        return std::expected<FunctionSymbol*, int>(copyAssignment);
    }
    auto it = functionMap.find(static_cast<TypeSymbol*>(classType));
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    ClassCopyAssignment* function = new ClassCopyAssignment(classType, sourcePos, context);
    if (!function->Valid())
    {
        return std::unexpected<int>(function->GetError());
    }
    function->SetParent(classType);
    std::expected<bool, int> rv = GenerateImplementation(function, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    functionMap[classType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

std::expected<bool, int> ClassCopyAssignmentOperation::GenerateImplementation(ClassCopyAssignment* classCopyAssignment, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    ClassTypeSymbol* classType = classCopyAssignment->ClassType();
    std::unique_ptr<BoundFunctionNode> boundFunction(new BoundFunctionNode(classCopyAssignment, sourcePos));
    boundFunction->SetBody(new BoundCompoundStatementNode(sourcePos));
    context->PushBoundFunction(boundFunction.release());
    int nb = classType->BaseClasses().size();
    for (int i = 0; i < nb; ++i)
    {
        TypeSymbol* baseClass = classType->BaseClasses()[i];
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::expected<ParameterSymbol*, int> tp = classCopyAssignment->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, *rrv);
        std::expected<TypeSymbol*, int> pt = baseClass->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* ptrType = *pt;
        std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            ptrType, thisPtr->GetType(), sourcePos, context);
        if (!arv) return std::unexpected<int>(arv.error());
        FunctionSymbol* conversion = *arv;
        if (conversion)
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            ParameterSymbol* thatParam = classCopyAssignment->MemFunParameters(context)[1];
            if (!classCopyAssignment->Valid()) return std::unexpected<int>(classCopyAssignment->GetError());
            BoundExpressionNode* thatPtr = new BoundParameterNode(thatParam, sourcePos, thatParam->GetType());
            pt = baseClass->AddConst(context);
            if (!pt) return std::unexpected<int>(pt.error());
            ptrType = *pt;
            pt = ptrType->AddLValueRef(context);
            if (!pt) return std::unexpected<int>(pt.error());
            ptrType = *pt;
            arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(ptrType, thatParam->GetType(), sourcePos, context);
            if (!arv) return std::unexpected<int>(arv.error());
            FunctionSymbol* thatConversion = *arv;
            if (thatConversion)
            {
                args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thatPtr, thatConversion, sourcePos)));
                std::vector<TypeSymbol*> templateArgs;
                std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(
                    context->GetSymbolTable()->CurrentScope(), U"operator=", templateArgs, args, sourcePos, context);
                if (!orv) return std::unexpected<int>(orv.error());
                std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = std::move(*orv);
                BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
                std::expected<bool, int> rv = expressionStatement->SetExpr(boundFunctionCall.release(), sourcePos, context);
                if (!rv) return std::unexpected<int>(rv.error());
                context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
            }
            else
            {
                return Error("base class conversion not found", sourcePos, context);
            }
        }
        else
        {
            return Error("base class conversion not found", sourcePos, context);
        }
    }
    int n = classType->MemberVariables().size();
    for (int i = 0; i < n; ++i)
    {
        VariableSymbol* memberVariableSymbol = classType->MemberVariables()[i];
        BoundVariableNode* boundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        std::expected<ParameterSymbol*, int> tp = classCopyAssignment->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        boundMemberVariable->SetThisPtr(new BoundParameterNode(thisParam, sourcePos, *rrv));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::expected<TypeSymbol*, int> pt = boundMemberVariable->GetType()->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* ptrType = *pt;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundMemberVariable, sourcePos, ptrType)));
        ParameterSymbol* thatParam = classCopyAssignment->MemFunParameters(context)[1];
        if (!classCopyAssignment->Valid()) return std::unexpected<int>(classCopyAssignment->GetError());
        BoundVariableNode* thatBoundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        if (!rrv) return std::unexpected<int>(rrv.error());
        rrv = thatParam->GetReferredType(context);
        pt = thatParam->GetType()->RemoveReference(context);
        if (!pt) return std::unexpected<int>(pt.error());
        ptrType = *pt;
        pt = ptrType->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        ptrType = *pt;
        thatBoundMemberVariable->SetThisPtr(new BoundRefToPtrNode(new BoundParameterNode(thatParam, sourcePos, *rrv), sourcePos, ptrType));
        args.push_back(std::unique_ptr<BoundExpressionNode>(thatBoundMemberVariable));
        std::vector<TypeSymbol*> templateArgs;
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(classType->GetScope(), U"operator=", templateArgs, args, sourcePos, context);
        if (!orv) return std::unexpected<int>(orv.error());
        std::unique_ptr<BoundFunctionCallNode> memberAssignmentrCall = std::move(*orv);
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        std::expected<bool, int> rv = expressionStatement->SetExpr(memberAssignmentrCall.release(), sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
    }
    BoundReturnStatementNode* returnStatement = new BoundReturnStatementNode(sourcePos);
    otava::ast::ThisNode* thisNode = new otava::ast::ThisNode(sourcePos);
    otava::ast::UnaryExprNode derefNode(sourcePos, new otava::ast::DerefNode(sourcePos), thisNode);
    std::expected<BoundExpressionNode*, int> brv = BindExpression(&derefNode, context);
    if (!brv) return std::unexpected<int>(brv.error());
    BoundExpressionNode* derefThisExpr = *brv;
    std::expected<bool, int> rv = returnStatement->SetExpr(derefThisExpr, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    context->GetBoundFunction()->Body()->AddStatement(returnStatement);
    if (!context->GetFlag(ContextFlags::leaveBoundFunction))
    {
        std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
        if (!rv) return std::unexpected<int>(rv.error());
        context->PopBoundFunction();
    }
    if (classType->TotalMemberCount() <= inlineClassOperationsThreshold)
    {
        classCopyAssignment->SetInline();
    }
    return std::expected<bool, int>(true);
}

std::expected<FunctionDefinitionSymbol*, int> GenerateClassCopyAssignment(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::unique_ptr<ClassCopyAssignment> copyAssignment(new ClassCopyAssignment(classType, sourcePos, context));
    if (!copyAssignment->Valid())
    {
        return std::unexpected<int>(copyAssignment->GetError());
    }
    ClassCopyAssignmentOperation operation;
    context->PushSetFlag(ContextFlags::leaveBoundFunction);
    std::expected<bool, int> rv = operation.GenerateImplementation(copyAssignment.get(), sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    context->PopFlags();
    return std::expected<FunctionDefinitionSymbol*, int>(static_cast<FunctionDefinitionSymbol*>(copyAssignment.release()));
}

class ClassMoveAssignment : public FunctionDefinitionSymbol
{
public:
    ClassMoveAssignment(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, Context* context);
    ClassTypeSymbol* ClassType() const { return classType; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassMoveAssignment::ClassMoveAssignment(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionDefinitionSymbol(U"operator="), classType(classType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetGenerated();
    SetAccess(Access::public_);
    SetParent(classType);
    std::expected<ParameterSymbol*, int> tp = ThisParam(context);
    if (!tp)
    {
        SetError(tp.error());
        return;
    }
    ParameterSymbol* thisParam = *tp;
    std::expected<TypeSymbol*, int> pt = classType->AddRValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", *pt);
    std::expected<bool, int> rv = AddParameter(thatParam, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = classType->AddLValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    rv = SetReturnType(*pt, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    std::expected<std::u32string, int> fname = classType->FullName();
    if (!fname)
    {
        SetError(fname.error());
        return;
    }
    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
    if (!sfname)
    {
        SetError(sfname.error());
        return;
    }
    std::string digestSource = *sfname;
    std::expected<std::string, int> irv = classType->IrName(context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    digestSource.append(1, '.').append(*irv);
    digestSource.append(context->GetBoundCompileUnit()->Id());
    std::expected<std::string, int> groupName = util::ToUtf8(classType->Group()->Name());
    if (!groupName)
    {
        SetError(groupName.error());
        return;
    }
    irName = "move_assignment_" + *groupName + "_" + util::GetSha1MessageDigest(digestSource);
    SetFixedIrName(irName);
}

class ClassMoveAssignmentOperation : public Operation
{
public:
    ClassMoveAssignmentOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<bool, int> GenerateImplementation(ClassMoveAssignment* classMoveAssignment, const soul::ast::SourcePos& sourcePos, Context* context);
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

ClassMoveAssignmentOperation::ClassMoveAssignmentOperation() : Operation(U"operator=", 2)
{
}

std::expected<FunctionSymbol*, int> ClassMoveAssignmentOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    std::expected<TypeSymbol*, int> pt = type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* tp = *pt;
    pt = tp->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* plainType = *pt;
    if (type->PointerCount() != 1 || !plainType->IsClassTypeSymbol()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    pt = args[1]->GetType()->PlainType(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* rightPlainType = *pt;
    if (!rightPlainType->IsClassTypeSymbol()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(type->GetBaseType());
    if (classType->IsClassTemplateSpecializationSymbol() && context->GetFlag(ContextFlags::ignoreClassTemplateSpecializations))
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    pt = classType->AddRValueRef(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* rvalueRefType = *pt;
    if (!TypesEqual(args[1]->GetType(), rvalueRefType, context) && !args[1]->BindToRvalueRef())
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
    FunctionSymbol* moveAssignment = classType->GetFunctionByIndex(moveAssignmentIndex);
    if (moveAssignment)
    {
        return std::expected<FunctionSymbol*, int>(moveAssignment);
    }
    auto it = functionMap.find(static_cast<TypeSymbol*>(classType));
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return std::expected<FunctionSymbol*, int>(function);
    }
    ClassMoveAssignment* function = new ClassMoveAssignment(classType, sourcePos, context);
    function->SetParent(classType);
    std::expected<bool, int> rv = GenerateImplementation(function, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    functionMap[classType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(function)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(function));
}

std::expected<bool, int> ClassMoveAssignmentOperation::GenerateImplementation(ClassMoveAssignment* classMoveAssignment, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    ClassTypeSymbol* classType = classMoveAssignment->ClassType();
    std::unique_ptr<BoundFunctionNode> boundFunction(new BoundFunctionNode(classMoveAssignment, sourcePos));
    boundFunction->SetBody(new BoundCompoundStatementNode(sourcePos));
    context->PushBoundFunction(boundFunction.release());
    int nb = classType->BaseClasses().size();
    for (int i = 0; i < nb; ++i)
    {
        TypeSymbol* baseClass = classType->BaseClasses()[i];
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::expected<ParameterSymbol*, int> tp = classMoveAssignment->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        BoundExpressionNode* thisPtr = new BoundParameterNode(thisParam, sourcePos, *rrv);
        std::expected<TypeSymbol*, int> pt = baseClass->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* ptrType = *pt;
        std::expected<FunctionSymbol*, int> arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            ptrType, thisPtr->GetType(), sourcePos, context);
        if (!arv) return std::unexpected<int>(arv.error());
        FunctionSymbol* conversion = *arv;
        if (conversion)
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            ParameterSymbol* thatParam = classMoveAssignment->MemFunParameters(context)[1];
            if (!classMoveAssignment->Valid()) return std::unexpected<int>(classMoveAssignment->GetError());
            BoundExpressionNode* thatPtr = new BoundParameterNode(thatParam, sourcePos, thatParam->GetType());
            std::expected<TypeSymbol*, int> pt = baseClass->AddRValueRef(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* rvalueRefType = *pt;
            arv = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(rvalueRefType, thatParam->GetType(), sourcePos, context);
            if (!arv) return std::unexpected<int>(arv.error());
            FunctionSymbol* thatConversion = *arv;
            std::vector<std::unique_ptr<BoundExpressionNode>> moveArgs;
            moveArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thatPtr, thatConversion, sourcePos)));
            std::expected<Scope*, int> nrv = context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context);
            if (!nrv) return std::unexpected<int>(nrv.error());
            Scope* stdScope = *nrv;
            std::vector<TypeSymbol*> templateArgs;
            std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(stdScope, U"move", templateArgs, moveArgs, sourcePos, context);
            if (!orv) return std::unexpected<int>(orv.error());
            std::unique_ptr<BoundFunctionCallNode> moveThat(std::move(*orv));
            args.push_back(std::unique_ptr<BoundExpressionNode>(moveThat.release()));
            orv = ResolveOverload(context->GetSymbolTable()->CurrentScope(), U"operator=", templateArgs, args, sourcePos, context);
            if (!orv) return std::unexpected<int>(orv.error());
            std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = std::move(*orv);
            BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
            std::expected<bool, int> rv = expressionStatement->SetExpr(boundFunctionCall.release(), sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
            context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
        }
        else
        {
            return Error("base class conversion not found", sourcePos, context);
        }
    }
    int n = classType->MemberVariables().size();
    for (int i = 0; i < n; ++i)
    {
        VariableSymbol* memberVariableSymbol = classType->MemberVariables()[i];
        BoundVariableNode* boundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        std::expected<ParameterSymbol*, int> tp = classMoveAssignment->ThisParam(context);
        if (!tp) return std::unexpected<int>(tp.error());
        ParameterSymbol* thisParam = *tp;
        std::expected<TypeSymbol*, int> rrv = thisParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        boundMemberVariable->SetThisPtr(new BoundParameterNode(thisParam, sourcePos, *rrv));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        args.push_back(std::unique_ptr<BoundExpressionNode>(boundMemberVariable));
        ParameterSymbol* thatParam = classMoveAssignment->MemFunParameters(context)[1];
        if (!classMoveAssignment->Valid()) return std::unexpected<int>(classMoveAssignment->GetError());
        BoundVariableNode* thatBoundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        rrv = thatParam->GetReferredType(context);
        if (!rrv) return std::unexpected<int>(rrv.error());
        std::expected<TypeSymbol*, int> pt = thatParam->GetType()->RemoveReference(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* ptrType = *pt;
        pt = ptrType->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        ptrType = *pt;
        thatBoundMemberVariable->SetThisPtr(new BoundRefToPtrNode(new BoundParameterNode(thatParam, sourcePos, *rrv), sourcePos, ptrType));
        args.push_back(std::unique_ptr<BoundExpressionNode>(thatBoundMemberVariable));
        std::expected<Scope*, int> nrv = context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context);
        if (!nrv) return std::unexpected<int>(nrv.error());
        Scope* stdScope = *nrv;
        std::vector<TypeSymbol*> templateArgs;
        std::expected<std::unique_ptr<BoundFunctionCallNode>, int> orv = ResolveOverload(stdScope, U"swap", templateArgs, args, sourcePos, context);
        if (!orv) return std::unexpected<int>(orv.error());
        std::unique_ptr<BoundFunctionCallNode> memberConstructorCall = std::move(*orv);
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        std::expected<bool, int> rv = expressionStatement->SetExpr(memberConstructorCall.release(), sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
    }
    BoundReturnStatementNode* returnStatement = new BoundReturnStatementNode(sourcePos);
    otava::ast::ThisNode* thisNode = new otava::ast::ThisNode(sourcePos);
    otava::ast::UnaryExprNode derefNode(sourcePos, new otava::ast::DerefNode(sourcePos), thisNode);
    std::expected<BoundExpressionNode*, int> erv = BindExpression(&derefNode, context);
    if (!erv) return std::unexpected<int>(erv.error());
    BoundExpressionNode* derefThisExpr = *erv;
    std::expected<bool, int> rv = returnStatement->SetExpr(derefThisExpr, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    context->GetBoundFunction()->Body()->AddStatement(returnStatement);
    if (!context->GetFlag(ContextFlags::leaveBoundFunction))
    {
        std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
        if (!rv) return std::unexpected<int>(rv.error());
        context->PopBoundFunction();
    }
    if (classType->TotalMemberCount() <= inlineClassOperationsThreshold)
    {
        classMoveAssignment->SetInline();
    }
    return std::expected<bool, int>(true);
}

std::expected<FunctionDefinitionSymbol*, int> GenerateClassMoveAssignment(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::unique_ptr<ClassMoveAssignment> moveAssignment(new ClassMoveAssignment(classType, sourcePos, context));
    if (!moveAssignment->Valid())
    {
        return std::unexpected<int>(moveAssignment->GetError());
    }
    ClassMoveAssignmentOperation operation;
    context->PushSetFlag(ContextFlags::leaveBoundFunction);
    std::expected<bool, int> rv = operation.GenerateImplementation(moveAssignment.get(), sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    context->PopFlags();
    return std::expected<FunctionDefinitionSymbol*, int>(static_cast<FunctionDefinitionSymbol*>(moveAssignment.release()));
}

class FunctionPtrApply : public FunctionSymbol
{
public:
    FunctionPtrApply(FunctionTypeSymbol* type_, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, Context* context);
private:
    FunctionTypeSymbol* functionType;
};

FunctionPtrApply::FunctionPtrApply(FunctionTypeSymbol* functionType_, const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionSymbol(U"operator()"), functionType(functionType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = functionType->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* parameter = new ParameterSymbol(U"fn", ptrType);
    std::expected<bool, int> rv = AddSymbol(parameter, sourcePos, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    for (TypeSymbol* parameterType : functionType->ParameterTypes())
    {
        ParameterSymbol* parameter = new ParameterSymbol(U"@param", parameterType);
        rv = AddSymbol(parameter, sourcePos, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    rv = SetReturnType(functionType->ReturnType(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> FunctionPtrApply::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* callee = emitter.Stack().Pop();
    int na = args.size() - 1;
    for (int i = 0; i < na; ++i)
    {
        rv = args[i + 1]->Load(emitter, OperationFlags::none, sourcePos, context);
        if (!rv) return rv;
    }
    std::vector<otava::intermediate::Value*> arguments;
    arguments.resize(na);
    for (int i = 0; i < na; ++i)
    {
        otava::intermediate::Value* arg = emitter.Stack().Pop();
        arguments[na - i - 1] = arg;
    }
    std::expected<otava::intermediate::Value*, int> crv = emitter.EmitCall(callee, arguments);
    if (!crv) return std::unexpected<int>(crv.error());
    return std::expected<bool, int>(true);
}

class FunctionPtrApplyOperation : public Operation
{
public:
    FunctionPtrApplyOperation();
    std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

FunctionPtrApplyOperation::FunctionPtrApplyOperation() : Operation(U"operator()", -1)
{
}

std::expected<FunctionSymbol*, int> FunctionPtrApplyOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    Context* context)
{
    if (args.size() < 1) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    TypeSymbol* type = args[0]->GetType();
    if (type->PointerCount() != 1) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    std::expected<TypeSymbol*, int> pt = type->RemovePointer(context);
    if (!pt) return std::unexpected<int>(pt.error());
    TypeSymbol* pointeeType = *pt;
    if (!pointeeType->IsFunctionTypeSymbol()) return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    FunctionTypeSymbol* functionType = static_cast<FunctionTypeSymbol*>(pointeeType);
    FunctionPtrApply* apply = new FunctionPtrApply(functionType, sourcePos, context);
    if (!apply->Valid())
    {
        return std::unexpected<int>(apply->GetError());
    }
    functions.push_back(std::unique_ptr<FunctionSymbol>(static_cast<FunctionSymbol*>(apply)));
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(apply));
}

Operation::Operation(const std::u32string& groupName_, int arity_) : groupName(groupName_), arity(arity_)
{
}

Operation::~Operation()
{
}

OperationGroup::OperationGroup(const std::u32string& name_) : name(name_)
{
}

void OperationGroup::AddOperation(Operation* operation)
{
    if (operation->Arity() == -1)
    {
        anyArityOperations.push_back(operation);
    }
    else
    {
        arityOperationsMap[operation->Arity()].push_back(operation);
    }
}

std::expected<FunctionSymbol*, int> OperationGroup::GetOperation(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos,
    Context* context)
{
    auto it = arityOperationsMap.find(static_cast<int>(args.size()));
    if (it != arityOperationsMap.cend())
    {
        const std::vector<Operation*>& operations = it->second;
        for (Operation* operation : operations)
        {
            std::expected<FunctionSymbol*, int> rv = operation->Get(args, sourcePos, context);
            if (!rv) return std::unexpected<int>(rv.error());
            FunctionSymbol* op = *rv;
            if (op)
            {
                return std::expected<FunctionSymbol*, int>(op);
            }
        }
    }
    for (Operation* operation : anyArityOperations)
    {
        std::expected<FunctionSymbol*, int> rv = operation->Get(args, sourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        FunctionSymbol* op = *rv;
        if (op)
        {
            return op;
        }
    }
    return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
}

OperationRepository::OperationRepository()
{
    AddOperation(new PointerDefaultCtorOperation());
    AddOperation(new PointerCopyCtorOperation());
    AddOperation(new PointerMoveCtorOperation());
    AddOperation(new PointerCopyAssignmentOperation());
    AddOperation(new PointerMoveAssignmentOperation());
    AddOperation(new PointerPlusOffsetOperation());
    AddOperation(new OffsetPlusPointerOperation());
    AddOperation(new PointerMinusOffsetOperation());
    AddOperation(new PointerMinusPointerOperation());
    AddOperation(new PointerEqualOperation());
    AddOperation(new PointerLessOperation());
    AddOperation(new PointerArrowOperation());
    AddOperation(new ClassDefaultCtorOperation());
    AddOperation(new ClassCopyCtorOperation());
    AddOperation(new ClassMoveCtorOperation());
    AddOperation(new ClassCopyAssignmentOperation());
    AddOperation(new ClassMoveAssignmentOperation());
    AddOperation(new CopyRefOperation());
    AddOperation(new FunctionPtrApplyOperation());
}

OperationGroup* OperationRepository::GetOrInsertOperationGroup(const std::u32string& operationGroupName)
{
    auto it = groupMap.find(operationGroupName);
    if (it != groupMap.cend())
    {
        return it->second;
    }
    OperationGroup* group = new OperationGroup(operationGroupName);
    groupMap[operationGroupName] = group;
    groups.push_back(std::unique_ptr<OperationGroup>(group));
    return group;
}

void OperationRepository::AddOperation(Operation* operation)
{
    OperationGroup* group = GetOrInsertOperationGroup(operation->GroupName());
    group->AddOperation(operation);
    operations.push_back(std::unique_ptr<Operation>(operation));
}

std::expected<FunctionSymbol*, int> OperationRepository::GetOperation(const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    auto it = groupMap.find(groupName);
    if (it != groupMap.cend())
    {
        OperationGroup* group = it->second;
        return group->GetOperation(args, sourcePos, context);
    }
    else
    {
        return std::expected<FunctionSymbol*, int>(static_cast<FunctionSymbol*>(nullptr));
    }
}

} // namespace otava::symbols

