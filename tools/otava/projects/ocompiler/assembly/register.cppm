// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.assembly.reg;

import std;
import otava.assembly.value;

export namespace otava::assembly {

enum class RegisterKind
{
    al, bl, cl, dl, sil, dil, bpl, spl, r8b, r9b, r10b, r11b, r12b, r13b, r14b, r15b,
    ax, bx, cx, dx, si, di, bp, sp, r8w, r9w, r10w, r11w, r12w, r13w, r14w, r15w,
    eax, ebx, ecx, edx, esi, edi, ebp, esp, r8d, r9d, r10d, r11d, r12d, r13d, r14d, r15d,
    rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8, r9, r10, r11, r12, r13, r14, r15,
    ah, bh, ch, dh,
    xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15,
    max
};

enum class RegisterGroupKind
{
    rax, rbx, rcx, rdx, rsi, rdi, rbp, rsp, r8, r9, r10, r11, r12, r13, r14, r15,
    xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15,
    max
};

class Register : public Value
{
public:
    Register();
    Register(RegisterKind kind_, RegisterGroupKind group_, int size_);
    inline RegisterKind RegKind() const { return kind; }
    inline RegisterGroupKind Group() const { return group; }
    inline int Size() const { return size; }
    inline bool IsFloatingPointReg() const { return group >= RegisterGroupKind::xmm0 && group <= RegisterGroupKind::xmm15; }
private:
    RegisterKind kind;
    RegisterGroupKind group;
    int size;
};

const int highByteRegSize = 9;

class RegisterGroup
{
public:
    RegisterGroup();
    RegisterGroup(RegisterGroupKind kind_);
    inline RegisterGroupKind Kind() const { return kind; }
    std::expected<const Register*, int> GetReg(std::int64_t size) const;
    std::expected<Register*, int> GetReg(std::int64_t size);
    std::expected<bool, int> SetReg(std::int64_t size, const Register& reg);
    bool IsLocal() const;
    inline bool IsFloatingPointReg() const { return kind >= RegisterGroupKind::xmm0 && kind <= RegisterGroupKind::xmm15; }
    inline bool IsVolatile() const { return !nonvolatile; }
    inline bool IsNonvolatile() const { return nonvolatile; }
    inline void SetNonvolatile(bool nonvolatile_) { nonvolatile = nonvolatile_; }
private:
    RegisterGroupKind kind;
    std::vector<Register> regs;
    bool nonvolatile;
};

class Registers
{
public:
    Registers();
    inline const RegisterGroup* GetRegisterGroup(RegisterGroupKind kind) const { return regGroups[int(kind)].get(); }
    inline RegisterGroup* GetRegisterGroup(RegisterGroupKind kind) { return regGroups[int(kind)].get(); }
    inline explicit operator bool() const { return Valid(); }
    inline bool Valid() const { return error == 0; }
    inline int Error() const { return error; }
private:
    std::vector<std::unique_ptr<RegisterGroup>> regGroups;
    int error;
};

struct RegisterGroupLess
{
    bool operator()(RegisterGroup* left, RegisterGroup* right) const;
};

class RegisterPool
{
public:
    RegisterPool(Registers& registers_);
    void AddLocalRegisterGroup(RegisterGroup* regGroup);
    void AddLocalXMMRegisterGroup(RegisterGroup* regGroup);
    std::expected<RegisterGroup*, int> GetLocalRegisterGroup();
    std::expected<RegisterGroup*, int> GetLocalXMMRegisterGroup();
    RegisterGroup* GetRegisterGroup(RegisterGroupKind regGroupKind, bool used);
    inline int LocalRegisterCount() const { return localRegisterCount; }
    inline int LocalXMMRegisterCount() const { return localXMMRegisterCount; }
    inline int NumFreeLocalRegisters() const { return localRegisterPool.size(); }
    inline int NumFreeLocalXMMRegisters() const { return localXMMRegisterPool.size(); }
    inline const std::set<RegisterGroup*, RegisterGroupLess>& UsedLocalRegs() const { return usedLocalRegs; }
    inline const std::set<RegisterGroup*, RegisterGroupLess>& UsedNonvolatileRegs() const { return usedNonvolatileRegs; }
    inline const std::set<RegisterGroup*, RegisterGroupLess>& UsedLocalXMMRegs() const { return usedLocalXMMRegs; }
    inline const std::set<RegisterGroup*, RegisterGroupLess>& UsedNonvolatileXMMRegs() const { return usedNonvolatileXMMRegs; }
private:
    Registers& registers;
    int localRegisterCount;
    int localXMMRegisterCount;
    std::set<RegisterGroup*, RegisterGroupLess> localRegisterPool;
    std::set<RegisterGroup*, RegisterGroupLess> localXMMRegisterPool;
    std::map<RegisterGroupKind, RegisterGroup*> globalRegisterMap;
    std::set<RegisterGroup*, RegisterGroupLess> usedLocalRegs;
    std::set<RegisterGroup*, RegisterGroupLess> usedNonvolatileRegs;
    std::set<RegisterGroup*, RegisterGroupLess> usedLocalXMMRegs;
    std::set<RegisterGroup*, RegisterGroupLess> usedNonvolatileXMMRegs;
};

} // namespace otava::assembly
