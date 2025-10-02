// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.fundamental.type.conversion.init;

import otava.symbols.context;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.symbol.table;
import otava.symbols.namespaces;
import otava.symbols.fundamental.type.conversion;

namespace otava::symbols {

void AddFundamentalTypeConversionsToSymboTable( 
    TypeSymbol* charType, TypeSymbol* signedCharType, TypeSymbol* unsignedCharType, TypeSymbol* char8Type, TypeSymbol* char16Type, TypeSymbol* char32Type, TypeSymbol* wcharType,
    TypeSymbol* shortIntType, TypeSymbol* unsignedShortIntType, TypeSymbol* intType, TypeSymbol* unsignedIntType, TypeSymbol* longIntType, TypeSymbol* unsignedLongIntType,
    TypeSymbol* longLongIntType, TypeSymbol* unsignedLongLongIntType, TypeSymbol* floatType, TypeSymbol* doubleType, Context* context)
{
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalType(FundamentalTypeKind::boolType);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(signedCharType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(unsignedCharType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(char8Type, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(char16Type, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(char32Type, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(wcharType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(shortIntType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(unsignedShortIntType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(intType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(unsignedIntType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(longIntType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(unsignedLongIntType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(longLongIntType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(unsignedLongLongIntType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(floatType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(doubleType, boolType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBoolToIntConversion(boolType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBoolToIntConversion(boolType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBoolToIntConversion(boolType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBoolToIntConversion(boolType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBoolToIntConversion(boolType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBoolToIntConversion(boolType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBoolToIntConversion(boolType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBoolToIntConversion(boolType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBoolToIntConversion(boolType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBoolToIntConversion(boolType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBoolToIntConversion(boolType, unsignedLongLongIntType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(10, ConversionKind::explicitConversion, charType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, charType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, charType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, charType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, charType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, charType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, charType, wcharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, charType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, charType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, charType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, charType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, charType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, charType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, charType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, charType, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, charType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, charType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(10, ConversionKind::explicitConversion, signedCharType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, signedCharType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, signedCharType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, signedCharType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, signedCharType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, signedCharType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, signedCharType, wcharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, signedCharType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, signedCharType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, signedCharType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, signedCharType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, signedCharType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, signedCharType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, signedCharType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, signedCharType, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, signedCharType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, signedCharType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(10, ConversionKind::explicitConversion, unsignedCharType, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedCharType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedCharType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedCharType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, unsignedCharType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedCharType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, unsignedCharType, wcharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, unsignedCharType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, unsignedCharType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedCharType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedCharType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedCharType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedCharType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, unsignedCharType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, unsignedCharType, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, unsignedCharType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, unsignedCharType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(10, ConversionKind::explicitConversion, char8Type, boolType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char8Type, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char8Type, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char8Type, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, char8Type, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, char8Type, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, char8Type, wcharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, char8Type, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, char8Type, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, char8Type, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, char8Type, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, char8Type, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, char8Type, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, char8Type, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, char8Type, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, char8Type, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, char8Type, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char16Type, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char16Type, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char16Type, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char16Type, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, char16Type, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, char16Type, wcharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::explicitConversion, char16Type, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::explicitConversion, char16Type, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, char16Type, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, char16Type, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, char16Type, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, char16Type, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, char16Type, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, char16Type, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, char16Type, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, char16Type, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, char32Type, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, char32Type, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, char32Type, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, char32Type, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char32Type, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char32Type, wcharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char32Type, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char32Type, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char32Type, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char32Type, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char32Type, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char32Type, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, char32Type, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, char32Type, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, char32Type, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, char32Type, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, wcharType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, wcharType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, wcharType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, wcharType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, wcharType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, wcharType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, wcharType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, wcharType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, wcharType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, wcharType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, wcharType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, wcharType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, wcharType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, wcharType, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, wcharType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, wcharType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(3, ConversionKind::implicitConversion, shortIntType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(3, ConversionKind::implicitConversion, shortIntType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, shortIntType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, shortIntType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, shortIntType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, shortIntType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, shortIntType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, shortIntType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, shortIntType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, shortIntType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, shortIntType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, shortIntType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, shortIntType, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, shortIntType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, shortIntType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedShortIntType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedShortIntType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedShortIntType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedShortIntType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedShortIntType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::explicitConversion, unsignedShortIntType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedShortIntType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedShortIntType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedShortIntType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedShortIntType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedShortIntType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, unsignedShortIntType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::explicitConversion, unsignedShortIntType, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, unsignedShortIntType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, unsignedShortIntType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, intType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(5, ConversionKind::implicitConversion, intType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, intType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, intType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, intType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, intType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(4, ConversionKind::implicitConversion, intType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, intType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, intType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, intType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, intType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, intType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, intType, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, intType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, intType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedIntType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedIntType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedIntType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedIntType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedIntType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedIntType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedIntType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedIntType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedIntType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedIntType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedIntType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedIntType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedIntType, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, unsignedIntType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, unsignedIntType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longIntType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(5, ConversionKind::implicitConversion, longIntType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longIntType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longIntType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, longIntType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, longIntType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(4, ConversionKind::implicitConversion, longIntType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, longIntType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, longIntType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, longIntType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, longIntType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, longIntType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, longIntType, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, longIntType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, longIntType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongIntType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedLongIntType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongIntType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongIntType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedLongIntType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedLongIntType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedLongIntType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedLongIntType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::explicitConversion, unsignedLongIntType, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, unsignedLongIntType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, unsignedLongIntType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longLongIntType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(5, ConversionKind::implicitConversion, longLongIntType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longLongIntType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longLongIntType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, longLongIntType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, longLongIntType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(4, ConversionKind::implicitConversion, longLongIntType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, longLongIntType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(3, ConversionKind::implicitConversion, longLongIntType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, longLongIntType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(3, ConversionKind::implicitConversion, longLongIntType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, longLongIntType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, longLongIntType, unsignedLongLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, longLongIntType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, longLongIntType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongLongIntType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongLongIntType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongLongIntType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongLongIntType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongLongIntType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedLongLongIntType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongLongIntType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongLongIntType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedLongLongIntType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedLongLongIntType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedLongLongIntType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedLongLongIntType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedLongLongIntType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::explicitConversion, unsignedLongLongIntType, floatType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::explicitConversion, unsignedLongLongIntType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, floatType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, floatType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, floatType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, floatType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, floatType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, floatType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, floatType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, floatType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, floatType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, floatType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, floatType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, floatType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(2, ConversionKind::implicitConversion, floatType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(2, ConversionKind::implicitConversion, floatType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(1, ConversionKind::explicitConversion, floatType, doubleType, context), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, doubleType, charType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, doubleType, signedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, doubleType, unsignedCharType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, doubleType, char8Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, doubleType, char16Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, doubleType, char32Type, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, doubleType, shortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, doubleType, unsignedShortIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, doubleType, intType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, doubleType, unsignedIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, doubleType, longIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, doubleType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(2, ConversionKind::implicitConversion, doubleType, longLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(2, ConversionKind::implicitConversion, doubleType, unsignedLongIntType, context), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatingPointExtendConversion(1, ConversionKind::implicitConversion, doubleType, floatType, context), context);
}

} // namespace otava::symbols
