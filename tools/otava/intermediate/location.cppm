// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.location;

import otava.assembly;
import std;

export namespace otava::intermediate {

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
    FrameLocation() : reg(otava::assembly::RegisterGroupKind::rbp), index(-1), offset(0), size(0), macro(nullptr) {}
    FrameLocation(otava::assembly::RegisterGroupKind reg_, int index_, std::int64_t offset_, std::int64_t size_) : 
        reg(reg_), index(index_), offset(offset_), size(size_), macro(nullptr) {}
    void Dump();
    inline bool Valid() const { return index != -1; }
    otava::assembly::RegisterGroupKind reg;
    int index;
    std::int64_t offset;
    std::int64_t size;
    otava::assembly::Macro* macro;
};

struct ArgLocation
{
    ArgLocation(int index_, std::int64_t offset_, std::int64_t size_) : reg(otava::assembly::RegisterGroupKind::rsp), index(index_), offset(offset_), size(size_) {}
    otava::assembly::RegisterGroupKind reg;
    int index;
    std::int64_t offset;
    std::int64_t size;
};

class Frame
{
public:
    Frame();
    FrameLocation GetParamLocation(std::int64_t size, otava::assembly::Context* assemblyContext);
    FrameLocation GetFrameLocation(std::int64_t size);
    inline void SetRbxPushed() { rbxPushed = true; }
    inline bool RbxPushed() const { return rbxPushed; }
    std::int64_t Size() const;
    inline std::int64_t CalleeParamAreaSize() const { return calleeParamAreaSize; }
    inline std::int64_t XMMSaveRegSize() const { return 16 * numUsedXMMRegs; }
    inline void SetCalleeParamAreaSize(std::int64_t calleeParamAreaSize_) { calleeParamAreaSize = calleeParamAreaSize_; }
    void SetMacroValues(otava::assembly::Context* assemblyContext);
    inline void SetNumUsedXMMRegs(int numUsedXMMRegs_) { numUsedXMMRegs = numUsedXMMRegs_; }
    inline int GetNumUsedXMMRegs() const { return numUsedXMMRegs; }
    void Dump();
private:
    std::vector<FrameLocation> paramLocations;
    std::vector<FrameLocation> frameLocations;
    std::int64_t calleeParamAreaSize;
    int numUsedXMMRegs;
    bool rbxPushed;
};

class CallFrame
{
public:
    CallFrame();
    void AllocateArgLocation(std::int64_t size);
    ArgLocation GetArgLocation(int index);
private:
    std::vector<ArgLocation> argLocations;
};

} // otava::intermediate
