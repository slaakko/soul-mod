// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build.project_file;

import std.core;

export namespace otava::build {

enum class ProjectTarget
{
    program, library
};

class Project;

void MakeProjectFile(Project* project, const std::string& projectFilePath, const std::vector<std::string> asmFiles, const std::vector<std::string>& cppFiles,
    const std::vector<std::string>& resourceFiles,
    const std::string& libraryDirs, const std::vector<std::unique_ptr<Project>>& referencedProjects, const std::string& config, const std::string& classIndexFilePath,
    ProjectTarget target, bool verbose);

} // namespace otava::build
