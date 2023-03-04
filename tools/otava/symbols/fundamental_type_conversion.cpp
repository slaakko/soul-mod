// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.fundamental.type.conversion;

namespace otava::symbols {

otava::intermediate::Value* FundamentalTypeSignExtension::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return emitter.EmitSignExtend(value, destType);
}

otava::intermediate::Value* FundamentalTypeZeroExtension::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return emitter.EmitZeroExtend(value, destType);
}

otava::intermediate::Value* FundamentalTypeTruncate::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return emitter.EmitTruncate(value, destType);
}

otava::intermediate::Value* FundamentalTypeBitcast::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return emitter.EmitBitcast(value, destType);
}

otava::intermediate::Value* FundamentalTypeIntToFloat::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return emitter.EmitIntToFloat(value, destType);
}

otava::intermediate::Value* FundamentalTypeFloatToInt::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
{
    return emitter.EmitFloatToInt(value, destType);
}

FundamentalTypeSignExtendConversion::FundamentalTypeSignExtendConversion() : FundamentalTypeConversion<FundamentalTypeSignExtension>(SymbolKind::fundamentalTypeSignExtension)
{
}

FundamentalTypeSignExtendConversion::FundamentalTypeSignExtendConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, 
    Context* context) :
    FundamentalTypeConversion<FundamentalTypeSignExtension>(SymbolKind::fundamentalTypeSignExtension, distance_, conversionKind_, paramType_, argType_, context)
{
}

FundamentalTypeZeroExtendConversion::FundamentalTypeZeroExtendConversion() : FundamentalTypeConversion<FundamentalTypeZeroExtension>(SymbolKind::fundamentalTypeZeroExtension)
{
}

FundamentalTypeZeroExtendConversion::FundamentalTypeZeroExtendConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, 
    Context* context) :
    FundamentalTypeConversion<FundamentalTypeZeroExtension>(SymbolKind::fundamentalTypeZeroExtension, distance_, conversionKind_, paramType_, argType_, context)
{
}

FundamentalTypeTruncateConversion::FundamentalTypeTruncateConversion() : FundamentalTypeConversion<FundamentalTypeTruncate>(SymbolKind::fundamentalTypeTruncate)
{
}

FundamentalTypeTruncateConversion::FundamentalTypeTruncateConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context) :
    FundamentalTypeConversion<FundamentalTypeTruncate>(SymbolKind::fundamentalTypeTruncate, distance_, conversionKind_, paramType_, argType_, context)
{
}

FundamentalTypeBitcastConversion::FundamentalTypeBitcastConversion() : FundamentalTypeConversion<FundamentalTypeBitcast>(SymbolKind::fundamentalTypeBitcast)
{
}
    
FundamentalTypeBitcastConversion::FundamentalTypeBitcastConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context) :
    FundamentalTypeConversion<FundamentalTypeBitcast>(SymbolKind::fundamentalTypeBitcast, distance_, conversionKind_, paramType_, argType_, context)
{
}

FundamentalTypeIntToFloatConversion::FundamentalTypeIntToFloatConversion() : FundamentalTypeConversion<FundamentalTypeIntToFloat>(SymbolKind::fundamentalTypeIntToFloat)
{
}

FundamentalTypeIntToFloatConversion::FundamentalTypeIntToFloatConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, 
    Context* context) :
    FundamentalTypeConversion<FundamentalTypeIntToFloat>(SymbolKind::fundamentalTypeIntToFloat, distance_, conversionKind_, paramType_, argType_, context)
{
}

FundamentalTypeFloatToIntConversion::FundamentalTypeFloatToIntConversion() : FundamentalTypeConversion<FundamentalTypeFloatToInt>(SymbolKind::fundamentalTypeFloatToInt)
{
}

FundamentalTypeFloatToIntConversion::FundamentalTypeFloatToIntConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, 
    Context* context) :
    FundamentalTypeConversion<FundamentalTypeFloatToInt>(SymbolKind::fundamentalTypeFloatToInt, distance_, conversionKind_, paramType_, argType_, context)
{
}

FundamentalTypeBooleanConversion::FundamentalTypeBooleanConversion() : FunctionSymbol(SymbolKind::fundamentalTypeBoolean, U"@conversion"), argType(), argTypeId(), paramType(),
    paramTypeId()
{
}

FundamentalTypeBooleanConversion::FundamentalTypeBooleanConversion(TypeSymbol* type_, TypeSymbol* boolType, Context* context) : 
    FunctionSymbol(SymbolKind::fundamentalTypeBoolean, U"@conversion"), paramType(boolType), argType(type_), argTypeId(), paramTypeId()
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* param = new ParameterSymbol(U"param", argType);
    AddParameter(param, soul::ast::SourcePos(), context);
    SetReturnType(boolType, context);
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

void FundamentalTypeBooleanConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    otava::intermediate::Type* irType = static_cast<otava::intermediate::Type*>(argType->IrType(emitter, sourcePos, context));
    otava::intermediate::Value* defaultValue = irType->DefaultValue();
    otava::intermediate::Value* equal = emitter.EmitEqual(value, defaultValue);
    otava::intermediate::Value* notEqual = emitter.EmitNot(equal);
    emitter.Stack().Push(notEqual);
}

} // namespace otava::symbols
