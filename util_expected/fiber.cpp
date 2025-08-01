// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module;

#ifdef _WIN32
#include <Windows.h>
#endif

module util_expected.fiber;

namespace util {

#ifdef _WIN32

void* ConvertThreadToFiber(void* param)
{
    return ::ConvertThreadToFiber(param);
}

void* CreateFiber(std::uint64_t stackSize, void* startAddress, void* param)
{
    return ::CreateFiber(stackSize, (LPFIBER_START_ROUTINE)startAddress, param);
}

void SwitchToFiber(void* fiber)
{
    ::SwitchToFiber(fiber);
}

void* GetFiberData()
{
    return ::GetFiberData();
}

void DeleteFiber(void* fiber)
{
    ::DeleteFiber(fiber);
}

#endif

} // namespace util
