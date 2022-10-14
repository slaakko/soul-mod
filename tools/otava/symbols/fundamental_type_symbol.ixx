// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.fundamental.type.symbol;

import std.core;
import soul.ast.source.pos;
import otava.symbols.namespaces;
import otava.symbols.type.symbol;
import otava.symbols.declaration;

export namespace otava::symbols {

class Context;

enum class FundamentalTypeKind : int32_t
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
    FundamentalTypeKind GetFundamentalTypeKind() const { return kind; }
    bool IsAutoTypeSymbol() const { return kind == FundamentalTypeKind::autoType; }
    std::string SymbolKindStr() const override { return "fundamental type symbol"; }
    std::string SymbolDocKindStr() const override { return "fundamental_type"; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    bool IsVoidType() const override { return kind == FundamentalTypeKind::voidType; }
    bool IsBoolType() const override { return kind == FundamentalTypeKind::boolType; }
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    int32_t Score() const { return static_cast<int32_t>(kind); }
private:
    FundamentalTypeKind kind;
};

TypeSymbol* GetFundamentalType(DeclarationFlags fundamentalTypeFlags, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
