module soul.cpp20.sln.spg.rules;

namespace soul::cpp20::sln::spg::rules {

std::mutex ruleMtx;

std::map<int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<int64_t, std::string> ruleNameMap = {
        { 2364037509677056001, "SolutionParser.SolutionFile" },
        { 2364037509677056002, "SolutionParser.SolutionDeclaration" },
        { 2364037509677056003, "SolutionParser.FilePath" },
        { 2364037509677056004, "SolutionParser.ProjectFilePath" },
        { 2364037509677056005, "SolutionParser.QualifiedId" }
    };
    return &ruleNameMap;
}

} // soul::cpp20::sln::spg::rules
