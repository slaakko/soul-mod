// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.symbol;

import std.core;
import otava.symbols.symbol;
import otava.symbols.container.symbol;
import otava.symbols.bound.tree;
import otava.ast.node;
import otava.intermediate.type;

export namespace otava::symbols {

enum class FunctionKind
{
    function, constructor, destructor, special, conversionMemFn
};

enum class SpecialFunctionKind
{
    none, defaultCtor, copyCtor, moveCtor, copyAssignment, moveAssignment, dtor
};

std::string SpecialFunctionKindPrefix(SpecialFunctionKind specialFunctionKind);

enum class Linkage : int32_t
{
    c_linkage, cpp_linkage
};

enum class FunctionQualifiers : int32_t
{
    none = 0, isConst = 1 << 0, isVolatile = 1 << 1, isOverride = 1 << 2, isFinal = 1 << 3, isPure = 1 << 4, isDefault = 1 << 5, isDeleted = 1 << 6, noreturn = 1 << 7
};

enum class ConversionKind : int32_t;

constexpr FunctionQualifiers operator|(FunctionQualifiers left, FunctionQualifiers right)
{
    return FunctionQualifiers(int32_t(left) | int32_t(right));
}

constexpr FunctionQualifiers operator&(FunctionQualifiers left, FunctionQualifiers right)
{
    return FunctionQualifiers(int32_t(left) & int32_t(right));
}

constexpr FunctionQualifiers operator~(FunctionQualifiers qualifiers)
{
    return FunctionQualifiers(~int32_t(qualifiers));
}

std::string MakeFunctionQualifierStr(FunctionQualifiers qualifiers);

enum class FunctionSymbolFlags : int32_t
{
    none = 0, bound = 1 << 0, specialization = 1 << 1, trivialDestructor = 1 << 2, returnsClass = 1 << 3, conversion = 1 << 4, fixedIrName = 1 << 5
};

constexpr FunctionSymbolFlags operator|(FunctionSymbolFlags left, FunctionSymbolFlags right)
{
    return FunctionSymbolFlags(int32_t(left) | int32_t(right));
}

constexpr FunctionSymbolFlags operator&(FunctionSymbolFlags left, FunctionSymbolFlags right)
{
    return FunctionSymbolFlags(int32_t(left) & int32_t(right));
}

constexpr FunctionSymbolFlags operator~(FunctionSymbolFlags flags)
{
    return FunctionSymbolFlags(~int32_t(flags));
}

class TypeSymbol;
class Value;

class ParameterSymbol : public Symbol
{
public:
    ParameterSymbol(const std::u32string& name_);
    ParameterSymbol(const std::u32string& name_, TypeSymbol* type_);
    std::string SymbolKindStr() const override { return "parameter symbol"; }
    std::string SymbolDocKindStr() const override { return "paremeter"; }
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    TypeSymbol* GetType() const { return type; }
    TypeSymbol* GetReferredType(Context* context) const;
    void SetType(TypeSymbol* type_) { type = type_; }
    ParameterSymbol* Copy() const;
    otava::ast::Node* DefaultValue() const { return defaultValue; }
    void SetDefaultValue(otava::ast::Node* defaultValue_) { defaultValue = defaultValue_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    TypeSymbol* type;
    util::uuid typeId;
    otava::ast::Node* defaultValue;
    int64_t defaultValueNodeId;
};

class FunctionSymbol : public ContainerSymbol
{
public:
    FunctionSymbol(const std::u32string& name_);
    FunctionSymbol(SymbolKind kind_, const std::u32string& name_);
    std::u32string GroupName() const;
    int Arity() const;
    int MemFunArity(Context* context) const;
    int MinArity() const;
    int MinMemFunArity(Context* context) const;
    std::string SymbolKindStr() const override { return "function symbol"; }
    std::string SymbolDocKindStr() const override { return "function"; }
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    virtual FunctionKind GetFunctionKind() const { return kind; }
    void SetFunctionKind(FunctionKind kind_) { kind = kind_; }
    FunctionQualifiers Qualifiers() const { return qualifiers; }
    void SetFunctionQualifiers(FunctionQualifiers qualifiers_) { qualifiers = qualifiers_; }
    bool IsConversion() const { return GetFlag(FunctionSymbolFlags::conversion); }
    void SetConversion() { SetFlag(FunctionSymbolFlags::conversion); }
    bool IsConversionMemFn() const { return GetFunctionKind() == FunctionKind::conversionMemFn; }
    void SetConversionMemFn() { SetFunctionKind(FunctionKind::conversionMemFn); }
    virtual bool IsArrayElementAccess() const { return false; }
    TemplateDeclarationSymbol* ParentTemplateDeclaration() const;
    void SetReturnType(TypeSymbol* returnType_, Context* context);
    TypeSymbol* ReturnType() const { return returnType; }
    bool ReturnsClass() const { return GetFlag(FunctionSymbolFlags::returnsClass); }
    void SetReturnsClass() { SetFlag(FunctionSymbolFlags::returnsClass); }
    std::u32string FullName() const override;
    bool IsTemplate() const;
    int TemplateArity() const;
    bool IsMemFnOfClassTemplate() const;
    virtual TypeSymbol* ConversionParamType() const { return conversionParamType; }
    void SetConversionParamType(TypeSymbol* conversionParamType_);
    virtual TypeSymbol* ConversionArgType() const { return conversionArgType; }
    void SetConversionArgType(TypeSymbol* conversionArgType_);
    virtual ConversionKind GetConversionKind() const { return conversionKind; }
    void SetConversionKind(ConversionKind conversionKind_);
    virtual int32_t ConversionDistance() const { return conversionDistance; }
    void SetConversionDistance(int32_t conversionDistance_);
    virtual bool IsCtorAssignmentOrArrow() const { return false; }
    virtual bool IsIdentityConversion() const { return false; }
    virtual bool IsDerivedToBaseConversion() const { return false; }
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    const std::vector<ParameterSymbol*>& Parameters() const { return parameters; }
    const std::vector<ParameterSymbol*>& MemFunParameters(Context* context) const;
    ParameterSymbol* ReturnValueParam() const { return returnValueParam.get(); }
    void SetReturnValueParam(ParameterSymbol* returnValueParam_);
    void AddParameter(ParameterSymbol* parameter, const soul::ast::SourcePos& sourcePos, Context* context);
    void AddLocalVariable(VariableSymbol* variable);
    void RemoveLocalVariable(VariableSymbol* variable);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    virtual void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    void GenerateVirtualFunctionCall(Emitter& emitter, std::vector<BoundExpressionNode*>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    std::string IrName(Context* context) const override;
    const std::vector<VariableSymbol*>& LocalVariables() const { return  localVariables; }
    VariableSymbol* CreateTemporary(TypeSymbol* type);
    virtual bool IsConst() const;
    virtual bool IsVirtual() const;
    virtual bool IsPure() const;
    void SetVirtual();
    virtual bool IsOverride() const;
    void SetOverride();
    ClassTypeSymbol* ParentClassType() const override;
    ParameterSymbol* ThisParam(Context* ciontext) const;
    bool IsMemberFunction() const;
    SpecialFunctionKind GetSpecialFunctionKind(Context* context) const;
    Linkage GetLinkage() const { return linkage; }
    void SetLinkage(Linkage linkage_) { linkage = linkage_; }
    int32_t Index() const { return index; }
    void SetIndex(int32_t index_) { index = index_; }
    bool GetFlag(FunctionSymbolFlags flag) const { return (flags & flag) != FunctionSymbolFlags::none; }
    void SetFlag(FunctionSymbolFlags flag) { flags = flags | flag; }
    bool IsBound() const { return GetFlag(FunctionSymbolFlags::bound); }
    void SetBound() { SetFlag(FunctionSymbolFlags::bound); }
    bool IsSpecialization() const { return GetFlag(FunctionSymbolFlags::specialization); }
    void SetSpecialization() { SetFlag(FunctionSymbolFlags::specialization); }
    bool IsTrivialDestructor() const { return GetFlag(FunctionSymbolFlags::trivialDestructor); }
    std::u32string NextTemporaryName();
    void SetVTabIndex(int32_t vtabIndex_) { vtabIndex = vtabIndex_; }
    virtual int32_t VTabIndex() const { return vtabIndex; }
    FunctionDefinitionSymbol* Destructor() const { return destructor; }
    void SetDestructor(FunctionDefinitionSymbol* destructor_) { destructor = destructor_; }
    virtual bool IsStatic() const;
    virtual bool IsExplicit() const;
    virtual bool IsPointerCopyAssignment() const { return false; }
    void CheckGenerateClassCopyCtor(const soul::ast::SourcePos& sourcePos, Context* context);
private:
    mutable bool memFunParamsConstructed;
    FunctionKind kind;
    FunctionQualifiers qualifiers;
    Linkage linkage;
    int32_t index;
    FunctionSymbolFlags flags;
    TypeSymbol* returnType;
    util::uuid returnTypeId;
    std::vector<ParameterSymbol*> parameters;
    mutable std::unique_ptr<ParameterSymbol> thisParam;
    std::unique_ptr<ParameterSymbol> returnValueParam;
    mutable std::vector<ParameterSymbol*> memFunParameters;
    std::vector<VariableSymbol*> localVariables;
    int32_t nextTemporaryId;
    int32_t vtabIndex;
    FunctionDefinitionSymbol* destructor;
    ConversionKind conversionKind;
    TypeSymbol* conversionParamType;
    util::uuid conversionParamTypeId;
    TypeSymbol* conversionArgType;
    util::uuid conversionArgTypeId;
    int32_t conversionDistance;
    mutable std::string fixedIrName;
};

class FunctionDefinitionSymbol : public FunctionSymbol
{
public:
    FunctionDefinitionSymbol(const std::u32string& name_);
    FunctionDefinitionSymbol(SymbolKind kind_, const std::u32string& name_);
    FunctionKind GetFunctionKind() const override;
    std::string SymbolKindStr() const override { return "function definition symbol"; }
    std::string SymbolDocKindStr() const override { return "function_definition"; }
    void SetDeclaration(FunctionSymbol* declaration_) { declaration = declaration_; }
    FunctionSymbol* Declaration() const { return declaration; }
    std::string IrName(Context* context) const override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    int32_t DefIndex() const { return defIndex; }
    void SetDefIndex(int32_t defIndex_) { defIndex = defIndex_; }
    bool IsConst() const override;
    bool IsVirtual() const override;
    bool IsPure() const override;
    bool IsOverride() const override;
    int32_t VTabIndex() const override;
    bool IsStatic() const override;
    bool IsExplicit() const override;
    TypeSymbol* ConversionParamType() const override;
    TypeSymbol* ConversionArgType() const override;
    int32_t ConversionDistance() const override;
private:
    FunctionSymbol* declaration;
    util::uuid declarationId;
    int32_t defIndex;
};

class ExplicitlyInstantiatedFunctionDefinitionSymbol : public FunctionDefinitionSymbol
{
public:
    ExplicitlyInstantiatedFunctionDefinitionSymbol(FunctionDefinitionSymbol* functionDefinitionSymbol, const soul::ast::SourcePos& sourcePos, Context* context);
    ExplicitlyInstantiatedFunctionDefinitionSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "explicitly instantiated function definition symbol"; }
    std::string SymbolDocKindStr() const override { return "explcitly_instantiated_function_definition"; }
    std::string IrName(Context* context) const override { return irName; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
private:
    std::string irName;
};

struct FunctionLess
{
    bool operator()(FunctionSymbol* left, FunctionSymbol* right) const;
};

void InitFunction();

} // namespace otava::symbols
