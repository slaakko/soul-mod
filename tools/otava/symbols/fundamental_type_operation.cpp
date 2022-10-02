// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.fundamental.type.operation;

import otava.symbols.fundamental.type.symbol;
import otava.symbols.symbol.table;
import otava.symbols.namespaces;

namespace otava::symbols {

FundamentalTypeAddOperation::FundamentalTypeAddOperation() : FundamentalTypeBinaryOperation<FundamentalTypeAdd>(SymbolKind::fundamentalTypeAdd)
{
}

FundamentalTypeAddOperation::FundamentalTypeAddOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeAdd>(SymbolKind::fundamentalTypeAdd, type_)
{
}

FundamentalTypeSubOperation::FundamentalTypeSubOperation() : FundamentalTypeBinaryOperation<FundamentalTypeSub>(SymbolKind::fundamentalTypeSub)
{
}

FundamentalTypeSubOperation::FundamentalTypeSubOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeSub>(SymbolKind::fundamentalTypeSub, type_)
{
}

FundamentalTypeMulOperation::FundamentalTypeMulOperation() : FundamentalTypeBinaryOperation<FundamentalTypeMul>(SymbolKind::fundamentalTypeMul)
{
}

FundamentalTypeMulOperation::FundamentalTypeMulOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeMul>(SymbolKind::fundamentalTypeMul, type_)
{
}

FundamentalTypeDivOperation::FundamentalTypeDivOperation() : FundamentalTypeBinaryOperation<FundamentalTypeDiv>(SymbolKind::fundamentalTypeDiv)
{
}

FundamentalTypeDivOperation::FundamentalTypeDivOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeDiv>(SymbolKind::fundamentalTypeDiv, type_)
{
}

FundamentalTypeModOperation::FundamentalTypeModOperation() : FundamentalTypeBinaryOperation<FundamentalTypeMod>(SymbolKind::fundamentalTypeMod)
{
}

FundamentalTypeModOperation::FundamentalTypeModOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeMod>(SymbolKind::fundamentalTypeMod, type_)
{
}

FundamentalTypeAndOperation::FundamentalTypeAndOperation() : FundamentalTypeBinaryOperation<FundamentalTypeAnd>(SymbolKind::fundamentalTypeAnd)
{
}

FundamentalTypeAndOperation::FundamentalTypeAndOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeAnd>(SymbolKind::fundamentalTypeAnd, type_)
{
}

FundamentalTypeOrOperation::FundamentalTypeOrOperation() : FundamentalTypeBinaryOperation<FundamentalTypeOr>(SymbolKind::fundamentalTypeOr)
{
}

FundamentalTypeOrOperation::FundamentalTypeOrOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeOr>(SymbolKind::fundamentalTypeOr, type_)
{
}

FundamentalTypeXorOperation::FundamentalTypeXorOperation() : FundamentalTypeBinaryOperation<FundamentalTypeXor>(SymbolKind::fundamentalTypeXor)
{
}

FundamentalTypeXorOperation::FundamentalTypeXorOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeXor>(SymbolKind::fundamentalTypeXor, type_)
{
}

FundamentalTypeShlOperation::FundamentalTypeShlOperation() : FundamentalTypeBinaryOperation<FundamentalTypeShl>(SymbolKind::fundamentalTypeShl)
{
}

FundamentalTypeShlOperation::FundamentalTypeShlOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeShl>(SymbolKind::fundamentalTypeShl, type_)
{
}

FundamentalTypeShrOperation::FundamentalTypeShrOperation() : FundamentalTypeBinaryOperation<FundamentalTypeShr>(SymbolKind::fundamentalTypeShr)
{
}

FundamentalTypeShrOperation::FundamentalTypeShrOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeShr>(SymbolKind::fundamentalTypeShr, type_)
{
}

FundamentalTypeEqualOperation::FundamentalTypeEqualOperation() : FundamentalTypeBinaryOperation<FundamentalTypeEqual>(SymbolKind::fundamentalTypeEqual)
{
}

FundamentalTypeEqualOperation::FundamentalTypeEqualOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeEqual>(SymbolKind::fundamentalTypeEqual, type_)
{
}

FundamentalTypeLessOperation::FundamentalTypeLessOperation() : FundamentalTypeBinaryOperation<FundamentalTypeLess>(SymbolKind::fundamentalTypeLess)
{
}

FundamentalTypeLessOperation::FundamentalTypeLessOperation(TypeSymbol* type_) : FundamentalTypeBinaryOperation<FundamentalTypeLess>(SymbolKind::fundamentalTypeLess, type_)
{
}

void AddFundamentalIntegerOperationsToSymbolTable(SymbolTable& symbolTable, TypeSymbol* type)
{
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeAddOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeSubOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeMulOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeDivOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeModOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeAndOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeOrOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeXorOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeShlOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeShrOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeEqualOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeLessOperation(type), soul::ast::SourcePos(), nullptr);
}

void AddFundamentalFloatingPointOperationsToSymbolTable(SymbolTable& symbolTable, TypeSymbol* type)
{
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeAddOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeSubOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeMulOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeDivOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeEqualOperation(type), soul::ast::SourcePos(), nullptr);
    symbolTable.GlobalNs()->AddSymbol(new FundamentalTypeLessOperation(type), soul::ast::SourcePos(), nullptr);
}

void AddFundamentalTypeOperationsToSymbolTable(SymbolTable& symbolTable)
{
    TypeSymbol* boolType = symbolTable.GetFundamentalType(FundamentalTypeKind::boolType);
    TypeSymbol* charType = symbolTable.GetFundamentalType(FundamentalTypeKind::charType);
    TypeSymbol* signedCharType = symbolTable.GetFundamentalType(FundamentalTypeKind::signedCharType);
    TypeSymbol* unsignedCharType = symbolTable.GetFundamentalType(FundamentalTypeKind::unsignedCharType);
    TypeSymbol* char8Type = symbolTable.GetFundamentalType(FundamentalTypeKind::char8Type);
    TypeSymbol* char16Type = symbolTable.GetFundamentalType(FundamentalTypeKind::char16Type);
    TypeSymbol* char32Type = symbolTable.GetFundamentalType(FundamentalTypeKind::char32Type);
    TypeSymbol* wcharType = symbolTable.GetFundamentalType(FundamentalTypeKind::wcharType);
    TypeSymbol* shortIntType = symbolTable.GetFundamentalType(FundamentalTypeKind::shortIntType);
    TypeSymbol* unsignedShortIntType = symbolTable.GetFundamentalType(FundamentalTypeKind::unsignedShortIntType);
    TypeSymbol* intType = symbolTable.GetFundamentalType(FundamentalTypeKind::intType);
    TypeSymbol* unsignedIntType = symbolTable.GetFundamentalType(FundamentalTypeKind::unsignedIntType);
    TypeSymbol* longIntType = symbolTable.GetFundamentalType(FundamentalTypeKind::longIntType);
    TypeSymbol* unsignedLongIntType = symbolTable.GetFundamentalType(FundamentalTypeKind::unsignedLongIntType);
    TypeSymbol* longLongIntType = symbolTable.GetFundamentalType(FundamentalTypeKind::longLongIntType);
    TypeSymbol* unsignedLongLongIntType = symbolTable.GetFundamentalType(FundamentalTypeKind::unsignedLongLongIntType);
    TypeSymbol* floatType = symbolTable.GetFundamentalType(FundamentalTypeKind::floatType);
    TypeSymbol* doubleType = symbolTable.GetFundamentalType(FundamentalTypeKind::doubleType);
    TypeSymbol* longDoubleType = symbolTable.GetFundamentalType(FundamentalTypeKind::longDoubleType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, charType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, signedCharType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, unsignedCharType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, char8Type);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, char16Type);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, char32Type);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, wcharType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, shortIntType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, unsignedShortIntType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, intType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, unsignedIntType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, longIntType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, unsignedLongIntType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, longLongIntType);
    AddFundamentalIntegerOperationsToSymbolTable(symbolTable, unsignedLongLongIntType);
    AddFundamentalFloatingPointOperationsToSymbolTable(symbolTable, floatType);
    AddFundamentalFloatingPointOperationsToSymbolTable(symbolTable, doubleType);
}

} // namespace otava::symbols
