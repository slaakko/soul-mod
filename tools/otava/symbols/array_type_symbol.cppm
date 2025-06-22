// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.array.type.symbol;

import std;
import otava.symbols.type.symbol;
import otava.symbols.function.symbol;

export namespace otava::symbols {

class ArrayTypeSymbol : public TypeSymbol
{
public:
    ArrayTypeSymbol(const std::u32string& name_);
    ArrayTypeSymbol(TypeSymbol* elementType_, std::int64_t size_);
    std::string SymbolKindStr() const override { return "array type symbol"; }
    std::string SymbolDocKindStr() const override { return "array_type"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    TypeSymbol* ElementType() const { return elementType; }
    std::int64_t Size() const { return size; }
    void SetSize(std::int64_t size_) { size = size_; }
    otava::intermediate::Type* IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsBound() const { return bound; }
    void SetBound() { bound = true; }
    void Bind(const soul::ast::SourcePos& sourcePos, Context* context);
private:
    bool bound;
    TypeSymbol* elementType;
    util::uuid elementTypeId;
    std::int64_t size;
};

class ArrayTypeDefaultCtor : public FunctionSymbol
{
public:
    ArrayTypeDefaultCtor(const std::u32string& name_);
    ArrayTypeDefaultCtor(ArrayTypeSymbol* arrayType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeCopyCtor : public FunctionSymbol
{
public:
    ArrayTypeCopyCtor(const std::u32string& name_);
    ArrayTypeCopyCtor(ArrayTypeSymbol* arrayType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeMoveCtor : public FunctionSymbol
{
public:
    ArrayTypeMoveCtor(const std::u32string& name_);
    ArrayTypeMoveCtor(ArrayTypeSymbol* arrayType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeCopyAssignment : public FunctionSymbol
{
public:
    ArrayTypeCopyAssignment(const std::u32string& name_);
    ArrayTypeCopyAssignment(ArrayTypeSymbol* arrayType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeMoveAssignment : public FunctionSymbol
{
public:
    ArrayTypeMoveAssignment(const std::u32string& name_);
    ArrayTypeMoveAssignment(ArrayTypeSymbol* arrayType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeBegin : public FunctionSymbol
{
public:
    ArrayTypeBegin(const std::u32string& name_);
    ArrayTypeBegin(ArrayTypeSymbol* arrayType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeEnd : public FunctionSymbol
{
public:
    ArrayTypeEnd(const std::u32string& name_);
    ArrayTypeEnd(ArrayTypeSymbol* arrayType_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

} // namespace otava::symbols
