// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.simple.assembly.code.generator;

import otava.intermediate.code.generator;

export namespace otava::intermediate {

class Instruction;

class SimpleAssemblyCodeGenerator : public CodeGenerator
{
public:
    SimpleAssemblyCodeGenerator(Context* context_, const std::string& assemblyFilePath_);
    Context* Ctx() const override { return context; }
    const SourcePos& GetSourcePos() const override;
    RegisterAllocator* RegAllocator() const override { return registerAllocator; }
    void Emit(otava::assembly::Instruction* assemblyInstruction) override;
    int ExitLabelId() const override;
    void Error(const std::string& message) override;
    otava::assembly::File* AssemblyFile() override { return &file; }
    void Write() override;
    void AddFrameLocation(otava::assembly::UniqueLiteral* frameLoc);
    void Visit(GlobalVariable& globalVariable) override;
    void Visit(Function& function) override;
    void Visit(BasicBlock& basicBlock) override;
    void Visit(StoreInstruction& inst) override;
    void Visit(LoadInstruction& inst) override;
    void Visit(ElemAddrInstruction& inst) override;
    void Visit(PtrOffsetInstruction& inst) override;
    void Visit(PtrDiffInstruction& inst) override;
    void Visit(ArgInstruction& inst) override;
    void Visit(ParamInstruction& inst) override;
    void Visit(RetInstruction& inst) override;
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
    void Visit(SignExtendInstruction& inst) override;
    void Visit(ZeroExtendInstruction& inst) override;
    void Visit(TruncateInstruction& inst) override;
    void Visit(BitcastInstruction& inst) override;
    void Visit(IntToFloatInstruction& inst) override;
    void Visit(FloatToIntInstruction& inst) override;
    void Visit(IntToPtrInstruction& inst) override;
    void Visit(PtrToIntInstruction& inst) override;
    void Visit(EqualInstruction& inst) override;
    void Visit(LessInstruction& inst) override;
    void Visit(JmpInstruction& inst) override;
    void Visit(BranchInstruction& inst) override;
    void Visit(ProcedureCallInstruction& inst) override;
    void Visit(FunctionCallInstruction& inst) override;
    void Visit(NotInstruction& inst) override;
    void Visit(NegInstruction& inst) override;
    void Visit(NoOperationInstruction& inst) override;
    void Visit(SwitchInstruction& inst) override;
private:
    void PatchFrameLocations();
    Context* context;
    otava::assembly::File file;
    Function* currentFunction;
    Instruction* currentInst;
    otava::assembly::Function* assemblyFunction;
    RegisterAllocator* registerAllocator;
    bool leader;
    int lineNumber;
    std::vector<ArgInstruction*> args;
    std::vector<otava::assembly::UniqueLiteral*> frameLocations;
};

} // otava::intermediate
