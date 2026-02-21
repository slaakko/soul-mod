// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.fundamental.type.operation;

import otava.symbols.emitter;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.context;
import otava.intermediate.data;
import std;

export namespace otava::symbols {

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
    static const char32_t* AssignmentOpGroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeSub
{
    static const char32_t* GroupName();
    static const char32_t* AssignmentOpGroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeMul
{
    static const char32_t* GroupName();
    static const char32_t* AssignmentOpGroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeDiv
{
    static const char32_t* GroupName();
    static const char32_t* AssignmentOpGroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeMod
{
    static const char32_t* GroupName();
    static const char32_t* AssignmentOpGroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeAnd
{
    static const char32_t* GroupName();
    static const char32_t* AssignmentOpGroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeOr
{
    static const char32_t* GroupName();
    static const char32_t* AssignmentOpGroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeXor
{
    static const char32_t* GroupName();
    static const char32_t* AssignmentOpGroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeShl
{
    static const char32_t* GroupName();
    static const char32_t* AssignmentOpGroupName();
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right);
};

struct FundamentalTypeShr
{
    static const char32_t* GroupName();
    static const char32_t* AssignmentOpGroupName();
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
    FundamentalTypeUnaryOperation(SymbolKind kind_, TypeSymbol* type_, Context* context) : FunctionSymbol(kind_, Op::GroupName())
    {
        SetFunctionKind(FunctionKind::function);
        SetAccess(Access::public_);
        ParameterSymbol* param = new ParameterSymbol(U"param", type_);
        AddParameter(param, soul::ast::SourcePos(), nullptr);
        SetReturnType(type_, context);
        SetNoExcept();
    }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override
    {
        args[0]->Load(emitter, flags, sourcePos, context);
        otava::intermediate::Value* value = emitter.Stack().Pop();
        emitter.Stack().Push(Op::Generate(emitter, value));
    }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
};

template<class Op>
class FundamentalTypeBinaryOperation : public FunctionSymbol
{
public:
    FundamentalTypeBinaryOperation(SymbolKind kind_) : FunctionSymbol(kind_, Op::GroupName())
    {
    }
    FundamentalTypeBinaryOperation(SymbolKind kind_, TypeSymbol* type_, Context* context) : FunctionSymbol(kind_, Op::GroupName())
    {
        SetFunctionKind(FunctionKind::function);
        SetAccess(Access::public_);
        ParameterSymbol* leftParam = new ParameterSymbol(U"left", type_);
        AddParameter(leftParam, soul::ast::SourcePos(), nullptr);
        ParameterSymbol* rightParam = new ParameterSymbol(U"right", type_);
        AddParameter(rightParam, soul::ast::SourcePos(), nullptr);
        SetReturnType(type_, context);
        SetNoExcept();
    }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override
    {
        args[0]->Load(emitter, flags, sourcePos, context);
        otava::intermediate::Value* left = emitter.Stack().Pop();
        args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* right = emitter.Stack().Pop();
        emitter.Stack().Push(Op::Generate(emitter, left, right));
    }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
};

template<typename Op>
class FundamentalTypeAssignmentOperation : public FunctionSymbol
{
public:
    FundamentalTypeAssignmentOperation(SymbolKind kind_) : FunctionSymbol(kind_, Op::AssignmentOpGroupName())
    {
    }
    FundamentalTypeAssignmentOperation(SymbolKind kind_, TypeSymbol* type_, Context* context) : FunctionSymbol(kind_, Op::AssignmentOpGroupName()), type(type_)
    {
        SetFunctionKind(FunctionKind::function);
        SetAccess(Access::public_);
        ParameterSymbol* thisParam = new ParameterSymbol(U"this", type);
        AddParameter(thisParam, soul::ast::SourcePos(), context);
        ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
        AddParameter(thatParam, soul::ast::SourcePos(), context);
        SetReturnType(type->AddLValueRef(context), context);
        SetNoExcept();
    }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
    {
        args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* left = emitter.Stack().Pop();
        args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* right = emitter.Stack().Pop();
        emitter.Stack().Push(Op::Generate(emitter, left, right));
        args[0]->Store(emitter, OperationFlags::setPtr, sourcePos, context);
        emitter.Stack().Push(context->Ptr());
    }
    bool IsCtorAssignmentOrArrow() const noexcept override { return true; }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
private:
    TypeSymbol* type;
};

template<class Op>
class FundamentalTypeComparisonOperation : public FunctionSymbol
{
public:
    FundamentalTypeComparisonOperation(SymbolKind kind_) : FunctionSymbol(kind_, Op::GroupName())
    {
    }
    FundamentalTypeComparisonOperation(SymbolKind kind_, TypeSymbol* type_, TypeSymbol* boolType, Context* context) : FunctionSymbol(kind_, Op::GroupName())
    {
        SetFunctionKind(FunctionKind::function);
        SetAccess(Access::public_);
        ParameterSymbol* leftParam = new ParameterSymbol(U"left", type_);
        AddParameter(leftParam, soul::ast::SourcePos(), nullptr);
        ParameterSymbol* rightParam = new ParameterSymbol(U"right", type_);
        AddParameter(rightParam, soul::ast::SourcePos(), nullptr);
        SetReturnType(boolType, context);
        SetNoExcept();
    }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override
    {
        args[0]->Load(emitter, flags, sourcePos, context);
        otava::intermediate::Value* left = emitter.Stack().Pop();
        args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* right = emitter.Stack().Pop();
        emitter.Stack().Push(Op::Generate(emitter, left, right));
    }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
};

class FundamentalTypeNotOperation : public FundamentalTypeUnaryOperation<FundamentalTypeNot>
{
public:
    FundamentalTypeNotOperation();
    FundamentalTypeNotOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeUnaryPlusOperation : public FundamentalTypeUnaryOperation<FundamentalTypeUnaryPlus>
{
public:
    FundamentalTypeUnaryPlusOperation();
    FundamentalTypeUnaryPlusOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeUnaryMinusOperation : public FundamentalTypeUnaryOperation<FundamentalTypeUnaryMinus>
{
public:
    FundamentalTypeUnaryMinusOperation();
    FundamentalTypeUnaryMinusOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeComplementOperation : public FundamentalTypeUnaryOperation<FundamentalTypeComplement>
{
public:
    FundamentalTypeComplementOperation();
    FundamentalTypeComplementOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeAddOperation : public FundamentalTypeBinaryOperation<FundamentalTypeAdd>
{
public:
    FundamentalTypeAddOperation();
    FundamentalTypeAddOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeSubOperation : public FundamentalTypeBinaryOperation<FundamentalTypeSub>
{
public:
    FundamentalTypeSubOperation();
    FundamentalTypeSubOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeMulOperation : public FundamentalTypeBinaryOperation<FundamentalTypeMul>
{
public:
    FundamentalTypeMulOperation();
    FundamentalTypeMulOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeDivOperation : public FundamentalTypeBinaryOperation<FundamentalTypeDiv>
{
public:
    FundamentalTypeDivOperation();
    FundamentalTypeDivOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeModOperation : public FundamentalTypeBinaryOperation<FundamentalTypeMod>
{
public:
    FundamentalTypeModOperation();
    FundamentalTypeModOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeAndOperation : public FundamentalTypeBinaryOperation<FundamentalTypeAnd>
{
public:
    FundamentalTypeAndOperation();
    FundamentalTypeAndOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeOrOperation : public FundamentalTypeBinaryOperation<FundamentalTypeOr>
{
public:
    FundamentalTypeOrOperation();
    FundamentalTypeOrOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeXorOperation : public FundamentalTypeBinaryOperation<FundamentalTypeXor>
{
public:
    FundamentalTypeXorOperation();
    FundamentalTypeXorOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeShlOperation : public FundamentalTypeBinaryOperation<FundamentalTypeShl>
{
public:
    FundamentalTypeShlOperation();
    FundamentalTypeShlOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeShrOperation : public FundamentalTypeBinaryOperation<FundamentalTypeShr>
{
public:
    FundamentalTypeShrOperation();
    FundamentalTypeShrOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypePlusAssignOperation : public FundamentalTypeAssignmentOperation<FundamentalTypeAdd>
{
public:
    FundamentalTypePlusAssignOperation();
    FundamentalTypePlusAssignOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeMinusAssignOperation : public FundamentalTypeAssignmentOperation<FundamentalTypeSub>
{
public:
    FundamentalTypeMinusAssignOperation();
    FundamentalTypeMinusAssignOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeMulAssignOperation : public FundamentalTypeAssignmentOperation<FundamentalTypeMul>
{
public:
    FundamentalTypeMulAssignOperation();
    FundamentalTypeMulAssignOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeDivAssignOperation : public FundamentalTypeAssignmentOperation<FundamentalTypeDiv>
{
public:
    FundamentalTypeDivAssignOperation();
    FundamentalTypeDivAssignOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeModAssignOperation : public FundamentalTypeAssignmentOperation<FundamentalTypeMod>
{
public:
    FundamentalTypeModAssignOperation();
    FundamentalTypeModAssignOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeAndAssignOperation : public FundamentalTypeAssignmentOperation<FundamentalTypeAnd>
{
public:
    FundamentalTypeAndAssignOperation();
    FundamentalTypeAndAssignOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeOrAssignOperation : public FundamentalTypeAssignmentOperation<FundamentalTypeOr>
{
public:
    FundamentalTypeOrAssignOperation();
    FundamentalTypeOrAssignOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeXorAssignOperation : public FundamentalTypeAssignmentOperation<FundamentalTypeXor>
{
public:
    FundamentalTypeXorAssignOperation();
    FundamentalTypeXorAssignOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeShlAssignOperation : public FundamentalTypeAssignmentOperation<FundamentalTypeShl>
{
public:
    FundamentalTypeShlAssignOperation();
    FundamentalTypeShlAssignOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeShrAssignOperation : public FundamentalTypeAssignmentOperation<FundamentalTypeShr>
{
public:
    FundamentalTypeShrAssignOperation();
    FundamentalTypeShrAssignOperation(TypeSymbol* type_, Context* context);
};

class FundamentalTypeEqualOperation : public FundamentalTypeComparisonOperation<FundamentalTypeEqual>
{
public:
    FundamentalTypeEqualOperation();
    FundamentalTypeEqualOperation(TypeSymbol* type_, TypeSymbol* boolType_, Context* context);
};

class FundamentalTypeLessOperation : public FundamentalTypeComparisonOperation<FundamentalTypeLess>
{
public:
    FundamentalTypeLessOperation();
    FundamentalTypeLessOperation(TypeSymbol* type_, TypeSymbol* boolType_, Context* context);
};

class FundamentalTypeDefaultCtor : public FunctionSymbol
{
public:
    FundamentalTypeDefaultCtor();
    FundamentalTypeDefaultCtor(TypeSymbol* type_, Context* context);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const noexcept override { return true; }
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
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const noexcept override { return true; }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
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
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const noexcept override { return true; }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
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
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const noexcept override { return true; }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
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
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    bool IsCtorAssignmentOrArrow() const noexcept override { return true; }
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
private:
    TypeSymbol* type;
    util::uuid typeId;
};

class TrivialDestructor : public FunctionSymbol
{
public:
    TrivialDestructor();
    TrivialDestructor(TypeSymbol* type_, Context* context);
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override;
    ParameterSymbol* ThisParam(Context* context) const override { return nullptr; }
private:
    TypeSymbol* type;
};

void AddFundamentalTypeOperationsToSymbolTable(Context* context);

} // namespace otava::symbols
