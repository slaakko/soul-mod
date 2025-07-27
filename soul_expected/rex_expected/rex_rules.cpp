module soul_expected.rex.spg.rules;

namespace soul_expected::rex::spg::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 1058390567207043073, "RexParser.RegularExpression" },
        { 1058390567207043074, "RexParser.Alternative" },
        { 1058390567207043075, "RexParser.Catenation" },
        { 1058390567207043076, "RexParser.Repetition" },
        { 1058390567207043077, "RexParser.Primary" },
        { 1058390567207043078, "RexParser.Class" },
        { 1058390567207043079, "RexParser.Range" },
        { 1058390567207043080, "RexParser.Char" }
    };
    return &ruleNameMap;
}

} // soul_expected::rex::spg::rules
