// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.fundamental.type.symbol;

import util.unicode;
import otava.symbols.context;
import otava.symbols.emitter;
import otava.symbols.error;
import otava.symbols.symbol.table;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.intermediate.types;

namespace otava::symbols {

std::string GetFundamentalTypeName(FundamentalTypeKind kind)
{
    switch (kind)
    {
        case FundamentalTypeKind::boolType: return "bool";
        case FundamentalTypeKind::charType: return "char";
        case FundamentalTypeKind::signedCharType: return "signed char";
        case FundamentalTypeKind::unsignedCharType: return "unsigned char";
        case FundamentalTypeKind::char8Type: return "char8_t";
        case FundamentalTypeKind::char16Type: return "char16_t";
        case FundamentalTypeKind::shortIntType: return "short int";
        case FundamentalTypeKind::unsignedShortIntType: return "unsigned short int";
        case FundamentalTypeKind::char32Type: return "char32_t";
        case FundamentalTypeKind::wcharType: return "wchar_t";
        case FundamentalTypeKind::intType: return "int";
        case FundamentalTypeKind::unsignedIntType: return "unsigned int";
        case FundamentalTypeKind::longIntType: return "long int";
        case FundamentalTypeKind::unsignedLongIntType: return "unsigned long int";
        case FundamentalTypeKind::longLongIntType: return "long long int";
        case FundamentalTypeKind::unsignedLongLongIntType: return "unsigned long long int";
        case FundamentalTypeKind::floatType: return "float";
        case FundamentalTypeKind::doubleType: return "double";
        case FundamentalTypeKind::longDoubleType: return "long double";
        case FundamentalTypeKind::voidType: return "void";
        case FundamentalTypeKind::autoType: return "auto";
        case FundamentalTypeKind::nullPtrType: return "nullptr_t";
    }
    return "<fundamental type>";
}

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

std::expected<std::u32string, int> MakeFundamentalTypeName(FundamentalTypeKind kind)
{
    return util::ToUtf32(GetFundamentalTypeName(kind));
}

FundamentalTypeSymbol::FundamentalTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::fundamentalTypeSymbol, name_), fundamentalTypeKind()
{
}

FundamentalTypeSymbol::FundamentalTypeSymbol(FundamentalTypeKind kind_) : TypeSymbol(SymbolKind::fundamentalTypeSymbol, std::u32string()), fundamentalTypeKind(kind_)
{
    std::expected<std::u32string, int> rv = MakeFundamentalTypeName(fundamentalTypeKind);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    SetName(*rv);
}

bool FundamentalTypeSymbol::IsIntegralType() const
{
    switch (fundamentalTypeKind)
    {
        case FundamentalTypeKind::charType:
        case FundamentalTypeKind::signedCharType:
        case FundamentalTypeKind::unsignedCharType:
        case FundamentalTypeKind::char8Type:
        case FundamentalTypeKind::char16Type:
        case FundamentalTypeKind::shortIntType:
        case FundamentalTypeKind::unsignedShortIntType:
        case FundamentalTypeKind::char32Type:
        case FundamentalTypeKind::wcharType:
        case FundamentalTypeKind::intType:
        case FundamentalTypeKind::unsignedIntType:
        case FundamentalTypeKind::longIntType:
        case FundamentalTypeKind::unsignedLongIntType:
        case FundamentalTypeKind::longLongIntType:
        case FundamentalTypeKind::unsignedLongLongIntType:
        {
            return true;
        }
    }
    return false;
}

std::expected<bool, int> FundamentalTypeSymbol::Write(Writer& writer)
{
    static_assert(static_cast<std::int32_t>(FundamentalTypeKind::max) < 256);
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    std::uint8_t k = static_cast<uint8_t>(static_cast<int32_t>(fundamentalTypeKind));
    rv = writer.GetBinaryStreamWriter().Write(k);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint8_t, int> brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t b = *brv;
    fundamentalTypeKind = static_cast<FundamentalTypeKind>(static_cast<int32_t>(b));
    return std::expected<bool, int>(true);
}

void FundamentalTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<otava::intermediate::Type*, int> FundamentalTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    switch (fundamentalTypeKind)
    {
        case FundamentalTypeKind::charType:
        case FundamentalTypeKind::unsignedCharType:
        case FundamentalTypeKind::char8Type:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetByteType());
        }
        case FundamentalTypeKind::signedCharType:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetSByteType());
        }
        case FundamentalTypeKind::shortIntType:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetShortType());
        }
        case FundamentalTypeKind::char16Type:
        case FundamentalTypeKind::wcharType:
        case FundamentalTypeKind::unsignedShortIntType:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetUShortType());
        }
        case FundamentalTypeKind::intType:
        case FundamentalTypeKind::longIntType:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetIntType());
        }
        case FundamentalTypeKind::char32Type:
        case FundamentalTypeKind::unsignedIntType:
        case FundamentalTypeKind::unsignedLongIntType:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetUIntType());
        }
        case FundamentalTypeKind::boolType:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetBoolType());
        }
        case FundamentalTypeKind::longLongIntType:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetLongType());
        }
        case FundamentalTypeKind::unsignedLongLongIntType:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetULongType());
        }
        case FundamentalTypeKind::floatType:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetFloatType());
        }
        case FundamentalTypeKind::doubleType:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetDoubleType());
        }
        case FundamentalTypeKind::voidType:
        {
            return std::expected<otava::intermediate::Type*, int>(emitter.GetVoidType());
        }
        case FundamentalTypeKind::nullPtrType:
        {
            return emitter.MakePtrType(emitter.GetVoidType());
        }
        default:
        {
            return Error("unsupported fundamental type", sourcePos, context);
        }
    }
    return std::expected<otava::intermediate::Type*, int>(nullptr);
}

std::expected<TypeSymbol*, int> GetFundamentalType(DeclarationFlags fundamentalTypeFlags, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    FundamentalTypeKind fundamentalTypeKind = FundamentalTypeFlagMapper::Instance().GetFundamentalTypeKind(fundamentalTypeFlags);
    if (fundamentalTypeKind != FundamentalTypeKind::none)
    {
        return context->GetSymbolTable()->GetFundamentalTypeSymbol(fundamentalTypeKind);
    }
    else
    {
        return Error("invalid combination of fundamental type specifiers", sourcePos, context);
    }
}

} // namespace otava::symbols

