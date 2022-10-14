// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.reg;

import std.core;
import otava.assembly.value;

export namespace otava::assembly {

enum class RegisterKind
{
    al, bl, cl, dl, sil, dil, bpl, spl, r8b, r9b, r10b, r11b, r12b, r13b, r14b, r15b,
    ax, bx, cx, dx, si, di, bp, sp, r8w, r9w, r10w, r11w, r12w, r13w, r14w, r15w,
    eax, ebx, ecx, edx, esi, edi, ebp, esp, r8d, r9d, r10d, r11d, r12d, r13d, r14d, r15d,
    rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8, r9, r10, r11, r12, r13, r14, r15, max
};

class Register : public Value
{
public:
    Register();
    Register(RegisterKind kind_);
    RegisterKind Kind() const { return kind; }
private:
    RegisterKind kind;
};

enum class RegisterGroupKind
{
    rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8, r9, r10, r11, r12, r13, r14, r15, max
};

class RegisterGroup
{
public:
    RegisterGroup();
    RegisterGroup(RegisterGroupKind kind_);
    RegisterGroupKind Kind() const { return kind; }
    const Register* GetReg(int size) const;
    Register* GetReg(int size);
    void SetReg(int size, const Register& reg);
private:
    RegisterGroupKind kind;
    Register regs[8];
};

class Registers
{
public:    
    Registers();
    const RegisterGroup* GetRegisterGroup(RegisterGroupKind kind) const { return &regGroups[int(kind)]; }
    RegisterGroup* GetRegisterGroup(RegisterGroupKind kind) { return &regGroups[int(kind)]; }
private:
    RegisterGroup regGroups[int(RegisterGroupKind::max)];
};

struct RegisterGroupLess
{
    bool operator()(RegisterGroup* left, RegisterGroup* right) const;
};

class RegisterPool
{
public:
    RegisterPool(Registers& registers);
    void AddLocalRegisterGroup(RegisterGroup* regGroup);
    RegisterGroup* GetLocalRegisterGroup();
    RegisterGroup* GetGlobalRegisterGroup(RegisterGroupKind regGroupKind);
    int LocalRegisterCount() const { return localRegisterCount; }
    int NumFreeLocalRegisters() const { return localRegisterPool.size(); }
private:
    int localRegisterCount;
    std::set<RegisterGroup*, RegisterGroupLess> localRegisterPool;
    std::map<RegisterGroupKind, RegisterGroup*> globalRegisterMap;
};

} // namespace otava::assembly
