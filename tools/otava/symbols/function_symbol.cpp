// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

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
import otava.symbols.bound.tree;
import otava.symbols.context;
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

std::string SpecialFunctionKindPrefix(SpecialFunctionKind specialFunctionKind)
{
    switch (specialFunctionKind)
    {
        case SpecialFunctionKind::defaultCtor: return "default_ctor";
        case SpecialFunctionKind::copyCtor: return "copy_ctor";
        case SpecialFunctionKind::moveCtor: return "move_ctor";
        case SpecialFunctionKind::copyAssignment: return "copy_assignment";
        case SpecialFunctionKind::moveAssignment: return "move_assignment";
        case SpecialFunctionKind::dtor: return "dtor";
    }
    return std::string();
}

class OperatorFunctionMap
{
public:
    OperatorFunctionMap();
    static OperatorFunctionMap& Instance();
    void Init();
    std::string GetPrefix(const std::u32string& name) const;
private:
    std::map<std::u32string, std::string> map;
};

OperatorFunctionMap::OperatorFunctionMap()
{
    map[U"operator new[]"] = "op_new_array";
    map[U"operator new"] = "op_new";
    map[U"operator delete[]"] = "op_delete_array";
    map[U"operator delete"] = "op_delete";
    map[U"operator co_await"] = "op_co_await";
    map[U"operator()"] = "op_apply";
    map[U"operator[]"] = "op_subscript";
    map[U"operator->"] = "op_arrow";
    map[U"operator->*"] = "op_arrow_star";
    map[U"operator~"] = "op_cpl";
    map[U"operator!"] = "op_not";
    map[U"operator+"] = "op_plus";
    map[U"operator-"] = "op_minus";
    map[U"operator*"] = "op_star";
    map[U"operator/"] = "op_div";
    map[U"operator%"] = "op_mod";
    map[U"operator^"] = "op_xor";
    map[U"operator&"] = "op_and";
    map[U"operator|"] = "op_or";
    map[U"operator="] = "op_assign";
    map[U"operator+="] = "op_plus_assign";
    map[U"operator-="] = "op_minus_assign";
    map[U"operator*="] = "op_mul_assign";
    map[U"operator/="] = "op_div_assign";
    map[U"operator%="] = "op_mod_assign"; 
    map[U"operator^="] = "op_xor_assign";
    map[U"operator&="] = "op_and_assign";
    map[U"operator|="] = "op_or_assign";
    map[U"operator<<="] = "op_shift_left_assign";
    map[U"operator>>="] = "op_shift_right_assign";
    map[U"operator=="] = "op_eq";
    map[U"operator!="] = "op_neq";
    map[U"operator<="] = "op_leq";
    map[U"operator>="] = "op_geq";
    map[U"operator<=>"] = "op_compare";
    map[U"operator<"] = "op_less";
    map[U"operator>"] = "op_greater";
    map[U"operator&&"] = "op_conjuction";
    map[U"operator||"] = "op_disjuction";
    map[U"operator<<"] = "op_shift_left";
    map[U"operator>>"] = "op_shift_right";
    map[U"operator++"] = "op_plus_plus";
    map[U"operator--"] = "op_minus_minus";
    map[U"operator,"] = "op_comma";
}

OperatorFunctionMap& OperatorFunctionMap::Instance()
{
    static OperatorFunctionMap instance;
    return instance;
}

void OperatorFunctionMap::Init()
{
}

std::string OperatorFunctionMap::GetPrefix(const std::u32string& name) const
{
    auto it = map.find(name);
    if (it != map.cend())
    {
        return it->second;
    }
    else
    {
        return std::string();
    }
}

std::string GetOperatorFunctionPrefix(const std::u32string& functionName)
{
    return OperatorFunctionMap::Instance().GetPrefix(functionName);
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

TypeSymbol* ParameterSymbol::GetReferredType(Context* context) const
{
    TypeSymbol* referredType = type->GetBaseType();
    while (referredType->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(referredType);
        referredType = aliasType->ReferredType();
    }
    if (type->IsCompoundType())
    {
        referredType = context->GetSymbolTable()->MakeCompoundType(referredType, type->GetDerivations());
    }
    return referredType;
}

FunctionSymbol::FunctionSymbol(const std::u32string& name_) : 
    ContainerSymbol(SymbolKind::functionSymbol, name_), 
    returnType(nullptr), 
    returnTypeId(util::nil_uuid()), 
    memFunParamsConstructed(false), 
    linkage(Linkage::cpp_linkage), 
    index(0),
    flags(FunctionSymbolFlags::none),
    nextTemporaryId(0),
    kind(),
    qualifiers()
{
    GetScope()->SetKind(ScopeKind::functionScope);
}

FunctionSymbol::FunctionSymbol(SymbolKind kind_, const std::u32string& name_) :
    ContainerSymbol(kind_, name_), 
    returnType(nullptr), 
    returnTypeId(util::nil_uuid()), 
    memFunParamsConstructed(false), 
    linkage(Linkage::cpp_linkage),
    index(0),
    flags(FunctionSymbolFlags::none),
    nextTemporaryId(0),
    kind(),
    qualifiers()
{
    GetScope()->SetKind(ScopeKind::functionScope);
}

std::u32string FunctionSymbol::GroupName() const
{
    if (kind == FunctionKind::constructor)
    {
        return U"@constructor";
    }
    else if (kind == FunctionKind::destructor)
    {
        return U"@destructor";
    }
    else
    {
        return Name();
    }
}

int FunctionSymbol::Arity() const
{
    return parameters.size();
}

int FunctionSymbol::MemFunArity() const
{
    return MemFunParameters().size();
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

ClassTypeSymbol* FunctionSymbol::ParentClassType() const
{
    Symbol* parent = const_cast<FunctionSymbol*>(this)->Parent();
    if (parent && parent->IsClassTypeSymbol())
    {
        return static_cast<ClassTypeSymbol*>(parent);
    }
    else
    {
        Scope* scope = const_cast<FunctionSymbol*>(this)->GetScope();
        Scope* classScope = scope->GetClassScope();
        if (classScope)
        {
            Symbol* symbol = classScope->GetSymbol();
            if (symbol && symbol->IsClassTypeSymbol())
            {
                return static_cast<ClassTypeSymbol*>(symbol);
            }
        }
    }
    return nullptr;
}

ParameterSymbol* FunctionSymbol::ThisParam() const
{
    if (!thisParam)
    {
        ClassTypeSymbol* classType = ParentClassType();
        if (classType)
        {
            if ((Qualifiers() & FunctionQualifiers::isConst) != FunctionQualifiers::none)
            {
                thisParam.reset(new ParameterSymbol(U"this", classType->AddConst()->AddPointer()));
            }
            else
            {
                thisParam.reset(new ParameterSymbol(U"this", classType->AddPointer()));
            }
        }
    }
    return thisParam.get();
}

const std::vector<ParameterSymbol*>& FunctionSymbol::MemFunParameters() const
{
    if (memFunParamsConstructed) return memFunParameters;
    memFunParamsConstructed = true;
    ParameterSymbol* thisParam = ThisParam();
    if (thisParam)
    {
        memFunParameters.push_back(thisParam);
    }
    for (const auto& parameter : parameters)
    {
        memFunParameters.push_back(parameter);
    }
    return memFunParameters;
}

bool FunctionSymbol::IsMemberFunction() const
{
    ClassTypeSymbol* classType = ParentClassType();
    if (classType)
    {
        return true;
    }
    else
    {
        return false;
    }
}

SpecialFunctionKind FunctionSymbol::GetSpecialFunctionKind() const
{
    ClassTypeSymbol* classType = ParentClassType();
    if (classType)
    {
        const std::vector<ParameterSymbol*>& memFunParams = MemFunParameters();
        TypeSymbol* pointerType = classType->AddPointer();
        if (memFunParams.size() == 1 && TypesEqual(memFunParams[0]->GetType(), pointerType) && Name() == classType->Name()) return SpecialFunctionKind::defaultCtor;
        if (memFunParams.size() == 1 && TypesEqual(memFunParams[0]->GetType(), pointerType) && Name() == U"~" + classType->Name()) return SpecialFunctionKind::dtor;
        TypeSymbol* constRefType = classType->AddConst()->AddLValueRef();
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType) && Name() == classType->Name() &&
            TypesEqual(memFunParams[1]->GetType(), constRefType)) return SpecialFunctionKind::copyCtor;
        TypeSymbol* rvalueRefType = classType->AddRValueRef();
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType) && Name() == classType->Name() &&
            TypesEqual(memFunParams[1]->GetType(), rvalueRefType)) return SpecialFunctionKind::moveCtor;
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType) && Name() == U"operator=" &&
            TypesEqual(memFunParams[1]->GetType(), constRefType)) return SpecialFunctionKind::copyAssignment;
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType) && Name() == U"operator=" &&
            TypesEqual(memFunParams[1]->GetType(), rvalueRefType)) return SpecialFunctionKind::moveAssignment;
    }
    return SpecialFunctionKind::none;
}

TemplateDeclarationSymbol* FunctionSymbol::ParentTemplateDeclaration() const
{
    Symbol* parentSymbol = const_cast<FunctionSymbol*>(this)->Parent();
    if (parentSymbol && parentSymbol->IsTemplateDeclarationSymbol())
    {
        return static_cast<TemplateDeclarationSymbol*>(parentSymbol);
    }
    return nullptr;
}

void FunctionSymbol::SetReturnType(TypeSymbol* returnType_, Context* context)
{
    returnType = returnType_;
    if (returnType)
    {
        context->GetSymbolTable()->MapType(returnType);
        if (returnType->IsClassTypeSymbol())
        {
            SetReturnsClass();
            context->GetSymbolTable()->MapType(returnType);
            context->GetSymbolTable()->MapType(returnType->AddPointer());
            SetReturnValueParam(new ParameterSymbol(U"@return_value", returnType->AddPointer()));
        }
    }
}

bool FunctionSymbol::IsTemplate() const
{
    return ParentTemplateDeclaration() != nullptr && !IsSpecialization();
}

bool FunctionSymbol::IsMemFnOfClassTemplate() const
{
    if (IsSpecialization()) return false;
    ClassTypeSymbol* parentClassType = ParentClassType();
    if (parentClassType && parentClassType->IsTemplate())
    {
        return true;
    }
    return false;
}

std::u32string FunctionSymbol::FullName() const
{
    ClassTypeSymbol* parentClassType = ParentClassType();
    std::u32string fullName;
    if (parentClassType)
    {
        fullName = parentClassType->FullName();
    }
    else
    {
        fullName = Parent()->FullName();
    }
    fullName.append(U"::").append(Name()).append(U"(");
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
    std::string qualifierStr = MakeFunctionQualifierStr(Qualifiers());
    if (!qualifierStr.empty())
    {
        fullName.append(U" ").append(util::ToUtf32(qualifierStr));
    }
    return fullName;
}

void FunctionSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ContainerSymbol::AddSymbol(symbol, sourcePos, context);
    if (symbol->IsParameterSymbol())
    {
        parameters.push_back(static_cast<ParameterSymbol*>(symbol));
    }
    if (symbol->IsLocalVariableSymbol())
    {
        localVariables.push_back(static_cast<VariableSymbol*>(symbol));
    }
}

void FunctionSymbol::AddParameter(ParameterSymbol* parameter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    AddSymbol(parameter, sourcePos, context);
}

void FunctionSymbol::SetReturnValueParam(ParameterSymbol* returnValueParam_)
{
    returnValueParam.reset(returnValueParam_);
}

void FunctionSymbol::Write(Writer& writer)
{
    ContainerSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(kind));
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(qualifiers));
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(linkage));
    writer.GetBinaryStreamWriter().Write(index);
    writer.GetBinaryStreamWriter().Write(static_cast<uint8_t>(flags));
    if (returnType)
    {
        writer.GetBinaryStreamWriter().Write(returnType->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
    if (ReturnsClass())
    {
        writer.Write(ReturnValueParam());
    }
}

void FunctionSymbol::Read(Reader& reader)
{
    ContainerSymbol::Read(reader);
    kind = static_cast<FunctionKind>(reader.GetBinaryStreamReader().ReadByte());
    qualifiers = static_cast<FunctionQualifiers>(reader.GetBinaryStreamReader().ReadByte());
    linkage = static_cast<Linkage>(reader.GetBinaryStreamReader().ReadByte());
    index = reader.GetBinaryStreamReader().ReadInt();
    flags = static_cast<FunctionSymbolFlags>(reader.GetBinaryStreamReader().ReadByte());
    reader.GetBinaryStreamReader().ReadUuid(returnTypeId);
    if (ReturnsClass())
    {
        Symbol* returnValueParamSymbol = reader.ReadSymbol();
        if (returnValueParamSymbol->IsParameterSymbol())
        {
            returnValueParam.reset(static_cast<ParameterSymbol*>(returnValueParamSymbol));
        }
    }
}

void FunctionSymbol::Resolve(SymbolTable& symbolTable)
{
    ContainerSymbol::Resolve(symbolTable);
    if (returnTypeId != util::nil_uuid())
    {
        returnType = symbolTable.GetType(returnTypeId);
        if (ReturnsClass())
        {
            returnValueParam->Resolve(symbolTable);
        }
    }
}

void FunctionSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FunctionSymbol::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    if (IsTrivialDestructor()) return;
    int n = args.size();
    for (int i = 0; i < n; ++i)
    {
        BoundExpressionNode* arg = args[i];
        arg->Load(emitter, OperationFlags::none, sourcePos, context);
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
        otava::intermediate::Function* function = emitter.GetOrInsertFunction(IrName(context), functionType);
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
        if (returnType && !ReturnsClass())
        {
            returnIrType = returnType->IrType(emitter, sourcePos, context);
        }
        else
        {
            returnIrType = emitter.GetVoidType();
        }
        std::vector<otava::intermediate::Type*> paramIrTypes;
        for (const auto& param : MemFunParameters())
        {
            paramIrTypes.push_back(param->GetReferredType(context)->IrType(emitter, sourcePos, context));
        }
        if (ReturnsClass())
        {
            paramIrTypes.push_back(ReturnValueParam()->GetReferredType(context)->IrType(emitter, sourcePos, context));
        }
        type = emitter.MakeFunctionType(returnIrType, paramIrTypes);
        emitter.SetType(Id(), type);
    }
    return type;
}

std::string FunctionSymbol::IrName(Context* context) const
{
    if (linkage == Linkage::cpp_linkage)
    {
        std::string irName;
        SpecialFunctionKind specialFunctionKind = GetSpecialFunctionKind();
        if (specialFunctionKind != SpecialFunctionKind::none)
        {
            irName.append(SpecialFunctionKindPrefix(specialFunctionKind));
            ClassTypeSymbol* classType = ParentClassType();
            irName.append("_").append(util::ToUtf8(classType->Name()));
        }
        else
        {
            std::string operatorFunctionPrefix = GetOperatorFunctionPrefix(Name());
            if (!operatorFunctionPrefix.empty())
            {
                irName.append(operatorFunctionPrefix);
                ClassTypeSymbol* classType = ParentClassType();
                if (classType)
                {
                    irName.append("_").append(util::ToUtf8(classType->Name()));
                }
            }
            else
            {
                irName.append("function_" + util::ToUtf8(Name()));
            }
        }
        std::string fullName = util::ToUtf8(FullName());
        irName.append("_").append(util::GetSha1MessageDigest(fullName));
        if (IsSpecialization())
        {
            irName.append("_").append(context->GetBoundCompileUnit()->Id());
        }
        return irName;
    }
    else if (linkage == Linkage::c_linkage)
    {
        return util::ToUtf8(Name());
    }
    else
    {
        return util::ToUtf8(Name());
    }
}

void FunctionSymbol::AddLocalVariable(VariableSymbol* localVariable)
{
    if (std::find(localVariables.begin(), localVariables.end(), localVariable) != localVariables.end()) return;
    if (!localVariable->Parent())
    {
        localVariable->SetParent(this);
    }
    localVariables.push_back(localVariable);
}

void FunctionSymbol::RemoveLocalVariable(VariableSymbol* variable)
{
    auto it = std::find(localVariables.begin(), localVariables.end(), variable);
    if (it != localVariables.end())
    {
        localVariables.erase(it);
    }
}

std::u32string FunctionSymbol::NextTemporaryName()
{
    return U"@t" + util::ToUtf32(std::to_string(nextTemporaryId++));
}

VariableSymbol* FunctionSymbol::CreateTemporary(TypeSymbol* type)
{
    VariableSymbol* temporary = new VariableSymbol(NextTemporaryName());
    temporary->SetDeclaredType(type);
    AddLocalVariable(temporary);
    return temporary;
}

FunctionDefinitionSymbol::FunctionDefinitionSymbol(const std::u32string& name_) : FunctionSymbol(SymbolKind::functionDefinitionSymbol, name_), declaration(), declarationId()
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

std::string FunctionDefinitionSymbol::IrName(Context* context) const
{
    if (declaration)
    {
        return declaration->IrName(context);
    }
    else
    {
        return FunctionSymbol::IrName(context);
    }
}

bool FunctionLess::operator()(FunctionSymbol* left, FunctionSymbol* right) const
{
    if (int(left->GetFunctionKind()) < int(right->GetFunctionKind())) return true;
    if (int(left->GetFunctionKind()) > int(right->GetFunctionKind())) return false;
    return left->Name() < right->Name();
}

void InitFunction()
{
    OperatorFunctionMap::Instance().Init();
}

} // namespace otava::symbols
