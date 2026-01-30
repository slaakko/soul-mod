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
import otava.symbols.exception;
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
    PointerDefaultCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    TypeSymbol* Type() const { return type; }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

PointerDefaultCtor::PointerDefaultCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) : 
    FunctionSymbol(U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer(context));
    AddParameter(thisParam, sourcePos, context);
    SetNoExcept();
}

void PointerDefaultCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    if ((flags & OperationFlags::defaultInit) != OperationFlags::none)
    {
        emitter.Stack().Push(type->IrType(emitter, sourcePos, context)->DefaultValue());
        OperationFlags storeFlags = OperationFlags::none;
        if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
        {
            storeFlags = storeFlags | OperationFlags::deref;
        }
        args[0]->Store(emitter, storeFlags, sourcePos, context);
    }
}

class PointerDefaultCtorOperation : public Operation
{
public:
    PointerDefaultCtorOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerDefaultCtorOperation::PointerDefaultCtorOperation() : Operation(U"@constructor", 1)
{
}

FunctionSymbol* PointerDefaultCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return nullptr;
    if (type->IsReferenceType()) return nullptr;
    TypeSymbol* pointerType = type->RemovePointer(context);
    auto it = functionMap.find(pointerType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerDefaultCtor* function = new PointerDefaultCtor(pointerType, sourcePos, context);
    functionMap[pointerType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class PointerCopyCtor : public FunctionSymbol
{
public:
    PointerCopyCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    TypeSymbol* Type() const { return type; }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

PointerCopyCtor::PointerCopyCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer(context));
    AddParameter(thisParam, sourcePos, context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    AddParameter(thatParam, sourcePos, context);
    SetNoExcept();
}

void PointerCopyCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if ((flags & OperationFlags::dup) != OperationFlags::none)
    {
        emitter.Stack().Dup();
    }
    OperationFlags storeFlags = OperationFlags::none;
    if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
    {
        storeFlags = storeFlags | OperationFlags::deref;
    }
    args[0]->Store(emitter, storeFlags, sourcePos, context);
}

class PointerCopyCtorOperation : public Operation
{
public:
    PointerCopyCtorOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerCopyCtorOperation::PointerCopyCtorOperation() : Operation(U"@constructor", 2)
{
}

FunctionSymbol* PointerCopyCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return nullptr;
    if (type->IsReferenceType()) return nullptr;
    TypeSymbol* pointerType = type->RemovePointer(context);
    TypeSymbol* rvalueRefType = pointerType->AddRValueRef(context);
    if (TypesEqual(args[1]->GetType(), rvalueRefType, context)) return nullptr;
    auto it = functionMap.find(pointerType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerCopyCtor* function = new PointerCopyCtor(pointerType, sourcePos, context);
    functionMap[pointerType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class PointerMoveCtor : public FunctionSymbol
{
public:
    PointerMoveCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    TypeSymbol* Type() const { return type; }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

PointerMoveCtor::PointerMoveCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer(context));
    AddParameter(thisParam, sourcePos, context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type->AddRValueRef(context));
    AddParameter(thatParam, sourcePos, context);
    SetNoExcept();
}

void PointerMoveCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* rvalueRefValue = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLoad(rvalueRefValue));
    OperationFlags storeFlags = OperationFlags::none;
    if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
    {
        storeFlags = storeFlags | OperationFlags::deref;
    }
    args[0]->Store(emitter, storeFlags, sourcePos, context);
}

class PointerMoveCtorOperation : public Operation
{
public:
    PointerMoveCtorOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerMoveCtorOperation::PointerMoveCtorOperation() : Operation(U"@constructor", 2)
{
}

FunctionSymbol* PointerMoveCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos,
    otava::symbols::Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return nullptr;
    if (type->IsReferenceType()) return nullptr;
    TypeSymbol* pointerType = type->RemovePointer(context);
    TypeSymbol* rvalueRefType = pointerType->AddRValueRef(context);
    if (!TypesEqual(args[1]->GetType(), rvalueRefType, context) && !args[1]->BindToRvalueRef()) return nullptr;
    auto it = functionMap.find(pointerType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerMoveCtor* function = new PointerMoveCtor(pointerType, sourcePos, context);
    functionMap[pointerType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class PointerCopyAssignment : public FunctionSymbol
{
public:
    PointerCopyAssignment(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    TypeSymbol* Type() const { return type; }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
    bool IsPointerCopyAssignment() const override { return true; }
private:
    TypeSymbol* type;
};

PointerCopyAssignment::PointerCopyAssignment(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator="), type(type_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer(context));
    AddParameter(thisParam, sourcePos, context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    AddParameter(thatParam, sourcePos, context);
    SetReturnType(type->AddLValueRef(context), context);
    SetNoExcept();
}

void PointerCopyAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    args[0]->Store(emitter, OperationFlags::setPtr, sourcePos, context);
    emitter.Stack().Push(context->Ptr());
}

class PointerCopyAssignmentOperation : public Operation
{
public:
    PointerCopyAssignmentOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerCopyAssignmentOperation::PointerCopyAssignmentOperation() : Operation(U"operator=", 2)
{
}

FunctionSymbol* PointerCopyAssignmentOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return nullptr;
    TypeSymbol* pointerType = type->RemovePointer(context)->RemoveReference(context);
    if (TypesEqual(args[1]->GetType(), pointerType->AddRValueRef(context), context) || args[1]->BindToRvalueRef()) return nullptr;
    auto it = functionMap.find(pointerType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerCopyAssignment* function = new PointerCopyAssignment(pointerType, sourcePos, context);
    functionMap[pointerType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class PointerMoveAssignment : public FunctionSymbol
{
public:
    PointerMoveAssignment(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    TypeSymbol* Type() const { return type; }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

PointerMoveAssignment::PointerMoveAssignment(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator="), type(type_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer(context));
    AddParameter(thisParam, sourcePos, context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type->AddRValueRef(context));
    AddParameter(thatParam, sourcePos, context);
    SetReturnType(type->AddLValueRef(context), context);
    SetNoExcept();
}

void PointerMoveAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* refValue = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLoad(refValue));
    args[0]->Store(emitter, OperationFlags::setPtr, sourcePos, context);
    emitter.Stack().Push(context->Ptr());
}

class PointerMoveAssignmentOperation : public Operation
{
public:
    PointerMoveAssignmentOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerMoveAssignmentOperation::PointerMoveAssignmentOperation() : Operation(U"operator=", 2)
{
}

FunctionSymbol* PointerMoveAssignmentOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return nullptr;
    TypeSymbol* pointerType = type->RemovePointer(context)->RemoveReference(context);
    if (!TypesEqual(args[1]->GetType(), pointerType->AddRValueRef(context), context) && !args[1]->BindToRvalueRef()) return nullptr;
    auto it = functionMap.find(pointerType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerMoveAssignment* function = new PointerMoveAssignment(pointerType, sourcePos, context);
    functionMap[pointerType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class PointerPlusOffset : public FunctionSymbol
{
public:
    PointerPlusOffset(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* pointerType;
    TypeSymbol* longLongIntType;
};

PointerPlusOffset::PointerPlusOffset(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator+"), pointerType(pointerType_), longLongIntType(longLongIntType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", pointerType);
    AddParameter(leftParam, sourcePos, context);
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", longLongIntType);
    AddParameter(rightParam, sourcePos, context);
    SetReturnType(pointerType, context);
    SetNoExcept();
}

void PointerPlusOffset::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* left = emitter.Stack().Pop();
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitPtrOffset(left, right));
}

class PointerPlusOffsetOperation : public Operation
{
public:
    PointerPlusOffsetOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerPlusOffsetOperation::PointerPlusOffsetOperation() : Operation(U"operator+", 2)
{
}

FunctionSymbol* PointerPlusOffsetOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    if (context->GetFlag(ContextFlags::noPtrOps)) return nullptr;
    TypeSymbol* leftType = args[0]->GetType()->PlainType(context);
    if (!leftType->IsPointerType()) return nullptr;
    TypeSymbol* rightType = args[1]->GetType();
    if (!rightType->PlainType(context)->IsIntegralType())
    {
        if (!context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            rightType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context))
        {
            return nullptr;
        }
    }
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerPlusOffset* function = new PointerPlusOffset(leftType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context);
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class OffsetPlusPointer : public FunctionSymbol
{
public:
    OffsetPlusPointer(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* pointerType;
    TypeSymbol* longLongIntType;
};

OffsetPlusPointer::OffsetPlusPointer(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator+"), pointerType(pointerType_), longLongIntType(longLongIntType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", longLongIntType);
    AddParameter(leftParam, sourcePos, context);
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", pointerType);
    AddParameter(rightParam, sourcePos, context);
    SetReturnType(pointerType, context);
    SetNoExcept();
}

void OffsetPlusPointer::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* left = emitter.Stack().Pop();
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitPtrOffset(right, left));
}

class OffsetPlusPointerOperation : public Operation
{
public:
    OffsetPlusPointerOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

OffsetPlusPointerOperation::OffsetPlusPointerOperation() : Operation(U"operator+", 2)
{
}

FunctionSymbol* OffsetPlusPointerOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    TypeSymbol* leftType = args[0]->GetType();
    if (!leftType->PlainType(context)->IsIntegralType())
    {
        if (!context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            leftType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context))
        {
            return nullptr;
        }
    }
    TypeSymbol* rightType = args[1]->GetType()->PlainType(context);
    if (!rightType->IsPointerType()) return nullptr;
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    OffsetPlusPointer* function = new OffsetPlusPointer(rightType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context);
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class PointerMinusOffset : public FunctionSymbol
{
public:
    PointerMinusOffset(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* pointerType;
    TypeSymbol* longLongIntType;
};

PointerMinusOffset::PointerMinusOffset(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator-"), pointerType(pointerType_), longLongIntType(longLongIntType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", pointerType);
    AddParameter(leftParam, sourcePos, context);
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", longLongIntType);
    AddParameter(rightParam, sourcePos, context);
    SetReturnType(pointerType, context);
    SetNoExcept();
}

void PointerMinusOffset::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* left = emitter.Stack().Pop();
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* right = emitter.Stack().Pop();
    otava::intermediate::Value* offset = emitter.EmitNeg(right);
    emitter.Stack().Push(emitter.EmitPtrOffset(left, offset));
}

class PointerMinusOffsetOperation : public Operation
{
public:
    PointerMinusOffsetOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerMinusOffsetOperation::PointerMinusOffsetOperation() : Operation(U"operator-", 2)
{
}

FunctionSymbol* PointerMinusOffsetOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    if (context->GetFlag(ContextFlags::noPtrOps)) return nullptr;
    TypeSymbol* leftType = args[0]->GetType()->PlainType(context);
    if (!leftType->IsPointerType()) return nullptr;
    TypeSymbol* rightType = args[1]->GetType();
    if (!rightType->PlainType(context)->IsIntegralType())
    {
        if (!context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            rightType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context))
        {
            return nullptr;
        }
    }
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerMinusOffset* function = new PointerMinusOffset(leftType, 
        context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context);
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class PointerMinusPointer : public FunctionSymbol
{
public:
    PointerMinusPointer(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* pointerType;
    TypeSymbol* longLongIntType;
};

PointerMinusPointer::PointerMinusPointer(TypeSymbol* pointerType_, TypeSymbol* longLongIntType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator-"), pointerType(pointerType_), longLongIntType(longLongIntType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", pointerType);
    AddParameter(leftParam, sourcePos, context);
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", pointerType);
    AddParameter(rightParam, sourcePos, context);
    SetReturnType(longLongIntType, context);
    SetNoExcept();
}

void PointerMinusPointer::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* left = emitter.Stack().Pop();
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitPtrDiff(left, right));
}

class PointerMinusPointerOperation : public Operation
{
public:
    PointerMinusPointerOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerMinusPointerOperation::PointerMinusPointerOperation() : Operation(U"operator-", 2)
{
}

FunctionSymbol* PointerMinusPointerOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    TypeSymbol* leftType = args[0]->GetType()->PlainType(context);
    if (!leftType->IsPointerType()) return nullptr;
    TypeSymbol* rightType = args[1]->GetType()->PlainType(context);
    if (!rightType->IsPointerType()) return nullptr;
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerMinusPointer* function = new PointerMinusPointer(leftType, 
        context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context);
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class PointerEqual : public FunctionSymbol
{
public:
    PointerEqual(TypeSymbol* pointerType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* pointerType;
};

PointerEqual::PointerEqual(TypeSymbol* pointerType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator=="), pointerType(pointerType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", pointerType);
    AddParameter(leftParam, sourcePos, context);
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", pointerType);
    AddParameter(rightParam, sourcePos, context);
    SetReturnType(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType), context);
    SetNoExcept();
}

void PointerEqual::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* left = emitter.Stack().Pop();
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitEqual(left, right));
}

class PointerEqualOperation : public Operation
{
public:
    PointerEqualOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerEqualOperation::PointerEqualOperation() : Operation(U"operator==", 2)
{
}

FunctionSymbol* PointerEqualOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    TypeSymbol* leftType = args[0]->GetType()->PlainType(context);
    if (!leftType->IsPointerType() && !leftType->IsNullPtrType()) return nullptr;
    TypeSymbol* rightType = args[1]->GetType()->PlainType(context);
    if (!rightType->IsPointerType() && !rightType->IsNullPtrType()) return nullptr;
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerEqual* function = new PointerEqual(leftType, sourcePos, context);
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class PointerLess : public FunctionSymbol
{
public:
    PointerLess(TypeSymbol* pointerType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* pointerType;
};

PointerLess::PointerLess(TypeSymbol* pointerType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator<"), pointerType(pointerType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* leftParam = new ParameterSymbol(U"left", pointerType);
    AddParameter(leftParam, sourcePos, context);
    ParameterSymbol* rightParam = new ParameterSymbol(U"right", pointerType);
    AddParameter(rightParam, sourcePos, context);
    SetReturnType(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType), context);
    SetNoExcept();
}

void PointerLess::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* left = emitter.Stack().Pop();
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLess(left, right));
}

class PointerLessOperation : public Operation
{
public:
    PointerLessOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerLessOperation::PointerLessOperation() : Operation(U"operator<", 2)
{
}

FunctionSymbol* PointerLessOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    TypeSymbol* leftType = args[0]->GetType()->PlainType(context);
    if (!leftType->IsPointerType()) return nullptr;
    TypeSymbol* rightType = args[1]->GetType()->PlainType(context);
    if (!rightType->IsPointerType()) return nullptr;
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerLess* function = new PointerLess(leftType, sourcePos, context);
    functionMap[leftType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class PointerArrow : public FunctionSymbol
{
public:
    PointerArrow(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

PointerArrow::PointerArrow(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator->"), type(type_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* operandParam = new ParameterSymbol(U"operand", type->AddPointer(context));
    AddParameter(operandParam, sourcePos, context);
    SetReturnType(type, context);
    SetNoExcept();
}

void PointerArrow::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
}

class PointerArrowOperation : public Operation
{
public:
    PointerArrowOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

PointerArrowOperation::PointerArrowOperation() : Operation(U"operator->", 1)
{
}

FunctionSymbol* PointerArrowOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    TypeSymbol* operandType = args[0]->GetType();
    if (operandType->PointerCount() <= 1) return nullptr;
    TypeSymbol* type = operandType->RemovePointer(context);
    auto it = functionMap.find(type);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerArrow* function = new PointerArrow(type, sourcePos, context);
    functionMap[type] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

class CopyRef: public FunctionSymbol
{
public:
    CopyRef(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    TypeSymbol* type;
};

CopyRef::CopyRef(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer(context));
    AddParameter(thisParam, sourcePos, context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    AddParameter(thatParam, sourcePos, context);
    SetNoExcept();
}

void CopyRef::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
}

class CopyRefOperation : public Operation
{
public:
    CopyRefOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

CopyRefOperation::CopyRefOperation() : Operation(U"@constructor", 2)
{
}

FunctionSymbol* CopyRefOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    TypeSymbol* arg0Type = args[0]->GetType();
    if (arg0Type->PointerCount() != 1) return nullptr;
    TypeSymbol* type = arg0Type->RemovePointer(context);
    if (!type->IsReferenceType()) return nullptr;
    TypeSymbol* argType = args[1]->GetType();
    if (!argType->IsReferenceType()) return nullptr;
    auto it = functionMap.find(type);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    CopyRef* copyRef = new CopyRef(type, sourcePos, context);
    functionMap[type] = copyRef;
    functions.push_back(std::unique_ptr<FunctionSymbol>(copyRef));
    return copyRef;
}

class ClassDefaultCtor : public FunctionDefinitionSymbol
{
public:
    ClassDefaultCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    ClassTypeSymbol* ClassType() const { return classType; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassDefaultCtor::ClassDefaultCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) : 
    FunctionDefinitionSymbol(U"@class_default_ctor"), classType(classType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetGenerated();
    SetParent(classType);
    SetAccess(Access::public_);
    SetReturnType(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType), context);
    std::string digestSource = util::ToUtf8(classType->FullName());
    digestSource.append(1, '.').append(classType->IrName(context));
    digestSource.append(context->GetBoundCompileUnit()->Id());
    irName = "default_ctor_" + util::ToUtf8(classType->Group()->Name()) + "_" + util::GetSha1MessageDigest(digestSource);
    SetFixedIrName(irName);
}

class ClassDefaultCtorOperation : public Operation
{
public:
    ClassDefaultCtorOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    void GenerateImplementation(ClassDefaultCtor* classDefaultCtor, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

ClassDefaultCtorOperation::ClassDefaultCtorOperation() : Operation(U"@constructor", 1)
{
}

FunctionSymbol* ClassDefaultCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    if (type->PointerCount() != 1 || !type->RemovePointer(context)->PlainType(context)->IsClassTypeSymbol()) return nullptr;
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(type->GetBaseType());
    if (classType->IsClassTemplateSpecializationSymbol() && context->GetFlag(ContextFlags::ignoreClassTemplateSpecializations)) return nullptr;
    FunctionSymbol* defaultCtor = classType->GetFunctionByIndex(defaultCtorIndex);
    if (defaultCtor)
    {
        return defaultCtor;
    }
    if (classType->HasUserDefinedConstructor()) return nullptr;
    auto it = functionMap.find(classType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    ClassDefaultCtor* function = new ClassDefaultCtor(classType, sourcePos, context);
    function->SetParent(classType);
    GenerateImplementation(function, sourcePos, context);
    functionMap[classType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

void ClassDefaultCtorOperation::GenerateImplementation(ClassDefaultCtor* classDefaultCtor, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ClassTypeSymbol* classType = classDefaultCtor->ClassType();
    if (!classType->ObjectLayoutComputed())
    {
        classType->MakeObjectLayout(sourcePos, context);
    }
    std::unique_ptr<BoundFunctionNode> boundFunction(new BoundFunctionNode(classDefaultCtor, sourcePos));
    boundFunction->SetBody(new BoundCompoundStatementNode(sourcePos)); 
    context->PushBoundFunction(boundFunction.release());
    bool setNoExcept = true;
    int nb = classType->BaseClasses().size();
    for (int i = 0; i < nb; ++i)
    {
        TypeSymbol* baseClass = classType->BaseClasses()[i];
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        BoundExpressionNode* thisPtr = new BoundParameterNode(classDefaultCtor->ThisParam(context), sourcePos, 
            classDefaultCtor->ThisParam(context)->GetReferredType(context));
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            baseClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
        if (conversion)
        {
            std::vector<TypeSymbol*> templateArgs;
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
                context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
            if (boundFunctionCall->MayThrow())
            {
                setNoExcept = false;
            }
            BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
            expressionStatement->SetExpr(boundFunctionCall.release(), sourcePos, context);
            context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
        }
        else
        {
            ThrowException("base class conversion not found", sourcePos, context);
        }
    }
    if (classType->IsPolymorphic())
    {
        std::vector<ClassTypeSymbol*> vptrHolderClasses = classType->VPtrHolderClasses();
        if (vptrHolderClasses.empty())
        {
            ThrowException("no vptr holder classes for the class '" + util::ToUtf8(classType->FullName()) + "'", sourcePos, context);
        }
        for (ClassTypeSymbol* vptrHolderClass : vptrHolderClasses)
        {
            if (vptrHolderClass != classType)
            {
                BoundExpressionNode* thisPtr = new BoundParameterNode(classDefaultCtor->ThisParam(context), sourcePos, 
                    classDefaultCtor->ThisParam(context)->GetReferredType(context));
                FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    vptrHolderClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
                if (conversion)
                {
                    BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr, conversion, sourcePos);
                    BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtrConverted, classType, vptrHolderClass, sourcePos);
                    context->GetBoundFunction()->Body()->AddStatement(setVPtrStatement);
                }
                else
                {
                    ThrowException("vptr holder class conversion not found", sourcePos, context);
                }
            }
            else
            {
                BoundExpressionNode* thisPtr = new BoundParameterNode(classDefaultCtor->ThisParam(context), sourcePos, 
                    classDefaultCtor->ThisParam(context)->GetReferredType(context));
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
        boundMemberVariable->SetThisPtr(new BoundParameterNode(classDefaultCtor->ThisParam(context), sourcePos, 
            classDefaultCtor->ThisParam(context)->GetReferredType(context)));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::vector<TypeSymbol*> templateArgs;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundMemberVariable, sourcePos, 
            boundMemberVariable->GetType()->AddPointer(context))));
        std::unique_ptr<BoundFunctionCallNode> memberConstructorCall = ResolveOverloadThrow(classType->GetScope(), U"@constructor", templateArgs, 
            args, sourcePos, context);
        if (memberConstructorCall->MayThrow())
        {
            setNoExcept = false;
        }
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        expressionStatement->SetExpr(memberConstructorCall.release(), sourcePos, context);
        context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
    }
    if (!context->GetFlag(ContextFlags::leaveBoundFunction))
    {
        context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
        context->PopBoundFunction();
    }
    if (classType->TotalMemberCount() <= inlineClassOperationsThreshold)
    {
        classDefaultCtor->SetInline();
    }
    if (setNoExcept)
    {
        classDefaultCtor->SetNoExcept();
    }
}

FunctionDefinitionSymbol* GenerateClassDefaultCtor(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::unique_ptr<ClassDefaultCtor> defaultCtor(new ClassDefaultCtor(classType, sourcePos, context));
    ClassDefaultCtorOperation operation;
    context->PushSetFlag(ContextFlags::leaveBoundFunction);
    operation.GenerateImplementation(defaultCtor.get(), sourcePos, context);
    context->PopFlags();
    return defaultCtor.release();
}

class ClassCopyCtor : public FunctionDefinitionSymbol
{
public:
    ClassCopyCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    ~ClassCopyCtor();
    ClassTypeSymbol* ClassType() const { return classType; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassCopyCtor::ClassCopyCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionDefinitionSymbol(U"@class_copy_ctor"), classType(classType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetGenerated();
    SetAccess(Access::public_);
    SetParent(classType);
    ParameterSymbol* thisParam = ThisParam(context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", classType->AddConst(context)->AddLValueRef(context));
    AddParameter(thatParam, sourcePos, context);
    SetReturnType(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType), context);
    std::string digestSource = util::ToUtf8(classType->FullName());
    digestSource.append(1, '.').append(classType->IrName(context));
    digestSource.append(context->GetBoundCompileUnit()->Id());
    irName = "copy_ctor_" + util::ToUtf8(classType->Group()->Name()) + "_" + util::GetSha1MessageDigest(digestSource);
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
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    void GenerateImplementation(ClassCopyCtor* classCopyCtor, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

ClassCopyCtorOperation::ClassCopyCtorOperation() : Operation(U"@constructor", 2)
{
}

FunctionSymbol* ClassCopyCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    if (type->PointerCount() != 1 || !type->RemovePointer(context)->RemoveConst(context)->IsClassTypeSymbol()) return nullptr;
    if (!args[1]->GetType()->PlainType(context)->IsClassTypeSymbol()) return nullptr;
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(type->GetBaseType());
    if (classType->IsClassTemplateSpecializationSymbol() && context->GetFlag(ContextFlags::ignoreClassTemplateSpecializations)) return nullptr;
    if (TypesEqual(args[1]->GetType(), classType->AddRValueRef(context), context) || args[1]->BindToRvalueRef()) return nullptr;
    int distance = 0;
    if (!TypesEqual(args[1]->GetType()->GetBaseType(), classType, context) && 
        !args[1]->GetType()->GetBaseType()->HasBaseClass(classType, distance, context)) return nullptr;
    FunctionSymbol* copyCtor = classType->GetFunctionByIndex(copyCtorIndex);
    if (copyCtor)
    {
        return copyCtor;
    }
    auto it = functionMap.find(classType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    ClassCopyCtor* function = new ClassCopyCtor(classType, sourcePos, context);
    function->SetParent(classType);
    GenerateImplementation(function, sourcePos, context);
    functionMap[classType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

void ClassCopyCtorOperation::GenerateImplementation(ClassCopyCtor* classCopyCtor, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    ClassTypeSymbol* classType = classCopyCtor->ClassType();
    if (!classType->ObjectLayoutComputed())
    {
        classType->MakeObjectLayout(sourcePos, context);
    }
    std::unique_ptr<BoundFunctionNode> boundFunction(new BoundFunctionNode(classCopyCtor, sourcePos));
    boundFunction->SetBody(new BoundCompoundStatementNode(sourcePos));
    context->PushBoundFunction(boundFunction.release());
    bool setNoExcept = true;
    int nb = classType->BaseClasses().size();
    for (int i = 0; i < nb; ++i)
    {
        TypeSymbol* baseClass = classType->BaseClasses()[i];
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        BoundExpressionNode* thisPtr = new BoundParameterNode(classCopyCtor->ThisParam(context), sourcePos, classCopyCtor->ThisParam(context)->GetReferredType(context));
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            baseClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
        if (conversion)
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            ParameterSymbol* thatParam = classCopyCtor->MemFunParameters(context)[1];
            FunctionSymbol* thatConversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                baseClass->AddConst(context)->AddLValueRef(context), thatParam->GetType(), sourcePos, context);
            if (thatConversion)
            {
                BoundExpressionNode* thatPtr = new BoundParameterNode(thatParam, sourcePos, thatParam->GetType());
                args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thatPtr, thatConversion, sourcePos)));
                std::vector<TypeSymbol*> templateArgs;
                std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
                    context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
                if (boundFunctionCall->MayThrow())
                {
                    setNoExcept = false;
                }
                BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
                expressionStatement->SetExpr(boundFunctionCall.release(), sourcePos, context);
                context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
            }
            else
            {
                ThrowException("base class conversion not found", sourcePos, context);
            }
        }
        else
        {
            ThrowException("base class conversion not found", sourcePos, context);
        }
    }
    if (classType->IsPolymorphic())
    {
        std::vector<ClassTypeSymbol*> vptrHolderClasses = classType->VPtrHolderClasses();
        if (vptrHolderClasses.empty())
        {
            ThrowException("no vptr holder classes for the class '" + util::ToUtf8(classType->FullName()) + "'", sourcePos, context);
        }
        for (ClassTypeSymbol* vptrHolderClass : vptrHolderClasses)
        {
            if (vptrHolderClass != classType)
            {
                BoundExpressionNode* thisPtr = new BoundParameterNode(classCopyCtor->ThisParam(context), sourcePos, 
                    classCopyCtor->ThisParam(context)->GetReferredType(context));
                FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    vptrHolderClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
                if (conversion)
                {
                    BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr, conversion, sourcePos);
                    BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtrConverted, classType, vptrHolderClass, sourcePos);
                    context->GetBoundFunction()->Body()->AddStatement(setVPtrStatement);
                }
                else
                {
                    ThrowException("vptr holder class conversion not found", sourcePos, context);
                }
            }
            else
            {
                BoundExpressionNode* thisPtr = new BoundParameterNode(classCopyCtor->ThisParam(context), sourcePos, 
                    classCopyCtor->ThisParam(context)->GetReferredType(context));
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
        boundMemberVariable->SetThisPtr(new BoundParameterNode(classCopyCtor->ThisParam(context), sourcePos, classCopyCtor->ThisParam(context)->GetReferredType(context)));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundMemberVariable, sourcePos, 
            boundMemberVariable->GetType()->AddPointer(context))));
        ParameterSymbol* thatParam = classCopyCtor->MemFunParameters(context)[1];
        BoundVariableNode* thatBoundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        thatBoundMemberVariable->SetThisPtr(new BoundRefToPtrNode(
            new BoundParameterNode(thatParam, sourcePos, thatParam->GetReferredType(context)), sourcePos, 
            thatParam->GetType()->RemoveReference(context)->AddPointer(context)));
        args.push_back(std::unique_ptr<BoundExpressionNode>(thatBoundMemberVariable));
        std::vector<TypeSymbol*> templateArgs;
        std::unique_ptr<BoundFunctionCallNode> memberConstructorCall = ResolveOverloadThrow(classType->GetScope(), U"@constructor", templateArgs, args, 
            sourcePos, context);
        if (memberConstructorCall->MayThrow())
        {
            setNoExcept = false;
        }
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        expressionStatement->SetExpr(memberConstructorCall.release(), sourcePos, context);
        context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
    }
    if (!context->GetFlag(ContextFlags::leaveBoundFunction))
    {
        context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
        context->PopBoundFunction();
    }
    if (classType->TotalMemberCount() <= inlineClassOperationsThreshold)
    {
        classCopyCtor->SetInline();
    }
    if (setNoExcept)
    {
        classCopyCtor->SetNoExcept();
    }
}

FunctionDefinitionSymbol* GenerateClassCopyCtor(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::unique_ptr<ClassCopyCtor> copyCtor(new ClassCopyCtor(classType, sourcePos, context));
    ClassCopyCtorOperation operation;
    context->PushSetFlag(ContextFlags::leaveBoundFunction);
    operation.GenerateImplementation(copyCtor.get(), sourcePos, context);
    context->PopFlags();
    return copyCtor.release();
}

class ClassMoveCtor : public FunctionDefinitionSymbol
{
public:
    ClassMoveCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    ClassTypeSymbol* ClassType() const { return classType; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassMoveCtor::ClassMoveCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionDefinitionSymbol(U"@class_move_ctor"), classType(classType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetGenerated();
    SetAccess(Access::public_);
    SetParent(classType);
    ParameterSymbol* thisParam = ThisParam(context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", classType->AddRValueRef(context));
    AddParameter(thatParam, sourcePos, context);
    SetReturnType(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType), context);
    std::string digestSource = util::ToUtf8(classType->FullName());
    digestSource.append(1, '.').append(classType->IrName(context));
    digestSource.append(context->GetBoundCompileUnit()->Id());
    irName = "move_ctor_" + util::ToUtf8(classType->Group()->Name()) + "_" + util::GetSha1MessageDigest(digestSource);
    SetFixedIrName(irName);
    SetNoExcept();
}

class ClassMoveCtorOperation : public Operation
{
public:
    ClassMoveCtorOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    void GenerateImplementation(ClassMoveCtor* classMoveCtor, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

ClassMoveCtorOperation::ClassMoveCtorOperation() : Operation(U"@constructor", 2)
{
}

FunctionSymbol* ClassMoveCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    if (type->PointerCount() != 1 || !type->RemovePointer(context)->RemoveConst(context)->IsClassTypeSymbol()) return nullptr;
    if (!args[1]->GetType()->PlainType(context)->IsClassTypeSymbol()) return nullptr;
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(type->GetBaseType());
    if (classType->IsClassTemplateSpecializationSymbol() && context->GetFlag(ContextFlags::ignoreClassTemplateSpecializations)) return nullptr;
    if (!TypesEqual(args[1]->GetType(), classType->AddRValueRef(context), context) && !args[1]->BindToRvalueRef()) return nullptr;
    int distance = 0;
    if (!TypesEqual(args[1]->GetType()->GetBaseType(), classType, context) && 
        !args[1]->GetType()->GetBaseType()->HasBaseClass(classType, distance, context)) return nullptr;
    FunctionSymbol* moveCtor = classType->GetFunctionByIndex(moveCtorIndex);
    if (moveCtor)
    {
        return moveCtor;
    }
    auto it = functionMap.find(classType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    ClassMoveCtor* function = new ClassMoveCtor(classType, sourcePos, context);
    function->SetParent(classType);
    GenerateImplementation(function, sourcePos, context);
    functionMap[classType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

void ClassMoveCtorOperation::GenerateImplementation(ClassMoveCtor* classMoveCtor, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    ClassTypeSymbol* classType = classMoveCtor->ClassType();
    if (!classType->ObjectLayoutComputed())
    {
        classType->MakeObjectLayout(sourcePos, context);
    }
    std::unique_ptr<BoundFunctionNode> boundFunction(new BoundFunctionNode(classMoveCtor, sourcePos));
    boundFunction->SetBody(new BoundCompoundStatementNode(sourcePos));
    context->PushBoundFunction(boundFunction.release());
    int nb = classType->BaseClasses().size();
    for (int i = 0; i < nb; ++i)
    {
        TypeSymbol* baseClass = classType->BaseClasses()[i];
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        BoundExpressionNode* thisPtr = new BoundParameterNode(classMoveCtor->ThisParam(context), sourcePos, classMoveCtor->ThisParam(context)->GetReferredType(context));
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            baseClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
        if (conversion)
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            ParameterSymbol* thatParam = classMoveCtor->MemFunParameters(context)[1];
            FunctionSymbol* thatParamConversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                baseClass->AddRValueRef(context), thatParam->GetType(), sourcePos, context);
            if (thatParamConversion)
            {
                BoundExpressionNode* thatPtr = new BoundParameterNode(thatParam, sourcePos, thatParam->GetType());
                args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thatPtr, thatParamConversion, sourcePos)));
                std::vector<TypeSymbol*> templateArgs;
                std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
                    context->GetSymbolTable()->CurrentScope(), U"@constructor", templateArgs, args, sourcePos, context);
                BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
                expressionStatement->SetExpr(boundFunctionCall.release(), sourcePos, context);
                context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
            }
            else
            {
                ThrowException("base class conversion not found", sourcePos, context);
            }
        }
        else
        {
            ThrowException("base class conversion not found", sourcePos, context);
        }
    }
    if (classType->IsPolymorphic())
    {
        std::vector<ClassTypeSymbol*> vptrHolderClasses = classType->VPtrHolderClasses();
        if (vptrHolderClasses.empty())
        {
            ThrowException("no vptr holder classes for the class '" + util::ToUtf8(classType->FullName()) + "'", sourcePos, context);
        }
        for (ClassTypeSymbol* vptrHolderClass : vptrHolderClasses)
        {
            if (vptrHolderClass != classType)
            {
                BoundExpressionNode* thisPtr = new BoundParameterNode(classMoveCtor->ThisParam(context), sourcePos, 
                    classMoveCtor->ThisParam(context)->GetReferredType(context));
                FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                    vptrHolderClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
                if (conversion)
                {
                    BoundExpressionNode* thisPtrConverted = new BoundConversionNode(thisPtr, conversion, sourcePos);
                    BoundSetVPtrStatementNode* setVPtrStatement = new BoundSetVPtrStatementNode(thisPtrConverted, classType, vptrHolderClass, sourcePos);
                    context->GetBoundFunction()->Body()->AddStatement(setVPtrStatement);
                }
                else
                {
                    ThrowException("vptr holder class conversion not found", sourcePos, context);
                }
            }
            else
            {
                BoundExpressionNode* thisPtr = new BoundParameterNode(classMoveCtor->ThisParam(context), sourcePos, 
                    classMoveCtor->ThisParam(context)->GetReferredType(context));
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
        boundMemberVariable->SetThisPtr(new BoundParameterNode(classMoveCtor->ThisParam(context), sourcePos, classMoveCtor->ThisParam(context)->GetReferredType(context)));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        std::vector<TypeSymbol*> templateArgs;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundMemberVariable, sourcePos, 
            boundMemberVariable->GetType()->AddPointer(context))));
        ParameterSymbol* thatParam = classMoveCtor->MemFunParameters(context)[1];
        BoundVariableNode* thatBoundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        thatBoundMemberVariable->SetThisPtr(new BoundRefToPtrNode(
            new BoundParameterNode(thatParam, sourcePos, thatParam->GetReferredType(context)), sourcePos, 
            thatParam->GetType()->RemoveReference(context)->AddPointer(context)));
        if (thatBoundMemberVariable->GetType()->IsFunctionPtrType())
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(thatBoundMemberVariable));
        }
        else
        {
            std::vector<std::unique_ptr<BoundExpressionNode>> moveArgs;
            moveArgs.push_back(std::unique_ptr<BoundExpressionNode>(thatBoundMemberVariable));
            Scope* stdScope = context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context);
            std::unique_ptr<BoundFunctionCallNode> moveThat(ResolveOverloadThrow(
                stdScope, U"move", templateArgs, moveArgs, sourcePos, context));
            args.push_back(std::unique_ptr<BoundExpressionNode>(moveThat.release()));
        }
        std::unique_ptr<BoundFunctionCallNode> memberConstructorCall = ResolveOverloadThrow(classType->GetScope(), U"@constructor", 
            templateArgs, args, sourcePos, context);
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        expressionStatement->SetExpr(memberConstructorCall.release(), sourcePos, context);
        context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
    }
    if (!context->GetFlag(ContextFlags::leaveBoundFunction))
    {
        context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
        context->PopBoundFunction();
    }
    if (classType->TotalMemberCount() <= inlineClassOperationsThreshold)
    {
        classMoveCtor->SetInline();
    }
}

FunctionDefinitionSymbol* GenerateClassMoveCtor(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::unique_ptr<ClassMoveCtor> classMoveCtor(new ClassMoveCtor(classType, sourcePos, context));;
    ClassMoveCtorOperation operation;
    context->PushSetFlag(ContextFlags::leaveBoundFunction);
    operation.GenerateImplementation(classMoveCtor.get(), sourcePos, context);
    context->PopFlags();
    return classMoveCtor.release();
}

class ClassCopyAssignment: public FunctionDefinitionSymbol
{
public:
    ClassCopyAssignment(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    ClassTypeSymbol* ClassType() const { return classType; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassCopyAssignment::ClassCopyAssignment(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionDefinitionSymbol(U"operator="), classType(classType_)
{
    SetFunctionKind(FunctionKind::special);
    SetGenerated();
    SetAccess(Access::public_);
    SetParent(classType);
    ParameterSymbol* thisParam = ThisParam(context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", classType->AddConst(context)->AddLValueRef(context));
    AddParameter(thatParam, sourcePos, context);
    SetReturnType(classType->AddLValueRef(context), context);
    std::string digestSource = util::ToUtf8(classType->FullName());
    digestSource.append(1, '.').append(classType->IrName(context));
    digestSource.append(context->GetBoundCompileUnit()->Id());
    irName = "copy_assignment_" + util::ToUtf8(classType->Group()->Name()) + "_" + util::GetSha1MessageDigest(digestSource);
    SetFixedIrName(irName);
}

class ClassCopyAssignmentOperation : public Operation
{
public:
    ClassCopyAssignmentOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    void GenerateImplementation(ClassCopyAssignment* classCopyAssignment, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

ClassCopyAssignmentOperation::ClassCopyAssignmentOperation() : Operation(U"operator=", 2)
{
}

FunctionSymbol* ClassCopyAssignmentOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    if (type->PointerCount() != 1 || !type->RemovePointer(context)->PlainType(context)->IsClassTypeSymbol()) return nullptr;
    if (!args[1]->GetType()->PlainType(context)->IsClassTypeSymbol()) return nullptr;
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(type->GetBaseType());
    if (classType->IsClassTemplateSpecializationSymbol() && context->GetFlag(ContextFlags::ignoreClassTemplateSpecializations)) return nullptr;
    if (TypesEqual(args[1]->GetType(), classType->AddRValueRef(context), context) || args[1]->BindToRvalueRef()) return nullptr;
    FunctionSymbol* copyAssignment = classType->GetFunctionByIndex(copyAssignmentIndex);
    if (copyAssignment)
    {
        return copyAssignment;
    }
    auto it = functionMap.find(classType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    ClassCopyAssignment* function = new ClassCopyAssignment(classType, sourcePos, context);
    function->SetParent(classType);
    GenerateImplementation(function, sourcePos, context);
    functionMap[classType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

void ClassCopyAssignmentOperation::GenerateImplementation(ClassCopyAssignment* classCopyAssignment, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    ClassTypeSymbol* classType = classCopyAssignment->ClassType();
    std::unique_ptr<BoundFunctionNode> boundFunction(new BoundFunctionNode(classCopyAssignment, sourcePos));
    boundFunction->SetBody(new BoundCompoundStatementNode(sourcePos));
    context->PushBoundFunction(boundFunction.release());
    bool setNoExcept = true;
    int nb = classType->BaseClasses().size();
    for (int i = 0; i < nb; ++i)
    {
        TypeSymbol* baseClass = classType->BaseClasses()[i];
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        BoundExpressionNode* thisPtr = new BoundParameterNode(classCopyAssignment->ThisParam(context), sourcePos, 
            classCopyAssignment->ThisParam(context)->GetReferredType(context));
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            baseClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
        if (conversion)
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            ParameterSymbol* thatParam = classCopyAssignment->MemFunParameters(context)[1];
            BoundExpressionNode* thatPtr = new BoundParameterNode(thatParam, sourcePos, thatParam->GetType());
            FunctionSymbol* thatConversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                baseClass->AddConst(context)->AddLValueRef(context), thatParam->GetType(), sourcePos, context);
            if (thatConversion)
            {
                args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thatPtr, thatConversion, sourcePos)));
                std::vector<TypeSymbol*> templateArgs;
                std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
                    context->GetSymbolTable()->CurrentScope(), U"operator=", templateArgs, args, sourcePos, context);
                if (boundFunctionCall->MayThrow())
                {
                    setNoExcept = false;
                }
                BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
                expressionStatement->SetExpr(boundFunctionCall.release(), sourcePos, context);
                context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
            }
            else
            {
                ThrowException("base class conversion not found", sourcePos, context);
            }
        }
        else
        {
            ThrowException("base class conversion not found", sourcePos, context);
        }
    }
    int n = classType->MemberVariables().size();
    for (int i = 0; i < n; ++i)
    {
        VariableSymbol* memberVariableSymbol = classType->MemberVariables()[i];
        BoundVariableNode* boundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        boundMemberVariable->SetThisPtr(new BoundParameterNode(classCopyAssignment->ThisParam(context), sourcePos, 
            classCopyAssignment->ThisParam(context)->GetReferredType(context)));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundMemberVariable, sourcePos, 
            boundMemberVariable->GetType()->AddPointer(context))));
        ParameterSymbol* thatParam = classCopyAssignment->MemFunParameters(context)[1];
        BoundVariableNode* thatBoundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        thatBoundMemberVariable->SetThisPtr(new BoundRefToPtrNode(
            new BoundParameterNode(thatParam, sourcePos, thatParam->GetReferredType(context)), sourcePos, 
            thatParam->GetType()->RemoveReference(context)->AddPointer(context)));
        args.push_back(std::unique_ptr<BoundExpressionNode>(thatBoundMemberVariable));
        std::vector<TypeSymbol*> templateArgs;
        std::unique_ptr<BoundFunctionCallNode> memberAssignmentrCall = ResolveOverloadThrow(classType->GetScope(), U"operator=", templateArgs, args, sourcePos, context);
        if (memberAssignmentrCall->MayThrow())
        {
            setNoExcept = false;
        }
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        expressionStatement->SetExpr(memberAssignmentrCall.release(), sourcePos, context);
        context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
    }
    BoundReturnStatementNode* returnStatement = new BoundReturnStatementNode(sourcePos);
    otava::ast::ThisNode* thisNode(new otava::ast::ThisNode(sourcePos));
    otava::ast::UnaryExprNode derefNode(sourcePos, new otava::ast::DerefNode(sourcePos), thisNode);
    BoundExpressionNode* derefThisExpr = BindExpression(&derefNode, context);
    returnStatement->SetExpr(derefThisExpr, sourcePos, context);
    context->GetBoundFunction()->Body()->AddStatement(returnStatement);
    if (!context->GetFlag(ContextFlags::leaveBoundFunction))
    {
        context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
        context->PopBoundFunction();
    }
    if (classType->TotalMemberCount() <= inlineClassOperationsThreshold)
    {
        classCopyAssignment->SetInline();
    }
    if (setNoExcept)
    {
        classCopyAssignment->SetNoExcept();
    }
}

FunctionDefinitionSymbol* GenerateClassCopyAssignment(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::unique_ptr<ClassCopyAssignment> copyAssignment(new ClassCopyAssignment(classType, sourcePos, context));
    ClassCopyAssignmentOperation operation;
    context->PushSetFlag(ContextFlags::leaveBoundFunction);
    operation.GenerateImplementation(copyAssignment.get(), sourcePos, context);
    context->PopFlags();
    return copyAssignment.release();
}

class ClassMoveAssignment : public FunctionDefinitionSymbol
{
public:
    ClassMoveAssignment(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    ClassTypeSymbol* ClassType() const { return classType; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassMoveAssignment::ClassMoveAssignment(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionDefinitionSymbol(U"operator="), classType(classType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetGenerated();
    SetAccess(Access::public_);
    SetParent(classType);
    ParameterSymbol* thisParam = ThisParam(context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", classType->AddRValueRef(context));
    AddParameter(thatParam, sourcePos, context);
    SetReturnType(classType->AddLValueRef(context), context);
    std::string digestSource = util::ToUtf8(classType->FullName());
    digestSource.append(1, '.').append(classType->IrName(context));
    digestSource.append(context->GetBoundCompileUnit()->Id());
    irName = "move_assignment_" + util::ToUtf8(classType->Group()->Name()) + "_" + util::GetSha1MessageDigest(digestSource);
    SetFixedIrName(irName);
    SetNoExcept();
}

class ClassMoveAssignmentOperation : public Operation
{
public:
    ClassMoveAssignmentOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    void GenerateImplementation(ClassMoveAssignment* classMoveAssignment, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
private:
    std::map<TypeSymbol*, FunctionSymbol*> functionMap;
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

ClassMoveAssignmentOperation::ClassMoveAssignmentOperation() : Operation(U"operator=", 2)
{
}

FunctionSymbol* ClassMoveAssignmentOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    if (type->PointerCount() != 1 || !type->RemovePointer(context)->PlainType(context)->IsClassTypeSymbol()) return nullptr;
    if (!args[1]->GetType()->PlainType(context)->IsClassTypeSymbol()) return nullptr;
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(type->GetBaseType());
    if (classType->IsClassTemplateSpecializationSymbol() && context->GetFlag(ContextFlags::ignoreClassTemplateSpecializations)) return nullptr;
    if (!TypesEqual(args[1]->GetType(), classType->AddRValueRef(context), context) && !args[1]->BindToRvalueRef()) return nullptr;
    FunctionSymbol* moveAssignment = classType->GetFunctionByIndex(moveAssignmentIndex);
    if (moveAssignment)
    {
        return moveAssignment;
    }
    auto it = functionMap.find(classType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    ClassMoveAssignment* function = new ClassMoveAssignment(classType, sourcePos, context);
    function->SetParent(classType);
    GenerateImplementation(function, sourcePos, context);
    functionMap[classType] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

void ClassMoveAssignmentOperation::GenerateImplementation(ClassMoveAssignment* classMoveAssignment, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
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
        BoundExpressionNode* thisPtr = new BoundParameterNode(classMoveAssignment->ThisParam(context), sourcePos, 
            classMoveAssignment->ThisParam(context)->GetReferredType(context));
        FunctionSymbol* conversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            baseClass->AddPointer(context), thisPtr->GetType(), sourcePos, context);
        if (conversion)
        {
            args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thisPtr, conversion, sourcePos)));
            ParameterSymbol* thatParam = classMoveAssignment->MemFunParameters(context)[1];
            BoundExpressionNode* thatPtr = new BoundParameterNode(thatParam, sourcePos, thatParam->GetType());
            FunctionSymbol* thatConversion = context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
                baseClass->AddRValueRef(context), thatParam->GetType(), sourcePos, context);
            std::vector<std::unique_ptr<BoundExpressionNode>> moveArgs;
            moveArgs.push_back(std::unique_ptr<BoundExpressionNode>(new BoundConversionNode(thatPtr, thatConversion, sourcePos)));
            Scope* stdScope = context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context);
            std::vector<TypeSymbol*> templateArgs;
            std::unique_ptr<BoundFunctionCallNode> moveThat(ResolveOverloadThrow(
                stdScope, U"move", templateArgs, moveArgs, sourcePos, context));
            args.push_back(std::unique_ptr<BoundExpressionNode>(moveThat.release()));
            std::unique_ptr<BoundFunctionCallNode> boundFunctionCall = ResolveOverloadThrow(
                context->GetSymbolTable()->CurrentScope(), U"operator=", templateArgs, args, sourcePos, context);
            BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
            expressionStatement->SetExpr(boundFunctionCall.release(), sourcePos, context);
            context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
        }
        else
        {
            ThrowException("base class conversion not found", sourcePos, context);
        }
    }
    int n = classType->MemberVariables().size();
    for (int i = 0; i < n; ++i)
    {
        VariableSymbol* memberVariableSymbol = classType->MemberVariables()[i];
        BoundVariableNode* boundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        boundMemberVariable->SetThisPtr(new BoundParameterNode(classMoveAssignment->ThisParam(context), sourcePos, 
            classMoveAssignment->ThisParam(context)->GetReferredType(context)));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        args.push_back(std::unique_ptr<BoundExpressionNode>(boundMemberVariable));
        ParameterSymbol* thatParam = classMoveAssignment->MemFunParameters(context)[1];
        BoundVariableNode* thatBoundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        thatBoundMemberVariable->SetThisPtr(new BoundRefToPtrNode(
            new BoundParameterNode(thatParam, sourcePos, thatParam->GetReferredType(context)), sourcePos, 
            thatParam->GetType()->RemoveReference(context)->AddPointer(context)));
        args.push_back(std::unique_ptr<BoundExpressionNode>(thatBoundMemberVariable));
        Scope* stdScope = context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context);
        std::vector<TypeSymbol*> templateArgs;
        std::unique_ptr<BoundFunctionCallNode> memberConstructorCall = ResolveOverloadThrow(stdScope, U"swap", templateArgs, args, sourcePos, context);
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        expressionStatement->SetExpr(memberConstructorCall.release(), sourcePos, context);
        context->GetBoundFunction()->Body()->AddStatement(expressionStatement);
    }
    BoundReturnStatementNode* returnStatement = new BoundReturnStatementNode(sourcePos);
    otava::ast::ThisNode* thisNode(new otava::ast::ThisNode(sourcePos));
    otava::ast::UnaryExprNode derefNode(sourcePos, new otava::ast::DerefNode(sourcePos), thisNode);
    BoundExpressionNode* derefThisExpr = BindExpression(&derefNode, context);
    returnStatement->SetExpr(derefThisExpr, sourcePos, context);
    context->GetBoundFunction()->Body()->AddStatement(returnStatement);
    if (!context->GetFlag(ContextFlags::leaveBoundFunction))
    {
        context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
        context->PopBoundFunction();
    }
    if (classType->TotalMemberCount() <= inlineClassOperationsThreshold)
    {
        classMoveAssignment->SetInline();
    }
}

FunctionDefinitionSymbol* GenerateClassMoveAssignment(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::unique_ptr<ClassMoveAssignment> moveAssignment(new ClassMoveAssignment(classType, sourcePos, context));
    ClassMoveAssignmentOperation operation;
    context->PushSetFlag(ContextFlags::leaveBoundFunction);
    operation.GenerateImplementation(moveAssignment.get(), sourcePos, context);
    context->PopFlags();
    return moveAssignment.release();
}

class FunctionPtrApply : public FunctionSymbol
{
public:
    FunctionPtrApply(FunctionTypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
private:
    FunctionTypeSymbol* functionType;
};

FunctionPtrApply::FunctionPtrApply(FunctionTypeSymbol* functionType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) : 
    FunctionSymbol(U"operator()"), functionType(functionType_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* parameter = new ParameterSymbol(U"fn", functionType->AddPointer(context));
    AddSymbol(parameter, sourcePos, context);
    for (TypeSymbol* parameterType : functionType->ParameterTypes())
    {
        ParameterSymbol* parameter = new ParameterSymbol(U"@param", parameterType);
        AddSymbol(parameter, sourcePos, context);
    }
    SetReturnType(functionType->ReturnType(), context);
}

void FunctionPtrApply::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* callee = emitter.Stack().Pop();
    int na = args.size() - 1;
    for (int i = 0; i < na; ++i)
    {
        args[i + 1]->Load(emitter, OperationFlags::none, sourcePos, context);
    }
    std::vector<otava::intermediate::Value*> arguments;
    arguments.resize(na);
    for (int i = 0; i < na; ++i)
    {
        otava::intermediate::Value* arg = emitter.Stack().Pop();
        arguments[na - i - 1] = arg;
    }
    emitter.EmitCall(callee, arguments);
}

class FunctionPtrApplyOperation : public Operation
{
public:
    FunctionPtrApplyOperation();
    FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    std::vector<std::unique_ptr<FunctionSymbol>> functions;
};

FunctionPtrApplyOperation::FunctionPtrApplyOperation() : Operation(U"operator()", -1)
{
}

FunctionSymbol* FunctionPtrApplyOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    if (args.size() < 1) return nullptr;
    TypeSymbol* type = args[0]->GetType();
    if (type->PointerCount() != 1) return nullptr;
    TypeSymbol* pointeeType = type->RemovePointer(context);
    if (!pointeeType->IsFunctionTypeSymbol()) return nullptr;
    FunctionTypeSymbol* functionType = static_cast<FunctionTypeSymbol*>(pointeeType);
    FunctionPtrApply* apply = new FunctionPtrApply(functionType, sourcePos, context);
    functions.push_back(std::unique_ptr<FunctionSymbol>(apply));
    return apply;
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

FunctionSymbol* OperationGroup::GetOperation(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos,
    otava::symbols::Context* context)
{
    auto it = arityOperationsMap.find(args.size());
    if (it != arityOperationsMap.cend())
    {
        const std::vector<Operation*>& operations = it->second;
        for (Operation* operation : operations)
        {
            FunctionSymbol* op = operation->Get(args, sourcePos, context);
            if (op)
            {
                return op;
            }
        }
    }
    for (Operation* operation : anyArityOperations)
    {
        FunctionSymbol* op = operation->Get(args, sourcePos, context);
        if (op)
        {
            return op;
        }
    }
    return nullptr;
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

FunctionSymbol* OperationRepository::GetOperation(const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    auto it = groupMap.find(groupName);
    if (it != groupMap.cend())
    {
        OperationGroup* group = it->second;
        return group->GetOperation(args, sourcePos, context);
    }
    else
    {
        return nullptr;
    }
}

} // namespace otava::symbols

