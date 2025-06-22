// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.scope;

import std.core;
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

enum class ScopeKind : std::int32_t
{
    none, namespaceScope, templateDeclarationScope, classScope, enumerationScope, functionScope, arrayScope, blockScope, usingDeclarationScope, usingDirectiveScope, instantiationScope
};

enum class SymbolGroupKind : std::int32_t;

std::string ScopeKindStr(ScopeKind kind);

class Scope
{
public:
    Scope();
    virtual ~Scope();
    ScopeKind Kind() const { return kind; }
    void SetKind(ScopeKind kind_) { kind = kind_; }
    void Install(Symbol* symbol);
    void Install(Symbol* symbol, Symbol* from);
    void Uninstall(Symbol* symbol);
    Symbol* Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags) const;
    bool IsBlockScope() const { return kind == ScopeKind::blockScope; }
    bool IsClassScope() const { return kind == ScopeKind::classScope; }
    bool IsNamespaceScope() const { return kind == ScopeKind::namespaceScope;  }
    bool IsTemplateDeclarationScope() const { return kind == ScopeKind::templateDeclarationScope; }
    virtual Scope* GroupScope();
    virtual Scope* SymbolScope();
    virtual std::string FullName() const = 0;
    virtual bool IsContainerScope() const { return false; }
    virtual Scope* GetClassScope() const { return nullptr; }
    virtual Scope* GetNamespaceScope() const { return nullptr; }
    virtual Symbol* GetSymbol() { return nullptr; }
    virtual ClassTemplateSpecializationSymbol* GetClassTemplateSpecialization() const { return nullptr; }
    virtual void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, LookupFlags flags, 
        std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const;
    virtual void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::unique_ptr<Symbol> RemoveSymbol(Symbol* symbol);
    virtual std::vector<Scope*> ParentScopes() const { return std::vector<Scope*>(); }
    virtual void AddParentScope(Scope* parentScope_);
    virtual void PushParentScope(Scope* parentScope);
    virtual void PopParentScope();
    virtual void ClearParentScopes() {}
    virtual void AddBaseScope(Scope* baseScope, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual void AddUsingDeclaration(Symbol* usingDeclaration, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual void AddUsingDirective(NamespaceSymbol* ns, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual ClassGroupSymbol* GetOrInsertClassGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual FunctionGroupSymbol* GetOrInsertFunctionGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual ConceptGroupSymbol* GetOrInsertConceptGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual VariableGroupSymbol* GetOrInsertVariableGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual AliasGroupSymbol* GetOrInsertAliasGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual EnumGroupSymbol* GetOrInsertEnumGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual void Import(Scope* that);
private:
    ScopeKind kind;
    std::map<std::pair<std::u32string, SymbolGroupKind>, Symbol*> symbolMap;
};

class ContainerScope : public Scope
{
public:
    ContainerScope();
    void Import(Scope* that) override;
    std::vector<Scope*> ParentScopes() const override { return parentScopes; }
    void AddParentScope(Scope* parentScope) override;
    void PushParentScope(Scope* parentScope) override;
    void PopParentScope() override;
    void ClearParentScopes() override;
    bool IsContainerScope() const override { return true; }
    Scope* GetClassScope() const override;
    Scope* GetNamespaceScope() const override;
    void AddBaseScope(Scope* baseScope, const soul::ast::SourcePos& sourcePos, Context* context) override;
    Symbol* GetSymbol() override;
    ClassTemplateSpecializationSymbol* GetClassTemplateSpecialization() const override;
    ContainerSymbol* GetContainerSymbol() const { return containerSymbol; }
    void SetContainerSymbol(ContainerSymbol* containerSymbol_) { containerSymbol = containerSymbol_; }
    void AddUsingDeclaration(Symbol* usingDeclaration, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void AddUsingDirective(NamespaceSymbol* ns, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::string FullName() const override;
    void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, LookupFlags flags, 
        std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const override;
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::unique_ptr<Symbol> RemoveSymbol(Symbol* symbol) override;
    ClassGroupSymbol* GetOrInsertClassGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    FunctionGroupSymbol* GetOrInsertFunctionGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    ConceptGroupSymbol* GetOrInsertConceptGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    VariableGroupSymbol* GetOrInsertVariableGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    AliasGroupSymbol* GetOrInsertAliasGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    EnumGroupSymbol* GetOrInsertEnumGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
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
    std::string FullName() const override;
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
    std::string FullName() const override;
    NamespaceSymbol* Ns() const { return ns; }
private:
    NamespaceSymbol* ns;
};

class InstantiationScope : public Scope
{
public:
    InstantiationScope(Scope* parentScope_);
    std::string FullName() const override;
    Scope* GroupScope() override;
    Scope* SymbolScope() override;
    Scope* GetClassScope() const override;
    Scope* GetNamespaceScope() const override;
    ClassTemplateSpecializationSymbol* GetClassTemplateSpecialization() const override;
    void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, LookupFlags flags, 
        std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const override;
    void PushParentScope(Scope* parentScope_) override;
    void PopParentScope() override;
private:
    std::vector<Scope*> parentScopes;
};

} // namespace otava::symbols
