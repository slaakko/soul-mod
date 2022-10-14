// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.function;

import otava.assembly.instruction;

namespace otava::assembly {

Function::Function(const std::string& name_) : name(name_)
{
}

void Function::AddInstruction(Instruction* inst)
{
    instructions.push_back(std::unique_ptr<Instruction>(inst));
}

void Function::Write(util::CodeFormatter& formatter)
{
    formatter.WriteLine(name + " PROC");
    formatter.IncIndent();
    for (const auto& inst : instructions)
    {
        inst->Write(formatter);
    }
    formatter.DecIndent();
    formatter.WriteLine(name + " ENDP");
}

} // namespace otava::assembly
