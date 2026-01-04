// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.register_allocator;

import otava.intermediate.location;
import otava.assembly;
import std;

export namespace otava::intermediate {

class Instruction;

struct SpillData
{
    SpillData();
    otava::assembly::RegisterGroup* registerGroupToSpill;
    FrameLocation spillToFrameLocation;
    Instruction* instToSpill;
};

enum class RegisterAllocationAction
{
    none, spill, registerAllocated
};

class RegisterAllocator
{
public:
    RegisterAllocator();
    virtual ~RegisterAllocator();
    virtual std::expected<RegisterAllocationAction, int> Run(Instruction* inst) = 0;
    virtual const std::vector<SpillData>& GetSpillData() const = 0;
    virtual Locations GetLocations(Instruction* inst) const = 0;
    virtual otava::assembly::RegisterGroup* GetRegisterGroup(Instruction* inst) const = 0;
    virtual void AddRegisterLocation(Instruction* inst, otava::assembly::RegisterGroup* regGroup) = 0;
    virtual Frame& GetFrame() = 0;
    virtual FrameLocation GetFrameLocation(Instruction* inst) const = 0;
    virtual int LastActiveLocalRegGroup() const = 0;
    virtual void RemoveFromRegisterGroups(Instruction* inst) = 0;
};

} // otava::intermediate
