// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.enums;

import std.core;
import otava.symbols.scope;
import otava.symbols.function.symbol;
import otava.symbols.type.symbol;
import otava.ast.node;

export namespace otava::symbols {

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
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsBound() const { return bound; }
    void SetBound() { bound = true; }
private:
    bool bound;
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

struct EnumTypeLessFunctor
{
    bool operator()(EnumeratedTypeSymbol* left, EnumeratedTypeSymbol* right) const;
};

class EnumTypeDefaultCtor : public FunctionSymbol
{
public:
    EnumTypeDefaultCtor(const std::u32string& name_);
    EnumTypeDefaultCtor(EnumeratedTypeSymbol* enumType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    util::uuid enumTypeId;
    EnumeratedTypeSymbol* enumType;
};

class EnumTypeCopyCtor : public FunctionSymbol
{
public:
    EnumTypeCopyCtor(const std::u32string& name_);
    EnumTypeCopyCtor(EnumeratedTypeSymbol* enumType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    util::uuid enumTypeId;
    EnumeratedTypeSymbol* enumType;
};

class EnumTypeMoveCtor : public FunctionSymbol
{
public:
    EnumTypeMoveCtor(const std::u32string& name_);
    EnumTypeMoveCtor(EnumeratedTypeSymbol* enumType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    util::uuid enumTypeId;
    EnumeratedTypeSymbol* enumType;
};

class EnumTypeCopyAssignment : public FunctionSymbol
{
public:
    EnumTypeCopyAssignment(const std::u32string& name_);
    EnumTypeCopyAssignment(EnumeratedTypeSymbol* enumType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    util::uuid enumTypeId;
    EnumeratedTypeSymbol* enumType;
};

class EnumTypeMoveAssignment : public FunctionSymbol
{
public:
    EnumTypeMoveAssignment(const std::u32string& name_);
    EnumTypeMoveAssignment(EnumeratedTypeSymbol* enumType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const override { return true; }
private:
    util::uuid enumTypeId;
    EnumeratedTypeSymbol* enumType;
};

class EnumTypeEqual : public FunctionSymbol
{
public:
    EnumTypeEqual(const std::u32string& name_);
    EnumTypeEqual(EnumeratedTypeSymbol* enumType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    util::uuid enumTypeId;
    EnumeratedTypeSymbol* enumType;
};

class EnumTypeLess : public FunctionSymbol
{
public:
    EnumTypeLess(const std::u32string& name_);
    EnumTypeLess(EnumeratedTypeSymbol* enumType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    util::uuid enumTypeId;
    EnumeratedTypeSymbol* enumType;
};


class Context;

void BeginEnumType(otava::ast::Node* node, Context* context);
void AddEnumerators(otava::ast::Node* node, Context* context);
void EndEnumType(otava::ast::Node* node, Context* context);
void ProcessEnumForwardDeclaration(otava::ast::Node* node, Context* context);
void BindEnumType(EnumeratedTypeSymbol* enumType, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
