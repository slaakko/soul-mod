// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.argument.conversion.table;

import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.conversion.table;
import otava.symbols.function.symbol;
import otava.symbols.type.symbol;
import otava.symbols.fundamental.type.conversion;
import otava.symbols.emitter;
import otava.intermediate.value;

namespace otava::symbols {

class NullPtrToPtrConversion : public FunctionSymbol
{
public:
    NullPtrToPtrConversion(TypeSymbol* argType_, TypeSymbol* pointerType_);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    TypeSymbol* ConversionParamType() const override { return pointerType; }
    TypeSymbol* ConversionArgType() const override { return argType; }
    ConversionKind GetConversionKind() const override { return ConversionKind::implicitConversion; }
    int32_t ConversionDistance() const override { return 1; }
private:
    TypeSymbol* argType;
    TypeSymbol* pointerType;
};

NullPtrToPtrConversion::NullPtrToPtrConversion(TypeSymbol* argType_, TypeSymbol* pointerType_) : 
    FunctionSymbol(U"@conversion"), argType(argType_), pointerType(pointerType_)
{
    SetConversion();
    SetAccess(Access::public_);
    ParameterSymbol* arg = new ParameterSymbol(U"arg", argType);
    AddParameter(arg, soul::ast::SourcePos(), nullptr);
    SetReturnType(pointerType);
}

void NullPtrToPtrConversion::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Value* value = emitter.Stack().Pop();
    emitter.Stack().Push(emitter.EmitBitcast(value, pointerType->IrType(emitter, sourcePos, context)));
}

class NullPtrToPtrArgumentConversion : public ArgumentConversion
{
public:
    FunctionSymbol* Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context) override;
};

FunctionSymbol* NullPtrToPtrArgumentConversion::Get(TypeSymbol* paramType, TypeSymbol* argType, Context* context)
{
    if (argType->IsNullPtrType() && paramType->IsPointerType())
    {
        return new NullPtrToPtrConversion(argType, paramType);
    }
    return nullptr;
}

ArgumentConversionTable::ArgumentConversionTable()
{
    AddArgumentConversion(new NullPtrToPtrArgumentConversion());
}

void ArgumentConversionTable::AddArgumentConversion(ArgumentConversion* argumentConversion)
{
    argumentConversions.push_back(std::unique_ptr<ArgumentConversion>(argumentConversion));
}

FunctionSymbol* ArgumentConversionTable::GetArgumentConversion(TypeSymbol* paramType, TypeSymbol* argType, Context* context)
{
    FunctionSymbol* conversion = context->GetSymbolTable()->GetConversionTable().GetConversion(paramType, argType);
    if (conversion)
    {
        return conversion;
    }
    for (const auto& argumentConversion : argumentConversions)
    {
        FunctionSymbol* conversionFunction = argumentConversion->Get(paramType, argType, context);
        if (conversionFunction)
        {
            conversionFunctions.push_back(std::unique_ptr<FunctionSymbol>(conversionFunction));
            return conversionFunction;
        }
    }
    return nullptr;
}

} // namespace otava::symbols

