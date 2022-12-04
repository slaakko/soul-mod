// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.fundamental.type.operation;

import otava.symbols.fundamental.type.conversion.init;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.bound.tree;
import otava.symbols.symbol.table;
import otava.symbols.context;
import otava.symbols.namespaces;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.type.symbol;

namespace otava::symbols {

const char32_t* FundamentalTypeNot::GroupName()
{
    return U"operator!";
}

otava::intermediate::Value* FundamentalTypeNot::Generate(Emitter& emitter, otava::intermediate::Value* arg)
{
    return emitter.EmitNot(arg);
}

const char32_t* FundamentalTypeUnaryPlus::GroupName()
{
    return U"operator+";
}

otava::intermediate::Value* FundamentalTypeUnaryPlus::Generate(Emitter& emitter, otava::intermediate::Value* arg)
{
    return arg;
}

const char32_t* FundamentalTypeUnaryMinus::GroupName()
{
    return U"operator-";
}

otava::intermediate::Value* FundamentalTypeUnaryMinus::Generate(Emitter& emitter, otava::intermediate::Value* arg)
{
    return emitter.EmitNeg(arg);
}

const char32_t* FundamentalTypeComplement::GroupName()
{
    return U"operator~";
}

otava::intermediate::Value* FundamentalTypeComplement::Generate(Emitter& emitter, otava::intermediate::Value* arg)
{
    return emitter.EmitNot(arg);
}

const char32_t* FundamentalTypeAdd::GroupName()
{ 
    return U"operator+"; 
}

otava::intermediate::Value* FundamentalTypeAdd::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) 
{ 
    return emitter.EmitAdd(left, right); 
}

const char32_t* FundamentalTypeSub::GroupName() 
{ 
    return U"operator-"; 
}

otava::intermediate::Value* FundamentalTypeSub::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) 
{
    return emitter.EmitSub(left, right); 
}

const char32_t* FundamentalTypeMul::GroupName() 
{ 
    return U"operator*"; 
}

otava::intermediate::Value* FundamentalTypeMul::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitMul(left, right);
}

const char32_t* FundamentalTypeDiv::GroupName()
{ 
    return U"operator/"; 
}

otava::intermediate::Value* FundamentalTypeDiv::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) 
{ 
    return emitter.EmitDiv(left, right); 
}

const char32_t* FundamentalTypeMod::GroupName() 
{ 
    return U"operator%"; 
}

otava::intermediate::Value* FundamentalTypeMod::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{ 
    return emitter.EmitMod(left, right); 
}

const char32_t* FundamentalTypeAnd::GroupName() 
{ 
    return U"operator&"; 
}

otava::intermediate::Value* FundamentalTypeAnd::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) 
{ 
    return emitter.EmitAnd(left, right); 
}

const char32_t* FundamentalTypeOr::GroupName() 
{ 
    return U"operator|"; 
}

otava::intermediate::Value* FundamentalTypeOr::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) 
{ 
    return emitter.EmitOr(left, right); 
}

const char32_t* FundamentalTypeXor::GroupName() 
{ 
    return U"operator^"; 
}

otava::intermediate::Value* FundamentalTypeXor::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) 
{ 
    return emitter.EmitXor(left, right); 
}

const char32_t* FundamentalTypeShl::GroupName() 
{ 
    return U"operator<<"; 
}

otava::intermediate::Value* FundamentalTypeShl::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) 
{ 
    return emitter.EmitShl(left, right); 
}

const char32_t* FundamentalTypeShr::GroupName() 
{ 
    return U"operator>>"; 
}

otava::intermediate::Value* FundamentalTypeShr::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) 
{ 
    return emitter.EmitShr(left, right); 
}

const char32_t* FundamentalTypeEqual::GroupName() 
{ 
    return U"operator=="; 
}

otava::intermediate::Value* FundamentalTypeEqual::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) 
{ 
    return emitter.EmitEqual(left, right); 
}

const char32_t* FundamentalTypeLess::GroupName()
{ 
    return U"operator<"; 
}

otava::intermediate::Value* FundamentalTypeLess::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) 
{
    return emitter.EmitLess(left, right); 
}

FundamentalTypeNotOperation::FundamentalTypeNotOperation() : FundamentalTypeUnaryOperation<FundamentalTypeNot>(SymbolKind::fundamentalTypeNot)
{
}

FundamentalTypeNotOperation::FundamentalTypeNotOperation(TypeSymbol* type_, Context* context) : 
    FundamentalTypeUnaryOperation<FundamentalTypeNot>(SymbolKind::fundamentalTypeNot, type_, context)
{
}

FundamentalTypeUnaryPlusOperation::FundamentalTypeUnaryPlusOperation() : 
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryPlus>(SymbolKind::fundamentalTypeUnaryPlus)
{
}

FundamentalTypeUnaryPlusOperation::FundamentalTypeUnaryPlusOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryPlus>(SymbolKind::fundamentalTypeUnaryPlus, type_, context)
{
}

FundamentalTypeUnaryMinusOperation::FundamentalTypeUnaryMinusOperation() :
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryMinus>(SymbolKind::fundamentalTypeUnaryMinus)
{
}

FundamentalTypeUnaryMinusOperation::FundamentalTypeUnaryMinusOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryMinus>(SymbolKind::fundamentalTypeUnaryMinus, type_, context)
{
}

FundamentalTypeComplementOperation::FundamentalTypeComplementOperation() : 
    FundamentalTypeUnaryOperation<FundamentalTypeComplement>(SymbolKind::fundamentalTypeComplement)
{
}

FundamentalTypeComplementOperation::FundamentalTypeComplementOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeUnaryOperation<FundamentalTypeComplement>(SymbolKind::fundamentalTypeComplement, type_, context)
{
}

FundamentalTypeAddOperation::FundamentalTypeAddOperation() : FundamentalTypeBinaryOperation<FundamentalTypeAdd>(SymbolKind::fundamentalTypeAdd)
{
}

FundamentalTypeAddOperation::FundamentalTypeAddOperation(TypeSymbol* type_, Context* context) : 
    FundamentalTypeBinaryOperation<FundamentalTypeAdd>(SymbolKind::fundamentalTypeAdd, type_, context)
{
}

FundamentalTypeSubOperation::FundamentalTypeSubOperation() : FundamentalTypeBinaryOperation<FundamentalTypeSub>(SymbolKind::fundamentalTypeSub)
{
}

FundamentalTypeSubOperation::FundamentalTypeSubOperation(TypeSymbol* type_, Context* context) : 
    FundamentalTypeBinaryOperation<FundamentalTypeSub>(SymbolKind::fundamentalTypeSub, type_, context)
{
}

FundamentalTypeMulOperation::FundamentalTypeMulOperation() : FundamentalTypeBinaryOperation<FundamentalTypeMul>(SymbolKind::fundamentalTypeMul)
{
}

FundamentalTypeMulOperation::FundamentalTypeMulOperation(TypeSymbol* type_, Context* context) : 
    FundamentalTypeBinaryOperation<FundamentalTypeMul>(SymbolKind::fundamentalTypeMul, type_, context)
{
}

FundamentalTypeDivOperation::FundamentalTypeDivOperation() : FundamentalTypeBinaryOperation<FundamentalTypeDiv>(SymbolKind::fundamentalTypeDiv)
{
}

FundamentalTypeDivOperation::FundamentalTypeDivOperation(TypeSymbol* type_, Context* context) : 
    FundamentalTypeBinaryOperation<FundamentalTypeDiv>(SymbolKind::fundamentalTypeDiv, type_, context)
{
}

FundamentalTypeModOperation::FundamentalTypeModOperation() : FundamentalTypeBinaryOperation<FundamentalTypeMod>(SymbolKind::fundamentalTypeMod)
{
}

FundamentalTypeModOperation::FundamentalTypeModOperation(TypeSymbol* type_, Context* context) : 
    FundamentalTypeBinaryOperation<FundamentalTypeMod>(SymbolKind::fundamentalTypeMod, type_, context)
{
}

FundamentalTypeAndOperation::FundamentalTypeAndOperation() : FundamentalTypeBinaryOperation<FundamentalTypeAnd>(SymbolKind::fundamentalTypeAnd)
{
}

FundamentalTypeAndOperation::FundamentalTypeAndOperation(TypeSymbol* type_, Context* context) 
    : FundamentalTypeBinaryOperation<FundamentalTypeAnd>(SymbolKind::fundamentalTypeAnd, type_, context)
{
}

FundamentalTypeOrOperation::FundamentalTypeOrOperation() : FundamentalTypeBinaryOperation<FundamentalTypeOr>(SymbolKind::fundamentalTypeOr)
{
}

FundamentalTypeOrOperation::FundamentalTypeOrOperation(TypeSymbol* type_, Context* context) : 
    FundamentalTypeBinaryOperation<FundamentalTypeOr>(SymbolKind::fundamentalTypeOr, type_, context)
{
}

FundamentalTypeXorOperation::FundamentalTypeXorOperation() : FundamentalTypeBinaryOperation<FundamentalTypeXor>(SymbolKind::fundamentalTypeXor)
{
}

FundamentalTypeXorOperation::FundamentalTypeXorOperation(TypeSymbol* type_, Context* context) : 
    FundamentalTypeBinaryOperation<FundamentalTypeXor>(SymbolKind::fundamentalTypeXor, type_, context)
{
}

FundamentalTypeShlOperation::FundamentalTypeShlOperation() : FundamentalTypeBinaryOperation<FundamentalTypeShl>(SymbolKind::fundamentalTypeShl)
{
}

FundamentalTypeShlOperation::FundamentalTypeShlOperation(TypeSymbol* type_, Context* context) : 
    FundamentalTypeBinaryOperation<FundamentalTypeShl>(SymbolKind::fundamentalTypeShl, type_, context)
{
}

FundamentalTypeShrOperation::FundamentalTypeShrOperation() : FundamentalTypeBinaryOperation<FundamentalTypeShr>(SymbolKind::fundamentalTypeShr)
{
}

FundamentalTypeShrOperation::FundamentalTypeShrOperation(TypeSymbol* type_, Context* context) : 
    FundamentalTypeBinaryOperation<FundamentalTypeShr>(SymbolKind::fundamentalTypeShr, type_, context)
{
}

FundamentalTypeEqualOperation::FundamentalTypeEqualOperation() : FundamentalTypeComparisonOperation<FundamentalTypeEqual>(SymbolKind::fundamentalTypeEqual)
{
}

FundamentalTypeEqualOperation::FundamentalTypeEqualOperation(TypeSymbol* type_, TypeSymbol* boolType_, Context* context) : 
    FundamentalTypeComparisonOperation<FundamentalTypeEqual>(SymbolKind::fundamentalTypeEqual, type_, boolType_, context)
{
}

FundamentalTypeLessOperation::FundamentalTypeLessOperation() : FundamentalTypeComparisonOperation<FundamentalTypeLess>(SymbolKind::fundamentalTypeLess)
{
}

FundamentalTypeLessOperation::FundamentalTypeLessOperation(TypeSymbol* type_, TypeSymbol* boolType_, Context* context) :
    FundamentalTypeComparisonOperation<FundamentalTypeLess>(SymbolKind::fundamentalTypeLess, type_, boolType_, context)
{
}

FundamentalTypeDefaultCtor::FundamentalTypeDefaultCtor() : FunctionSymbol(SymbolKind::fundamentalTypeDefaultCtor, U"@constructor"), type(nullptr)
{
}

FundamentalTypeDefaultCtor::FundamentalTypeDefaultCtor(TypeSymbol* type_, Context* context) : 
    FunctionSymbol(SymbolKind::fundamentalTypeDefaultCtor, U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer());
    AddParameter(thisParam, soul::ast::SourcePos(), context);
}

void FundamentalTypeDefaultCtor::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(type->Id());
}

void FundamentalTypeDefaultCtor::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(typeId);
}

void FundamentalTypeDefaultCtor::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    type = symbolTable.GetType(typeId);
}

void FundamentalTypeDefaultCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    if ((flags & OperationFlags::defaultInit) != OperationFlags::none)
    {
        emitter.Stack().Push(type->IrType(emitter, sourcePos, context)->DefaultValue());
        args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
    }
}

FundamentalTypeCopyCtor::FundamentalTypeCopyCtor() : FunctionSymbol(SymbolKind::fundamentalTypeCopyCtor, U"@constructor"), type(nullptr)
{
}

FundamentalTypeCopyCtor::FundamentalTypeCopyCtor(TypeSymbol* type_, Context* context) :
    FunctionSymbol(SymbolKind::fundamentalTypeCopyCtor, U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer());
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    AddParameter(thatParam, soul::ast::SourcePos(), context);
}

void FundamentalTypeCopyCtor::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(type->Id());
}

void FundamentalTypeCopyCtor::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(typeId);
}

void FundamentalTypeCopyCtor::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    type = symbolTable.GetType(typeId);
}

void FundamentalTypeCopyCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
}

FundamentalTypeMoveCtor::FundamentalTypeMoveCtor() : FunctionSymbol(SymbolKind::fundamentalTypeMoveCtor, U"@constructor"), type(nullptr)
{
}

FundamentalTypeMoveCtor::FundamentalTypeMoveCtor(TypeSymbol* type_, Context* context) : 
    FunctionSymbol(SymbolKind::fundamentalTypeMoveCtor, U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer());
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type->AddRValueRef());
    AddParameter(thatParam, soul::ast::SourcePos(), context);
}

void FundamentalTypeMoveCtor::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(type->Id());
}

void FundamentalTypeMoveCtor::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(typeId);
}

void FundamentalTypeMoveCtor::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    type = symbolTable.GetType(typeId);
}

void FundamentalTypeMoveCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* rvalueRefValue = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLoad(rvalueRefValue));
    args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
}

FundamentalTypeCopyAssignment::FundamentalTypeCopyAssignment() : FunctionSymbol(SymbolKind::fundamentalTypeCopyAssignment, U"operator="), type(nullptr)
{
}

FundamentalTypeCopyAssignment::FundamentalTypeCopyAssignment(TypeSymbol* type_, Context* context) 
    : FunctionSymbol(SymbolKind::fundamentalTypeCopyAssignment, U"operator="), type(type_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer());
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    AddParameter(thatParam, soul::ast::SourcePos(), context);
    SetReturnType(type->AddLValueRef(), context);
}

void FundamentalTypeCopyAssignment::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(type->Id());
}

void FundamentalTypeCopyAssignment::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(typeId);
}

void FundamentalTypeCopyAssignment::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    type = symbolTable.GetType(typeId);
}

void FundamentalTypeCopyAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
    args[0]->Load(emitter, OperationFlags::addr, sourcePos, context);
}

FundamentalTypeMoveAssignment::FundamentalTypeMoveAssignment() : FunctionSymbol(SymbolKind::fundamentalTypeMoveAssignment, U"operator="), type(nullptr)
{
}

FundamentalTypeMoveAssignment::FundamentalTypeMoveAssignment(TypeSymbol* type_, Context* context) :
    FunctionSymbol(SymbolKind::fundamentalTypeMoveAssignment, U"operator="), type(type_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", type->AddPointer());
    AddParameter(thisParam, soul::ast::SourcePos(), context);
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type->AddRValueRef());
    AddParameter(thatParam, soul::ast::SourcePos(), context);
    SetReturnType(type->AddLValueRef(), context);
}

void FundamentalTypeMoveAssignment::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(type->Id());
}

void FundamentalTypeMoveAssignment::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(typeId);
}

void FundamentalTypeMoveAssignment::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
    type = symbolTable.GetType(typeId);
}

void FundamentalTypeMoveAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* refValue = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitLoad(refValue));
    args[0]->Store(emitter, OperationFlags::none, sourcePos, context);
    args[0]->Load(emitter, OperationFlags::addr, sourcePos, context);
}

void AddFundamentalIntegerOperationsToSymbolTable(TypeSymbol* type, Context* context)
{
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeUnaryPlusOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeUnaryMinusOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeComplementOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeAddOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSubOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMulOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDivOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeModOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeAndOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeOrOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeXorOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeShlOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeShrOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeEqualOperation(type, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeLessOperation(type, boolType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDefaultCtor(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyCtor(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveCtor(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyAssignment(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveAssignment(type, context), context);
}

void AddFundamentalFloatingPointOperationsToSymbolTable(TypeSymbol* type, Context* context)
{
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeAddOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSubOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMulOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDivOperation(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeEqualOperation(type, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeLessOperation(type, boolType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDefaultCtor(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyCtor(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveCtor(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyAssignment(type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveAssignment(type, context), context);
}

void AddFundamentalTypeOperationsToSymbolTable(Context* context)
{
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDefaultCtor(boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyCtor(boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveCtor(boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyAssignment(boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveAssignment(boolType, context), context);
    TypeSymbol* charType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::charType);
    TypeSymbol* signedCharType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::signedCharType);
    TypeSymbol* unsignedCharType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedCharType);
    TypeSymbol* char8Type = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char8Type);
    TypeSymbol* char16Type = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char16Type);
    TypeSymbol* char32Type = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char32Type);
    TypeSymbol* wcharType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::wcharType);
    TypeSymbol* shortIntType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::shortIntType);
    TypeSymbol* unsignedShortIntType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedShortIntType);
    TypeSymbol* intType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::intType);
    TypeSymbol* unsignedIntType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedIntType);
    TypeSymbol* longIntType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longIntType);
    TypeSymbol* unsignedLongIntType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedLongIntType);
    TypeSymbol* longLongIntType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType);
    TypeSymbol* unsignedLongLongIntType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedLongLongIntType);
    TypeSymbol* floatType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::floatType);
    TypeSymbol* doubleType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::doubleType);
    TypeSymbol* longDoubleType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longDoubleType);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeNotOperation(boolType, context), context);
    AddFundamentalIntegerOperationsToSymbolTable(charType, context);
    AddFundamentalIntegerOperationsToSymbolTable(signedCharType, context);
    AddFundamentalIntegerOperationsToSymbolTable(unsignedCharType, context);
    AddFundamentalIntegerOperationsToSymbolTable(char8Type, context);
    AddFundamentalIntegerOperationsToSymbolTable(char16Type, context);
    AddFundamentalIntegerOperationsToSymbolTable(char32Type, context);
    AddFundamentalIntegerOperationsToSymbolTable(wcharType, context);
    AddFundamentalIntegerOperationsToSymbolTable(shortIntType, context);
    AddFundamentalIntegerOperationsToSymbolTable(unsignedShortIntType, context);
    AddFundamentalIntegerOperationsToSymbolTable(intType, context);
    AddFundamentalIntegerOperationsToSymbolTable(unsignedIntType, context);
    AddFundamentalIntegerOperationsToSymbolTable(longIntType, context);
    AddFundamentalIntegerOperationsToSymbolTable(unsignedLongIntType, context);
    AddFundamentalIntegerOperationsToSymbolTable(longLongIntType, context);
    AddFundamentalIntegerOperationsToSymbolTable(unsignedLongLongIntType, context);
    AddFundamentalFloatingPointOperationsToSymbolTable(floatType, context);
    AddFundamentalFloatingPointOperationsToSymbolTable(doubleType, context);
    AddFundamentalTypeConversionsToSymboTable(charType, signedCharType, unsignedCharType, char8Type, char16Type, char32Type, wcharType,
        shortIntType, unsignedShortIntType, intType, unsignedIntType, longIntType, unsignedLongIntType, longLongIntType, unsignedLongLongIntType,
        floatType, doubleType, context);
}

} // namespace otava::symbols