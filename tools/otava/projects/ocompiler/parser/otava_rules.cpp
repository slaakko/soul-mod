module otava.parser.rules;

namespace otava::parser::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 1955786072029921281, "PunctuationParser.Semicolon" },
        { 1955786072029921282, "PunctuationParser.Comma" },
        { 1955786072029921283, "PunctuationParser.Quest" },
        { 1955786072029921284, "PunctuationParser.Colon" },
        { 1955786072029921285, "PunctuationParser.ColonColon" },
        { 1955786072029921286, "PunctuationParser.Ellipsis" },
        { 1955786072029921287, "PunctuationParser.LParen" },
        { 1955786072029921288, "PunctuationParser.RParen" },
        { 1955786072029921289, "PunctuationParser.LBracket" },
        { 1955786072029921290, "PunctuationParser.RBracket" },
        { 1955786072029921291, "PunctuationParser.LBrace" },
        { 1955786072029921292, "PunctuationParser.RBrace" },
        { 1955786072029921293, "PunctuationParser.Assign" }
    };
    return &ruleNameMap;
}

} // otava::parser::rules
