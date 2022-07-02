// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.scope;

import std.core;
import soul.ast.source.pos;
import soul.cpp20.symbols.lookup;

export namespace soul::cpp20::symbols {

class Symbol;
class Context;
class NamespaceSymbol;
class ContainerSymbol;
class ClassGroupSymbol;
class FunctionGroupSymbol;
class ConceptGroupSymbol;
class VariableGroupSymbol;
class AliasGroupSymbol;
class UsingDeclarationScope;
class UsingDirectiveScope;

enum class ScopeKind : int32_t
{
    none, namespaceScope, templateDeclarationScope, classScope, enumerationScope, functionScope, blockScope, usingDeclarationScope, usingDirectiveScope
};

enum class SymbolGroupKind : int32_t;

std::string ScopeKindStr(ScopeKind kind);

class Scope
{
public:
    Scope();
    virtual ~Scope();
    ScopeKind Kind() const { return kind; }
    void SetKind(ScopeKind kind_) { kind = kind_; }
    void Install(Symbol* symbol);
    void Uninstall(Symbol* symbol);
    Symbol* Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, const soul::ast::SourcePos& sourcePos, Context* context, LookupFlags flags) const;
    virtual std::string FullName() const = 0;
    virtual bool IsContainerScope() const { return false; }
    virtual Scope* GetClassScope() const { return nullptr; }
    virtual Symbol* GetSymbol() { return nullptr; }
    virtual void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, std::vector<Symbol*>& symbols) const;
    virtual void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::unique_ptr<Symbol> RemoveSymbol(Symbol* symbol);
    virtual Scope* ParentScope() const { return nullptr; }
    virtual void SetParentScope(Scope* parentScope_);
    virtual void AddBaseScope(Scope* baseScope, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual void AddUsingDeclaration(Symbol* usingDeclaration, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual void AddUsingDirective(NamespaceSymbol* ns, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual ClassGroupSymbol* GetOrInsertClassGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual FunctionGroupSymbol* GetOrInsertFunctionGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual ConceptGroupSymbol* GetOrInsertConceptGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual VariableGroupSymbol* GetOrInsertVariableGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual AliasGroupSymbol* GetOrInsertAliasGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context);
private:
    ScopeKind kind;
    std::map<std::pair<std::u32string, SymbolGroupKind>, Symbol*> symbolMap;
};

class ContainerScope : public Scope
{
public:
    ContainerScope();
    Scope* ParentScope() const override { return parentScope; }
    void SetParentScope(Scope* parentScope_) override { parentScope = parentScope_; }
    bool IsContainerScope() const override { return true; }
    Scope* GetClassScope() const override;
    void AddBaseScope(Scope* baseScope, const soul::ast::SourcePos& sourcePos, Context* context) override;
    Symbol* GetSymbol() override;
    ContainerSymbol* GetContainerSymbol() const { return containerSymbol; }
    void SetContainerSymbol(ContainerSymbol* containerSymbol_) { containerSymbol = containerSymbol_; }
    void AddUsingDeclaration(Symbol* usingDeclaration, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void AddUsingDirective(NamespaceSymbol* ns, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::string FullName() const override;
    void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, std::vector<Symbol*>& symbols) const override;
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::unique_ptr<Symbol> RemoveSymbol(Symbol* symbol) override;
    ClassGroupSymbol* GetOrInsertClassGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    FunctionGroupSymbol* GetOrInsertFunctionGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    ConceptGroupSymbol* GetOrInsertConceptGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    VariableGroupSymbol* GetOrInsertVariableGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
    AliasGroupSymbol* GetOrInsertAliasGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    Scope* parentScope;
    std::vector<Scope*> baseScopes;
    Scope* usingDeclarationScope;
    ContainerSymbol* containerSymbol;
    std::vector<UsingDirectiveScope*> usingDirectiveScopes;
    std::vector<std::unique_ptr<Scope>> scopes;
};

class UsingDeclarationScope : public Scope
{
public:
    UsingDeclarationScope(ContainerScope* parentScope_);
    std::string FullName() const override;
    void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, std::vector<Symbol*>& symbols) const override;
private:
    ContainerScope* parentScope;
};

class UsingDirectiveScope : public Scope
{
public:
    UsingDirectiveScope(NamespaceSymbol* ns_);
    void Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, std::vector<Symbol*>& symbols) const override;
    std::string FullName() const override;
    NamespaceSymbol* Ns() const { return ns; }
private:
    NamespaceSymbol* ns;
};

} // namespace soul::cpp20::symbols
