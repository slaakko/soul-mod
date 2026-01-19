// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.kind;

import std;

export namespace otava::symbols {

enum class FunctionKind
{
    function, constructor, destructor, special, conversionMemFn
};

std::string FunctionKindStr(FunctionKind functionKind);

enum class SpecialFunctionKind
{
    none, defaultCtor, copyCtor, moveCtor, copyAssignment, moveAssignment, dtor
};

std::string SpecialFunctionKindPrefix(SpecialFunctionKind specialFunctionKind);

enum class Linkage : std::int32_t
{
    c_linkage, cpp_linkage
};

enum class FunctionQualifiers : std::uint16_t
{
    none = 0, isConst = 1 << 0, isVolatile = 1 << 1, isOverride = 1 << 2, isFinal = 1 << 3, isPure = 1 << 4, isDefault = 1 << 5, isDeleted = 1 << 6, 
    noreturn = 1 << 7, isNoexcept = 1 << 8
};

enum class ConversionKind : std::int32_t
{
    implicitConversion, explicitConversion
};

constexpr FunctionQualifiers operator|(FunctionQualifiers left, FunctionQualifiers right)
{
    return FunctionQualifiers(std::int32_t(left) | std::int32_t(right));
}

constexpr FunctionQualifiers operator&(FunctionQualifiers left, FunctionQualifiers right)
{
    return FunctionQualifiers(std::int32_t(left) & std::int32_t(right));
}

constexpr FunctionQualifiers operator~(FunctionQualifiers qualifiers)
{
    return FunctionQualifiers(~std::int32_t(qualifiers));
}

std::string MakeFunctionQualifierStr(FunctionQualifiers qualifiers);

enum class FunctionSymbolFlags : std::int32_t
{
    none = 0, bound = 1 << 0, specialization = 1 << 1, trivialDestructor = 1 << 2, returnsClass = 1 << 3, conversion = 1 << 4, fixedIrName = 1 << 5, inline_ = 1 << 6,
    generated = 1 << 7, skip = 1 << 8, containsReturnStatement = 1 << 9, containsStatics = 1 << 10
};

constexpr FunctionSymbolFlags operator|(FunctionSymbolFlags left, FunctionSymbolFlags right)
{
    return FunctionSymbolFlags(std::int32_t(left) | std::int32_t(right));
}

constexpr FunctionSymbolFlags operator&(FunctionSymbolFlags left, FunctionSymbolFlags right)
{
    return FunctionSymbolFlags(std::int32_t(left) & std::int32_t(right));
}

constexpr FunctionSymbolFlags operator~(FunctionSymbolFlags flags)
{
    return FunctionSymbolFlags(~std::int32_t(flags));
}

} // namespace otava::symbols
