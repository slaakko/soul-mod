// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.symbol;

import std;
import soul.xml.dom;
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

enum class DeclarationFlags : std::int32_t;

enum class Access : std::int32_t
{
    none, public_, protected_, private_
};

std::string AccessStr(Access access);

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

std::string SymbolGroupStr(SymbolGroupKind group);

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

enum class SymbolKind : std::int32_t
{
    null, 
    classGroupSymbol, conceptGroupSymbol, functionGroupSymbol, variableGroupSymbol, aliasGroupSymbol, enumGroupSymbol,
    boolValueSymbol, integerValueSymbol, floatingValueSymbol, stringValueSymbol, charValueSymbol, genericTypeSymbol, nullPtrTypeSymbol, arrayValueSymbol, structureValueSymbol,
    aliasTypeSymbol, arrayTypeSymbol, blockSymbol, classTypeSymbol, compoundTypeSymbol,
    conceptSymbol, enumTypeSymbol, enumConstantSymbol, functionSymbol, functionTypeSymbol, functionDefinitionSymbol, explicitlyInstantiatedFunctionDefinitionSymbol,
    fundamentalTypeSymbol, namespaceSymbol, templateDeclarationSymbol, typenameConstraintSymbol, explicitInstantiationSymbol,
    templateParameterSymbol, varArgTypeSymbol, variableSymbol, parameterSymbol, errorSymbol,
    classTemplateSpecializationSymbol, aliasTypeTemplateSpecializationSymbol, nestedTypeSymbol, dependentTypeSymbol, nullPtrValueSymbol, symbolValueSymbol, invokeValueSymbol,
    forwardClassDeclarationSymbol, forwardEnumDeclarationSymbol, boundTemplateParameterSymbol, constraintExprSymbol,
    fundamentalTypeNot, fundamentalTypeUnaryPlus, fundamentalTypeUnaryMinus, fundamentalTypeComplement,
    fundamentalTypeAdd, fundamentalTypeSub, fundamentalTypeMul, fundamentalTypeDiv, fundamentalTypeMod,
    fundamentalTypeAnd, fundamentalTypeOr, fundamentalTypeXor, fundamentalTypeShl, fundamentalTypeShr,
    fundamentalTypePlusAssign, fundamentalTypeMinusAssign, fundamentalTypeMulAssign, fundamentalTypeDivAssign,
    fundamentalTypeModAssign, fundamentalTypeAndAssign, fundamentalTypeOrAssign, fundamentalTypeXorAssign, fundamentalTypeShlAssign, fundamentalTypeShrAssign,
    fundamentalTypeEqual, fundamentalTypeLess, fundamentalTypeBoolean,
    fundamentalTypeSignExtension, fundamentalTypeZeroExtension, fundamentalTypeFloatingPointExtension,
    fundamentalTypeTruncate, fundamentalTypeBitcast, fundamentalTypeIntToFloat, fundamentalTypeFloatToInt,
    fundamentalTypeDefaultCtor, fundamentalTypeCopyCtor, fundamentalTypeCopyCtorLiteral, fundamentalTypeMoveCtor, fundamentalTypeCopyAssignment, fundamentalTypeMoveAssignment,
    enumTypeDefaultCtor, enumTypeCopyCtor, enumTypeMoveCtor, enumTypeCopyAssignment, enumTypeMoveAssignment, enumTypeEqual, enumTypeLess,
    arrayTypeDefaultCtor, arrayTypeCopyCtor, arrayTypeMoveCtor, arrayTypeCopyAssignment, arrayTypeMoveAssignment,
    arrayTypeBegin, arrayTypeEnd,
    defaultBool, defaultSByte, defaultByte, defaultShort, defaultUShort, defaultInt, defaultUInt, defaultLong, defaultULong, defaultFloat, defaultDouble,
    defaultChar, defaultChar16, defaultChar32,
    functionGroupTypeSymbol, classGroupTypeSymbol, aliasGroupTypeSymbol, friendSymbol, namespaceTypeSymbol,
    max
};

std::string SymbolKindToString(SymbolKind kind);

enum class SymbolGroupKind : std::int32_t;

std::vector<SymbolGroupKind> SymbolGroupKindstoSymbolGroupKindVec(SymbolGroupKind symbolGroupKinds);

using SymbolDestroyedFunc = void(*)(Symbol*);

void SetSymbolDestroyedFunc(SymbolDestroyedFunc func);

class Symbol
{
public:
    Symbol(SymbolKind kind_, const std::u32string& name_);
    virtual ~Symbol();
    inline SymbolKind Kind() const { return kind; }
    inline const util::uuid& Id() const { return id; }
    inline const std::u32string& Name() const { return name; }
    void SetName(const std::u32string& name_);
    inline Access GetAccess() const { return access; }
    inline void SetAccess(Access access_) { access = access_; }
    inline void SetDeclarationFlags(DeclarationFlags declarationFlags_) { declarationFlags = declarationFlags_; }
    inline DeclarationFlags GetDeclarationFlags() const { return declarationFlags; }
    virtual const std::u32string& SimpleName() const { return Name(); }
    virtual int PtrIndex() const { return -1; }
    virtual Scope* GetScope() { return nullptr; }
    virtual Scope* GetGroupScope() { return nullptr; }
    virtual std::string IrName(Context* context) const;
    virtual std::u32string FullName() const;
    virtual std::string SymbolKindStr() const = 0;
    virtual bool IsValidDeclarationScope(ScopeKind scopeKind) const { return true; }
    virtual void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const;
    virtual std::unique_ptr<Symbol> RemoveSymbol(Symbol* symbol);
    virtual void Write(Writer& writer);
    virtual void Read(Reader& reader);
    virtual void Resolve(SymbolTable& symbolTable);
    virtual void Accept(Visitor& visitor) = 0;
    virtual bool IsExportSymbol(Context* context) const { return true; }
    virtual bool IsExportMapSymbol(Context* context)  const { return IsExportSymbol(context); }
    virtual Symbol* GetSingleSymbol() { return this; }
    virtual std::string SymbolDocKindStr() const = 0;
    inline Symbol* Parent() { return parent; }
    inline const Symbol* Parent() const { return parent; }
    inline void SetParent(Symbol* parent_) { parent = parent_; }
    FunctionSymbol* ParentFunction() const;
    virtual ClassTypeSymbol* ParentClassType() const;
    NamespaceSymbol* ParentNamespace() const;
    std::string DocName() const;
    bool CanInstall() const;
    bool IsTypeSymbol() const;
    inline bool IsNamespaceSymbol() const { return kind == SymbolKind::namespaceSymbol; }
    inline bool IsGlobalNamespace() const { return kind == SymbolKind::namespaceSymbol && parent == nullptr; }
    inline bool IsClassTemplateSpecializationSymbol() const { return kind == SymbolKind::classTemplateSpecializationSymbol;  }
    inline bool IsAliasTypeTemplateSpecializationSymbol() const { return kind == SymbolKind::aliasTypeTemplateSpecializationSymbol; }
    inline bool IsArrayTypeSymbol() const { return kind == SymbolKind::arrayTypeSymbol; }
    inline bool IsCompoundTypeSymbol() const { return kind == SymbolKind::compoundTypeSymbol; }
    inline bool IsExplicitInstantiationSymbol() const { return kind == SymbolKind::explicitInstantiationSymbol; }
    inline bool IsIntegerValueSymbol() const { return kind == SymbolKind::integerValueSymbol; }
    inline bool IsFloatingValueSymbol() const { return kind == SymbolKind::floatingValueSymbol; }
    inline bool IsStringValueSymbol() const { return kind == SymbolKind::stringValueSymbol; }
    inline bool IsCharValueSymbol() const { return kind == SymbolKind::charValueSymbol; }
    inline bool IsSymbolValueSymbol() const { return kind == SymbolKind::symbolValueSymbol; }
    inline bool IsAliasTypeSymbol() const { return kind == SymbolKind::aliasTypeSymbol || IsAliasTypeTemplateSpecializationSymbol(); }
    inline bool IsAliasGroupSymbol() const { return kind == SymbolKind::aliasGroupSymbol; }
    inline bool IsClassGroupSymbol() const { return kind == SymbolKind::classGroupSymbol; }
    inline bool IsClassTypeSymbol() const { return kind == SymbolKind::classTypeSymbol || IsClassTemplateSpecializationSymbol(); }
    inline bool IsForwardClassDeclarationSymbol() const { return kind == SymbolKind::forwardClassDeclarationSymbol; }
    inline bool IsConceptGroupSymbol() const { return kind == SymbolKind::conceptGroupSymbol; }
    inline bool IsConceptSymbol() const { return kind == SymbolKind::conceptSymbol; }
    inline bool IsEnumGroupSymbol() const { return kind == SymbolKind::enumGroupSymbol; }
    inline bool IsEnumeratedTypeSymbol() const { return kind == SymbolKind::enumTypeSymbol; }
    inline bool IsForwardEnumDeclarationSymbol() const { return kind == SymbolKind::forwardEnumDeclarationSymbol; }
    inline bool IsEnumConstantSymbol() const { return kind == SymbolKind::enumConstantSymbol; }
    inline bool IsFunctionGroupSymbol() const { return kind == SymbolKind::functionGroupSymbol; }
    bool IsFunctionSymbol() const;
    inline bool IsFunctionTypeSymbol() const { return kind == SymbolKind::functionTypeSymbol; }
    inline bool IsFunctionDefinitionSymbol() const { return kind == SymbolKind::functionDefinitionSymbol; }
    inline bool IsExplicitlyInstantiatedFunctionDefinitionSymbol() const { return kind == SymbolKind::explicitlyInstantiatedFunctionDefinitionSymbol;  }
    inline bool IsBlockSymbol() const { return kind == SymbolKind::blockSymbol; }
    inline bool IsFundamentalTypeSymbol() const { return kind == SymbolKind::fundamentalTypeSymbol; }
    inline bool IsParameterSymbol() const { return kind == SymbolKind::parameterSymbol; }
    bool IsLocalVariableSymbol() const;
    bool IsMemberVariableSymbol() const;
    bool IsGlobalVariableSymbol() const;
    inline bool IsTemplateParameterSymbol() const { return kind == SymbolKind::templateParameterSymbol; }
    inline bool IsBoundTemplateParameterSymbol() const { return kind == SymbolKind::boundTemplateParameterSymbol; }
    inline bool IsTemplateDeclarationSymbol() const { return kind == SymbolKind::templateDeclarationSymbol; }
    inline bool IsTypenameConstraintSymbol() const { return kind == SymbolKind::typenameConstraintSymbol; }
    inline bool IsVariableGroupSymbol() const { return kind == SymbolKind::variableGroupSymbol; }
    inline bool IsVariableSymbol() const { return kind == SymbolKind::variableSymbol; }
    inline bool IsErrorTypeSymbol() const { return kind == SymbolKind::errorSymbol; }
    inline bool IsConstraintExprSymbol() const { return kind == SymbolKind::constraintExprSymbol; }
    bool IsValueSymbol() const;
    inline bool IsForwardDeclarationSymbol() const { return IsForwardClassDeclarationSymbol() || IsForwardEnumDeclarationSymbol(); }
    inline bool IsFunctionGroupTypeSymbol() const { return kind == SymbolKind::functionGroupTypeSymbol; }
    inline bool IsClassGroupTypeSymbol() const { return kind == SymbolKind::classGroupTypeSymbol; }
    inline bool IsAliasGroupTypeSymbol() const { return kind == SymbolKind::aliasGroupTypeSymbol; }
    inline bool IsNestedTypeSymbol() const { return kind == SymbolKind::nestedTypeSymbol; }
    inline bool IsDependentTypeSymbol()  const { return kind == SymbolKind::dependentTypeSymbol; }
    bool IsDefaultCtor() const;
    bool IsCopyCtor() const;
    bool IsMoveCtor() const;
    bool IsCopyAssignment() const;
    bool IsMoveAssignment() const;
    bool IsDtor() const;
    SymbolGroupKind GetSymbolGroupKind() const;
    void* IrObject(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context);
    bool IsExtern() const;
    virtual soul::xml::Element* ToXml() const;
private:
    SymbolKind kind;
    util::uuid id;
    std::u32string name;
    Symbol* parent;
    DeclarationFlags declarationFlags;
    Access access;
};

} // namespace otava::symbols
