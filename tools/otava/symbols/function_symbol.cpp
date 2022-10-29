// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module otava.symbols.function.symbol;

import otava.symbols.modules;
import otava.symbols.classes;
import otava.symbols.declaration;
import otava.symbols.emitter;
import otava.symbols.exception;
import otava.symbols.alias.type.symbol;
import otava.symbols.type.symbol;
import otava.symbols.symbol.table;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;
import otava.symbols.templates;
import otava.symbols.value;
import otava.symbols.variable.symbol;
import otava.symbols.fundamental.type.conversion;
import otava.symbols.bound.node;
import otava.intermediate.function;
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

TypeSymbol* ParameterSymbol::GetReferredType() const
{
    TypeSymbol* referredType = type;
    while (referredType->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(referredType);
        referredType = aliasType->ReferredType();
    }
    return referredType;
}

FunctionSymbol::FunctionSymbol(const std::u32string& name_) : 
    ContainerSymbol(SymbolKind::functionSymbol, name_), returnType(nullptr), returnTypeId(util::nil_uuid()), memFunParamsConstructed(false)
{
}

FunctionSymbol::FunctionSymbol(SymbolKind kind_, const std::u32string& name_) :
    ContainerSymbol(kind_, name_), returnType(nullptr), returnTypeId(util::nil_uuid()), memFunParamsConstructed(false)
{
}

int FunctionSymbol::Arity() const
{
    return parameters.size();
}

int FunctionSymbol::MemFunArity() const
{
    const Symbol* parent = Parent();
    if (parent && parent->IsClassTypeSymbol())
    {
        return parameters.size() + 1;
    }
    else
    {
        return parameters.size();
    }
}

ConversionKind FunctionSymbol::GetConversionKind() const
{
    return ConversionKind::implicitConversion;
}

bool FunctionSymbol::IsVirtual() const
{
    if ((GetDeclarationFlags() & DeclarationFlags::virtualFlag) != DeclarationFlags::none) return true;
    if ((qualifiers & FunctionQualifiers::isOverride) != FunctionQualifiers::none) return true;
    if ((qualifiers & FunctionQualifiers::isFinal) != FunctionQualifiers::none) return true;
    return false;
}

ParameterSymbol* FunctionSymbol::ThisParam()
{
    Symbol* parent = Parent();
    if (parent && parent->IsClassTypeSymbol())
    {
        if (!thisParam)
        {
            ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(parent);
            if ((Qualifiers() & FunctionQualifiers::isConst) != FunctionQualifiers::none)
            {
                thisParam.reset(new ParameterSymbol(U"this", classType->AddConst()->AddPointer()));
            }
            else
            {
                thisParam.reset(new ParameterSymbol(U"this", classType->AddPointer()));
            }
        }
        return thisParam.get();
    }
    else
    {
        return nullptr;
    }
}

const std::vector<ParameterSymbol*>& FunctionSymbol::MemFunParameters() 
{
    if (memFunParamsConstructed) return memFunParameters;
    memFunParamsConstructed = true;
    Symbol* parent = Parent();
    if (parent && parent->IsClassTypeSymbol())
    {
        memFunParameters.push_back(ThisParam());
    }
    for (const auto& parameter : parameters)
    {
        memFunParameters.push_back(parameter);
    }
    return memFunParameters;
}

bool FunctionSymbol::IsMemberFunction() const
{
    const Symbol* parent = Parent();
    return parent && parent->IsClassTypeSymbol();
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

std::u32string FunctionSymbol::FullName() const
{
    std::u32string fullName = Parent()->FullName() + U"(";
    bool first = true;
    for (const auto& parameter : parameters)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            fullName.append(U", ");
        }
        fullName.append(parameter->GetType()->FullName());
    }
    fullName.append(U")");
    return fullName;
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

void FunctionSymbol::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    int n = args.size();
    for (int i = 0; i < n; ++i)
    {
        args[i]->Load(emitter, OperationFlags::none, sourcePos, context);
    }
    std::vector<otava::intermediate::Value*> arguments;
    arguments.resize(n);
    for (int i = 0; i < n; ++i)
    {
        otava::intermediate::Value* arg = emitter.Stack().Pop();
        arguments[n - i - 1] = arg;
    }
    otava::intermediate::Type* type = IrType(emitter, sourcePos, context);
    if (type->IsFunctionType())
    {
        otava::intermediate::FunctionType* functionType = static_cast<otava::intermediate::FunctionType*>(type);
        otava::intermediate::Function* function = emitter.GetOrInsertFunction(IrName(), functionType);
        if (!functionType->ReturnType() || functionType->ReturnType()->IsVoidType())
        {
            emitter.EmitCall(function, arguments);
        }
        else
        {
            emitter.Stack().Push(emitter.EmitCall(function, arguments));
        }
    }
    else
    {
        ThrowException("function type expected", sourcePos, context);
    }
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
            paramIrTypes.push_back(param->GetReferredType()->IrType(emitter, sourcePos, context));
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

} // namespace otava::symbols
