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

std::expected<otava::intermediate::Value*, int> FundamentalTypeSignExtension::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
{
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitSignExtend(value, destType));
}

std::expected<otava::intermediate::Value*, int> FundamentalTypeZeroExtension::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
{
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitZeroExtend(value, destType));
}

std::expected<otava::intermediate::Value*, int> FundamentalTypeFloatingPointExtension::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
{
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitFPExtend(value, destType));
}

std::expected<otava::intermediate::Value*, int> FundamentalTypeTruncate::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
{
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitTruncate(value, destType));
}

std::expected<otava::intermediate::Value*, int> FundamentalTypeBitcast::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
{
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitBitcast(value, destType));
}

std::expected<otava::intermediate::Value*, int> FundamentalTypeIntToFloat::Generate(Emitter& emitter, otava::intermediate::Value* value, 
    otava::intermediate::Type* destType, Context* context)
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
            std::expected<FunctionSymbol*, int> rv = conversionTable.GetConversion(paramType, argType, context);
            if (!rv) return std::unexpected<int>(rv.error());
            FunctionSymbol * conversion = *rv;
            BoundValueExpressionNode* arg = new BoundValueExpressionNode(value, argType);
            BoundConversionNode boundConversionNode(arg, conversion, soul::ast::SourcePos());
            std::expected<bool, int> lrv = boundConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
            if (!lrv) return std::unexpected<int>(lrv.error());
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
            std::expected<FunctionSymbol*, int> rv = conversionTable.GetConversion(paramType, argType, context);
            if (!rv) return std::unexpected<int>(rv.error());
            FunctionSymbol* conversion = *rv;
            BoundValueExpressionNode* arg = new BoundValueExpressionNode(value, argType);
            BoundConversionNode boundConversionNode(arg, conversion, soul::ast::SourcePos());
            std::expected<bool, int> lrv = boundConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
            if (!lrv) return std::unexpected<int>(lrv.error());
            value = emitter.Stack().Pop();
        }
    }
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitIntToFloat(value, destType));
}

std::expected<otava::intermediate::Value*, int> FundamentalTypeFloatToInt::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
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
            std::expected<FunctionSymbol*, int> rv = conversionTable.GetConversion(paramType, argType, context);
            if (!rv) return std::unexpected<int>(rv.error());
            FunctionSymbol* firstConversion = *rv;
            BoundValueExpressionNode* firstArg = new BoundValueExpressionNode(value, argType);
            BoundConversionNode firstConversionNode(firstArg, firstConversion, soul::ast::SourcePos());
            std::expected<bool, int> lrv = firstConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
            if (!lrv) return std::unexpected<int>(lrv.error());
            value = emitter.Stack().Pop();
            BoundValueExpressionNode* arg = new BoundValueExpressionNode(value, paramType);
            rv = conversionTable.GetConversion(finalParamType, paramType, context);
            if (!rv) return std::unexpected<int>(rv.error());
            FunctionSymbol* conversion = *rv;
            BoundConversionNode boundConversionNode(arg, conversion, soul::ast::SourcePos());
            lrv = boundConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
            if (!lrv) return std::unexpected<int>(lrv.error());
            value = emitter.Stack().Pop();
            return std::expected<otava::intermediate::Value*, int>(value);
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
            std::expected<FunctionSymbol*, int> rv = conversionTable.GetConversion(paramType, argType, context);
            if (!rv) return std::unexpected<int>(rv.error());
            FunctionSymbol* firstConversion = *rv;
            BoundValueExpressionNode* firstArg = new BoundValueExpressionNode(value, argType);
            BoundConversionNode firstConversionNode(firstArg, firstConversion, soul::ast::SourcePos());
            std::expected<bool, int> lrv = firstConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
            if (!lrv) return std::unexpected<int>(lrv.error());
            value = emitter.Stack().Pop();
            BoundValueExpressionNode* arg = new BoundValueExpressionNode(value, paramType);
            rv = conversionTable.GetConversion(finalParamType, paramType, context);
            if (!rv) return std::unexpected<int>(rv.error());
            FunctionSymbol* conversion = *rv;
            BoundConversionNode boundConversionNode(arg, conversion, soul::ast::SourcePos());
            lrv = boundConversionNode.Load(emitter, OperationFlags::none, soul::ast::SourcePos(), context);
            if (!lrv) return std::unexpected<int>(lrv.error());
            value = emitter.Stack().Pop();
            return std::expected<otava::intermediate::Value*, int>(value);
        }
    }
    return std::expected<otava::intermediate::Value*, int>(emitter.EmitFloatToInt(value, destType));
}

std::expected<otava::intermediate::Value*, int> FundamentalTypeBoolToInt::Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
{
    std::expected<otava::intermediate::Instruction*, int> rv = emitter.EmitLocal(destType);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value * resultVar = *rv;
    otava::intermediate::BasicBlock* trueDest = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* falseDest = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* next = emitter.CreateBasicBlock();
    emitter.EmitBranch(value, trueDest, falseDest);
    emitter.SetCurrentBasicBlock(falseDest);
    otava::intermediate::Value* zero = emitter.EmitIntegerValue(destType, 0);
    emitter.EmitStore(zero, resultVar);
    emitter.EmitJump(next);
    emitter.SetCurrentBasicBlock(trueDest);
    otava::intermediate::Value* one = emitter.EmitIntegerValue(destType, 1);
    emitter.EmitStore(one, resultVar);
    emitter.EmitJump(next);
    emitter.SetCurrentBasicBlock(next);
    rv = emitter.EmitLoad(resultVar);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Value* result = *rv;
    return std::expected<otava::intermediate::Value*, int>(result);
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

FundamentalTypeBoolToIntConversion::FundamentalTypeBoolToIntConversion() : FundamentalTypeConversion<FundamentalTypeBoolToInt>(SymbolKind::fundamentalTypeBoolToInt)
{
}

FundamentalTypeBoolToIntConversion::FundamentalTypeBoolToIntConversion(TypeSymbol* boolType, TypeSymbol* destType, Context* context) :
    FundamentalTypeConversion<FundamentalTypeBoolToInt>(SymbolKind::fundamentalTypeBoolToInt, 255, ConversionKind::explicitConversion, destType, boolType, context)
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
    std::expected<bool, int> rv = AddParameter(param, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
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

std::expected<bool, int> FundamentalTypeBooleanConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    std::expected<otava::intermediate::Type*, int> rv = argType->IrType(emitter, sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::intermediate::Type* irType = *rv;
    otava::intermediate::Value* defaultValue = irType->DefaultValue();
    otava::intermediate::Value* equal = emitter.EmitEqual(value, defaultValue);
    otava::intermediate::Value* notEqual = emitter.EmitNot(equal);
    emitter.Stack().Push(notEqual);
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
