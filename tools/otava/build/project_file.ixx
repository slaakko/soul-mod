// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.project_file;

import std.core;

export namespace otava::build {

void MakeProjectFile(const std::string& projectFilePath, const std::string& projectName, const std::vector<std::string> asmFiles, const std::vector<std::string>& cppFiles);

} // namespace otava::build
