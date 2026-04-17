module fruits.spg.rules;

namespace fruits::spg::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 1391209262306295809, "FruitParser.FruitList" },
        { 1391209262306295810, "FruitParser.Fruit" }
    };
    return &ruleNameMap;
}

} // fruits::spg::rules
