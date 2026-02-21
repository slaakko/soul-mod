// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.classes;

import std;
import otava.symbols.scope;
import otava.symbols.type.symbol;
import otava.symbols.function.kind;
import otava.ast.node;
import otava.ast.statement;
import otava.ast.classes;
import otava.intermediate.data;

export namespace otava::symbols {

const std::int32_t undefinedIndex = 0;
const std::int32_t defaultCtorIndex = -1;
const std::int32_t copyCtorIndex = -2;
const std::int32_t moveCtorIndex = -3;
const std::int32_t copyAssignmentIndex = -4;
const std::int32_t moveAssignmentIndex = -5;
const std::int32_t destructorIndex = -6;

const std::int32_t vtabClassIdElementCount = 2;
const std::int32_t vtabFunctionSectionOffset = 2;

class FunctionDefinitionSymbol;
class ClassGroupSymbol;

std::int32_t GetSpecialFunctionIndex(SpecialFunctionKind specialFunctionKind) noexcept;

using RecordedParseCompoundStatementFn = void (*)(otava::ast::CompoundStatementNode* compoundStatementNode, Context* context);

void SetRecordedParseCompoundStatementFn(RecordedParseCompoundStatementFn fn) noexcept;

using RecordedParseCtorInitializerFn = void (*)(otava::ast::ConstructorInitializerNode* ctorInitializerNode, Context* context);

void SetRecordedParseCtorInitializerFn(RecordedParseCtorInitializerFn fn) noexcept;

class TemplateDeclarationSymbol;
class TemplateParameterSymbol;
class BoundCompileUnitNode;
class BoundFunctionNode;

enum class ClassKind : std::uint8_t
{
    class_, struct_, union_
};

enum class ClassTypeSymbolFlags : std::uint8_t
{
    none = 0, objectLayoutComputed = 1 << 0, hasUserDefinedDestructor = 1 << 1, hasUserDefinedConstructor = 1 << 2, vtabInitialized = 1 << 3, vtabGenerated = 1 << 4,
    resolved = 1 << 5
};

constexpr ClassTypeSymbolFlags operator|(ClassTypeSymbolFlags left, ClassTypeSymbolFlags right) noexcept
{
    return static_cast<ClassTypeSymbolFlags>(std::uint8_t(left) | std::uint8_t(right));
}

constexpr ClassTypeSymbolFlags operator&(ClassTypeSymbolFlags left, ClassTypeSymbolFlags right) noexcept
{
    return static_cast<ClassTypeSymbolFlags>(std::uint8_t(left) & std::uint8_t(right));
}

constexpr ClassTypeSymbolFlags operator~(ClassTypeSymbolFlags flags) noexcept
{
    return static_cast<ClassTypeSymbolFlags>(~std::uint8_t(flags));
}

class ClassTypeSymbol : public TypeSymbol
{
public:
    ClassTypeSymbol(const std::u32string& name_);
    ClassTypeSymbol(SymbolKind kind_, const std::u32string& name_);
    ClassTypeSymbol(SymbolKind kind_, const util::uuid& id_, const std::u32string& name_);
    int Arity() noexcept;
    inline ClassKind GetClassKind() const noexcept { return classKind; }
    inline void SetClassKind(ClassKind classKind_) noexcept { classKind = classKind_; }
    inline TypeSymbol* Specialization() const noexcept { return specialization; }
    void SetSpecialization(TypeSymbol* specialization_, Context* context) noexcept;
    std::string SymbolKindStr() const override { return "class type symbol"; }
    std::string SymbolDocKindStr() const override { return "class"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration() const noexcept;
    bool IsTemplate() const noexcept;
    void MakeVTab(Context* context, const soul::ast::SourcePos& sourcePos);
    void InitVTab(std::vector<FunctionSymbol*>& vtab, Context* context, const soul::ast::SourcePos& sourcePos, bool clear);
    const std::vector<FunctionSymbol*>& VTab() const { return vtab; }
    std::string IrName(Context* context) const override;
    const std::string& VTabName(Context* context) const { return vtabName; }
    void ComputeVTabName(Context* context);
    inline std::int32_t VPtrIndex() const noexcept { return vptrIndex; }
    inline void SetVPtrIndex(std::int32_t vptrIndex_) noexcept { vptrIndex = vptrIndex_; }
    inline std::int32_t DeltaIndex() const noexcept { return deltaIndex; }
    inline void SetDeltaIndex(std::int32_t deltaIndex_) noexcept { deltaIndex = deltaIndex_; }
    otava::intermediate::Type* VPtrType(Emitter& emitter) const noexcept;
    otava::intermediate::Value* GetVTabVariable(Emitter& emitter, Context* context);
    std::vector<ClassTypeSymbol*> VPtrHolderClasses() const;
    inline const std::vector<ClassTypeSymbol*>& BaseClasses() const noexcept { return baseClasses; }
    void AddBaseClass(ClassTypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context);
    inline const std::vector<ClassTypeSymbol*>& DerivedClasses() const noexcept { return derivedClasses; }
    void AddDerivedClass(ClassTypeSymbol* derivedClass);
    bool HasBaseClass(TypeSymbol* baseClass, int& distance, Context* context) const noexcept override;
    bool HasPolymorphicBaseClass() const noexcept;
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    inline int Level() const noexcept { return level; }
    inline void SetLevel(int level_) noexcept { level = level_; }
    bool IsPolymorphic() const noexcept override;
    inline const std::vector<VariableSymbol*>& MemberVariables() const noexcept { return memberVariables; }
    inline const std::vector<FunctionSymbol*>& MemberFunctions() const noexcept { return memberFunctions; }
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void SetMemFnDefSymbol(FunctionDefinitionSymbol* memFnDefSymbol);
    FunctionDefinitionSymbol* GetMemFnDefSymbol(int32_t defIndex) const noexcept;
    inline const std::map<std::int32_t, FunctionDefinitionSymbol*>& MemFnDefSymbolMap() const noexcept { return memFnDefSymbolMap; }
    inline void SetNextMemFnDefIndex(int32_t defIndex) noexcept { nextMemFnDefIndex = std::max(defIndex, nextMemFnDefIndex); }
    inline int32_t NextMemFnDefIndex() const noexcept { return nextMemFnDefIndex; }
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline const std::vector<TypeSymbol*>& ObjectLayout() const noexcept { return objectLayout; }
    void MakeObjectLayout(const soul::ast::SourcePos& sourcePos, Context* context);
    void MapFunction(FunctionSymbol* function);
    FunctionSymbol* GetFunctionByIndex(std::int32_t functionIndex) const noexcept;
    std::int32_t NextFunctionIndex() noexcept;
    FunctionSymbol* GetFunctionByNodeId(std::int32_t nodeId) const noexcept;
    inline bool GetFlag(ClassTypeSymbolFlags flag) const noexcept { return (flags & flag) != ClassTypeSymbolFlags::none; }
    inline void SetFlag(ClassTypeSymbolFlags flag) noexcept { flags = flags | flag; }
    inline void ResetFlag(ClassTypeSymbolFlags flag) noexcept { flags = flags & ~flag; }
    inline bool ObjectLayoutComputed() const noexcept { return GetFlag(ClassTypeSymbolFlags::objectLayoutComputed); }
    inline void SetObjectLayoutComputed() noexcept { SetFlag(ClassTypeSymbolFlags::objectLayoutComputed); }
    inline void ResetObjectLayoutComputed() noexcept { ResetFlag(ClassTypeSymbolFlags::objectLayoutComputed); }
    inline bool HasUserDefinedDestructor() const noexcept { return GetFlag(ClassTypeSymbolFlags::hasUserDefinedDestructor); }
    inline void SetHasUserDefinedDestructor() noexcept { SetFlag(ClassTypeSymbolFlags::hasUserDefinedDestructor); }
    inline bool HasUserDefinedConstructor() const noexcept { return GetFlag(ClassTypeSymbolFlags::hasUserDefinedConstructor); }
    inline void SetHasUserDefinedConstructor() noexcept { SetFlag(ClassTypeSymbolFlags::hasUserDefinedConstructor); }
    inline bool VTabInitialized() const noexcept { return GetFlag(ClassTypeSymbolFlags::vtabInitialized); }
    inline void SetVTabInitialized() noexcept { SetFlag(ClassTypeSymbolFlags::vtabInitialized); }
    inline const std::vector<FunctionSymbol*>& ConversionFunctions() const noexcept { return conversionFunctions; }
    FunctionSymbol* GetConversionFunction(TypeSymbol* type, Context* context) const noexcept;
    virtual ClassGroupSymbol* Group() const noexcept { return group; }
    inline void SetGroup(ClassGroupSymbol* group_) noexcept { group = group_; }
    bool IsComplete(std::set<const TypeSymbol*>& visited, const TypeSymbol*& incompleteType) const noexcept override;
    FunctionSymbol* CopyCtor() const noexcept { return copyCtor; }
    void GenerateCopyCtor(const soul::ast::SourcePos& sourcePos, Context* context);
    void ResetCopyCtor() noexcept { copyCtor = nullptr; }
    std::pair<bool, std::int64_t> Delta(ClassTypeSymbol* base, Emitter& emitter, Context* context) noexcept;
    int TotalMemberCount() const noexcept;
private:
    ClassTypeSymbolFlags flags;
    std::vector<ClassTypeSymbol*> baseClasses;
    std::vector<util::uuid> baseClassIds;
    ClassKind classKind;
    TypeSymbol* specialization;
    util::uuid specializationId;
    std::vector<ClassTypeSymbol*> derivedClasses;
    std::int32_t level;
    std::vector<VariableSymbol*> memberVariables;
    std::vector<VariableSymbol*> staticMemberVariables;
    std::vector<FunctionSymbol*> memberFunctions;
    std::map<std::int32_t, FunctionDefinitionSymbol*> memFnDefSymbolMap;
    std::map<std::int32_t, util::uuid> memFnDefSymbolIdMap;
    std::vector<TypeSymbol*> objectLayout;
    std::vector<util::uuid> objectLayoutIds;
    otava::intermediate::Type* irType;
    std::map<std::int32_t, FunctionSymbol*> functionIndexMap;
    std::map<std::int32_t, util::uuid> functionIdMap;
    std::map<std::int32_t, FunctionSymbol*> functionNodeIdMap;
    std::int32_t currentFunctionIndex;
    std::vector<FunctionSymbol*> vtab;
    std::int32_t vtabSize;
    std::int32_t vptrIndex;
    std::int32_t deltaIndex;
    std::vector<FunctionSymbol*> conversionFunctions;
    ClassGroupSymbol* group;
    util::uuid groupId;
    std::string vtabName;
    FunctionSymbol* copyCtor;
    std::vector<std::unique_ptr<Symbol>> tempVars;
    int32_t nextMemFnDefIndex;
};

class ForwardClassDeclarationSymbol : public TypeSymbol
{
public:
    ForwardClassDeclarationSymbol(const std::u32string& name_);
    int Arity() noexcept;
    util::uuid IrId(Context* context) const noexcept override;
    inline ClassKind GetClassKind() const noexcept { return classKind; }
    inline void SetClassKind(ClassKind classKind_) noexcept { classKind = classKind_; }
    inline TypeSymbol* Specialization() const noexcept { return specialization; }
    inline void SetSpecialization(TypeSymbol* specialization_) noexcept { specialization = specialization_; }
    inline void SetClassTypeSymbol(ClassTypeSymbol* classTypeSymbol_) noexcept { classTypeSymbol = classTypeSymbol_; }
    inline ClassTypeSymbol* GetClassTypeSymbol() const noexcept { return classTypeSymbol; }
    std::string SymbolKindStr() const override { return "forward class declaration symbol"; }
    std::string SymbolDocKindStr() const override { return "forward_class"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration() noexcept;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    TypeSymbol* FinalType(const soul::ast::SourcePos& sourcePos, Context* context) override;
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsComplete(std::set<const TypeSymbol*>& visited, const TypeSymbol*& incompleteType) const noexcept override;
    inline ClassGroupSymbol* Group() const noexcept { return group; }
    inline void SetGroup(ClassGroupSymbol* group_) noexcept { group = group_; }
private:
    ClassKind classKind;
    TypeSymbol* specialization;
    ClassTypeSymbol* classTypeSymbol;
    util::uuid classTypeSymbolId;
    ClassGroupSymbol* group;
};

void BeginClass(otava::ast::Node* node, Context* context);
void EndClass(otava::ast::Node* node, Context* context);
void ProcessElaboratedClassDeclaration(otava::ast::Node* node, otava::symbols::Context* context);
void SetCurrentAccess(otava::ast::Node* node, otava::symbols::Context* context);
void GetClassAttributes(otava::ast::Node* node, std::u32string& name, otava::symbols::ClassKind& kind, TypeSymbol*& specialization, Context* context);
std::vector<ClassTypeSymbol*> ResolveBaseClasses(otava::ast::Node* node, Context* context);
void ParseInlineMemberFunctions(otava::ast::Node* classSpecifierNode, ClassTypeSymbol* classTypeSymbol, otava::symbols::Context* context);
Symbol* GenerateDestructor(ClassTypeSymbol* classTypeSymbol, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
void GenerateDestructors(BoundCompileUnitNode* compileUnit, otava::symbols::Context* context);
void ThrowMemberDeclarationParsingError(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
void ThrowStatementParsingError(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);

struct ClassLess
{
    bool operator()(ClassTypeSymbol* left, ClassTypeSymbol* right) const noexcept;
};

std::pair<bool, std::int64_t> Delta(ClassTypeSymbol* left, ClassTypeSymbol* right, Emitter& emitter, Context* context) noexcept;

} // namespace otava::symbols
