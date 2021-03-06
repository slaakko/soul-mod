// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.symbol;

import std.core;
import util.uuid;
import soul.ast.source.pos;
import soul.cpp20.symbols.scope;

export namespace soul::cpp20::symbols {

class Context;
class Reader;
class Writer;
class SymbolTable;

enum class ScopeKind : int32_t;

enum class DeclarationFlags : int32_t;

enum class SymbolKind : int32_t
{
    null, 
    classGroupSymbol, conceptGroupSymbol, functionGroupSymbol, variableGroupSymbol, aliasGroupSymbol,
    boolValueSymbol, integerValueSymbol, floatingValueSymbol, genericTypeSymbol, nullPtrTypeSymbol,
    aliasTypeSymbol, arrayTypeSymbol, blockSymbol, classTypeSymbol, compoundTypeSymbol,
    conceptSymbol, enumTypeSymbol, enumeratorSymbol, functionSymbol, functionTypeSymbol, 
    fundamentalTypeSymbol, namespaceSymbol, templateDeclarationSymbol, 
    templateParameterSymbol, varArgTypeSymbol, variableSymbol, parameterSymbol, errorSymbol, max
};

enum class SymbolGroupKind : int32_t
{
    none = 0,
    functionSymbolGroup = 1 << 0,
    typeSymbolGroup = 1 << 1,
    variableSymbolGroup = 1 << 2,
    conceptSymbolGroup = 1 << 3,
    blockSymbolGroup = 1 << 4,
    all = functionSymbolGroup | typeSymbolGroup | variableSymbolGroup | conceptSymbolGroup | blockSymbolGroup
};

constexpr SymbolGroupKind operator|(SymbolGroupKind left, SymbolGroupKind right)
{
    return SymbolGroupKind(int32_t(left) | int32_t(right));
}

constexpr SymbolGroupKind operator&(SymbolGroupKind left, SymbolGroupKind right)
{
    return SymbolGroupKind(int32_t(left) & int32_t(right));
}

constexpr SymbolGroupKind operator~(SymbolGroupKind kind)
{
    return SymbolGroupKind(~int32_t(kind));
}

std::vector<SymbolGroupKind> SymbolGroupKindstoSymbolGroupKindVec(SymbolGroupKind symbolGroupKinds);

class Symbol
{
public:
    Symbol(SymbolKind kind_, const std::u32string& name_);
    virtual ~Symbol();
    SymbolKind Kind() const { return kind; }
    const util::uuid& Id() const { return id; }
    const std::u32string& Name() const { return name; }
    void SetDeclarationFlags(DeclarationFlags declarationFlags_) { declarationFlags = declarationFlags_; }
    DeclarationFlags GetDeclarationFlags() const { return declarationFlags; }
    virtual Scope* GetScope() { return nullptr; }
    virtual Scope* GetGroupScope() { return nullptr; }
    virtual std::u32string FullName() const;
    virtual std::string SymbolKindStr() const = 0;
    virtual const std::u32string& InstallationName() const { return name; }
    virtual bool IsValidDeclarationScope(ScopeKind scopeKind) const { return true; }
    virtual void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::unique_ptr<Symbol> RemoveSymbol(Symbol* symbol);
    virtual void Write(Writer& writer);
    virtual void Read(Reader& reader);
    virtual void Resolve(SymbolTable& symbolTable);
    virtual Symbol* GetSingleSymbol() { return this; }
    Symbol* Parent() { return parent; }
    void SetParent(Symbol* parent_) { parent = parent_; }
    bool CanInstall() const;
    bool IsTypeSymbol() const;
    bool IsNamespaceSymbol() const { return kind == SymbolKind::namespaceSymbol; }
    bool IsCompoundTypeSymbol() const { return kind == SymbolKind::compoundTypeSymbol; }
    bool IsIntegerValueSymbol() const { return kind == SymbolKind::integerValueSymbol; }
    bool IsFloatingValueSymbol() const { return kind == SymbolKind::floatingValueSymbol; }
    bool IsAliasTypeSymbol() const { return kind == SymbolKind::aliasTypeSymbol; }
    bool IsAliasGroupSymbol() const { return kind == SymbolKind::aliasGroupSymbol; }
    bool IsClassGroupSymbol() const { return kind == SymbolKind::classGroupSymbol; }
    bool IsBlockSymbol() const { return kind == SymbolKind::blockSymbol; }
    SymbolGroupKind GetSymbolGroupKind() const;
private:
    SymbolKind kind;
    util::uuid id;
    std::u32string name;
    Symbol* parent;
    DeclarationFlags declarationFlags;
};

bool SymbolsEqual(const std::vector<Symbol*>& left, const std::vector<Symbol*>& right);
bool SymbolsEqual(Symbol* left, Symbol* right);
int Match(const std::vector<Symbol*>& left, const std::vector<Symbol*>& right);
int Match(Symbol* left, Symbol* right);

Symbol* CreateSymbol(SymbolKind symbolKind, const std::u32string& name);

} // namespace soul::cpp20::symbols
