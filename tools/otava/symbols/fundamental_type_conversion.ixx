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
import otava.symbols.type.symbol;
import otava.intermediate.value;

export namespace otava::symbols {

enum class ConversionKind : int32_t
{
    implicitConversion, explicitConversion
};

struct FundamentalTypeSignExtension
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType);
};

struct FundamentalTypeZeroExtension
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType);
};

struct FundamentalTypeTruncate
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType);
};

struct FundamentalTypeBitcast
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType);
};

struct FundamentalTypeIntToFloat
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType);
};

struct FundamentalTypeFloatToInt
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType);
};

template<class Op>
struct FundamentalTypeConversion : public FunctionSymbol
{
    FundamentalTypeConversion(SymbolKind kind_) : 
        FunctionSymbol(kind_, U"@conversion"), distance(0), conversionKind(ConversionKind::implicitConversion), paramType(nullptr), argType(nullptr), 
        paramTypeId(util::nil_uuid()), argTypeId(util::nil_uuid())
    {
    }
    FundamentalTypeConversion(SymbolKind kind_, int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context) :
        FunctionSymbol(kind_, U"@conversion"), distance(distance_), conversionKind(conversionKind_), paramType(paramType_), argType(argType_),
        paramTypeId(util::nil_uuid()), argTypeId(util::nil_uuid())
    {
        SetConversion();
        SetAccess(Access::public_);
        ParameterSymbol* arg = new ParameterSymbol(U"arg", argType);
        AddParameter(arg, soul::ast::SourcePos(), nullptr);
        SetReturnType(paramType_, context);
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
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        emitter.Stack().Push(Op::Generate(emitter, value, static_cast<otava::intermediate::Type*>(paramType->IrType(emitter, sourcePos, context))));
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
    FundamentalTypeSignExtendConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeZeroExtendConversion : public FundamentalTypeConversion<FundamentalTypeZeroExtension>
{
public:
    FundamentalTypeZeroExtendConversion();
    FundamentalTypeZeroExtendConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeTruncateConversion : public FundamentalTypeConversion<FundamentalTypeTruncate>
{
public:
    FundamentalTypeTruncateConversion();
    FundamentalTypeTruncateConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeBitcastConversion : public FundamentalTypeConversion<FundamentalTypeBitcast>
{
public:
    FundamentalTypeBitcastConversion();
    FundamentalTypeBitcastConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeIntToFloatConversion : public FundamentalTypeConversion<FundamentalTypeIntToFloat>
{
public:
    FundamentalTypeIntToFloatConversion();
    FundamentalTypeIntToFloatConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeFloatToIntConversion : public FundamentalTypeConversion<FundamentalTypeFloatToInt>
{
public:
    FundamentalTypeFloatToIntConversion();
    FundamentalTypeFloatToIntConversion(int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeBooleanConversion : public FunctionSymbol
{
public:    
    FundamentalTypeBooleanConversion();
    FundamentalTypeBooleanConversion(TypeSymbol* type_, TypeSymbol* boolType, Context* context);
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
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* paramType;
    TypeSymbol* argType;
    util::uuid paramTypeId;
    util::uuid argTypeId;
};

} // namespace otava::symbols

