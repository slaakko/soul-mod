
// this file has been automatically generated from 'D:/work/soul-mod/tools/otava/projects/ocompiler/intermediate/intermediate.parser' using soul parser generator ospg version 5.0.0

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
    static std::expected<bool, int> Parse(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> IntermediateFile(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> TypeDeclarations(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> TypeDeclaration(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> TypeId(LexerT& lexer);
    static std::expected<soul::parser::Match, int> FundamentalTypeId(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ParseTypeRef(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ParseStructureType(LexerT& lexer, otava::intermediate::Context* context, std::int32_t typeId);
    static std::expected<soul::parser::Match, int> ParseArrayType(LexerT& lexer, otava::intermediate::Context* context, std::int32_t typeId);
    static std::expected<soul::parser::Match, int> ParseFunctionType(LexerT& lexer, otava::intermediate::Context* context, std::int32_t typeId);
    static std::expected<soul::parser::Match, int> DataDefinitions(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> DataDefinition(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> Constant(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static std::expected<soul::parser::Match, int> BoolConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> SByteConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ByteConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ShortConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> UShortConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> IntConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> UIntConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> LongConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ULongConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> FloatConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> DoubleConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> AddressConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ArrayConstant(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static std::expected<soul::parser::Match, int> StructureConstant(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static std::expected<soul::parser::Match, int> StringConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> StringArrayConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> StringArrayPrefix(LexerT& lexer);
    static std::expected<soul::parser::Match, int> ConversionConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ClsIdConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> SymbolConstant(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseValue(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static std::expected<soul::parser::Match, int> ParseRegValue(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static std::expected<soul::parser::Match, int> ResultRegValue(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static std::expected<soul::parser::Match, int> ParseSymbolValue(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static std::expected<soul::parser::Match, int> LiteralValue(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static std::expected<soul::parser::Match, int> FunctionDefinitions(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> FunctionDeclaration(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> FunctionDefinition(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> FunctionHeader(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseBasicBlock(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::Function* function);
    static std::expected<soul::parser::Match, int> Label(LexerT& lexer);
    static std::expected<soul::parser::Match, int> Operand(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> Instructions(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::BasicBlock* basicBlock);
    static std::expected<soul::parser::Match, int> ParseInstruction(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseStoreInstruction(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseArgInstruction(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseJmpInstruction(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseBranchInstruction(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseProcedureCallInstruction(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseRetInstruction(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseSwitchInstruction(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseValueInstruction(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> Operation(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static std::expected<soul::parser::Match, int> ParseUnaryInstruction(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static std::expected<soul::parser::Match, int> ParseBinaryInstruction(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static std::expected<soul::parser::Match, int> ParseParamInstruction(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static std::expected<soul::parser::Match, int> ParseLocalInstruction(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static std::expected<soul::parser::Match, int> ParseLoadInstruction(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static std::expected<soul::parser::Match, int> ParseElemAddrInstruction(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static std::expected<soul::parser::Match, int> ParsePtrOffsetInstruction(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static std::expected<soul::parser::Match, int> ParsePtrDiffInstruction(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static std::expected<soul::parser::Match, int> ParseFunctionCallInstruction(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static std::expected<soul::parser::Match, int> ParseNoOperationInstruction(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseMetadata(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseMetadataStruct(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseMetadataField(LexerT& lexer, otava::intermediate::Context* context, otava::intermediate::MetadataStruct* parent);
    static std::expected<soul::parser::Match, int> ParseMetadataItem(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseMetadataBool(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseMetadataLong(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseMetadataString(LexerT& lexer, otava::intermediate::Context* context);
    static std::expected<soul::parser::Match, int> ParseMetadataRef(LexerT& lexer, otava::intermediate::Context* context);
};

} // namespace otava::intermediate::parser
