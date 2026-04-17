
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/compiler/intermediate/intermediate.parser' using soul parser generator ospg version 5.0.0

export module otava.intermediate.parser;

import std;
import soul.lexer;
import soul.parser;
import otava.intermediate.context;
import otava.intermediate.types;
import otava.intermediate.code;
import otava.intermediate.metadata;

export namespace otava::intermediate::parser {

template<typename LexerT>
struct IntermediateParser
{
    static void Parse(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match IntermediateFile(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match TypeDeclarations(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match TypeDeclaration(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match TypeId(LexerT& lexer);
    static soul::parser::Match FundamentalTypeId(LexerT& lexer);
    static soul::parser::Match ParseTypeRef(LexerT& lexer);
    static soul::parser::Match ParseStructureType(LexerT& lexer, otava::intermediate::IntermediateContext* context, std::int32_t typeId);
    static soul::parser::Match ParseArrayType(LexerT& lexer, otava::intermediate::IntermediateContext* context, std::int32_t typeId);
    static soul::parser::Match ParseFunctionType(LexerT& lexer, otava::intermediate::IntermediateContext* context, std::int32_t typeId);
    static soul::parser::Match DataDefinitions(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match DataDefinition(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match Constant(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::Type* type);
    static soul::parser::Match BoolConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match SByteConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ByteConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ShortConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match UShortConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match IntConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match UIntConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match LongConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ULongConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match FloatConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match DoubleConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match AddressConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ArrayConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::Type* type);
    static soul::parser::Match StructureConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::Type* type);
    static soul::parser::Match StringConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match StringArrayConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match StringArrayPrefix(LexerT& lexer);
    static soul::parser::Match ConversionConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ClsIdConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match SymbolConstant(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseValue(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::Type* type);
    static soul::parser::Match ParseRegValue(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::Type* type);
    static soul::parser::Match ResultRegValue(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::Type* type);
    static soul::parser::Match ParseSymbolValue(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::Type* type);
    static soul::parser::Match LiteralValue(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::Type* type);
    static soul::parser::Match FunctionDefinitions(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match FunctionDeclaration(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match FunctionDefinition(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match FunctionHeader(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseBasicBlock(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::Function* function);
    static soul::parser::Match Label(LexerT& lexer);
    static soul::parser::Match Operand(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match Instructions(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::BasicBlock* basicBlock);
    static soul::parser::Match ParseInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseStoreInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseArgInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseJmpInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseBranchInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseProcedureCallInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseRetInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseSwitchInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseValueInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match Operation(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParseUnaryInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParseBinaryInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParseParamInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParseLocalInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParsePLocalInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParseLoadInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParseElemAddrInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParsePtrOffsetInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParsePtrDiffInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParseGetRbpInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParseFunctionCallInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::RegValue* result);
    static soul::parser::Match BlockValue(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseNoOperationInstruction(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseMetadata(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseMetadataStruct(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseMetadataField(LexerT& lexer, otava::intermediate::IntermediateContext* context, otava::intermediate::MetadataStruct* parent);
    static soul::parser::Match ParseMetadataItem(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseMetadataBool(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseMetadataLong(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseMetadataString(LexerT& lexer, otava::intermediate::IntermediateContext* context);
    static soul::parser::Match ParseMetadataRef(LexerT& lexer, otava::intermediate::IntermediateContext* context);
};

} // namespace otava::intermediate::parser
