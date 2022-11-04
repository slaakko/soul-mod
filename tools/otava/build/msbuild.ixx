// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.msbuild;

import std.core;

export namespace otava::build {

void MSBuild(const std::string& projectFilePath, const std::string& config);

} // namespace otava::build
