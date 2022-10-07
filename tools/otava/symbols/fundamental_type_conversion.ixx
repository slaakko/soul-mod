// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.fundamental.type.conversion;

import std.core;
import otava.symbols.emitter;
import otava.symbols.function.symbol;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.symbol.table;
import otava.intermediate.value;

export namespace otava::symbols {

enum class ConversionKind : int32_t
{
    implicitConversion, narrowingConversion
};

struct FundamentalTypeSignExtension
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
    {
        return emitter.EmitSignExtend(value, destType);
    }
};

struct FundamentalTypeZeroExtension
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
    {
        return emitter.EmitZeroExtend(value, destType);
    }
};

struct FundamentalTypeTruncate
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
    {
        return emitter.EmitTruncate(value, destType);
    }
};

struct FundamentalTypeBitcast
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
    {
        return emitter.EmitBitcast(value, destType);
    }
};

struct FundamentalTypeIntToFloat
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
    {
        return emitter.EmitIntToFloat(value, destType);
    }
};

struct FundamentalTypeFloatToInt
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType)
    {
        return emitter.EmitFloatToInt(value, destType);
    }
};

template<class Op>
struct FundamentalTypeConversion : public FunctionSymbol
{
    FundamentalTypeConversion(SymbolKind kind_) : FunctionSymbol(kind_, U"@conversion")
    {
    }
    FundamentalTypeConversion(SymbolKind kind_, int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_) :
        FunctionSymbol(kind_, U"@conversion"), distance(distance_), conversionKind(conversionKind_), paramType(paramType_), argType(argType_)
    {
        SetConversion();
        SetAccess(Access::public_);
        ParameterSymbol* arg = new ParameterSymbol(U"arg", argType);
        AddParameter(arg, soul::ast::SourcePos(), nullptr);
        SetReturnType(paramType_);
    }
    TypeSymbol* ConversionParamType() const override
    {
        return paramType;
    }
    TypeSymbol* ConversionArgType() const override
    {
        return argType;
    }
    ConversionKind GetConversionKind() const override
    {
        return conversionKind;
    }
    int32_t ConversionDistance() const override
    { 
        return distance;
    }
    void Write(Writer& writer) override
    {
        FunctionSymbol::Write(writer);
        writer.GetBinaryStreamWriter().Write(distance);
        writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(conversionKind));
        writer.GetBinaryStreamWriter().Write(paramType->Id());
        writer.GetBinaryStreamWriter().Write(argType->Id());
    }
    void Read(Reader& reader) override
    {
        FunctionSymbol::Read(reader);
        distance = reader.GetBinaryStreamReader().ReadInt();
        conversionKind = static_cast<ConversionKind>(reader.GetBinaryStreamReader().ReadByte());
        reader.GetBinaryStreamReader().ReadUuid(paramTypeId);
        reader.GetBinaryStreamReader().ReadUuid(argTypeId);
    }
    void Resolve(SymbolTable& symbolTable) override
    {
        FunctionSymbol::Resolve(symbolTable);
        paramType = symbolTable.GetType(paramTypeId);
        argType = symbolTable.GetType(argTypeId);
    }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        emitter.Stack().Push(Op::Generate(emitter, value, paramType->IrType(emitter, sourcePos, context)));
    }
    int32_t distance;
    ConversionKind conversionKind;
    TypeSymbol* paramType;
    TypeSymbol* argType;
    util::uuid paramTypeId;
    util::uuid argTypeId;
};

class FundamentalTypeSignExtendConversion : public FundamentalTypeConversion<FundamentalTypeSignExtension>
{
public:
    FundamentalTypeSignExtendConversion();
    FundamentalTypeSignExtendConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_);
};

class FundamentalTypeZeroExtendConversion : public FundamentalTypeConversion<FundamentalTypeZeroExtension>
{
public:
    FundamentalTypeZeroExtendConversion();
    FundamentalTypeZeroExtendConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_);
};

class FundamentalTypeTruncateConversion : public FundamentalTypeConversion<FundamentalTypeTruncate>
{
public:
    FundamentalTypeTruncateConversion();
    FundamentalTypeTruncateConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_);
};

class FundamentalTypeBitcastConversion : public FundamentalTypeConversion<FundamentalTypeBitcast>
{
public:
    FundamentalTypeBitcastConversion();
    FundamentalTypeBitcastConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_);
};

class FundamentalTypeIntToFloatConversion : public FundamentalTypeConversion<FundamentalTypeIntToFloat>
{
public:
    FundamentalTypeIntToFloatConversion();
    FundamentalTypeIntToFloatConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_);
};

class FundamentalTypeFloatToIntConversion : public FundamentalTypeConversion<FundamentalTypeFloatToInt>
{
public:
    FundamentalTypeFloatToIntConversion();
    FundamentalTypeFloatToIntConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_);
};

class FundamentalTypeBooleanConversion : public FunctionSymbol
{
public:    
    FundamentalTypeBooleanConversion();
    FundamentalTypeBooleanConversion(TypeSymbol* type_, TypeSymbol* boolType);
    TypeSymbol* ConversionParamType() const override;
    TypeSymbol* ConversionArgType() const override;
    ConversionKind GetConversionKind() const override;
    int32_t ConversionDistance() const override;
    void Write(Writer& writer) override
    {
        FunctionSymbol::Write(writer);
        writer.GetBinaryStreamWriter().Write(paramType->Id());
        writer.GetBinaryStreamWriter().Write(argType->Id());
    }
    void Read(Reader& reader) override
    {
        FunctionSymbol::Read(reader);
        reader.GetBinaryStreamReader().ReadUuid(paramTypeId);
        reader.GetBinaryStreamReader().ReadUuid(argTypeId);
    }
    void Resolve(SymbolTable& symbolTable) override
    {
        FunctionSymbol::Resolve(symbolTable);
        paramType = symbolTable.GetType(paramTypeId);
        argType = symbolTable.GetType(argTypeId);
    }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* paramType;
    TypeSymbol* argType;
    util::uuid paramTypeId;
    util::uuid argTypeId;
};

} // namespace otava::symbols

