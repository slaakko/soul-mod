module re_expected.rules;

namespace re_expected::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 2270120791255285761, "RegExParser.RegularExpression" },
        { 2270120791255285762, "RegExParser.Alternative" },
        { 2270120791255285763, "RegExParser.Catenation" },
        { 2270120791255285764, "RegExParser.Repetition" },
        { 2270120791255285765, "RegExParser.Primary" },
        { 2270120791255285766, "RegExParser.Class" },
        { 2270120791255285767, "RegExParser.Range" },
        { 2270120791255285768, "RegExParser.Char" },
        { 2270120791255285769, "RegExParser.ExpressionReference" }
    };
    return &ruleNameMap;
}

} // re_expected::rules
