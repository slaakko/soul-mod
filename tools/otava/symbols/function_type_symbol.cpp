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
    ptrIndex = name.length();
    name.append(U")(");
    bool first = true;
    for (const auto& parameterType : parameterTypes)
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

void FunctionTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(returnType->Id());
    std::uint32_t paramTypeCount = parameterTypes.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(paramTypeCount);
    for (const auto& paramType : parameterTypes)
    {
        writer.GetBinaryStreamWriter().Write(paramType->Id());
    }
}

void FunctionTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(returnTypeId);
    std::uint32_t paramTypeCount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < paramTypeCount; ++i)
    {
        util::uuid paramTypeId;
        reader.GetBinaryStreamReader().ReadUuid(paramTypeId);
        parameterTypeIds.push_back(paramTypeId);
    }
}

void FunctionTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol::Resolve(symbolTable, context);
    returnType = symbolTable.GetType(returnTypeId);
    if (!returnType)
    {
        std::cout << "FunctionTypeSymbol::Resolve(): warning: return type of '" + util::ToUtf8(FullName()) + "' not resolved" << "\n";
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
            std::cout << "FunctionTypeSymbol::Resolve(): warning: parameter type of '" + util::ToUtf8(FullName()) + "' not resolved" << "\n";
        }
    }
}

void FunctionTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

otava::intermediate::Type* FunctionTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Type* type = emitter.GetType(Id());
    if (!type)
    {
        std::vector<otava::intermediate::Type*> paramTypes;
        for (const auto& paramType : parameterTypes)
        {
            paramTypes.push_back(paramType->IrType(emitter, sourcePos, context));
        }
        type = emitter.MakeFunctionType(returnType->IrType(emitter, sourcePos, context), paramTypes);
        emitter.SetType(Id(), type);
    }
    return type;
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
