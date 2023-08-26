export module solution_file.ast;

import std.core;
import project_file.ast;
import counters;

export namespace solution_file::ast {

std::string ParseString(const std::u32string& str);

class Solution
{
public:
    Solution(const std::string& filePath_);
    const std::string& Root() const { return root; }
    const std::vector<std::unique_ptr<project_file::ast::Project>>& Projects() const { return projects; }
    void AddProject(project_file::ast::Project* project);
    void ProcessProjects();
    const Counters& GetCounters() const { return counters; }
private:
    std::string root;
    std::string filePath;
    std::vector<std::unique_ptr<project_file::ast::Project>> projects;
    Counters counters;
};

std::unique_ptr<Solution> ParseSolutionFile(const std::string& filePath);
void ProcessSolution(Solution* solution);

} // namespace solution_file::ast
