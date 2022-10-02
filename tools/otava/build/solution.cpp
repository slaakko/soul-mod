// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build_solution;

import otava.build_project;
import otava.symbols.namespaces;
import otava.symbols.compound.type.symbol;

namespace otava::build {

Solution::Solution(const std::string& filePath_, const std::string& name_) : filePath(filePath_), name(name_)
{
}

void Solution::AddProjectFilePath(const std::string& projectFilePath)
{
    projectFilePaths.push_back(projectFilePath);
}

void Solution::AddProject(Project* project)
{
    projects.push_back(std::unique_ptr<Project>(project));
    projectMap[project->FilePath()] = project;
}

Project* Solution::GetProject(const std::string& projectFilePath) const
{
    auto it = projectMap.find(projectFilePath);
    if (it != projectMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

} // namespace otava::build
