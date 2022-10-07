// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.fundamental.type.operation;

import otava.symbols.fundamental.type.conversion.init;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.symbol.table;
import otava.symbols.context;
import otava.symbols.namespaces;

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

FundamentalTypeNotOperation::FundamentalTypeNotOperation(TypeSymbol* type_) : FundamentalTypeUnaryOperation<FundamentalTypeNot>(SymbolKind::fundamentalTypeNot, type_)
{
}

FundamentalTypeUnaryPlusOperation::FundamentalTypeUnaryPlusOperation() : 
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryPlus>(SymbolKind::fundamentalTypeUnaryPlus)
{
}

FundamentalTypeUnaryPlusOperation::FundamentalTypeUnaryPlusOperation(TypeSymbol* type_) : 
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryPlus>(SymbolKind::fundamentalTypeUnaryPlus, type_)
{
}

FundamentalTypeUnaryMinusOperation::FundamentalTypeUnaryMinusOperation() :
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryMinus>(SymbolKind::fundamentalTypeUnaryMinus)
{
}

FundamentalTypeUnaryMinusOperation::FundamentalTypeUnaryMinusOperation(TypeSymbol* type_) :
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryMinus>(SymbolKind::fundamentalTypeUnaryMinus, type_)
{
}

FundamentalTypeComplementOperation::FundamentalTypeComplementOperation() : 
    FundamentalTypeUnaryOperation<FundamentalTypeComplement>(SymbolKind::fundamentalTypeComplement)
{
}

FundamentalTypeComplementOperation::FundamentalTypeComplementOperation(TypeSymbol* type_) : 
    FundamentalTypeUnaryOperation<FundamentalTypeComplement>(SymbolKind::fundamentalTypeComplement, type_)
{
}

FundamentalTypeAddOperation::FundamentalTypeAddOperation() : FundamentalTypeBinaryOperation<FundamentalTypeAdd>(SymbolKind::fundamentalTypeAdd)
{
}

FundamentalTypeAddOperation::FundamentalTypeAddOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeAdd>(SymbolKind::fundamentalTypeAdd, type_)
{
}

FundamentalTypeSubOperation::FundamentalTypeSubOperation() : FundamentalTypeBinaryOperation<FundamentalTypeSub>(SymbolKind::fundamentalTypeSub)
{
}

FundamentalTypeSubOperation::FundamentalTypeSubOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeSub>(SymbolKind::fundamentalTypeSub, type_)
{
}

FundamentalTypeMulOperation::FundamentalTypeMulOperation() : FundamentalTypeBinaryOperation<FundamentalTypeMul>(SymbolKind::fundamentalTypeMul)
{
}

FundamentalTypeMulOperation::FundamentalTypeMulOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeMul>(SymbolKind::fundamentalTypeMul, type_)
{
}

FundamentalTypeDivOperation::FundamentalTypeDivOperation() : FundamentalTypeBinaryOperation<FundamentalTypeDiv>(SymbolKind::fundamentalTypeDiv)
{
}

FundamentalTypeDivOperation::FundamentalTypeDivOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeDiv>(SymbolKind::fundamentalTypeDiv, type_)
{
}

FundamentalTypeModOperation::FundamentalTypeModOperation() : FundamentalTypeBinaryOperation<FundamentalTypeMod>(SymbolKind::fundamentalTypeMod)
{
}

FundamentalTypeModOperation::FundamentalTypeModOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeMod>(SymbolKind::fundamentalTypeMod, type_)
{
}

FundamentalTypeAndOperation::FundamentalTypeAndOperation() : FundamentalTypeBinaryOperation<FundamentalTypeAnd>(SymbolKind::fundamentalTypeAnd)
{
}

FundamentalTypeAndOperation::FundamentalTypeAndOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeAnd>(SymbolKind::fundamentalTypeAnd, type_)
{
}

FundamentalTypeOrOperation::FundamentalTypeOrOperation() : FundamentalTypeBinaryOperation<FundamentalTypeOr>(SymbolKind::fundamentalTypeOr)
{
}

FundamentalTypeOrOperation::FundamentalTypeOrOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeOr>(SymbolKind::fundamentalTypeOr, type_)
{
}

FundamentalTypeXorOperation::FundamentalTypeXorOperation() : FundamentalTypeBinaryOperation<FundamentalTypeXor>(SymbolKind::fundamentalTypeXor)
{
}

FundamentalTypeXorOperation::FundamentalTypeXorOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeXor>(SymbolKind::fundamentalTypeXor, type_)
{
}

FundamentalTypeShlOperation::FundamentalTypeShlOperation() : FundamentalTypeBinaryOperation<FundamentalTypeShl>(SymbolKind::fundamentalTypeShl)
{
}

FundamentalTypeShlOperation::FundamentalTypeShlOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeShl>(SymbolKind::fundamentalTypeShl, type_)
{
}

FundamentalTypeShrOperation::FundamentalTypeShrOperation() : FundamentalTypeBinaryOperation<FundamentalTypeShr>(SymbolKind::fundamentalTypeShr)
{
}

FundamentalTypeShrOperation::FundamentalTypeShrOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeShr>(SymbolKind::fundamentalTypeShr, type_)
{
}

FundamentalTypeEqualOperation::FundamentalTypeEqualOperation() : FundamentalTypeComparisonOperation<FundamentalTypeEqual>(SymbolKind::fundamentalTypeEqual)
{
}

FundamentalTypeEqualOperation::FundamentalTypeEqualOperation(TypeSymbol* type_, TypeSymbol* boolType_) : 
    FundamentalTypeComparisonOperation<FundamentalTypeEqual>(SymbolKind::fundamentalTypeEqual, type_, boolType_)
{
}

FundamentalTypeLessOperation::FundamentalTypeLessOperation() : FundamentalTypeComparisonOperation<FundamentalTypeLess>(SymbolKind::fundamentalTypeLess)
{
}

FundamentalTypeLessOperation::FundamentalTypeLessOperation(TypeSymbol* type_, TypeSymbol* boolType_) :
    FundamentalTypeComparisonOperation<FundamentalTypeLess>(SymbolKind::fundamentalTypeLess, type_, boolType_)
{
}

void AddFundamentalIntegerOperationsToSymbolTable(TypeSymbol* type, Context* context)
{
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeUnaryPlusOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeUnaryMinusOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeComplementOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeAddOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSubOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMulOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDivOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeModOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeAndOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeOrOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeXorOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeShlOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeShrOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeEqualOperation(type, boolType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeLessOperation(type, boolType), context);
}

void AddFundamentalFloatingPointOperationsToSymbolTable(TypeSymbol* type, Context* context)
{
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeAddOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSubOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMulOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDivOperation(type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeEqualOperation(type, boolType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeLessOperation(type, boolType), context);
}

void AddFundamentalTypeOperationsToSymbolTable(Context* context)
{
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
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
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeNotOperation(boolType), context);
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