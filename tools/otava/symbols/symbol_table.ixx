// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.symbol.table;

import std.core;
import soul.ast.source.pos;
import otava.ast;
import otava.symbols.derivations;
import otava.symbols.lookup;
import otava.symbols.specialization.compare;
import otava.symbols.symbol_map;
import util.uuid;

export namespace otava::symbols {

enum class FunctionKind;
enum class FunctionQualifiers;
enum class EnumTypeKind;
enum class DeclarationFlags : int32_t;

enum class MapKind : int32_t
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

enum class FundamentalTypeKind : int32_t;
enum class ClassKind;
enum class Access : int32_t;

class Context;
class Module;
class Symbol;
class Scope;
class AliasTypeSymbol;
class ClassTypeSymbol;
class ConceptSymbol;
class EnumeratedTypeSymbol;
class SpecializationSymbol;
class CompoundTypeSymbol;
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

enum class SymbolGroupKind : int32_t;

class SymbolTable
{
public:
    SymbolTable();
    void SetModule(Module* module_) { module = module_; }
    Module* GetModule() const { return module; }
    NamespaceSymbol* GlobalNs() const { return globalNs.get(); }
    void Init();
    void Import(const SymbolTable& that);
    void Write(Writer& writer);
    void Read(Reader& reader);
    void Resolve();
    void Accept(Visitor& visitor);
    void WriteMaps(Writer& writer);
    void ReadMaps(Reader& reader, otava::ast::NodeMap* nodeMap, SymbolMap* symbolMap);
    TypeSymbol* GetFundamentalTypeSymbol(FundamentalTypeKind kind);
    Symbol* GetTypenameConstraintSymbol() { return typenameConstraintSymbol; }
    void SetTypenameConstraintSymbol(Symbol* typenameConstraintSymbol_) { typenameConstraintSymbol = typenameConstraintSymbol_; }
    TypeSymbol* GetErrorTypeSymbol() { return errorTypeSymbol; }
    void SetErrorTypeSymbol(TypeSymbol* errorTypeSymbol_) { errorTypeSymbol = errorTypeSymbol_; }
    Scope* CurrentScope() const { return currentScope; }
    void SetCurrentScope(Scope* scope);
    void PushScope();
    void PopScope();
    void BeginScope(Scope* scope);
    void EndScope();
    void PushTopScopeIndex();
    void PopTopScopeIndex();
    void BeginNamespace(const std::u32string& name, otava::ast::Node* node, Context* context);
    void EndNamespace();
    void BeginNamespace(otava::ast::Node* node, Context* context);
    void EndNamespace(int level);
    void BeginClass(const std::u32string& name, ClassKind classKind, otava::ast::Node* node, Context* context);
    void AddBaseClass(TypeSymbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context);
    void EndClass();
    void AddForwardClassDeclaration(const std::u32string& name, ClassKind classKind, otava::ast::Node* node, Context* context);
    void BeginEnumeratedType(const std::u32string& name, EnumTypeKind kind, TypeSymbol* underlyingType, otava::ast::Node* node, Context* context);
    void EndEnumeratedType();
    void AddForwardEnumDeclaration(const std::u32string& name, EnumTypeKind enumTypeKind, TypeSymbol* underlyingType, otava::ast::Node* node, Context* context);
    void AddEnumerator(const std::u32string& name, Value* value, otava::ast::Node* node, Context* context);
    void BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context);
    void EndBlock();
    void RemoveBlock();
    void BeginTemplateDeclaration(otava::ast::Node* node, Context* context);
    void EndTemplateDeclaration();
    void RemoveTemplateDeclaration();
    void AddTemplateParameter(const std::u32string& name, otava::ast::Node* node, Symbol* constraint, int index, ParameterSymbol* parameter, 
        otava::ast::Node* defaultTemplateArgNode, Context* context);
    FunctionSymbol* AddFunction(const std::u32string& name, otava::ast::Node* node, FunctionKind kind, FunctionQualifiers qualifiers, DeclarationFlags flags, Context* context);
    void AddFunctionSymbol(Scope* scope, FunctionSymbol* functionSymbol, Context* context);
    FunctionDefinitionSymbol* AddFunctionDefinition(Scope* scope, const std::u32string& name, const std::vector<TypeSymbol*>& paramterTypes, 
        FunctionQualifiers qualifiers, otava::ast::Node* node, FunctionSymbol* declaration, Context* context);
    ParameterSymbol* CreateParameter(const std::u32string& name, otava::ast::Node* node, TypeSymbol* type, Context* context);
    VariableSymbol* AddVariable(const std::u32string& name, otava::ast::Node* node, TypeSymbol* declaredType, TypeSymbol* type, 
        Value* value, DeclarationFlags flags, Context* context);
    void AddAliasType(otava::ast::Node* node, TypeSymbol* type, Context* context);
    void AddUsingDeclaration(otava::ast::Node* node, Symbol* symbol, Context* context);
    void AddUsingDirective(NamespaceSymbol* ns, otava::ast::Node* node, Context* context);
    TypeSymbol* MakeCompoundType(TypeSymbol* baseType, const Derivations& derivations);
    TypeSymbol* MakeConstCharPtrType();
    TypeSymbol* MakeConstChar8PtrType();
    TypeSymbol* MakeConstChar16PtrType();
    TypeSymbol* MakeConstChar32PtrType();
    TypeSymbol* MakeConstWCharPtrType();
    ConceptSymbol* AddConcept(const std::u32string& name, otava::ast::Node* node, Context* context);
    SpecializationSymbol* MakeSpecialization(TypeSymbol* classTemplate, const std::vector<Symbol*>& templateArguments);
    Symbol* Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context);
    Symbol* Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags);
    Symbol* LookupInScopeStack(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags);
    Symbol* LookupSymbol(Symbol* symbol);
    void CollectViableFunctions(Scope* scope, const std::u32string& groupName, int arity, std::vector<FunctionSymbol*>& viableFunctions, Context* context);
    void MapNode(otava::ast::Node* node);
    void MapNode(otava::ast::Node* node, Symbol* symbol);
    void MapNode(otava::ast::Node* node, Symbol* symbol, MapKind kind);
    otava::ast::Node* GetNodeNothrow(Symbol* symbol) const;
    otava::ast::Node* GetNode(Symbol* symbol) const;
    void RemoveNode(otava::ast::Node* node);
    otava::ast::Node* GetSpecifierNode(Symbol* symbol) const;
    void SetSpecifierNode(Symbol* symbol, otava::ast::Node* node);
    Symbol* GetSymbolNothrow(otava::ast::Node* node) const;
    Symbol* GetSymbol(otava::ast::Node* node) const;
    TypeSymbol* GetTypeNothrow(const util::uuid& id) const;
    TypeSymbol* GetType(const util::uuid& id) const;
    void MapType(TypeSymbol* type);
    void MapFundamentalType(FundamentalTypeSymbol* fundamentalTypeSymbol);
    void MapFunction(FunctionSymbol* function);
    void MapFunctionDefinition(FunctionDefinitionSymbol* functionDefinition);
    void MapVariable(VariableSymbol* variable);
    void MapConstraint(Symbol* constraint);
    FunctionSymbol* GetFunction(const util::uuid& id) const;
    FunctionDefinitionSymbol* GetFunctionDefinition(const util::uuid& id) const;
    AliasTypeSymbol* GetAliasType(const util::uuid& id) const;
    ClassTypeSymbol* GetClass(const util::uuid& id) const;
    VariableSymbol* GetVariable(const util::uuid& id) const;
    Symbol* GetConstraint(const util::uuid& id) const;
    TypeSymbol* GetFundamentalType(FundamentalTypeKind kind) const;
    void SetAddToRecomputeNameSet(bool addToRecomputeNameSet_) { addToRecomputeNameSet = addToRecomputeNameSet_; }
    bool AddToRecomputeNameSet() const { return addToRecomputeNameSet; }
    void AddToRecomputeNameSet(CompoundTypeSymbol* compoundTypeSymbol);
    void RecomputeNames();
    const std::set<Symbol*>& ForwardDeclarations() const { return forwardDeclarations; }
    const std::set<Symbol*>& AllForwardDeclarations() const { return allForwardDeclarations; }
    Access CurrentAccess() const { return currentAccess; }
    void SetCurrentAccess(Access access);
    void PushAccess(Access access);
    void PopAccess();
    void AddClass(ClassTypeSymbol* cls);
    const std::set<ClassTypeSymbol*>& Classes() const { return allClasses; }
    void SetNodeMap(otava::ast::NodeMap* nodeMap_) { nodeMap = nodeMap_; }
    otava::ast::NodeMap* GetNodeMap() { return nodeMap; }
    void SetSymbolMap(SymbolMap* symbolMap_) { symbolMap = symbolMap_; }
    SymbolMap* GetSymbolMap() { return symbolMap; }
    ConversionTable& GetConversionTable() { return *conversionTable; }
    const ConversionTable& GetConversionTable() const { return *conversionTable; }
private:
    void CreateFundamentalTypes();
    void AddFundamentalType(FundamentalTypeKind kind);
    void CreateCoreSymbols();
    void AddFundamentalTypeOperations();
    void ImportSpecializations();
    void ImportCompoundTypeMap(const SymbolTable& that);
    void ImportFundamentalTypeMap(const SymbolTable& that);
    void ImportNodeSymbolMap(const SymbolTable& that);
    void ImportSymbolNodeMap(const SymbolTable& that);
    void ImportTypeMap(const SymbolTable& that);
    void ImportFunctionMap(const SymbolTable& that);
    void ImportFunctionDefinitionMap(const SymbolTable& that);
    void ImportVariableMap(const SymbolTable& that);
    void ImportConstraintMap(const SymbolTable& that);
    void ImportForwardDeclarations(const SymbolTable& that);
    void ImportSpecifierMap(const SymbolTable& that);
    void ImportClasses(const SymbolTable& that);
    Module* module;
    std::unique_ptr<NamespaceSymbol> globalNs;
    std::vector<std::unique_ptr<Symbol>> specializations;
    std::set<SpecializationSymbol*, SpecializationLess> specializationSet;
    std::vector<std::unique_ptr<CompoundTypeSymbol>> compoundTypes;
    std::map<TypeSymbol*, std::vector<CompoundTypeSymbol*>> compoundTypeMap;
    std::map<int32_t, TypeSymbol*> fundamentalTypeMap;
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
};

} // namespace otava::symbols