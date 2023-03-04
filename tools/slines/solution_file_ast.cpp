module solution_file.ast;

import solution_file.lexer;
import solution_file.parser;
import util.file.stream;
import util.unicode;
import util.path;

namespace solution_file::ast {

std::string ParseString(const std::u32string& str)
{
    return util::ToUtf8(str.substr(1, str.length() - 2));
}

Solution::Solution(const std::string& filePath_) : root(util::GetFullPath(util::Path::GetDirectoryName(filePath_))), filePath(filePath_)
{
}

void Solution::AddProject(project_file::ast::Project* project)
{
    projects.push_back(std::unique_ptr<project_file::ast::Project>(project));
}

void Solution::ProcessProjects()
{
    for (const auto& project : projects)
    {
        if (project->IsCppProject())
        {
            ProcessProject(project.get());
        }
        counters += project->GetCounters();
    }
}

std::unique_ptr<Solution> ParseSolutionFile(const std::string& filePath)
{
    std::u32string content = util::ToUtf32(util::ReadFile(filePath));
    auto lexer = solution_file::lexer::MakeLexer(content.c_str(), content.c_str() + content.length(), filePath);
    std::unique_ptr<solution_file::ast::Solution> solution = solution_file::parser::solution_file_parser<decltype(lexer)>::Parse(lexer);
    return solution;
}

void ProcessSolution(Solution* solution)
{
    solution->ProcessProjects();
    PrintResults(solution->GetCounters());
}

} // namespace solution_file::ast
