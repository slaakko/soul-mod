// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.project.build;

import std.core;

export namespace soul::cpp20::project::build {

enum class BuildFlags : int32_t
{
    none = 0, multithreadedBuild = 1 << 0
};

constexpr BuildFlags operator|(BuildFlags left, BuildFlags right)
{
    return BuildFlags(int32_t(left) | int32_t(right));
}

constexpr BuildFlags operator&(BuildFlags left, BuildFlags right)
{
    return BuildFlags(int32_t(left) & int32_t(right));
}

constexpr BuildFlags operator~(BuildFlags flags)
{
    return BuildFlags(~int32_t(flags));
}

void Build(const std::string& projectFilePath, BuildFlags flags);

} // namespace soul::cpp20::project::build
