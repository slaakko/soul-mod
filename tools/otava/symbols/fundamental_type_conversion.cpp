// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.fundamental.type.conversion;

import otava.symbols.fundamental.type.symbol;
import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.conversion.table;

namespace otava::symbols {

    otava::intermediate::Value* FundamentalTypeSignExtension::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
    {
        return emitter.EmitSignExtend(value, destType);
    }

    otava::intermediate::Value* FundamentalTypeZeroExtension::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
    {
        return emitter.EmitZeroExtend(value, destType);
    }

    otava::intermediate::Value* FundamentalTypeFloatingPointExtension::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
    {
        return emitter.EmitFPExtend(value, destType);
    }

    otava::intermediate::Value* FundamentalTypeTruncate::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
    {
        return emitter.EmitTruncate(value, destType);
    }

    otava::intermediate::Value* FundamentalTypeBitcast::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
    {
        return emitter.EmitBitcast(value, destType);
    }

    otava::intermediate::Value* FundamentalTypeIntToFloat::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
    {
        if (destType->Size() == 4)
        {
            if (value->GetType()->Size() < 4)
            {
                ConversionTable& conversionTable = context->GetSymbolTable()->GetConversionTable();
                TypeSymbol* argType = context->ArgType();
                TypeSymbol* paramType = nullptr;
                if (value->GetType()->IsSignedType())
                {
                    paramType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::intType);
                }
                else if (value->GetType()->IsUnsignedType())
                {
                    paramType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedIntType);
                }
                FunctionSymbol* conversion = conversionTable.GetConversion(paramType, argType, context);
                BoundValueExpressionNode* arg(new BoundValueExpressionNode(value, argType));
                BoundConversionNode boundConversionNode(arg, conversion, soul::ast::SourcePos());
                boundConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
                value = emitter.Stack().Pop();
            }
        }
        else if (destType->Size() == 8)
        {
            if (value->GetType()->Size() < 8)
            {
                ConversionTable& conversionTable = context->GetSymbolTable()->GetConversionTable();
                TypeSymbol* argType = context->ArgType();
                TypeSymbol* paramType = nullptr;
                if (value->GetType()->IsSignedType())
                {
                    paramType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType);
                }
                else if (value->GetType()->IsUnsignedType())
                {
                    paramType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedLongLongIntType);
                }
                FunctionSymbol* conversion = conversionTable.GetConversion(paramType, argType, context);
                BoundValueExpressionNode* arg(new BoundValueExpressionNode(value, argType));
                BoundConversionNode boundConversionNode(arg, conversion, soul::ast::SourcePos());
                boundConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
                value = emitter.Stack().Pop();
            }
        }
        return emitter.EmitIntToFloat(value, destType);
    }

otava::intermediate::Value* FundamentalTypeFloatToInt::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
{
    if (value->GetType()->Size() == 4)
    {
        if (destType->Size() < 4)
        {
            ConversionTable& conversionTable = context->GetSymbolTable()->GetConversionTable();
            TypeSymbol* argType = context->ArgType();
            TypeSymbol* finalParamType = context->ParamType();
            TypeSymbol* paramType = nullptr;
            if (destType->IsSignedType())
            {
                paramType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::intType);
            }
            else if (destType->IsUnsignedType())
            {
                paramType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedIntType);
            }
            FunctionSymbol* firstConversion = conversionTable.GetConversion(paramType, argType, context);
            BoundValueExpressionNode* firstArg(new BoundValueExpressionNode(value, argType));
            BoundConversionNode firstConversionNode(firstArg, firstConversion, soul::ast::SourcePos());
            firstConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
            value = emitter.Stack().Pop();
            BoundValueExpressionNode* arg(new BoundValueExpressionNode(value, paramType));
            FunctionSymbol* conversion = conversionTable.GetConversion(finalParamType, paramType, context);
            BoundConversionNode boundConversionNode(arg, conversion, soul::ast::SourcePos());
            boundConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
            value = emitter.Stack().Pop();
            return value;
        }
    }
    else if (value->GetType()->Size() == 8)
    {
        if (destType->Size() < 8)
        {
            ConversionTable& conversionTable = context->GetSymbolTable()->GetConversionTable();
            TypeSymbol* argType = context->ArgType();
            TypeSymbol* finalParamType = context->ParamType();
            TypeSymbol* paramType = nullptr;
            if (destType->IsSignedType())
            {
                paramType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType);
            }
            else if (destType->IsUnsignedType())
            {
                paramType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedLongLongIntType);
            }
            FunctionSymbol* firstConversion = conversionTable.GetConversion(paramType, argType, context);
            BoundValueExpressionNode* firstArg(new BoundValueExpressionNode(value, argType));
            BoundConversionNode firstConversionNode(firstArg, firstConversion, soul::ast::SourcePos());
            firstConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
            value = emitter.Stack().Pop();
            BoundValueExpressionNode* arg(new BoundValueExpressionNode(value, paramType));
            FunctionSymbol* conversion = conversionTable.GetConversion(finalParamType, paramType, context);
            BoundConversionNode boundConversionNode(arg, conversion, soul::ast::SourcePos());
            boundConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
            value = emitter.Stack().Pop();
            return value;
        }
    }
    return emitter.EmitFloatToInt(value, destType);
}

FundamentalTypeSignExtendConversion::FundamentalTypeSignExtendConversion() : FundamentalTypeConversion<FundamentalTypeSignExtension>(SymbolKind::fundamentalTypeSignExtension)
{
}

FundamentalTypeSignExtendConversion::FundamentalTypeSignExtendConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, 
    Context* context) :
    FundamentalTypeConversion<FundamentalTypeSignExtension>(SymbolKind::fundamentalTypeSignExtension, distance_, conversionKind_, paramType_, argType_, context)
{
}

FundamentalTypeZeroExtendConversion::FundamentalTypeZeroExtendConversion() : FundamentalTypeConversion<FundamentalTypeZeroExtension>(SymbolKind::fundamentalTypeZeroExtension)
{
}

FundamentalTypeZeroExtendConversion::FundamentalTypeZeroExtendConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, 
    Context* context) :
    FundamentalTypeConversion<FundamentalTypeZeroExtension>(SymbolKind::fundamentalTypeZeroExtension, distance_, conversionKind_, paramType_, argType_, context)
{
}

FundamentalTypeFloatingPointExtendConversion::FundamentalTypeFloatingPointExtendConversion() : 
    FundamentalTypeConversion<FundamentalTypeFloatingPointExtension>(SymbolKind::fundamentalTypeFloatingPointExtension) 
{
}

FundamentalTypeFloatingPointExtendConversion::FundamentalTypeFloatingPointExtendConversion(std::int32_t distance_, ConversionKind conversionKind_,
    TypeSymbol* paramType_, TypeSymbol* argType_, Context* context) : 
    FundamentalTypeConversion<FundamentalTypeFloatingPointExtension>(SymbolKind::fundamentalTypeFloatingPointExtension, distance_, conversionKind_, paramType_, argType_, 
        context)
{
}

FundamentalTypeTruncateConversion::FundamentalTypeTruncateConversion() : FundamentalTypeConversion<FundamentalTypeTruncate>(SymbolKind::fundamentalTypeTruncate)
{
}

FundamentalTypeTruncateConversion::FundamentalTypeTruncateConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context) :
    FundamentalTypeConversion<FundamentalTypeTruncate>(SymbolKind::fundamentalTypeTruncate, distance_, conversionKind_, paramType_, argType_, context)
{
}

FundamentalTypeBitcastConversion::FundamentalTypeBitcastConversion() : FundamentalTypeConversion<FundamentalTypeBitcast>(SymbolKind::fundamentalTypeBitcast)
{
}
    
FundamentalTypeBitcastConversion::FundamentalTypeBitcastConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context) :
    FundamentalTypeConversion<FundamentalTypeBitcast>(SymbolKind::fundamentalTypeBitcast, distance_, conversionKind_, paramType_, argType_, context)
{
}

FundamentalTypeIntToFloatConversion::FundamentalTypeIntToFloatConversion() : FundamentalTypeConversion<FundamentalTypeIntToFloat>(SymbolKind::fundamentalTypeIntToFloat)
{
}

FundamentalTypeIntToFloatConversion::FundamentalTypeIntToFloatConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, 
    Context* context) :
    FundamentalTypeConversion<FundamentalTypeIntToFloat>(SymbolKind::fundamentalTypeIntToFloat, distance_, conversionKind_, paramType_, argType_, context)
{
}

FundamentalTypeFloatToIntConversion::FundamentalTypeFloatToIntConversion() : FundamentalTypeConversion<FundamentalTypeFloatToInt>(SymbolKind::fundamentalTypeFloatToInt)
{
}

FundamentalTypeFloatToIntConversion::FundamentalTypeFloatToIntConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, 
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

std::int32_t FundamentalTypeBooleanConversion::ConversionDistance() const 
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
