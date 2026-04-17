// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.enums;

import std;
import otava.symbols.context;
import otava.symbols.scope;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.type.symbol;
import otava.ast.node;

export namespace otava::symbols {

class Value;

enum class EnumTypeKind : std::uint8_t
{
    enum_, enumClass, enumStruct
};

class EnumeratedTypeSymbol : public TypeSymbol
{
public:
    EnumeratedTypeSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "enumerated type symbol"; }
    std::string SymbolDocKindStr() const override { return "enum_type"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    inline EnumTypeKind GetEnumTypeKind() const noexcept { return kind; }
    inline void SetEnumTypeKind(EnumTypeKind kind_) noexcept { kind = kind_; }
    inline TypeSymbol* UnderlyingType() const noexcept { return underlyingType; }
    inline void SetUnderlyingType(TypeSymbol* underlyingType_) noexcept { underlyingType = underlyingType_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline bool IsBound() const noexcept { return bound; }
    inline void SetBound() noexcept { bound = true; }
    int Rank() const noexcept override { return underlyingType ? underlyingType->Rank() : -1; }
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
    inline void SetEnumTypeKind(EnumTypeKind enumTypeKind_) noexcept { enumTypeKind = enumTypeKind_; }
    inline EnumTypeKind GetEnumTypeKind() const noexcept { return enumTypeKind; }
    inline TypeSymbol* GetUnderlyingType() const noexcept { return underlyingType; }
    inline void SetUnderlyingType(TypeSymbol* underlyingType_) noexcept { underlyingType = underlyingType_; }
    inline void SetEnumeratedTypeSymbol(EnumeratedTypeSymbol* enumTypeSymbol_) noexcept { enumTypeSymbol = enumTypeSymbol_; }
    inline EnumeratedTypeSymbol* GetEnumeratedTypeSymbol() const noexcept { return enumTypeSymbol; }
    std::string SymbolKindStr() const override { return "forward enum declaration symbol"; }
    std::string SymbolDocKindStr() const override { return "forward_enum"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
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
    Value* GetValue() const noexcept { return value; }
    void SetValue(Value* value_) noexcept { value = value_; }
    std::string SymbolKindStr() const override { return "enum constant symbol"; }
    std::string SymbolDocKindStr() const override { return "enum_constant"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    inline EnumeratedTypeSymbol* GetEnumType() const noexcept { return enumType; }
    inline void SetEnumType(EnumeratedTypeSymbol* enumType_) noexcept { enumType = enumType_; }
private:
    Value* value;
    util::uuid valueId;
    EnumeratedTypeSymbol* enumType;
    util::uuid enumTypeId;
};

struct EnumTypeLessFunctor
{
    bool operator()(EnumeratedTypeSymbol* left, EnumeratedTypeSymbol* right) const noexcept;
};

class EnumTypeDefaultCtor : public FunctionSymbol
{
public:
    EnumTypeDefaultCtor(const std::u32string& name_);
    EnumTypeDefaultCtor(EnumeratedTypeSymbol* enumType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const noexcept override { return true; }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
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
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const noexcept override { return true; }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
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
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const noexcept override { return true; }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
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
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const noexcept override { return true; }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
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
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const noexcept override { return true; }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
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
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
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
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
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
