// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.reg;

namespace otava::assembly {

std::string regName[] = 
{
    "al", "bl", "cl", "dl", "sil", "dil", "bpl", "spl", "r8b", "r9b", "r10b", "r11b", "r12b", "r13b", "r14b", "r15b",
    "ax", "bx", "cx", "dx", "di", "si", "bp", "sp", "r8w", "r9w", "r10w", "r11w", "r12w", "r13w", "r14w", "r15w",
    "eax", "ebx", "ecx", "edx", "edi", "esi", "ebp", "esp", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d",
    "rax", "rbx", "rcx", "rdx", "rbp", "rsi", "rdi", "rsp", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", ""
};


Register::Register() : Value(std::string())
{
}

Register::Register(RegisterKind kind_) : Value(regName[int(kind_)]), kind(kind_)
{
}

RegisterGroup::RegisterGroup() : kind(RegisterGroupKind::max)
{
}

RegisterGroup::RegisterGroup(RegisterGroupKind kind_) : kind(kind_)
{
}

const Register* RegisterGroup::GetReg(int size) const
{
    if (size >= 1 && size <= 8)
    {
        return &regs[size - 1];
    }
    else
    {
        throw std::runtime_error("invalid size");
    }
}

Register* RegisterGroup::GetReg(int size)
{
    if (size >= 1 && size <= 8)
    {
        return &regs[size - 1];
    }
    else
    {
        throw std::runtime_error("invalid size");
    }
}

void RegisterGroup::SetReg(int size, const Register& reg)
{
    if (size >= 1 && size <= 8)
    {
        regs[size - 1] = reg;
    }
    else
    {
        throw std::runtime_error("invalid size");
    }
}

Registers::Registers()
{
    RegisterGroup& rax = regGroups[int(RegisterGroupKind::rax)];
    rax.SetReg(1, Register(RegisterKind::al));
    rax.SetReg(2, Register(RegisterKind::ax));
    rax.SetReg(4, Register(RegisterKind::eax));
    rax.SetReg(8, Register(RegisterKind::rax));

    RegisterGroup& rbx = regGroups[int(RegisterGroupKind::rbx)];
    rbx.SetReg(1, Register(RegisterKind::bl));
    rbx.SetReg(2, Register(RegisterKind::bx));
    rbx.SetReg(4, Register(RegisterKind::ebx));
    rbx.SetReg(8, Register(RegisterKind::rbx));

    RegisterGroup& rcx = regGroups[int(RegisterGroupKind::rcx)];
    rcx.SetReg(1, Register(RegisterKind::cl));
    rcx.SetReg(2, Register(RegisterKind::cx));
    rcx.SetReg(4, Register(RegisterKind::ecx));
    rcx.SetReg(8, Register(RegisterKind::rcx));

    RegisterGroup& rdx = regGroups[int(RegisterGroupKind::rdx)];
    rdx.SetReg(1, Register(RegisterKind::dl));
    rdx.SetReg(2, Register(RegisterKind::dx));
    rdx.SetReg(4, Register(RegisterKind::edx));
    rdx.SetReg(8, Register(RegisterKind::rdx));

    RegisterGroup& rsi = regGroups[int(RegisterGroupKind::rsi)];
    rsi.SetReg(1, Register(RegisterKind::sil));
    rsi.SetReg(2, Register(RegisterKind::si));
    rsi.SetReg(4, Register(RegisterKind::esi));
    rsi.SetReg(8, Register(RegisterKind::rsi));

    RegisterGroup& rdi = regGroups[int(RegisterGroupKind::rdi)];
    rdi.SetReg(1, Register(RegisterKind::dil));
    rdi.SetReg(2, Register(RegisterKind::di));
    rdi.SetReg(4, Register(RegisterKind::edi));
    rdi.SetReg(8, Register(RegisterKind::rdi));

    RegisterGroup& rbp = regGroups[int(RegisterGroupKind::rbp)];
    rbp.SetReg(1, Register(RegisterKind::bpl));
    rbp.SetReg(2, Register(RegisterKind::bp));
    rbp.SetReg(4, Register(RegisterKind::ebp));
    rbp.SetReg(8, Register(RegisterKind::rbp));

    RegisterGroup& rsp = regGroups[int(RegisterGroupKind::rsp)];
    rsp.SetReg(1, Register(RegisterKind::spl));
    rsp.SetReg(2, Register(RegisterKind::sp));
    rsp.SetReg(4, Register(RegisterKind::esp));
    rsp.SetReg(8, Register(RegisterKind::rsp));

    RegisterGroup& r8 = regGroups[int(RegisterGroupKind::r8)];
    r8.SetReg(1, Register(RegisterKind::r8b));
    r8.SetReg(2, Register(RegisterKind::r8w));
    r8.SetReg(4, Register(RegisterKind::r8d));
    r8.SetReg(8, Register(RegisterKind::r8));

    RegisterGroup& r9 = regGroups[int(RegisterGroupKind::r9)];
    r9.SetReg(1, Register(RegisterKind::r9b));
    r9.SetReg(2, Register(RegisterKind::r9w));
    r9.SetReg(4, Register(RegisterKind::r9d));
    r9.SetReg(8, Register(RegisterKind::r9));

    RegisterGroup& r10 = regGroups[int(RegisterGroupKind::r10)];
    r10.SetReg(1, Register(RegisterKind::r10b));
    r10.SetReg(2, Register(RegisterKind::r10w));
    r10.SetReg(4, Register(RegisterKind::r10d));
    r10.SetReg(8, Register(RegisterKind::r10));

    RegisterGroup& r11 = regGroups[int(RegisterGroupKind::r11)];
    r11.SetReg(1, Register(RegisterKind::r11b));
    r11.SetReg(2, Register(RegisterKind::r11w));
    r11.SetReg(4, Register(RegisterKind::r11d));
    r11.SetReg(8, Register(RegisterKind::r11));

    RegisterGroup& r12 = regGroups[int(RegisterGroupKind::r12)];
    r12.SetReg(1, Register(RegisterKind::r12b));
    r12.SetReg(2, Register(RegisterKind::r12w));
    r12.SetReg(4, Register(RegisterKind::r12d));
    r12.SetReg(8, Register(RegisterKind::r12));

    RegisterGroup& r13 = regGroups[int(RegisterGroupKind::r13)];
    r13.SetReg(1, Register(RegisterKind::r13b));
    r13.SetReg(2, Register(RegisterKind::r13w));
    r13.SetReg(4, Register(RegisterKind::r13d));
    r13.SetReg(8, Register(RegisterKind::r13));

    RegisterGroup& r14 = regGroups[int(RegisterGroupKind::r14)];
    r14.SetReg(1, Register(RegisterKind::r14b));
    r14.SetReg(2, Register(RegisterKind::r14w));
    r14.SetReg(4, Register(RegisterKind::r14d));
    r14.SetReg(8, Register(RegisterKind::r14));

    RegisterGroup& r15 = regGroups[int(RegisterGroupKind::r15)];
    r15.SetReg(1, Register(RegisterKind::r15b));
    r15.SetReg(2, Register(RegisterKind::r15w));
    r15.SetReg(4, Register(RegisterKind::r15d));
    r15.SetReg(8, Register(RegisterKind::r15));
}

RegisterPool::RegisterPool(Registers& registers)
{
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r8));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r9));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r10));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r11));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r12));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r13));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r14));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r15));
    localRegisterCount = localRegisterPool.size();
    globalRegisterMap[RegisterGroupKind::rax] = registers.GetRegisterGroup(RegisterGroupKind::rax);
    globalRegisterMap[RegisterGroupKind::rbx] = registers.GetRegisterGroup(RegisterGroupKind::rbx);
    globalRegisterMap[RegisterGroupKind::rcx] = registers.GetRegisterGroup(RegisterGroupKind::rcx);
    globalRegisterMap[RegisterGroupKind::rdx] = registers.GetRegisterGroup(RegisterGroupKind::rdx);
    globalRegisterMap[RegisterGroupKind::rsi] = registers.GetRegisterGroup(RegisterGroupKind::rsi);
    globalRegisterMap[RegisterGroupKind::rdi] = registers.GetRegisterGroup(RegisterGroupKind::rdi);
    globalRegisterMap[RegisterGroupKind::rbp] = registers.GetRegisterGroup(RegisterGroupKind::rbp);
    globalRegisterMap[RegisterGroupKind::rsp] = registers.GetRegisterGroup(RegisterGroupKind::rsp);
}

void RegisterPool::AddLocalRegisterGroup(RegisterGroup* regGroup)
{
    localRegisterPool.insert(regGroup);
}

RegisterGroup* RegisterPool::GetLocalRegisterGroup()
{
    if (localRegisterPool.empty())
    {
        throw std::runtime_error("register pool is empty");
    }
    RegisterGroup* regGroup = *localRegisterPool.begin();
    localRegisterPool.erase(regGroup);
    return regGroup;
}

RegisterGroup* RegisterPool::GetGlobalRegisterGroup(RegisterGroupKind regGroupKind)
{
    auto it = globalRegisterMap.find(regGroupKind);
    if (it != globalRegisterMap.cend())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("invalid global register");
    }
}

bool RegisterGroupLess::operator()(RegisterGroup* left, RegisterGroup* right) const
{
    return int(left->Kind()) < int(right->Kind());
}

} // namespace otava::ast
