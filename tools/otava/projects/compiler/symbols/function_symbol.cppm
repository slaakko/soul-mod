// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.symbol;

import std;
import otava.symbols.symbol;
import otava.symbols.container.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.type.symbol;
import otava.symbols.bound.tree;
import otava.ast;
import otava.intermediate.types;

export namespace otava::symbols {

class TypeSymbol;
class Value;
class BlockSymbol;

class ParameterSymbol : public Symbol
{
public:
    ParameterSymbol(const std::u32string& name_);
    ParameterSymbol(const std::u32string& name_, TypeSymbol* type_);
    std::string SymbolKindStr() const override { return "parameter symbol"; }
    std::string SymbolDocKindStr() const override { return "parameter"; }
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    inline TypeSymbol* GetType() const noexcept { return type; }
    TypeSymbol* GetReferredType(Context* context) const;
    inline void SetType(TypeSymbol* type_) noexcept { type = type_; }
    ParameterSymbol* Copy() const;
    inline otava::ast::Node* DefaultValue() const noexcept { return defaultValue; }
    inline void SetDefaultValue(otava::ast::Node* defaultValue_) noexcept { defaultValue = defaultValue_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    soul::xml::Element* ToXml() const override;
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
    inline FunctionGroupSymbol* Group() const noexcept { return group; }
    inline void SetGroup(FunctionGroupSymbol* group_) noexcept { group = group_; }
    int Arity() const noexcept;
    int MemFunArity(Context* context) const;
    int MinArity() const noexcept;
    int MinMemFunArity(Context* context) const;
    inline bool HasDefaultParams() const noexcept { return MinArity() < Arity(); }
    std::string SymbolKindStr() const override { return "function symbol"; }
    std::string SymbolDocKindStr() const override { return "function"; }
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    virtual FunctionKind GetFunctionKind() const noexcept { return kind; }
    inline void SetFunctionKind(FunctionKind kind_) noexcept { kind = kind_; }
    inline FunctionQualifiers Qualifiers() const noexcept { return qualifiers; }
    inline void SetFunctionQualifiers(FunctionQualifiers qualifiers_) noexcept { qualifiers = qualifiers_; }
    inline bool IsInline() const noexcept { return GetFlag(FunctionSymbolFlags::inline_); }
    inline void SetInline() noexcept { SetFlag(FunctionSymbolFlags::inline_); }
    inline bool IsGenerated() const noexcept { return GetFlag(FunctionSymbolFlags::generated); }
    inline void SetGenerated() noexcept { SetFlag(FunctionSymbolFlags::generated); }
    inline bool IsConversion() const noexcept { return GetFlag(FunctionSymbolFlags::conversion); }
    inline void SetConversion() noexcept { SetFlag(FunctionSymbolFlags::conversion); }
    inline bool IsConversionMemFn() const noexcept { return GetFunctionKind() == FunctionKind::conversionMemFn; }
    inline void SetConversionMemFn() noexcept { SetFunctionKind(FunctionKind::conversionMemFn); }
    inline bool ContainsStatics() const noexcept { return GetFlag(FunctionSymbolFlags::containsStatics); }
    inline void SetContainsStatics() noexcept { SetFlag(FunctionSymbolFlags::containsStatics); }
    inline bool ContainsNodeWithNoSource() const noexcept { return GetFlag(FunctionSymbolFlags::containsNodeWithNoSource); }
    inline void SetContainsNodeWithNoSource() noexcept { SetFlag(FunctionSymbolFlags::containsNodeWithNoSource); }
    inline bool SkipInvokeChecking() const noexcept { return GetFlag(FunctionSymbolFlags::skipInvokeChecking); }
    inline void SetSkipInvokeChecking() noexcept { SetFlag(FunctionSymbolFlags::skipInvokeChecking); }
    inline bool Skip() const noexcept { return GetFlag(FunctionSymbolFlags::skip); }
    inline void SetSkip() noexcept { SetFlag(FunctionSymbolFlags::skip); }
    virtual bool IsArrayElementAccess() const noexcept { return false; }
    TemplateDeclarationSymbol* ParentTemplateDeclaration() const noexcept;
    virtual void SetReturnType(TypeSymbol* returnType_, Context* context);
    inline TypeSymbol* ReturnType() const noexcept { return returnType; }
    inline bool ReturnsClass() const noexcept { return GetFlag(FunctionSymbolFlags::returnsClass); }
    inline void SetReturnsClass() noexcept { SetFlag(FunctionSymbolFlags::returnsClass); }
    std::u32string FullName() const override;
    bool IsTemplate() const noexcept;
    int TemplateArity() const noexcept;
    bool IsMemFnOfClassTemplate() const noexcept;
    virtual TypeSymbol* ConversionParamType() const noexcept { return conversionParamType; }
    void SetConversionParamType(TypeSymbol* conversionParamType_) noexcept;
    virtual TypeSymbol* ConversionArgType() const noexcept { return conversionArgType; }
    void SetConversionArgType(TypeSymbol* conversionArgType_) noexcept;
    virtual ConversionKind GetConversionKind() const noexcept { return conversionKind; }
    void SetConversionKind(ConversionKind conversionKind_) noexcept;
    virtual std::int32_t ConversionDistance() const noexcept { return conversionDistance; }
    void SetConversionDistance(std::int32_t conversionDistance_) noexcept;
    virtual bool IsCtorAssignmentOrArrow() const noexcept { return false; }
    virtual bool IsIdentityConversion() const noexcept { return false; }
    virtual bool IsDerivedToBaseConversion() const noexcept { return false; }
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline const std::vector<ParameterSymbol*>& Parameters() const noexcept { return parameters; }
    const std::vector<ParameterSymbol*>& MemFunParameters(Context* context) const;
    inline ParameterSymbol* ReturnValueParam() const noexcept { return returnValueParam.get(); }
    void SetReturnValueParam(ParameterSymbol* returnValueParam_) noexcept;
    void AddParameter(ParameterSymbol* parameter, const soul::ast::SourcePos& sourcePos, Context* context);
    void AddTemporaryParameter(TypeSymbol* paramType, int index);
    void ClearTemporaryParameters();
    void AddLocalVariable(VariableSymbol* variable);
    void RemoveLocalVariable(VariableSymbol* variable);
    void SetSpecialization(const std::vector<TypeSymbol*>& specialization_);
    inline const std::vector<TypeSymbol*>& Specialization() const noexcept { return specialization; }
    bool IsExplicitSpecializationDefinitionSymbol() const noexcept;
    bool IsExplicitSpecializationDeclaration() const noexcept;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    virtual void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    void GenerateVirtualFunctionCall(Emitter& emitter, std::vector<BoundExpressionNode*>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    FunctionTypeSymbol* GetFunctionType(otava::symbols::Context* context);
    virtual otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) const;
    std::string IrName(Context* context) const override;
    const std::vector<VariableSymbol*>& LocalVariables() const noexcept { return  localVariables; }
    VariableSymbol* CreateTemporary(TypeSymbol* type);
    virtual bool IsConst() const noexcept;
    virtual bool IsVirtual() const noexcept;
    virtual bool IsPure() const noexcept;
    void SetVirtual() noexcept;
    virtual bool IsOverride() const noexcept;
    virtual bool IsFinal() const noexcept;
    void SetOverride() noexcept;
    virtual bool IsNoExcept() const noexcept;
    virtual void SetNoExcept() noexcept;
    bool ContainsLocalVariableWithDestructor() const noexcept { return GetFlag(FunctionSymbolFlags::containsLocalVariableWithDestructor); }
    ClassTypeSymbol* ParentClassType() const noexcept override;
    virtual ParameterSymbol* ThisParam(Context* context) const;
    virtual bool IsMemberFunction() const noexcept;
    SpecialFunctionKind GetSpecialFunctionKind(Context* context) const noexcept;
    inline Linkage GetLinkage() const noexcept { return linkage; }
    inline void SetLinkage(Linkage linkage_) noexcept { linkage = linkage_; }
    inline std::int32_t Index() const noexcept { return index; }
    inline void SetIndex(std::int32_t index_) noexcept { index = index_; }
    inline bool GetFlag(FunctionSymbolFlags flag) const noexcept { return (flags & flag) != FunctionSymbolFlags::none; }
    inline void SetFlag(FunctionSymbolFlags flag) noexcept { flags = flags | flag; }
    inline bool IsBound() const noexcept { return GetFlag(FunctionSymbolFlags::bound); }
    inline void SetBound() noexcept { SetFlag(FunctionSymbolFlags::bound); }
    inline bool IsSpecialization() const noexcept { return GetFlag(FunctionSymbolFlags::specialization); }
    inline void SetSpecialization() noexcept { SetFlag(FunctionSymbolFlags::specialization); }
    inline bool IsTrivialDestructor() const noexcept { return GetFlag(FunctionSymbolFlags::trivialDestructor); }
    std::u32string NextTemporaryName();
    inline void SetVTabIndex(std::int32_t vtabIndex_) noexcept { vtabIndex = vtabIndex_; }
    virtual std::int32_t VTabIndex() const noexcept { return vtabIndex; }
    inline FunctionDefinitionSymbol* Destructor() const noexcept { return destructor; }
    inline void SetDestructor(FunctionDefinitionSymbol* destructor_) noexcept { destructor = destructor_; }
    bool IsDestructor() const noexcept;
    virtual bool IsStatic() const noexcept;
    virtual bool IsExplicit() const noexcept;
    virtual bool IsPointerCopyAssignment() const noexcept { return false; }
    void CheckGenerateClassCopyCtor(const soul::ast::SourcePos& sourcePos, Context* context);
    virtual void AddDefinitionToGroup(Context* context);
    void SetFixedIrName(const std::string& fixedIrName_);
    const std::string& FixedIrName() const noexcept { return fixedIrName; }
    void SetCompileUnitId(const std::string& compileUnitId_);
    inline const std::string& CompileUnitId() const noexcept { return compileUnitId; }
    void SetTemplateArgs(const std::vector<TypeSymbol*>& templateArgs_);
    soul::xml::Element* ToXml() const override;
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
};

class FunctionDefinitionSymbol : public FunctionSymbol
{
public:
    FunctionDefinitionSymbol(const std::u32string& name_);
    FunctionDefinitionSymbol(SymbolKind kind_, const std::u32string& name_);
    FunctionKind GetFunctionKind() const noexcept override;
    std::string SymbolKindStr() const override { return "function definition symbol"; }
    std::string SymbolDocKindStr() const override { return "function_definition"; }
    inline void SetDeclaration(FunctionSymbol* declaration_) noexcept { declaration = declaration_; }
    inline FunctionSymbol* Declaration() const noexcept { return declaration; }
    std::string IrName(Context* context) const override;
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) const override;
    void SetReturnType(TypeSymbol* returnType_, Context* context) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    inline std::int32_t DefIndex() const noexcept { return defIndex; }
    inline void SetDefIndex(std::int32_t defIndex_) noexcept { defIndex = defIndex_; }
    bool IsConst() const noexcept override;
    bool IsVirtual() const noexcept override;
    bool IsPure() const noexcept override;
    bool IsOverride() const noexcept override;
    bool IsFinal() const noexcept override;
    bool IsNoExcept() const noexcept override;
    void SetNoExcept() noexcept override;
    std::int32_t VTabIndex() const noexcept override;
    bool IsStatic() const noexcept override;
    bool IsExplicit() const noexcept override;
    TypeSymbol* ConversionParamType() const noexcept override;
    TypeSymbol* ConversionArgType() const noexcept override;
    std::int32_t ConversionDistance() const noexcept override;
    void AddDefinitionToGroup(Context* context) override;
    inline const std::string& GetIrName() const noexcept { return irName; }
    bool IsMemberFunction() const noexcept override;
    soul::xml::Element* ToXml() const override;
    inline FunctionDefinitionSymbol* ParentFn() const noexcept { return parentFn; }
    inline void SetParentFn(FunctionDefinitionSymbol* parentFn_) noexcept { parentFn = parentFn_; }
    inline Scope* ParentFnScope() const noexcept { return parentFnScope; }
    inline void SetParentFnScope(Scope* parentFnScope_) noexcept { parentFnScope = parentFnScope_; }
    std::u32string ResultVarExprStr(TypeSymbol* resultType) const;
    void SetResultVarName(const std::u32string& resultVarName_);
    TypeSymbol* NonChildFunctionResultType(Context* context) const noexcept;
    inline bool ContainsGotosOrLabels() const noexcept { return containsGotosOrLabels; }
    inline void SetContainsGotosOrLabels() noexcept { containsGotosOrLabels = true; }
    void MapBlock(int blockId, Symbol* block);
    Symbol* GetBlock(int blockId) const noexcept;
    inline void SetFnDefNode(otava::ast::FunctionDefinitionNode* fnDefNode_) { fnDefNode.reset(fnDefNode_); }
private:
    FunctionSymbol* declaration;
    util::uuid declarationId;
    std::int32_t defIndex;
    mutable std::string irName;
    FunctionDefinitionSymbol* parentFn;
    Scope* parentFnScope;
    std::u32string resultVarName;
    bool containsGotosOrLabels;
    std::map<int, Symbol*> blockMap;
    std::unique_ptr<otava::ast::FunctionDefinitionNode> fnDefNode;
};

class ExplicitlyInstantiatedFunctionDefinitionSymbol : public FunctionDefinitionSymbol
{
public:
    ExplicitlyInstantiatedFunctionDefinitionSymbol(FunctionDefinitionSymbol* functionDefinitionSymbol_, const soul::ast::SourcePos& sourcePos, Context* context);
    ExplicitlyInstantiatedFunctionDefinitionSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "explicitly instantiated function definition symbol"; }
    std::string SymbolDocKindStr() const override { return "explcitly_instantiated_function_definition"; }
    std::string IrName(Context* context) const override { return irName; }
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) const override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
private:
    FunctionDefinitionSymbol* functionDefinitionSymbol;
    util::uuid functionDefinitionId;
    std::string irName;
};

struct FunctionLess
{
    bool operator()(FunctionSymbol* left, FunctionSymbol* right) const noexcept;
};

bool FunctionMatches(FunctionSymbol* left, FunctionSymbol* right, Context* context) noexcept;

void InitFunction();

class CompileUnitInitFn : public FunctionSymbol
{
public:
    CompileUnitInitFn(const std::u32string& name_);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
};

} // namespace otava::symbols
