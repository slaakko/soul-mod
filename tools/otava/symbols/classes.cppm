// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.classes;

import std;
import otava.symbols.scope;
import otava.symbols.type.symbol;
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

enum class SpecialFunctionKind : std::int32_t;

std::int32_t GetSpecialFunctionIndex(SpecialFunctionKind specialFunctionKind);

using RecordedParseCompoundStatementFn = void (*)(otava::ast::CompoundStatementNode* compoundStatementNode, Context* context);

void SetRecordedParseCompoundStatementFn(RecordedParseCompoundStatementFn fn);

using RecordedParseCtorInitializerFn = void (*)(otava::ast::ConstructorInitializerNode* ctorInitializerNode, Context* context);

void SetRecordedParseCtorInitializerFn(RecordedParseCtorInitializerFn fn);

class TemplateDeclarationSymbol;
class TemplateParameterSymbol;
class BoundCompileUnitNode;

enum class ClassKind
{
    class_, struct_, union_
};

enum class ClassTypeSymbolFlags : std::int32_t
{
    none = 0, objectLayoutComputed = 1 << 0, hasUserDefinedDestructor = 1 << 1, hasUserDefinedConstructor = 1 << 2, vtabInitialized = 1 << 3, vtabGenerated = 1 << 4,
    resolved = 1 << 5
};

constexpr ClassTypeSymbolFlags operator|(ClassTypeSymbolFlags left, ClassTypeSymbolFlags right)
{
    return static_cast<ClassTypeSymbolFlags>(std::int32_t(left) | std::int32_t(right));
}

constexpr ClassTypeSymbolFlags operator&(ClassTypeSymbolFlags left, ClassTypeSymbolFlags right)
{
    return static_cast<ClassTypeSymbolFlags>(std::int32_t(left) & std::int32_t(right));
}

constexpr ClassTypeSymbolFlags operator~(ClassTypeSymbolFlags flags)
{
    return static_cast<ClassTypeSymbolFlags>(~std::int32_t(flags));
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
    std::string SymbolKindStr() const override { return "class type symbol"; }
    std::string SymbolDocKindStr() const override { return "class"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration() const;
    bool IsTemplate() const;
    void MakeVTab(Context* context, const soul::ast::SourcePos& sourcePos);
    void InitVTab(std::vector<FunctionSymbol*>& vtab, Context* context, const soul::ast::SourcePos& sourcePos, bool clear);
    inline const std::vector<FunctionSymbol*>& VTab() const { return vtab; }
    std::string IrName(Context* context) const override;
    inline const std::string& VTabName(Context* context) const { return vtabName; }
    void ComputeVTabName(Context* context);
    inline std::int32_t VPtrIndex() const { return vptrIndex; }
    inline void SetVPtrIndex(std::int32_t vptrIndex_) { vptrIndex = vptrIndex_; }
    inline std::int32_t DeltaIndex() const { return deltaIndex; }
    inline void SetDeltaIndex(std::int32_t deltaIndex_) { deltaIndex = deltaIndex_; }
    otava::intermediate::Type* VPtrType(Emitter& emitter) const;
    otava::intermediate::Value* GetVTabVariable(Emitter& emitter, Context* context);
    std::vector<ClassTypeSymbol*> VPtrHolderClasses() const;
    inline const std::vector<ClassTypeSymbol*>& BaseClasses() const { return baseClasses; }
    void AddBaseClass(ClassTypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context);
    inline const std::vector<ClassTypeSymbol*>& DerivedClasses() const { return derivedClasses; }
    void AddDerivedClass(ClassTypeSymbol* derivedClass);
    bool HasBaseClass(TypeSymbol* baseClass, int& distance) const override;
    bool HasPolymorphicBaseClass() const;
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    inline int Level() const { return level; }
    inline void SetLevel(int level_) { level = level_; }
    bool IsPolymorphic() const override;
    inline const std::vector<VariableSymbol*>& MemberVariables() const { return memberVariables; }
    inline const std::vector<FunctionSymbol*>& MemberFunctions() const { return memberFunctions; }
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void SetMemFnDefSymbol(FunctionDefinitionSymbol* memFnDefSymbol);
    FunctionDefinitionSymbol* GetMemFnDefSymbol(int32_t defIndex) const;
    const std::map<std::int32_t, FunctionDefinitionSymbol*>& MemFnDefSymbolMap() const { return memFnDefSymbolMap; }
    inline void SetNextMemFnDefIndex(int32_t defIndex) { nextMemFnDefIndex = std::max(defIndex, nextMemFnDefIndex); }
    inline int32_t NextMemFnDefIndex() const { return nextMemFnDefIndex; }
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline const std::vector<TypeSymbol*>& ObjectLayout() const { return objectLayout; }
    void MakeObjectLayout(const soul::ast::SourcePos& sourcePos, Context* context);
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
    FunctionSymbol* GetConversionFunction(TypeSymbol* type) const;
    virtual ClassGroupSymbol* Group() const { return group; }
    inline void SetGroup(ClassGroupSymbol* group_) { group = group_; }
    bool IsComplete(std::set<const TypeSymbol*>& visited) const override;
    inline FunctionSymbol* CopyCtor() const { return copyCtor; }
    void GenerateCopyCtor(const soul::ast::SourcePos& sourcePos, Context* context);
    void ResetCopyCtor() { copyCtor = nullptr; }
    std::pair<bool, std::int64_t> Delta(ClassTypeSymbol* base, Emitter& emitter, Context* context);
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
    std::string SymbolKindStr() const override { return "forward class declaration symbol"; }
    std::string SymbolDocKindStr() const override { return "forward_class"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration();
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    TypeSymbol* FinalType(const soul::ast::SourcePos& sourcePos, Context* context) override;
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsComplete(std::set<const TypeSymbol*>& visited) const override;
    inline ClassGroupSymbol* Group() const { return group; }
    inline void SetGroup(ClassGroupSymbol* group_) { group = group_; }
private:
    ClassKind classKind;
    TypeSymbol* specialization;
    ClassTypeSymbol* classTypeSymbol;
    util::uuid classTypeSymbolId;
    ClassGroupSymbol* group;
};

void BeginClass(otava::ast::Node* node, Context* context);
void EndClass(otava::ast::Node* node, Context* context);
void AddClassInfo(ClassTypeSymbol* classTypeSymbol, Context* context);
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
    bool operator()(ClassTypeSymbol* left, ClassTypeSymbol* right) const;
};

std::pair<bool, std::int64_t> Delta(ClassTypeSymbol* left, ClassTypeSymbol* right, Emitter& emitter, Context* context);

} // namespace otava::symbols
