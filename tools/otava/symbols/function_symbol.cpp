// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.function.symbol;

import otava.symbols.modules;
import otava.symbols.classes;
import otava.symbols.class_group.symbol;
import otava.symbols.declaration;
import otava.symbols.emitter;
import otava.symbols.exception;
import otava.symbols.alias.type.symbol;
import otava.symbols.type.symbol;
import otava.symbols.type_compare;
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
import otava.symbols.class_templates;
import otava.symbols.inline_functions;
import otava.symbols.function.group.symbol;
import otava.symbols.namespaces;
import otava.symbols.function.templates;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
import otava.symbols.type.resolver;
import otava.intermediate;
import otava.ast;
import util.sha1;
import util.unicode;

namespace otava::symbols {

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
    defaultValueNodeId(-1)
{
}

ParameterSymbol::ParameterSymbol(const std::u32string& name_, TypeSymbol* type_) : 
    Symbol(SymbolKind::parameterSymbol, name_), 
    type(type_), 
    typeId(util::nil_uuid()), 
    defaultValue(nullptr),
    defaultValueNodeId(-1)
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
        writer.GetBinaryStreamWriter().Write(defaultValue->InternalId());
        otava::ast::Writer astWriter(&writer.GetBinaryStreamWriter());
        astWriter.Write(defaultValue);
    }
}

void ParameterSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(typeId);
    bool hasDefaultValue = reader.GetBinaryStreamReader().ReadBool();
    if (hasDefaultValue)
    {
        defaultValueNodeId = reader.GetBinaryStreamReader().ReadLong();
        otava::ast::Reader astReader(&reader.GetBinaryStreamReader());
        astReader.SetNodeMap(reader.GetSymbolTable()->GetNodeMap());
        defaultValueNode.reset(astReader.ReadNode());
    }
}

void ParameterSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    Symbol::Resolve(symbolTable, context);
    type = symbolTable.GetType(typeId);
    if (!type)
    {
        std::string note;
        Module* requesterModule = context->GetRequesterModule();
        if (requesterModule)
        {
            note = ": note: requester module is " + requesterModule->Name();
        }
        std::cout << "ParameterSymbol::Resolve(): warning: type of parameter '" + util::ToUtf8(Name()) + "' not resolved" << note << "\n";
    }
    if (defaultValueNodeId != -1)
    {
        otava::ast::NodeMap* nodeMap = symbolTable.GetNodeMap();
        defaultValue = nodeMap->GetNode(defaultValueNodeId);
    }
}

void ParameterSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeSymbol* ParameterSymbol::GetReferredType(Context* context) const
{
    TypeSymbol* referredType = type->GetBaseType()->DirectType(context)->FinalType(soul::ast::SourcePos(), context);
    if (context->GetFlag(ContextFlags::resolveNestedTypes) && referredType->IsNestedTypeSymbol())
    {
        if (context->TemplateParameterMap())
        {
            if (referredType->Parent()->IsTemplateParameterSymbol())
            {
                TemplateParameterSymbol* templateParam = static_cast<TemplateParameterSymbol*>(referredType->Parent());
                auto it = context->TemplateParameterMap()->find(templateParam);
                if (it != context->TemplateParameterMap()->end())
                {
                    TypeSymbol* type = it->second;
                    Symbol* symbol = type->GetScope()->Lookup(referredType->Name(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, context->GetSourcePos(), context,
                        LookupFlags::none);
                    if (symbol && symbol->IsTypeSymbol())
                    {
                        referredType = static_cast<TypeSymbol*>(symbol);
                    }
                }
            }
        }
    }
    while (referredType->IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(referredType);
        referredType = aliasType->ReferredType();
        if (context->GetFlag(ContextFlags::resolveDependentTypes) && referredType->IsDependentTypeSymbol())
        {
            DependentTypeSymbol* dependentType = static_cast<DependentTypeSymbol*>(referredType);
            referredType = ResolveType(dependentType->GetNode(), DeclarationFlags::none, context);
        }
        else if (context->GetFlag(ContextFlags::resolveNestedTypes) && referredType->IsNestedTypeSymbol())
        {
            if (context->TemplateParameterMap())
            {
                if (referredType->Parent()->IsTemplateParameterSymbol())
                {
                    TemplateParameterSymbol* templateParam = static_cast<TemplateParameterSymbol*>(referredType->Parent());
                    auto it = context->TemplateParameterMap()->find(templateParam);
                    if (it != context->TemplateParameterMap()->end())
                    {
                        TypeSymbol* type = it->second;
                        Symbol* symbol = type->GetScope()->Lookup(referredType->Name(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, context->GetSourcePos(), context,
                            LookupFlags::none);
                        if (symbol && symbol->IsTypeSymbol())
                        {
                            referredType = static_cast<TypeSymbol*>(symbol);
                        }
                    }
                }
            }
        }
    }
    if (type->IsCompoundType())
    {
        referredType = context->GetSymbolTable()->MakeCompoundType(referredType, type->GetDerivations(), context);
    }
    if (context->GetFlag(ContextFlags::resolveDependentTypes) && referredType->IsDependentTypeSymbol())
    {
        DependentTypeSymbol* dependentType = static_cast<DependentTypeSymbol*>(referredType);
        TypeSymbol* type = ResolveType(dependentType->GetNode(), DeclarationFlags::none, context);
        referredType = type;
        while (referredType->IsAliasTypeSymbol())
        {
            AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(referredType);
            referredType = aliasType->ReferredType();
        }
    }
    return referredType;
}

ParameterSymbol* ParameterSymbol::Copy() const
{
    ParameterSymbol* copy = new ParameterSymbol(Name(), type);
    if (defaultValue)
    {
        copy->SetDefaultValue(defaultValue);
    }
    return copy;
}

bool ParameterSymbol::IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const
{ 
    if (visited.find(this) == visited.end())
    {
        visited.insert(this);
        return type->IsTemplateParameterInstantiation(context, visited);
    }
    return false;
}

soul::xml::Element* ParameterSymbol::ToXml() const
{
    soul::xml::Element* element = Symbol::ToXml();
    element->SetAttribute("type", util::ToUtf8(type->Name()));
    element->SetAttribute("typeId", util::ToString(type->Id()));
    return element;
}

FunctionSymbol::FunctionSymbol(const std::u32string& name_) : 
    ContainerSymbol(SymbolKind::functionSymbol, name_), 
    memFunParamsConstructed(false), 
    kind(FunctionKind::function),
    qualifiers(FunctionQualifiers::none),
    linkage(Linkage::cpp_linkage),
    index(0),
    flags(FunctionSymbolFlags::none),
    returnType(nullptr),
    returnTypeId(util::nil_uuid()),
    nextTemporaryId(0),
    vtabIndex(-1),
    destructor(nullptr),
    conversionKind(ConversionKind::implicitConversion),
    conversionParamType(nullptr), 
    conversionArgType(nullptr),
    conversionDistance(0),
    group(nullptr)
{
    GetScope()->SetKind(ScopeKind::functionScope);
}

FunctionSymbol::FunctionSymbol(SymbolKind kind_, const std::u32string& name_) :
    ContainerSymbol(kind_, name_), 
    memFunParamsConstructed(false), 
    kind(FunctionKind::function),
    qualifiers(FunctionQualifiers::none),
    linkage(Linkage::cpp_linkage),
    index(0),
    flags(FunctionSymbolFlags::none),
    returnType(nullptr),
    returnTypeId(util::nil_uuid()),
    nextTemporaryId(0),
    vtabIndex(-1),
    destructor(nullptr),
    conversionKind(ConversionKind::implicitConversion),
    conversionParamType(nullptr),
    conversionArgType(nullptr),
    conversionDistance(0),
    group(nullptr)
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

int FunctionSymbol::MemFunArity(Context* context) const
{
    return MemFunParameters(context).size();
}

int FunctionSymbol::MinArity() const
{
    int minArity = Arity();
    for (int i = parameters.size() - 1; i >= 0; --i)
    {
        ParameterSymbol* parameter = parameters[i];
        if (parameter->DefaultValue())
        {
            --minArity;
        }
        else
        {
            break;
        }
    }
    return minArity;
}

int FunctionSymbol::MinMemFunArity(Context* context) const
{
    int minMemFunArity = MemFunArity(context);
    for (int i = parameters.size() - 1; i >= 0; --i)
    {
        ParameterSymbol* parameter = parameters[i];
        if (parameter->DefaultValue())
        {
            --minMemFunArity;
        }
        else
        {
            break;
        }
    }
    return minMemFunArity;
}

bool FunctionSymbol::IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const
{
    if (visited.find(this) == visited.end())
    {
        visited.insert(this);
        for (ParameterSymbol* parameter : MemFunParameters(context))
        {
            if (parameter->IsTemplateParameterInstantiation(context, visited)) return true;
        }
        if (returnType)
        {
            if (returnType->IsTemplateParameterInstantiation(context, visited)) return true;
        }
        for (VariableSymbol* localVariable : localVariables)
        {
            if (localVariable->IsTemplateParameterInstantiation(context, visited)) return true;
        }
    }
    return false;
}

bool FunctionSymbol::IsVirtual() const
{
    if ((GetDeclarationFlags() & DeclarationFlags::virtualFlag) != DeclarationFlags::none) return true;
    if ((qualifiers & FunctionQualifiers::isOverride) != FunctionQualifiers::none) return true;
    if ((qualifiers & FunctionQualifiers::isFinal) != FunctionQualifiers::none) return true;
    return false;
}

bool FunctionSymbol::IsConst() const
{
    if ((qualifiers & FunctionQualifiers::isConst) != FunctionQualifiers::none) return true;
    return false;
}

bool FunctionSymbol::IsPure() const
{
    if ((qualifiers & FunctionQualifiers::isPure) != FunctionQualifiers::none) return true;
    return false;
}

void FunctionSymbol::SetVirtual()
{
    SetDeclarationFlags(GetDeclarationFlags() | DeclarationFlags::virtualFlag);
}

bool FunctionSymbol::IsOverride() const
{
    return (qualifiers & FunctionQualifiers::isOverride) != FunctionQualifiers::none;
}

bool FunctionSymbol::IsFinal() const
{
    return (qualifiers & FunctionQualifiers::isFinal) != FunctionQualifiers::none;
}

void FunctionSymbol::SetOverride()
{
    qualifiers = qualifiers | FunctionQualifiers::isOverride;
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

ParameterSymbol* FunctionSymbol::ThisParam(Context* context) const
{
    if (IsStatic()) return nullptr;
    if (!thisParam)
    {
        ClassTypeSymbol* classType = ParentClassType();
        if (classType)
        {
            if ((Qualifiers() & FunctionQualifiers::isConst) != FunctionQualifiers::none)
            {
                thisParam.reset(new ParameterSymbol(U"this", classType->AddConst(context)->AddPointer(context)));
            }
            else
            {
                thisParam.reset(new ParameterSymbol(U"this", classType->AddPointer(context)));
            }
        }
    }
    return thisParam.get();
}

const std::vector<ParameterSymbol*>& FunctionSymbol::MemFunParameters(Context* context) const
{
    if (memFunParamsConstructed) return memFunParameters;
    memFunParamsConstructed = true;
    ParameterSymbol* thisParam = ThisParam(context);
    if (thisParam)
    {
        memFunParameters.push_back(thisParam);
    }
    for (ParameterSymbol* parameter : parameters)
    {
        memFunParameters.push_back(parameter);
    }
    return memFunParameters;
}

bool FunctionSymbol::IsMemberFunction() const
{
    ClassTypeSymbol* classType = ParentClassType();
    if (classType && Parent() == classType)
    {
        return true;
    }
    else
    {
        return false;
    }
}

SpecialFunctionKind FunctionSymbol::GetSpecialFunctionKind(Context* context) const
{
    ClassTypeSymbol* classType = ParentClassType();
    TypeSymbol* classTemplate = nullptr;
    std::u32string className;
    if (classType)
    {
        className = classType->Name();
    }
    if (classType && classType->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* specialization = static_cast<ClassTemplateSpecializationSymbol*>(classType);
        classTemplate = specialization->ClassTemplate();
        className = classTemplate->Name();
    }
    if (classType)
    {
        const std::vector<ParameterSymbol*>& memFunParams = MemFunParameters(context);
        TypeSymbol* pointerType = classType->AddPointer(context);
        if (memFunParams.size() == 1 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == className) return SpecialFunctionKind::defaultCtor;
        if (memFunParams.size() == 1 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == U"~" + className) return SpecialFunctionKind::dtor;
        if (classTemplate)
        {
            if (memFunParams.size() == 1 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == U"~" + classTemplate->Name()) return SpecialFunctionKind::dtor;
        }
        TypeSymbol* constRefType = classType->AddConst(context)->AddLValueRef(context);
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == className &&
            TypesEqual(memFunParams[1]->GetType(), constRefType, context)) return SpecialFunctionKind::copyCtor;
        TypeSymbol* rvalueRefType = classType->AddRValueRef(context);
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == className &&
            TypesEqual(memFunParams[1]->GetType(), rvalueRefType, context)) return SpecialFunctionKind::moveCtor;
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == U"operator=" &&
            TypesEqual(memFunParams[1]->GetType(), constRefType, context)) return SpecialFunctionKind::copyAssignment;
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == U"operator=" &&
            TypesEqual(memFunParams[1]->GetType(), rvalueRefType, context)) return SpecialFunctionKind::moveAssignment;
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
        if (returnType->IsClassTypeSymbol() || returnType->IsForwardClassDeclarationSymbol())
        {
            SetReturnsClass();
            TypeSymbol* returnValueType = returnType->AddPointer(context);
            SetReturnValueParam(new ParameterSymbol(U"@return_value", returnValueType));
        }
    }
}

bool FunctionSymbol::IsTemplate() const
{
    return ParentTemplateDeclaration() != nullptr && !IsSpecialization();
}

int FunctionSymbol::TemplateArity() const
{
    TemplateDeclarationSymbol* templateDecl = ParentTemplateDeclaration();
    return templateDecl->Arity();
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

void FunctionSymbol::SetConversionParamType(TypeSymbol* conversionParamType_)
{
    conversionParamType = conversionParamType_;
}

void FunctionSymbol::SetConversionArgType(TypeSymbol* conversionArgType_)
{
    conversionArgType = conversionArgType_;
}

void FunctionSymbol::SetConversionKind(ConversionKind conversionKind_)
{
    conversionKind = conversionKind_;
}

void FunctionSymbol::SetConversionDistance(std::int32_t conversionDistance_)
{
    conversionDistance = conversionDistance_;
}

std::u32string FunctionSymbol::FullName() const
{
    ClassTypeSymbol* parentClassType = ParentClassType();
    std::u32string fullName;
    if (parentClassType)
    {
        fullName = parentClassType->FullName();
    }
    else if (ParentNamespace())
    {
        fullName = ParentNamespace()->FullName();
    }
    fullName.append(U"::").append(Name()).append(U"(");
    bool first = true;
    for (ParameterSymbol* parameter : parameters)
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
        ParameterSymbol* parameterSymbol = static_cast<ParameterSymbol*>(symbol);
        parameters.push_back(parameterSymbol);
    }
    else if (symbol->IsLocalVariableSymbol())
    {
        localVariables.push_back(static_cast<VariableSymbol*>(symbol));
    }
}

void FunctionSymbol::AddParameter(ParameterSymbol* parameter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    AddSymbol(parameter, sourcePos, context);
}

void FunctionSymbol::AddTemporaryParameter(TypeSymbol* paramType, int index)
{
    std::u32string paramName = U"p" + util::ToUtf32(std::to_string(index));
    std::unique_ptr<ParameterSymbol> temporaryParam(new ParameterSymbol(paramName, paramType));
    parameters.push_back(temporaryParam.get());
    temporaryParams.push_back(std::move(temporaryParam));
}

void FunctionSymbol::ClearTemporaryParameters()
{
    thisParam.reset();
    memFunParamsConstructed = false;
    memFunParameters.clear();
    parameters.clear();
    temporaryParams.clear();
    SetParent(nullptr);
}

void FunctionSymbol::SetReturnValueParam(ParameterSymbol* returnValueParam_)
{
    returnValueParam.reset(returnValueParam_);
}

void FunctionSymbol::Write(Writer& writer)
{
    ContainerSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(kind));
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(qualifiers));
    writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(linkage));
    writer.GetBinaryStreamWriter().Write(index);
    writer.GetBinaryStreamWriter().Write(static_cast<std::int32_t>(flags));
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
    writer.GetBinaryStreamWriter().Write(vtabIndex);
    if (IsConversion())
    {
        writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(GetConversionKind()));
        TypeSymbol* convParamType = ConversionParamType();
        if (convParamType)
        {
            writer.GetBinaryStreamWriter().Write(convParamType->Id());
        }
        else
        {
            writer.GetBinaryStreamWriter().Write(util::nil_uuid());
        }
        TypeSymbol* convArgType = ConversionArgType();
        if (convArgType)
        {
            writer.GetBinaryStreamWriter().Write(convArgType->Id());
        }
        else
        {
            writer.GetBinaryStreamWriter().Write(util::nil_uuid());
        }
        writer.GetBinaryStreamWriter().Write(ConversionDistance());
    }
    if (GetFlag(FunctionSymbolFlags::fixedIrName))
    {
        writer.GetBinaryStreamWriter().Write(fixedIrName);
    }
    std::uint32_t ns = specialization.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(ns);
    for (std::uint32_t i = 0; i < ns; ++i)
    {
        writer.GetBinaryStreamWriter().Write(specialization[i]->Id());
    }
}

void FunctionSymbol::Read(Reader& reader)
{
    ContainerSymbol::Read(reader);
    kind = static_cast<FunctionKind>(reader.GetBinaryStreamReader().ReadByte());
    qualifiers = static_cast<FunctionQualifiers>(reader.GetBinaryStreamReader().ReadByte());
    linkage = static_cast<Linkage>(reader.GetBinaryStreamReader().ReadByte());
    index = reader.GetBinaryStreamReader().ReadInt();
    flags = static_cast<FunctionSymbolFlags>(reader.GetBinaryStreamReader().ReadInt());
    reader.GetBinaryStreamReader().ReadUuid(returnTypeId);
    if (ReturnsClass())
    {
        Symbol* returnValueParamSymbol = reader.ReadSymbol();
        if (returnValueParamSymbol->IsParameterSymbol())
        {
            returnValueParam.reset(static_cast<ParameterSymbol*>(returnValueParamSymbol));
        }
    }
    vtabIndex = reader.GetBinaryStreamReader().ReadInt();
    if (IsConversion())
    {
        conversionKind = static_cast<ConversionKind>(reader.GetBinaryStreamReader().ReadByte());
        reader.GetBinaryStreamReader().ReadUuid(conversionParamTypeId);
        reader.GetBinaryStreamReader().ReadUuid(conversionArgTypeId);
        conversionDistance = reader.GetBinaryStreamReader().ReadInt();
    }
    if (GetFlag(FunctionSymbolFlags::fixedIrName))
    {
        fixedIrName = reader.GetBinaryStreamReader().ReadUtf8String();
    }
    std::uint32_t ns = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < ns; ++i)
    {
        util::uuid sid;
        reader.GetBinaryStreamReader().ReadUuid(sid);
        specializationIds.push_back(sid);
    }
}

void FunctionSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    ContainerSymbol::Resolve(symbolTable, context);
    if (returnTypeId != util::nil_uuid())
    {
        returnType = symbolTable.GetType(returnTypeId);
        if (!returnType)
        {
            std::string note;
            Module* requesterModule = context->GetRequesterModule();
            if (requesterModule)
            {
                note = ": note: requester module is " + requesterModule->Name();
            }
            std::cout << "FunctionSymbol::Resolve(): warning: return type of '" + util::ToUtf8(Name()) + "' not resolved" << note << "\n";
        }
        if (ReturnsClass())
        {
            returnValueParam->Resolve(symbolTable, context);
        }
    }
    if (IsConversion())
    {
        if (conversionParamTypeId != util::nil_uuid())
        {
            conversionParamType = symbolTable.GetType(conversionParamTypeId);
            if (!conversionParamType)
            {
                std::string note;
                Module* requesterModule = context->GetRequesterModule();
                if (requesterModule)
                {
                    note = ": note: requester module is " + requesterModule->Name();
                }
                std::cout << "FunctionSymbol::Resolve(): warning: conversion parameter type of '" + util::ToUtf8(Name()) + "' not resolved" << note << "\n";
            }
        }
        if (conversionArgTypeId != util::nil_uuid())
        {
            conversionArgType = symbolTable.GetType(conversionArgTypeId);
            if (!conversionArgType)
            {
                std::string note;
                Module* requesterModule = context->GetRequesterModule();
                if (requesterModule)
                {
                    note = ": note: requester module is " + requesterModule->Name();
                }
                std::cout << "FunctionSymbol::Resolve(): warning: conversion argument type of '" + util::ToUtf8(Name()) + "' not resolved" << note << "\n";
            }
        }
    }
    specialization.clear();
    for (const auto& id : specializationIds)
    {
        TypeSymbol* type = symbolTable.GetType(id);
        if (type)
        {
            specialization.push_back(type);
        }
        else
        {
            std::string note;
            Module* requesterModule = context->GetRequesterModule();
            if (requesterModule)
            {
                note = ": note: requester module is " + requesterModule->Name();
            }
            std::cout << "FunctionSymbol::Resolve(): warning: specialization type of '" + util::ToUtf8(Name()) + "' not resolved" << note << "\n";
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
    if ((flags & OperationFlags::virtualCall) != OperationFlags::none)
    {
        GenerateVirtualFunctionCall(emitter, args, sourcePos, context);
        return;
    }
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
        std::string irName = IrName(context);
        otava::intermediate::Function* function = emitter.GetOrInsertFunction(irName, functionType);
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

void FunctionSymbol::GenerateVirtualFunctionCall(Emitter& emitter, std::vector<BoundExpressionNode*>& args, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context)
{
    TypeSymbol* thisPtrBaseType = args[0]->GetType()->GetBaseType();
    otava::intermediate::Type* irType = IrType(emitter, sourcePos, context);
    otava::intermediate::FunctionType* functionType = nullptr;
    if (irType->IsFunctionType())
    {
        functionType = static_cast<otava::intermediate::FunctionType*>(irType);
    }
    else
    {
        ThrowException("function type expected", sourcePos, context);
    }
    ClassTypeSymbol* classType = nullptr;
    if (thisPtrBaseType->IsClassTypeSymbol())
    {
        classType = static_cast<ClassTypeSymbol*>(thisPtrBaseType);
    }
    else
    {
        ThrowException("class type expected", sourcePos, context);
    }
    std::vector<ClassTypeSymbol*> vptrHolderClasses = classType->VPtrHolderClasses();
    if (vptrHolderClasses.empty())
    {
        ThrowException("no vptr holder classes for the class '" + util::ToUtf8(classType->FullName()) + "'", sourcePos, context);
    }
    ClassTypeSymbol* vptrHolderClass = vptrHolderClasses.front();
    int na = args.size();
    otava::intermediate::Value* callee = nullptr;
    for (int i = 0; i < na; ++i)
    {
        args[i]->Load(emitter, OperationFlags::none, sourcePos, context);
        if (i == 0)
        {
            otava::intermediate::Value* thisPtr = emitter.Stack().Pop();
            if (classType != vptrHolderClass)
            {
                thisPtr = emitter.EmitBitcast(thisPtr, vptrHolderClass->AddPointer(context)->IrType(emitter, sourcePos, context));
            }
            otava::intermediate::Value* vptrPtr = emitter.EmitElemAddr(thisPtr, emitter.EmitLong(vptrHolderClass->VPtrIndex()));
            otava::intermediate::Value* voidVPtr = emitter.EmitLoad(vptrPtr);
            otava::intermediate::Value* vptr = emitter.EmitBitcast(voidVPtr, classType->VPtrType(emitter));
            otava::intermediate::Value* objectDeltaPtrElem = emitter.EmitElemAddr(thisPtr, emitter.EmitLong(vptrHolderClass->DeltaIndex()));
            otava::intermediate::Type* deltaPtrType = emitter.MakePtrType(emitter.GetLongType());
            otava::intermediate::Value* objectDeltaPtr = emitter.EmitBitcast(objectDeltaPtrElem, deltaPtrType);
            otava::intermediate::Value* objectDelta = emitter.EmitLoad(objectDeltaPtr);
            otava::intermediate::Value* adjustedObjectPtr = emitter.EmitClassPtrConversion(thisPtr, objectDelta, thisPtr->GetType(), false);
            if (VTabIndex() == -1)
            {
                ThrowException("invalid vtab index", sourcePos, context);
            }
            otava::intermediate::Value* functionPtrPtr = emitter.EmitElemAddr(vptr, emitter.EmitLong(vtabClassIdElementCount + 2 * VTabIndex()));
            otava::intermediate::Value* voidFunctionPtr = emitter.EmitLoad(functionPtrPtr);
            callee = emitter.EmitBitcast(voidFunctionPtr, emitter.MakePtrType(functionType));
            otava::intermediate::Value* deltaPtrElem = emitter.EmitElemAddr(vptr, emitter.EmitLong(vtabClassIdElementCount + 2 * VTabIndex() + 1));
            otava::intermediate::Value* deltaPtr = emitter.EmitBitcast(deltaPtrElem, deltaPtrType);
            otava::intermediate::Value* delta = emitter.EmitLoad(deltaPtr);
            otava::intermediate::Value* adjustedThisPtr = emitter.EmitClassPtrConversion(adjustedObjectPtr, delta, thisPtr->GetType(), false);
            emitter.Stack().Push(adjustedThisPtr);
        }
    }
    std::vector<otava::intermediate::Value*> arguments;
    arguments.resize(na);
    for (int i = 0; i < na; ++i)
    {
        otava::intermediate::Value* arg = emitter.Stack().Pop();
        arguments[na - i - 1] = arg;
    }
    if (!functionType->ReturnType() || functionType->ReturnType()->IsVoidType())
    {
        emitter.EmitCall(callee, arguments);
    }
    else
    {
        emitter.Stack().Push(emitter.EmitCall(callee, arguments));
    }
    context->GetBoundCompileUnit()->AddBoundNodeForClass(classType, sourcePos, context);
}

FunctionTypeSymbol* FunctionSymbol::GetFunctionType(otava::symbols::Context* context)
{
    FunctionTypeSymbol* functionType = context->GetSymbolTable()->MakeFunctionTypeSymbol(this);
    return functionType;
}

otava::intermediate::Type* FunctionSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) const
{
    util::uuid irId = IrId(context);
    otava::intermediate::Type* type = emitter.GetType(irId);
    if (!type)
    {
        otava::intermediate::Type* returnIrType = nullptr;
        if (returnType && !ReturnsClass())
        {
            returnIrType = returnType->DirectType(context)->FinalType(sourcePos, context)->IrType(emitter, sourcePos, context);
        }
        else
        {
            returnIrType = emitter.GetVoidType();
        }
        std::vector<otava::intermediate::Type*> paramIrTypes;
        for (ParameterSymbol* param : MemFunParameters(context))
        {
            otava::intermediate::Type* paramIrType = nullptr;
            TypeSymbol* paramType = param->GetReferredType(context);
            if (paramType->IsClassTypeSymbol())
            {
                paramIrType = paramType->AddConst(context)->AddLValueRef(context)->IrType(emitter, sourcePos, context);
            }
            else
            {
                paramIrType = paramType->IrType(emitter, sourcePos, context);
            }
            paramIrTypes.push_back(paramIrType);
        }
        if (ReturnsClass())
        {
            paramIrTypes.push_back(ReturnValueParam()->GetReferredType(context)->IrType(emitter, sourcePos, context));
        }
        type = emitter.MakeFunctionType(returnIrType, paramIrTypes);
        emitter.SetType(irId, type);
    }
    return type;
}

void FunctionSymbol::SetFixedIrName(const std::string& fixedIrName_)
{
    fixedIrName = fixedIrName_;
    SetFlag(FunctionSymbolFlags::fixedIrName);
}

void FunctionSymbol::SetCompileUnitId(const std::string& compileUnitId_)
{
    compileUnitId = compileUnitId_;
}

std::string FunctionSymbol::IrName(Context* context) const
{
    if (GetFlag(FunctionSymbolFlags::fixedIrName) && !fixedIrName.empty())
    {
        return fixedIrName;
    }
    if (linkage == Linkage::cpp_linkage)
    {
        std::string irName;
        SpecialFunctionKind specialFunctionKind = GetSpecialFunctionKind(context);
        std::string digestSource;
        if (specialFunctionKind != SpecialFunctionKind::none)
        {
            irName.append(SpecialFunctionKindPrefix(specialFunctionKind));
            ClassTypeSymbol* classType = ParentClassType();
            digestSource.append(classType->IrName(context));
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
                    digestSource.append(classType->IrName(context));
                    irName.append("_").append(util::ToUtf8(classType->Group()->Name()));
                }
            }
            else
            {
                if (kind == FunctionKind::constructor && ParentClassType())
                {
                    ClassTypeSymbol* classType = ParentClassType();
                    irName.append("ctor_").append(util::ToUtf8(classType->Group()->Name()));
                    digestSource.append(classType->IrName(context));
                }
                else if (kind == FunctionKind::destructor && ParentClassType())
                {
                    ClassTypeSymbol* classType = ParentClassType();
                    irName.append("dtor_").append(util::ToUtf8(classType->Group()->Name()));
                    digestSource.append(classType->IrName(context));
                }
                else if (ParentClassType())
                {
                    ClassTypeSymbol* classType = ParentClassType();
                    irName.append("mfn_").append(util::ToUtf8(classType->Group()->Name())).append("_").append(util::ToUtf8(Name()));
                }
                else
                {
                    irName.append("fn_" + util::ToUtf8(Name()));
                }
            }
        }
        std::string fullName = util::ToUtf8(FullName());
        if (!specialization.empty())
        {
            int n = specialization.size();
            for (int i = 0; i < n; ++i)
            {
                digestSource.append(".").append(util::ToUtf8(specialization[i]->FullName()));
            }
        }
        digestSource.append(fullName);
        digestSource.append(compileUnitId);
        if (returnType)
        {
            digestSource.append(".").append(util::ToUtf8(returnType->FullName()));
        }
        irName.append("_").append(util::GetSha1MessageDigest(digestSource));
        if (GetFlag(FunctionSymbolFlags::fixedIrName))
        {
            fixedIrName = irName;
            return fixedIrName;
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

void FunctionSymbol::SetSpecialization(const std::vector<TypeSymbol*>& specialization_)
{
    specialization = specialization_;
}

bool FunctionSymbol::IsExplicitSpecializationDefinitionSymbol() const
{
    if (!IsFunctionDefinitionSymbol()) return false;
    TemplateDeclarationSymbol* templateDeclaration = ParentTemplateDeclaration();
    if (!templateDeclaration) return false;
    if (templateDeclaration->Arity() != 0) return false;
    return true;
}

bool FunctionSymbol::IsExplicitSpecializationDeclaration() const
{
    if (IsFunctionDefinitionSymbol()) return false;
    TemplateDeclarationSymbol* templateDeclaration = ParentTemplateDeclaration();
    if (!templateDeclaration) return false;
    if (templateDeclaration->Arity() != 0) return false;
    return true;
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

bool FunctionSymbol::IsStatic() const
{
    return (GetDeclarationFlags() & DeclarationFlags::staticFlag) != DeclarationFlags::none;
}

bool FunctionSymbol::IsExplicit() const
{
    return (GetDeclarationFlags() & DeclarationFlags::explicitFlag) != DeclarationFlags::none;
}

bool FunctionSymbol::IsDestructor() const
{
    return GroupName() == U"@destructor";
}

void FunctionSymbol::CheckGenerateClassCopyCtor(const soul::ast::SourcePos& sourcePos, Context* context)
{
    for (ParameterSymbol* parameter : MemFunParameters(context))
    {
        TypeSymbol* paramType = parameter->GetReferredType(context);
        if (paramType->IsClassTypeSymbol())
        {
            ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(paramType);
            classType->GenerateCopyCtor(sourcePos, context);
        }
    }
}

void FunctionSymbol::AddDefinitionToGroup(Context* context)
{
}

soul::xml::Element* FunctionSymbol::ToXml() const
{
    soul::xml::Element* element = ContainerSymbol::ToXml();
    element->SetAttribute("functionKind", FunctionKindStr(kind));
    if (returnType)
    {
        element->SetAttribute("returnType", util::ToUtf8(returnType->Name()));
        element->SetAttribute("returnTypeId", util::ToString(returnType->Id()));
    }
    return element;
}

FunctionDefinitionSymbol::FunctionDefinitionSymbol(const std::u32string& name_) : 
    FunctionSymbol(SymbolKind::functionDefinitionSymbol, name_), 
    declaration(), 
    declarationId(),
    defIndex(-1)
{
}

FunctionDefinitionSymbol::FunctionDefinitionSymbol(SymbolKind kind_, const std::u32string& name_) :
    FunctionSymbol(kind_, name_),
    declaration(),
    declarationId(),
    defIndex(-1)
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
    writer.GetBinaryStreamWriter().Write(defIndex);
    writer.GetBinaryStreamWriter().Write(irName);
}

void FunctionDefinitionSymbol::Read(Reader& reader)
{
    FunctionSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(declarationId);
    defIndex = reader.GetBinaryStreamReader().ReadInt();
    irName = reader.GetBinaryStreamReader().ReadUtf8String();
}

void FunctionDefinitionSymbol::Accept(Visitor& visitor) 
{
    visitor.Visit(*this);
}

void FunctionDefinitionSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    FunctionSymbol::Resolve(symbolTable, context);
    if (declarationId != util::nil_uuid())
    {
        declaration = symbolTable.GetFunction(declarationId);
    }
}

std::string FunctionDefinitionSymbol::IrName(Context* context) const
{
    if (declaration)
    {
        if (irName.empty())
        {
            irName = declaration->IrName(context);
        }
        return irName;
    }
    else
    {
        if (irName.empty())
        {
            irName = FunctionSymbol::IrName(context);
        }
        return irName;
    }
}

otava::intermediate::Type* FunctionDefinitionSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) const
{
    if (declaration)
    {
        return declaration->IrType(emitter, sourcePos, context);
    }
    else
    {
        return FunctionSymbol::IrType(emitter, sourcePos, context);
    }
}

void FunctionDefinitionSymbol::SetReturnType(TypeSymbol* returnType_, Context* context)
{
    if (declaration)
    {
        declaration->SetReturnType(returnType_, context);
    }
    FunctionSymbol::SetReturnType(returnType_, context);
}

FunctionKind FunctionDefinitionSymbol::GetFunctionKind() const
{
    if (declaration)
    {
        return declaration->GetFunctionKind();
    }
    else
    {
        return FunctionSymbol::GetFunctionKind();
    }
}

bool FunctionDefinitionSymbol::IsVirtual() const
{
    if (declaration)
    {
        return declaration->IsVirtual();
    }
    else
    {
        return FunctionSymbol::IsVirtual();
    }
}

bool FunctionDefinitionSymbol::IsConst() const
{
    if (declaration)
    {
        return declaration->IsConst();
    }
    else
    {
        return FunctionSymbol::IsConst();
    }
}

bool FunctionDefinitionSymbol::IsPure() const
{
    if (declaration)
    {
        return declaration->IsPure();
    }
    else
    {
        return FunctionSymbol::IsPure();
    }
}

bool FunctionDefinitionSymbol::IsOverride() const
{
    if (declaration)
    {
        return declaration->IsOverride();
    }
    else
    {
        return FunctionSymbol::IsOverride();
    }
}

bool FunctionDefinitionSymbol::IsFinal() const
{
    if (declaration)
    {
        return declaration->IsFinal();
    }
    else
    {
        return FunctionSymbol::IsFinal();
    }
}

std::int32_t FunctionDefinitionSymbol::VTabIndex() const
{
    if (declaration)
    {
        return declaration->VTabIndex();
    }
    else
    {
        return FunctionSymbol::VTabIndex();
    }
}

bool FunctionDefinitionSymbol::IsStatic() const
{
    if (declaration)
    {
        return declaration->IsStatic();
    }
    else
    {
        return FunctionSymbol::IsStatic();
    }
}

bool FunctionDefinitionSymbol::IsExplicit() const
{
    if (declaration)
    {
        return declaration->IsExplicit();
    }
    else
    {
        return FunctionSymbol::IsExplicit();
    }
}

TypeSymbol* FunctionDefinitionSymbol::ConversionParamType() const
{
    if (declaration)
    {
        return declaration->ConversionParamType();
    }
    else
    {
        return FunctionSymbol::ConversionParamType();
    }
}

TypeSymbol* FunctionDefinitionSymbol::ConversionArgType() const
{
    if (declaration)
    {
        return declaration->ConversionArgType();
    }
    else
    {
        return FunctionSymbol::ConversionArgType();
    }
}

std::int32_t FunctionDefinitionSymbol::ConversionDistance() const
{
    if (declaration)
    {
        return declaration->ConversionDistance();
    }
    else
    {
        return FunctionSymbol::ConversionDistance();
    }
}

void FunctionDefinitionSymbol::AddDefinitionToGroup(Context* context)
{
    Group()->AddFunctionDefinition(this, context);
}

bool FunctionDefinitionSymbol::IsMemberFunction() const
{
    if (declaration)
    {
        return declaration->IsMemberFunction();
    }
    return false;
}

soul::xml::Element* FunctionDefinitionSymbol::ToXml() const
{
    soul::xml::Element* element = FunctionSymbol::ToXml();
    element->SetAttribute("defIndex", std::to_string(defIndex));
    return element;
}

ExplicitlyInstantiatedFunctionDefinitionSymbol::ExplicitlyInstantiatedFunctionDefinitionSymbol(FunctionDefinitionSymbol* functionDefinitionSymbol_,
    const soul::ast::SourcePos& sourcePos, Context* context) : 
    FunctionDefinitionSymbol(SymbolKind::explicitlyInstantiatedFunctionDefinitionSymbol, functionDefinitionSymbol_->Name()),
    functionDefinitionSymbol(functionDefinitionSymbol_),
    irName(functionDefinitionSymbol->IrName(context))
{
    SetDeclarationFlags(functionDefinitionSymbol->GetDeclarationFlags());
    SetVTabIndex(functionDefinitionSymbol->VTabIndex());
    SetDefIndex(functionDefinitionSymbol->DefIndex());
    for (ParameterSymbol* parameter : functionDefinitionSymbol->Parameters())
    {
        AddParameter(parameter->Copy(), sourcePos, context);
    }
    if (functionDefinitionSymbol->ReturnType())
    {
        SetReturnType(functionDefinitionSymbol->ReturnType(), context);
    }
}

ExplicitlyInstantiatedFunctionDefinitionSymbol::ExplicitlyInstantiatedFunctionDefinitionSymbol(const std::u32string& name_) : 
    FunctionDefinitionSymbol(SymbolKind::explicitlyInstantiatedFunctionDefinitionSymbol, name_), functionDefinitionSymbol(nullptr)
{
}

void ExplicitlyInstantiatedFunctionDefinitionSymbol::Write(Writer& writer)
{
    FunctionDefinitionSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(irName);
    if (!functionDefinitionSymbol->IsGenerated())
    {
        writer.GetBinaryStreamWriter().Write(functionDefinitionSymbol->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
}

void ExplicitlyInstantiatedFunctionDefinitionSymbol::Read(Reader& reader)
{
    FunctionDefinitionSymbol::Read(reader);
    irName = reader.GetBinaryStreamReader().ReadUtf8String();
    reader.GetBinaryStreamReader().ReadUuid(functionDefinitionId);
}

void ExplicitlyInstantiatedFunctionDefinitionSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    FunctionDefinitionSymbol::Resolve(symbolTable, context);
    if (!functionDefinitionId.is_nil())
    {
        functionDefinitionSymbol = symbolTable.GetFunctionDefinition(functionDefinitionId);
    }
}

otava::intermediate::Type* ExplicitlyInstantiatedFunctionDefinitionSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context) const
{
    if (functionDefinitionSymbol)
    {
        return functionDefinitionSymbol->IrType(emitter, sourcePos, context);
    }
    else
    {
        return FunctionDefinitionSymbol::IrType(emitter, sourcePos, context);
    }
}

bool FunctionLess::operator()(FunctionSymbol* left, FunctionSymbol* right) const
{
    if (int(left->GetFunctionKind()) < int(right->GetFunctionKind())) return true;
    if (int(left->GetFunctionKind()) > int(right->GetFunctionKind())) return false;
    return left->Name() < right->Name();
}

bool FunctionMatches(FunctionSymbol* left, FunctionSymbol* right, Context* context)
{
    if (left->GroupName() != right->GroupName()) return false;
    if (left->IsConst() != right->IsConst()) return false;
    if (left->IsTemplate() != right->IsTemplate()) return false;
    if (left->IsTemplate())
    {
        TemplateDeclarationSymbol* leftTemplateDeclaration = left->ParentTemplateDeclaration();
        TemplateDeclarationSymbol* rightTemplateDeclaration = right->ParentTemplateDeclaration();
        if (leftTemplateDeclaration->Arity() != rightTemplateDeclaration->Arity()) return false;
        for (int i = 0; i < leftTemplateDeclaration->Arity(); ++i)
        {
            if (!TypesEqual(leftTemplateDeclaration->TemplateParameters()[i], rightTemplateDeclaration->TemplateParameters()[i], context)) return false;
        }
    }
    int leftsn = left->Specialization().size();
    int rightsn = right->Specialization().size();
    if (leftsn != rightsn) return false;
    for (int i = 0; i < leftsn; ++i)
    {
        if (!TypesEqual(left->Specialization()[i], right->Specialization()[i], context)) return false;
    }
    if (left->MemFunArity(context) != right->MemFunArity(context)) return false;
    for (int i = 0; i < left->MemFunArity(context); ++i)
    {
        if (!TypesEqual(left->MemFunParameters(context)[i]->GetType(), right->MemFunParameters(context)[i]->GetType(), context)) return false;
    }
    return true;
}

void InitFunction()
{
    OperatorFunctionMap::Instance().Init();
}

} // namespace otava::symbols
