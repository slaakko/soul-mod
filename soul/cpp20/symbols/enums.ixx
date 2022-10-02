// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.enums;

import std.core;
import soul.cpp20.symbols.scope;
import soul.cpp20.symbols.type.symbol;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

class Value;

enum class EnumTypeKind
{
    enum_, enumClass, enumStruct
};

class EnumeratedTypeSymbol : public TypeSymbol
{
public:
    EnumeratedTypeSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "enumerated type symbol"; }
    std::string SymbolDocKindStr() const override { return "enum_type"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    EnumTypeKind GetEnumTypeKind() const { return kind; }
    void SetEnumTypeKind(EnumTypeKind kind_) { kind = kind_; }
    TypeSymbol* UnderlyingType() const { return underlyingType; }
    void SetUnderlyingType(TypeSymbol* underlyingType_) { underlyingType = underlyingType_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    EnumTypeKind kind;
    TypeSymbol* underlyingType;
    util::uuid underlyingTypeId;
};

class ForwardEnumDeclarationSymbol : public TypeSymbol
{
public:
    ForwardEnumDeclarationSymbol(const std::u32string& name_);
    void SetEnumTypeKind(EnumTypeKind enumTypeKind_) { enumTypeKind = enumTypeKind_; }
    EnumTypeKind GetEnumTypeKind() const { return enumTypeKind; }
    TypeSymbol* GetUnderlyingType() const { return underlyingType; }
    void SetUnderlyingType(TypeSymbol* underlyingType_) { underlyingType = underlyingType_; }
    void SetEnumeratedTypeSymbol(EnumeratedTypeSymbol* enumTypeSymbol_) { enumTypeSymbol = enumTypeSymbol_; }
    EnumeratedTypeSymbol* GetEnumeratedTypeSymbol() const { return enumTypeSymbol; }
    std::string SymbolKindStr() const override { return "forward enum declaration symbol"; }
    std::string SymbolDocKindStr() const override { return "forward_enum"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
private:
    EnumTypeKind enumTypeKind;
    TypeSymbol* underlyingType;
    util::uuid underlyingTypeId;
    EnumeratedTypeSymbol* enumTypeSymbol;
    util::uuid enumTypeSymbolId;
};

class EnumConstantSymbol : public Symbol
{
public:
    EnumConstantSymbol(const std::u32string& name_);
    Value* GetValue() const { return value; }
    void SetValue(Value* value_) { value = value_; }
    std::string SymbolKindStr() const override { return "enum constant symbol"; }
    std::string SymbolDocKindStr() const override { return "enum_constant"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    EnumeratedTypeSymbol* GetType() const;
private:
    Value* value;
    util::uuid valueId;
};

struct EnumTypeLess
{
    bool operator()(EnumeratedTypeSymbol* left, EnumeratedTypeSymbol* right) const;
};

class Context;

void BeginEnumType(soul::cpp20::ast::Node* node, Context* context);
void AddEnumerators(soul::cpp20::ast::Node* node, Context* context);
void EndEnumType(soul::cpp20::ast::Node* node, Context* context);
void ProcessEnumForwardDeclaration(soul::cpp20::ast::Node* node, Context* context);

} // namespace soul::cpp20::symbols
