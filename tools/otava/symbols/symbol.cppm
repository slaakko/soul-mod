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
import util.unicode;

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

enum class DeclarationFlags : std::int32_t
{
    none = 0,
    staticFlag = 1 << 0,
    threadLocalFlag = 1 << 1,
    externFlag = 1 << 2,
    mutableFlag = 1 << 3,
    virtualFlag = 1 << 4,
    explicitFlag = 1 << 5,
    inlineFlag = 1 << 6,
    friendFlag = 1 << 7,
    typedefFlag = 1 << 8,
    constExprFlag = 1 << 9,
    constEvalFlag = 1 << 10,
    constInitFlag = 1 << 11,
    constFlag = 1 << 12,
    volatileFlag = 1 << 13,
    lvalueRefFlag = 1 << 14,
    rvalueRefFlag = 1 << 15,

    charFlag = 1 << 16,
    char8Flag = 1 << 17,
    char16Flag = 1 << 18,
    char32Flag = 1 << 19,
    wcharFlag = 1 << 20,
    boolFlag = 1 << 21,
    shortFlag = 1 << 22,
    intFlag = 1 << 23,
    longFlag = 1 << 24,
    longLongFlag = 1 << 25,
    signedFlag = 1 << 26,
    unsignedFlag = 1 << 27,
    floatFlag = 1 << 28,
    doubleFlag = 1 << 29,
    voidFlag = 1 << 30,
    autoFlag = 1 << 31,

    fundamentalTypeFlags =
    charFlag | char8Flag | char16Flag | char32Flag | wcharFlag | boolFlag | shortFlag | intFlag | longFlag | longLongFlag | signedFlag | unsignedFlag | floatFlag | doubleFlag |
    voidFlag | autoFlag,

    typedefFlagMask = staticFlag | threadLocalFlag | externFlag | mutableFlag | virtualFlag | explicitFlag | inlineFlag | friendFlag | constExprFlag | constEvalFlag | constInitFlag,

    cvQualifierFlagMask = constFlag | volatileFlag
};

constexpr DeclarationFlags operator|(DeclarationFlags left, DeclarationFlags right) noexcept
{
    return DeclarationFlags(std::int32_t(left) | std::int32_t(right));
}

constexpr DeclarationFlags operator&(DeclarationFlags left, DeclarationFlags right) noexcept
{
    return DeclarationFlags(std::int32_t(left) & std::int32_t(right));
}

constexpr DeclarationFlags operator~(DeclarationFlags flags) noexcept
{
    return DeclarationFlags(~std::int32_t(flags));
}

enum class Access : std::uint8_t
{
    none, public_, protected_, private_
};

std::string AccessStr(Access access);

enum class SymbolKind : std::uint8_t
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
    fundamentalTypeTruncate, fundamentalTypeBitcast, fundamentalTypeIntToFloat, fundamentalTypeFloatToInt, fundamentalTypeBoolToInt,
    fundamentalTypeDefaultCtor, fundamentalTypeCopyCtor, fundamentalTypeCopyCtorLiteral, fundamentalTypeMoveCtor, fundamentalTypeCopyAssignment, 
    fundamentalTypeMoveAssignment, 
    enumTypeDefaultCtor, enumTypeCopyCtor, enumTypeMoveCtor, enumTypeCopyAssignment, enumTypeMoveAssignment, enumTypeEqual, enumTypeLess,
    arrayTypeDefaultCtor, arrayTypeCopyCtor, arrayTypeMoveCtor, arrayTypeCopyAssignment, arrayTypeMoveAssignment,
    arrayTypeBegin, arrayTypeEnd,
    defaultBool, defaultSByte, defaultByte, defaultShort, defaultUShort, defaultInt, defaultUInt, defaultLong, defaultULong, defaultFloat, defaultDouble,
    defaultChar, defaultChar16, defaultChar32,
    functionGroupTypeSymbol, classGroupTypeSymbol, aliasGroupTypeSymbol, friendSymbol, namespaceTypeSymbol,
    intrinsicGetRbp,
    max
};

std::string SymbolKindToString(SymbolKind kind);

using SymbolDestroyedFunc = void(*)(Symbol*);

void SetSymbolDestroyedFunc(SymbolDestroyedFunc func) noexcept;

enum class SymbolFlags : std::uint8_t
{
    none = 0, project = 1 << 0
};

constexpr SymbolFlags operator|(SymbolFlags left, SymbolFlags right) noexcept
{
    return SymbolFlags(std::uint8_t(left) | std::uint8_t(right));
}

constexpr SymbolFlags operator&(SymbolFlags left, SymbolFlags right) noexcept
{
    return SymbolFlags(std::uint8_t(left) & std::uint8_t(right));
}

constexpr SymbolFlags operator~(SymbolFlags flags) noexcept
{
    return SymbolFlags(~std::uint8_t(flags));
}

class Symbol
{
public:
    Symbol(SymbolKind kind_, const std::u32string& name_);
    Symbol(SymbolKind kind_, const util::uuid& id_, const std::u32string& name_);
    virtual ~Symbol();
    inline SymbolKind Kind() const noexcept { return kind; }
    inline const util::uuid& Id() const noexcept { return id; }
    void SetId(const util::uuid& id_) noexcept { id = id_; }
    virtual util::uuid IrId(Context* context) const noexcept { return id; }
    inline const std::u32string& Name() const noexcept { return name; }
    void SetName(const std::u32string& name_);
    inline Access GetAccess() const noexcept { return access; }
    inline void SetAccess(Access access_) noexcept { access = access_; }
    inline bool GetFlag(SymbolFlags flag) const noexcept { return (flags & flag) != SymbolFlags::none; }
    inline void SetFlag(SymbolFlags flag) noexcept { flags = flags | flag; }
    inline void ResetFlag(SymbolFlags flag) noexcept { flags = flags & ~flag; }
    inline bool IsProject() const noexcept { return GetFlag(SymbolFlags::project); }
    inline void SetProject() noexcept { SetFlag(SymbolFlags::project); }
    inline void SetDeclarationFlags(DeclarationFlags declarationFlags_) noexcept { declarationFlags = declarationFlags_; }
    inline DeclarationFlags GetDeclarationFlags() const noexcept { return declarationFlags; }
    virtual const std::u32string& SimpleName() const noexcept { return Name(); }
    virtual int PtrIndex() const noexcept { return -1; }
    virtual Scope* GetScope() noexcept { return nullptr; }
    virtual Scope* GetGroupScope() noexcept { return nullptr; }
    virtual std::string IrName(Context* context) const;
    virtual std::u32string FullName() const;
    virtual std::string SymbolKindStr() const = 0;
    virtual bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept { return true; }
    virtual void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const;
    virtual std::unique_ptr<Symbol> RemoveSymbol(Symbol* symbol);
    virtual void Write(Writer& writer);
    virtual void Read(Reader& reader);
    virtual void Resolve(SymbolTable& symbolTable, Context* context);
    virtual void Accept(Visitor& visitor) = 0;
    virtual bool IsExportSymbol(Context* context) const noexcept { return IsProject(); }
    virtual bool IsExportMapSymbol(Context* context) const noexcept { return IsExportSymbol(context); }
    virtual Symbol* GetSingleSymbol() noexcept { return this; }
    virtual std::string SymbolDocKindStr() const = 0;
    virtual bool IsCharTypeSymbol() const noexcept { return false; }
    virtual bool IsChar8TypeSymbol() const noexcept { return false; }
    virtual bool IsChar16TypeSymbol() const noexcept { return false; }
    virtual bool IsChar32TypeSymbol() const noexcept { return false; }
    inline Symbol* Parent() noexcept { return parent; }
    inline const Symbol* Parent() const noexcept { return parent; }
    inline void SetParent(Symbol* parent_) noexcept { parent = parent_; }
    FunctionSymbol* ParentFunction() const noexcept;
    virtual ClassTypeSymbol* ParentClassType() const noexcept;
    NamespaceSymbol* ParentNamespace() const noexcept;
    std::string DocName() const;
    bool CanInstall() const noexcept;
    bool IsTypeSymbol() const noexcept;
    inline bool IsNamespaceSymbol() const noexcept { return kind == SymbolKind::namespaceSymbol; }
    inline bool IsGlobalNamespace() const noexcept { return kind == SymbolKind::namespaceSymbol && parent == nullptr; }
    inline bool IsClassTemplateSpecializationSymbol() const noexcept { return kind == SymbolKind::classTemplateSpecializationSymbol;  }
    inline bool IsAliasTypeTemplateSpecializationSymbol() const noexcept { return kind == SymbolKind::aliasTypeTemplateSpecializationSymbol; }
    inline bool IsArrayTypeSymbol() const noexcept { return kind == SymbolKind::arrayTypeSymbol; }
    inline bool IsCompoundTypeSymbol() const noexcept { return kind == SymbolKind::compoundTypeSymbol; }
    inline bool IsExplicitInstantiationSymbol() const noexcept { return kind == SymbolKind::explicitInstantiationSymbol; }
    inline bool IsIntegerValueSymbol() const noexcept { return kind == SymbolKind::integerValueSymbol; }
    inline bool IsFloatingValueSymbol() const noexcept { return kind == SymbolKind::floatingValueSymbol; }
    inline bool IsStringValueSymbol() const noexcept { return kind == SymbolKind::stringValueSymbol; }
    inline bool IsCharValueSymbol() const noexcept { return kind == SymbolKind::charValueSymbol; }
    inline bool IsSymbolValueSymbol() const noexcept { return kind == SymbolKind::symbolValueSymbol; }
    inline bool IsAliasTypeSymbol() const noexcept { return kind == SymbolKind::aliasTypeSymbol || IsAliasTypeTemplateSpecializationSymbol(); }
    inline bool IsAliasGroupSymbol() const noexcept { return kind == SymbolKind::aliasGroupSymbol; }
    inline bool IsClassGroupSymbol() const noexcept { return kind == SymbolKind::classGroupSymbol; }
    inline bool IsClassTypeSymbol() const noexcept { return kind == SymbolKind::classTypeSymbol || IsClassTemplateSpecializationSymbol(); }
    inline bool IsForwardClassDeclarationSymbol() const noexcept { return kind == SymbolKind::forwardClassDeclarationSymbol; }
    inline bool IsConceptGroupSymbol() const noexcept { return kind == SymbolKind::conceptGroupSymbol; }
    inline bool IsConceptSymbol() const noexcept { return kind == SymbolKind::conceptSymbol; }
    inline bool IsEnumGroupSymbol() const noexcept { return kind == SymbolKind::enumGroupSymbol; }
    inline bool IsEnumeratedTypeSymbol() const noexcept { return kind == SymbolKind::enumTypeSymbol; }
    inline bool IsForwardEnumDeclarationSymbol() const noexcept { return kind == SymbolKind::forwardEnumDeclarationSymbol; }
    inline bool IsEnumConstantSymbol() const noexcept { return kind == SymbolKind::enumConstantSymbol; }
    inline bool IsFunctionGroupSymbol() const noexcept { return kind == SymbolKind::functionGroupSymbol; }
    bool IsFunctionSymbol() const noexcept;
    inline bool IsFunctionTypeSymbol() const noexcept { return kind == SymbolKind::functionTypeSymbol; }
    inline bool IsFunctionDefinitionSymbol() const noexcept { return kind == SymbolKind::functionDefinitionSymbol; }
    inline bool IsExplicitlyInstantiatedFunctionDefinitionSymbol() const noexcept { return kind == SymbolKind::explicitlyInstantiatedFunctionDefinitionSymbol;  }
    inline bool IsBlockSymbol() const noexcept { return kind == SymbolKind::blockSymbol; }
    inline bool IsFundamentalTypeSymbol() const noexcept { return kind == SymbolKind::fundamentalTypeSymbol; }
    inline bool IsParameterSymbol() const noexcept { return kind == SymbolKind::parameterSymbol; }
    bool IsLocalVariableSymbol() const noexcept;
    bool IsMemberVariableSymbol() const noexcept;
    bool IsGlobalVariableSymbol() const noexcept;
    inline bool IsTemplateParameterSymbol() const noexcept { return kind == SymbolKind::templateParameterSymbol; }
    inline bool IsBoundTemplateParameterSymbol() const noexcept { return kind == SymbolKind::boundTemplateParameterSymbol; }
    inline bool IsTemplateDeclarationSymbol() const noexcept { return kind == SymbolKind::templateDeclarationSymbol; }
    inline bool IsTypenameConstraintSymbol() const noexcept { return kind == SymbolKind::typenameConstraintSymbol; }
    inline bool IsVariableGroupSymbol() const noexcept { return kind == SymbolKind::variableGroupSymbol; }
    inline bool IsVariableSymbol() const noexcept { return kind == SymbolKind::variableSymbol; }
    inline bool IsErrorTypeSymbol() const noexcept { return kind == SymbolKind::errorSymbol; }
    inline bool IsConstraintExprSymbol() const noexcept { return kind == SymbolKind::constraintExprSymbol; }
    bool IsValueSymbol() const noexcept;
    inline bool IsForwardDeclarationSymbol() const noexcept { return IsForwardClassDeclarationSymbol() || IsForwardEnumDeclarationSymbol(); }
    inline bool IsFunctionGroupTypeSymbol() const noexcept { return kind == SymbolKind::functionGroupTypeSymbol; }
    inline bool IsClassGroupTypeSymbol() const noexcept { return kind == SymbolKind::classGroupTypeSymbol; }
    inline bool IsAliasGroupTypeSymbol() const noexcept { return kind == SymbolKind::aliasGroupTypeSymbol; }
    inline bool IsNestedTypeSymbol() const noexcept { return kind == SymbolKind::nestedTypeSymbol; }
    inline bool IsDependentTypeSymbol()  const noexcept { return kind == SymbolKind::dependentTypeSymbol; }
    bool IsDefaultCtor() const noexcept;
    bool IsCopyCtor() const noexcept;
    bool IsMoveCtor() const noexcept;
    bool IsCopyAssignment() const noexcept;
    bool IsMoveAssignment() const noexcept;
    bool IsDtor() const noexcept;
    SymbolGroupKind GetSymbolGroupKind() const noexcept;
    void* IrObject(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context);
    bool IsExtern() const noexcept;
    virtual soul::xml::Element* ToXml() const;
    inline void SetSourcePos(const soul::ast::SourcePos& sourcePos_) noexcept { sourcePos = sourcePos_; }
    inline const soul::ast::SourcePos& GetSourcePos() const noexcept { return sourcePos; }
private:
    SymbolKind kind;
    SymbolFlags flags;
    util::uuid id;
    std::u32string name;
    Symbol* parent;
    DeclarationFlags declarationFlags;
    Access access;
    soul::ast::SourcePos sourcePos;
};

} // namespace otava::symbols
