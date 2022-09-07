// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module soul.cpp20.symbols.function.symbol;

import soul.cpp20.symbols.modules;
import soul.cpp20.symbols.type.symbol;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.visitor;
import soul.cpp20.symbols.templates;
import soul.cpp20.symbols.value;

namespace soul::cpp20::symbols {


std::string MakeFunctionQualifierStr(FunctionQualifiers qualifiers)
{
    std::string s;
    if ((qualifiers & FunctionQualifiers::isVolatile) != FunctionQualifiers::none)
    {
        s.append("volatile");
    }
    if ((qualifiers & FunctionQualifiers::isConst) != FunctionQualifiers::none)
    {
        if (!s.empty())
        {
            s.append(1, ' ');
        }
        s.append("const");
    }
    if ((qualifiers & FunctionQualifiers::isOverride) != FunctionQualifiers::none)
    {
        if (!s.empty())
        {
            s.append(1, ' ');
        }
        s.append("override");
    }
    if ((qualifiers & FunctionQualifiers::isFinal) != FunctionQualifiers::none)
    {
        if (!s.empty())
        {
            s.append(1, ' ');
        }
        s.append("final");
    }
    if ((qualifiers & FunctionQualifiers::isDefault) != FunctionQualifiers::none)
    {
        if (!s.empty())
        {
            s.append(1, ' ');
        }
        s.append("= default");
    }
    if ((qualifiers & FunctionQualifiers::isDeleted) != FunctionQualifiers::none)
    {
        if (!s.empty())
        {
            s.append(1, ' ');
        }
        s.append("= delete");
    }
    return s;
}

ParameterSymbol::ParameterSymbol(const std::u32string& name_) : 
    Symbol(SymbolKind::parameterSymbol, name_), 
    type(nullptr), 
    typeId(util::nil_uuid()), 
    defaultValue(nullptr), 
    defaultValueId(util::nil_uuid())
{
}

ParameterSymbol::ParameterSymbol(const std::u32string& name_, TypeSymbol* type_) : 
    Symbol(SymbolKind::parameterSymbol, name_), 
    type(type_), 
    typeId(util::nil_uuid()), 
    defaultValue(nullptr),
    defaultValueId(util::nil_uuid())
{
}

void ParameterSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(type->Id());
    bool hasDefaultValue = defaultValue != nullptr;
    writer.GetBinaryStreamWriter().Write(hasDefaultValue);
    if (hasDefaultValue)
    {
        writer.GetBinaryStreamWriter().Write(defaultValue->Id());
    }
}

void ParameterSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(typeId);
    bool hasDefaultValue = reader.GetBinaryStreamReader().ReadBool();
    if (hasDefaultValue)
    {
        reader.GetBinaryStreamReader().ReadUuid(defaultValueId);
    }
}

void ParameterSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    type = symbolTable.GetType(typeId);
    if (defaultValueId != util::nil_uuid())
    {
        EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
        defaultValue = evaluationContext->GetValue(defaultValueId);
    }
}

void ParameterSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FunctionSymbol::FunctionSymbol(const std::u32string& name_) : ContainerSymbol(SymbolKind::functionSymbol, name_), returnType(nullptr), returnTypeId(util::nil_uuid())
{
}

TemplateDeclarationSymbol* FunctionSymbol::ParentTemplateDeclaration()
{
    Symbol* parentSymbol = Parent();
    if (parentSymbol->IsTemplateDeclarationSymbol())
    {
        return static_cast<TemplateDeclarationSymbol*>(parentSymbol);
    }
    return nullptr;
}

void FunctionSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ContainerSymbol::AddSymbol(symbol, sourcePos, context);
    if (symbol->IsParameterSymbol())
    {
        parameters.push_back(static_cast<ParameterSymbol*>(symbol));
    }
}

void FunctionSymbol::AddParameter(ParameterSymbol* parameter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    AddSymbol(parameter, sourcePos, context);
}

void FunctionSymbol::Write(Writer& writer)
{
    ContainerSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(kind));
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(qualifiers));
    if (returnType)
    {
        writer.GetBinaryStreamWriter().Write(returnType->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
}

void FunctionSymbol::Read(Reader& reader)
{
    ContainerSymbol::Read(reader);
    kind = static_cast<FunctionKind>(reader.GetBinaryStreamReader().ReadByte());
    qualifiers = static_cast<FunctionQualifiers>(reader.GetBinaryStreamReader().ReadByte());
    reader.GetBinaryStreamReader().ReadUuid(returnTypeId);
}

void FunctionSymbol::Resolve(SymbolTable& symbolTable)
{
    ContainerSymbol::Resolve(symbolTable);
    if (returnTypeId != util::nil_uuid())
    {
        returnType = symbolTable.GetType(returnTypeId);
    }
}

void FunctionSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FunctionDefinitionSymbol::FunctionDefinitionSymbol(const std::u32string& name_) : ContainerSymbol(SymbolKind::functionDefinitionSymbol, name_)
{
}

void FunctionDefinitionSymbol::Write(Writer& writer)
{
    ContainerSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(qualifiers));
    if (returnType)
    {
        writer.GetBinaryStreamWriter().Write(returnType->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
    if (declaration)
    {
        writer.GetBinaryStreamWriter().Write(declaration->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
}

void FunctionDefinitionSymbol::Read(Reader& reader)
{
    ContainerSymbol::Read(reader);
    qualifiers = static_cast<FunctionQualifiers>(reader.GetBinaryStreamReader().ReadByte());
    reader.GetBinaryStreamReader().ReadUuid(returnTypeId);
    reader.GetBinaryStreamReader().ReadUuid(declarationId);
}

void FunctionDefinitionSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) 
{
    ContainerSymbol::AddSymbol(symbol, sourcePos, context);
    if (symbol->IsParameterSymbol())
    {
        parameters.push_back(static_cast<ParameterSymbol*>(symbol));
    }
}

void FunctionDefinitionSymbol::AddParameter(ParameterSymbol* parameter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    AddSymbol(parameter, sourcePos, context);
}

void FunctionDefinitionSymbol::Accept(Visitor& visitor) 
{
    visitor.Visit(*this);
}

void FunctionDefinitionSymbol::Resolve(SymbolTable& symbolTable)
{
    ContainerSymbol::Resolve(symbolTable);
    if (returnTypeId != util::nil_uuid())
    {
        returnType = symbolTable.GetType(returnTypeId);
    }
    if (declarationId != util::nil_uuid())
    {
        declaration = symbolTable.GetFunction(declarationId);
    }
}

bool FunctionLess::operator()(FunctionSymbol* left, FunctionSymbol* right) const
{
    if (int(left->GetFunctionKind()) < int(right->GetFunctionKind())) return true;
    if (int(left->GetFunctionKind()) > int(right->GetFunctionKind())) return false;
    return left->Name() < right->Name();
}

FunctionTypeSymbol::FunctionTypeSymbol() : TypeSymbol(SymbolKind::functionTypeSymbol, std::u32string()), ptrIndex(-1)
{
}

FunctionTypeSymbol::FunctionTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::functionTypeSymbol, name_), ptrIndex(-1)
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
    uint32_t paramTypeCount = parameterTypes.size();
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
    uint32_t paramTypeCount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < paramTypeCount; ++i)
    {
        util::uuid paramTypeId;
        reader.GetBinaryStreamReader().ReadUuid(paramTypeId);
        parameterTypeIds.push_back(paramTypeId);
    }
}

void FunctionTypeSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    returnType = symbolTable.GetType(returnTypeId);
    for (const auto& parameterTypeId : parameterTypeIds)
    {
        TypeSymbol* parameterType = symbolTable.GetType(parameterTypeId);
        parameterTypes.push_back(parameterType);
    }
}

void FunctionTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace soul::cpp20::symbols
