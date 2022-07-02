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
import util.uuid;

export namespace soul::cpp20::symbols {

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

class Context;
class Module;
class Symbol;
class Scope;
class CompoundTypeSymbol;
class NamespaceSymbol;
class TypeSymbol;
class FunctionSymbol;
class ParameterSymbol;
class Reader;
class Writer;

enum class SymbolGroupKind : int32_t;

class SymbolTable
{
public:
    SymbolTable();
    void SetModule(Module* module_) { module = module_; }
    Module* GetModule() const { return module; }
    NamespaceSymbol* GlobalNs() const { return globalNs.get(); }
    void Init();
    void Write(Writer& writer);
    void Read(Reader& reader);
    void Resolve();
    TypeSymbol* GetFundamentalTypeSymbol(FundamentalTypeKind kind);
    Scope* CurrentScope() const { return currentScope; }
    void SetCurrentScope(Scope* scope) { currentScope = scope; }
    void PushScope();
    void PopScope();
    void BeginScope(Scope* scope);
    void EndScope();
    void BeginNamespace(soul::cpp20::ast::Node* node, Context* context);
    void EndNamespace(int level);
    void BeginClass(const std::u32string& name, soul::cpp20::ast::Node* node, Context* context);
    void EndClass();
    void BeginBlock(const soul::ast::SourcePos& sourcePos, Context* context);
    void EndBlock();
    void RemoveBlock();
    FunctionSymbol* AddFunction(const std::u32string& name, soul::cpp20::ast::Node* node, Context* context);
    ParameterSymbol* CreateParameter(const std::u32string& name, soul::cpp20::ast::Node* node, TypeSymbol* type, Context* context);
    void AddVariable(const std::u32string& name, soul::cpp20::ast::Node* node, TypeSymbol* type, Context* context);
    void AddAliasType(soul::cpp20::ast::Node* node, TypeSymbol* type, Context* context);
    void AddUsingDeclaration(soul::cpp20::ast::Node* node, Symbol* symbol, Context* context);
    void AddUsingDirective(NamespaceSymbol* ns, soul::cpp20::ast::Node* node, Context* context);
    TypeSymbol* MakeCompoundType(TypeSymbol* baseType, const Derivations& derivations);
    Symbol* Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context);
    Symbol* Lookup(const std::u32string& name, SymbolGroupKind symbolGroupKind, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags);
    void MapNode(soul::cpp20::ast::Node* node);
    void MapNode(soul::cpp20::ast::Node* node, Symbol* symbol);
    void MapNode(soul::cpp20::ast::Node* node, Symbol* symbol, MapKind kind);
    soul::cpp20::ast::Node* GetNodeNothrow(Symbol* symbol) const;
    soul::cpp20::ast::Node* GetNode(Symbol* symbol) const;
    Symbol* GetSymbolNothrow(soul::cpp20::ast::Node* node) const;
    Symbol* GetSymbol(soul::cpp20::ast::Node* node) const;
    TypeSymbol* GetTypeNothrow(const util::uuid& id) const;
    TypeSymbol* GetType(const util::uuid& id) const;
    void MapType(TypeSymbol* type);
private:
    void CreateFundamentalTypes();
    void AddFundamentalType(FundamentalTypeKind kind);
    Module* module;
    std::unique_ptr<NamespaceSymbol> globalNs;
    std::vector<std::unique_ptr<CompoundTypeSymbol>> compoundTypes;
    std::map<TypeSymbol*, std::vector<CompoundTypeSymbol*>> compoundTypeMap;
    std::map<int32_t, TypeSymbol*> fundamentalTypeMap;
    std::stack<Scope*> scopeStack;
    Scope* currentScope;
    std::map<soul::cpp20::ast::Node*, Symbol*> nodeSymbolMap;
    std::map<Symbol*, soul::cpp20::ast::Node*> symbolNodeMap;
    std::map<util::uuid, TypeSymbol*> typeMap;
};

} // namespace soul::cpp20::symbols
