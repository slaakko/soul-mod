// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.fundamental.type.symbol;

import std;
import soul.ast.source.pos;
import otava.symbols.namespaces;
import otava.symbols.type.symbol;
import otava.symbols.declaration;

export namespace otava::symbols {

class Context;

enum class FundamentalTypeKind : std::uint8_t
{
    none, boolType, charType, signedCharType, unsignedCharType, char8Type, char16Type,
    shortIntType, unsignedShortIntType, char32Type, wcharType, intType, unsignedIntType, longIntType, unsignedLongIntType,
    longLongIntType, unsignedLongLongIntType, floatType, doubleType, longDoubleType, voidType, autoType, nullPtrType,
    max
};

int Rank(FundamentalTypeKind fundamentalTypeKind) noexcept;
bool IsSignedIntegerType(FundamentalTypeKind fundamentalTypeKind) noexcept;
bool IsUnsignedIntegerType(FundamentalTypeKind fundamentalTypeKind) noexcept;

class FundamentalTypeSymbol : public TypeSymbol
{
public:
    FundamentalTypeSymbol(const std::u32string& name_);
    FundamentalTypeSymbol(FundamentalTypeKind kind_);
    inline FundamentalTypeKind GetFundamentalTypeKind() const noexcept { return fundamentalTypeKind; }
    inline bool IsAutoTypeSymbol() const noexcept { return fundamentalTypeKind == FundamentalTypeKind::autoType; }
    bool IsIntegralType() const noexcept override;
    std::string SymbolKindStr() const override { return "fundamental type symbol"; }
    std::string SymbolDocKindStr() const override { return "fundamental_type"; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    bool IsBoolType() const noexcept override { return fundamentalTypeKind == FundamentalTypeKind::boolType; }
    bool IsIntType() const noexcept override { return fundamentalTypeKind == FundamentalTypeKind::intType; }
    bool IsUnsignedShortType() const noexcept override { return fundamentalTypeKind == FundamentalTypeKind::unsignedShortIntType; }
    bool IsVoidType() const noexcept override { return fundamentalTypeKind == FundamentalTypeKind::voidType; }
    bool IsNullPtrType() const noexcept override { return fundamentalTypeKind == FundamentalTypeKind::nullPtrType; }
    bool IsDoubleType() const noexcept override { return fundamentalTypeKind == FundamentalTypeKind::doubleType; }
    bool IsFloatType() const noexcept override { return fundamentalTypeKind == FundamentalTypeKind::floatType; }
    bool IsCharTypeSymbol() const noexcept override { return fundamentalTypeKind == FundamentalTypeKind::charType; }
    bool IsChar8TypeSymbol() const noexcept override { return fundamentalTypeKind == FundamentalTypeKind::char8Type; }
    bool IsChar16TypeSymbol() const noexcept override { return fundamentalTypeKind == FundamentalTypeKind::char16Type; }
    bool IsChar32TypeSymbol() const noexcept override { return fundamentalTypeKind == FundamentalTypeKind::char32Type; }
    int Rank() const noexcept override { return otava::symbols::Rank(fundamentalTypeKind); }
    bool IsSignedIntegerType() const noexcept override { return otava::symbols::IsSignedIntegerType(fundamentalTypeKind);; }
    bool IsUnsignedIntegerType() const noexcept override { return otava::symbols::IsUnsignedIntegerType(fundamentalTypeKind);; }
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline std::int32_t Score() const noexcept { return static_cast<std::uint8_t>(fundamentalTypeKind); }
private:
    FundamentalTypeKind fundamentalTypeKind;
};

TypeSymbol* GetFundamentalType(DeclarationFlags fundamentalTypeFlags, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
