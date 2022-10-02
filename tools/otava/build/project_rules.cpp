module otava.project_spg.rules;

namespace otava::project_spg::rules {

std::mutex ruleMtx;

std::map<int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<int64_t, std::string> ruleNameMap = {
        { 3083016289157906433, "ProjectParser.ProjectFile" },
        { 3083016289157906434, "ProjectParser.ProjectDeclaration" },
        { 3083016289157906435, "ProjectParser.Define" },
        { 3083016289157906436, "ProjectParser.FilePath" },
        { 3083016289157906437, "ProjectParser.InterfaceFilePath" },
        { 3083016289157906438, "ProjectParser.SourceFilePath" },
        { 3083016289157906439, "ProjectParser.ReferenceFilePath" },
        { 3083016289157906440, "ProjectParser.QualifiedId" }
    };
    return &ruleNameMap;
}

} // otava::project_spg::rules
