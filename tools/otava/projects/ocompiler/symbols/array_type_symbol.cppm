// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.array.type.symbol;

import std;
import otava.symbols.type.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.context;
import otava.symbols.symbol.table;

export namespace otava::symbols {

class ArrayTypeSymbol : public TypeSymbol
{
public:
    ArrayTypeSymbol(const std::u32string& name_);
    ArrayTypeSymbol(TypeSymbol* elementType_, std::int64_t size_);
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    inline TypeSymbol* ElementType() const { return elementType; }
    inline std::int64_t Size() const { return size; }
    inline void SetSize(std::int64_t size_) { size = size_; }
    std::expected<otava::intermediate::Type*, int> IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline bool IsBound() const { return bound; }
    inline void SetBound() { bound = true; }
    std::expected<bool, int> Bind(const soul::ast::SourcePos& sourcePos, Context* context);
    void SetError(int error_) { error = error_; }
    int GetError() const { return error; }
    inline bool Valid() const { return error == 0; }
    inline operator bool() const { return Valid(); }
private:
    bool bound;
    TypeSymbol* elementType;
    util::uuid elementTypeId;
    std::int64_t size;
    int error;
};

class ArrayTypeDefaultCtor : public FunctionSymbol
{
public:
    ArrayTypeDefaultCtor(const std::u32string& name_);
    ArrayTypeDefaultCtor(ArrayTypeSymbol* arrayType_, Context* context);
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    std::expected<ParameterSymbol*, int> ThisParam(Context* context) const override { return std::expected<ParameterSymbol*, int>(nullptr); }
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeCopyCtor : public FunctionSymbol
{
public:
    ArrayTypeCopyCtor(const std::u32string& name_);
    ArrayTypeCopyCtor(ArrayTypeSymbol* arrayType_, Context* context);
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    std::expected<ParameterSymbol*, int> ThisParam(Context* context) const override { return std::expected<ParameterSymbol*, int>(nullptr); }
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeMoveCtor : public FunctionSymbol
{
public:
    ArrayTypeMoveCtor(const std::u32string& name_);
    ArrayTypeMoveCtor(ArrayTypeSymbol* arrayType_, Context* context);
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    std::expected<ParameterSymbol*, int> ThisParam(Context* context) const override { return std::expected<ParameterSymbol*, int>(nullptr); }
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeCopyAssignment : public FunctionSymbol
{
public:
    ArrayTypeCopyAssignment(const std::u32string& name_);
    ArrayTypeCopyAssignment(ArrayTypeSymbol* arrayType_, Context* context);
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    std::expected<ParameterSymbol*, int> ThisParam(Context* context) const override { return std::expected<ParameterSymbol*, int>(nullptr); }
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeMoveAssignment : public FunctionSymbol
{
public:
    ArrayTypeMoveAssignment(const std::u32string& name_);
    ArrayTypeMoveAssignment(ArrayTypeSymbol* arrayType_, Context* context);
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    std::expected<ParameterSymbol*, int> ThisParam(Context* context) const override { return std::expected<ParameterSymbol*, int>(nullptr); }
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeBegin : public FunctionSymbol
{
public:
    ArrayTypeBegin(const std::u32string& name_);
    ArrayTypeBegin(ArrayTypeSymbol* arrayType_, Context* context);
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    std::expected<ParameterSymbol*, int> ThisParam(Context* context) const override { return std::expected<ParameterSymbol*, int>(nullptr); }
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

class ArrayTypeEnd : public FunctionSymbol
{
public:
    ArrayTypeEnd(const std::u32string& name_);
    ArrayTypeEnd(ArrayTypeSymbol* arrayType_, Context* context);
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    std::expected<bool, int> GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    std::expected<ParameterSymbol*, int> ThisParam(Context* context) const override { return std::expected<ParameterSymbol*, int>(nullptr); }
private:
    ArrayTypeSymbol* arrayType;
    util::uuid arrayTypeId;
};

} // namespace otava::symbols
