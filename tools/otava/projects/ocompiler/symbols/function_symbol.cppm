// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.symbol;

import std;
import otava.symbols.symbol;
import otava.symbols.container.symbol;
import otava.symbols.function.kind;
import otava.symbols.bound.tree;
import otava.ast.node;
import otava.intermediate.types;

export namespace otava::symbols {

class TypeSymbol;
class FunctionTypeSymbol;
class Value;

class ParameterSymbol : public Symbol
{
public:
    ParameterSymbol(const std::u32string& name_);
    ParameterSymbol(const std::u32string& name_, TypeSymbol* type_);
    std::string SymbolKindStr() const override { return "parameter symbol"; }
    std::string SymbolDocKindStr() const override { return "parameter"; }
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    inline TypeSymbol* GetType() const { return type; }
    std::expected<TypeSymbol*, int> GetReferredType(Context* context) const;
    inline void SetType(TypeSymbol* type_) { type = type_; }
    ParameterSymbol* Copy() const;
    inline otava::ast::Node* DefaultValue() const { return defaultValue; }
    inline void SetDefaultValue(otava::ast::Node* defaultValue_) { defaultValue = defaultValue_; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    std::expected<soul::xml::Element*, int> ToXml() const override;
private:
    TypeSymbol* type;
    util::uuid typeId;
    otava::ast::Node* defaultValue;
    std::int64_t defaultValueNodeId;
    std::unique_ptr<otava::ast::Node> defaultValueNode;
};

class FunctionSymbol : public ContainerSymbol
{
public:
    FunctionSymbol(const std::u32string& name_);
    FunctionSymbol(SymbolKind kind_, const std::u32string& name_);
    std::u32string GroupName() const;
    inline FunctionGroupSymbol* Group() const { return group; }
    inline void SetGroup(FunctionGroupSymbol* group_) { group = group_; }
    int Arity() const;
    int MemFunArity(Context* context) const;
    int MinArity() const;
    int MinMemFunArity(Context* context) const;
    inline bool HasDefaultParams() const { return MinArity() < Arity(); }
    std::string SymbolKindStr() const override { return "function symbol"; }
    std::string SymbolDocKindStr() const override { return "function"; }
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    virtual FunctionKind GetFunctionKind() const { return kind; }
    inline void SetFunctionKind(FunctionKind kind_) { kind = kind_; }
    inline FunctionQualifiers Qualifiers() const { return qualifiers; }
    inline void SetFunctionQualifiers(FunctionQualifiers qualifiers_) { qualifiers = qualifiers_; }
    inline bool IsInline() const { return GetFlag(FunctionSymbolFlags::inline_); }
    inline void SetInline() { SetFlag(FunctionSymbolFlags::inline_); }
    inline bool IsGenerated() const { return GetFlag(FunctionSymbolFlags::generated); }
    inline void SetGenerated() { SetFlag(FunctionSymbolFlags::generated); }
    inline bool IsConversion() const { return GetFlag(FunctionSymbolFlags::conversion); }
    inline void SetConversion() { SetFlag(FunctionSymbolFlags::conversion); }
    inline bool IsConversionMemFn() const { return GetFunctionKind() == FunctionKind::conversionMemFn; }
    inline void SetConversionMemFn() { SetFunctionKind(FunctionKind::conversionMemFn); }
    inline bool Skip() const { return GetFlag(FunctionSymbolFlags::skip); }
    inline void SetSkip() { SetFlag(FunctionSymbolFlags::skip); }
    virtual bool IsArrayElementAccess() const { return false; }
    TemplateDeclarationSymbol* ParentTemplateDeclaration() const;
    virtual std::expected<bool, int> SetReturnType(TypeSymbol* returnType_, Context* context);
    inline TypeSymbol* ReturnType() const { return returnType; }
    inline bool ReturnsClass() const { return GetFlag(FunctionSymbolFlags::returnsClass); }
    inline void SetReturnsClass() { SetFlag(FunctionSymbolFlags::returnsClass); }
    std::expected<std::u32string, int> FullName() const override;
    bool IsTemplate() const;
    int TemplateArity() const;
    bool IsMemFnOfClassTemplate() const;
    virtual TypeSymbol* ConversionParamType() const { return conversionParamType; }
    void SetConversionParamType(TypeSymbol* conversionParamType_);
    virtual TypeSymbol* ConversionArgType() const { return conversionArgType; }
    void SetConversionArgType(TypeSymbol* conversionArgType_);
    virtual ConversionKind GetConversionKind() const { return conversionKind; }
    void SetConversionKind(ConversionKind conversionKind_);
    virtual std::int32_t ConversionDistance() const { return conversionDistance; }
    void SetConversionDistance(std::int32_t conversionDistance_);
    virtual bool IsCtorAssignmentOrArrow() const { return false; }
    virtual bool IsIdentityConversion() const { return false; }
    virtual bool IsDerivedToBaseConversion() const { return false; }
    std::expected<bool, int> AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline const std::vector<ParameterSymbol*>& Parameters() const { return parameters; }
    const std::vector<ParameterSymbol*>& MemFunParameters(Context* context) const;
    inline ParameterSymbol* ReturnValueParam() const { return returnValueParam.get(); }
    void SetReturnValueParam(ParameterSymbol* returnValueParam_);
    std::expected<bool, int> AddParameter(ParameterSymbol* parameter, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<bool, int> AddTemporaryParameter(TypeSymbol* paramType, int index);
    void ClearTemporaryParameters();
    void AddLocalVariable(VariableSymbol* variable);
    void RemoveLocalVariable(VariableSymbol* variable);
    void SetSpecialization(const std::vector<TypeSymbol*>& specialization_);
    inline const std::vector<TypeSymbol*>& Specialization() const { return specialization; }
    bool IsExplicitSpecializationDefinitionSymbol() const;
    bool IsExplicitSpecializationDeclaration()  const;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    virtual std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    std::expected<bool, int> GenerateVirtualFunctionCall(Emitter& emitter, std::vector<BoundExpressionNode*>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    FunctionTypeSymbol* GetFunctionType(otava::symbols::Context* context);
    virtual std::expected<otava::intermediate::Type*, int> IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) const;
    std::expected<std::string, int> IrName(Context* context) const override;
    inline const std::vector<VariableSymbol*>& LocalVariables() const { return  localVariables; }
    std::expected<VariableSymbol*, int> CreateTemporary(TypeSymbol* type);
    virtual bool IsConst() const;
    virtual bool IsVirtual() const;
    virtual bool IsPure() const;
    void SetVirtual();
    virtual bool IsOverride() const;
    virtual bool IsFinal() const;
    void SetOverride();
    ClassTypeSymbol* ParentClassType() const override;
    virtual std::expected<ParameterSymbol*, int> ThisParam(Context* context) const;
    virtual bool IsMemberFunction() const;
    std::expected<SpecialFunctionKind, int> GetSpecialFunctionKind(Context* context) const;
    inline Linkage GetLinkage() const { return linkage; }
    inline void SetLinkage(Linkage linkage_) { linkage = linkage_; }
    inline std::int32_t Index() const { return index; }
    inline void SetIndex(std::int32_t index_) { index = index_; }
    inline bool GetFlag(FunctionSymbolFlags flag) const { return (flags & flag) != FunctionSymbolFlags::none; }
    inline void SetFlag(FunctionSymbolFlags flag) { flags = flags | flag; }
    inline bool IsBound() const { return GetFlag(FunctionSymbolFlags::bound); }
    inline void SetBound() { SetFlag(FunctionSymbolFlags::bound); }
    inline bool IsSpecialization() const { return GetFlag(FunctionSymbolFlags::specialization); }
    inline void SetSpecialization() { SetFlag(FunctionSymbolFlags::specialization); }
    inline bool IsTrivialDestructor() const { return GetFlag(FunctionSymbolFlags::trivialDestructor); }
    std::expected<std::u32string, int> NextTemporaryName();
    inline void SetVTabIndex(std::int32_t vtabIndex_) { vtabIndex = vtabIndex_; }
    inline virtual std::int32_t VTabIndex() const { return vtabIndex; }
    inline FunctionDefinitionSymbol* Destructor() const { return destructor; }
    inline void SetDestructor(FunctionDefinitionSymbol* destructor_) { destructor = destructor_; }
    bool IsDestructor() const;
    virtual bool IsStatic() const;
    virtual bool IsExplicit() const;
    virtual bool IsPointerCopyAssignment() const { return false; }
    std::expected<bool, int> CheckGenerateClassCopyCtor(const soul::ast::SourcePos& sourcePos, Context* context);
    virtual void AddDefinitionToGroup(Context* context);
    void SetFixedIrName(const std::string& fixedIrName_);
    const std::string& FixedIrName() const { return fixedIrName; }
    void SetCompileUnitId(const std::string& compileUnitId_);
    inline const std::string& CompileUnitId() const { return compileUnitId; }
    void SetTemplateArgs(const std::vector<TypeSymbol*>& templateArgs_);
    std::expected<soul::xml::Element*, int> ToXml() const override;
    inline bool Valid() const { return error == 0; }
    explicit inline operator bool() const { return Valid(); }
    inline int GetError() const { return error; }
    inline void SetError(int error_) { error = error_; }
private:
    mutable bool memFunParamsConstructed;
    FunctionKind kind;
    FunctionQualifiers qualifiers;
    Linkage linkage;
    std::int32_t index;
    FunctionSymbolFlags flags;
    TypeSymbol* returnType;
    util::uuid returnTypeId;
    std::vector<ParameterSymbol*> parameters;
    mutable std::unique_ptr<ParameterSymbol> thisParam;
    std::unique_ptr<ParameterSymbol> returnValueParam;
    mutable std::vector<ParameterSymbol*> memFunParameters;
    std::vector<VariableSymbol*> localVariables;
    std::vector<TypeSymbol*> specialization;
    std::vector<util::uuid> specializationIds;
    std::int32_t nextTemporaryId;
    std::int32_t vtabIndex;
    FunctionDefinitionSymbol* destructor;
    ConversionKind conversionKind;
    TypeSymbol* conversionParamType;
    util::uuid conversionParamTypeId;
    TypeSymbol* conversionArgType;
    util::uuid conversionArgTypeId;
    std::int32_t conversionDistance;
    mutable std::string fixedIrName;
    FunctionGroupSymbol* group;
    std::vector<std::unique_ptr<ParameterSymbol>> temporaryParams;
    std::string compileUnitId;
    int error;
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
    std::expected<std::string, int> IrName(Context* context) const override;
    std::expected<otava::intermediate::Type*, int> IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) const override;
    std::expected<bool, int> SetReturnType(TypeSymbol* returnType_, Context* context) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    inline std::int32_t DefIndex() const { return defIndex; }
    inline void SetDefIndex(std::int32_t defIndex_) { defIndex = defIndex_; }
    bool IsConst() const override;
    bool IsVirtual() const override;
    bool IsPure() const override;
    bool IsOverride() const override;
    bool IsFinal() const override;
    std::int32_t VTabIndex() const override;
    bool IsStatic() const override;
    bool IsExplicit() const override;
    TypeSymbol* ConversionParamType() const override;
    TypeSymbol* ConversionArgType() const override;
    std::int32_t ConversionDistance() const override;
    void AddDefinitionToGroup(Context* context) override;
    bool IsMemberFunction() const override;
    inline const std::string& GetIrName() const { return irName; }
    std::expected<soul::xml::Element*, int> ToXml() const override;
private:
    FunctionSymbol* declaration;
    util::uuid declarationId;
    std::int32_t defIndex;
    mutable std::string irName;
};

class ExplicitlyInstantiatedFunctionDefinitionSymbol : public FunctionDefinitionSymbol
{
public:
    ExplicitlyInstantiatedFunctionDefinitionSymbol(FunctionDefinitionSymbol* functionDefinitionSymbol, const soul::ast::SourcePos& sourcePos, Context* context);
    ExplicitlyInstantiatedFunctionDefinitionSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "explicitly instantiated function definition symbol"; }
    std::string SymbolDocKindStr() const override { return "explcitly_instantiated_function_definition"; }
    std::expected<std::string, int> IrName(Context* context) const override { return std::expected<std::string, int>(irName); }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
private:
    std::string irName;
};

struct FunctionLess
{
    bool operator()(FunctionSymbol* left, FunctionSymbol* right) const;
};

bool FunctionMatches(FunctionSymbol* left, FunctionSymbol* right, Context* context);

void InitFunction();

} // namespace otava::symbols
