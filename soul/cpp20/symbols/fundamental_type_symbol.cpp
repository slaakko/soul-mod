// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.fundamental.type.symbol;

import util.unicode;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;

namespace soul::cpp20::symbols {

constexpr const char* fundamentalTypeNames[] =
{
    "none", "char", "char8_t", "char16_t", "char32_t", "wchar_t", "bool", "short int", "int", "long int", "long long int", "float", "double", "void",
    "signed char", "unsigned char", "unsigned short int", "unsigned int", "unsigned long int", "unsigned long long int", "long double", "auto"
};

class FundamentalTypeFlagMapper
{
public:
    static FundamentalTypeFlagMapper& Instance();
    FundamentalTypeKind GetFundamentalTypeKind(DeclarationFlags flags) const;
private:
    FundamentalTypeFlagMapper();
    std::map<DeclarationFlags, FundamentalTypeKind> flagMap;
};

FundamentalTypeFlagMapper& FundamentalTypeFlagMapper::Instance()
{
    static FundamentalTypeFlagMapper instance;
    return instance;
}

FundamentalTypeFlagMapper::FundamentalTypeFlagMapper()
{
    flagMap[DeclarationFlags::voidFlag] = FundamentalTypeKind::voidType;
    flagMap[DeclarationFlags::charFlag] = FundamentalTypeKind::charType;
    flagMap[DeclarationFlags::char8Flag] = FundamentalTypeKind::char8Type;
    flagMap[DeclarationFlags::char16Flag] = FundamentalTypeKind::char16Type;
    flagMap[DeclarationFlags::char32Flag] = FundamentalTypeKind::char32Type;
    flagMap[DeclarationFlags::wcharFlag] = FundamentalTypeKind::wcharType;
    flagMap[DeclarationFlags::boolFlag] = FundamentalTypeKind::boolType;
    flagMap[DeclarationFlags::shortFlag] = FundamentalTypeKind::shortIntType;
    flagMap[DeclarationFlags::shortFlag | DeclarationFlags::intFlag] = FundamentalTypeKind::shortIntType;
    flagMap[DeclarationFlags::intFlag] = FundamentalTypeKind::intType;
    flagMap[DeclarationFlags::longFlag] = FundamentalTypeKind::longIntType;
    flagMap[DeclarationFlags::longFlag | DeclarationFlags::intFlag] = FundamentalTypeKind::longIntType;
    flagMap[DeclarationFlags::longLongFlag] = FundamentalTypeKind::longLongIntType;
    flagMap[DeclarationFlags::longLongFlag | DeclarationFlags::intFlag] = FundamentalTypeKind::longLongIntType;
    flagMap[DeclarationFlags::signedFlag] = FundamentalTypeKind::intType;
    flagMap[DeclarationFlags::signedFlag | DeclarationFlags::charFlag] = FundamentalTypeKind::signedCharType;
    flagMap[DeclarationFlags::signedFlag | DeclarationFlags::longFlag] = FundamentalTypeKind::longIntType;
    flagMap[DeclarationFlags::signedFlag | DeclarationFlags::shortFlag] = FundamentalTypeKind::shortIntType;
    flagMap[DeclarationFlags::signedFlag | DeclarationFlags::intFlag] = FundamentalTypeKind::intType;
    flagMap[DeclarationFlags::signedFlag | DeclarationFlags::longLongFlag] = FundamentalTypeKind::longLongIntType;
    flagMap[DeclarationFlags::signedFlag | DeclarationFlags::longFlag | DeclarationFlags::intFlag] = FundamentalTypeKind::longIntType;
    flagMap[DeclarationFlags::signedFlag | DeclarationFlags::longLongFlag | DeclarationFlags::intFlag] = FundamentalTypeKind::longLongIntType;
    flagMap[DeclarationFlags::signedFlag | DeclarationFlags::shortFlag | DeclarationFlags::intFlag] = FundamentalTypeKind::shortIntType;
    flagMap[DeclarationFlags::unsignedFlag] = FundamentalTypeKind::unsignedIntType;
    flagMap[DeclarationFlags::unsignedFlag | DeclarationFlags::charFlag] = FundamentalTypeKind::unsignedCharType;
    flagMap[DeclarationFlags::unsignedFlag | DeclarationFlags::longFlag] = FundamentalTypeKind::unsignedLongIntType;
    flagMap[DeclarationFlags::unsignedFlag | DeclarationFlags::shortFlag] = FundamentalTypeKind::unsignedShortIntType;
    flagMap[DeclarationFlags::unsignedFlag | DeclarationFlags::intFlag] = FundamentalTypeKind::unsignedIntType;
    flagMap[DeclarationFlags::unsignedFlag | DeclarationFlags::shortFlag | DeclarationFlags::intFlag] = FundamentalTypeKind::unsignedShortIntType;
    flagMap[DeclarationFlags::unsignedFlag | DeclarationFlags::longFlag | DeclarationFlags::intFlag] = FundamentalTypeKind::unsignedLongIntType;
    flagMap[DeclarationFlags::unsignedFlag | DeclarationFlags::longLongFlag] = FundamentalTypeKind::unsignedLongLongIntType;
    flagMap[DeclarationFlags::unsignedFlag | DeclarationFlags::longLongFlag | DeclarationFlags::intFlag] = FundamentalTypeKind::unsignedLongLongIntType;
    flagMap[DeclarationFlags::floatFlag] = FundamentalTypeKind::floatType;
    flagMap[DeclarationFlags::doubleFlag] = FundamentalTypeKind::doubleType;
    flagMap[DeclarationFlags::longFlag | DeclarationFlags::doubleFlag] = FundamentalTypeKind::longDoubleType;
    flagMap[DeclarationFlags::autoFlag] = FundamentalTypeKind::autoType;
}

FundamentalTypeKind FundamentalTypeFlagMapper::GetFundamentalTypeKind(DeclarationFlags flags) const
{
    auto it = flagMap.find(flags);
    if (it != flagMap.cend())
    {
        return it->second;
    }
    else
    {
        return FundamentalTypeKind::none;
    }
}

std::u32string MakeFundamentalTypeName(FundamentalTypeKind kind)
{
    return util::ToUtf32(fundamentalTypeNames[static_cast<int32_t>(kind)]);
}

FundamentalTypeSymbol::FundamentalTypeSymbol(FundamentalTypeKind kind_) : TypeSymbol(SymbolKind::fundamentalTypeSymbol, MakeFundamentalTypeName(kind_)), kind(kind_)
{
}

void FundamentalTypeSymbol::Write(Writer& writer)
{
    static_assert(static_cast<int32_t>(FundamentalTypeKind::max) < 256);
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(kind));
}

void FundamentalTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    kind = static_cast<FundamentalTypeKind>(reader.GetBinaryStreamReader().ReadByte());
}

TypeSymbol* GetFundamentalType(DeclarationFlags fundamentalTypeFlags, const soul::ast::SourcePos& sourcePos, soul::cpp20::symbols::Context* context)
{
    FundamentalTypeKind fundamentalTypeKind = FundamentalTypeFlagMapper::Instance().GetFundamentalTypeKind(fundamentalTypeFlags);
    if (fundamentalTypeKind != FundamentalTypeKind::none)
    {
        return context->GetSymbolTable()->GetFundamentalTypeSymbol(fundamentalTypeKind);
    }
    else
    {
        throw Exception("invalid combination of fundamental type specifiers", sourcePos, context);
    }
}

} // namespace soul::cpp20::symbols
