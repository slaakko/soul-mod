module string_parser.parser.rules;

namespace string_parser::parser::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 1367067835251032065, "str_parser.names" },
        { 1367067835251032066, "str_parser.name" }
    };
    return &ruleNameMap;
}

} // string_parser::parser::rules
