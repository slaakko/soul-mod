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
    function, constructor, destructor, special, conversion
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
    none = 0, isConst = 1 << 0, isVolatile = 1 << 1, isOverride = 1 << 2, isFinal = 1 << 3, isDefault = 1 << 4, isDeleted = 1 << 5
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
    none = 0, bound = 1 << 0, specialization = 1 << 1, trivialDestructor = 1 << 2, returnsClass = 1 << 3
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
    TypeSymbol* GetType() const { return type; }
    TypeSymbol* GetReferredType(Context* context) const;
    void SetType(TypeSymbol* type_) { type = type_; }
    ParameterSymbol* Copy() const;
    Value* DefaultValue() const { return defaultValue; }
    void SetDefaultValue(Value* defaultValue_) { defaultValue = defaultValue_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    TypeSymbol* type;
    util::uuid typeId;
    Value* defaultValue;
    util::uuid defaultValueId;
};

class FunctionSymbol : public ContainerSymbol
{
public:
    FunctionSymbol(const std::u32string& name_);
    FunctionSymbol(SymbolKind kind_, const std::u32string& name_);
    std::u32string GroupName() const;
    int Arity() const;
    int MemFunArity(Context* context) const;
    std::string SymbolKindStr() const override { return "function symbol"; }
    std::string SymbolDocKindStr() const override { return "function"; }
    FunctionKind GetFunctionKind() const { return kind; }
    void SetFunctionKind(FunctionKind kind_) { kind = kind_; }
    FunctionQualifiers Qualifiers() const { return qualifiers; }
    void SetFunctionQualifiers(FunctionQualifiers qualifiers_) { qualifiers = qualifiers_; }
    bool IsConversion() const { return kind == FunctionKind::conversion; }
    void SetConversion() { kind = FunctionKind::conversion; }
    virtual bool IsArrayElementAccess() const { return false; }
    TemplateDeclarationSymbol* ParentTemplateDeclaration() const;
    void SetReturnType(TypeSymbol* returnType_, Context* context);
    TypeSymbol* ReturnType() const { return returnType; }
    bool ReturnsClass() const { return GetFlag(FunctionSymbolFlags::returnsClass); }
    void SetReturnsClass() { SetFlag(FunctionSymbolFlags::returnsClass); }
    std::u32string FullName() const override;
    bool IsTemplate() const;
    bool IsMemFnOfClassTemplate() const;
    virtual TypeSymbol* ConversionParamType() const { return nullptr; }
    virtual TypeSymbol* ConversionArgType() const { return nullptr; }
    virtual ConversionKind GetConversionKind() const;
    virtual int32_t ConversionDistance() const { return 0; }
    virtual bool IsCtorAssignmentOrArrow() const { return false; }
    virtual bool IsIdentityConversion() const { return false; }
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
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    std::string IrName(Context* context) const override;
    const std::vector<VariableSymbol*>& LocalVariables() const { return  localVariables; }
    VariableSymbol* CreateTemporary(TypeSymbol* type);
    bool IsVirtual() const;
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
};

class FunctionDefinitionSymbol : public FunctionSymbol
{
public:
    FunctionDefinitionSymbol(const std::u32string& name_);
    FunctionDefinitionSymbol(SymbolKind kind_, const std::u32string& name_);
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
