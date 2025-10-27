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
import otava.symbols.error;
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

std::expected<bool, int> ParameterSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(type->Id());
    if (!rv) return rv;
    bool hasDefaultValue = defaultValue != nullptr;
    rv = writer.GetBinaryStreamWriter().Write(hasDefaultValue);
    if (!rv) return rv;
    if (hasDefaultValue)
    {
        rv = writer.GetBinaryStreamWriter().Write(defaultValue->InternalId());
        if (!rv) return rv;
        otava::ast::Writer astWriter(&writer.GetBinaryStreamWriter());
        rv = astWriter.Write(defaultValue);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ParameterSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(typeId);
    if (!rv) return rv;
    std::expected<bool, int> brv = reader.GetBinaryStreamReader().ReadBool();
    if (!brv) return brv;
    bool hasDefaultValue = *brv;
    if (hasDefaultValue)
    {
        std::expected<std::int64_t, int> lrv = reader.GetBinaryStreamReader().ReadLong();
        if (!lrv) return std::unexpected<int>(lrv.error());
        defaultValueNodeId = *lrv;
        otava::ast::Reader astReader(&reader.GetBinaryStreamReader());
        astReader.SetNodeMap(reader.GetSymbolTable()->GetNodeMap());
        std::expected<otava::ast::Node*, int> nrv = astReader.ReadNode();
        if (!nrv) return std::unexpected<int>(nrv.error());
        defaultValueNode.reset(*nrv);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ParameterSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    type = symbolTable.GetType(typeId);
    if (!type)
    {
        std::expected<std::string, int> name = util::ToUtf8(Name());
        if (!name) return std::unexpected<int>(name.error());
        std::cout << "ParameterSymbol::Resolve(): warning: type of parameter '" + *name + "' not resolved" << "\n";
    }
    if (defaultValueNodeId != -1)
    {
        otava::ast::NodeMap* nodeMap = symbolTable.GetNodeMap();
        std::expected<otava::ast::Node*, int> nrv = nodeMap->GetNode(defaultValueNodeId);
        if (!nrv) return std::unexpected<int>(nrv.error());
        defaultValue = *nrv;
    }
    return std::expected<bool, int>(true);
}

void ParameterSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<TypeSymbol*, int> ParameterSymbol::GetReferredType(Context* context) const
{
    std::expected<TypeSymbol*, int> rv = type->GetBaseType()->FinalType(soul::ast::SourcePos(), context);
    if (!rv) return rv;
    TypeSymbol* referredType = *rv;
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
                    std::expected<Symbol*, int> lrv = type->GetScope()->Lookup(referredType->Name(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, 
                        context->GetSourcePos(), context, LookupFlags::none);
                    if (!lrv) return std::unexpected<int>(lrv.error());
                    Symbol* symbol = *lrv;
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
            std::expected<TypeSymbol*, int> rv = ResolveType(dependentType->GetNode(), DeclarationFlags::none, context);
            if (!rv) return std::unexpected<int>(rv.error());
            referredType = *rv;
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
                        std::expected<Symbol*, int> lrv = type->GetScope()->Lookup(referredType->Name(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, 
                            context->GetSourcePos(), context, LookupFlags::none);
                        if (!lrv) return std::unexpected<int>(lrv.error());
                        Symbol* symbol = *lrv;
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
        std::expected<TypeSymbol*, int> c = context->GetSymbolTable()->MakeCompoundType(referredType, type->GetDerivations());
        if (!c) return c;
        referredType = *c;
    }
    if (context->GetFlag(ContextFlags::resolveDependentTypes) && referredType->IsDependentTypeSymbol())
    {
        DependentTypeSymbol* dependentType = static_cast<DependentTypeSymbol*>(referredType);
        std::expected<TypeSymbol*, int> rv = ResolveType(dependentType->GetNode(), DeclarationFlags::none, context);
        if (!rv) return std::unexpected<int>(rv.error());
        TypeSymbol* type = *rv;
        referredType = type;
        while (referredType->IsAliasTypeSymbol())
        {
            AliasTypeSymbol* aliasType = static_cast<AliasTypeSymbol*>(referredType);
            referredType = aliasType->ReferredType();
        }
    }
    return std::expected<TypeSymbol*, int>(referredType);
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

std::expected<soul::xml::Element*, int> ParameterSymbol::ToXml() const
{
    std::expected<soul::xml::Element*, int> rv = Symbol::ToXml();
    if (!rv) return rv;
    soul::xml::Element* element = *rv;
    std::expected<std::string, int> name = util::ToUtf8(type->Name());
    if (!name) return std::unexpected<int>(name.error());
    element->SetAttribute("type", *name);
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
    group(nullptr),
    error(0)
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
    group(nullptr),
    error(0)
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

std::expected<ParameterSymbol*, int> FunctionSymbol::ThisParam(Context* context) const
{
    if (IsStatic()) return std::expected<ParameterSymbol*, int>(nullptr);
    if (!thisParam)
    {
        ClassTypeSymbol* classType = ParentClassType();
        if (classType)
        {
            if ((Qualifiers() & FunctionQualifiers::isConst) != FunctionQualifiers::none)
            {
                std::expected<TypeSymbol*, int> pt = classType->AddConst(context);
                if (!pt) return std::unexpected<int>(pt.error());
                TypeSymbol* type = *pt;
                pt = type->AddPointer(context);
                if (!pt) return std::unexpected<int>(pt.error());
                type = *pt;
                thisParam.reset(new ParameterSymbol(U"this", type));
            }
            else
            {
                std::expected<TypeSymbol*, int> pt = classType->AddPointer(context);
                if (!pt) return std::unexpected<int>(pt.error());
                TypeSymbol* type = *pt;
                thisParam.reset(new ParameterSymbol(U"this", type));
            }
        }
    }
    return std::expected<ParameterSymbol*, int>(thisParam.get());
}

const std::vector<ParameterSymbol*>& FunctionSymbol::MemFunParameters(Context* context) const
{
    if (memFunParamsConstructed) return memFunParameters;
    memFunParamsConstructed = true;
    std::expected<ParameterSymbol*, int> tp = ThisParam(context);
    if (!tp)
    {
        SetError(tp.error());
        return memFunParameters;
    }
    ParameterSymbol* thisParam = *tp;
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

std::expected<SpecialFunctionKind, int> FunctionSymbol::GetSpecialFunctionKind(Context* context) const
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
        if (!Valid()) return std::unexpected<int>(GetError());
        std::expected<TypeSymbol*, int> pt = classType->AddPointer(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* pointerType = *pt;
        if (memFunParams.size() == 1 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == className) return SpecialFunctionKind::defaultCtor;
        if (memFunParams.size() == 1 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == U"~" + className) return SpecialFunctionKind::dtor;
        if (classTemplate)
        {
            if (memFunParams.size() == 1 && 
                TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == U"~" + classTemplate->Name()) return SpecialFunctionKind::dtor;
        }
        pt = classType->AddConst(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* type = *pt;
        pt = type->AddLValueRef(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* constRefType = *pt;
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == className &&
            TypesEqual(memFunParams[1]->GetType(), constRefType, context)) return std::expected<SpecialFunctionKind, int>(SpecialFunctionKind::copyCtor);
        pt = classType->AddRValueRef(context);
        if (!pt) return std::unexpected<int>(pt.error());
        TypeSymbol* rvalueRefType = *pt;
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == className &&
            TypesEqual(memFunParams[1]->GetType(), rvalueRefType, context)) return std::expected<SpecialFunctionKind, int>(SpecialFunctionKind::moveCtor);
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == U"operator=" &&
            TypesEqual(memFunParams[1]->GetType(), constRefType, context)) return std::expected<SpecialFunctionKind, int>(SpecialFunctionKind::copyAssignment);
        if (memFunParams.size() == 2 && TypesEqual(memFunParams[0]->GetType(), pointerType, context) && Name() == U"operator=" &&
            TypesEqual(memFunParams[1]->GetType(), rvalueRefType, context)) return std::expected<SpecialFunctionKind, int>(SpecialFunctionKind::moveAssignment);
    }
    return std::expected<SpecialFunctionKind, int>(SpecialFunctionKind::none);
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

std::expected<bool, int> FunctionSymbol::SetReturnType(TypeSymbol* returnType_, Context* context)
{
    returnType = returnType_;
    if (returnType)
    {
        if (returnType->IsClassTypeSymbol() || returnType->IsForwardClassDeclarationSymbol())
        {
            SetReturnsClass();
            std::expected<TypeSymbol*, int> pt = returnType->AddPointer(context);
            if (!pt) return std::unexpected<int>(pt.error());
            TypeSymbol* returnValueType = *pt;
            SetReturnValueParam(new ParameterSymbol(U"@return_value", returnValueType));
        }
    }
    return std::expected<bool, int>(true);
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

std::expected<std::u32string, int> FunctionSymbol::FullName() const
{
    ClassTypeSymbol* parentClassType = ParentClassType();
    std::u32string fullName;
    if (parentClassType)
    {
        std::expected<std::u32string, int> fname = parentClassType->FullName();
        if (!fname) return fname;
        fullName = *fname;
    }
    else if (ParentNamespace())
    {
        std::expected<std::u32string, int> fname = ParentNamespace()->FullName();
        if (!fname) return fname;
        fullName = *fname;
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
        std::expected<std::u32string, int> fname = parameter->GetType()->FullName();
        if (!fname) return fname;
        fullName.append(*fname);
    }
    fullName.append(U")");
    std::string qualifierStr = MakeFunctionQualifierStr(Qualifiers());
    if (!qualifierStr.empty())
    {
        std::expected<std::u32string, int> qstr = util::ToUtf32(qualifierStr);
        if (!qstr) return qstr;
        fullName.append(U" ").append(*qstr);
    }
    return std::expected<std::u32string, int>(fullName);
}

std::expected<bool, int> FunctionSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<bool, int> rv = ContainerSymbol::AddSymbol(symbol, sourcePos, context);
    if (!rv) return rv;
    if (symbol->IsParameterSymbol())
    {
        ParameterSymbol* parameterSymbol = static_cast<ParameterSymbol*>(symbol);
        parameters.push_back(parameterSymbol);
    }
    else if (symbol->IsLocalVariableSymbol())
    {
        localVariables.push_back(static_cast<VariableSymbol*>(symbol));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionSymbol::AddParameter(ParameterSymbol* parameter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return AddSymbol(parameter, sourcePos, context);
}

std::expected<bool, int> FunctionSymbol::AddTemporaryParameter(TypeSymbol* paramType, int index)
{
    std::expected<std::u32string, int> pstr = util::ToUtf32(std::to_string(index));
    if (!pstr) return std::unexpected<int>(pstr.error());
    std::u32string paramName = U"p" + *pstr;
    std::unique_ptr<ParameterSymbol> temporaryParam(new ParameterSymbol(paramName, paramType));
    parameters.push_back(temporaryParam.get());
    temporaryParams.push_back(std::move(temporaryParam));
    return std::expected<bool, int>(true);
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

std::expected<bool, int> FunctionSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = ContainerSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(kind));
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(qualifiers));
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(linkage));
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(index);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(static_cast<std::int32_t>(flags));
    if (!rv) return rv;
    if (returnType)
    {
        rv = writer.GetBinaryStreamWriter().Write(returnType->Id());
        if (!rv) return rv;
    }
    else
    {
        rv = writer.GetBinaryStreamWriter().Write(util::nil_uuid());
        if (!rv) return rv;
    }
    if (ReturnsClass())
    {
        rv = writer.Write(ReturnValueParam());
        if (!rv) return rv;
    }
    rv = writer.GetBinaryStreamWriter().Write(vtabIndex);
    if (!rv) return rv;
    if (IsConversion())
    {
        rv = writer.GetBinaryStreamWriter().Write(static_cast<std::uint8_t>(GetConversionKind()));
        if (!rv) return rv;
        TypeSymbol* convParamType = ConversionParamType();
        if (convParamType)
        {
            rv = writer.GetBinaryStreamWriter().Write(convParamType->Id());
            if (!rv) return rv;
        }
        else
        {
            rv = writer.GetBinaryStreamWriter().Write(util::nil_uuid());
            if (!rv) return rv;
        }
        TypeSymbol* convArgType = ConversionArgType();
        if (convArgType)
        {
            rv = writer.GetBinaryStreamWriter().Write(convArgType->Id());
            if (!rv) return rv;
        }
        else
        {
            rv = writer.GetBinaryStreamWriter().Write(util::nil_uuid());
            if (!rv) return rv;
        }
        rv = writer.GetBinaryStreamWriter().Write(ConversionDistance());
        if (!rv) return rv;
    }
    if (GetFlag(FunctionSymbolFlags::fixedIrName))
    {
        rv = writer.GetBinaryStreamWriter().Write(fixedIrName);
        if (!rv) return rv;
    }
    std::uint32_t ns = specialization.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(ns);
    if (!rv) return rv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(ns); ++i)
    {
        rv = writer.GetBinaryStreamWriter().Write(specialization[i]->Id());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = ContainerSymbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint8_t, int> brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t b = *brv;
    kind = static_cast<FunctionKind>(b);
    brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    b = *brv;
    qualifiers = static_cast<FunctionQualifiers>(b);
    brv = reader.GetBinaryStreamReader().ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    b = *brv;
    linkage = static_cast<Linkage>(b);
    std::expected<std::int32_t, int> irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    index = *irv;
    irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    std::int32_t i = *irv;
    flags = static_cast<FunctionSymbolFlags>(i);
    rv = reader.GetBinaryStreamReader().ReadUuid(returnTypeId);
    if (!rv) return rv;
    if (ReturnsClass())
    {
        std::expected<Symbol*, int> srv = reader.ReadSymbol();
        if (!srv) return std::unexpected<int>(srv.error());
        Symbol* returnValueParamSymbol = *srv;
        if (returnValueParamSymbol->IsParameterSymbol())
        {
            returnValueParam.reset(static_cast<ParameterSymbol*>(returnValueParamSymbol));
        }
    }
    irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    vtabIndex = *irv;
    if (IsConversion())
    {
        brv = reader.GetBinaryStreamReader().ReadByte();
        if (!brv) return std::unexpected<int>(brv.error());
        b = *brv;
        conversionKind = static_cast<ConversionKind>(b);
        rv = reader.GetBinaryStreamReader().ReadUuid(conversionParamTypeId);
        if (!rv) return rv;
        rv = reader.GetBinaryStreamReader().ReadUuid(conversionArgTypeId);
        if (!rv) return rv;
        irv = reader.GetBinaryStreamReader().ReadInt();
        if (!irv) return std::unexpected<int>(irv.error());
        conversionDistance = *irv;
    }
    if (GetFlag(FunctionSymbolFlags::fixedIrName))
    {
        std::expected<std::string, int> srv = reader.GetBinaryStreamReader().ReadUtf8String();
        if (!srv) return std::unexpected<int>(srv.error());
        fixedIrName = std::move(*srv);
    }
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::int32_t ns = static_cast<std::int32_t>(*urv);
    for (std::int32_t i = 0; i < ns; ++i)
    {
        util::uuid sid;
        rv = reader.GetBinaryStreamReader().ReadUuid(sid);
        if (!rv) return rv;
        specializationIds.push_back(sid);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = ContainerSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    if (returnTypeId != util::nil_uuid())
    {
        returnType = symbolTable.GetType(returnTypeId);
        if (!returnType)
        {
            std::expected<std::string, int> name = util::ToUtf8(Name());
            if (!name) return std::unexpected<int>(name.error());
            std::cout << "FunctionSymbol::Resolve(): warning: return type of '" + *name + "' not resolved" << "\n";
        }
        if (ReturnsClass())
        {
            rv = returnValueParam->Resolve(symbolTable, context);
            if (!rv) return rv;
        }
    }
    if (IsConversion())
    {
        if (conversionParamTypeId != util::nil_uuid())
        {
            conversionParamType = symbolTable.GetType(conversionParamTypeId);
            if (!conversionParamType)
            {
                std::expected<std::string, int> name = util::ToUtf8(Name());
                if (!name) return std::unexpected<int>(name.error());
                std::cout << "FunctionSymbol::Resolve(): warning: conversion parameter type of '" + *name + "' not resolved" << "\n";
            }
        }
        if (conversionArgTypeId != util::nil_uuid())
        {
            conversionArgType = symbolTable.GetType(conversionArgTypeId);
            if (!conversionArgType)
            {
                std::expected<std::string, int> name = util::ToUtf8(Name());
                if (!name) return std::unexpected<int>(name.error());
                std::cout << "FunctionSymbol::Resolve(): warning: conversion argument type of '" + *name + "' not resolved" << "\n";
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
            std::expected<std::string, int> name = util::ToUtf8(Name());
            if (!name) return std::unexpected<int>(name.error());
            std::cout << "FunctionSymbol::Resolve(): warning: specialization type of '" + *name + "' not resolved" << "\n";
        }
    }
    return std::expected<bool, int>(true);
}

void FunctionSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> FunctionSymbol::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    if (IsTrivialDestructor()) return std::expected<bool, int>(false);
    if ((flags & OperationFlags::virtualCall) != OperationFlags::none)
    {
        return GenerateVirtualFunctionCall(emitter, args, sourcePos, context);
    }
    int n = args.size();
    for (int i = 0; i < n; ++i)
    {
        BoundExpressionNode* arg = args[i];
        std::expected<bool, int> rv = arg->Load(emitter, OperationFlags::none, sourcePos, context);
        if (!rv) return rv;
    }
    std::vector<otava::intermediate::Value*> arguments;
    arguments.resize(n);
    for (int i = 0; i < n; ++i)
    {
        otava::intermediate::Value* arg = emitter.Stack().Pop();
        arguments[n - i - 1] = arg;
    }
    std::expected< otava::intermediate::Type*, int> irv = IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    otava::intermediate::Type* type = *irv;
    if (type->IsFunctionType())
    {
        otava::intermediate::FunctionType* functionType = static_cast<otava::intermediate::FunctionType*>(type);
        std::expected<std::string, int> irName = IrName(context);
        if (!irName) return std::unexpected<int>(irName.error());
        std::expected<otava::intermediate::Function*, int> frv = emitter.GetOrInsertFunction(*irName, functionType);
        if (!frv) return std::unexpected<int>(frv.error());
        otava::intermediate::Function* function = *frv;
        if (!functionType->ReturnType() || functionType->ReturnType()->IsVoidType())
        {
            std::expected<otava::intermediate::Value*, int> rv = emitter.EmitCall(function, arguments);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        else
        {
            std::expected<otava::intermediate::Value*, int> rv = emitter.EmitCall(function, arguments);
            if (!rv) return std::unexpected<int>(rv.error());
            otava::intermediate::Value* call = *rv;
            emitter.Stack().Push(call);
        }
    }
    else
    {
        return Error("function type expected", sourcePos, context);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionSymbol::GenerateVirtualFunctionCall(Emitter& emitter, std::vector<BoundExpressionNode*>& args, const soul::ast::SourcePos& sourcePos,
    otava::symbols::Context* context)
{
    TypeSymbol* thisPtrBaseType = args[0]->GetType()->GetBaseType();
    std::expected< otava::intermediate::Type*, int> irv = IrType(emitter, sourcePos, context);
    if (!irv) return std::unexpected<int>(irv.error());
    otava::intermediate::Type* irType = *irv;
    otava::intermediate::FunctionType* functionType = nullptr;
    if (irType->IsFunctionType())
    {
        functionType = static_cast<otava::intermediate::FunctionType*>(irType);
    }
    else
    {
        return Error("function type expected", sourcePos, context);
    }
    ClassTypeSymbol* classType = nullptr;
    if (thisPtrBaseType->IsClassTypeSymbol())
    {
        classType = static_cast<ClassTypeSymbol*>(thisPtrBaseType);
    }
    else
    {
        return Error("class type expected for this pointer base type", sourcePos, context);
    }
    std::vector<ClassTypeSymbol*> vptrHolderClasses = classType->VPtrHolderClasses();
    if (vptrHolderClasses.empty())
    {
        std::expected<std::u32string, int> fname = classType->FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        return Error("no vptr holder classes for the class '" + *sfname + "'", sourcePos, context);
    }
    ClassTypeSymbol* vptrHolderClass = vptrHolderClasses.front();
    int na = args.size();
    otava::intermediate::Value* callee = nullptr;
    for (int i = 0; i < na; ++i)
    {
        std::expected<bool, int> rv = args[i]->Load(emitter, OperationFlags::none, sourcePos, context);
        if (!rv) return rv;
        if (i == 0)
        {
            otava::intermediate::Value* thisPtr = emitter.Stack().Pop();
            if (classType != vptrHolderClass)
            {
                std::expected<TypeSymbol*, int> pt = vptrHolderClass->AddPointer(context);
                if (!pt) return std::unexpected<int>(pt.error());
                TypeSymbol* type = *pt;
                std::expected<otava::intermediate::Type*, int> irv = type->IrType(emitter, sourcePos, context);
                if (!irv) return std::unexpected<int>(irv.error());
                thisPtr = emitter.EmitBitcast(thisPtr, *irv);
            }
            std::expected<otava::intermediate::Value*, int> erv = emitter.EmitElemAddr(thisPtr, emitter.EmitLong(vptrHolderClass->VPtrIndex()));
            if (!erv) return std::unexpected<int>(erv.error());
            otava::intermediate::Value* vptrPtr = *erv;
            std::expected<otava::intermediate::Instruction*, int> lrv = emitter.EmitLoad(vptrPtr);
            if (!lrv) return std::unexpected<int>(lrv.error());
            otava::intermediate::Value* voidVPtr = *lrv;
            std::expected<otava::intermediate::Type*, int> vrv = classType->VPtrType(emitter);
            if (!vrv) return std::unexpected<int>(vrv.error());
            otava::intermediate::Type* vptrType = *vrv;
            otava::intermediate::Value* vptr = emitter.EmitBitcast(voidVPtr, vptrType);
            erv = emitter.EmitElemAddr(thisPtr, emitter.EmitLong(vptrHolderClass->DeltaIndex()));
            if (!erv) return std::unexpected<int>(erv.error());
            otava::intermediate::Value* objectDeltaPtrElem = *erv;
            std::expected<otava::intermediate::Type*, int> prv = emitter.MakePtrType(emitter.GetLongType());
            if (!prv) return std::unexpected<int>(prv.error());
            otava::intermediate::Type* deltaPtrType = *prv;
            otava::intermediate::Value* objectDeltaPtr = emitter.EmitBitcast(objectDeltaPtrElem, deltaPtrType);
            lrv = emitter.EmitLoad(objectDeltaPtr);
            if (!lrv) return std::unexpected<int>(lrv.error());
            otava::intermediate::Value* objectDelta = *lrv;
            std::expected<otava::intermediate::Value*, int> crv = emitter.EmitClassPtrConversion(thisPtr, objectDelta, thisPtr->GetType());
            if (!crv) return std::unexpected<int>(crv.error());
            otava::intermediate::Value* adjustedObjectPtr = *crv;
            if (VTabIndex() == -1)
            {
                return Error("invalid vtab index", sourcePos, context);
            }
            erv = emitter.EmitElemAddr(vptr, emitter.EmitLong(vtabClassIdElementCount + 2 * VTabIndex()));
            if (!erv) return std::unexpected<int>(erv.error());
            otava::intermediate::Value* functionPtrPtr = *erv;
            lrv = emitter.EmitLoad(functionPtrPtr);
            if (!lrv) return std::unexpected<int>(lrv.error());
            otava::intermediate::Value* voidFunctionPtr = *lrv;
            prv = emitter.MakePtrType(functionType);
            if (!prv) return std::unexpected<int>(prv.error());
            callee = emitter.EmitBitcast(voidFunctionPtr, *prv);
            erv = emitter.EmitElemAddr(vptr, emitter.EmitLong(vtabClassIdElementCount + 2 * VTabIndex() + 1));
            if (!erv) return std::unexpected<int>(erv.error());
            otava::intermediate::Value* deltaPtrElem = *erv;
            otava::intermediate::Value* deltaPtr = emitter.EmitBitcast(deltaPtrElem, deltaPtrType);
            lrv = emitter.EmitLoad(deltaPtr);
            if (!lrv) return std::unexpected<int>(lrv.error());
            otava::intermediate::Value* delta = *lrv;
            crv = emitter.EmitClassPtrConversion(adjustedObjectPtr, delta, thisPtr->GetType());
            if (!crv) return std::unexpected<int>(crv.error());
            otava::intermediate::Value* adjustedThisPtr = *crv;
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
        std::expected<otava::intermediate::Value*, int> rv = emitter.EmitCall(callee, arguments);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    else
    {
        std::expected<otava::intermediate::Value*, int> rv = emitter.EmitCall(callee, arguments);
        if (!rv) return std::unexpected<int>(rv.error());
        otava::intermediate::Value* call = *rv;
        emitter.Stack().Push(call);
    }
    std::expected<bool, int> rv = context->GetBoundCompileUnit()->AddBoundNodeForClass(classType, sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

FunctionTypeSymbol* FunctionSymbol::GetFunctionType(otava::symbols::Context* context)
{
    FunctionTypeSymbol* functionType = context->GetSymbolTable()->MakeFunctionTypeSymbol(this);
    return functionType;
}

std::expected<otava::intermediate::Type*, int> FunctionSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) const
{
    otava::intermediate::Type* type = emitter.GetType(Id());
    if (!type)
    {
        otava::intermediate::Type* returnIrType = nullptr;
        if (returnType && !ReturnsClass())
        {
            std::expected<TypeSymbol*, int> dt = returnType->DirectType(context);
            if (!dt) return std::unexpected<int>(dt.error());
            TypeSymbol* directType = *dt;
            auto frv = directType->FinalType(sourcePos, context);
            if (!frv) return std::unexpected<int>(frv.error());
            TypeSymbol* finalType = *frv;
            std::expected<otava::intermediate::Type*, int> rv = finalType->IrType(emitter, sourcePos, context);
            if (!rv) return rv;
            returnIrType = *rv;
        }
        else
        {
            returnIrType = emitter.GetVoidType();
        }
        std::vector<otava::intermediate::Type*> paramIrTypes;
        for (ParameterSymbol* param : MemFunParameters(context))
        {
            if (!Valid()) return std::unexpected<int>(GetError());
            otava::intermediate::Type* paramIrType = nullptr;
            std::expected<TypeSymbol*, int> rrv = param->GetReferredType(context);
            if (!rrv) return std::unexpected<int>(rrv.error());
            TypeSymbol* paramType = *rrv;
            if (paramType->IsClassTypeSymbol())
            {
                std::expected<TypeSymbol*, int> pt = paramType->AddConst(context);
                if (!pt) return std::unexpected<int>(pt.error());
                TypeSymbol* type = *pt;
                pt = type->AddLValueRef(context);
                if (!pt) return std::unexpected<int>(pt.error());
                type = *pt;
                std::expected<otava::intermediate::Type*, int> rv = type->IrType(emitter, sourcePos, context);
                if (!rv) return rv;
                paramIrType = *rv;
            }
            else
            {
                std::expected<otava::intermediate::Type*, int> rv = paramType->IrType(emitter, sourcePos, context);
                if (!rv) return rv;
                paramIrType = *rv;
            }
            paramIrTypes.push_back(paramIrType);
        }
        if (ReturnsClass())
        {
            std::expected<TypeSymbol*, int> trv = ReturnValueParam()->GetReferredType(context);
            if (!trv) return std::unexpected<int>(trv.error());
            TypeSymbol* returnType = *trv;
            std::expected<otava::intermediate::Type*, int> rv = returnType->IrType(emitter, sourcePos, context);
            if (!rv) return rv;
            paramIrTypes.push_back(*rv);
        }
        std::expected<otava::intermediate::Type*, int> rv = emitter.MakeFunctionType(returnIrType, paramIrTypes);
        if (!rv) return rv;
        type = *rv;
        emitter.SetType(Id(), type);
    }
    return std::expected<otava::intermediate::Type*, int>(type);
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

std::expected<std::string, int> FunctionSymbol::IrName(Context* context) const
{
    if (GetFlag(FunctionSymbolFlags::fixedIrName) && !fixedIrName.empty())
    {
        return std::expected<std::string, int>(fixedIrName);
    }
    if (linkage == Linkage::cpp_linkage)
    {
        std::string irName;
        std::expected<SpecialFunctionKind, int> s = GetSpecialFunctionKind(context);
        if (!s) return std::unexpected<int>(s.error());
        SpecialFunctionKind specialFunctionKind = *s;
        std::string digestSource;
        if (specialFunctionKind != SpecialFunctionKind::none)
        {
            irName.append(SpecialFunctionKindPrefix(specialFunctionKind));
            ClassTypeSymbol* classType = ParentClassType();
            std::expected<std::string, int> cirName = classType->IrName(context);
            if (!cirName) return cirName;
            digestSource.append(*cirName);
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
                    std::expected<std::string, int> cirName = classType->IrName(context);
                    if (!cirName) return cirName;
                    digestSource.append(*cirName);
                    std::expected<std::string, int> groupName = util::ToUtf8(classType->Group()->Name());
                    if (!groupName) return std::unexpected<int>(groupName.error());
                    irName.append("_").append(*groupName);
                }
            }
            else
            {
                if (kind == FunctionKind::constructor && ParentClassType())
                {
                    ClassTypeSymbol* classType = ParentClassType();
                    std::expected<std::string, int> groupName = util::ToUtf8(classType->Group()->Name());
                    if (!groupName) return std::unexpected<int>(groupName.error());
                    irName.append("ctor_").append(*groupName);
                    std::expected<std::string, int> cirName = classType->IrName(context);
                    if (!cirName) return cirName;
                    digestSource.append(*cirName);
                }
                else if (kind == FunctionKind::destructor && ParentClassType())
                {
                    ClassTypeSymbol* classType = ParentClassType();
                    std::expected<std::string, int> groupName = util::ToUtf8(classType->Group()->Name());
                    if (!groupName) return std::unexpected<int>(groupName.error());
                    irName.append("dtor_").append(*groupName);
                    std::expected<std::string, int> cirName = classType->IrName(context);
                    if (!cirName) return cirName;
                    digestSource.append(*cirName);
                }
                else if (ParentClassType())
                {
                    ClassTypeSymbol* classType = ParentClassType();
                    std::expected<std::string, int> groupName = util::ToUtf8(classType->Group()->Name());
                    if (!groupName) return std::unexpected<int>(groupName.error());
                    std::expected<std::string, int> name = util::ToUtf8(Name());
                    if (!name) return std::unexpected<int>(name.error());
                    irName.append("mfn_").append(*groupName).append("_").append(*name);
                }
                else
                {
                    std::expected<std::string, int> name = util::ToUtf8(Name());
                    if (!name) return std::unexpected<int>(name.error());
                    irName.append("fn_" + *name);
                }
            }
        }
        std::expected<std::u32string, int> fname = FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return sfname;
        std::string fullName = std::move(*sfname);
        if (!specialization.empty())
        {
            int n = specialization.size();
            for (int i = 0; i < n; ++i)
            {
                fname = specialization[i]->FullName();
                if (!fname) return std::unexpected<int>(fname.error());
                sfname = util::ToUtf8(*fname);
                if (!sfname) return sfname;
                digestSource.append(".").append(*sfname);
            }
        }
        digestSource.append(fullName);
        digestSource.append(compileUnitId);
        if (returnType)
        {
            std::expected<std::string, int> irv = returnType->IrName(context);
            if (!irv) return irv;
            std::string retName = std::move(*irv);
            digestSource.append(retName);
        }
        irName.append("_").append(util::GetSha1MessageDigest(digestSource));
        if (GetFlag(FunctionSymbolFlags::fixedIrName))
        {
            fixedIrName = irName;
            return fixedIrName;
        }
        return std::expected<std::string, int>(irName);
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

std::expected<std::u32string, int> FunctionSymbol::NextTemporaryName()
{
    std::expected<std::u32string, int> t = util::ToUtf32(std::to_string(nextTemporaryId++));
    if (!t) return t;
    return std::expected<std::u32string, int>(U"@t" + *t);
}

std::expected<VariableSymbol*, int> FunctionSymbol::CreateTemporary(TypeSymbol* type)
{
    std::expected<std::u32string, int> t = NextTemporaryName();
    if (!t) return std::unexpected<int>(t.error());
    VariableSymbol* temporary = new VariableSymbol(*t);
    temporary->SetDeclaredType(type);
    AddLocalVariable(temporary);
    return std::expected<VariableSymbol*, int>(temporary);
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

std::expected<bool, int> FunctionSymbol::CheckGenerateClassCopyCtor(const soul::ast::SourcePos& sourcePos, Context* context)
{
    for (ParameterSymbol* parameter : MemFunParameters(context))
    {
        if (!Valid()) return std::unexpected<int>(GetError());
        std::expected<TypeSymbol*, int> trv = parameter->GetReferredType(context);
        if (!trv) return std::unexpected<int>(trv.error());
        TypeSymbol* paramType = *trv;
        if (paramType->IsClassTypeSymbol())
        {
            ClassTypeSymbol* classType = static_cast<ClassTypeSymbol*>(paramType);
            std::expected<bool, int> rv = classType->GenerateCopyCtor(sourcePos, context);
            if (!rv) return rv;
        }
    }
    return std::expected<bool, int>(true);
}

void FunctionSymbol::AddDefinitionToGroup(Context* context)
{
}

std::expected<soul::xml::Element*, int> FunctionSymbol::ToXml() const
{
    std::expected<soul::xml::Element*, int> rv = ContainerSymbol::ToXml();
    if (!rv) return rv;
    soul::xml::Element* element = *rv;
    element->SetAttribute("functionKind", FunctionKindStr(kind));
    if (returnType)
    {
        std::expected<std::string, int> name = util::ToUtf8(returnType->Name());
        if (!name) return std::unexpected<int>(name.error());
        element->SetAttribute("returnType", *name);
        element->SetAttribute("returnTypeId", util::ToString(returnType->Id()));
    }
    return std::expected<soul::xml::Element*, int>(element);
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

std::expected<bool, int> FunctionDefinitionSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    if (declaration)
    {
        rv = writer.GetBinaryStreamWriter().Write(declaration->Id());
        if (!rv) return rv;
    }
    else
    {
        rv = writer.GetBinaryStreamWriter().Write(util::nil_uuid());
        if (!rv) return rv;
    }
    rv = writer.GetBinaryStreamWriter().Write(defIndex);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(irName);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionDefinitionSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(declarationId);
    if (!rv) return rv;
    std::expected<std::int32_t, int> irv = reader.GetBinaryStreamReader().ReadInt();
    if (!irv) return std::unexpected<int>(irv.error());
    defIndex = *irv;
    std::expected<std::string, int> srv = reader.GetBinaryStreamReader().ReadUtf8String();
    if (!srv) return std::unexpected<int>(srv.error());
    irName = *srv;
    return std::expected<bool, int>(true);
}

void FunctionDefinitionSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> FunctionDefinitionSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    if (declarationId != util::nil_uuid())
    {
        std::expected<FunctionSymbol*, int> f = symbolTable.GetFunction(declarationId);
        if (!f) return std::unexpected<int>(f.error());
        declaration = *f;
    }
    return std::expected<bool, int>(true);
}

std::expected<std::string, int> FunctionDefinitionSymbol::IrName(Context* context) const
{
    if (declaration)
    {
        if (irName.empty())
        {
            std::expected<std::string, int> rv = declaration->IrName(context);
            if (!rv) return rv;
            irName = *rv;
        }
        return std::expected<std::string, int>(irName);
    }
    else
    {
        if (irName.empty())
        {
            std::expected<std::string, int> rv = FunctionSymbol::IrName(context);
            if (!rv) return rv;
            irName = *rv;
        }
        return std::expected<std::string, int>(irName);
    }
}

std::expected<otava::intermediate::Type*, int> FunctionDefinitionSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, 
    otava::symbols::Context* context) const
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

std::expected<bool, int> FunctionDefinitionSymbol::SetReturnType(TypeSymbol* returnType_, Context* context)
{
    if (declaration)
    {
        std::expected<bool, int> rv = declaration->SetReturnType(returnType_, context);
        if (!rv) return rv;
    }
    std::expected<bool, int> rv = FunctionSymbol::SetReturnType(returnType_, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<soul::xml::Element*, int> FunctionDefinitionSymbol::ToXml() const
{
    std::expected<soul::xml::Element*, int> rv = FunctionSymbol::ToXml();
    if (!rv) return rv;
    soul::xml::Element* element = *rv;
    element->SetAttribute("defIndex", std::to_string(defIndex));
    return std::expected<soul::xml::Element*, int>(element);
}

ExplicitlyInstantiatedFunctionDefinitionSymbol::ExplicitlyInstantiatedFunctionDefinitionSymbol(FunctionDefinitionSymbol* functionDefinitionSymbol,
    const soul::ast::SourcePos& sourcePos, Context* context) :
    FunctionDefinitionSymbol(SymbolKind::explicitlyInstantiatedFunctionDefinitionSymbol, functionDefinitionSymbol->Name()), irName()
{
    std::expected<std::string, int> irv = functionDefinitionSymbol->IrName(context);
    if (!irv)
    {
        SetError(irv.error());
        return;
    }
    irName = *irv;
    SetDeclarationFlags(functionDefinitionSymbol->GetDeclarationFlags());
    SetVTabIndex(functionDefinitionSymbol->VTabIndex());
    SetDefIndex(functionDefinitionSymbol->DefIndex());
    for (ParameterSymbol* parameter : functionDefinitionSymbol->Parameters())
    {
        std::expected<bool, int> rv = AddParameter(parameter->Copy(), sourcePos, context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
    if (functionDefinitionSymbol->ReturnType())
    {
        std::expected<bool, int> rv = SetReturnType(functionDefinitionSymbol->ReturnType(), context);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
    }
}

ExplicitlyInstantiatedFunctionDefinitionSymbol::ExplicitlyInstantiatedFunctionDefinitionSymbol(const std::u32string& name_) :
    FunctionDefinitionSymbol(SymbolKind::explicitlyInstantiatedFunctionDefinitionSymbol, name_)
{
}

std::expected<bool, int> ExplicitlyInstantiatedFunctionDefinitionSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionDefinitionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(irName);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExplicitlyInstantiatedFunctionDefinitionSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionDefinitionSymbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::string, int> srv = reader.GetBinaryStreamReader().ReadUtf8String();
    if (!srv) return std::unexpected<int>(srv.error());
    irName = *srv;
    return std::expected<bool, int>(true);
}

bool FunctionLess::operator()(FunctionSymbol* left, FunctionSymbol* right) const
{
    if (std::uint8_t(left->GetFunctionKind()) < std::uint8_t(right->GetFunctionKind())) return true;
    if (std::uint8_t(left->GetFunctionKind()) > std::uint8_t(right->GetFunctionKind())) return false;
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
