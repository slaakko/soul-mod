module soul_expected.xml.xpath.parser.rules;

namespace soul_expected::xml::xpath::parser::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 8096769971578732545, "XPathParser.Expr" },
        { 8096769971578732546, "XPathParser.OrExpr" },
        { 8096769971578732547, "XPathParser.AndExpr" },
        { 8096769971578732548, "XPathParser.EqualityExpr" },
        { 8096769971578732549, "XPathParser.RelationalExpr" },
        { 8096769971578732550, "XPathParser.AdditiveExpr" },
        { 8096769971578732551, "XPathParser.MultiplicativeExpr" },
        { 8096769971578732552, "XPathParser.UnaryExpr" },
        { 8096769971578732553, "XPathParser.UnionExpr" },
        { 8096769971578732554, "XPathParser.PathExpr" },
        { 8096769971578732555, "XPathParser.LocationPath" },
        { 8096769971578732556, "XPathParser.AbsoluteLocationPath" },
        { 8096769971578732557, "XPathParser.AbbreviatedAbsoluteLocationPath" },
        { 8096769971578732558, "XPathParser.RelativeLocationPath" },
        { 8096769971578732559, "XPathParser.Step" },
        { 8096769971578732560, "XPathParser.AxisSpecifier" },
        { 8096769971578732561, "XPathParser.AxisName" },
        { 8096769971578732562, "XPathParser.AbbreviatedAxisSpecifier" },
        { 8096769971578732563, "XPathParser.NodeTest" },
        { 8096769971578732564, "XPathParser.Literal" },
        { 8096769971578732565, "XPathParser.NodeType" },
        { 8096769971578732566, "XPathParser.NameTest" },
        { 8096769971578732567, "XPathParser.NCName" },
        { 8096769971578732568, "XPathParser.QName" },
        { 8096769971578732569, "XPathParser.PrefixedName" },
        { 8096769971578732570, "XPathParser.Prefix" },
        { 8096769971578732571, "XPathParser.UnprefixedName" },
        { 8096769971578732572, "XPathParser.LocalPart" },
        { 8096769971578732573, "XPathParser.Predicate" },
        { 8096769971578732574, "XPathParser.AbbreviatedStep" },
        { 8096769971578732575, "XPathParser.FunctionCall" },
        { 8096769971578732576, "XPathParser.FunctionName" },
        { 8096769971578732577, "XPathParser.Argument" },
        { 8096769971578732578, "XPathParser.FilterExpr" },
        { 8096769971578732579, "XPathParser.PrimaryExpr" },
        { 8096769971578732580, "XPathParser.VariableReference" },
        { 8096769971578732581, "XPathParser.Number" },
        { 8096769971578732582, "XPathParser.EqualityOp" },
        { 8096769971578732583, "XPathParser.RelationalOp" },
        { 8096769971578732584, "XPathParser.AdditiveOp" },
        { 8096769971578732585, "XPathParser.MultiplicativeOp" },
        { 8096769971578732586, "XPathParser.CombinePathOp" },
        { 8096769971578732587, "XPathParser.OrKeyword" },
        { 8096769971578732588, "XPathParser.AndKeyword" },
        { 8096769971578732589, "XPathParser.DivKeyword" },
        { 8096769971578732590, "XPathParser.ModKeyword" },
        { 8096769971578732591, "XPathParser.ProcessingInstructionKeyword" }
    };
    return &ruleNameMap;
}

} // soul_expected::xml::xpath::parser::rules
