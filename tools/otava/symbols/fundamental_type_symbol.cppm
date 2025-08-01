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

enum class FundamentalTypeKind : std::int32_t
{
    none, boolType, charType, signedCharType, unsignedCharType, char8Type, char16Type, 
    shortIntType, unsignedShortIntType, char32Type, wcharType, intType, unsignedIntType, longIntType, unsignedLongIntType, 
    longLongIntType, unsignedLongLongIntType, floatType, doubleType, longDoubleType, voidType, autoType, nullPtrType, 
    max
};

class FundamentalTypeSymbol : public TypeSymbol
{
public:
    FundamentalTypeSymbol(const std::u32string& name_);
    FundamentalTypeSymbol(FundamentalTypeKind kind_);
    inline FundamentalTypeKind GetFundamentalTypeKind() const { return fundamentalTypeKind; }
    inline bool IsAutoTypeSymbol() const { return fundamentalTypeKind == FundamentalTypeKind::autoType; }
    bool IsIntegralType() const override;
    std::string SymbolKindStr() const override { return "fundamental type symbol"; }
    std::string SymbolDocKindStr() const override { return "fundamental_type"; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    inline bool IsBoolType() const override { return fundamentalTypeKind == FundamentalTypeKind::boolType; }
    inline bool IsVoidType() const override { return fundamentalTypeKind == FundamentalTypeKind::voidType; }
    inline bool IsNullPtrType() const override { return fundamentalTypeKind == FundamentalTypeKind::nullPtrType; }
    inline bool IsDoubleType() const override { return fundamentalTypeKind == FundamentalTypeKind::doubleType; }
    inline bool IsFloatType() const override { return fundamentalTypeKind == FundamentalTypeKind::floatType; }
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline std::int32_t Score() const { return static_cast<std::int32_t>(fundamentalTypeKind); }
private:
    FundamentalTypeKind fundamentalTypeKind;
};

TypeSymbol* GetFundamentalType(DeclarationFlags fundamentalTypeFlags, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
