// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.msbuild;

import std;

export namespace otava::build {

std::expected<bool, int> MSBuild(const std::string& projectFilePath, const std::string& config);

} // namespace otava::build
