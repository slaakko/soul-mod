module soul.slg.parsers.rules;

namespace soul::slg::parsers::rules {

std::mutex ruleMtx;

std::map<std::int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<std::int64_t, std::string> ruleNameMap = {
        { 5410810734487535617, "ExpressionFileParser.ExpressionFile" },
        { 5410810734487535618, "ExpressionFileParser.Expression" },
        { 8883513078608560129, "LexerFileParser.LexerFile" },
        { 8883513078608560130, "LexerFileParser.Imports" },
        { 8883513078608560131, "LexerFileParser.LexerContent" },
        { 8883513078608560132, "LexerFileParser.Rules" },
        { 8883513078608560133, "LexerFileParser.Rule" },
        { 8883513078608560134, "LexerFileParser.Variables" },
        { 8883513078608560135, "LexerFileParser.Variable" },
        { 8883513078608560136, "LexerFileParser.Actions" },
        { 8883513078608560137, "LexerFileParser.Action" },
        { 8613845327771860993, "KeywordFileParser.KeywordFile" },
        { 8613845327771860994, "KeywordFileParser.Imports" },
        { 8613845327771860995, "KeywordFileParser.Keyword" },
        { 7800349797168185345, "SlgFileParser.SlgFile" },
        { 7800349797168185346, "SlgFileParser.SlgFileDeclaration" },
        { 7800349797168185347, "SlgFileParser.TokenFileDeclaration" },
        { 7800349797168185348, "SlgFileParser.KeywordFileDeclaration" },
        { 7800349797168185349, "SlgFileParser.ExpressionFileDeclaration" },
        { 7800349797168185350, "SlgFileParser.LexerFileDeclaration" },
        { 7544922165020196865, "TokenFileParser.TokenFile" },
        { 7544922165020196866, "TokenFileParser.Token" },
        { 2231932063773097985, "CommonParser.QualifiedId" },
        { 2231932063773097986, "CommonParser.ExportModule" },
        { 2231932063773097987, "CommonParser.Import" },
        { 2231932063773097988, "CommonParser.ImportPrefix" },
        { 2231932063773097989, "CommonParser.ExprString" },
        { 2231932063773097990, "CommonParser.FilePath" },
        { 2231932063773097991, "CommonParser.ExportKeyword" },
        { 2231932063773097992, "CommonParser.ModuleKeyword" },
        { 2231932063773097993, "CommonParser.ImportKeyword" },
        { 2231932063773097994, "CommonParser.ImplementationPrefix" },
        { 2231932063773097995, "CommonParser.InterfacePrefix" },
        { 2231932063773097996, "CommonParser.ImplementationKeyword" },
        { 2231932063773097997, "CommonParser.InterfaceKeyword" },
        { 2231932063773097998, "CommonParser.ParserKeyword" },
        { 2231932063773097999, "CommonParser.LexerKeyword" },
        { 7462140351176769537, "DeclarationParser.BlockDeclaration" },
        { 7462140351176769538, "DeclarationParser.SimpleDeclaration" },
        { 7462140351176769539, "DeclarationParser.DeclSpecifierSeq" },
        { 7462140351176769540, "DeclarationParser.DeclSpecifier" },
        { 7462140351176769541, "DeclarationParser.StorageClassSpecifier" },
        { 7462140351176769542, "DeclarationParser.TypeSpecifier" },
        { 7462140351176769543, "DeclarationParser.SimpleTypeSpecifier" },
        { 7462140351176769544, "DeclarationParser.TypeName" },
        { 7462140351176769545, "DeclarationParser.TemplateArgumentList" },
        { 7462140351176769546, "DeclarationParser.TemplateArgument" },
        { 7462140351176769547, "DeclarationParser.Typedef" },
        { 7462140351176769548, "DeclarationParser.CVQualifier" },
        { 7462140351176769549, "DeclarationParser.NamespaceAliasDefinition" },
        { 7462140351176769550, "DeclarationParser.UsingDeclaration" },
        { 7462140351176769551, "DeclarationParser.UsingDirective" },
        { 264249250160836609, "DeclaratorParser.InitDeclaratorList" },
        { 264249250160836610, "DeclaratorParser.InitDeclarator" },
        { 264249250160836611, "DeclaratorParser.Declarator" },
        { 264249250160836612, "DeclaratorParser.DirectDeclarator" },
        { 264249250160836613, "DeclaratorParser.DeclaratorId" },
        { 264249250160836614, "DeclaratorParser.TypeId" },
        { 264249250160836615, "DeclaratorParser.Type" },
        { 264249250160836616, "DeclaratorParser.TypeSpecifierSeq" },
        { 264249250160836617, "DeclaratorParser.AbstractDeclarator" },
        { 264249250160836618, "DeclaratorParser.DirectAbstractDeclarator" },
        { 264249250160836619, "DeclaratorParser.PtrOperator" },
        { 264249250160836620, "DeclaratorParser.CVQualifierSeq" },
        { 264249250160836621, "DeclaratorParser.Initializer" },
        { 264249250160836622, "DeclaratorParser.InitializerClause" },
        { 264249250160836623, "DeclaratorParser.InitializerList" },
        { 2139687109831688193, "ExpressionParser.Expression" },
        { 2139687109831688194, "ExpressionParser.ConstantExpression" },
        { 2139687109831688195, "ExpressionParser.AssignmentExpression" },
        { 2139687109831688196, "ExpressionParser.AssignmentOp" },
        { 2139687109831688197, "ExpressionParser.ConditionalExpression" },
        { 2139687109831688198, "ExpressionParser.LogicalOrExpression" },
        { 2139687109831688199, "ExpressionParser.LogicalAndExpression" },
        { 2139687109831688200, "ExpressionParser.InclusiveOrExpression" },
        { 2139687109831688201, "ExpressionParser.ExclusiveOrExpression" },
        { 2139687109831688202, "ExpressionParser.AndExpression" },
        { 2139687109831688203, "ExpressionParser.EqualityExpression" },
        { 2139687109831688204, "ExpressionParser.EqOp" },
        { 2139687109831688205, "ExpressionParser.RelationalExpression" },
        { 2139687109831688206, "ExpressionParser.RelOp" },
        { 2139687109831688207, "ExpressionParser.ShiftExpression" },
        { 2139687109831688208, "ExpressionParser.ShiftOp" },
        { 2139687109831688209, "ExpressionParser.AdditiveExpression" },
        { 2139687109831688210, "ExpressionParser.AddOp" },
        { 2139687109831688211, "ExpressionParser.MultiplicativeExpression" },
        { 2139687109831688212, "ExpressionParser.MulOp" },
        { 2139687109831688213, "ExpressionParser.PmExpression" },
        { 2139687109831688214, "ExpressionParser.PmOp" },
        { 2139687109831688215, "ExpressionParser.CastExpression" },
        { 2139687109831688216, "ExpressionParser.UnaryExpression" },
        { 2139687109831688217, "ExpressionParser.UnaryOperator" },
        { 2139687109831688218, "ExpressionParser.PostfixExpression" },
        { 2139687109831688219, "ExpressionParser.PostCastExpression" },
        { 2139687109831688220, "ExpressionParser.ExpressionList" },
        { 2139687109831688221, "ExpressionParser.PrimaryExpression" },
        { 2139687109831688222, "ExpressionParser.IdExpression" },
        { 2139687109831688223, "ExpressionParser.TypeSpecifierOrTypeName" },
        { 2139687109831688224, "ExpressionParser.NewExpression" },
        { 2139687109831688225, "ExpressionParser.NewPlacement" },
        { 2139687109831688226, "ExpressionParser.NewTypeId" },
        { 2139687109831688227, "ExpressionParser.NewDeclarator" },
        { 2139687109831688228, "ExpressionParser.NewInitializer" },
        { 2139687109831688229, "ExpressionParser.DirectNewDeclarator" },
        { 2139687109831688230, "ExpressionParser.DeleteExpression" },
        { 2139687109831688231, "ExpressionParser.OperatorFunctionId" },
        { 2139687109831688232, "ExpressionParser.Operator" },
        { 2155528619961614337, "CppIdentifierParser.CppIdentifier" },
        { 2155528619961614338, "CppIdentifierParser.QualifiedCppId" },
        { 5808325801866690561, "LiteralParser.Literal" },
        { 8599657534669717505, "StatementParser.Statement" },
        { 8599657534669717506, "StatementParser.LabeledStatement" },
        { 8599657534669717507, "StatementParser.EmptyStatement" },
        { 8599657534669717508, "StatementParser.CompoundStatement" },
        { 8599657534669717509, "StatementParser.SelectionStatement" },
        { 8599657534669717510, "StatementParser.IfStatement" },
        { 8599657534669717511, "StatementParser.SwitchStatement" },
        { 8599657534669717512, "StatementParser.IterationStatement" },
        { 8599657534669717513, "StatementParser.WhileStatement" },
        { 8599657534669717514, "StatementParser.DoStatement" },
        { 8599657534669717515, "StatementParser.RangeForStatement" },
        { 8599657534669717516, "StatementParser.ForRangeDeclaration" },
        { 8599657534669717517, "StatementParser.ForStatement" },
        { 8599657534669717518, "StatementParser.ForInitStatement" },
        { 8599657534669717519, "StatementParser.JumpStatement" },
        { 8599657534669717520, "StatementParser.BreakStatement" },
        { 8599657534669717521, "StatementParser.ContinueStatement" },
        { 8599657534669717522, "StatementParser.ReturnStatement" },
        { 8599657534669717523, "StatementParser.GotoStatement" },
        { 8599657534669717524, "StatementParser.DeclarationStatement" },
        { 8599657534669717525, "StatementParser.Condition" },
        { 8599657534669717526, "StatementParser.ExpressionStatement" }
    };
    return &ruleNameMap;
}

} // soul::slg::parsers::rules
