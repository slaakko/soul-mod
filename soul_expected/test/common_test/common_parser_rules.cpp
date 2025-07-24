module common_expected.parser.rules;

namespace common_expected::parser::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 4690153052290678785, "CommonParser.QualifiedId" },
        { 4690153052290678786, "CommonParser.ExportModule" },
        { 4690153052290678787, "CommonParser.Import" },
        { 4690153052290678788, "CommonParser.ImportPrefix" },
        { 4690153052290678789, "CommonParser.ExprString" },
        { 4690153052290678790, "CommonParser.FilePath" },
        { 4690153052290678791, "CommonParser.ExportKeyword" },
        { 4690153052290678792, "CommonParser.ModuleKeyword" },
        { 4690153052290678793, "CommonParser.ImportKeyword" },
        { 4690153052290678794, "CommonParser.ImplementationPrefix" },
        { 4690153052290678795, "CommonParser.InterfacePrefix" },
        { 4690153052290678796, "CommonParser.ImplementationKeyword" },
        { 4690153052290678797, "CommonParser.InterfaceKeyword" },
        { 4690153052290678798, "CommonParser.ParserKeyword" },
        { 4690153052290678799, "CommonParser.LexerKeyword" }
    };
    return &ruleNameMap;
}

} // common_expected::parser::rules
