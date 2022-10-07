// =================================
// Copyright (c) 2022 Seppo Laakko
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

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, boolType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, wcharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBooleanConversion(charType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, charType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, charType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, charType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, charType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, charType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, charType, wcharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, charType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, charType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, charType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, charType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, charType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, charType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, charType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, charType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, charType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, charType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, signedCharType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, signedCharType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, signedCharType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, signedCharType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, signedCharType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, signedCharType, wcharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, signedCharType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, signedCharType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, signedCharType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, signedCharType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, signedCharType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, signedCharType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, signedCharType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, signedCharType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, signedCharType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, signedCharType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedCharType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedCharType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedCharType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, unsignedCharType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedCharType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, unsignedCharType, wcharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, unsignedCharType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, unsignedCharType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedCharType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedCharType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedCharType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedCharType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, unsignedCharType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, unsignedCharType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, unsignedCharType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, unsignedCharType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char8Type, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char8Type, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char8Type, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, char8Type, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, char8Type, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, char8Type, wcharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, char8Type, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, char8Type, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, char8Type, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, char8Type, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, char8Type, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, char8Type, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, char8Type, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, char8Type, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, char8Type, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, char8Type, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char16Type, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char16Type, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char16Type, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char16Type, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, char16Type, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, char16Type, wcharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::narrowingConversion, char16Type, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::narrowingConversion, char16Type, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, char16Type, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, char16Type, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, char16Type, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, char16Type, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, char16Type, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, char16Type, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, char16Type, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, char16Type, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, char32Type, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, char32Type, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, char32Type, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, char32Type, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char32Type, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char32Type, wcharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char32Type, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, char32Type, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char32Type, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char32Type, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char32Type, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, char32Type, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, char32Type, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, char32Type, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, char32Type, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, char32Type, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, wcharType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, wcharType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, wcharType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, wcharType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, wcharType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, wcharType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, wcharType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(2, ConversionKind::implicitConversion, wcharType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, wcharType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, wcharType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, wcharType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, wcharType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, wcharType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, wcharType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, wcharType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, wcharType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(3, ConversionKind::implicitConversion, shortIntType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(3, ConversionKind::implicitConversion, shortIntType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, shortIntType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, shortIntType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, shortIntType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, shortIntType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, shortIntType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, shortIntType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, shortIntType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, shortIntType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, shortIntType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, shortIntType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, shortIntType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, shortIntType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, shortIntType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedShortIntType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedShortIntType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedShortIntType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedShortIntType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedShortIntType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(2, ConversionKind::narrowingConversion, unsignedShortIntType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedShortIntType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedShortIntType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedShortIntType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedShortIntType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedShortIntType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, unsignedShortIntType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(4, ConversionKind::narrowingConversion, unsignedShortIntType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, unsignedShortIntType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, unsignedShortIntType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, intType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(5, ConversionKind::implicitConversion, intType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, intType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, intType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, intType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, intType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(4, ConversionKind::implicitConversion, intType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, intType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, intType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, intType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, intType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, intType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, intType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, intType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, intType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedIntType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedIntType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedIntType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedIntType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedIntType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedIntType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedIntType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedIntType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedIntType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedIntType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedIntType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedIntType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedIntType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, unsignedIntType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, unsignedIntType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longIntType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(5, ConversionKind::implicitConversion, longIntType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longIntType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longIntType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, longIntType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, longIntType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(4, ConversionKind::implicitConversion, longIntType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, longIntType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, longIntType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, longIntType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, longIntType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, longIntType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, longIntType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, longIntType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, longIntType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongIntType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedLongIntType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongIntType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongIntType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedLongIntType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedLongIntType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedLongIntType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedLongIntType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(3, ConversionKind::narrowingConversion, unsignedLongIntType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, unsignedLongIntType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, unsignedLongIntType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longLongIntType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(5, ConversionKind::implicitConversion, longLongIntType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longLongIntType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, longLongIntType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, longLongIntType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, longLongIntType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(4, ConversionKind::implicitConversion, longLongIntType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, longLongIntType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(3, ConversionKind::implicitConversion, longLongIntType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, longLongIntType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(3, ConversionKind::implicitConversion, longLongIntType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, longLongIntType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, longLongIntType, unsignedLongLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, longLongIntType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, longLongIntType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(5, ConversionKind::implicitConversion, unsignedLongIntType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongIntType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedLongIntType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongIntType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(4, ConversionKind::implicitConversion, unsignedLongIntType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedLongIntType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedLongIntType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedLongIntType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeZeroExtendConversion(3, ConversionKind::implicitConversion, unsignedLongIntType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeBitcastConversion(1, ConversionKind::implicitConversion, unsignedLongIntType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(5, ConversionKind::narrowingConversion, unsignedLongIntType, floatType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeFloatToIntConversion(6, ConversionKind::narrowingConversion, unsignedLongIntType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, floatType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, floatType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, floatType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, floatType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, floatType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, floatType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, floatType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, floatType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, floatType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, floatType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, floatType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, floatType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(2, ConversionKind::implicitConversion, floatType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(2, ConversionKind::implicitConversion, floatType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeTruncateConversion(1, ConversionKind::narrowingConversion, floatType, doubleType), context);

    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, doubleType, charType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, doubleType, signedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, doubleType, unsignedCharType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(5, ConversionKind::implicitConversion, doubleType, char8Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, doubleType, char16Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, doubleType, char32Type), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, doubleType, shortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(4, ConversionKind::implicitConversion, doubleType, unsignedShortIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, doubleType, intType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, doubleType, unsignedIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, doubleType, longIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(3, ConversionKind::implicitConversion, doubleType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(2, ConversionKind::implicitConversion, doubleType, longLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeIntToFloatConversion(2, ConversionKind::implicitConversion, doubleType, unsignedLongIntType), context);
    context->GetSymbolTable()->AddFunctionSymbol(context->GetSymbolTable()->GlobalNs()->GetScope(), new FundamentalTypeSignExtendConversion(1, ConversionKind::implicitConversion, doubleType, floatType), context);
}

} // namespace otava::symbols
