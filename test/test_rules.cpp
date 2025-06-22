module test.rules;

namespace test::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 5305326204553789441, "TestParser.ClassKey" }
    };
    return &ruleNameMap;
}

} // test::rules
