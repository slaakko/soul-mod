// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.type.symbol;

import std.core;
import otava.symbols.container.symbol;
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
    virtual TypeSymbol* PlainType() { return this; }
    virtual bool IsVoidType() const { return false; }
    virtual bool IsBoolType() const { return false; }
    virtual bool IsPolymorphic() const { return false; }
    TypeSymbol* AddConst();
    TypeSymbol* RemoveConst();
    TypeSymbol* AddPointer();
    TypeSymbol* RemovePointer();
    TypeSymbol* AddLValueRef();
    TypeSymbol* RemoveLValueRef();
    TypeSymbol* AddRValueRef();
    TypeSymbol* RemoveRValueRef();
    TypeSymbol* DirectType();
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    virtual otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context);
    FunctionSymbol* DefaultCtor() { return defaultCtor; }
    void SetDefaultCtor(FunctionSymbol* defaultCtor_) { defaultCtor = defaultCtor_; }
    FunctionSymbol* CopyCtor() { return copyCtor; }
    void SetCopyCtor(FunctionSymbol* copyCtor_) { copyCtor = copyCtor_; }
    FunctionSymbol* MoveCtor() { return moveCtor; }
    void SetMoveCtor(FunctionSymbol* moveCtor_) { moveCtor = moveCtor_; }
    FunctionSymbol* CopyAssignment() { return copyAssignment; }
    void SetCopyAssignment(FunctionSymbol* copyAssignment_) { copyAssignment = copyAssignment_; }
    FunctionSymbol* MoveAssignment() { return moveAssignment; }
    void SetMoveAssignment(FunctionSymbol* moveAssignment_) { moveAssignment = moveAssignment_; }
    FunctionSymbol* Dtor() { return dtor; }
    void SetDtor(FunctionSymbol* dtor_) { dtor = dtor_; }
private:
    FunctionSymbol* defaultCtor;
    FunctionSymbol* copyCtor;
    FunctionSymbol* moveCtor;
    FunctionSymbol* copyAssignment;
    FunctionSymbol* moveAssignment;
    FunctionSymbol* dtor;
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
