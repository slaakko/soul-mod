// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.type.symbol;

import std.core;
import otava.symbols.container.symbol;
import otava.symbols.emitter;
import otava.intermediate.type;

export namespace otava::symbols {

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
    TypeSymbol* AddConst();
    TypeSymbol* RemoveConst();
    TypeSymbol* AddPointer();
    TypeSymbol* RemovePointer();
    TypeSymbol* AddLValueRef();
    TypeSymbol* RemoveLValueRef();
    TypeSymbol* AddRValueRef();
    TypeSymbol* RemoveRValueRef();
    TypeSymbol* DirectType();
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

} // namespace otava::symbols
