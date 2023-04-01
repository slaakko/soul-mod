// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.classes;

import std.core;
import otava.symbols.scope;
import otava.symbols.type.symbol;
import otava.ast.node;
import otava.ast.statement;
import otava.ast.classes;

export namespace otava::symbols {

const int32_t undefinedIndex = 0;
const int32_t defaultCtorIndex = -1;
const int32_t copyCtorIndex = -2;
const int32_t moveCtorIndex = -3;
const int32_t copyAssignmentIndex = -4;
const int32_t moveAssignmentIndex = -5;
const int32_t destructorIndex = -6;

const int32_t vtabClassIdElementCount = 2;
const int32_t vtabFunctionSectionOffset = 2;

class FunctionDefinitionSymbol;
class ClassGroupSymbol;

enum class SpecialFunctionKind : int32_t;

int32_t GetSpecialFunctionIndex(SpecialFunctionKind specialFunctionKind);

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

enum class ClassTypeSymbolFlags : int32_t
{
    none = 0, objectLayoutComputed = 1 << 0, hasUserDefinedDestructor = 1 << 1, hasUserDefinedConstructor = 1 << 2, vtabInitialized = 1 << 3
};

constexpr ClassTypeSymbolFlags operator|(ClassTypeSymbolFlags left, ClassTypeSymbolFlags right)
{
    return static_cast<ClassTypeSymbolFlags>(int32_t(left) | int32_t(right));
}

constexpr ClassTypeSymbolFlags operator&(ClassTypeSymbolFlags left, ClassTypeSymbolFlags right)
{
    return static_cast<ClassTypeSymbolFlags>(int32_t(left) & int32_t(right));
}

constexpr ClassTypeSymbolFlags operator~(ClassTypeSymbolFlags flags)
{
    return static_cast<ClassTypeSymbolFlags>(~int32_t(flags));
}

class ClassTypeSymbol : public TypeSymbol
{
public:
    ClassTypeSymbol(const std::u32string& name_);
    ClassTypeSymbol(SymbolKind kind_, const std::u32string& name_);
    int Arity();
    ClassKind GetClassKind() const { return classKind; }
    void SetClassKind(ClassKind classKind_) { classKind = classKind_; }
    TypeSymbol* Specialization() const { return specialization; }
    void SetSpecialization(TypeSymbol* specialization_) { specialization = specialization_; }
    std::string SymbolKindStr() const override { return "class type symbol"; }
    std::string SymbolDocKindStr() const override { return "class"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    TemplateDeclarationSymbol* ParentTemplateDeclaration() const;
    bool IsTemplate() const;
    void MakeVTab(Context* context, const soul::ast::SourcePos& sourcePos);
    void InitVTab(std::vector<FunctionSymbol*>& vtab, Context* context, const soul::ast::SourcePos& sourcePos);
    const std::vector<FunctionSymbol*>& VTab() const { return vtab; }
    std::string IrName(Context* context) const override;
    const std::string& VTabName(Context* context) const { return vtabName; }
    void ComputeVTabName(Context* context);
    int32_t VPtrIndex() const { return vptrIndex; }
    void SetVPtrIndex(int32_t vptrIndex_) { vptrIndex = vptrIndex_; }
    otava::intermediate::Type* VPtrType(Emitter& emitter) const;
    otava::intermediate::Value* GetVTabVariable(Emitter& emitter, Context* context);
    ClassTypeSymbol* VPtrHolderClass() const;
    const std::vector<ClassTypeSymbol*>& BaseClasses() const { return baseClasses; }
    void AddBaseClass(ClassTypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context);
    const std::vector<ClassTypeSymbol*>& DerivedClasses() const { return derivedClasses; }
    void AddDerivedClass(ClassTypeSymbol* derivedClass);
    bool HasBaseClass(TypeSymbol* baseClass, int& distance) const override;
    bool HasPolymorphicBaseClass() const;
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    int Level() const { return level; }
    void SetLevel(int level_) { level = level_; }
    bool IsPolymorphic() const override;
    const std::vector<VariableSymbol*>& MemberVariables() const { return memberVariables; }
    const std::vector<FunctionSymbol*>& MemberFunctions() const { return memberFunctions; }
    std::vector<FunctionDefinitionSymbol*> MemFunDefSymbols() const { return memFunDefSymbols; }
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void AddMemFunDefSymbol(FunctionDefinitionSymbol* memFunDefSymbol);
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    const std::vector<TypeSymbol*>& ObjectLayout() const { return objectLayout; }
    void MakeObjectLayout(const soul::ast::SourcePos& sourcePos, Context* context);
    void MapFunction(FunctionSymbol* function);
    FunctionSymbol* GetFunction(int32_t functionIndex) const;
    int32_t NextFunctionIndex();
    bool GetFlag(ClassTypeSymbolFlags flag) const { return (flags & flag) != ClassTypeSymbolFlags::none; }
    void SetFlag(ClassTypeSymbolFlags flag) { flags = flags | flag; }
    void ResetFlag(ClassTypeSymbolFlags flag) { flags = flags & ~flag; }
    bool ObjectLayoutComputed() const { return GetFlag(ClassTypeSymbolFlags::objectLayoutComputed); }
    void SetObjectLayoutComputed() { SetFlag(ClassTypeSymbolFlags::objectLayoutComputed); }
    void ResetObjectLayoutComputed() { ResetFlag(ClassTypeSymbolFlags::objectLayoutComputed); }
    bool HasUserDefinedDestructor() const { return GetFlag(ClassTypeSymbolFlags::hasUserDefinedDestructor); }
    void SetHasUserDefinedDestructor() { SetFlag(ClassTypeSymbolFlags::hasUserDefinedDestructor); }
    bool HasUserDefinedConstructor() const { return GetFlag(ClassTypeSymbolFlags::hasUserDefinedConstructor); }
    void SetHasUserDefinedConstructor() { SetFlag(ClassTypeSymbolFlags::hasUserDefinedConstructor); }
    bool VTabInitialized() const { return GetFlag(ClassTypeSymbolFlags::vtabInitialized); }
    void SetVTabInitialized() { SetFlag(ClassTypeSymbolFlags::vtabInitialized); }
    const std::vector<FunctionSymbol*>& ConversionFunctions() const { return conversionFunctions; }
    FunctionSymbol* GetConversionFunction(TypeSymbol* type) const;
    ClassGroupSymbol* Group() const { return group; }
    void SetGroup(ClassGroupSymbol* group_) { group = group_; }
    bool IsComplete(std::set<const TypeSymbol*>& visited) const override;
    FunctionSymbol* CopyCtor() const { return copyCtor; }
    void GenerateCopyCtor(const soul::ast::SourcePos& sourcePos, Context* context);
private:
    ClassTypeSymbolFlags flags;
    std::vector<ClassTypeSymbol*> baseClasses;
    std::vector<util::uuid> baseClassIds;
    ClassKind classKind;
    TypeSymbol* specialization;
    util::uuid specializationId;
    std::vector<ClassTypeSymbol*> derivedClasses;
    int32_t level;
    std::vector<VariableSymbol*> memberVariables;
    std::vector<VariableSymbol*> staticMemberVariables;
    std::vector<FunctionSymbol*> memberFunctions;
    std::vector<FunctionDefinitionSymbol*> memFunDefSymbols;
    std::vector<TypeSymbol*> objectLayout;
    std::vector<util::uuid> objectLayoutIds;
    otava::intermediate::Type* irType;
    std::map<int32_t, FunctionSymbol*> functionMap;
    std::map<int32_t, util::uuid> functionIdMap;
    int32_t currentFunctionIndex;
    std::vector<FunctionSymbol*> vtab;
    int32_t vtabSize;
    int32_t vptrIndex;
    std::vector<FunctionSymbol*> conversionFunctions;
    ClassGroupSymbol* group;
    std::string vtabName;
    FunctionSymbol* copyCtor;
    std::vector<std::unique_ptr<Symbol>> tempVars;
};

class ForwardClassDeclarationSymbol : public TypeSymbol
{
public:
    ForwardClassDeclarationSymbol(const std::u32string& name_);
    int Arity();
    ClassKind GetClassKind() const { return classKind; }
    void SetClassKind(ClassKind classKind_) { classKind = classKind_; }
    TypeSymbol* Specialization() const { return specialization; }
    void SetSpecialization(TypeSymbol* specialization_) { specialization = specialization_; }
    void SetClassTypeSymbol(ClassTypeSymbol* classTypeSymbol_) { classTypeSymbol = classTypeSymbol_; }
    ClassTypeSymbol* GetClassTypeSymbol() const { return classTypeSymbol; }
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
private:
    ClassKind classKind;
    TypeSymbol* specialization;
    ClassTypeSymbol* classTypeSymbol;
    util::uuid classTypeSymbolId;
};

void BeginClass(otava::ast::Node* node, Context* context);
void EndClass(otava::ast::Node* node, Context* context);
void AddClassInfo(ClassTypeSymbol* classTypeSymbol, Context* context);
void AddForwardClassDeclaration(otava::ast::Node* node, otava::symbols::Context* context);
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

} // namespace otava::symbols
