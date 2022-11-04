// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.type.symbol;

import std.core;
import otava.symbols.container.symbol;
import otava.symbols.derivations;
import otava.intermediate.type;

export namespace otava::symbols {

class Emitter;

class TypeSymbol : public ContainerSymbol
{
public:
    TypeSymbol(SymbolKind kind_, const std::u32string& name_);
    virtual TypeSymbol* GetBaseType() { return this; }
    bool IsAutoTypeSymbol() const;
    bool IsPointerType() const;
    bool IsConstType() const;
    bool IsLValueRefType() const;
    bool IsRValueRefType() const;
    bool IsReferenceType() const;
    virtual TypeSymbol* PlainType() { return this; }
    virtual bool IsVoidType() const { return false; }
    virtual bool IsBoolType() const { return false; }
    virtual bool IsNullPtrType() const { return false; }
    virtual bool IsIntegralType() const { return false; }
    virtual bool IsPolymorphic() const { return false; }
    virtual int PointerCount() const { return 0; }
    virtual const Derivations& GetDerivations() const;
    virtual TypeSymbol* RemoveDerivations(const Derivations& sourceDerivations, Context* context);
    virtual TypeSymbol* Unify(TypeSymbol* argType, Context* context);
    TypeSymbol* AddConst();
    TypeSymbol* RemoveConst();
    TypeSymbol* AddPointer();
    TypeSymbol* RemovePointer();
    TypeSymbol* AddLValueRef();
    TypeSymbol* RemoveLValueRef();
    TypeSymbol* AddRValueRef();
    TypeSymbol* RemoveRValueRef();
    TypeSymbol* RemoveReference();
    TypeSymbol* RemoveRefOrPtr();
    TypeSymbol* DirectType();
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

bool TypesEqual(TypeSymbol* left, TypeSymbol* right);

} // namespace otava::symbols
