// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.register_allocator;

import std.core;
import otava.assembly.literal;
import otava.assembly.reg;

export namespace otava::intermediate {

class Instruction;
class Context;

enum class Locations : int
{
    none = 0, reg = 1 << 0, frame = 1 << 1
};
    
constexpr Locations operator|(Locations left, Locations right)
{
    return Locations(int(left) | int(right));
}

constexpr Locations operator&(Locations left, Locations right)
{
    return Locations(int(left) & int(right));
}

constexpr Locations operator~(Locations locs)
{
    return Locations(~int(locs));
}

struct FrameLocation
{
    FrameLocation() : index(-1), offset(0), size(0) {}
    FrameLocation(int index_, int64_t offset_, int64_t size_) : index(index_), offset(offset_), size(size_) {}
    bool Valid() const { return index != -1; }
    int64_t ItemOffset() const { return offset + size; }
    int index;
    int64_t offset;
    int64_t size;
};

struct ArgLocation
{
    ArgLocation(int index_, int64_t offset_, int64_t size_);
    int64_t ItemOffset() const { return offset + size; }
    int index;
    int64_t offset;
    int64_t size;
};

class CallFrame
{
public:
    CallFrame();
    void AllocateArgLocation(int64_t size);
    ArgLocation GetArgLocation(int index);
    std::vector<ArgLocation> argLocations;
private:
    int64_t top;
};

class Frame
{
public:
    Frame();
    FrameLocation GetFrameLocation(int64_t size);
    int64_t Size() const;
private:
    int64_t top;
    std::vector<FrameLocation> frameLocations;
};

struct SpillData
{
    SpillData();
    otava::assembly::RegisterGroup* registerGroupToSpill;
    FrameLocation spillToFrameLocation;
};

enum class RegisterAllocationAction
{
    none, spill, registerAllocated
};

class RegisterAllocator
{
public:
    virtual ~RegisterAllocator();
    virtual RegisterAllocationAction Run(Instruction* inst) = 0;
    virtual const std::vector<SpillData>& GetSpillData() const = 0;
    virtual Locations GetLocations(Instruction* inst) const = 0;
    virtual otava::assembly::RegisterGroup* GetRegisterGroup(Instruction* inst) const = 0;
    virtual void AddRegisterLocation(Instruction* inst, otava::assembly::RegisterGroup* regGroup) = 0;
    virtual Frame& GetFrame() = 0;
    virtual FrameLocation GetFrameLocation(Instruction* inst) const = 0;
    virtual int LastActiveLocalRegGroup() const = 0;
};

} // otava::intermediate
