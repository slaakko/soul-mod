// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.assembly.reg;

import util;

namespace otava::assembly {

std::string RegName(RegisterKind kind)
{
    switch (kind)
    {
        case RegisterKind::al: return "al";
        case RegisterKind::bl: return "bl";
        case RegisterKind::cl: return "cl";
        case RegisterKind::dl: return "dl";
        case RegisterKind::sil: return "sil";
        case RegisterKind::dil: return "dil";
        case RegisterKind::bpl: return "bpl";
        case RegisterKind::spl: return "spl";
        case RegisterKind::r8b: return "r8b";
        case RegisterKind::r9b: return "r9b";
        case RegisterKind::r10b: return "r10b";
        case RegisterKind::r11b: return "r11b";
        case RegisterKind::r12b: return "r12b";
        case RegisterKind::r13b: return "r13b";
        case RegisterKind::r14b: return "r14b";
        case RegisterKind::r15b: return "r15b";
        case RegisterKind::ax: return "ax";
        case RegisterKind::bx: return "bx";
        case RegisterKind::cx: return "cx";
        case RegisterKind::dx: return "dx";
        case RegisterKind::si: return "si";
        case RegisterKind::di: return "di";
        case RegisterKind::bp: return "bp";
        case RegisterKind::sp: return "sp";
        case RegisterKind::r8w: return "r8w";
        case RegisterKind::r9w: return "r9w";
        case RegisterKind::r10w: return "r10w";
        case RegisterKind::r11w: return "r11w";
        case RegisterKind::r12w: return "r12w";
        case RegisterKind::r13w: return "r13w";
        case RegisterKind::r14w: return "r14w";
        case RegisterKind::r15w: return "r15w";
        case RegisterKind::eax: return "eax";
        case RegisterKind::ebx: return "ebx";
        case RegisterKind::ecx: return "ecx";
        case RegisterKind::edx: return "edx";
        case RegisterKind::esi: return "esi";
        case RegisterKind::edi: return "edi";
        case RegisterKind::ebp: return "ebp";
        case RegisterKind::esp: return "esp";
        case RegisterKind::r8d: return "r8d";
        case RegisterKind::r9d: return "r9d";
        case RegisterKind::r10d: return "r10d";
        case RegisterKind::r11d: return "r11d";
        case RegisterKind::r12d: return "r12d";
        case RegisterKind::r13d: return "r13d";
        case RegisterKind::r14d: return "r14d";
        case RegisterKind::r15d: return "r15d";
        case RegisterKind::rax: return "rax";
        case RegisterKind::rbx: return "rbx";
        case RegisterKind::rcx: return "rcx";
        case RegisterKind::rdx: return "rdx";
        case RegisterKind::rsi: return "rsi";
        case RegisterKind::rdi: return "rdi";
        case RegisterKind::rbp: return "rbp";
        case RegisterKind::rsp: return "rsp";
        case RegisterKind::r8: return "r8";
        case RegisterKind::r9: return "r9";
        case RegisterKind::r10: return "r10";
        case RegisterKind::r11: return "r11";
        case RegisterKind::r12: return "r12";
        case RegisterKind::r13: return "r13";
        case RegisterKind::r14: return "r14";
        case RegisterKind::r15: return "r15";
        case RegisterKind::ah: return "ah";
        case RegisterKind::bh: return "bh";
        case RegisterKind::ch: return "ch";
        case RegisterKind::dh: return "dh";
        case RegisterKind::xmm0: return "xmm0";
        case RegisterKind::xmm1: return "xmm1";
        case RegisterKind::xmm2: return "xmm2";
        case RegisterKind::xmm3: return "xmm3";
        case RegisterKind::xmm4: return "xmm4";
        case RegisterKind::xmm5: return "xmm5";
        case RegisterKind::xmm6: return "xmm6";
        case RegisterKind::xmm7: return "xmm7";
        case RegisterKind::xmm8: return "xmm8";
        case RegisterKind::xmm9: return "xmm9";
        case RegisterKind::xmm10: return "xmm10";
        case RegisterKind::xmm11: return "xmm11";
        case RegisterKind::xmm12: return "xmm12";
        case RegisterKind::xmm13: return "xmm13";
        case RegisterKind::xmm14: return "xmm14";
        case RegisterKind::xmm15: return "xmm15";
    }
    return "<reg>";
}

Register::Register() : Value(ValueKind::reg, std::string()), kind(), group(), size(0)
{
}

Register::Register(RegisterKind kind_, RegisterGroupKind group_, int size_) : Value(ValueKind::reg, RegName(kind_)), kind(kind_), group(group_), size(size_)
{
}

RegisterGroup::RegisterGroup() : kind(RegisterGroupKind::max), nonvolatile(false)
{
    regs.resize(16);
}

RegisterGroup::RegisterGroup(RegisterGroupKind kind_) : kind(kind_), nonvolatile(false)
{
    regs.resize(16);
}

std::expected<const Register*, int> RegisterGroup::GetReg(std::int64_t size) const
{
    if (size >= 1 && size <= 8 || size == highByteRegSize || size == 16)
    {
        const Register* r = &regs[size - 1];
        return std::expected<const Register*, int>(r);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.assembly.RegisterGroup::GetReg: invalid size"));
    }
}

std::expected<Register*, int> RegisterGroup::GetReg(std::int64_t size)
{
    if (size >= 1 && size <= 8 || size == highByteRegSize || size == 16)
    {
        Register* r = &regs[size - 1];
        return std::expected<Register*, int>(r);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.assembly.RegisterGroup::GetReg: invalid size"));
    }
}

std::expected<bool, int> RegisterGroup::SetReg(std::int64_t size, const Register& reg)
{
    if (size >= 1 && size <= 8 || size == highByteRegSize || size == 16)
    {
        regs[size - 1] = reg;
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.assembly.RegisterGroup::GetReg: invalid size"));
    }
    return std::expected<bool, int>(true);
}

bool RegisterGroup::IsLocal() const
{
    if (kind == RegisterGroupKind::rsi || kind == RegisterGroupKind::rdi || kind >= RegisterGroupKind::r12 && kind <= RegisterGroupKind::r15)
    {
        return true;
    }
    else if (kind >= RegisterGroupKind::xmm6 && kind <= RegisterGroupKind::xmm15)
    {
        return true;
    }
    return false;
}

Registers::Registers() : error(0)
{
    RegisterGroup* rax = new RegisterGroup(RegisterGroupKind::rax);
    rax->SetNonvolatile(false);
    auto rv = rax->SetReg(1, Register(RegisterKind::al, RegisterGroupKind::rax, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rax->SetReg(2, Register(RegisterKind::ax, RegisterGroupKind::rax, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rax->SetReg(4, Register(RegisterKind::eax, RegisterGroupKind::rax, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rax->SetReg(8, Register(RegisterKind::rax, RegisterGroupKind::rax, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rax->SetReg(highByteRegSize, Register(RegisterKind::ah, RegisterGroupKind::rax, highByteRegSize));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(rax));

    RegisterGroup* rbx = new RegisterGroup(RegisterGroupKind::rbx);
    rbx->SetNonvolatile(true);
    rv = rbx->SetReg(1, Register(RegisterKind::bl, RegisterGroupKind::rbx, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rbx->SetReg(2, Register(RegisterKind::bx, RegisterGroupKind::rbx, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rbx->SetReg(4, Register(RegisterKind::ebx, RegisterGroupKind::rbx, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rbx->SetReg(8, Register(RegisterKind::rbx, RegisterGroupKind::rbx, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rbx->SetReg(highByteRegSize, Register(RegisterKind::bh, RegisterGroupKind::rbx, highByteRegSize));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(rbx));

    RegisterGroup* rcx = new RegisterGroup(RegisterGroupKind::rcx);
    rcx->SetNonvolatile(false);
    rv = rcx->SetReg(1, Register(RegisterKind::cl, RegisterGroupKind::rcx, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rcx->SetReg(2, Register(RegisterKind::cx, RegisterGroupKind::rcx, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rcx->SetReg(4, Register(RegisterKind::ecx, RegisterGroupKind::rcx, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rcx->SetReg(8, Register(RegisterKind::rcx, RegisterGroupKind::rcx, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rcx->SetReg(highByteRegSize, Register(RegisterKind::ch, RegisterGroupKind::rcx, highByteRegSize));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(rcx));

    RegisterGroup* rdx = new RegisterGroup(RegisterGroupKind::rdx);
    rdx->SetNonvolatile(false);
    rv = rdx->SetReg(1, Register(RegisterKind::dl, RegisterGroupKind::rdx, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rdx->SetReg(2, Register(RegisterKind::dx, RegisterGroupKind::rdx, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rdx->SetReg(4, Register(RegisterKind::edx, RegisterGroupKind::rdx, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rdx->SetReg(8, Register(RegisterKind::rdx, RegisterGroupKind::rdx, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rdx->SetReg(highByteRegSize, Register(RegisterKind::dh, RegisterGroupKind::rdx, highByteRegSize));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(rdx));

    RegisterGroup* rsi = new RegisterGroup(RegisterGroupKind::rsi);
    rsi->SetNonvolatile(true);
    rv = rsi->SetReg(1, Register(RegisterKind::sil, RegisterGroupKind::rsi, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rsi->SetReg(2, Register(RegisterKind::si, RegisterGroupKind::rsi, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rsi->SetReg(4, Register(RegisterKind::esi, RegisterGroupKind::rsi, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rsi->SetReg(8, Register(RegisterKind::rsi, RegisterGroupKind::rsi, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(rsi));

    RegisterGroup* rdi = new RegisterGroup(RegisterGroupKind::rdi);
    rdi->SetNonvolatile(true);
    rv = rdi->SetReg(1, Register(RegisterKind::dil, RegisterGroupKind::rdi, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rdi->SetReg(2, Register(RegisterKind::di, RegisterGroupKind::rdi, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rdi->SetReg(4, Register(RegisterKind::edi, RegisterGroupKind::rdi, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rdi->SetReg(8, Register(RegisterKind::rdi, RegisterGroupKind::rdi, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(rdi));

    RegisterGroup* rbp = new RegisterGroup(RegisterGroupKind::rbp);
    rbp->SetNonvolatile(false);
    rv = rbp->SetReg(1, Register(RegisterKind::bpl, RegisterGroupKind::rbp, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rbp->SetReg(2, Register(RegisterKind::bp, RegisterGroupKind::rbp, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rbp->SetReg(4, Register(RegisterKind::ebp, RegisterGroupKind::rbp, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rbp->SetReg(8, Register(RegisterKind::rbp, RegisterGroupKind::rbp, 8));
    regGroups.push_back(std::unique_ptr<RegisterGroup>(rbp));

    RegisterGroup* rsp = new RegisterGroup(RegisterGroupKind::rsp);
    rsp->SetNonvolatile(false);
    rv = rsp->SetReg(1, Register(RegisterKind::spl, RegisterGroupKind::rsp, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rsp->SetReg(2, Register(RegisterKind::sp, RegisterGroupKind::rsp, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rsp->SetReg(4, Register(RegisterKind::esp, RegisterGroupKind::rsp, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = rsp->SetReg(8, Register(RegisterKind::rsp, RegisterGroupKind::rsp, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(rsp));

    RegisterGroup* r8 = new RegisterGroup(RegisterGroupKind::r8);
    r8->SetNonvolatile(false);
    rv = r8->SetReg(1, Register(RegisterKind::r8b, RegisterGroupKind::r8, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r8->SetReg(2, Register(RegisterKind::r8w, RegisterGroupKind::r8, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r8->SetReg(4, Register(RegisterKind::r8d, RegisterGroupKind::r8, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r8->SetReg(8, Register(RegisterKind::r8, RegisterGroupKind::r8, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(r8));

    RegisterGroup* r9 = new RegisterGroup(RegisterGroupKind::r9);
    r9->SetNonvolatile(false);
    rv = r9->SetReg(1, Register(RegisterKind::r9b, RegisterGroupKind::r9, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r9->SetReg(2, Register(RegisterKind::r9w, RegisterGroupKind::r9, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r9->SetReg(4, Register(RegisterKind::r9d, RegisterGroupKind::r9, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r9->SetReg(8, Register(RegisterKind::r9, RegisterGroupKind::r9, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(r9));

    RegisterGroup* r10 = new RegisterGroup(RegisterGroupKind::r10);
    r10->SetNonvolatile(false);
    rv = r10->SetReg(1, Register(RegisterKind::r10b, RegisterGroupKind::r10, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r10->SetReg(2, Register(RegisterKind::r10w, RegisterGroupKind::r10, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r10->SetReg(4, Register(RegisterKind::r10d, RegisterGroupKind::r10, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r10->SetReg(8, Register(RegisterKind::r10, RegisterGroupKind::r10, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(r10));

    RegisterGroup* r11 = new RegisterGroup(RegisterGroupKind::r11);
    r11->SetNonvolatile(false);
    rv = r11->SetReg(1, Register(RegisterKind::r11b, RegisterGroupKind::r11, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r11->SetReg(2, Register(RegisterKind::r11w, RegisterGroupKind::r11, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r11->SetReg(4, Register(RegisterKind::r11d, RegisterGroupKind::r11, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r11->SetReg(8, Register(RegisterKind::r11, RegisterGroupKind::r11, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(r11));

    RegisterGroup* r12 = new RegisterGroup(RegisterGroupKind::r12);
    r12->SetNonvolatile(true);
    rv = r12->SetReg(1, Register(RegisterKind::r12b, RegisterGroupKind::r12, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r12->SetReg(2, Register(RegisterKind::r12w, RegisterGroupKind::r12, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r12->SetReg(4, Register(RegisterKind::r12d, RegisterGroupKind::r12, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r12->SetReg(8, Register(RegisterKind::r12, RegisterGroupKind::r12, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(r12));

    RegisterGroup* r13 = new RegisterGroup(RegisterGroupKind::r13);
    r13->SetNonvolatile(true);
    rv = r13->SetReg(1, Register(RegisterKind::r13b, RegisterGroupKind::r13, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r13->SetReg(2, Register(RegisterKind::r13w, RegisterGroupKind::r13, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r13->SetReg(4, Register(RegisterKind::r13d, RegisterGroupKind::r13, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r13->SetReg(8, Register(RegisterKind::r13, RegisterGroupKind::r13, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(r13));

    RegisterGroup* r14 = new RegisterGroup(RegisterGroupKind::r14);
    r14->SetNonvolatile(true);
    rv = r14->SetReg(1, Register(RegisterKind::r14b, RegisterGroupKind::r14, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r14->SetReg(2, Register(RegisterKind::r14w, RegisterGroupKind::r14, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r14->SetReg(4, Register(RegisterKind::r14d, RegisterGroupKind::r14, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r14->SetReg(8, Register(RegisterKind::r14, RegisterGroupKind::r14, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(r14));

    RegisterGroup* r15 = new RegisterGroup(RegisterGroupKind::r15);
    r15->SetNonvolatile(true);
    rv = r15->SetReg(1, Register(RegisterKind::r15b, RegisterGroupKind::r15, 1));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r15->SetReg(2, Register(RegisterKind::r15w, RegisterGroupKind::r15, 2));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r15->SetReg(4, Register(RegisterKind::r15d, RegisterGroupKind::r15, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = r15->SetReg(8, Register(RegisterKind::r15, RegisterGroupKind::r15, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(r15));

    RegisterGroup* xmm0 = new RegisterGroup(RegisterGroupKind::xmm0);
    rv = xmm0->SetReg(4, Register(RegisterKind::xmm0, RegisterGroupKind::xmm0, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm0->SetReg(8, Register(RegisterKind::xmm0, RegisterGroupKind::xmm0, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm0->SetReg(16, Register(RegisterKind::xmm0, RegisterGroupKind::xmm0, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm0));

    RegisterGroup* xmm1 = new RegisterGroup(RegisterGroupKind::xmm1);
    rv = xmm1->SetReg(4, Register(RegisterKind::xmm1, RegisterGroupKind::xmm1, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm1->SetReg(8, Register(RegisterKind::xmm1, RegisterGroupKind::xmm1, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm1->SetReg(16, Register(RegisterKind::xmm1, RegisterGroupKind::xmm1, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm1));

    RegisterGroup* xmm2 = new RegisterGroup(RegisterGroupKind::xmm2);
    rv = xmm2->SetReg(4, Register(RegisterKind::xmm2, RegisterGroupKind::xmm2, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm2->SetReg(8, Register(RegisterKind::xmm2, RegisterGroupKind::xmm2, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm2->SetReg(16, Register(RegisterKind::xmm2, RegisterGroupKind::xmm2, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm2));

    RegisterGroup* xmm3 = new RegisterGroup(RegisterGroupKind::xmm3);
    rv = xmm3->SetReg(4, Register(RegisterKind::xmm3, RegisterGroupKind::xmm3, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm3->SetReg(8, Register(RegisterKind::xmm3, RegisterGroupKind::xmm3, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm3->SetReg(16, Register(RegisterKind::xmm3, RegisterGroupKind::xmm3, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm3));

    RegisterGroup* xmm4 = new RegisterGroup(RegisterGroupKind::xmm4);
    rv = xmm4->SetReg(4, Register(RegisterKind::xmm4, RegisterGroupKind::xmm4, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm4->SetReg(8, Register(RegisterKind::xmm4, RegisterGroupKind::xmm4, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm4->SetReg(16, Register(RegisterKind::xmm4, RegisterGroupKind::xmm4, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm4));

    RegisterGroup* xmm5 = new RegisterGroup(RegisterGroupKind::xmm5);
    rv = xmm5->SetReg(4, Register(RegisterKind::xmm5, RegisterGroupKind::xmm5, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm5->SetReg(8, Register(RegisterKind::xmm5, RegisterGroupKind::xmm5, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm5->SetReg(16, Register(RegisterKind::xmm5, RegisterGroupKind::xmm5, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm5));

    RegisterGroup* xmm6 = new RegisterGroup(RegisterGroupKind::xmm6);
    xmm6->SetNonvolatile(true);
    rv = xmm6->SetReg(4, Register(RegisterKind::xmm6, RegisterGroupKind::xmm6, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm6->SetReg(8, Register(RegisterKind::xmm6, RegisterGroupKind::xmm6, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm6->SetReg(16, Register(RegisterKind::xmm6, RegisterGroupKind::xmm6, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm6));

    RegisterGroup* xmm7 = new RegisterGroup(RegisterGroupKind::xmm7);
    xmm7->SetNonvolatile(true);
    rv = xmm7->SetReg(4, Register(RegisterKind::xmm7, RegisterGroupKind::xmm7, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm7->SetReg(8, Register(RegisterKind::xmm7, RegisterGroupKind::xmm7, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm7->SetReg(16, Register(RegisterKind::xmm7, RegisterGroupKind::xmm7, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm7));

    RegisterGroup* xmm8 = new RegisterGroup(RegisterGroupKind::xmm8);
    xmm8->SetNonvolatile(true);
    rv = xmm8->SetReg(4, Register(RegisterKind::xmm8, RegisterGroupKind::xmm8, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm8->SetReg(8, Register(RegisterKind::xmm8, RegisterGroupKind::xmm8, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm8->SetReg(16, Register(RegisterKind::xmm8, RegisterGroupKind::xmm8, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm8));

    RegisterGroup* xmm9 = new RegisterGroup(RegisterGroupKind::xmm9);
    xmm9->SetNonvolatile(true);
    rv = xmm9->SetReg(4, Register(RegisterKind::xmm9, RegisterGroupKind::xmm9, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm9->SetReg(8, Register(RegisterKind::xmm9, RegisterGroupKind::xmm9, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm9->SetReg(16, Register(RegisterKind::xmm9, RegisterGroupKind::xmm9, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm9));

    RegisterGroup* xmm10 = new RegisterGroup(RegisterGroupKind::xmm10);
    xmm10->SetNonvolatile(true);
    rv = xmm10->SetReg(4, Register(RegisterKind::xmm10, RegisterGroupKind::xmm10, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm10->SetReg(8, Register(RegisterKind::xmm10, RegisterGroupKind::xmm10, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm10->SetReg(16, Register(RegisterKind::xmm10, RegisterGroupKind::xmm10, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm10));

    RegisterGroup* xmm11 = new RegisterGroup(RegisterGroupKind::xmm11);
    xmm11->SetNonvolatile(true);
    rv = xmm11->SetReg(4, Register(RegisterKind::xmm11, RegisterGroupKind::xmm11, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm11->SetReg(8, Register(RegisterKind::xmm11, RegisterGroupKind::xmm11, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm11->SetReg(16, Register(RegisterKind::xmm11, RegisterGroupKind::xmm11, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm11));

    RegisterGroup* xmm12 = new RegisterGroup(RegisterGroupKind::xmm12);
    xmm12->SetNonvolatile(true);
    rv = xmm12->SetReg(4, Register(RegisterKind::xmm12, RegisterGroupKind::xmm12, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm12->SetReg(8, Register(RegisterKind::xmm12, RegisterGroupKind::xmm12, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm12->SetReg(16, Register(RegisterKind::xmm12, RegisterGroupKind::xmm12, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm12));

    RegisterGroup* xmm13 = new RegisterGroup(RegisterGroupKind::xmm13);
    xmm13->SetNonvolatile(true);
    rv = xmm13->SetReg(4, Register(RegisterKind::xmm13, RegisterGroupKind::xmm13, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm13->SetReg(8, Register(RegisterKind::xmm13, RegisterGroupKind::xmm13, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm13->SetReg(16, Register(RegisterKind::xmm13, RegisterGroupKind::xmm13, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm13));

    RegisterGroup* xmm14 = new RegisterGroup(RegisterGroupKind::xmm14);
    xmm14->SetNonvolatile(true);
    rv = xmm14->SetReg(4, Register(RegisterKind::xmm14, RegisterGroupKind::xmm14, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm14->SetReg(8, Register(RegisterKind::xmm14, RegisterGroupKind::xmm14, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm14->SetReg(16, Register(RegisterKind::xmm14, RegisterGroupKind::xmm14, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm14));

    RegisterGroup* xmm15 = new RegisterGroup(RegisterGroupKind::xmm15);
    xmm15->SetNonvolatile(true);
    rv = xmm15->SetReg(4, Register(RegisterKind::xmm15, RegisterGroupKind::xmm15, 4));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm15->SetReg(8, Register(RegisterKind::xmm15, RegisterGroupKind::xmm15, 8));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    rv = xmm15->SetReg(16, Register(RegisterKind::xmm15, RegisterGroupKind::xmm15, 16));
    if (!rv)
    {
        error = rv.error();
        return;
    }
    regGroups.push_back(std::unique_ptr<RegisterGroup>(xmm15));
}

RegisterPool::RegisterPool(Registers& registers_) : registers(registers_), localRegisterCount(0), localXMMRegisterCount(0)
{
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::rsi));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::rdi));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r12));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r13));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r14));
    AddLocalRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::r15));
    AddLocalXMMRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::xmm6));
    AddLocalXMMRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::xmm7));
    AddLocalXMMRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::xmm8));
    AddLocalXMMRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::xmm9));
    AddLocalXMMRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::xmm10));
    AddLocalXMMRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::xmm11));
    AddLocalXMMRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::xmm12));
    AddLocalXMMRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::xmm13));
    AddLocalXMMRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::xmm14));
    AddLocalXMMRegisterGroup(registers.GetRegisterGroup(RegisterGroupKind::xmm15));
    localRegisterCount = static_cast<int>(localRegisterPool.size());
    localXMMRegisterCount = static_cast<int>(localXMMRegisterPool.size());
    globalRegisterMap[RegisterGroupKind::rax] = registers.GetRegisterGroup(RegisterGroupKind::rax);
    globalRegisterMap[RegisterGroupKind::rbx] = registers.GetRegisterGroup(RegisterGroupKind::rbx);
    globalRegisterMap[RegisterGroupKind::rcx] = registers.GetRegisterGroup(RegisterGroupKind::rcx);
    globalRegisterMap[RegisterGroupKind::rdx] = registers.GetRegisterGroup(RegisterGroupKind::rdx);
    globalRegisterMap[RegisterGroupKind::r8] = registers.GetRegisterGroup(RegisterGroupKind::r8);
    globalRegisterMap[RegisterGroupKind::r9] = registers.GetRegisterGroup(RegisterGroupKind::r9);
    globalRegisterMap[RegisterGroupKind::r10] = registers.GetRegisterGroup(RegisterGroupKind::r10);
    globalRegisterMap[RegisterGroupKind::r11] = registers.GetRegisterGroup(RegisterGroupKind::r11);
    globalRegisterMap[RegisterGroupKind::rbp] = registers.GetRegisterGroup(RegisterGroupKind::rbp);
    globalRegisterMap[RegisterGroupKind::rsp] = registers.GetRegisterGroup(RegisterGroupKind::rsp);
    globalRegisterMap[RegisterGroupKind::xmm0] = registers.GetRegisterGroup(RegisterGroupKind::xmm0);
    globalRegisterMap[RegisterGroupKind::xmm1] = registers.GetRegisterGroup(RegisterGroupKind::xmm1);
    globalRegisterMap[RegisterGroupKind::xmm2] = registers.GetRegisterGroup(RegisterGroupKind::xmm2);
    globalRegisterMap[RegisterGroupKind::xmm3] = registers.GetRegisterGroup(RegisterGroupKind::xmm3);
    globalRegisterMap[RegisterGroupKind::xmm4] = registers.GetRegisterGroup(RegisterGroupKind::xmm4);
    globalRegisterMap[RegisterGroupKind::xmm5] = registers.GetRegisterGroup(RegisterGroupKind::xmm5);
}

void RegisterPool::AddLocalRegisterGroup(RegisterGroup* regGroup)
{
    localRegisterPool.insert(regGroup);
}

void RegisterPool::AddLocalXMMRegisterGroup(RegisterGroup* regGroup)
{
    localXMMRegisterPool.insert(regGroup);
}

std::expected<RegisterGroup*, int> RegisterPool::GetLocalRegisterGroup()
{
    if (localRegisterPool.empty())
    {
        return std::unexpected<int>(util::AllocateError("local register pool is empty"));
    }
    RegisterGroup* regGroup = *localRegisterPool.begin();
    localRegisterPool.erase(regGroup);
    usedLocalRegs.insert(regGroup);
    return std::expected<RegisterGroup*, int>(regGroup);
}

std::expected<RegisterGroup*, int> RegisterPool::GetLocalXMMRegisterGroup()
{
    if (localXMMRegisterPool.empty())
    {
        return std::unexpected<int>(util::AllocateError("local XMM register pool is empty"));
    }
    RegisterGroup* regGroup = *localXMMRegisterPool.begin();
    localXMMRegisterPool.erase(regGroup);
    usedLocalXMMRegs.insert(regGroup);
    return std::expected<RegisterGroup*, int>(regGroup);
}

RegisterGroup* RegisterPool::GetRegisterGroup(RegisterGroupKind regGroupKind, bool used)
{
    RegisterGroup* regGroup = registers.GetRegisterGroup(regGroupKind);
    if (used && !regGroup->IsLocal() && regGroup->IsNonvolatile())
    {
        usedNonvolatileRegs.insert(regGroup);
    }
    return regGroup;
}

bool RegisterGroupLess::operator()(RegisterGroup* left, RegisterGroup* right) const
{
    return int(left->Kind()) < int(right->Kind());
}

} // namespace otava::assembly
