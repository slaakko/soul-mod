// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.fundamental.type.operation;

import otava.symbols.emitter;
import otava.symbols.function.symbol;
import otava.symbols.bound.tree;
import otava.intermediate.data;
import std.core;

export namespace otava::symbols {

class SymbolTable;

struct FundamentalTypeAdd
{
    static const char32_t* GroupName() { return  U"operator+"; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitAdd(left, right); }
};

struct FundamentalTypeSub
{
    static const char32_t* GroupName() { return  U"operator-"; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitSub(left, right); }
};

struct FundamentalTypeMul
{
    static const char32_t* GroupName() { return  U"operator*"; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitMul(left, right); }
};

struct FundamentalTypeDiv
{
    static const char32_t* GroupName() { return  U"operator/"; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitDiv(left, right); }
};

struct FundamentalTypeMod
{
    static const char32_t* GroupName() { return  U"operator%"; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitMod(left, right); }
};

struct FundamentalTypeAnd
{
    static const char32_t* GroupName() { return  U"operator&"; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitAnd(left, right); }
};

struct FundamentalTypeOr
{
    static const char32_t* GroupName() { return  U"operator|"; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitOr(left, right); }
};

struct FundamentalTypeXor
{
    static const char32_t* GroupName() { return  U"operator^"; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitXor(left, right); }
};

struct FundamentalTypeShl
{
    static const char32_t* GroupName() { return  U"operator<<"; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitShl(left, right); }
};

struct FundamentalTypeShr
{
    static const char32_t* GroupName() { return  U"operator>>"; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitShr(left, right); }
};

struct FundamentalTypeEqual
{
    static const char32_t* GroupName() { return  U"operator=="; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitEqual(left, right); }
};

struct FundamentalTypeLess
{
    static const char32_t* GroupName() { return  U"operator<"; }
    static otava::intermediate::Value* Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right) { return emitter.EmitLess(left, right); }
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
        ParameterSymbol* leftParam = new ParameterSymbol(U"left", type_);
        AddParameter(leftParam, soul::ast::SourcePos(), nullptr);
        ParameterSymbol* rightParam = new ParameterSymbol(U"right", type_);
        AddParameter(rightParam, soul::ast::SourcePos(), nullptr);
        SetReturnType(type_);
    }
    void GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) override
    {
        args[0]->Load(emitter, OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* left = emitter.Stack().Pop();
        args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* right = emitter.Stack().Pop();
        emitter.Stack().Push(Op::Generate(emitter, left, right));
    }
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

class FundamentalTypeEqualOperation : public FundamentalTypeBinaryOperation<FundamentalTypeEqual>
{
public:
    FundamentalTypeEqualOperation();
    FundamentalTypeEqualOperation(TypeSymbol* type_);
};

class FundamentalTypeLessOperation : public FundamentalTypeBinaryOperation<FundamentalTypeLess>
{
public:
    FundamentalTypeLessOperation();
    FundamentalTypeLessOperation(TypeSymbol* type_);
};

void AddFundamentalTypeOperationsToSymbolTable(SymbolTable& symbolTable);

} // namespace otava::symbols
