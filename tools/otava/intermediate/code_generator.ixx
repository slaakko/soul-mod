// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.code.generator;

import otava.intermediate.visitor;
import otava.intermediate.register_allocator;
import otava.assembly.instruction;
import otava.assembly.file;
import soul.ast.source.pos;
import std.core;

export namespace otava::intermediate {

using SourcePos = soul::ast::SourcePos;

class BinaryInstruction;
class Context;
class RegisterAllocator;
class CallFrame;

class CodeGenerator : public Visitor
{
public:
    CodeGenerator(Context* context_);
    virtual ~CodeGenerator();
    virtual Context* Ctx() const = 0;
    virtual const SourcePos& GetSourcePos() const = 0;
    virtual RegisterAllocator* RegAllocator() const = 0;
    virtual void Emit(otava::assembly::Instruction* assemblyInstruction) = 0;
    virtual void Error(const std::string& message) = 0;
    virtual int ExitLabelId() const = 0;
    virtual otava::assembly::File* AssemblyFile() = 0;
    virtual void Write() = 0;
};

void GenerateCode(Context& context, CodeGenerator& codeGenerator, bool verbose);

void EmitParam(ParamInstruction& inst, CodeGenerator& codeGen);
void EmitLoad(int64_t size, const FrameLocation& frameLocation, otava::assembly::RegisterGroup* regGroup, CodeGenerator& codeGen);
void EmitStore(int64_t size, const FrameLocation& frameLocation, otava::assembly::RegisterGroup* regGroup, CodeGenerator& codeGen);
void EmitLoad(LoadInstruction& inst, CodeGenerator& codeGen);
void EmitStore(StoreInstruction& inst, CodeGenerator& codeGen);
void EmitElemAddr(ElemAddrInstruction& inst, CodeGenerator& codeGen);
void EmitPtrOffset(PtrOffsetInstruction& inst, CodeGenerator& codeGen);
void EmitPtrDiff(PtrDiffInstruction& inst, CodeGenerator& codeGen);
void EmitArg(ArgInstruction& inst, CallFrame* callFrame, int32_t index, CodeGenerator& codeGen);
void EmitArgs(const std::vector<ArgInstruction*>& args, CodeGenerator& codeGen);
void EmitSignExtend(SignExtendInstruction& inst, CodeGenerator& codeGen);
void EmitZeroExtend(ZeroExtendInstruction& inst, CodeGenerator& codeGen);
void EmitTruncate(TruncateInstruction& inst, CodeGenerator& codeGen);
void EmitBitcast(BitcastInstruction& inst, CodeGenerator& codeGen);
void EmitIntToFloat(IntToFloatInstruction& inst, CodeGenerator& codeGen);
void EmitFloatToInt(FloatToIntInstruction& inst, CodeGenerator& codeGen);
void EmitIntToPtr(IntToPtrInstruction& inst, CodeGenerator& codeGen);
void EmitPtrToInt(PtrToIntInstruction& inst, CodeGenerator& codeGen);
void EmitEqual(EqualInstruction& inst, CodeGenerator& codeGen);
void EmitLess(LessInstruction& inst, CodeGenerator& codeGen);
void EmitJmp(JmpInstruction& inst, CodeGenerator& codeGen);
void EmitBranch(BranchInstruction& inst, CodeGenerator& codeGen);
void EmitProcedureCall(ProcedureCallInstruction& inst, const std::vector<ArgInstruction*>& args, CodeGenerator& codeGen);
void EmitFunctionCall(FunctionCallInstruction& inst, const std::vector<ArgInstruction*>& args, CodeGenerator& codeGen);
void EmitRet(RetInstruction& inst, CodeGenerator& codeGen);
void EmitIntegerBinOpInst(BinaryInstruction& inst, CodeGenerator& codeGen);
void EmitFloatingPointBinOpInst(BinaryInstruction& inst, CodeGenerator& codeGen);
void EmitNot(NotInstruction& inst, CodeGenerator& codeGen);
void EmitNeg(NegInstruction& inst, CodeGenerator& codeGen);
void EmitPrologue(CodeGenerator& codeGen);
void EmitEpilogue(CodeGenerator& codeGen);


} // otava::intermediate
