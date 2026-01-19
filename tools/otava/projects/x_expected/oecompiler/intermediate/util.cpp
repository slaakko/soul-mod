// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.util;

namespace otava::intermediate {

std::expected<bool, int> ReplaceInstructionWithValue(Instruction* inst, Value* value)
{
    std::expected<bool, int> rv = inst->ReplaceUsesWith(value);
    if (!rv) return rv;
    inst->Parent()->RemoveInstruction(inst);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ReplaceInstructionWithInstruction(Instruction* oldInst, Instruction* newInst)
{
    if (oldInst->IsValueInstruction() && newInst->IsValueInstruction())
    {
        ValueInstruction* valueInst = static_cast<ValueInstruction*>(newInst);
        std::expected<bool, int> rv = oldInst->ReplaceUsesWith(valueInst->Result());
        if (!rv) return rv;
    }
    BasicBlock* bb = oldInst->Parent();
    bb->InsertInstructionAfter(newInst, oldInst);
    bb->RemoveInstruction(oldInst);
    return std::expected<bool, int>(true);
}

bool IsPowerOfTwo(std::uint64_t n, int& shift)
{
    std::uint64_t p = 2;
    shift = 1;
    while (p != 0 && p < n)
    {
        p <<= 1;
        ++shift;
    }
    if (n == p)
    {
        return true;
    }
    else
    {
        return false;
    }
}

} // otava::intermediate
