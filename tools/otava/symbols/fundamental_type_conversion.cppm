// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.fundamental.type.conversion;

import std;
import otava.symbols.context;
import otava.symbols.emitter;
import otava.symbols.function.symbol;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.symbol.table;
import otava.symbols.type.symbol;
import otava.intermediate.data;
import otava.intermediate.types;

export namespace otava::symbols {

enum class ConversionKind : std::int32_t
{
    implicitConversion, explicitConversion
};

struct FundamentalTypeIdentity
{
    inline static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context) 
    { 
        return value; 
    }
};

struct FundamentalTypeSignExtension
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeZeroExtension
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeFloatingPointExtension
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeTruncate
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeFloatingPointTruncate
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeBitcast
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeIntToFloat
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeFloatToInt
{
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

template<class Op>
struct FundamentalTypeConversion : public FunctionSymbol
{
    FundamentalTypeConversion(SymbolKind kind_) : 
        FunctionSymbol(kind_, U"@conversion"), distance(0), conversionKind(ConversionKind::implicitConversion), paramType(nullptr), argType(nullptr), 
        paramTypeId(util::nil_uuid()), argTypeId(util::nil_uuid())
    {
    }
    FundamentalTypeConversion(SymbolKind kind_, std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context) :
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
    std::int32_t ConversionDistance() const override
    { 
        return distance;
    }
    void Write(Writer& writer) override
    {
        FunctionSymbol::Write(writer);
        writer.GetBinaryStreamWriter().Write(distance);
        writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(conversionKind));
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
        context->SetArgType(argType);
        context->SetParamType(paramType);
        otava::intermediate::Value* value = emitter.Stack().Pop();
        emitter.Stack().Push(Op::Generate(emitter, value, static_cast<otava::intermediate::Type*>(paramType->IrType(emitter, sourcePos, context)), context));
    }
    std::int32_t distance;
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
    FundamentalTypeSignExtendConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeZeroExtendConversion : public FundamentalTypeConversion<FundamentalTypeZeroExtension>
{
public:
    FundamentalTypeZeroExtendConversion();
    FundamentalTypeZeroExtendConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeFloatingPointExtendConversion : public FundamentalTypeConversion<FundamentalTypeFloatingPointExtension>
{
public:
    FundamentalTypeFloatingPointExtendConversion();
    FundamentalTypeFloatingPointExtendConversion(::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeTruncateConversion : public FundamentalTypeConversion<FundamentalTypeTruncate>
{
public:
    FundamentalTypeTruncateConversion();
    FundamentalTypeTruncateConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeBitcastConversion : public FundamentalTypeConversion<FundamentalTypeBitcast>
{
public:
    FundamentalTypeBitcastConversion();
    FundamentalTypeBitcastConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeIntToFloatConversion : public FundamentalTypeConversion<FundamentalTypeIntToFloat>
{
public:
    FundamentalTypeIntToFloatConversion();
    FundamentalTypeIntToFloatConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeFloatToIntConversion : public FundamentalTypeConversion<FundamentalTypeFloatToInt>
{
public:
    FundamentalTypeFloatToIntConversion();
    FundamentalTypeFloatToIntConversion(std::int32_t distance_, ConversionKind conversionKind_, TypeSymbol* paramType_, TypeSymbol* argType_, Context* context);
};

class FundamentalTypeBooleanConversion : public FunctionSymbol
{
public:    
    FundamentalTypeBooleanConversion();
    FundamentalTypeBooleanConversion(TypeSymbol* type_, TypeSymbol* boolType, Context* context);
    TypeSymbol* ConversionParamType() const override;
    TypeSymbol* ConversionArgType() const override;
    ConversionKind GetConversionKind() const override;
    std::int32_t ConversionDistance() const override;
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

