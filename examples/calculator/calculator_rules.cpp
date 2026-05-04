module calculator.spg.rules;

namespace calculator::spg::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 7571050353752276993, "CalculatorParser.expression" },
        { 7571050353752276994, "CalculatorParser.assignment" },
        { 7571050353752276995, "CalculatorParser.term" },
        { 7571050353752276996, "CalculatorParser.weak_operator" },
        { 7571050353752276997, "CalculatorParser.factor" },
        { 7571050353752276998, "CalculatorParser.strong_operator" },
        { 7571050353752276999, "CalculatorParser.unary" },
        { 7571050353752277000, "CalculatorParser.primary" }
    };
    return &ruleNameMap;
}

} // calculator::spg::rules
