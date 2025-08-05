// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.optimizer.optimizing_code_generator;

import std;
import otava.intermediate;
import otava.assembly;

export namespace otava::optimizer {

const int jumpTableSwitchThreshold = 4;
const int maxJumpTableEntries = 1024;

class OptimizingCodeGenerator : public otava::intermediate::CodeGenerator
{
public:
    OptimizingCodeGenerator(otava::intermediate::Context* context_, const std::string& assemblyFilePath_);
    void Emit(otava::assembly::Instruction* assemblyInstruction) override;
    void Visit(otava::intermediate::SwitchInstruction& inst) override;
    void Visit(otava::intermediate::JmpInstruction& inst) override;
    void Visit(otava::intermediate::RetInstruction& inst) override;
    void Visit(otava::intermediate::NoOperationInstruction& inst) override;
    int ExitLabelId() const override;
    void EmitJumpToExit(otava::intermediate::RetInstruction& retInst) override;
    void EmitBranchJumps(otava::intermediate::BranchInstruction& branchInst) override;
private:
    void EmitXorInst(const std::string& label, otava::assembly::Register* reg);
};

} // otava::optimizer
