// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.register_allocator;

import util.align;
import otava.intermediate.context;

namespace otava::intermediate {

ArgLocation::ArgLocation(int index_, int64_t offset_, int64_t size_) : index(index_), offset(offset_), size(size_)
{
}

CallFrame::CallFrame() : top(48)
{
}

void CallFrame::AllocateArgLocation(int64_t size)
{
    if (argLocations.empty())
    {
        ArgLocation argLocation(0, top, 8);
        argLocations.push_back(argLocation);
    }
    else
    {
        const ArgLocation& last = argLocations.back();
        ArgLocation argLocation(argLocations.size(), last.offset + last.size, 8);
        argLocations.push_back(argLocation);
    }
}

ArgLocation CallFrame::GetArgLocation(int index)
{
    return argLocations[index];
}

Frame::Frame() : top(8)
{
}

FrameLocation Frame::GetFrameLocation(int64_t size)
{
    if (frameLocations.empty())
    {
        FrameLocation frameLocation(0, top, size);
        frameLocations.push_back(frameLocation);
        return frameLocation;
    }
    else
    {
        const FrameLocation& last = frameLocations.back();
        FrameLocation frameLocation(frameLocations.size(), last.offset + last.size, size);
        frameLocations.push_back(frameLocation);
        return frameLocation;
    }
}

int64_t Frame::Size() const
{
    if (frameLocations.empty())
    {
        return 32ll;
    }
    else
    {
        const FrameLocation& last = frameLocations.back();
        return 32ll + last.offset + last.size;
    }
}

RegisterAllocator::~RegisterAllocator()
{
}

SpillData::SpillData() : registerGroupToSpill(), spillToFrameLocation()
{
}

} // otava::intermediate
