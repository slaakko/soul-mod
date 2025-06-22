// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.align;

import std.core;

export namespace util {

inline std::uint64_t Align(std::uint64_t n, std::uint64_t alignment)
{
    return (n + alignment - 1u) & -alignment;
}

} // namespace util