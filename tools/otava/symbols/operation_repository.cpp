// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.operation.repository;

import otava.symbols.type.symbol;
import otava.symbols.bound.tree;
import otava.symbols.bound.tree.visitor;
import otava.symbols.function.symbol;
import otava.symbols.bound.node;
import otava.symbols.context;
import otava.symbols.emitter;
import otava.symbols.argument.conversion.table;
import otava.symbols.symbol.table;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.classes;
import otava.symbols.overload.resolution;
import otava.symbols.exception;
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
private:
    TypeSymbol* type;
};

PointerDefaultCtor::PointerDefaultCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) : 
    FunctionSymbol(U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer());
    AddParameter(thisParam, sourcePos, context);
}

void PointerDefaultCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    if ((flags & OperationFlags::defaultInit) != OperationFlags::none)
    {
        emitter.Stack().Push(type->IrType(emitter, sourcePos, context)->DefaultValue());
        args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
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
    TypeSymbol* pointerType = type->RemovePointer();
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
private:
    TypeSymbol* type;
};

PointerCopyCtor::PointerCopyCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer());
    AddParameter(thisParam, sourcePos, context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    AddParameter(thatParam, sourcePos, context);
}

void PointerCopyCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
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

FunctionSymbol* PointerCopyCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return nullptr;
    if (type->IsReferenceType()) return nullptr;
    TypeSymbol* pointerType = type->RemovePointer();
    TypeSymbol* rvalueRefType = pointerType->AddRValueRef();
    if (TypesEqual(args[1]->GetType(), rvalueRefType)) return nullptr;
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
private:
    TypeSymbol* type;
};

PointerMoveCtor::PointerMoveCtor(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer());
    AddParameter(thisParam, sourcePos, context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type->AddRValueRef());
    AddParameter(thatParam, sourcePos, context);
}

void PointerMoveCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* rvalueRefValue = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLoad(rvalueRefValue));
    args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
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
    TypeSymbol* pointerType = type->RemovePointer();
    TypeSymbol* rvalueRefType = pointerType->AddRValueRef();
    if (!TypesEqual(args[1]->GetType(), rvalueRefType) && !args[1]->BindToRvalueRef()) return nullptr;
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
private:
    TypeSymbol* type;
};

PointerCopyAssignment::PointerCopyAssignment(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator="), type(type_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer());
    AddParameter(thisParam, sourcePos, context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    AddParameter(thatParam, sourcePos, context);
    SetReturnType(type->AddLValueRef());
}

void PointerCopyAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
    args[0]->Load(emitter, OperationFlags::addr, sourcePos, context);
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

FunctionSymbol* PointerCopyAssignmentOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return nullptr;
    if (type->IsReferenceType()) return nullptr;
    TypeSymbol* pointerType = type->RemovePointer();
    if (TypesEqual(args[1]->GetType(), pointerType->AddRValueRef()) || args[1]->BindToRvalueRef()) return nullptr;
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
private:
    TypeSymbol* type;
};

PointerMoveAssignment::PointerMoveAssignment(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator="), type(type_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer());
    AddParameter(thisParam, sourcePos, context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type->AddRValueRef());
    AddParameter(thatParam, sourcePos, context);
    SetReturnType(type->AddLValueRef());
}

void PointerMoveAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* refValue = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLoad(refValue));
    args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
    args[0]->Load(emitter, OperationFlags::addr, sourcePos, context);
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

FunctionSymbol* PointerMoveAssignmentOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    BoundExpressionNode* arg = args[0].get();
    TypeSymbol* type = arg->GetType();
    if (type->PointerCount() <= 1) return nullptr;
    if (type->IsReferenceType()) return nullptr;
    TypeSymbol* pointerType = type->RemovePointer();
    if (!TypesEqual(args[1]->GetType(), pointerType->AddRValueRef()) && !args[1]->BindToRvalueRef()) return nullptr;
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
    SetReturnType(pointerType);
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

FunctionSymbol* PointerPlusOffsetOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    TypeSymbol* leftType = args[0]->GetType();
    if (!leftType->IsPointerType()) return nullptr;
    TypeSymbol* rightType = args[1]->GetType();
    if (!rightType->PlainType()->IsIntegralType())
    {
        if (!context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            rightType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), context))
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
    SetReturnType(pointerType);
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

FunctionSymbol* OffsetPlusPointerOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    TypeSymbol* leftType = args[0]->GetType();
    if (!leftType->PlainType()->IsIntegralType())
    {
        if (!context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            leftType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), context))
        {
            return nullptr;
        }
    }
    TypeSymbol* rightType = args[1]->GetType();
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
    SetReturnType(pointerType);
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

FunctionSymbol* PointerMinusOffsetOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    TypeSymbol* leftType = args[0]->GetType();
    if (!leftType->IsPointerType()) return nullptr;
    TypeSymbol* rightType = args[1]->GetType();
    if (!rightType->PlainType()->IsIntegralType())
    {
        if (!context->GetBoundCompileUnit()->GetArgumentConversionTable()->GetArgumentConversion(
            rightType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), context))
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
    PointerMinusOffset* function = new PointerMinusOffset(leftType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context);
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
    SetReturnType(longLongIntType);
}

void PointerMinusPointer::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* left = emitter.Stack().Pop();
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* right = emitter.Stack().Pop();
    emitter.EmitPtrDiff(left, right);
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

FunctionSymbol* PointerMinusPointerOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    TypeSymbol* leftType = args[0]->GetType();
    if (!leftType->IsPointerType()) return nullptr;
    TypeSymbol* rightType = args[1]->GetType();
    if (!rightType->IsPointerType()) return nullptr;
    auto it = functionMap.find(leftType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    PointerMinusPointer* function = new PointerMinusPointer(leftType, context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType), sourcePos, context);
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
    SetReturnType(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType));
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
    TypeSymbol* leftType = args[0]->GetType();
    if (!leftType->IsPointerType()) return nullptr;
    TypeSymbol* rightType = args[1]->GetType();
    if (!rightType->IsPointerType()) return nullptr;
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
    SetReturnType(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType));
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
    TypeSymbol* leftType = args[0]->GetType();
    if (!leftType->IsPointerType()) return nullptr;
    TypeSymbol* rightType = args[1]->GetType();
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
private:
    TypeSymbol* type;
};

PointerArrow::PointerArrow(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionSymbol(U"operator->"), type(type_)
{
    SetFunctionKind(FunctionKind::function);
    SetAccess(Access::public_);
    ParameterSymbol* operandParam = new ParameterSymbol(U"operand", type->AddPointer());
    AddParameter(operandParam, sourcePos, context);
    SetReturnType(type);
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
    TypeSymbol* type = operandType->RemovePointer();
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

class ClassDefaultCtor : public FunctionDefinitionSymbol
{
public:
    ClassDefaultCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    ClassTypeSymbol* ClassType() const { return classType; }
    std::string IrName() const override { return irName; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassDefaultCtor::ClassDefaultCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) : 
    FunctionDefinitionSymbol(U"@constructor"), classType(classType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    SetReturnType(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType));
    irName = "default_ctor_" + util::ToUtf8(classType->Name()) + "_" + util::GetSha1MessageDigest(util::ToUtf8(classType->FullName())) + "_" + context->GetBoundCompileUnit()->Id();
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

FunctionSymbol* ClassDefaultCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    if (type->PointerCount() != 1 || !type->RemovePointer()->PlainType()->IsClassTypeSymbol()) return nullptr;
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(type->GetBaseType());
    FunctionSymbol* defaultCtor = classType->GetFunction(defaultCtorIndex);
    if (defaultCtor)
    {
        return defaultCtor;
    }
    auto it = functionMap.find(classType);
    if (it != functionMap.cend())
    {
        FunctionSymbol* function = it->second;
        return function;
    }
    ClassDefaultCtor* function = new ClassDefaultCtor(classType, sourcePos, context);
    function->SetParent(classType);
    GenerateImplementation(function, sourcePos, context);
    functionMap[type] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

void ClassDefaultCtorOperation::GenerateImplementation(ClassDefaultCtor* classDefaultCtor, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ClassTypeSymbol* classType = classDefaultCtor->ClassType();
    std::unique_ptr<BoundFunctionNode> boundFunction(new BoundFunctionNode(classDefaultCtor, sourcePos));
    boundFunction->SetBody(new BoundCompoundStatementNode(sourcePos)); 
    int n = classType->MemberVariables().size();
    for (int i = 0; i < n; ++i)
    {
        VariableSymbol* memberVariableSymbol = classType->MemberVariables()[i];
        BoundVariableNode* boundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        boundMemberVariable->SetThisPtr(new BoundParameterNode(classDefaultCtor->ThisParam(), sourcePos));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundMemberVariable, sourcePos)));
        std::unique_ptr<BoundFunctionCallNode> memberConstructorCall = ResolveOverloadThrow(classType->GetScope(), U"@constructor", args, sourcePos, context);
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        expressionStatement->SetExpr(memberConstructorCall.release());
        boundFunction->Body()->AddStatement(expressionStatement);
    }
    context->GetBoundCompileUnit()->AddBoundNode(boundFunction.release());
}

class ClassCopyCtor : public FunctionDefinitionSymbol
{
public:
    ClassCopyCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    ClassTypeSymbol* ClassType() const { return classType; }
    std::string IrName() const override { return irName; }
private:
    ClassTypeSymbol* classType;
    std::string irName;
};

ClassCopyCtor::ClassCopyCtor(ClassTypeSymbol* classType_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    FunctionDefinitionSymbol(U"@constructor"), classType(classType_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = ThisParam();
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", classType->AddConst()->AddLValueRef());
    AddParameter(thatParam, sourcePos, context);
    SetReturnType(context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::voidType));
    irName = "copy_ctor_" + util::ToUtf8(classType->Name()) + "_" + util::GetSha1MessageDigest(util::ToUtf8(classType->FullName())) + "_" + context->GetBoundCompileUnit()->Id();
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

FunctionSymbol* ClassCopyCtorOperation::Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    TypeSymbol* type = args[0]->GetType();
    if (type->PointerCount() != 1 || !type->RemovePointer()->PlainType()->IsClassTypeSymbol()) return nullptr;
    ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(type->GetBaseType());
    if (TypesEqual(args[1]->GetType(), classType->AddRValueRef()) || args[1]->BindToRvalueRef()) return nullptr;
    FunctionSymbol* copyCtor = classType->GetFunction(copyCtorIndex);
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
    functionMap[type] = function;
    functions.push_back(std::unique_ptr<FunctionSymbol>(function));
    return function;
}

void ClassCopyCtorOperation::GenerateImplementation(ClassCopyCtor* classCopyCtor, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    ClassTypeSymbol* classType = classCopyCtor->ClassType();
    std::unique_ptr<BoundFunctionNode> boundFunction(new BoundFunctionNode(classCopyCtor, sourcePos));
    boundFunction->SetBody(new BoundCompoundStatementNode(sourcePos));
    int n = classType->MemberVariables().size();
    for (int i = 0; i < n; ++i)
    {
        VariableSymbol* memberVariableSymbol = classType->MemberVariables()[i];
        BoundVariableNode* boundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        boundMemberVariable->SetThisPtr(new BoundParameterNode(classCopyCtor->ThisParam(), sourcePos));
        std::vector<std::unique_ptr<BoundExpressionNode>> args;
        args.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundMemberVariable, sourcePos)));
        ParameterSymbol* thatParam = classCopyCtor->MemFunParameters()[1];
        BoundVariableNode* thatBoundMemberVariable = new BoundVariableNode(memberVariableSymbol, sourcePos);
        thatBoundMemberVariable->SetThisPtr(new BoundRefToPtrNode(new BoundParameterNode(thatParam, sourcePos), sourcePos));
        args.push_back(std::unique_ptr<BoundExpressionNode>(thatBoundMemberVariable));
        std::unique_ptr<BoundFunctionCallNode> memberConstructorCall = ResolveOverloadThrow(classType->GetScope(), U"@constructor", args, sourcePos, context);
        BoundExpressionStatementNode* expressionStatement = new BoundExpressionStatementNode(sourcePos);
        expressionStatement->SetExpr(memberConstructorCall.release());
        boundFunction->Body()->AddStatement(expressionStatement);
    }
    context->GetBoundCompileUnit()->AddBoundNode(boundFunction.release());
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
    arityOperationsMap[operation->Arity()].push_back(operation);
}

FunctionSymbol* OperationGroup::GetOperation(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos,
    otava::symbols::Context* context)
{
    auto it = arityOperationsMap.find(args.size());
    if (it != arityOperationsMap.cend())
    {
        const std::vector<Operation*>& operations = it->second;
        for (const auto& operation : operations)
        {
            FunctionSymbol* op = operation->Get(args, sourcePos, context);
            if (op)
            {
                return op;
            }
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

