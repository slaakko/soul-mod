// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.fundamental.type.conversion;

import otava.symbols.bound.tree.util;

namespace otava::symbols {

FundamentalTypeSignExtendConversion::FundamentalTypeSignExtendConversion() : FundamentalTypeConversion<FundamentalTypeSignExtension>(SymbolKind::fundamentalTypeSignExtension)
{
}

FundamentalTypeSignExtendConversion::FundamentalTypeSignExtendConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_) :
    FundamentalTypeConversion<FundamentalTypeSignExtension>(SymbolKind::fundamentalTypeSignExtension, distance_, conversionKind_, paramType_, argType_)
{
}

FundamentalTypeZeroExtendConversion::FundamentalTypeZeroExtendConversion() : FundamentalTypeConversion<FundamentalTypeZeroExtension>(SymbolKind::fundamentalTypeZeroExtension)
{
}

FundamentalTypeZeroExtendConversion::FundamentalTypeZeroExtendConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_) :
    FundamentalTypeConversion<FundamentalTypeZeroExtension>(SymbolKind::fundamentalTypeZeroExtension, distance_, conversionKind_, paramType_, argType_)
{
}

FundamentalTypeTruncateConversion::FundamentalTypeTruncateConversion() : FundamentalTypeConversion<FundamentalTypeTruncate>(SymbolKind::fundamentalTypeTruncate)
{
}

FundamentalTypeTruncateConversion::FundamentalTypeTruncateConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_) : 
    FundamentalTypeConversion<FundamentalTypeTruncate>(SymbolKind::fundamentalTypeTruncate, distance_, conversionKind_, paramType_, argType_)
{
}

FundamentalTypeBitcastConversion::FundamentalTypeBitcastConversion() : FundamentalTypeConversion<FundamentalTypeBitcast>(SymbolKind::fundamentalTypeBitcast)
{
}
    
FundamentalTypeBitcastConversion::FundamentalTypeBitcastConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_) : 
    FundamentalTypeConversion<FundamentalTypeBitcast>(SymbolKind::fundamentalTypeBitcast, distance_, conversionKind_, paramType_, argType_)
{
}

FundamentalTypeIntToFloatConversion::FundamentalTypeIntToFloatConversion() : FundamentalTypeConversion<FundamentalTypeIntToFloat>(SymbolKind::fundamentalTypeIntToFloat)
{
}

FundamentalTypeIntToFloatConversion::FundamentalTypeIntToFloatConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_) :
    FundamentalTypeConversion<FundamentalTypeIntToFloat>(SymbolKind::fundamentalTypeIntToFloat, distance_, conversionKind_, paramType_, argType_)
{
}

FundamentalTypeFloatToIntConversion::FundamentalTypeFloatToIntConversion() : FundamentalTypeConversion<FundamentalTypeFloatToInt>(SymbolKind::fundamentalTypeFloatToInt)
{
}

FundamentalTypeFloatToIntConversion::FundamentalTypeFloatToIntConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_) : 
    FundamentalTypeConversion<FundamentalTypeFloatToInt>(SymbolKind::fundamentalTypeFloatToInt, distance_, conversionKind_, paramType_, argType_)
{
}

FundamentalTypeBooleanConversion::FundamentalTypeBooleanConversion() : FunctionSymbol(SymbolKind::fundamentalTypeBoolean, U"@conversion")
{
}

FundamentalTypeBooleanConversion::FundamentalTypeBooleanConversion(TypeSymbol* type_, TypeSymbol* boolType) : 
    FunctionSymbol(SymbolKind::fundamentalTypeBoolean, U"@conversion"), paramType(boolType), argType(type_)
{
    SetFunctionKind(FunctionKind::conversion);
    SetAccess(Access::public_);
    ParameterSymbol* param = new ParameterSymbol(U"param", argType);
    AddParameter(param, soul::ast::SourcePos(), nullptr);
    SetReturnType(boolType);
}

TypeSymbol* FundamentalTypeBooleanConversion::ConversionParamType() const 
{
    return paramType;
}

TypeSymbol* FundamentalTypeBooleanConversion::ConversionArgType() const 
{
    return argType;
}

ConversionKind FundamentalTypeBooleanConversion::GetConversionKind() const 
{
    return ConversionKind::implicitConversion;
}

int32_t FundamentalTypeBooleanConversion::ConversionDistance() const 
{
    return 1;
}

void FundamentalTypeBooleanConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    otava::intermediate::Type* irType = argType->IrType(emitter, sourcePos, context);
    otava::intermediate::ConstantValue* defaultValue = irType->DefaultValue();
    otava::intermediate::Value* equal = emitter.EmitEqual(value, defaultValue);
    otava::intermediate::Value* notEqual = emitter.EmitNot(equal);
    emitter.Stack().Push(notEqual);
}

} // namespace otava::symbols
