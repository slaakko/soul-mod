module minilang.spg.rules;

namespace minilang::spg::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 3662973475552755713, "ExpressionParser.Expression" },
        { 3662973475552755714, "ExpressionParser.PrimaryExpression" },
        { 3662973475552755715, "ExpressionParser.PostfixExpression" },
        { 3662973475552755716, "ExpressionParser.ExpressionList" },
        { 3662973475552755717, "ExpressionParser.UnaryExpression" },
        { 3662973475552755718, "ExpressionParser.UnaryOperator" },
        { 3662973475552755719, "ExpressionParser.MultiplicativeExpression" },
        { 3662973475552755720, "ExpressionParser.MultiplicativeOperator" },
        { 3662973475552755721, "ExpressionParser.AdditiveExpression" },
        { 3662973475552755722, "ExpressionParser.AdditiveOperator" },
        { 3662973475552755723, "ExpressionParser.RelationalExpression" },
        { 3662973475552755724, "ExpressionParser.RelationalOperator" },
        { 3662973475552755725, "ExpressionParser.EqualityExpression" },
        { 3662973475552755726, "ExpressionParser.EqualityOperator" },
        { 1162212618379722753, "FunctionParser.Function" },
        { 1162212618379722754, "FunctionParser.ParameterList" },
        { 1162212618379722755, "FunctionParser.Parameter" },
        { 2933912217394872321, "IdentifierParser.Identifier" },
        { 2710058753855586305, "LiteralParser.Literal" },
        { 2710058753855586306, "LiteralParser.BooleanLiteral" },
        { 2710058753855586307, "LiteralParser.IntegerLiteral" },
        { 604673310139088897, "SourceFileParser.SourceFile" },
        { 127393969859461121, "StatementParser.Statement" },
        { 127393969859461122, "StatementParser.IfStatement" },
        { 127393969859461123, "StatementParser.WhileStatement" },
        { 127393969859461124, "StatementParser.ReturnStatement" },
        { 127393969859461125, "StatementParser.CompoundStatement" },
        { 127393969859461126, "StatementParser.ConstructionStatement" },
        { 127393969859461127, "StatementParser.AssignmentStatement" },
        { 1020028859917008897, "TypeParser.Type" }
    };
    return &ruleNameMap;
}

} // minilang::spg::rules
