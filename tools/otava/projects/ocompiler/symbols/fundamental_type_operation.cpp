// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.fundamental.type.operation;

import otava.symbols.fundamental.type.conversion.init;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.bound.tree;
import otava.symbols.symbol.table;
import otava.symbols.context;
import otava.symbols.namespaces;
import otava.symbols.type.symbol;
import util;

namespace otava::symbols {

const char32_t* FundamentalTypeNot::GroupName()
{
    return U"operator!";
}

otava::intermediate::Value* FundamentalTypeNot::Generate(Emitter& emitter, otava::intermediate::Value* arg)
{
    return emitter.EmitNot(arg);
}

const char32_t* FundamentalTypeUnaryPlus::GroupName()
{
    return U"operator+";
}

otava::intermediate::Value* FundamentalTypeUnaryPlus::Generate(Emitter& emitter, otava::intermediate::Value* arg)
{
    return arg;
}

const char32_t* FundamentalTypeUnaryMinus::GroupName()
{
    return U"operator-";
}

otava::intermediate::Value* FundamentalTypeUnaryMinus::Generate(Emitter& emitter, otava::intermediate::Value* arg)
{
    return emitter.EmitNeg(arg);
}

const char32_t* FundamentalTypeComplement::GroupName()
{
    return U"operator~";
}

otava::intermediate::Value* FundamentalTypeComplement::Generate(Emitter& emitter, otava::intermediate::Value* arg)
{
    return emitter.EmitNot(arg);
}

const char32_t* FundamentalTypeAdd::GroupName()
{
    return U"operator+";
}

const char32_t* FundamentalTypeAdd::AssignmentOpGroupName()
{
    return U"operator+=";
}

otava::intermediate::Value* FundamentalTypeAdd::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitAdd(left, right);
}

const char32_t* FundamentalTypeSub::GroupName()
{
    return U"operator-";
}

const char32_t* FundamentalTypeSub::AssignmentOpGroupName()
{
    return U"operator-=";
}

otava::intermediate::Value* FundamentalTypeSub::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitSub(left, right);
}

const char32_t* FundamentalTypeMul::GroupName()
{
    return U"operator*";
}

const char32_t* FundamentalTypeMul::AssignmentOpGroupName()
{
    return U"operator*=";
}

otava::intermediate::Value* FundamentalTypeMul::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitMul(left, right);
}

const char32_t* FundamentalTypeDiv::GroupName()
{
    return U"operator/";
}

const char32_t* FundamentalTypeDiv::AssignmentOpGroupName()
{
    return U"operator/=";
}

otava::intermediate::Value* FundamentalTypeDiv::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitDiv(left, right);
}

const char32_t* FundamentalTypeMod::GroupName()
{
    return U"operator%";
}

const char32_t* FundamentalTypeMod::AssignmentOpGroupName()
{
    return U"operator%=";
}

otava::intermediate::Value* FundamentalTypeMod::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitMod(left, right);
}

const char32_t* FundamentalTypeAnd::GroupName()
{
    return U"operator&";
}

const char32_t* FundamentalTypeAnd::AssignmentOpGroupName()
{
    return U"operator&=";
}

otava::intermediate::Value* FundamentalTypeAnd::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitAnd(left, right);
}

const char32_t* FundamentalTypeOr::GroupName()
{
    return U"operator|";
}

const char32_t* FundamentalTypeOr::AssignmentOpGroupName()
{
    return U"operator|=";
}

otava::intermediate::Value* FundamentalTypeOr::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitOr(left, right);
}

const char32_t* FundamentalTypeXor::GroupName()
{
    return U"operator^";
}

const char32_t* FundamentalTypeXor::AssignmentOpGroupName()
{
    return U"operator^=";
}

otava::intermediate::Value* FundamentalTypeXor::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitXor(left, right);
}

const char32_t* FundamentalTypeShl::GroupName()
{
    return U"operator<<";
}

const char32_t* FundamentalTypeShl::AssignmentOpGroupName()
{
    return U"operator<<=";
}

otava::intermediate::Value* FundamentalTypeShl::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitShl(left, right);
}

const char32_t* FundamentalTypeShr::GroupName()
{
    return U"operator>>";
}

const char32_t* FundamentalTypeShr::AssignmentOpGroupName()
{
    return U"operator>>=";
}

otava::intermediate::Value* FundamentalTypeShr::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitShr(left, right);
}

const char32_t* FundamentalTypeEqual::GroupName()
{
    return U"operator==";
}

otava::intermediate::Value* FundamentalTypeEqual::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitEqual(left, right);
}

const char32_t* FundamentalTypeLess::GroupName()
{
    return U"operator<";
}

otava::intermediate::Value* FundamentalTypeLess::Generate(Emitter& emitter, otava::intermediate::Value* left, otava::intermediate::Value* right)
{
    return emitter.EmitLess(left, right);
}

FundamentalTypeNotOperation::FundamentalTypeNotOperation() : FundamentalTypeUnaryOperation<FundamentalTypeNot>(SymbolKind::fundamentalTypeNot)
{
}

FundamentalTypeNotOperation::FundamentalTypeNotOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeUnaryOperation<FundamentalTypeNot>(SymbolKind::fundamentalTypeNot, type_, context)
{
}

FundamentalTypeUnaryPlusOperation::FundamentalTypeUnaryPlusOperation() :
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryPlus>(SymbolKind::fundamentalTypeUnaryPlus)
{
}

FundamentalTypeUnaryPlusOperation::FundamentalTypeUnaryPlusOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryPlus>(SymbolKind::fundamentalTypeUnaryPlus, type_, context)
{
}

FundamentalTypeUnaryMinusOperation::FundamentalTypeUnaryMinusOperation() :
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryMinus>(SymbolKind::fundamentalTypeUnaryMinus)
{
}

FundamentalTypeUnaryMinusOperation::FundamentalTypeUnaryMinusOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeUnaryOperation<FundamentalTypeUnaryMinus>(SymbolKind::fundamentalTypeUnaryMinus, type_, context)
{
}

FundamentalTypeComplementOperation::FundamentalTypeComplementOperation() :
    FundamentalTypeUnaryOperation<FundamentalTypeComplement>(SymbolKind::fundamentalTypeComplement)
{
}

FundamentalTypeComplementOperation::FundamentalTypeComplementOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeUnaryOperation<FundamentalTypeComplement>(SymbolKind::fundamentalTypeComplement, type_, context)
{
}

FundamentalTypeAddOperation::FundamentalTypeAddOperation() : FundamentalTypeBinaryOperation<FundamentalTypeAdd>(SymbolKind::fundamentalTypeAdd)
{
}

FundamentalTypeAddOperation::FundamentalTypeAddOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeBinaryOperation<FundamentalTypeAdd>(SymbolKind::fundamentalTypeAdd, type_, context)
{
}

FundamentalTypeSubOperation::FundamentalTypeSubOperation() : FundamentalTypeBinaryOperation<FundamentalTypeSub>(SymbolKind::fundamentalTypeSub)
{
}

FundamentalTypeSubOperation::FundamentalTypeSubOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeBinaryOperation<FundamentalTypeSub>(SymbolKind::fundamentalTypeSub, type_, context)
{
}

FundamentalTypeMulOperation::FundamentalTypeMulOperation() : FundamentalTypeBinaryOperation<FundamentalTypeMul>(SymbolKind::fundamentalTypeMul)
{
}

FundamentalTypeMulOperation::FundamentalTypeMulOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeBinaryOperation<FundamentalTypeMul>(SymbolKind::fundamentalTypeMul, type_, context)
{
}

FundamentalTypeDivOperation::FundamentalTypeDivOperation() : FundamentalTypeBinaryOperation<FundamentalTypeDiv>(SymbolKind::fundamentalTypeDiv)
{
}

FundamentalTypeDivOperation::FundamentalTypeDivOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeBinaryOperation<FundamentalTypeDiv>(SymbolKind::fundamentalTypeDiv, type_, context)
{
}

FundamentalTypeModOperation::FundamentalTypeModOperation() : FundamentalTypeBinaryOperation<FundamentalTypeMod>(SymbolKind::fundamentalTypeMod)
{
}

FundamentalTypeModOperation::FundamentalTypeModOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeBinaryOperation<FundamentalTypeMod>(SymbolKind::fundamentalTypeMod, type_, context)
{
}

FundamentalTypeAndOperation::FundamentalTypeAndOperation() : FundamentalTypeBinaryOperation<FundamentalTypeAnd>(SymbolKind::fundamentalTypeAnd)
{
}

FundamentalTypeAndOperation::FundamentalTypeAndOperation(TypeSymbol* type_, Context* context)
    : FundamentalTypeBinaryOperation<FundamentalTypeAnd>(SymbolKind::fundamentalTypeAnd, type_, context)
{
}

FundamentalTypeOrOperation::FundamentalTypeOrOperation() : FundamentalTypeBinaryOperation<FundamentalTypeOr>(SymbolKind::fundamentalTypeOr)
{
}

FundamentalTypeOrOperation::FundamentalTypeOrOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeBinaryOperation<FundamentalTypeOr>(SymbolKind::fundamentalTypeOr, type_, context)
{
}

FundamentalTypeXorOperation::FundamentalTypeXorOperation() : FundamentalTypeBinaryOperation<FundamentalTypeXor>(SymbolKind::fundamentalTypeXor)
{
}

FundamentalTypeXorOperation::FundamentalTypeXorOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeBinaryOperation<FundamentalTypeXor>(SymbolKind::fundamentalTypeXor, type_, context)
{
}

FundamentalTypeShlOperation::FundamentalTypeShlOperation() : FundamentalTypeBinaryOperation<FundamentalTypeShl>(SymbolKind::fundamentalTypeShl)
{
}

FundamentalTypeShlOperation::FundamentalTypeShlOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeBinaryOperation<FundamentalTypeShl>(SymbolKind::fundamentalTypeShl, type_, context)
{
}

FundamentalTypeShrOperation::FundamentalTypeShrOperation() : FundamentalTypeBinaryOperation<FundamentalTypeShr>(SymbolKind::fundamentalTypeShr)
{
}

FundamentalTypeShrOperation::FundamentalTypeShrOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeBinaryOperation<FundamentalTypeShr>(SymbolKind::fundamentalTypeShr, type_, context)
{
}

FundamentalTypePlusAssignOperation::FundamentalTypePlusAssignOperation() : FundamentalTypeAssignmentOperation<FundamentalTypeAdd>(SymbolKind::fundamentalTypePlusAssign)
{
}

FundamentalTypePlusAssignOperation::FundamentalTypePlusAssignOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeAssignmentOperation<FundamentalTypeAdd>(SymbolKind::fundamentalTypePlusAssign, type_, context)
{
}

FundamentalTypeMinusAssignOperation::FundamentalTypeMinusAssignOperation() : FundamentalTypeAssignmentOperation<FundamentalTypeSub>(SymbolKind::fundamentalTypeMinusAssign)
{
}

FundamentalTypeMinusAssignOperation::FundamentalTypeMinusAssignOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeAssignmentOperation<FundamentalTypeSub>(SymbolKind::fundamentalTypeMinusAssign, type_, context)
{
}

FundamentalTypeMulAssignOperation::FundamentalTypeMulAssignOperation() : FundamentalTypeAssignmentOperation<FundamentalTypeMul>(SymbolKind::fundamentalTypeMulAssign)
{
}

FundamentalTypeMulAssignOperation::FundamentalTypeMulAssignOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeAssignmentOperation<FundamentalTypeMul>(SymbolKind::fundamentalTypeMulAssign, type_, context)
{
}

FundamentalTypeDivAssignOperation::FundamentalTypeDivAssignOperation() : FundamentalTypeAssignmentOperation<FundamentalTypeDiv>(SymbolKind::fundamentalTypeDivAssign)
{
}

FundamentalTypeDivAssignOperation::FundamentalTypeDivAssignOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeAssignmentOperation<FundamentalTypeDiv>(SymbolKind::fundamentalTypeDivAssign, type_, context)
{
}

FundamentalTypeModAssignOperation::FundamentalTypeModAssignOperation() : FundamentalTypeAssignmentOperation<FundamentalTypeMod>(SymbolKind::fundamentalTypeModAssign)
{
}

FundamentalTypeModAssignOperation::FundamentalTypeModAssignOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeAssignmentOperation<FundamentalTypeMod>(SymbolKind::fundamentalTypeModAssign, type_, context)
{
}

FundamentalTypeAndAssignOperation::FundamentalTypeAndAssignOperation() : FundamentalTypeAssignmentOperation<FundamentalTypeAnd>(SymbolKind::fundamentalTypeAndAssign)
{
}

FundamentalTypeAndAssignOperation::FundamentalTypeAndAssignOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeAssignmentOperation<FundamentalTypeAnd>(SymbolKind::fundamentalTypeAndAssign, type_, context)
{
}

FundamentalTypeOrAssignOperation::FundamentalTypeOrAssignOperation() : FundamentalTypeAssignmentOperation<FundamentalTypeOr>(SymbolKind::fundamentalTypeOrAssign)
{
}

FundamentalTypeOrAssignOperation::FundamentalTypeOrAssignOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeAssignmentOperation<FundamentalTypeOr>(SymbolKind::fundamentalTypeOrAssign, type_, context)
{
}

FundamentalTypeXorAssignOperation::FundamentalTypeXorAssignOperation() : FundamentalTypeAssignmentOperation<FundamentalTypeXor>(SymbolKind::fundamentalTypeXorAssign)
{
}

FundamentalTypeXorAssignOperation::FundamentalTypeXorAssignOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeAssignmentOperation<FundamentalTypeXor>(SymbolKind::fundamentalTypeXorAssign, type_, context)
{
}

FundamentalTypeShlAssignOperation::FundamentalTypeShlAssignOperation() : FundamentalTypeAssignmentOperation<FundamentalTypeShl>(SymbolKind::fundamentalTypeShlAssign)
{
}

FundamentalTypeShlAssignOperation::FundamentalTypeShlAssignOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeAssignmentOperation<FundamentalTypeShl>(SymbolKind::fundamentalTypeShlAssign, type_, context)
{
}

FundamentalTypeShrAssignOperation::FundamentalTypeShrAssignOperation() : FundamentalTypeAssignmentOperation<FundamentalTypeShr>(SymbolKind::fundamentalTypeShrAssign)
{
}

FundamentalTypeShrAssignOperation::FundamentalTypeShrAssignOperation(TypeSymbol* type_, Context* context) :
    FundamentalTypeAssignmentOperation<FundamentalTypeShr>(SymbolKind::fundamentalTypeShrAssign, type_, context)
{
}

FundamentalTypeEqualOperation::FundamentalTypeEqualOperation() : FundamentalTypeComparisonOperation<FundamentalTypeEqual>(SymbolKind::fundamentalTypeEqual)
{
}

FundamentalTypeEqualOperation::FundamentalTypeEqualOperation(TypeSymbol* type_, TypeSymbol* boolType_, Context* context) :
    FundamentalTypeComparisonOperation<FundamentalTypeEqual>(SymbolKind::fundamentalTypeEqual, type_, boolType_, context)
{
}

FundamentalTypeLessOperation::FundamentalTypeLessOperation() : FundamentalTypeComparisonOperation<FundamentalTypeLess>(SymbolKind::fundamentalTypeLess)
{
}

FundamentalTypeLessOperation::FundamentalTypeLessOperation(TypeSymbol* type_, TypeSymbol* boolType_, Context* context) :
    FundamentalTypeComparisonOperation<FundamentalTypeLess>(SymbolKind::fundamentalTypeLess, type_, boolType_, context)
{
}

FundamentalTypeDefaultCtor::FundamentalTypeDefaultCtor() : FunctionSymbol(SymbolKind::fundamentalTypeDefaultCtor, U"@constructor"), type(nullptr)
{
}

FundamentalTypeDefaultCtor::FundamentalTypeDefaultCtor(TypeSymbol* type_, Context* context) :
    FunctionSymbol(SymbolKind::fundamentalTypeDefaultCtor, U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> FundamentalTypeDefaultCtor::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(type->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeDefaultCtor::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(typeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeDefaultCtor::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    type = symbolTable.GetType(typeId);
    if (!type)
    {
        std::expected<std::u32string, int> fname = FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        std::cout << "FundamentalTypeDefaultCtor::Resolve(): warning: type of '" + *sfname + "' not resolved" << "\n";
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeDefaultCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    if ((flags & OperationFlags::defaultInit) != OperationFlags::none)
    {
        std::expected<otava::intermediate::Type*, int> irv = type->IrType(emitter, sourcePos, context);
        if (!irv) return std::unexpected<int>(irv.error());
        otava::intermediate::Type* irType = *irv;
        emitter.Stack().Push(irType->DefaultValue());
        OperationFlags storeFlags = OperationFlags::none;
        if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
        {
            storeFlags = storeFlags | OperationFlags::deref;
        }
        std::expected<bool, int> rv = args[0]->Store(emitter, storeFlags, sourcePos, context);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

FundamentalTypeCopyCtor::FundamentalTypeCopyCtor() : FunctionSymbol(SymbolKind::fundamentalTypeCopyCtor, U"@constructor"), type(nullptr)
{
}

FundamentalTypeCopyCtor::FundamentalTypeCopyCtor(TypeSymbol* type_, Context* context) :
    FunctionSymbol(SymbolKind::fundamentalTypeCopyCtor, U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    rv = AddParameter(thatParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> FundamentalTypeCopyCtor::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(type->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeCopyCtor::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(typeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeCopyCtor::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    type = symbolTable.GetType(typeId);
    if (!type)
    {
        std::expected<std::u32string, int> fname = FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        std::cout << "FundamentalTypeCopyCtor::Resolve(): warning: type of '" + *sfname + "' not resolved" << "\n";
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeCopyCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    OperationFlags storeFlags = OperationFlags::none;
    if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
    {
        storeFlags = storeFlags | OperationFlags::deref;
    }
    rv = args[0]->Store(emitter, storeFlags, sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

FundamentalTypeMoveCtor::FundamentalTypeMoveCtor() : FunctionSymbol(SymbolKind::fundamentalTypeMoveCtor, U"@constructor"), type(nullptr)
{
}

FundamentalTypeMoveCtor::FundamentalTypeMoveCtor(TypeSymbol* type_, Context* context) :
    FunctionSymbol(SymbolKind::fundamentalTypeMoveCtor, U"@constructor"), type(type_)
{
    SetFunctionKind(FunctionKind::constructor);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = type->AddRValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* rvalueRefType = *pt;
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", rvalueRefType);
    rv = AddParameter(thatParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> FundamentalTypeMoveCtor::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(type->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeMoveCtor::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(typeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeMoveCtor::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    type = symbolTable.GetType(typeId);
    if (!type)
    {
        std::expected<std::u32string, int> fname = FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        std::cout << "FundamentalTypeMoveCtor::Resolve(): warning: type of '" + *sfname + "' not resolved" << "\n";
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeMoveCtor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* rvalueRefValue = emitter.Stack().Pop();
    std::expected<otava::intermediate::Instruction*, int> lrv = emitter.EmitLoad(rvalueRefValue);
    if (!lrv) return std::unexpected<int>(lrv.error());
    otava::intermediate::Instruction* inst = *lrv;
    emitter.Stack().Push(inst);
    OperationFlags storeFlags = OperationFlags::none;
    if ((flags & OperationFlags::storeDeref) != OperationFlags::none)
    {
        storeFlags = storeFlags | OperationFlags::deref;
    }
    rv = args[0]->Store(emitter, storeFlags, sourcePos, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

FundamentalTypeCopyAssignment::FundamentalTypeCopyAssignment() : FunctionSymbol(SymbolKind::fundamentalTypeCopyAssignment, U"operator="), type(nullptr)
{
}

FundamentalTypeCopyAssignment::FundamentalTypeCopyAssignment(TypeSymbol* type_, Context* context)
    : FunctionSymbol(SymbolKind::fundamentalTypeCopyAssignment, U"operator="), type(type_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", type);
    rv = AddParameter(thatParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = type->AddLValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* lvalueRefType = *pt;
    rv = SetReturnType(lvalueRefType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> FundamentalTypeCopyAssignment::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(type->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeCopyAssignment::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(typeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeCopyAssignment::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    type = symbolTable.GetType(typeId);
    if (!type)
    {
        std::expected<std::u32string, int> fname = FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        std::cout << "FundamentalTypeCopyAssignment::Resolve(): warning: type of '" + *sfname + "' not resolved" << "\n";
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeCopyAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    rv = args[0]->Store(emitter, OperationFlags::setPtr, sourcePos, context);
    if (!rv) return rv;
    emitter.Stack().Push(context->Ptr());
    return std::expected<bool, int>(true);
}

FundamentalTypeMoveAssignment::FundamentalTypeMoveAssignment() : FunctionSymbol(SymbolKind::fundamentalTypeMoveAssignment, U"operator="), type(nullptr)
{
}

FundamentalTypeMoveAssignment::FundamentalTypeMoveAssignment(TypeSymbol* type_, Context* context) :
    FunctionSymbol(SymbolKind::fundamentalTypeMoveAssignment, U"operator="), type(type_)
{
    SetFunctionKind(FunctionKind::special);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = type->AddRValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* rvalueRefType = *pt;
    ParameterSymbol* thatParam = new ParameterSymbol(U"that", rvalueRefType);
    rv = AddParameter(thatParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    pt = type->AddLValueRef(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* lvalueRefType = *pt;
    rv = SetReturnType(lvalueRefType, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
}

std::expected<bool, int> FundamentalTypeMoveAssignment::Write(Writer& writer)
{
    std::expected<bool, int> rv = FunctionSymbol::Write(writer);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(type->Id());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeMoveAssignment::Read(Reader& reader)
{
    std::expected<bool, int> rv = FunctionSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(typeId);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeMoveAssignment::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = FunctionSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    type = symbolTable.GetType(typeId);
    if (!type)
    {
        std::expected<std::u32string, int> fname = FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        std::cout << "FundamentalTypeMoveAssignment::Resolve(): warning: type of '" + *sfname + "' not resolved" << "\n";
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FundamentalTypeMoveAssignment::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    std::expected<bool, int> rv = args[1]->Load(emitter, OperationFlags::none, sourcePos, context);
    if (!rv) return rv;
    otava::intermediate::Value* refValue = emitter.Stack().Pop();
    std::expected<otava::intermediate::Instruction*, int> lrv = emitter.EmitLoad(refValue);
    if (!lrv) return std::unexpected<int>(lrv.error());
    otava::intermediate::Instruction* inst = *lrv;
    emitter.Stack().Push(inst);
    rv = args[0]->Store(emitter, OperationFlags::setPtr, sourcePos, context);
    if (!rv) return rv;
    emitter.Stack().Push(context->Ptr());
    return std::expected<bool, int>(true);
}

TrivialDestructor::TrivialDestructor() : FunctionSymbol(U"@destructor"), type(nullptr)
{
}

TrivialDestructor::TrivialDestructor(TypeSymbol* type_, Context* context) : FunctionSymbol(U"@destructor"), type(type_)
{
    SetFunctionKind(FunctionKind::destructor);
    SetAccess(Access::public_);
    std::expected<TypeSymbol*, int> pt = type->AddPointer(context);
    if (!pt)
    {
        SetError(pt.error());
        return;
    }
    TypeSymbol* ptrType = *pt;
    ParameterSymbol* thisParam = new ParameterSymbol(U"this", ptrType);
    std::expected<bool, int> rv = AddParameter(thisParam, soul::ast::SourcePos(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    SetFlag(FunctionSymbolFlags::trivialDestructor);
}

std::expected<bool, int> TrivialDestructor::GenerateCode(Emitter& emitter, std::vector<BoundExpressionNode*>& args, OperationFlags flags,
    const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AddFundamentalIntegerOperationsToSymbolTable(TypeSymbol* type, Context* context)
{
    std::expected<TypeSymbol*, int> trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* boolType = *trv;

    std::expected<bool, int> rv = context->GetSymbolTable()->AddFunctionSymbol(
        context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeUnaryPlusOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeUnaryPlusOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeUnaryMinusOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeComplementOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeAddOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSubOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMulOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDivOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeModOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeAndOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeOrOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeXorOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeShlOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeShrOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypePlusAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMinusAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMulAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDivAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeModAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeAndAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeOrAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeXorAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeShlAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeShrAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeEqualOperation(type, boolType, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeLessOperation(type, boolType, context), context);
    if (!rv) return rv;

    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDefaultCtor(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyCtor(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveCtor(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyAssignment(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveAssignment(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new TrivialDestructor(type, context), context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AddFundamentalFloatingPointOperationsToSymbolTable(TypeSymbol* type, Context* context)
{
    std::expected<TypeSymbol*, int> trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* boolType = *trv;

    std::expected<bool, int> rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeUnaryPlusOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeUnaryMinusOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeAddOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSubOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMulOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDivOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypePlusAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMinusAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMulAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDivAssignOperation(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeEqualOperation(type, boolType, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeLessOperation(type, boolType, context), context);
    if (!rv) return rv;

    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDefaultCtor(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyCtor(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveCtor(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyAssignment(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveAssignment(type, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new TrivialDestructor(type, context), context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AddFundamentalTypeOperationsToSymbolTable(Context* context)
{
    std::expected<TypeSymbol*, int> trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* boolType = *trv;

    std::expected<bool, int> rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeDefaultCtor(boolType, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyCtor(boolType, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveCtor(boolType, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeCopyAssignment(boolType, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeMoveAssignment(boolType, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeEqualOperation(boolType, boolType, context), context);
    if (!rv) return rv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new TrivialDestructor(boolType, context), context);
    if (!rv) return rv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::charType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* charType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::signedCharType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* signedCharType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedCharType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* unsignedCharType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char8Type);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* char8Type = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char16Type);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* char16Type = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::char32Type);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* char32Type = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::wcharType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* wcharType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::shortIntType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* shortIntType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedShortIntType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* unsignedShortIntType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::intType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* intType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedIntType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* unsignedIntType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longIntType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* longIntType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedLongIntType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* unsignedLongIntType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longLongIntType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* longLongIntType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::unsignedLongLongIntType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* unsignedLongLongIntType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::floatType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* floatType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::doubleType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* doubleType = *trv;
    trv = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::longDoubleType);
    if (!trv) return std::unexpected<int>(trv.error());
    TypeSymbol* longDoubleType = *trv;
    rv = context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeNotOperation(boolType, context), context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(charType, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(signedCharType, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(unsignedCharType, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(char8Type, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(char16Type, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(char32Type, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(wcharType, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(shortIntType, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(unsignedShortIntType, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(intType, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(unsignedIntType, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(longIntType, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(unsignedLongIntType, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(longLongIntType, context);
    if (!rv) return rv;
    rv = AddFundamentalIntegerOperationsToSymbolTable(unsignedLongLongIntType, context);
    if (!rv) return rv;
    rv = AddFundamentalFloatingPointOperationsToSymbolTable(floatType, context);
    if (!rv) return rv;
    rv = AddFundamentalFloatingPointOperationsToSymbolTable(doubleType, context);
    if (!rv) return rv;
    rv = AddFundamentalTypeConversionsToSymboTable(charType, signedCharType, unsignedCharType, char8Type, char16Type, char32Type, wcharType,
        shortIntType, unsignedShortIntType, intType, unsignedIntType, longIntType, unsignedLongIntType, longLongIntType, unsignedLongLongIntType,
        floatType, doubleType, context);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols