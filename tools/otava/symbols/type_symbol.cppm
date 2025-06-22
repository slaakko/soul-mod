// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.type.symbol;

import std.core;
import otava.symbols.container.symbol;
import otava.symbols.derivations;
import otava.symbols.template_param_compare;
import otava.intermediate.type;
import util.uuid;

export namespace otava::symbols {

class Emitter;
class TemplateParameterSymbol;

class TypeSymbol : public ContainerSymbol
{
public:
    TypeSymbol(SymbolKind kind_, const std::u32string& name_);
    virtual TypeSymbol* GetBaseType() { return this; }
    bool IsCompoundType() const { return Kind() == SymbolKind::compoundTypeSymbol; }
    bool IsAutoTypeSymbol() const;
    bool IsPointerType() const;
    bool IsArrayType() const;
    bool IsConstType() const;
    bool IsLValueRefType() const;
    bool IsRValueRefType() const;
    bool IsReferenceType() const;
    virtual TypeSymbol* PlainType(Context* context) { return this; }
    virtual TypeSymbol* FinalType(const soul::ast::SourcePos& sourcePos, Context* context) { return this; }
    virtual TypeSymbol* DirectType(Context* context) { return this; }
    virtual bool HasBaseClass(TypeSymbol* baseClass, int& distance) const { return false; }
    virtual bool IsVoidType() const { return false; }
    virtual bool IsBoolType() const { return false; }
    virtual bool IsNullPtrType() const { return false; }
    virtual bool IsVoidPtrType() const { return false; }
    virtual bool IsIntegralType() const { return false; }
    virtual bool IsPolymorphic() const { return false; }
    virtual int PointerCount() const { return 0; }
    virtual const Derivations& GetDerivations() const;
    virtual TypeSymbol* RemoveDerivations(const Derivations& sourceDerivations, Context* context);
    virtual TypeSymbol* Unify(TypeSymbol* argType, Context* context);
    virtual TypeSymbol* UnifyTemplateArgumentType(const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, Context* context) { return nullptr; }
    virtual bool IsComplete(std::set<const TypeSymbol*>& visited) const { return true; }
    TypeSymbol* AddConst(Context* context);
    TypeSymbol* RemoveConst(Context* context);
    TypeSymbol* AddPointer(Context* context);
    TypeSymbol* RemovePointer(Context* context);
    TypeSymbol* AddLValueRef(Context* context);
    TypeSymbol* RemoveLValueRef(Context* context);
    TypeSymbol* AddRValueRef(Context* context);
    TypeSymbol* RemoveRValueRef(Context* context);
    TypeSymbol* RemoveReference(Context* context);
    TypeSymbol* RemoveRefOrPtr(Context* context);
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    virtual otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context);
};

class NestedTypeSymbol : public TypeSymbol
{
public:
    NestedTypeSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "nested type symbol"; }
    std::string SymbolDocKindStr() const override { return "nested_type"; }
    void Accept(Visitor& visitor) override;
};

class ErrorTypeSymbol : public TypeSymbol
{
public:
    ErrorTypeSymbol();
    std::string SymbolKindStr() const override { return "error type symbol"; }
    std::string SymbolDocKindStr() const override { return "error_type"; }
    void Accept(Visitor& visitor) override;
};

class FunctionGroupTypeSymbol : public TypeSymbol
{
public:
    FunctionGroupTypeSymbol(const std::u32string& name_);
    FunctionGroupTypeSymbol(FunctionGroupSymbol* functionGroupSymbol_);
    std::string SymbolKindStr() const override { return "function group type symbol"; }
    std::string SymbolDocKindStr() const override { return "function_group_type"; }
    FunctionGroupSymbol* FunctionGroup() const { return functionGroupSymbol; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    FunctionGroupSymbol* functionGroupSymbol;
    util::uuid functionGroupSymbolId;
};

class GenericTypeSymbol : public TypeSymbol
{
public:
    static TypeSymbol* Instance();
    std::string SymbolKindStr() const override { return "generic type symbol"; }
    std::string SymbolDocKindStr() const override { return "generic_type"; }
    void Accept(Visitor& visitor) override;
private:
    GenericTypeSymbol();
};

} // namespace otava::symbols
