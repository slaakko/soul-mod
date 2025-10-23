// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.scope;

import std;
import soul.ast.source.pos;
import otava.symbols.lookup;

export namespace otava::symbols {

class Symbol;
class Module;
class Context;
class NamespaceSymbol;
class ContainerSymbol;
class ClassGroupSymbol;
class FunctionGroupSymbol;
class ConceptGroupSymbol;
class VariableGroupSymbol;
class AliasGroupSymbol;
class EnumGroupSymbol;
class UsingDeclarationScope;
class UsingDirectiveScope;
class ClassTemplateSpecializationSymbol;

enum class SymbolGroupKind : std::int32_t
{
    none = 0,
    functionSymbolGroup = 1 << 0,
    typeSymbolGroup = 1 << 1,
    variableSymbolGroup = 1 << 2,
    enumConstantSymbolGroup = 1 << 3,
    conceptSymbolGroup = 1 << 4,
    blockSymbolGroup = 1 << 5,
    all = functionSymbolGroup | typeSymbolGroup | variableSymbolGroup | enumConstantSymbolGroup | conceptSymbolGroup | blockSymbolGroup
};

constexpr SymbolGroupKind operator|(SymbolGroupKind left, SymbolGroupKind right)
{
    return SymbolGroupKind(std::int32_t(left) | std::int32_t(right));
}

constexpr SymbolGroupKind operator&(SymbolGroupKind left, SymbolGroupKind right)
{
    return SymbolGroupKind(std::int32_t(left) & std::int32_t(right));
}

constexpr SymbolGroupKind operator~(SymbolGroupKind kind)
{
    return SymbolGroupKind(~std::int32_t(kind));
}

std::string SymbolGroupStr(SymbolGroupKind group);

std::vector<SymbolGroupKind> SymbolGroupKindstoSymbolGroupKindVec(SymbolGroupKind symbolGroupKinds);

enum class ScopeKind : std::int32_t
{
    none, namespaceScope, templateDeclarationScope, classScope, enumerationScope, functionScope, arrayScope, blockScope, usingDeclarationScope, usingDirectiveScope, instantiationScope
};

std::string ScopeKindStr(ScopeKind kind);

class Scope
{
public:
    Scope();
    virtual ~Scope();
    inline ScopeKind Kind() const { return kind; }
    inline void SetKind(ScopeKind kind_) { kind = kind_; }
    void Install(Symbol* symbol, Context* context);
    void Install(Symbol* symbol, Symbol* from, Context* context);
    void Uninstall(Symbol* symbol);
    std::expected<Symbol*, int> Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, const soul::ast::SourcePos& sourcePos, 
        Context* context, LookupFlags flags) const;
    inline bool IsBlockScope() const { return kind == ScopeKind::blockScope; }
    inline bool IsClassScope() const { return kind == ScopeKind::classScope; }
    inline bool IsNamespaceScope() const { return kind == ScopeKind::namespaceScope; }
    inline bool IsTemplateDeclarationScope() const { return kind == ScopeKind::templateDeclarationScope; }
    virtual Scope* GroupScope();
    virtual Scope* SymbolScope();
    virtual std::expected<std::string, int> FullName() const = 0;
    virtual bool IsContainerScope() const { return false; }
    virtual Scope* GetClassScope() const { return nullptr; }
    virtual Scope* GetNamespaceScope() const { return nullptr; }
    virtual Symbol* GetSymbol() { return nullptr; }
    virtual ClassTemplateSpecializationSymbol* GetClassTemplateSpecialization(std::set<Scope*>& visited) const { return nullptr; }
    virtual void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, LookupFlags flags,
        std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const;
    virtual std::expected<bool, int> AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::expected<std::unique_ptr<Symbol>, int> RemoveSymbol(Symbol* symbol);
    virtual std::vector<Scope*> ParentScopes() const { return std::vector<Scope*>(); }
    virtual std::expected<bool, int> AddParentScope(Scope* parentScope_);
    virtual std::expected<bool, int> PushParentScope(Scope* parentScope);
    virtual std::expected<bool, int> PopParentScope();
    virtual bool HasParentScope(const Scope* parentScope) const { return false; }
    virtual void ClearParentScopes() {}
    virtual std::expected<bool, int> AddBaseScope(Scope* baseScope, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::expected<bool, int> AddUsingDeclaration(Symbol* usingDeclaration, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::expected<bool, int> AddUsingDirective(NamespaceSymbol* ns, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::expected<ClassGroupSymbol*, int> GetOrInsertClassGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::expected<FunctionGroupSymbol*, int> GetOrInsertFunctionGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::expected<ConceptGroupSymbol*, int> GetOrInsertConceptGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::expected<VariableGroupSymbol*, int> GetOrInsertVariableGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::expected<AliasGroupSymbol*, int> GetOrInsertAliasGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::expected<EnumGroupSymbol*, int> GetOrInsertEnumGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual void Import(Scope* that, Context* context);
private:
    ScopeKind kind;
    std::map<std::pair<std::u32string, SymbolGroupKind>, Symbol*> symbolMap;
};

class ContainerScope : public Scope
{
public:
    ContainerScope();
    void Import(Scope* that, Context* context) override;
    std::vector<Scope*> ParentScopes() const override { return parentScopes; }
    std::expected<bool, int> AddParentScope(Scope* parentScope) override;
    std::expected<bool, int> PushParentScope(Scope* parentScope) override;
    std::expected<bool, int> PopParentScope() override;
    void ClearParentScopes() override;
    bool IsContainerScope() const override { return true; }
    Scope* GetClassScope() const override;
    Scope* GetNamespaceScope() const override;
    void AddBaseScope(Scope* baseScope, const soul::ast::SourcePos& sourcePos, Context* context) override;
    Symbol* GetSymbol() override;
    ClassTemplateSpecializationSymbol* GetClassTemplateSpecialization(std::set<Scope*>& visited) const override;
    inline ContainerSymbol* GetContainerSymbol() const { return containerSymbol; }
    void SetContainerSymbol(ContainerSymbol* containerSymbol_) { containerSymbol = containerSymbol_; }
    std::expected<bool, int> AddUsingDeclaration(Symbol* usingDeclaration, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<bool, int> AddUsingDirective(NamespaceSymbol* ns, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<std::string, int> FullName() const override;
    void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, LookupFlags flags,
        std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const override;
    std::expected<bool, int> AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<std::unique_ptr<Symbol>, int> RemoveSymbol(Symbol* symbol) override;
    std::expected<ClassGroupSymbol*, int> GetOrInsertClassGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<FunctionGroupSymbol*, int> GetOrInsertFunctionGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<ConceptGroupSymbol*, int> GetOrInsertConceptGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<VariableGroupSymbol*, int> GetOrInsertVariableGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<AliasGroupSymbol*, int> GetOrInsertAliasGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::expected<EnumGroupSymbol*, int> GetOrInsertEnumGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool HasParentScope(const Scope* parentScope) const override;
private:
    std::vector<Scope*> parentScopes;
    std::vector<Scope*> baseScopes;
    Scope* usingDeclarationScope;
    ContainerSymbol* containerSymbol;
    std::vector<UsingDirectiveScope*> usingDirectiveScopes;
    std::vector<std::unique_ptr<Scope>> scopes;
    bool parentScopePushed;
};

class UsingDeclarationScope : public Scope
{
public:
    UsingDeclarationScope(ContainerScope* parentScope_);
    std::expected<std::string, int> FullName() const override;
    void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, LookupFlags flags,
        std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const override;
private:
    ContainerScope* parentScope;
};

class UsingDirectiveScope : public Scope
{
public:
    UsingDirectiveScope(NamespaceSymbol* ns_);
    void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, LookupFlags flags,
        std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const override;
    std::expected<std::string, int> FullName() const override;
    NamespaceSymbol* Ns() const { return ns; }
private:
    NamespaceSymbol* ns;
};

class InstantiationScope : public Scope
{
public:
    InstantiationScope(Scope* parentScope_);
    std::expected<std::string, int> FullName() const override;
    Scope* GroupScope() override;
    Scope* SymbolScope() override;
    Scope* GetClassScope() const override;
    Scope* GetNamespaceScope() const override;
    ClassTemplateSpecializationSymbol* GetClassTemplateSpecialization(std::set<Scope*>& visited) const override;
    void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, LookupFlags flags,
        std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const override;
    std::expected<bool, int> PushParentScope(Scope* parentScope_) override;
    std::expected<bool, int> PopParentScope() override;
    bool HasParentScope(const Scope* parentScope) const override;
private:
    std::vector<Scope*> parentScopes;
};

} // namespace otava::symbols
