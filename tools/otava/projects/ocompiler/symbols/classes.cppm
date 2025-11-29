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

std::int32_t GetSpecialFunctionIndex(SpecialFunctionKind specialFunctionKind);

using RecordedParseCompoundStatementFn = std::expected<bool, int>(*)(otava::ast::CompoundStatementNode* compoundStatementNode, Context* context);

void SetRecordedParseCompoundStatementFn(RecordedParseCompoundStatementFn fn);

using RecordedParseCtorInitializerFn = std::expected<bool, int>(*)(otava::ast::ConstructorInitializerNode* ctorInitializerNode, Context* context);

void SetRecordedParseCtorInitializerFn(RecordedParseCtorInitializerFn fn);

class TemplateDeclarationSymbol;
class TemplateParameterSymbol;
class BoundCompileUnitNode;

enum class ClassKind : std::uint8_t
{
    class_, struct_, union_
};

enum class ClassTypeSymbolFlags : std::uint8_t
{
    none = 0, 
    objectLayoutComputed = 1 << 0, 
    hasUserDefinedDestructor = 1 << 1, 
    hasUserDefinedConstructor = 1 << 2, 
    vtabInitialized = 1 << 3, 
    vtabGenerated = 1 << 4,
    resolved = 1 << 5
};

constexpr ClassTypeSymbolFlags operator|(ClassTypeSymbolFlags left, ClassTypeSymbolFlags right)
{
    return static_cast<ClassTypeSymbolFlags>(std::uint8_t(left) | std::uint8_t(right));
}

constexpr ClassTypeSymbolFlags operator&(ClassTypeSymbolFlags left, ClassTypeSymbolFlags right)
{
    return static_cast<ClassTypeSymbolFlags>(std::uint8_t(left) & std::uint8_t(right));
}

constexpr ClassTypeSymbolFlags operator~(ClassTypeSymbolFlags flags)
{
    return static_cast<ClassTypeSymbolFlags>(~std::uint8_t(flags));
}

class ClassTypeSymbol : public TypeSymbol
{
public:
    ClassTypeSymbol(const std::u32string& name_);
    ClassTypeSymbol(SymbolKind kind_, const std::u32string& name_);
    ClassTypeSymbol(SymbolKind kind_, const util::uuid& id_, const std::u32string& name_);
    int Arity();
    inline ClassKind GetClassKind() const { return classKind; }
    inline void SetClassKind(ClassKind classKind_) { classKind = classKind_; }
    inline TypeSymbol* Specialization() const { return specialization; }
    void SetSpecialization(TypeSymbol* specialization_, Context* context);
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration() const;
    bool IsTemplate() const;
    std::expected<bool, int> MakeVTab(Context* context, const soul::ast::SourcePos& sourcePos);
    std::expected<bool, int> InitVTab(std::vector<FunctionSymbol*>& vtab, Context* context, const soul::ast::SourcePos& sourcePos, bool clear);
    const std::vector<FunctionSymbol*>& VTab() const;
    std::expected<std::string, int> IrName(Context* context) const override;
    const std::string& VTabName(Context* context) const { return vtabName; }
    std::expected<bool, int> ComputeVTabName(Context* context);
    inline std::int32_t VPtrIndex() const { return vptrIndex; }
    inline void SetVPtrIndex(std::int32_t vptrIndex_) { vptrIndex = vptrIndex_; }
    inline std::int32_t DeltaIndex() const { return deltaIndex; }
    inline void SetDeltaIndex(std::int32_t deltaIndex_) { deltaIndex = deltaIndex_; }
    std::expected<otava::intermediate::Type*, int> VPtrType(Emitter& emitter) const;
    std::expected<otava::intermediate::Value*, int> GetVTabVariable(Emitter& emitter, Context* context);
    std::vector<ClassTypeSymbol*> VPtrHolderClasses() const;
    inline const std::vector<ClassTypeSymbol*>& BaseClasses() const { return baseClasses; }
    std::expected<bool, int> AddBaseClass(ClassTypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context);
    inline const std::vector<ClassTypeSymbol*>& DerivedClasses() const { return derivedClasses; }
    void AddDerivedClass(ClassTypeSymbol* derivedClass);
    bool HasBaseClass(TypeSymbol* baseClass, int& distance, Context* context) const override;
    bool HasPolymorphicBaseClass() const;
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    inline int Level() const { return level; }
    inline void SetLevel(int level_) { level = level_; }
    bool IsPolymorphic() const override;
    inline const std::vector<VariableSymbol*>& MemberVariables() const { return memberVariables; }
    inline const std::vector<FunctionSymbol*>& MemberFunctions() const { return memberFunctions; }
    std::expected<bool, int> AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void SetMemFnDefSymbol(FunctionDefinitionSymbol* memFnDefSymbol);
    FunctionDefinitionSymbol* GetMemFnDefSymbol(int32_t defIndex) const;
    const std::map<std::int32_t, FunctionDefinitionSymbol*>& MemFnDefSymbolMap() const { return memFnDefSymbolMap; }
    inline void SetNextMemFnDefIndex(int32_t defIndex) { nextMemFnDefIndex = std::max(defIndex, nextMemFnDefIndex); }
    inline int32_t NextMemFnDefIndex() const { return nextMemFnDefIndex; }
    std::expected<otava::intermediate::Type*, int> IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline const std::vector<TypeSymbol*>& ObjectLayout() const { return objectLayout; }
    std::expected<bool, int> MakeObjectLayout(const soul::ast::SourcePos& sourcePos, Context* context);
    void MapFunction(FunctionSymbol* function);
    FunctionSymbol* GetFunctionByIndex(std::int32_t functionIndex) const;
    std::int32_t NextFunctionIndex();
    FunctionSymbol* GetFunctionByNodeId(std::int32_t nodeId) const;
    inline bool GetFlag(ClassTypeSymbolFlags flag) const { return (flags & flag) != ClassTypeSymbolFlags::none; }
    inline void SetFlag(ClassTypeSymbolFlags flag) { flags = flags | flag; }
    inline void ResetFlag(ClassTypeSymbolFlags flag) { flags = flags & ~flag; }
    inline bool ObjectLayoutComputed() const { return GetFlag(ClassTypeSymbolFlags::objectLayoutComputed); }
    inline void SetObjectLayoutComputed() { SetFlag(ClassTypeSymbolFlags::objectLayoutComputed); }
    inline void ResetObjectLayoutComputed() { ResetFlag(ClassTypeSymbolFlags::objectLayoutComputed); }
    inline bool HasUserDefinedDestructor() const { return GetFlag(ClassTypeSymbolFlags::hasUserDefinedDestructor); }
    inline void SetHasUserDefinedDestructor() { SetFlag(ClassTypeSymbolFlags::hasUserDefinedDestructor); }
    inline bool HasUserDefinedConstructor() const { return GetFlag(ClassTypeSymbolFlags::hasUserDefinedConstructor); }
    inline void SetHasUserDefinedConstructor() { SetFlag(ClassTypeSymbolFlags::hasUserDefinedConstructor); }
    inline bool VTabInitialized() const { return GetFlag(ClassTypeSymbolFlags::vtabInitialized); }
    inline void SetVTabInitialized() { SetFlag(ClassTypeSymbolFlags::vtabInitialized); }
    inline const std::vector<FunctionSymbol*>& ConversionFunctions() const { return conversionFunctions; }
    FunctionSymbol* GetConversionFunction(TypeSymbol* type, Context* context) const;
    virtual ClassGroupSymbol* Group() const { return group; }
    inline void SetGroup(ClassGroupSymbol* group_) { group = group_; }
    bool IsComplete(std::set<const TypeSymbol*>& visited, const TypeSymbol*& incompleteType) const override;
    FunctionSymbol* CopyCtor() const { return copyCtor; }
    std::expected<bool, int> GenerateCopyCtor(const soul::ast::SourcePos& sourcePos, Context* context);
    void ResetCopyCtor() { copyCtor = nullptr; }
    std::expected<std::int64_t, int> Delta(ClassTypeSymbol* base, Emitter& emitter, Context* context);
    int TotalMemberCount() const;
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
    int Arity();
    inline ClassKind GetClassKind() const { return classKind; }
    inline void SetClassKind(ClassKind classKind_) { classKind = classKind_; }
    inline TypeSymbol* Specialization() const { return specialization; }
    inline void SetSpecialization(TypeSymbol* specialization_) { specialization = specialization_; }
    inline void SetClassTypeSymbol(ClassTypeSymbol* classTypeSymbol_) { classTypeSymbol = classTypeSymbol_; }
    inline ClassTypeSymbol* GetClassTypeSymbol() const { return classTypeSymbol; }
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration();
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    std::expected<TypeSymbol*, int> FinalType(const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<otava::intermediate::Type*, int> IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsComplete(std::set<const TypeSymbol*>& visited, const TypeSymbol*& incompleteType) const override;
    inline ClassGroupSymbol* Group() const { return group; }
    inline void SetGroup(ClassGroupSymbol* group_) { group = group_; }
private:
    ClassKind classKind;
    TypeSymbol* specialization;
    ClassTypeSymbol* classTypeSymbol;
    util::uuid classTypeSymbolId;
    ClassGroupSymbol* group;
};

std::expected<bool, int> BeginClass(otava::ast::Node* node, Context* context);
std::expected<bool, int> EndClass(otava::ast::Node* node, Context* context);
std::expected<bool, int> ProcessElaboratedClassDeclaration(otava::ast::Node* node, otava::symbols::Context* context);
void SetCurrentAccess(otava::ast::Node* node, otava::symbols::Context* context);
std::expected<bool, int> GetClassAttributes(otava::ast::Node* node, std::u32string& name, otava::symbols::ClassKind& kind, TypeSymbol*& specialization, Context* context);
std::expected<std::vector<ClassTypeSymbol*>, int> ResolveBaseClasses(otava::ast::Node* node, Context* context);
std::expected<bool, int> ParseInlineMemberFunctions(otava::ast::Node* classSpecifierNode, ClassTypeSymbol* classTypeSymbol, otava::symbols::Context* context);
std::expected<Symbol*, int> GenerateDestructor(ClassTypeSymbol* classTypeSymbol, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
std::expected<bool, int> GenerateDestructors(BoundCompileUnitNode* compileUnit, otava::symbols::Context* context);
std::unexpected<int> ReturnMemberDeclarationParsingError(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
std::unexpected<int> ReturnStatementParsingError(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);

struct ClassLess
{
    bool operator()(ClassTypeSymbol* left, ClassTypeSymbol* right) const;
};

std::expected<std::int64_t, int> Delta(ClassTypeSymbol* left, ClassTypeSymbol* right, Emitter& emitter, Context* context);

} // namespace otava::symbols
