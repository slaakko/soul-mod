// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.build_solution;

import std;

export namespace otava::build_solution {}

export namespace otava::build {

class Project;

class Solution
{
public:
    Solution(const std::string& filePath_, const std::string& name_);
    inline const std::string& FilePath() const { return filePath; }
    inline const std::string& Name() const { return name; }
    void AddProjectFilePath(const std::string& projectFilePath);
    inline const std::vector<std::string>& ProjectFilePaths() const { return projectFilePaths; }
    void AddProject(Project* project);
    void AddProject(Project* project, bool own);
    inline const std::vector<Project*>& Projects() const { return projects; }
    Project* GetProject(const std::string& projectFilePath) const;
    bool IsProjectSolution() const { return projectSolution; }
    void SetProjectSolution() { projectSolution = true; }
private:
    std::string filePath;
    std::string name;
    std::vector<std::string> projectFilePaths;
    std::vector<std::unique_ptr<Project>> ownedProjects;
    std::vector<Project*> projects;
    std::map<std::string, Project*> projectMap;
    bool projectSolution;
};

} // namespace otava::build_solution
