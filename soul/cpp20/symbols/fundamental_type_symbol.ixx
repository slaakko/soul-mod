// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.fundamental.type.symbol;

import std.core;
import soul.ast.source.pos;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.type.symbol;
import soul.cpp20.symbols.declaration;

export namespace soul::cpp20::symbols {

class Context;

enum class FundamentalTypeKind : int32_t
{
    none, charType, char8Type, char16Type, char32Type, wcharType, boolType, shortIntType, intType, longIntType, longLongIntType, floatType, doubleType, voidType,
    signedCharType, unsignedCharType, unsignedShortIntType, unsignedIntType, unsignedLongIntType, unsignedLongLongIntType, longDoubleType, autoType, max
};

class FundamentalTypeSymbol : public TypeSymbol
{
public:
    FundamentalTypeSymbol(const std::u32string& name_);
    FundamentalTypeSymbol(FundamentalTypeKind kind_);
    FundamentalTypeKind GetFundamentalTypeKind() const { return kind; }
    std::string SymbolKindStr() const override { return "fundamental type symbol"; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
private:
    FundamentalTypeKind kind;
};

TypeSymbol* GetFundamentalType(DeclarationFlags fundamentalTypeFlags, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace soul::cpp20::symbols
