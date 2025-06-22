
// this file has been automatically generated from 'C:/work/soul-mod/tools/otava/intermediate/intermediate.parser' using soul parser generator spg version 4.1.0

export module otava.intermediate.code.parser;

import std;
import soul.lexer;
import soul.parser;
import otava.intermediate.context;

using namespace otava::intermediate::context;

export namespace otava::intermediate::code::parser {

template<typename Lexer>
struct IntermediateCodeParser
{
    static void Parse(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match IntermediateCodeFile(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match CompileUnitHeader(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match CompileUnitId(Lexer& lexer);
    static soul::parser::Match TypeDeclarations(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match TypeDeclaration(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match TypeId(Lexer& lexer);
    static soul::parser::Match FundamentalTypeId(Lexer& lexer);
    static soul::parser::Match TypeRef(Lexer& lexer);
    static soul::parser::Match StructureType(Lexer& lexer, otava::intermediate::Context* context, std::int32_t typeId);
    static soul::parser::Match ArrayType(Lexer& lexer, otava::intermediate::Context* context, std::int32_t typeId);
    static soul::parser::Match FunctionType(Lexer& lexer, otava::intermediate::Context* context, std::int32_t typeId);
    static soul::parser::Match DataDefinitions(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match DataDefinition(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match Constant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match BoolConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match SByteConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match ByteConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match ShortConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match UShortConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match IntConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match UIntConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match LongConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match ULongConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match FloatConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match DoubleConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match AddressConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match ArrayConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match StructureConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match StringConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match StringArrayConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match StringArrayPrefix(Lexer& lexer);
    static soul::parser::Match ConversionConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match ClsIdConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match SymbolConstant(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match Value(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static soul::parser::Match RegValue(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static soul::parser::Match ResultRegValue(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static soul::parser::Match SymbolValue(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static soul::parser::Match LiteralValue(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Type* type);
    static soul::parser::Match FunctionDefinitions(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match ExternalFunctionDeclaration(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match FunctionDefinition(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match FunctionHeader(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match BasicBlock(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::Function* function);
    static soul::parser::Match Label(Lexer& lexer);
    static soul::parser::Match Operand(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match Instructions(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::BasicBlock* basicBlock);
    static soul::parser::Match Instruction(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match StoreInstruction(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match ArgInstruction(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match JmpInstruction(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match BranchInstruction(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match ProcedureCallInstruction(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match RetInstruction(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match SwitchInstruction(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match ValueInstruction(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match Operation(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match UnaryInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match BinaryInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ParamInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match LocalInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match LoadInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match ElemAddrInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match PtrOffsetInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match PtrDiffInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match FunctionCallInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match TrapInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match PhiInstruction(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::RegValue* result);
    static soul::parser::Match BlockValue(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match NoOperationInstruction(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match Metadata(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match MetadataStruct(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match MetadataField(Lexer& lexer, otava::intermediate::Context* context, otava::intermediate::MetadataStruct* parent);
    static soul::parser::Match MetadataItem(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match MetadataBool(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match MetadataLong(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match MetadataString(Lexer& lexer, otava::intermediate::Context* context);
    static soul::parser::Match MetadataRef(Lexer& lexer, otava::intermediate::Context* context);
};

} // namespace otava::intermediate::code::parser
