module otava.solution_spg.rules;

namespace otava::solution_spg::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 1917470441149038593, "SolutionParser.SolutionFile" },
        { 1917470441149038594, "SolutionParser.SolutionDeclaration" },
        { 1917470441149038595, "SolutionParser.FilePath" },
        { 1917470441149038596, "SolutionParser.ProjectFilePath" },
        { 1917470441149038597, "SolutionParser.QualifiedId" }
    };
    return &ruleNameMap;
}

} // otava::solution_spg::rules
