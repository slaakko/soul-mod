// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.project_file;

import std.core;

export namespace otava::build {

enum class ProjectTarget
{
    program, library
};

void MakeProjectFile(const std::string& projectFilePath, const std::string& projectName, const std::vector<std::string> asmFiles, const std::vector<std::string>& cppFiles,
    const std::string& libraryDirs, const std::string& classIndexFilePath, ProjectTarget target, bool verbose);

} // namespace otava::build
