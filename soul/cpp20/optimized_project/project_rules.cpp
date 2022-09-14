module soul.cpp20.proj.spg.rules;

namespace soul::cpp20::proj::spg::rules {

std::mutex ruleMtx;

std::map<int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<int64_t, std::string> ruleNameMap = {
        { 7646038738983714817, "ProjectParser.ProjectFile" },
        { 7646038738983714818, "ProjectParser.ProjectDeclaration" },
        { 7646038738983714819, "ProjectParser.Define" },
        { 7646038738983714820, "ProjectParser.FilePath" },
        { 7646038738983714821, "ProjectParser.InterfaceFilePath" },
        { 7646038738983714822, "ProjectParser.SourceFilePath" },
        { 7646038738983714823, "ProjectParser.ReferenceFilePath" },
        { 7646038738983714824, "ProjectParser.QualifiedId" }
    };
    return &ruleNameMap;
}

} // soul::cpp20::proj::spg::rules
