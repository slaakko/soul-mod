// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.code_generator;

import otava.assembly;
import otava.intermediate.visitor;
import otava.intermediate.data;
import soul.ast.span;
import std;

export namespace otava::intermediate {

class Instruction;
class RegisterAllocator;

class CodeGenerator : public Visitor
{
public:
    CodeGenerator(Context* context_, const std::string& assemblyFilePath_);
    inline Context* Ctx() const { return context; }
    inline RegisterAllocator* RegAllocator() const { return registerAllocator; }
    inline otava::assembly::Function* AssemblyFunction() const { return assemblyFunction; }
    inline Function* CurrentFunction() const { return currentFunction; }
    const soul::ast::Span& Span() const;
    virtual void Emit(otava::assembly::Instruction* assemblyInstruction);
    void EmitDataValue(std::unique_ptr<otava::assembly::Value>&& dataValue, otava::assembly::OpCode dataOpCode);
    void Visit(GlobalVariable& globalVariable) override;
    void Visit(Function& function) override;
    void Visit(BasicBlock& basicBlock) override;
    void Visit(RetInstruction& inst) override;
    void Visit(SignExtendInstruction& inst) override;
    void Visit(ZeroExtendInstruction& inst) override;
    void Visit(FloatingPointExtendInstruction& inst) override;
    void Visit(ParamInstruction& inst) override;
    void Visit(LoadInstruction& inst) override;
    void Visit(StoreInstruction& inst) override;
    void Visit(ArgInstruction& inst) override;
    void Visit(ProcedureCallInstruction& inst) override;
    void Visit(FunctionCallInstruction& inst) override;
    void Visit(ElemAddrInstruction& inst) override;
    void Visit(PtrOffsetInstruction& inst) override;
    void Visit(PtrDiffInstruction& inst) override;
    void Visit(TruncateInstruction& inst) override;
    void Visit(AddInstruction& inst) override;
    void Visit(SubInstruction& inst) override;
    void Visit(MulInstruction& inst) override;
    void Visit(DivInstruction& inst) override;
    void Visit(ModInstruction& inst) override;
    void Visit(AndInstruction& inst) override;
    void Visit(OrInstruction& inst) override;
    void Visit(XorInstruction& inst) override;
    void Visit(ShlInstruction& inst) override;
    void Visit(ShrInstruction& inst) override;
    void Visit(BitcastInstruction& inst) override;
    void Visit(IntToFloatInstruction& inst) override;
    void Visit(FloatToIntInstruction& inst) override;
    void Visit(IntToPtrInstruction& inst) override;
    void Visit(PtrToIntInstruction& inst) override;
    void Visit(EqualInstruction& inst) override;
    void Visit(LessInstruction& inst) override;
    void Visit(JmpInstruction& inst) override;
    void Visit(BranchInstruction& inst) override;
    void Visit(NotInstruction& inst) override;
    void Visit(NegInstruction& inst) override;
    void Visit(NoOperationInstruction& inst) override;
    void Visit(SwitchInstruction& inst) override;
    void Visit(BoolValue& value) override;
    void Visit(SByteValue& value) override;
    void Visit(ByteValue& value) override;
    void Visit(ShortValue& value) override;
    void Visit(UShortValue& value) override;
    void Visit(IntValue& value) override;
    void Visit(UIntValue& value) override;
    void Visit(LongValue& value) override;
    void Visit(ULongValue& value) override;
    void Visit(FloatValue& value) override;
    void Visit(DoubleValue& value) override;
    void Visit(NullValue& value) override;
    void Visit(AddressValue& value) override;
    void Visit(ArrayValue& value) override;
    void Visit(StructureValue& value) override;
    void Visit(StringValue& value) override;
    void Visit(StringArrayValue& value) override;
    void Visit(ConversionValue& value) override;
    void Visit(SymbolValue& value) override;
    std::unexpected<int> Error(const std::string& message);
    void WriteOutputFile(bool verbose);
    inline void ResetLeader() { leader = false; }
    virtual int ExitLabelId() const;
    virtual void EmitJumpToExit(RetInstruction& retInst);
    virtual void EmitBranchJumps(BranchInstruction& branchInst);
private:
    Context* context;
    otava::assembly::File file;
    Function* currentFunction;
    Instruction* currentInst;
    otava::assembly::Function* assemblyFunction;
    RegisterAllocator* registerAllocator;
    std::vector<ArgInstruction*> args;
    bool leader;
    otava::assembly::Data* data;
    std::string label;
    std::unique_ptr<otava::assembly::Instruction> dataInstruction;
    otava::assembly::OpCode prevDataOpCode;
    std::int64_t currentOffset;
};

std::expected<otava::assembly::Register*, int> MakeIntegerRegOperand(Value* value, otava::assembly::Register* reg, CodeGenerator& codeGenerator);
void EmitSwitch(SwitchInstruction& inst, CodeGenerator& codeGenerator);

std::expected<bool, int> GenerateCode(Context& context, CodeGenerator& codeGenerator, bool verbose);

} // otava::intermediate
