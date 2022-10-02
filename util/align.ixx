// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.align;

import std.core;

export namespace util {

inline uint64_t Align(uint64_t n, uint64_t alignment)
{
#pragma warning(disable : 4146)
    return (n + alignment - 1u) & -alignment;
#pragma warning(default : 4146)
}

} // namespace util