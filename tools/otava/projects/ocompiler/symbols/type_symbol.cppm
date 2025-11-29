// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.type.symbol;

import std;
import otava.symbols.container.symbol;
import otava.symbols.derivations;
import otava.symbols.template_param_compare;
import otava.symbols.alias.group.symbol;
import otava.intermediate.types;
import otava.ast;
import util.uuid;

export namespace otava::symbols {

class Emitter;
class TemplateParameterSymbol;

class TypeSymbol : public ContainerSymbol
{
public:
    TypeSymbol(SymbolKind kind_, const std::u32string& name_);
    TypeSymbol(SymbolKind kind_, const util::uuid& id_, const std::u32string& name_);
    virtual TypeSymbol* GetBaseType() { return this; }
    virtual const TypeSymbol* GetBaseType() const { return this; }
    inline bool IsCompoundType() const { return Kind() == SymbolKind::compoundTypeSymbol; }
    bool IsAutoTypeSymbol() const;
    bool IsPointerType() const;
    bool IsArrayType() const;
    bool IsConstType() const;
    bool IsLValueRefType() const;
    bool IsRValueRefType() const;
    bool IsReferenceType() const;
    virtual std::expected<TypeSymbol*, int> PlainType(Context* context) { return std::expected<TypeSymbol*, int>(this); }
    virtual std::expected<TypeSymbol*, int> FinalType(const soul::ast::SourcePos& sourcePos, Context* context) { return std::expected<TypeSymbol*, int>(this); }
    virtual std::expected<TypeSymbol*, int> DirectType(Context* context) { return std::expected<TypeSymbol*, int>(this); }
    virtual bool HasBaseClass(TypeSymbol* baseClass, int& distance, Context* context) const { return false; }
    virtual bool IsVoidType() const { return false; }
    virtual bool IsBoolType() const { return false; }
    virtual bool IsDoubleType() const { return false; }
    virtual bool IsFloatType() const { return false; }
    virtual bool IsNullPtrType() const { return false; }
    virtual bool IsVoidPtrType() const { return false; }
    virtual bool IsIntegralType() const { return false; }
    virtual bool IsPolymorphic() const { return false; }
    virtual bool IsFunctionType() const { return false; }
    virtual bool IsBasicStringCharType(Context* context) { return false; }
    virtual bool IsBasicStringChar16Type(Context* context) { return false; }
    virtual bool IsBasicStringChar32Type(Context* context) { return false; }
    inline bool IsConstCharPtrType() const
    {
        return IsConstType() &&
            IsPointerType() &&
            PointerCount() == 1 &&
            (GetBaseType()->IsCharTypeSymbol() || GetBaseType()->IsChar8TypeSymbol());
    }
    inline bool IsConstChar16PtrType() const { return IsConstType() && IsPointerType() && PointerCount() == 1 && GetBaseType()->IsChar16TypeSymbol(); }
    inline bool IsConstChar32PtrType() const { return IsConstType() && IsPointerType() && PointerCount() == 1 && GetBaseType()->IsChar32TypeSymbol(); }
    inline bool IsFunctionPtrType() { return IsPointerType() && PointerCount() == 1 && GetBaseType()->IsFunctionType(); }
    virtual int PointerCount() const { return 0; }
    virtual Derivations GetDerivations() const { return Derivations::none; }
    virtual std::expected<TypeSymbol*, int> RemoveDerivations(Derivations sourceDerivations, Context* context);
    virtual std::expected<TypeSymbol*, int> Unify(TypeSymbol* argType, Context* context);
    virtual std::expected<TypeSymbol*, int> UnifyTemplateArgumentType(
        const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, Context* context);
    virtual bool IsComplete(std::set<const TypeSymbol*>& visited, const TypeSymbol*& incompleteType) const { return true; }
    std::expected<TypeSymbol*, int> AddConst(Context* context);
    std::expected<TypeSymbol*, int> RemoveConst(Context* context);
    std::expected<TypeSymbol*, int> AddPointer(Context* context);
    std::expected<TypeSymbol*, int> RemovePointer(Context* context);
    std::expected<TypeSymbol*, int> AddLValueRef(Context* context);
    std::expected<TypeSymbol*, int> RemoveLValueRef(Context* context);
    std::expected<TypeSymbol*, int> AddRValueRef(Context* context);
    std::expected<TypeSymbol*, int> RemoveRValueRef(Context* context);
    std::expected<TypeSymbol*, int> RemoveReference(Context* context);
    std::expected<TypeSymbol*, int> RemoveRefOrPtr(Context* context);
    std::expected<bool, int> AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    virtual std::expected<otava::intermediate::Type*, int> IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context);
    inline bool Valid() const { return error == 0; }
    inline int GetError() const { return error; }
    inline void SetError(int error_) { error = error_; }
    inline explicit operator bool() const { return Valid(); }
private:
    int error;
};

class NestedTypeSymbol : public TypeSymbol
{
public:
    NestedTypeSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    void Accept(Visitor& visitor) override;
};

class DependentTypeSymbol : public TypeSymbol
{
public:
    DependentTypeSymbol(const std::u32string& name_);
    DependentTypeSymbol(otava::ast::Node* node_);
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
    inline otava::ast::Node* GetNode() const { return node.get(); }
private:
    std::unique_ptr<otava::ast::Node> node;
};

class ErrorTypeSymbol : public TypeSymbol
{
public:
    ErrorTypeSymbol();
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    void Accept(Visitor& visitor) override;
};

class FunctionGroupTypeSymbol : public TypeSymbol
{
public:
    FunctionGroupTypeSymbol(const std::u32string& name_);
    FunctionGroupTypeSymbol(FunctionGroupSymbol* functionGroupSymbol_);
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    FunctionGroupSymbol* FunctionGroup() const { return functionGroupSymbol; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
private:
    FunctionGroupSymbol* functionGroupSymbol;
    util::uuid functionGroupSymbolId;
};

class ClassGroupTypeSymbol : public TypeSymbol
{
public:
    ClassGroupTypeSymbol(const std::u32string& name_);
    ClassGroupTypeSymbol(ClassGroupSymbol* classGroupSymbol_);
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    ClassGroupSymbol* ClassGroup() const { return classGroupSymbol; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
private:
    ClassGroupSymbol* classGroupSymbol;
    util::uuid classGroupSymbolId;
};

class AliasGroupTypeSymbol : public TypeSymbol
{
public:
    AliasGroupTypeSymbol(const std::u32string& name_);
    AliasGroupTypeSymbol(AliasGroupSymbol* aliasGroupSymbol_);
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    AliasGroupSymbol* AliasGroup() const { return aliasGroupSymbol; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
private:
    AliasGroupSymbol* aliasGroupSymbol;
    util::uuid aliasGroupSymbolId;
};

class GenericTypeSymbol : public TypeSymbol
{
public:
    static TypeSymbol* Instance();
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    void Accept(Visitor& visitor) override;
private:
    GenericTypeSymbol();
};

} // namespace otava::symbols
