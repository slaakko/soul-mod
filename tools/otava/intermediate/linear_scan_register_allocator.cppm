// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.linear_scan_register_allocator;

import std;
import otava.intermediate.register_allocator;

export namespace otava::intermediate {

class Context;
class Function;
class Instruction;

struct LiveRange
{
    inline LiveRange() : start(-1), end(-1) {}
    inline LiveRange(int start_, int end_) : start(start_), end(end_) {}
    inline bool Valid() const { return start != -1 && end != -1; }
    int start;
    int end;
};

inline bool operator<(const LiveRange& left, const LiveRange& right)
{
    if (left.start < right.start) return true;
    if (left.start > right.start) return false;
    return left.end < right.end;
}

struct LiveRangeByStart
{
    inline bool operator()(const LiveRange& left, const LiveRange& right) const
    {
        if (left.start < right.start) return true;
        if (left.start > right.start) return false;
        return left.end < right.end;
    }
};

struct LiveRangeByEnd
{
    inline bool operator()(const LiveRange& left, const LiveRange& right) const
    {
        if (left.end < right.end) return true;
        if (left.end > right.end) return false;
        return left.start < right.start;
    }
};

LiveRange GetLiveRange(Instruction* inst);

class LinearScanRegisterAllocator : public RegisterAllocator
{
public:
    LinearScanRegisterAllocator(Function& function, Context* context_);
    void AddLiveRange(const LiveRange& liveRange, Instruction* inst);
    void AddFreeRegGroupToPool(Instruction* inst);
    void RemoveFromActive(const LiveRange& range, bool integer);
    bool NoFreeRegs(bool floatingPoint) const;
    inline const std::set<LiveRange, LiveRangeByStart>& LiveRanges() const { return liveRanges; }
    inline const std::set<LiveRange, LiveRangeByEnd>& ActiveInteger() const { return activeInteger; }
    inline const std::set<LiveRange, LiveRangeByEnd>& ActiveFP() const { return activeFP; }
    FrameLocation GetFrameLocation(Instruction* inst) const override;
    otava::assembly::RegisterGroup* GetRegisterGroup(Instruction* inst) const override;
    void RemoveRegisterGroup(Instruction* inst);
    void AllocateRegister(Instruction* inst);
    void AllocateFrameLocation(Instruction* inst, bool spill);
    void Spill(Instruction* inst);
    LiveRange GetLiveRange(Instruction* inst) const;
    Frame& GetFrame() override { return frame; }
    const std::vector<Instruction*>& GetInstructions(const LiveRange& range) const;
    RegisterAllocationAction Run(Instruction* inst) override;
    Locations GetLocations(Instruction* inst) const override;
    void AddRegisterLocation(Instruction* inst, otava::assembly::RegisterGroup* regGroup) override;
    int LastActiveLocalRegGroup() const override;
    const std::vector<SpillData>& GetSpillData() const override;
    void RemoveFromRegisterGroups(Instruction* inst) override;
private:
    void ComputeLiveRanges(Function& function);
    void ExpireOldRanges(const LiveRange& range);
    Frame frame;
    std::set<LiveRange, LiveRangeByStart> liveRanges;
    std::set<LiveRange, LiveRangeByEnd> activeInteger;
    std::set<LiveRange, LiveRangeByEnd> activeFP;
    std::map<Instruction*, FrameLocation> frameLocations;
    std::map<Instruction*, otava::assembly::RegisterGroup*> registerGroups;
    std::map<Instruction*, LiveRange> instructionRangeMap;
    std::map<LiveRange, std::vector<Instruction*>> rangeInstructionMap;
    std::map<Instruction*, Locations> locations;
    std::vector<SpillData> spillDataVec;
    Context* context;
};

std::unique_ptr<LinearScanRegisterAllocator> CreateLinearScanRegisterAllocator(Function& function, Context* context);

} // otava::intermediate
