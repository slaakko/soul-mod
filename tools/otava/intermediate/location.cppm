// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.location;

import otava.assembly;
import soul.ast.span;
import std;

export namespace otava::intermediate {

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
    FrameLocation() : reg(otava::assembly::RegisterGroupKind::rbp), index(-1), offset(0), size(0), macro(nullptr), level(-1) {}
    FrameLocation(otava::assembly::RegisterGroupKind reg_, int index_, std::int64_t offset_, std::int64_t size_) : 
        reg(reg_), index(index_), offset(offset_), size(size_), macro(nullptr), level(-1) {}
    void Dump();
    inline bool Valid() const { return index != -1; }
    inline bool IsParentFrameLocation() const { return level >= 0; }
    otava::assembly::RegisterGroupKind reg;
    int index;
    std::int64_t offset;
    std::int64_t size;
    otava::assembly::Macro* macro;
    int level;
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
    FrameLocation AllocateParamLocation(std::int64_t size, otava::assembly::Context* assemblyContext);
    FrameLocation AllocateFrameLocation(std::int64_t size);
    FrameLocation GetFrameLocation(int index, const soul::ast::Span& span, Context* context) const;
    FrameLocation GetParentFrameLocation(const soul::ast::Span& span, Context* context) const;
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
    inline bool IsPFrame() const { return isPFrame; }
    inline void SetPFrame() { isPFrame = true; }
private:
    std::vector<FrameLocation> paramLocations;
    std::vector<FrameLocation> frameLocations;
    std::int64_t calleeParamAreaSize;
    int numUsedXMMRegs;
    bool rbxPushed;
    bool isPFrame;
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
