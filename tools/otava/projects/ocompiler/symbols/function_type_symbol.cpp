// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.function.type.symbol;

import otava.symbols.symbol.table;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.emitter;
import otava.symbols.type_compare;
import util;

namespace otava::symbols {

FunctionTypeSymbol::FunctionTypeSymbol() : TypeSymbol(SymbolKind::functionTypeSymbol, std::u32string()), ptrIndex(-1), returnType(), returnTypeId()
{
}

FunctionTypeSymbol::FunctionTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::functionTypeSymbol, name_), ptrIndex(-1), returnType(), returnTypeId()
{
}

void FunctionTypeSymbol::MakeName()
{
    std::u32string name = returnType->Name();
    name.append(U" (");
    ptrIndex = static_cast<int>(name.length());
    name.append(U")(");
    bool first = true;
    for (TypeSymbol* parameterType : parameterTypes)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            name.append(U", ");
        }
        name.append(parameterType->Name());
    }
    name.append(U")");
    SetName(name);
}

void FunctionTypeSymbol::AddParameterType(TypeSymbol* parameterType)
{
    parameterTypes.push_back(parameterType);
}

std::expected<bool, int> FunctionTypeSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(returnType->Id());
    if (!rv) return rv;
    std::uint32_t paramTypeCount = parameterTypes.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(paramTypeCount);
    if (!rv) return rv;
    for (TypeSymbol* paramType : parameterTypes)
    {
        rv = writer.GetBinaryStreamWriter().Write(paramType->Id());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionTypeSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(returnTypeId);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::uint32_t paramTypeCount = *urv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(paramTypeCount); ++i)
    {
        util::uuid paramTypeId;
        rv = reader.GetBinaryStreamReader().ReadUuid(paramTypeId);
        if (!rv) return rv;
        parameterTypeIds.push_back(paramTypeId);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    returnType = symbolTable.GetType(returnTypeId);
    if (!returnType)
    {
        std::expected<std::u32string, int> fname = FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        std::cout << "FunctionTypeSymbol::Resolve(): warning: return type of '" + *sfname + "' not resolved" << "\n";
    }
    for (const auto& parameterTypeId : parameterTypeIds)
    {
        TypeSymbol* parameterType = symbolTable.GetType(parameterTypeId);
        if (parameterType)
        {
            parameterTypes.push_back(parameterType);
        }
        else
        {
            std::expected<std::u32string, int> fname = FullName();
            if (!fname) return std::unexpected<int>(fname.error());
            std::expected<std::string, int> sfname = util::ToUtf8(*fname);
            if (!sfname) return std::unexpected<int>(sfname.error());
            std::cout << "FunctionTypeSymbol::Resolve(): warning: parameter type of '" + *sfname + "' not resolved" << "\n";
        }
    }
    return std::expected<bool, int>(true);
}

void FunctionTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<otava::intermediate::Type*, int> FunctionTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Type* type = emitter.GetType(Id());
    if (!type)
    {
        std::vector<otava::intermediate::Type*> paramTypes;
        for (TypeSymbol* paramType : parameterTypes)
        {
            std::expected<otava::intermediate::Type*, int> rv = paramType->IrType(emitter, sourcePos, context);
            if (!rv) return rv;
            paramTypes.push_back(*rv);
        }
        std::expected<otava::intermediate::Type*, int> rv = returnType->IrType(emitter, sourcePos, context);
        if (!rv) return rv;
        otava::intermediate::Type* retType = *rv;
        rv = emitter.MakeFunctionType(retType, paramTypes);
        if (!rv) return rv;
        type = *rv;
        emitter.SetType(Id(), type);
    }
    return std::expected<otava::intermediate::Type*, int>(type);
}

bool FunctionTypesEqual(FunctionTypeSymbol* left, FunctionTypeSymbol* right, Context* context)
{
    int n = left->ParameterTypes().size();
    if (n != right->ParameterTypes().size()) return false;
    for (int i = 0; i < n; ++i)
    {
        TypeSymbol* leftParamType = left->ParameterTypes()[i];
        TypeSymbol* rightParamType = right->ParameterTypes()[i];
        if (!TypesEqual(leftParamType, rightParamType, context)) return false;
    }
    return TypesEqual(left->ReturnType(), right->ReturnType(), context);
}

} // namespace otava::symbols
