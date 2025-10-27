// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.fundamental.type.conversion;

import std;
import otava.symbols.context;
import otava.symbols.emitter;
import otava.symbols.symbol.table;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.type.symbol;
import otava.intermediate.data;
import otava.intermediate.types;

export namespace otava::symbols {

struct FundamentalTypeIdentity
{
    inline static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context)
    {
        return value;
    }
};

struct FundamentalTypeSignExtension
{
    static std::expected<otava::intermediate::Value*, int> Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeZeroExtension
{
    static std::expected<otava::intermediate::Value*, int> Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeFloatingPointExtension
{
    static std::expected<otava::intermediate::Value*, int> Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeTruncate
{
    static std::expected<otava::intermediate::Value*, int> Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeBitcast
{
    static std::expected<otava::intermediate::Value*, int> Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeIntToFloat
{
    static std::expected<otava::intermediate::Value*, int> Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeFloatToInt
{
    static std::expected<otava::intermediate::Value*, int> Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
};

struct FundamentalTypeBoolToInt
{
    static std::expected<otava::intermediate::Value*, int> Generate(Emitter& emitter, otava::intermediate::Value* value, otava::intermediate::Type* destType, Context* context);
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
        SetConversionParamType(paramType_);
        SetConversionArgType(argType_);
        ParameterSymbol* arg = new ParameterSymbol(U"arg", argType);
        std::expected<bool, int> rv = AddParameter(arg, soul::ast::SourcePos(), nullptr);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        rv = SetReturnType(paramType_, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
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
    std::expected<bool, int> Write(Writer& writer) override
    {
        std::expected<bool, int> rv = FunctionSymbol::Write(writer);
        if (!rv) return rv;
        rv = writer.GetBinaryStreamWriter().Write(distance);
        if (!rv) return rv;
        rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(conversionKind));
        if (!rv) return rv;
        rv = writer.GetBinaryStreamWriter().Write(paramType->Id());
        if (!rv) return rv;
        rv = writer.GetBinaryStreamWriter().Write(argType->Id());
        if (!rv) return rv;
        return std::expected<bool, int>(true);
    }
    std::expected<bool, int> Read(Reader& reader) override
    {
        std::expected<bool, int> rv = FunctionSymbol::Read(reader);
        if (!rv) return rv;
        std::expected<std::int32_t, int> rrv = reader.GetBinaryStreamReader().ReadInt();
        if (!rrv) return std::unexpected<int>(rrv.error());
        distance = *rrv;
        std::expected<std::uint8_t, int> brv = reader.GetBinaryStreamReader().ReadByte();
        if (!brv) return std::unexpected<int>(brv.error());
        std::uint8_t b = *brv;
        conversionKind = static_cast<ConversionKind>(b);
        rv = reader.GetBinaryStreamReader().ReadUuid(paramTypeId);
        if (!rv) return rv;
        rv = reader.GetBinaryStreamReader().ReadUuid(argTypeId);
        if (!rv) return rv;
        return std::expected<bool, int>(true);
    }
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override
    {
        std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
        if (!rv) return rv;
        paramType = symbolTable.GetType(paramTypeId);
        argType = symbolTable.GetType(argTypeId);
        return std::expected<bool, int>(true);
    }
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override
    {
        context->SetArgType(argType);
        context->SetParamType(paramType);
        otava::intermediate::Value* value = emitter.Stack().Pop();
        std::expected<otava::intermediate::Type*, int> irv = paramType->IrType(emitter, sourcePos, context);
        if (!irv) return std::unexpected<int>(irv.error());
        std::expected<otava::intermediate::Value*, int> rv = Op::Generate(emitter, value, static_cast<otava::intermediate::Type*>(*irv), context);
        if (!rv) return std::unexpected<int>(rv.error());
        emitter.Stack().Push(*rv);
        return std::expected<bool, int>(true);
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

class FundamentalTypeBoolToIntConversion : public FundamentalTypeConversion<FundamentalTypeBoolToInt>
{
public:
    FundamentalTypeBoolToIntConversion();
    FundamentalTypeBoolToIntConversion(TypeSymbol* boolType, TypeSymbol* destType, Context* context);
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
    std::expected<bool, int> Write(Writer& writer) override
    {
        std::expected<bool, int> rv = FunctionSymbol::Write(writer);
        if (!rv) return rv;
        rv = writer.GetBinaryStreamWriter().Write(paramType->Id());
        if (!rv) return rv;
        rv = writer.GetBinaryStreamWriter().Write(argType->Id());
        if (!rv) return rv;
        return std::expected<bool, int>(true);
    }
    std::expected<bool, int> Read(Reader& reader) override
    {
        std::expected<bool, int> rv = FunctionSymbol::Read(reader);
        if (!rv) return rv;
        rv = reader.GetBinaryStreamReader().ReadUuid(paramTypeId);
        if (!rv) return rv;
        rv = reader.GetBinaryStreamReader().ReadUuid(argTypeId);
        if (!rv) return rv;
        return std::expected<bool, int>(true);
    }
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override
    {
        std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
        if (!rv) return rv;
        paramType = symbolTable.GetType(paramTypeId);
        argType = symbolTable.GetType(argTypeId);
        return std::expected<bool, int>(true);
    }
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override
    {
        return std::expected<bool, int>(true);
    }
private:
    TypeSymbol* paramType;
    TypeSymbol* argType;
    util::uuid paramTypeId;
    util::uuid argTypeId;
};

} // namespace otava::symbols

