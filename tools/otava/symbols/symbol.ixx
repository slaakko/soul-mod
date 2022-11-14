// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.symbol;

import std.core;
import util.uuid;
import soul.ast.source.pos;
import otava.symbols.scope;

export namespace otava::symbols {

class Context;
class Emitter;
class Reader;
class Writer;
class Visitor;
class SymbolTable;
class Module;
class ConceptSymbol;
class AliasTypeSymbol;
class ClassTypeSymbol;
class EnumeratedTypeSymbol;
class FunctionSymbol;
class NamespaceSymbol;
class TemplateDeclarationSymbol;
class VariableSymbol;

enum class DeclarationFlags : int32_t;

enum class Access : int32_t
{
    none, public_, protected_, private_
};

std::string AccessStr(Access access);

enum class SymbolGroupKind : int32_t
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

enum class SymbolKind : int32_t
{
    null, 
    classGroupSymbol, conceptGroupSymbol, functionGroupSymbol, variableGroupSymbol, aliasGroupSymbol, enumGroupSymbol,
    boolValueSymbol, integerValueSymbol, floatingValueSymbol, stringValueSymbol, charValueSymbol, genericTypeSymbol, nullPtrTypeSymbol, 
    aliasTypeSymbol, arrayTypeSymbol, blockSymbol, classTypeSymbol, compoundTypeSymbol,
    conceptSymbol, enumTypeSymbol, enumConstantSymbol, functionSymbol, functionTypeSymbol, functionDefinitionSymbol,
    fundamentalTypeSymbol, namespaceSymbol, templateDeclarationSymbol, typenameConstraintSymbol,
    templateParameterSymbol, varArgTypeSymbol, variableSymbol, parameterSymbol, errorSymbol,
    classTemplateSpecializationSymbol, aliasTypeTemplateSpecializationSymbol, nestedTypeSymbol, nullPtrValueSymbol, symbolValueSymbol, invokeValueSymbol,
    forwardClassDeclarationSymbol, forwardEnumDeclarationSymbol, boundTemplateParameterSymbol, constraintExprSymbol,
    fundamentalTypeNot, fundamentalTypeUnaryPlus, fundamentalTypeUnaryMinus, fundamentalTypeComplement,
    fundamentalTypeAdd, fundamentalTypeSub, fundamentalTypeMul, fundamentalTypeDiv, fundamentalTypeMod,
    fundamentalTypeAnd, fundamentalTypeOr, fundamentalTypeXor, fundamentalTypeShl, fundamentalTypeShr,
    fundamentalTypeEqual, fundamentalTypeLess, fundamentalTypeBoolean,
    fundamentalTypeSignExtension, fundamentalTypeZeroExtension, fundamentalTypeTruncate, fundamentalTypeBitcast, fundamentalTypeIntToFloat, fundamentalTypeFloatToInt,

    fundamentalTypeDefaultCtor, fundamentalTypeCopyCtor, fundamentalTypeCopyCtorLiteral, fundamentalTypeMoveCtor, fundamentalTypeCopyAssignment, fundamentalTypeMoveAssignment,

    defaultBool, defaultSByte, defaultByte, defaultShort, defaultUShort, defaultInt, defaultUInt, defaultLong, defaultULong, defaultFloat, defaultDouble,
    defaultChar, defaultChar16, defaultChar32,
    max
};

enum class SymbolGroupKind : int32_t;

std::vector<SymbolGroupKind> SymbolGroupKindstoSymbolGroupKindVec(SymbolGroupKind symbolGroupKinds);

class Symbol
{
public:
    Symbol(SymbolKind kind_, const std::u32string& name_);
    virtual ~Symbol();
    SymbolKind Kind() const { return kind; }
    const util::uuid& Id() const { return id; }
    const std::u32string& Name() const { return name; }
    void SetName(const std::u32string& name_);
    Access GetAccess() const { return access; }
    void SetAccess(Access access_) { access = access_; }
    void SetDeclarationFlags(DeclarationFlags declarationFlags_) { declarationFlags = declarationFlags_; }
    DeclarationFlags GetDeclarationFlags() const { return declarationFlags; }
    virtual int PtrIndex() const { return -1; }
    virtual Scope* GetScope() { return nullptr; }
    virtual Scope* GetGroupScope() { return nullptr; }
    virtual std::u32string FullName() const;
    virtual std::string SymbolKindStr() const = 0;
    virtual bool IsValidDeclarationScope(ScopeKind scopeKind) const { return true; }
    virtual void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual std::unique_ptr<Symbol> RemoveSymbol(Symbol* symbol);
    virtual void Write(Writer& writer);
    virtual void Read(Reader& reader);
    virtual void Resolve(SymbolTable& symbolTable);
    virtual void Accept(Visitor& visitor) = 0;
    virtual Symbol* GetSingleSymbol() { return this; }
    virtual std::string SymbolDocKindStr() const = 0;
    virtual SymbolTable* GetSymbolTable();
    Module* GetModule();
    Symbol* Parent() { return parent; }
    const Symbol* Parent() const { return parent; }
    void SetParent(Symbol* parent_) { parent = parent_; }
    ClassTypeSymbol* ParentClass() const;
    NamespaceSymbol* ParentNamespace() const;
    std::string DocName() const;
    bool CanInstall() const;
    bool IsTypeSymbol() const;
    bool IsNamespaceSymbol() const { return kind == SymbolKind::namespaceSymbol; }
    bool IsGlobalNamespace() const { return kind == SymbolKind::namespaceSymbol && parent == nullptr; }
    bool IsClassTemplateSpecializationSymbol() const { return kind == SymbolKind::classTemplateSpecializationSymbol;  }
    bool IsAliasTypeTemplateSpecializationSymbol() const { return kind == SymbolKind::aliasTypeTemplateSpecializationSymbol; }
    bool IsCompoundTypeSymbol() const { return kind == SymbolKind::compoundTypeSymbol; }
    bool IsIntegerValueSymbol() const { return kind == SymbolKind::integerValueSymbol; }
    bool IsFloatingValueSymbol() const { return kind == SymbolKind::floatingValueSymbol; }
    bool IsStringValueSymbol() const { return kind == SymbolKind::stringValueSymbol; }
    bool IsCharValueSymbol() const { return kind == SymbolKind::charValueSymbol; }
    bool IsAliasTypeSymbol() const { return kind == SymbolKind::aliasTypeSymbol || IsAliasTypeTemplateSpecializationSymbol(); }
    bool IsAliasGroupSymbol() const { return kind == SymbolKind::aliasGroupSymbol; }
    bool IsClassGroupSymbol() const { return kind == SymbolKind::classGroupSymbol; }
    bool IsClassTypeSymbol() const { return kind == SymbolKind::classTypeSymbol; }
    bool IsForwardClassDeclarationSymbol() const { return kind == SymbolKind::forwardClassDeclarationSymbol; }
    bool IsConceptSymbol() const { return kind == SymbolKind::conceptSymbol; }
    bool IsEnumGroupSymbol() const { return kind == SymbolKind::enumGroupSymbol; }
    bool IsEnumeratedTypeSymbol() const { return kind == SymbolKind::enumTypeSymbol; }
    bool IsForwardEnumDeclarationSymbol() const { return kind == SymbolKind::forwardEnumDeclarationSymbol; }
    bool IsEnumConstantSymbol() const { return kind == SymbolKind::enumConstantSymbol; }
    bool IsFunctionGroupSymbol() const { return kind == SymbolKind::functionGroupSymbol; }
    bool IsFunctionSymbol() const;
    bool IsFunctionTypeSymbol() const { return kind == SymbolKind::functionTypeSymbol; }
    bool IsFunctionDefinitionSymbol() const { return kind == SymbolKind::functionDefinitionSymbol; }
    bool IsBlockSymbol() const { return kind == SymbolKind::blockSymbol; }
    bool IsFundamentalTypeSymbol() const { return kind == SymbolKind::fundamentalTypeSymbol; }
    bool IsParameterSymbol() const { return kind == SymbolKind::parameterSymbol; }
    bool IsLocalVariableSymbol() const;
    bool IsTemplateParameterSymbol() const { return kind == SymbolKind::templateParameterSymbol; }
    bool IsBoundTemplateParameterSymbol() const { return kind == SymbolKind::boundTemplateParameterSymbol; }
    bool IsTemplateDeclarationSymbol() const { return kind == SymbolKind::templateDeclarationSymbol; }
    bool IsTypenameConstraintSymbol() const { return kind == SymbolKind::typenameConstraintSymbol; }
    bool IsVariableGroupSymbol() const { return kind == SymbolKind::variableGroupSymbol; }
    bool IsVariableSymbol() const { return kind == SymbolKind::variableSymbol; }
    bool IsErrorTypeSymbol() const { return kind == SymbolKind::errorSymbol; }
    bool IsConstraintExprSymbol() const { return kind == SymbolKind::constraintExprSymbol; }
    bool IsValueSymbol() const;
    bool IsForwardDeclarationSymbol() const { return IsForwardClassDeclarationSymbol() || IsForwardEnumDeclarationSymbol(); }
    bool IsDefaultCtor() const;
    bool IsCopyCtor() const;
    bool IsMoveCtor() const;
    bool IsCopyAssignment() const;
    bool IsMoveAssignment() const;
    bool IsDtor() const;
    SymbolGroupKind GetSymbolGroupKind() const;
    void* IrObject(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context);
private:
    SymbolKind kind;
    util::uuid id;
    std::u32string name;
    Symbol* parent;
    DeclarationFlags declarationFlags;
    Access access;
};

} // namespace otava::symbols
