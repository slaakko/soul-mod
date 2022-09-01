// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.symbol.table;

import std.core;
import soul.ast.source.pos;
import soul.cpp20.ast;
import soul.cpp20.symbols.derivations;
import soul.cpp20.symbols.lookup;
import soul.cpp20.symbols.specialization.compare;
import util.uuid;

export namespace soul::cpp20::symbols {

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
class ParameterSymbol;
class Value;
class VariableSymbol;
class Reader;
class Writer;
class Visitor;

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
    void Resolve(soul::cpp20::ast::NodeMap* nodeMap_);
    soul::cpp20::ast::NodeMap* GetNodeMap() const { return nodeMap; }
    void Accept(Visitor& visitor);
    void WriteMaps(Writer& writer);
    void ReadMaps(Reader& reader, soul::cpp20::ast::NodeMap* nodeMap);
    TypeSymbol* GetFundamentalTypeSymbol(FundamentalTypeKind kind);
    Symbol* GetTypenameConstraintSymbol() { return typenameConstraintSymbol; }
    void SetTypenameConstraintSymbol(Symbol* typenameConstraintSymbol_) { typenameConstraintSymbol = typenameConstraintSymbol_; }
    TypeSymbol* GetErrorTypeSymbol() { return errorTypeSymbol; }
    void SetErrorTypeSymbol(TypeSymbol* errorTypeSymbol_) { errorTypeSymbol = errorTypeSymbol_; }
    Scope* CurrentScope() const { return currentScope; }
    void SetCurrentScope(Scope* scope) { currentScope = scope; }
    void PushScope();
    void PopScope();
    void BeginScope(Scope* scope);
    void EndScope();
    void PushTopScopeIndex();
    void PopTopScopeIndex();
    void BeginNamespace(const std::u32string& name, soul::cpp20::ast::Node* node, Context* context);
    void EndNamespace();
    void BeginNamespace(soul::cpp20::ast::Node* node, Context* context);
    void EndNamespace(int level);
    void BeginClass(const std::u32string& name, ClassKind classKind, soul::cpp20::ast::Node* node, Context* context);
    void EndClass();
    void AddForwardClassDeclaration(const std::u32string& name, ClassKind classKind, soul::cpp20::ast::Node* node, Context* context);
    void BeginEnumeratedType(const std::u32string& name, EnumTypeKind kind, TypeSymbol* underlyingType, soul::cpp20::ast::Node* node, Context* context);
    void EndEnumeratedType();
    void AddForwardEnumDeclaration(const std::u32string& name, EnumTypeKind enumTypeKind, TypeSymbol* underlyingType, soul::cpp20::ast::Node* node, Context* context);
    void AddEnumerator(const std::u32string& name, Value* value, soul::cpp20::ast::Node* node, Context* context);
    void BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context);
    void EndBlock();
    void RemoveBlock();
    void BeginTemplateDeclaration(soul::cpp20::ast::Node* node, Context* context);
    void EndTemplateDeclaration();
    void RemoveTemplateDeclaration();
    void AddTemplateParameter(const std::u32string& name, soul::cpp20::ast::Node* node, Symbol* constraint, int index, ParameterSymbol* parameter, 
        soul::cpp20::ast::Node* defaultTemplateArgNode, Context* context);
    FunctionSymbol* AddFunction(const std::u32string& name, soul::cpp20::ast::Node* node, FunctionKind kind, FunctionQualifiers qualifiers, DeclarationFlags flags, Context* context);
    ParameterSymbol* CreateParameter(const std::u32string& name, soul::cpp20::ast::Node* node, TypeSymbol* type, Context* context);
    void AddVariable(const std::u32string& name, soul::cpp20::ast::Node* node, TypeSymbol* type, Value* value, DeclarationFlags flags, Context* context);
    void AddAliasType(soul::cpp20::ast::Node* node, TypeSymbol* type, Context* context);
    void AddUsingDeclaration(soul::cpp20::ast::Node* node, Symbol* symbol, Context* context);
    void AddUsingDirective(NamespaceSymbol* ns, soul::cpp20::ast::Node* node, Context* context);
    TypeSymbol* MakeCompoundType(TypeSymbol* baseType, const Derivations& derivations);
    ConceptSymbol* AddConcept(const std::u32string& name, soul::cpp20::ast::Node* node, Context* context);
    SpecializationSymbol* MakeSpecialization(TypeSymbol* classTemplate, const std::vector<Symbol*>& templateArguments);
    Symbol* Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context);
    Symbol* Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags);
    Symbol* LookupInScopeStack(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags);
    Symbol* LookupSymbol(Symbol* symbol);
    void MapNode(soul::cpp20::ast::Node* node);
    void MapNode(soul::cpp20::ast::Node* node, Symbol* symbol);
    void MapNode(soul::cpp20::ast::Node* node, Symbol* symbol, MapKind kind);
    soul::cpp20::ast::Node* GetNodeNothrow(Symbol* symbol) const;
    soul::cpp20::ast::Node* GetNode(Symbol* symbol) const;
    void RemoveNode(soul::cpp20::ast::Node* node);
    soul::cpp20::ast::Node* GetSpecifierNode(Symbol* symbol) const;
    void SetSpecifierNode(Symbol* symbol, soul::cpp20::ast::Node* node);
    Symbol* GetSymbolNothrow(soul::cpp20::ast::Node* node) const;
    Symbol* GetSymbol(soul::cpp20::ast::Node* node) const;
    TypeSymbol* GetTypeNothrow(const util::uuid& id) const;
    TypeSymbol* GetType(const util::uuid& id) const;
    void MapType(TypeSymbol* type);
    void MapFundamentalType(FundamentalTypeSymbol* fundamentalTypeSymbol);
    void MapFunction(FunctionSymbol* function);
    void MapVariable(VariableSymbol* variable);
    void MapConstraint(Symbol* constraint);
    FunctionSymbol* GetFunction(const util::uuid& id) const;
    AliasTypeSymbol* GetAliasType(const util::uuid& id) const;
    ClassTypeSymbol* GetClass(const util::uuid& id) const;
    VariableSymbol* GetVariable(const util::uuid& id) const;
    Symbol* GetConstraint(const util::uuid& id) const;
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
private:
    void CreateFundamentalTypes();
    void AddFundamentalType(FundamentalTypeKind kind);
    void CreateCoreSymbols();
    void ImportSpecializations();
    void ImportCompoundTypeMap(const SymbolTable& that);
    void ImportFundamentalTypeMap(const SymbolTable& that);
    void ImportNodeSymbolMap(const SymbolTable& that);
    void ImportSymbolNodeMap(const SymbolTable& that);
    void ImportTypeMap(const SymbolTable& that);
    void ImportFunctionMap(const SymbolTable& that);
    void ImportVariableMap(const SymbolTable& that);
    void ImportConstraintMap(const SymbolTable& that);
    void ImportForwardDeclarations(const SymbolTable& that);
    void ImportSpecifierMap(const SymbolTable& that);
    Module* module;
    std::unique_ptr<NamespaceSymbol> globalNs;
    std::vector<std::unique_ptr<Symbol>> specializations;
    std::set<SpecializationSymbol*, SpecializationLess> specializationSet;
    std::vector<std::unique_ptr<CompoundTypeSymbol>> compoundTypes;
    std::map<TypeSymbol*, std::vector<CompoundTypeSymbol*>> compoundTypeMap;
    std::map<int32_t, TypeSymbol*> fundamentalTypeMap;
    std::vector<Scope*> scopeStack;
    Scope* currentScope;
    std::map<soul::cpp20::ast::Node*, Symbol*> nodeSymbolMap;
    std::map<soul::cpp20::ast::Node*, Symbol*> allNodeSymbolMap;
    std::map<Symbol*, soul::cpp20::ast::Node*> symbolNodeMap;
    std::map<Symbol*, soul::cpp20::ast::Node*> allSymbolNodeMap;
    std::map<Symbol*, soul::cpp20::ast::Node*> specifierNodeMap;
    std::map<Symbol*, soul::cpp20::ast::Node*> allSpecifierNodeMap;
    std::map<util::uuid, TypeSymbol*> typeMap;
    std::map<util::uuid, FunctionSymbol*> functionMap;
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
    soul::cpp20::ast::NodeMap* nodeMap;
};

class Symbols
{
public:
    Symbols();
    void AddSymbol(Symbol* symbol);
    Symbol* GetSymbol(const util::uuid& symbolId);
private:
    std::map<util::uuid, Symbol*> symbolMap;
};

void SetSymbols(Symbols* symbols_);
void AddSymbol(Symbol* symbol);
Symbol* GetSymbol(const util::uuid& symbolId);

} // namespace soul::cpp20::symbols
