// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.function;

import otava.assembly.instruction;

namespace otava::assembly {

Function::Function(const std::string& name_) : name(name_), activeFunctionPart(FunctionPart::body)
{
}

void Function::AddInstruction(Instruction* inst)
{
    switch (activeFunctionPart)
    {
        case FunctionPart::prologue:
        {
            prologue.push_back(std::unique_ptr<Instruction>(inst));
            break;
        }
        case FunctionPart::body:
        {
            body.push_back(std::unique_ptr<Instruction>(inst));
            break;
        }
        case FunctionPart::epilogue:
        {
            epilogue.push_back(std::unique_ptr<Instruction>(inst));
            break;
        }
    }
}

void Function::SetActiveFunctionPart(FunctionPart activeFunctionPart_)
{
    activeFunctionPart = activeFunctionPart_;
}

void Function::Write(util::CodeFormatter& formatter)
{
    formatter.WriteLine(name + " PROC");
    formatter.IncIndent();
    for (const auto& instruction : prologue)
    {
        instruction->Write(formatter);
    }
    for (const auto& instruction : body)
    {
        instruction->Write(formatter);
    }
    for (const auto& instruction : epilogue)
    {
        instruction->Write(formatter);
    }    
    formatter.DecIndent();
    formatter.WriteLine(name + " ENDP");
}

} // namespace otava::assembly
