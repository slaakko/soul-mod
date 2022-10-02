module otava.command.spg.rules;

namespace otava::command::spg::rules {

std::mutex ruleMtx;

std::map<int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<int64_t, std::string> ruleNameMap = {
        { 5465240348223602689, "CommandParser.Command" },
        { 5465240348223602690, "CommandParser.BuildCommand" },
        { 5465240348223602691, "CommandParser.DumpCommand" },
        { 5465240348223602692, "CommandParser.AssembleCommand" },
        { 5465240348223602693, "CommandParser.IntermediateCompileCommand" },
        { 5465240348223602694, "CommandParser.FilePath" }
    };
    return &ruleNameMap;
}

} // otava::command::spg::rules
