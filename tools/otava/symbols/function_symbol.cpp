// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module otava.symbols.function.symbol;

import otava.symbols.modules;
import otava.symbols.classes;
import otava.symbols.type.symbol;
import otava.symbols.symbol.table;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.templates;
import otava.symbols.value;
import otava.symbols.variable.symbol;
import otava.symbols.fundamental.type.conversion;
import util.sha1;
import util.unicode;

namespace otava::symbols {

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

FunctionSymbol::FunctionSymbol(const std::u32string& name_) : 
    ContainerSymbol(SymbolKind::functionSymbol, name_), returnType(nullptr), returnTypeId(util::nil_uuid()), memFunParamsConstructed(false)
{
}

FunctionSymbol::FunctionSymbol(SymbolKind kind_, const std::u32string& name_) :
    ContainerSymbol(kind_, name_), returnType(nullptr), returnTypeId(util::nil_uuid()), memFunParamsConstructed(false)
{
}

ConversionKind FunctionSymbol::GetConversionKind() const
{
    return ConversionKind::implicitConversion;
}

const std::vector<ParameterSymbol*>& FunctionSymbol::MemFunParameters() 
{
    if (memFunParamsConstructed) return memFunParameters;
    memFunParamsConstructed = true;
    Symbol* parent = Parent();
    if (parent->IsClassTypeSymbol())
    {
        ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(Parent());
        if ((Qualifiers() & FunctionQualifiers::isConst) != FunctionQualifiers::none)
        {
            thisParam.reset(new ParameterSymbol(U"this", classType->AddConst()->AddPointer()));
            memFunParameters.push_back(thisParam.get());
        }
        else
        {
            thisParam.reset(new ParameterSymbol(U"this", classType->AddPointer()));
            memFunParameters.push_back(thisParam.get());
        }
    }
    for (const auto& parameter : parameters)
    {
        memFunParameters.push_back(parameter);
    }
    return memFunParameters;
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
    if (Name() == U"operator+")
    {
        int x = 0;
    }
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

void FunctionSymbol::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    // TODO
}

otava::intermediate::Type* FunctionSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    otava::intermediate::Type* type = emitter.GetType(Id());
    if (!type)
    {
        otava::intermediate::Type* returnIrType = nullptr;
        if (returnType)
        {
            returnIrType = returnType->IrType(emitter, sourcePos, context);
        }
        std::vector<otava::intermediate::Type*> paramIrTypes;
        for (const auto& param : MemFunParameters())
        {
            paramIrTypes.push_back(param->GetType()->IrType(emitter, sourcePos, context));
        }
        type = emitter.MakeFunctionType(returnIrType, paramIrTypes);
        emitter.SetType(Id(), type);
    }
    return type;
}

std::string FunctionSymbol::IrName() const
{
    std::string fullName = util::ToUtf8(FullName());
    std::string irName = "function_" + util::ToUtf8(Name()) + "_" + util::GetSha1MessageDigest(fullName);
    return irName;
}

void FunctionSymbol::AddLocalVariable(VariableSymbol* localVariable, const soul::ast::SourcePos& sourcePos, Context* context)
{
    localVariables.push_back(localVariable);
}

FunctionDefinitionSymbol::FunctionDefinitionSymbol(const std::u32string& name_) : FunctionSymbol(SymbolKind::functionDefinitionSymbol, name_)
{
}

void FunctionDefinitionSymbol::Write(Writer& writer)
{
    FunctionSymbol::Write(writer);
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
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(declarationId);
}

void FunctionDefinitionSymbol::Accept(Visitor& visitor) 
{
    visitor.Visit(*this);
}

void FunctionDefinitionSymbol::Resolve(SymbolTable& symbolTable)
{
    FunctionSymbol::Resolve(symbolTable);
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

} // namespace otava::symbols
