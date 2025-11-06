// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.symbol.table;

import std;
import soul.ast.source.pos;
import otava.ast;
import otava.symbols.derivations;
import otava.symbols.lookup;
import otava.symbols.specialization.compare;
import otava.symbols.array.type.compare;
import otava.symbols.function.type.compare;
import otava.symbols.type_compare;
import util.uuid;
import class_info_index;

export namespace otava::symbols {

const int maxTemplateParameters = 16;
const int numCompoundTypeIds = 256;
const int maxLevels = 16;

enum class FunctionKind;
enum class FunctionQualifiers;
enum class EnumTypeKind;
enum class DeclarationFlags : std::int32_t;
enum class Linkage : std::int32_t;

enum class MapKind : std::int32_t
{
    none, nodeToSymbol = 1 << 0, symbolToNode = 1 << 1, both = nodeToSymbol | symbolToNode
};

constexpr MapKind operator|(MapKind left, MapKind right)
{
    return MapKind(int(left) | int(right));
}

constexpr MapKind operator&(MapKind left, MapKind right)
{
    return MapKind(int(left) & int(right));
}

constexpr MapKind operator~(MapKind kind)
{
    return MapKind(~int(kind));
}

enum class FundamentalTypeKind : std::int32_t;
enum class ClassKind;
enum class Access : std::int32_t;

class Context;
class Module;
class Symbol;
class BlockSymbol;
class Scope;
class AliasTypeSymbol;
class AliasGroupSymbol;
class AliasGroupTypeSymbol;
class ArrayTypeSymbol;
class BoundExpressionNode;
class ClassTypeSymbol;
class ClassGroupSymbol;
class ClassGroupTypeSymbol;
class ConceptSymbol;
class EnumeratedTypeSymbol;
class FunctionTypeSymbol;
class FunctionGroupSymbol;
class FunctionGroupTypeSymbol;
class ClassTemplateSpecializationSymbol;
class AliasTypeTemplateSpecializationSymbol;
class CompoundTypeSymbol;
class ExplicitInstantiationSymbol;
class NamespaceSymbol;
class TypeSymbol;
class FundamentalTypeSymbol;
class FunctionSymbol;
class FunctionDefinitionSymbol;
class ParameterSymbol;
class Value;
class VariableSymbol;
class Reader;
class Writer;
class Visitor;
class ConversionTable;
class FunctionDefinitionSymbolSet;
class DependentTypeSymbol;
class SymbolMap;

enum class SymbolGroupKind : std::int32_t;

void SetProjectReady(bool projectReady_);

struct ClassTemplateNameLess
{
    bool operator()(ClassTemplateSpecializationSymbol* left, ClassTemplateSpecializationSymbol* right) const;
};

class SymbolTable
{
public:
    SymbolTable();
    inline void SetModule(Module* module_) { module = module_; }
    inline Module* GetModule() const { return module; }
    inline NamespaceSymbol* GlobalNs() const { return globalNs.get(); }
    void Init();
    void Import(const SymbolTable& that, FunctionDefinitionSymbolSet* functionDefinitionSymbolSet);
    void Write(Writer& writer, Context* context);
    void Read(Reader& reader);
    void Resolve(Context* context);
    void Accept(Visitor& visitor);
    void WriteMaps(Writer& writer, Context* context);
    void ReadMaps(Reader& reader, otava::ast::NodeMap* nodeMap);
    TypeSymbol* GetFundamentalTypeSymbol(FundamentalTypeKind kind);
    inline Symbol* GetTypenameConstraintSymbol() { return typenameConstraintSymbol; }
    inline void SetTypenameConstraintSymbol(Symbol* typenameConstraintSymbol_) { typenameConstraintSymbol = typenameConstraintSymbol_; }
    inline TypeSymbol* GetErrorTypeSymbol() { return errorTypeSymbol; }
    inline void SetErrorTypeSymbol(TypeSymbol* errorTypeSymbol_) { errorTypeSymbol = errorTypeSymbol_; }
    inline Scope* CurrentScope() const { return currentScope; }
    void SetCurrentScope(Scope* scope);
    Scope* GetNamespaceScope(const std::u32string& nsName, const soul::ast::SourcePos& sourcePos, Context* context);
    void PushScope();
    void PopScope();
    void BeginScope(Scope* scope);
    void EndScope();
    void BeginScopeGeneric(Scope* scope, Context* context);
    void EndScopeGeneric(Context* context);
    void PushTopScopeIndex();
    void PopTopScopeIndex();
    void SetTopScopeIndex(int topScopeIndex_) { topScopeIndex = topScopeIndex_; }
    inline int TopScopeIndex() const { return topScopeIndex; }
    void BeginNamespace(const std::u32string& name, otava::ast::Node* node, Context* context);
    void EndNamespace();
    void BeginNamespace(otava::ast::Node* node, Context* context);
    void EndNamespace(int level);
    void BeginClass(const std::u32string& name, ClassKind classKind, TypeSymbol* spcialiation, otava::ast::Node* node, Context* context);
    void AddBaseClass(ClassTypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context);
    void EndClass();
    void AddForwardClassDeclaration(const std::u32string& name, ClassKind classKind, TypeSymbol* specialization, otava::ast::Node* node, Context* context);
    void AddFriend(const std::u32string& name, otava::ast::Node* node, Context* context);
    void BeginEnumeratedType(const std::u32string& name, EnumTypeKind kind, TypeSymbol* underlyingType, otava::ast::Node* node, Context* context);
    void EndEnumeratedType();
    void AddForwardEnumDeclaration(const std::u32string& name, EnumTypeKind enumTypeKind, TypeSymbol* underlyingType, otava::ast::Node* node, Context* context);
    void AddEnumerator(const std::u32string& name, Value* value, otava::ast::Node* node, Context* context);
    BlockSymbol* BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context);
    void EndBlock(Context* context);
    void RemoveBlock();
    void BeginTemplateDeclaration(otava::ast::Node* node, Context* context);
    void EndTemplateDeclaration();
    void RemoveTemplateDeclaration();
    void AddTemplateParameter(const std::u32string& name, otava::ast::Node* node, Symbol* constraint, int index, ParameterSymbol* parameter, 
        otava::ast::Node* defaultTemplateArgNode, Context* context);
    FunctionSymbol* AddFunction(const std::u32string& name, const std::vector<TypeSymbol*>& specialization, otava::ast::Node* node, FunctionKind kind, 
        FunctionQualifiers qualifiers, DeclarationFlags flags, Context* context);
    void AddFunctionSymbol(Scope* scope, FunctionSymbol* functionSymbol, Context* context);
    FunctionDefinitionSymbol* AddOrGetFunctionDefinition(Scope* scope, const std::u32string& name, const std::vector<TypeSymbol*>& specialization,
        const std::vector<TypeSymbol*>& parameterTypes, FunctionQualifiers qualifiers, FunctionKind kind, DeclarationFlags declarationFlags, 
        otava::ast::Node* node, otava::ast::Node* functionNode, bool& get, Context* context);
    ParameterSymbol* CreateParameter(const std::u32string& name, otava::ast::Node* node, TypeSymbol* type, Context* context);
    VariableSymbol* AddVariable(const std::u32string& name, otava::ast::Node* node, TypeSymbol* declaredType, TypeSymbol* type, 
        Value* value, DeclarationFlags flags, Context* context);
    AliasTypeSymbol* AddAliasType(otava::ast::Node* idNnode, otava::ast::Node* aliasTypeNode, TypeSymbol* type, Context* context);
    void AddUsingDeclaration(otava::ast::Node* node, Symbol* symbol, Context* context);
    void AddUsingDirective(NamespaceSymbol* ns, otava::ast::Node* node, Context* context);
    TypeSymbol* MakeCompoundType(TypeSymbol* baseType, Derivations derivations, Context* context);
    void AddCompoundType(CompoundTypeSymbol* compoundType);
    void MapCompoundType(CompoundTypeSymbol* compoundType);
    CompoundTypeSymbol* GetCompoundType(const util::uuid& compoundTypeId) const;
    TypeSymbol* MakeConstCharPtrType(Context* context);
    TypeSymbol* MakeConstChar8PtrType(Context* context);
    TypeSymbol* MakeConstChar16PtrType(Context* context);
    TypeSymbol* MakeConstChar32PtrType(Context* context);
    TypeSymbol* MakeConstWCharPtrType(Context* context);
    FunctionTypeSymbol* MakeFunctionTypeSymbol(FunctionSymbol* functionSymbol);
    FunctionGroupTypeSymbol* MakeFunctionGroupTypeSymbol(FunctionGroupSymbol* functionGroup);
    ClassGroupTypeSymbol* MakeClassGroupTypeSymbol(ClassGroupSymbol* classGroup);
    AliasGroupTypeSymbol* MakeAliasGroupTypeSymbol(AliasGroupSymbol* aliasGroup);
    ConceptSymbol* AddConcept(const std::u32string& name, otava::ast::Node* node, Context* context);
    ClassTemplateSpecializationSymbol* MakeClassTemplateSpecialization(ClassTypeSymbol* classTemplate, const std::vector<Symbol*>& templateArguments,
        const soul::ast::SourcePos& sourcePos, Context* context);
    AliasTypeTemplateSpecializationSymbol* MakeAliasTypeTemplateSpecialization(TypeSymbol* aliasTypeTemplate, const std::vector<Symbol*>& templateArguments);
    ArrayTypeSymbol* MakeArrayType(TypeSymbol* elementType, std::int64_t size);
    DependentTypeSymbol* MakeDependentTypeSymbol(otava::ast::Node* node);
    Symbol* Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context);
    Symbol* Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags);
    Symbol* LookupInScopeStack(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags);
    Symbol* LookupSymbol(Symbol* symbol);
    void ResolveForwardDeclarations();
    void CollectViableFunctions(const std::vector<std::pair<Scope*, ScopeLookup>>& scopeLookups, const std::u32string& groupName, const std::vector<TypeSymbol*>& templateArgs, 
        int arity, std::vector<FunctionSymbol*>& viableFunctions, Context* context);
    void MapNode(otava::ast::Node* node);
    void MapNode(otava::ast::Node* node, Symbol* symbol);
    void MapNode(otava::ast::Node* node, Symbol* symbol, MapKind kind);
    otava::ast::Node* GetNodeNothrow(Symbol* symbol) const;
    otava::ast::Node* GetNode(Symbol* symbol) const;
    void RemoveNode(otava::ast::Node* node);
    void RemoveSymbol(Symbol* symbol);
    otava::ast::Node* GetSpecifierNode(Symbol* symbol) const;
    void SetSpecifierNode(Symbol* symbol, otava::ast::Node* node);
    Symbol* GetSymbolNothrow(otava::ast::Node* node) const;
    Symbol* GetSymbol(otava::ast::Node* node) const;
    TypeSymbol* GetTypeNoThrow(const util::uuid& id) const;
    TypeSymbol* GetType(const util::uuid& id) const;
    void MapType(TypeSymbol* type);
    void UnmapType(TypeSymbol* type);
    void MapFundamentalType(FundamentalTypeSymbol* fundamentalTypeSymbol);
    void MapFunction(FunctionSymbol* function);
    void MapFunctionDefinition(FunctionDefinitionSymbol* functionDefinition);
    void MapVariable(VariableSymbol* variable);
    void MapConstraint(Symbol* constraint);
    void MapFunctionGroup(FunctionGroupSymbol* functionGroup);
    void MapClassGroup(ClassGroupSymbol* classGroup);
    void MapAliasGroup(AliasGroupSymbol* aliasGroup);
    void MapConcept(ConceptSymbol* cncp);
    FunctionSymbol* GetFunction(const util::uuid& id) const;
    FunctionDefinitionSymbol* GetFunctionDefinition(const util::uuid& id) const;
    AliasTypeSymbol* GetAliasType(const util::uuid& id) const;
    ClassTypeSymbol* GetClass(const util::uuid& id) const;
    VariableSymbol* GetVariable(const util::uuid& id) const;
    ConceptSymbol* GetConcept(const util::uuid& id) const;
    Symbol* GetConstraint(const util::uuid& id) const;
    FunctionGroupSymbol* GetFunctionGroup(const util::uuid& id) const;
    ClassGroupSymbol* GetClassGroup(const util::uuid& id) const;
    AliasGroupSymbol* GetAliasGroup(const util::uuid& id) const;
    TypeSymbol* GetFundamentalType(FundamentalTypeKind kind) const;
    inline void SetAddToRecomputeNameSet(bool addToRecomputeNameSet_) { addToRecomputeNameSet = addToRecomputeNameSet_; }
    inline bool AddToRecomputeNameSet() const { return addToRecomputeNameSet; }
    void AddToRecomputeNameSet(CompoundTypeSymbol* compoundTypeSymbol);
    void RecomputeNames();
    inline const std::set<Symbol*>& ForwardDeclarations() const { return forwardDeclarations; }
    inline const std::set<Symbol*>& AllForwardDeclarations() const { return allForwardDeclarations; }
    inline std::set<Symbol*>& ForwardDeclarations() { return forwardDeclarations; }
    inline std::set<Symbol*>& AllForwardDeclarations() { return allForwardDeclarations; }
    inline Access CurrentAccess() const { return currentAccess; }
    void SetCurrentAccess(Access access);
    void PushAccess(Access access);
    void PopAccess();
    void AddClass(ClassTypeSymbol* cls);
    inline const std::set<ClassTypeSymbol*>& Classes() const { return allClasses; }
    inline void SetNodeMap(otava::ast::NodeMap* nodeMap_) { nodeMap = nodeMap_; }
    inline otava::ast::NodeMap* GetNodeMap() { return nodeMap; }
    inline void SetSymbolMap(SymbolMap* symbolMap_) { symbolMap = symbolMap_; }
    inline SymbolMap* GetSymbolMap() const { return symbolMap; }
    inline ConversionTable& GetConversionTable() { return *conversionTable; }
    inline const ConversionTable& GetConversionTable() const { return *conversionTable; }
    inline Linkage CurrentLinkage() const { return currentLinkage; }
    void PushLinkage(Linkage linkage_);
    void PopLinkage();
    ExplicitInstantiationSymbol* GetExplicitInstantiation(ClassTemplateSpecializationSymbol* classTemplateSpecialization) const;
    void AddExplicitInstantiation(ExplicitInstantiationSymbol* explicitInstantition);
    void MapExplicitInstantiation(ExplicitInstantiationSymbol* explicitInstantition);
    const info::class_index& ClassIndex() const { return index; }
    info::class_index& ClassIndex() { return index; }
    ClassTemplateSpecializationSymbol* GetClassTemplateSpecialization(const util::uuid& id) const;
    void AddClassTemplateSpecialization(ClassTemplateSpecializationSymbol* sp);
    void MapClassTemplateSpecialization(ClassTemplateSpecializationSymbol* sp);
    void AddChangedClassTemplateSpecialization(ClassTemplateSpecializationSymbol* sp);
    void UnmapClassTemplateSpecialization(ClassTemplateSpecializationSymbol* sp);
    void AddAliasTypeTemplateSpecializationToSet(AliasTypeTemplateSpecializationSymbol* at);
    void AddArrayTypeToSet(ArrayTypeSymbol* a);
    void ImportAfterResolve();
    void ToXml(const std::string& xmlFilePath) const;
    void InitTemplateParameterIds();
    void InitCompoundTypeIds();
    void InitLevelIds();
    const util::uuid& GetTemplateParameterId(int index) const;
    const util::uuid& GetCompoundTypeId(int index) const;
    const util::uuid& GetLevelId(int level) const;
private:
    void CreateFundamentalTypes();
    void AddFundamentalType(FundamentalTypeKind kind);
    void CreateCoreSymbols();
    void AddFundamentalTypeOperations();
    void ImportSpecializations(const SymbolTable& that);
    void ImportArrayTypes(const SymbolTable& that);
    void ImportDependentTypes(const SymbolTable& that);
    void ImportCompoundTypeMap(const SymbolTable& that, Context* context);
    void ImportFundamentalTypeMap(const SymbolTable& that);
    void ImportNodeSymbolMap(const SymbolTable& that);
    void ImportSymbolNodeMap(const SymbolTable& that);
    void ImportTypeMap(const SymbolTable& that);
    void ImportFunctionMap(const SymbolTable& that);
    void ImportFunctionDefinitionMap(const SymbolTable& that);
    void ImportVariableMap(const SymbolTable& that);
    void ImportConceptMap(const SymbolTable& that);
    void ImportConstraintMap(const SymbolTable& that);
    void ImportForwardDeclarations(const SymbolTable& that);
    void ImportSpecifierMap(const SymbolTable& that);
    void ImportClasses(const SymbolTable& that);
    void ImportExplicitInstantiations(const SymbolTable& that);
    void ImportFunctionGroupTypes(const SymbolTable& that);
    void ImportClassGroups(const SymbolTable& that);
    void ImportAliasGroups(const SymbolTable& that);
    void ImportClassGroupTypes(const SymbolTable& that);
    void ImportAliasGroupTypes(const SymbolTable& that);
    void ImportClassIndex(const SymbolTable& that);
    void AddImportAfterResolve(const SymbolTable* that);
    Module* module;
    std::unique_ptr<NamespaceSymbol> globalNs;
    std::vector<std::unique_ptr<Symbol>> classTemplateSpecializations;
    std::set<ClassTemplateSpecializationSymbol*> changedClassTemplateSpecializations;
    std::vector<std::unique_ptr<Symbol>> aliasTypeTemplateSpecializations;
    std::map<util::uuid, ClassTemplateSpecializationSymbol*> classTemplateSpecializationMap;
    std::set<AliasTypeTemplateSpecializationSymbol*, AliasTypeTemplateSpecializationLess> aliasTypeTemplateSpecializationSet;
    std::vector<std::unique_ptr<Symbol>> arrayTypes;
    std::set<ArrayTypeSymbol*, ArrayTypeLess> arrayTypeSet;
    std::set<DependentTypeSymbol*> dependentTypeSet;
    std::vector<std::unique_ptr<CompoundTypeSymbol>> compoundTypes;
    std::map<util::uuid, CompoundTypeSymbol*> compoundTypeMap;
    std::vector<std::unique_ptr<ExplicitInstantiationSymbol>> explicitInstantiations;
    std::map<ClassTemplateSpecializationSymbol*, ExplicitInstantiationSymbol*, ClassTemplateNameLess> explicitInstantiationMap;
    std::vector<std::unique_ptr<FunctionGroupTypeSymbol>> functionGroupTypes;
    std::map<FunctionGroupSymbol*, FunctionGroupTypeSymbol*> functionGroupTypeMap;
    std::vector<std::unique_ptr<ClassGroupTypeSymbol>> classGroupTypes;
    std::map<ClassGroupSymbol*, ClassGroupTypeSymbol*> classGroupTypeMap;
    std::vector<std::unique_ptr<AliasGroupTypeSymbol>> aliasGroupTypes;
    std::map<AliasGroupSymbol*, AliasGroupTypeSymbol*> aliasGroupTypeMap;
    std::map<std::int32_t, TypeSymbol*> fundamentalTypeMap;
    std::vector<std::unique_ptr<Symbol>> functionTypes;
    std::set<FunctionTypeSymbol*, FunctionTypeCompare> functionTypeSet;
    std::vector<Scope*> scopeStack;
    Scope* currentScope;
    std::map<otava::ast::Node*, Symbol*> nodeSymbolMap;
    std::map<otava::ast::Node*, Symbol*> allNodeSymbolMap;
    std::map<Symbol*, otava::ast::Node*> symbolNodeMap;
    std::map<Symbol*, otava::ast::Node*> allSymbolNodeMap;
    std::map<Symbol*, otava::ast::Node*> specifierNodeMap;
    std::map<Symbol*, otava::ast::Node*> allSpecifierNodeMap;
    std::map<util::uuid, TypeSymbol*> typeMap;
    std::map<util::uuid, FunctionSymbol*> functionMap;
    std::map<util::uuid, FunctionDefinitionSymbol*> functionDefinitionMap;
    std::map<util::uuid, VariableSymbol*> variableMap;
    std::map<util::uuid, Symbol*> constraintMap;
    std::map<util::uuid, FunctionGroupSymbol*> functionGroupMap;
    std::map<util::uuid, ClassGroupSymbol*> classGroupMap;
    std::map<util::uuid, AliasGroupSymbol*> aliasGroupMap;
    std::map<util::uuid, ConceptSymbol*> conceptMap;
    std::vector<std::unique_ptr<DependentTypeSymbol>> dependentTypeSymbols;
    Symbol* typenameConstraintSymbol;
    TypeSymbol* errorTypeSymbol;
    int topScopeIndex;
    std::stack<int> topScopeIndexStack;
    bool addToRecomputeNameSet;
    std::set<CompoundTypeSymbol*> recomputeNameSet;
    std::set<Symbol*> forwardDeclarations;
    std::set<Symbol*> allForwardDeclarations;
    Access currentAccess;
    std::stack<Access> accessStack;
    otava::ast::NodeMap* nodeMap;
    SymbolMap* symbolMap;
    std::set<ClassTypeSymbol*> classes;
    std::set<ClassTypeSymbol*> allClasses;
    int classLevel;
    std::unique_ptr<ConversionTable> conversionTable;
    Linkage currentLinkage;
    std::stack<Linkage> linkageStack;
    std::vector<ParameterSymbol*> returnValueParametersToResolve;
    info::class_index index;
    std::vector<const SymbolTable*> importAfterResolve;
    std::vector<util::uuid> templateParameterIds;
    std::vector<util::uuid> compoundTypeIds;
    std::vector<util::uuid> levelIds;
};

} // namespace otava::symbols
