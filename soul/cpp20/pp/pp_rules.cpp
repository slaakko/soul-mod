module soul.cpp20.pp.parser.spg.rules;

namespace soul::cpp20::pp::parser::spg::rules {

std::mutex ruleMtx;

std::map<int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<int64_t, std::string> ruleNameMap = {
        { 8694736574321000449, "PPParser.PPLIne" },
        { 8694736574321000450, "PPParser.PPCommand" },
        { 8694736574321000451, "PPParser.IfCommand" },
        { 8694736574321000452, "PPParser.ElifCommand" },
        { 8694736574321000453, "PPParser.IfdefCommand" },
        { 8694736574321000454, "PPParser.IfndefCommand" },
        { 8694736574321000455, "PPParser.ElseCommand" },
        { 8694736574321000456, "PPParser.EndifCommand" },
        { 8694736574321000457, "PPParser.DefineCommand" },
        { 8694736574321000458, "PPParser.UndefCommand" },
        { 8694736574321000459, "PPParser.IncludeCommand" },
        { 8694736574321000460, "PPParser.Header" },
        { 8694736574321000461, "PPParser.Expression" },
        { 8694736574321000462, "PPParser.LogicalOrExpr" },
        { 8694736574321000463, "PPParser.LogicalAndExpr" },
        { 8694736574321000464, "PPParser.InclusiveOrExpression" },
        { 8694736574321000465, "PPParser.ExclusiveOrExpression" },
        { 8694736574321000466, "PPParser.AndExpression" },
        { 8694736574321000467, "PPParser.EqualityExpression" },
        { 8694736574321000468, "PPParser.RelationalExpression" },
        { 8694736574321000469, "PPParser.ShiftExpression" },
        { 8694736574321000470, "PPParser.AdditiveExpression" },
        { 8694736574321000471, "PPParser.MultiplicativeExpression" },
        { 8694736574321000472, "PPParser.UnaryExpression" },
        { 8694736574321000473, "PPParser.PrimaryExpr" },
        { 8694736574321000474, "PPParser.DefinedExpr" }
    };
    return &ruleNameMap;
}

} // soul::cpp20::pp::parser::spg::rules
