// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.intermediate.location;

import util;

namespace otava::intermediate {

void FrameLocation::Dump()
{
    std::cout << "index=" << index << ", offset=" << offset << ", size=" << size << "\n";
}

Frame::Frame() : calleeParamAreaSize(32), numUsedXMMRegs(0), rbxPushed(false)
{
}

FrameLocation Frame::GetParamLocation(std::int64_t size, otava::assembly::Context* assemblyContext)
{
    if (paramLocations.empty())
    {
        FrameLocation paramLocation(otava::assembly::RegisterGroupKind::rsp, 0, 8, 8);
        paramLocations.push_back(paramLocation);
        return paramLocation;
    }
    else if (paramLocations.size() < 4)
    {
        const FrameLocation& last = paramLocations.back();
        FrameLocation paramLocation(otava::assembly::RegisterGroupKind::rsp, paramLocations.size(), last.offset + last.size, 8);
        paramLocations.push_back(paramLocation);
        return paramLocation;
    }
    else
    {
        const FrameLocation& last = paramLocations.back();
        otava::assembly::Macro* macro = assemblyContext->MakeMacro("param" + std::to_string(paramLocations.size()) + "$");
        FrameLocation paramLocation(otava::assembly::RegisterGroupKind::rbp, paramLocations.size(), last.offset + last.size, size);
        paramLocation.macro = macro;
        paramLocations.push_back(paramLocation);
        return paramLocation;
    }
}

FrameLocation Frame::GetFrameLocation(std::int64_t size)
{
    if (frameLocations.empty())
    {
        FrameLocation frameLocation(otava::assembly::RegisterGroupKind::rbp, 0, 8, size);
        frameLocations.push_back(frameLocation);
        return frameLocation;
    }
    else
    {
        const FrameLocation& last = frameLocations.back();
        FrameLocation frameLocation(otava::assembly::RegisterGroupKind::rbp, frameLocations.size(), last.offset + last.size, size);
        frameLocations.push_back(frameLocation);
        return frameLocation;
    }
}

std::int64_t Frame::Size() const
{
    if (frameLocations.empty())
    {
        return 32 + numUsedXMMRegs * 16;
    }
    else
    {
        const FrameLocation& last = frameLocations.back();
        return util::Align(calleeParamAreaSize + last.offset + last.size + numUsedXMMRegs * 16, 16);
    }
}

void Frame::Dump()
{
    for (auto& frameLocation : frameLocations)
    {
        frameLocation.Dump();
    }
}

void Frame::SetMacroValues(otava::assembly::Context* assemblyContext)
{
    int retVal = 1;
    int pushRbp = 1;
    int numUsedLocalRegs = assemblyContext->GetRegisterPool()->UsedLocalRegs().size();
    int numUsedNonvolatileRegs = assemblyContext->GetRegisterPool()->UsedNonvolatileRegs().size();

    std::int64_t paramOffset = 8 * (retVal + pushRbp + numUsedLocalRegs + numUsedNonvolatileRegs);
    if (rbxPushed)
    {
        paramOffset += 8;
    }
    std::int64_t frameSize = Size();

    for (auto& paramLocation : paramLocations)
    {
        otava::assembly::Macro* macro = paramLocation.macro;
        if (macro)
        {
            std::int64_t value = (paramLocation.index - 4) * 8 + paramOffset + frameSize;
            value -= XMMSaveRegSize();
            value -= calleeParamAreaSize - 4 * 8;
            macro->SetValue(assemblyContext->MakeIntegerLiteral(value, 8));
        }
    }
}

CallFrame::CallFrame()
{
}

void CallFrame::AllocateArgLocation(std::int64_t size)
{
    if (argLocations.empty())
    {
        ArgLocation argLocation(0, 0, 8);
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

} // otava::intermediate
