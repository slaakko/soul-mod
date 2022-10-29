// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.fundamental.type.operation;

import otava.symbols.emitter;
import otava.symbols.function.symbol;
import otava.symbols.bound.tree.util;
import otava.intermediate.value;
import std.core;

export namespace otava::symbols {

class Context;
class SymbolTable;

struct FundamentalTypeNot
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* arg);
};

struct FundamentalTypeUnaryPlus
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* arg);
};

struct FundamentalTypeUnaryMinus
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* arg);
};

struct FundamentalTypeComplement
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* arg);
};

struct FundamentalTypeAdd
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeSub
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeMul
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeDiv
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeMod
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeAnd
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeOr
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeXor
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeShl
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeShr
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeEqual
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeLess
{
    static const char32_t* GroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

template<class Op>
class FundamentalTypeUnaryOperation : public FunctionSymbol
{
public:
    FundamentalTypeUnaryOperation(SymbolKind kind_) : FunctionSymbol(kind_, Op::GroupName())
    {
    }
    FundamentalTypeUnaryOperation(SymbolKind kind_, TypeSymbol* type_) : FunctionSymbol(kind_, Op::GroupName())
    {
        SetFunctionKind(FunctionKind::function);
        SetAccess(Access::public_);
        ParameterSymbol* param = new ParameterSymbol(U"param", type_);
        AddParameter(param, soul::ast::SourcePos(), nullptr);
        SetReturnType(type_);
    }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override
    {
        Load(emitter, args[0], OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* value = emitter.Stack().Pop();
        emitter.Stack().Push(Op::Generate(emitter, value));
    }
};

template<class Op>
class FundamentalTypeBinaryOperation : public FunctionSymbol
{
public:
    FundamentalTypeBinaryOperation(SymbolKind kind_) : FunctionSymbol(kind_, Op::GroupName())
    {
    }
    FundamentalTypeBinaryOperation(SymbolKind kind_, TypeSymbol* type_) : FunctionSymbol(kind_, Op::GroupName())
    {
        SetFunctionKind(FunctionKind::function);
        SetAccess(Access::public_);
        ParameterSymbol* leftParam = new ParameterSymbol(U"left", type_);
        AddParameter(leftParam, soul::ast::SourcePos(), nullptr);
        ParameterSymbol* rightParam = new ParameterSymbol(U"right", type_);
        AddParameter(rightParam, soul::ast::SourcePos(), nullptr);
        SetReturnType(type_);
    }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override
    {
        Load(emitter, args[0], OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* left = emitter.Stack().Pop();
        Load(emitter, args[1], OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* right = emitter.Stack().Pop();
        emitter.Stack().Push(Op::Generate(emitter, left, right));
    }
};

template<class Op>
class FundamentalTypeComparisonOperation : public FunctionSymbol
{
public:
    FundamentalTypeComparisonOperation(SymbolKind kind_) : FunctionSymbol(kind_, Op::GroupName())
    {
    }
    FundamentalTypeComparisonOperation(SymbolKind kind_, TypeSymbol* type_, TypeSymbol* boolType) : FunctionSymbol(kind_, Op::GroupName())
    {
        SetFunctionKind(FunctionKind::function);
        SetAccess(Access::public_);
        ParameterSymbol* leftParam = new ParameterSymbol(U"left", type_);
        AddParameter(leftParam, soul::ast::SourcePos(), nullptr);
        ParameterSymbol* rightParam = new ParameterSymbol(U"right", type_);
        AddParameter(rightParam, soul::ast::SourcePos(), nullptr);
        SetReturnType(boolType);
    }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override
    {
        Load(emitter, args[0], OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* left = emitter.Stack().Pop();
        Load(emitter, args[1], OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* right = emitter.Stack().Pop();
        emitter.Stack().Push(Op::Generate(emitter, left, right));
    }
};

class FundamentalTypeNotOperation : public FundamentalTypeUnaryOperation<FundamentalTypeNot>
{
public:
    FundamentalTypeNotOperation();
    FundamentalTypeNotOperation(TypeSymbol* type_);
};

class FundamentalTypeUnaryPlusOperation : public FundamentalTypeUnaryOperation<FundamentalTypeUnaryPlus>
{
public:
    FundamentalTypeUnaryPlusOperation();
    FundamentalTypeUnaryPlusOperation(TypeSymbol* type_);
};

class FundamentalTypeUnaryMinusOperation : public FundamentalTypeUnaryOperation<FundamentalTypeUnaryMinus>
{
public:
    FundamentalTypeUnaryMinusOperation();
    FundamentalTypeUnaryMinusOperation(TypeSymbol* type_);
};

class FundamentalTypeComplementOperation : public FundamentalTypeUnaryOperation<FundamentalTypeComplement>
{
public:
    FundamentalTypeComplementOperation();
    FundamentalTypeComplementOperation(TypeSymbol* type_);
};

class FundamentalTypeAddOperation : public FundamentalTypeBinaryOperation<FundamentalTypeAdd>
{
public:
    FundamentalTypeAddOperation();
    FundamentalTypeAddOperation(TypeSymbol* type_);
};

class FundamentalTypeSubOperation : public FundamentalTypeBinaryOperation<FundamentalTypeSub>
{
public:
    FundamentalTypeSubOperation();
    FundamentalTypeSubOperation(TypeSymbol* type_);
};

class FundamentalTypeMulOperation : public FundamentalTypeBinaryOperation<FundamentalTypeMul>
{
public:
    FundamentalTypeMulOperation();
    FundamentalTypeMulOperation(TypeSymbol* type_);
};

class FundamentalTypeDivOperation : public FundamentalTypeBinaryOperation<FundamentalTypeDiv>
{
public:
    FundamentalTypeDivOperation();
    FundamentalTypeDivOperation(TypeSymbol* type_);
};

class FundamentalTypeModOperation : public FundamentalTypeBinaryOperation<FundamentalTypeMod>
{
public:
    FundamentalTypeModOperation();
    FundamentalTypeModOperation(TypeSymbol* type_);
};

class FundamentalTypeAndOperation : public FundamentalTypeBinaryOperation<FundamentalTypeAnd>
{
public:
    FundamentalTypeAndOperation();
    FundamentalTypeAndOperation(TypeSymbol* type_);
};

class FundamentalTypeOrOperation : public FundamentalTypeBinaryOperation<FundamentalTypeOr>
{
public:
    FundamentalTypeOrOperation();
    FundamentalTypeOrOperation(TypeSymbol* type_);
};

class FundamentalTypeXorOperation : public FundamentalTypeBinaryOperation<FundamentalTypeXor>
{
public:
    FundamentalTypeXorOperation();
    FundamentalTypeXorOperation(TypeSymbol* type_);
};

class FundamentalTypeShlOperation : public FundamentalTypeBinaryOperation<FundamentalTypeShl>
{
public:
    FundamentalTypeShlOperation();
    FundamentalTypeShlOperation(TypeSymbol* type_);
};

class FundamentalTypeShrOperation : public FundamentalTypeBinaryOperation<FundamentalTypeShr>
{
public:
    FundamentalTypeShrOperation();
    FundamentalTypeShrOperation(TypeSymbol* type_);
};

class FundamentalTypeEqualOperation : public FundamentalTypeComparisonOperation<FundamentalTypeEqual>
{
public:
    FundamentalTypeEqualOperation();
    FundamentalTypeEqualOperation(TypeSymbol* type_, TypeSymbol* boolType_);
};

class FundamentalTypeLessOperation : public FundamentalTypeComparisonOperation<FundamentalTypeLess>
{
public:
    FundamentalTypeLessOperation();
    FundamentalTypeLessOperation(TypeSymbol* type_, TypeSymbol* boolType_);
};

class FundamentalTypeDefaultCtor : public FunctionSymbol
{
public:
    FundamentalTypeDefaultCtor();
    FundamentalTypeDefaultCtor(TypeSymbol* type_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* type;
    util::uuid typeId;
};

class FundamentalTypeCopyCtor : public FunctionSymbol
{
public:
    FundamentalTypeCopyCtor();
    FundamentalTypeCopyCtor(TypeSymbol* type_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* type;
    util::uuid typeId;
};

class FundamentalTypeMoveCtor : public FunctionSymbol
{
public:
    FundamentalTypeMoveCtor();
    FundamentalTypeMoveCtor(TypeSymbol* type_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* type;
    util::uuid typeId;
};

class FundamentalTypeCopyAssignment : public FunctionSymbol
{
public:
    FundamentalTypeCopyAssignment();
    FundamentalTypeCopyAssignment(TypeSymbol* type_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* type;
    util::uuid typeId;
};

class FundamentalTypeMoveAssignment : public FunctionSymbol
{
public:
    FundamentalTypeMoveAssignment();
    FundamentalTypeMoveAssignment(TypeSymbol* type_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
private:
    TypeSymbol* type;
    util::uuid typeId;
};

void AddFundamentalTypeOperationsToSymbolTable(Context* context);

} // namespace otava::symbols
