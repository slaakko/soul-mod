module otava.parser.spg.rules;

namespace otava::parser::spg::rules {

std::mutex ruleMtx;

std::map<int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<int64_t, std::string> ruleNameMap = {
        { 4789400228853710849, "AttributeParser.AttributeSpecifierSeq" },
        { 4789400228853710850, "AttributeParser.AttributeSpecifier" },
        { 4789400228853710851, "AttributeParser.AttributeList" },
        { 4789400228853710852, "AttributeParser.AttributeUsingPrefix" },
        { 4789400228853710853, "AttributeParser.AttributeNamespace" },
        { 4789400228853710854, "AttributeParser.Attribute" },
        { 4789400228853710855, "AttributeParser.AttributeToken" },
        { 4789400228853710856, "AttributeParser.AttributeScopedToken" },
        { 4789400228853710857, "AttributeParser.AttributeArgumentClause" },
        { 4789400228853710858, "AttributeParser.BalancedTokenSeq" },
        { 4789400228853710859, "AttributeParser.BalancedToken" },
        { 4789400228853710860, "AttributeParser.AlignmentSpecifier" },
        { 1303477245251158017, "ClassParser.ClassSpecifier" },
        { 1303477245251158018, "ClassParser.ClassHead" },
        { 1303477245251158019, "ClassParser.ClassKey" },
        { 1303477245251158020, "ClassParser.ClassHeadName" },
        { 1303477245251158021, "ClassParser.ClassName" },
        { 1303477245251158022, "ClassParser.ClassVirtSpecifier" },
        { 1303477245251158023, "ClassParser.VirtSpecifierSeq" },
        { 1303477245251158024, "ClassParser.VirtSpecifier" },
        { 1303477245251158025, "ClassParser.OverrideKeyword" },
        { 1303477245251158026, "ClassParser.FinalKeyword" },
        { 1303477245251158027, "ClassParser.BaseClause" },
        { 1303477245251158028, "ClassParser.BaseSpecifierList" },
        { 1303477245251158029, "ClassParser.BaseSpecifier" },
        { 1303477245251158030, "ClassParser.ClassOrDeclType" },
        { 1303477245251158031, "ClassParser.MemberSpecification" },
        { 1303477245251158032, "ClassParser.MemberDeclaration" },
        { 1303477245251158033, "ClassParser.RBraceNext" },
        { 1303477245251158034, "ClassParser.MemberDeclSpecifiers" },
        { 1303477245251158035, "ClassParser.RetMemberDeclSpecifiers" },
        { 1303477245251158036, "ClassParser.MemberFunctionDefinition" },
        { 1303477245251158037, "ClassParser.RetMemberFunctionDefinition" },
        { 1303477245251158038, "ClassParser.MemberTemplateDeclaration" },
        { 1303477245251158039, "ClassParser.MemberDeclaratorList" },
        { 1303477245251158040, "ClassParser.MemberDeclarator" },
        { 1303477245251158041, "ClassParser.CtorInitializer" },
        { 1303477245251158042, "ClassParser.CtorInitializerGuarded" },
        { 1303477245251158043, "ClassParser.CtorInitializerUnguarded" },
        { 1303477245251158044, "ClassParser.CtorInitializerSaved" },
        { 1303477245251158045, "ClassParser.MemberInitializerList" },
        { 1303477245251158046, "ClassParser.MemberInitializer" },
        { 1303477245251158047, "ClassParser.MemberInitializerId" },
        { 1303477245251158048, "ClassParser.PureSpecifier" },
        { 1303477245251158049, "ClassParser.AccessSpecifier" },
        { 1303477245251158050, "ClassParser.Private" },
        { 1303477245251158051, "ClassParser.VirtualSpecifier" },
        { 2039843044483661825, "ConceptParser.ConceptDefinition" },
        { 2039843044483661826, "ConceptParser.ConceptName" },
        { 2039843044483661827, "ConceptParser.ConceptNameChecked" },
        { 2039843044483661828, "ConceptParser.ConstraintExpression" },
        { 2039843044483661829, "ConceptParser.RequiresClause" },
        { 2039843044483661830, "ConceptParser.ConstraintLogicalOrExpression" },
        { 2039843044483661831, "ConceptParser.ConstraintLogicalAndExpression" },
        { 2039843044483661832, "ConceptParser.RequiresExpression" },
        { 2039843044483661833, "ConceptParser.RequirementParameterList" },
        { 2039843044483661834, "ConceptParser.RequirementBody" },
        { 2039843044483661835, "ConceptParser.RequirementSeq" },
        { 2039843044483661836, "ConceptParser.Requirement" },
        { 2039843044483661837, "ConceptParser.SimpleRequirement" },
        { 2039843044483661838, "ConceptParser.TypeRequirement" },
        { 2039843044483661839, "ConceptParser.CompoundRequirement" },
        { 2039843044483661840, "ConceptParser.ReturnTypeRequirement" },
        { 2039843044483661841, "ConceptParser.NestedRequirement" },
        { 2039843044483661842, "ConceptParser.TypeConstraint" },
        { 8966079074640330753, "DeclarationParser.DeclarationSeq" },
        { 8966079074640330754, "DeclarationParser.NamespaceDeclarationSeq" },
        { 8966079074640330755, "DeclarationParser.RBraceNext" },
        { 8966079074640330756, "DeclarationParser.Declaration" },
        { 8966079074640330757, "DeclarationParser.BlockDeclaration" },
        { 8966079074640330758, "DeclarationParser.NoDeclSpecFunctionDeclaration" },
        { 8966079074640330759, "DeclarationParser.EmptyDeclaration" },
        { 8966079074640330760, "DeclarationParser.SimpleDeclaration" },
        { 8966079074640330761, "DeclarationParser.AsmDeclaration" },
        { 8966079074640330762, "DeclarationParser.Asm" },
        { 8966079074640330763, "DeclarationParser.LinkageSpecification" },
        { 8966079074640330764, "DeclarationParser.NamespaceDefinition" },
        { 8966079074640330765, "DeclarationParser.NamedNamespaceDefinition" },
        { 8966079074640330766, "DeclarationParser.UnnamedNamespaceDefinition" },
        { 8966079074640330767, "DeclarationParser.NestedNamespaceDefinition" },
        { 8966079074640330768, "DeclarationParser.NamespaceAliasDefinition" },
        { 8966079074640330769, "DeclarationParser.QualifiedNamespaceSpecifier" },
        { 8966079074640330770, "DeclarationParser.NamespaceBody" },
        { 8966079074640330771, "DeclarationParser.NestedNamespaceSpecifier" },
        { 8966079074640330772, "DeclarationParser.Namespace" },
        { 8966079074640330773, "DeclarationParser.NamespaceName" },
        { 8966079074640330774, "DeclarationParser.UsingDeclaration" },
        { 8966079074640330775, "DeclarationParser.Using" },
        { 8966079074640330776, "DeclarationParser.UsingDeclaratorList" },
        { 8966079074640330777, "DeclarationParser.UsingDeclarator" },
        { 8966079074640330778, "DeclarationParser.UsingEnumDeclaration" },
        { 8966079074640330779, "DeclarationParser.UsingDirective" },
        { 8966079074640330780, "DeclarationParser.StaticAssertDeclaration" },
        { 8966079074640330781, "DeclarationParser.StaticAssert" },
        { 8966079074640330782, "DeclarationParser.AliasDeclaration" },
        { 8966079074640330783, "DeclarationParser.DeclSpecifierSeq" },
        { 8966079074640330784, "DeclarationParser.Inline" },
        { 8966079074640330785, "DeclarationParser.DeclSpecifier" },
        { 8966079074640330786, "DeclarationParser.StorageClassSpecifier" },
        { 8966079074640330787, "DeclarationParser.FunctionSpecifier" },
        { 8966079074640330788, "DeclarationParser.ExplicitSpecifier" },
        { 8966079074640330789, "DeclarationParser.InitDeclaratorList" },
        { 8966079074640330790, "DeclarationParser.InitDeclarator" },
        { 8966079074640330791, "DeclarationParser.DeclaratorPushClassScope" },
        { 8966079074640330792, "DeclarationParser.Declarator" },
        { 8966079074640330793, "DeclarationParser.PtrDeclarator" },
        { 8966079074640330794, "DeclarationParser.NoPtrDeclarator" },
        { 8966079074640330795, "DeclarationParser.ParametersAndQualifiers" },
        { 8966079074640330796, "DeclarationParser.TrailingReturnType" },
        { 8966079074640330797, "DeclarationParser.PtrOperator" },
        { 8966079074640330798, "DeclarationParser.AbstractDeclarator" },
        { 8966079074640330799, "DeclarationParser.NoPtrAbstractDeclarator" },
        { 8966079074640330800, "DeclarationParser.PtrAbstractDeclarator" },
        { 8966079074640330801, "DeclarationParser.AbstractPackDeclarator" },
        { 8966079074640330802, "DeclarationParser.NoPtrAbstractPackDeclarator" },
        { 8966079074640330803, "DeclarationParser.DeclaratorId" },
        { 8966079074640330804, "DeclarationParser.Ptr" },
        { 8966079074640330805, "DeclarationParser.LvalueRef" },
        { 8966079074640330806, "DeclarationParser.RvalueRef" },
        { 8966079074640330807, "DeclarationParser.RefQualifier" },
        { 8966079074640330808, "DeclarationParser.CVQualifierSeq" },
        { 8966079074640330809, "DeclarationParser.CVQualifier" },
        { 8966079074640330810, "DeclarationParser.NoexceptSpecifier" },
        { 8966079074640330811, "DeclarationParser.ThrowSpecifier" },
        { 8966079074640330812, "DeclarationParser.AttributeDeclaration" },
        { 5996424684868993025, "EnumParser.EnumName" },
        { 5996424684868993026, "EnumParser.EnumSpecifier" },
        { 5996424684868993027, "EnumParser.EnumHead" },
        { 5996424684868993028, "EnumParser.EnumKey" },
        { 5996424684868993029, "EnumParser.EnumHeadName" },
        { 5996424684868993030, "EnumParser.EnumBase" },
        { 5996424684868993031, "EnumParser.EnumeratorList" },
        { 5996424684868993032, "EnumParser.EnumeratorDefinition" },
        { 5996424684868993033, "EnumParser.Enumerator" },
        { 5996424684868993034, "EnumParser.OpaqueEnumDeclaration" },
        { 5996424684868993035, "EnumParser.ElaboratedEnumSpecifier" },
        { 4756117359045902337, "ExpressionParser.Expression" },
        { 4756117359045902338, "ExpressionParser.ConstantExpression" },
        { 4756117359045902339, "ExpressionParser.AssignmentExpression" },
        { 4756117359045902340, "ExpressionParser.AssignmentOp" },
        { 4756117359045902341, "ExpressionParser.ConditionalExpression" },
        { 4756117359045902342, "ExpressionParser.YieldExpression" },
        { 4756117359045902343, "ExpressionParser.ThrowExpression" },
        { 4756117359045902344, "ExpressionParser.LogicalOrExpression" },
        { 4756117359045902345, "ExpressionParser.LogicalAndExpression" },
        { 4756117359045902346, "ExpressionParser.InclusiveOrExpression" },
        { 4756117359045902347, "ExpressionParser.ExclusiveOrExpression" },
        { 4756117359045902348, "ExpressionParser.AndExpression" },
        { 4756117359045902349, "ExpressionParser.EqualityExpression" },
        { 4756117359045902350, "ExpressionParser.EqualityOp" },
        { 4756117359045902351, "ExpressionParser.RelationalExpression" },
        { 4756117359045902352, "ExpressionParser.RelationalOp" },
        { 4756117359045902353, "ExpressionParser.CompareExpression" },
        { 4756117359045902354, "ExpressionParser.ShiftExpression" },
        { 4756117359045902355, "ExpressionParser.ShiftOp" },
        { 4756117359045902356, "ExpressionParser.AdditiveExpression" },
        { 4756117359045902357, "ExpressionParser.AdditiveOp" },
        { 4756117359045902358, "ExpressionParser.MultiplicativeExpression" },
        { 4756117359045902359, "ExpressionParser.MultiplicativeOp" },
        { 4756117359045902360, "ExpressionParser.PmExpression" },
        { 4756117359045902361, "ExpressionParser.PmOp" },
        { 4756117359045902362, "ExpressionParser.CastExpression" },
        { 4756117359045902363, "ExpressionParser.UnaryExpression" },
        { 4756117359045902364, "ExpressionParser.UnaryOp" },
        { 4756117359045902365, "ExpressionParser.AwaitExpression" },
        { 4756117359045902366, "ExpressionParser.SizeOfExpression" },
        { 4756117359045902367, "ExpressionParser.AlignOfExpression" },
        { 4756117359045902368, "ExpressionParser.NoexceptEpression" },
        { 4756117359045902369, "ExpressionParser.NewExpression" },
        { 4756117359045902370, "ExpressionParser.NewPlacement" },
        { 4756117359045902371, "ExpressionParser.NewInitializer" },
        { 4756117359045902372, "ExpressionParser.NewTypeId" },
        { 4756117359045902373, "ExpressionParser.NewDeclarator" },
        { 4756117359045902374, "ExpressionParser.NoPtrNewDeclarator" },
        { 4756117359045902375, "ExpressionParser.DeleteExpression" },
        { 4756117359045902376, "ExpressionParser.PostfixExpression" },
        { 4756117359045902377, "ExpressionParser.CppCastExpression" },
        { 4756117359045902378, "ExpressionParser.TypeIdExpression" },
        { 4756117359045902379, "ExpressionParser.IntrinsicInvokeExpr" },
        { 4756117359045902380, "ExpressionParser.PrimaryExpression" },
        { 4756117359045902381, "ExpressionParser.FoldExpression" },
        { 4756117359045902382, "ExpressionParser.FoldOp" },
        { 4756117359045902383, "ExpressionParser.ParenthesizedExpression" },
        { 4756117359045902384, "ExpressionParser.DotOp" },
        { 4756117359045902385, "ExpressionParser.ArrowOp" },
        { 4756117359045902386, "ExpressionParser.IdExpression" },
        { 4756117359045902387, "ExpressionParser.IdExpr" },
        { 4756117359045902388, "ExpressionParser.ExpressionList" },
        { 3334239814043041793, "FunctionParser.FunctionDefinition" },
        { 3334239814043041794, "FunctionParser.NoDeclSpecFunctionDefinition" },
        { 3334239814043041795, "FunctionParser.FunctionBody" },
        { 3334239814043041796, "FunctionParser.Default" },
        { 3334239814043041797, "FunctionParser.Delete" },
        { 3334239814043041798, "FunctionParser.ParameterDeclarationClause" },
        { 3334239814043041799, "FunctionParser.ParameterDeclarationList" },
        { 3334239814043041800, "FunctionParser.ParameterDeclaration" },
        { 3334239814043041801, "FunctionParser.OperatorFunctionId" },
        { 3334239814043041802, "FunctionParser.ConversionFunctionId" },
        { 3334239814043041803, "FunctionParser.DestructorId" },
        { 3334239814043041804, "FunctionParser.ConversionTypeId" },
        { 3334239814043041805, "FunctionParser.ConversionDeclarator" },
        { 3334239814043041806, "FunctionParser.OperatorKw" },
        { 3334239814043041807, "FunctionParser.Operator" },
        { 3334239814043041808, "FunctionParser.Noexcept" },
        { 3334239814043041809, "FunctionParser.FunctionTryBlock" },
        { 3962850076434366465, "GuardParser.ConceptGuard" },
        { 3962850076434366466, "GuardParser.NotDefiningTypeSpecifierGuard" },
        { 3962850076434366467, "GuardParser.AssumeTypeGuard" },
        { 3962850076434366468, "GuardParser.MemberFunctionGuard" },
        { 3962850076434366469, "GuardParser.SavedMemberFunctionBodyGuard" },
        { 3962850076434366470, "GuardParser.SavedCtorInitializerGuard" },
        { 3962850076434366471, "GuardParser.NoDeclSpecFunctionDeclarationGuard" },
        { 3962850076434366472, "GuardParser.NoDeclSpecFunctionDefinitionGuard" },
        { 1087988986435076097, "IdentifierParser.Identifier" },
        { 1087988986435076098, "IdentifierParser.UnqualifiedId" },
        { 1087988986435076099, "IdentifierParser.QualifiedId" },
        { 1087988986435076100, "IdentifierParser.Template" },
        { 1087988986435076101, "IdentifierParser.NestedNameSpecifier" },
        { 1087988986435076102, "IdentifierParser.IdentifierList" },
        { 1087988986435076103, "IdentifierParser.TypeIdentifier" },
        { 1087988986435076104, "IdentifierParser.TypeIdentifierUnchecked" },
        { 1087988986435076105, "IdentifierParser.TypeIdentifierChecked" },
        { 1087988986435076106, "IdentifierParser.Unnamed" },
        { 8049098643501744129, "InitializationParser.Initializer" },
        { 8049098643501744130, "InitializationParser.InitializerClause" },
        { 8049098643501744131, "InitializationParser.InitializerList" },
        { 8049098643501744132, "InitializationParser.DesignatedInitializerList" },
        { 8049098643501744133, "InitializationParser.DesignatedInitializerClause" },
        { 8049098643501744134, "InitializationParser.Designator" },
        { 8049098643501744135, "InitializationParser.ExprOrBracedInitList" },
        { 8049098643501744136, "InitializationParser.BraceOrEqualInitializer" },
        { 8049098643501744137, "InitializationParser.BracedInitList" },
        { 8834454897001758721, "LambdaParser.LambdaExpression" },
        { 8834454897001758722, "LambdaParser.LambdaIntroducer" },
        { 8834454897001758723, "LambdaParser.LambdaCapture" },
        { 8834454897001758724, "LambdaParser.CaptureDefault" },
        { 8834454897001758725, "LambdaParser.CaptureList" },
        { 8834454897001758726, "LambdaParser.Capture" },
        { 8834454897001758727, "LambdaParser.InitCapture" },
        { 8834454897001758728, "LambdaParser.SimpleCapture" },
        { 8834454897001758729, "LambdaParser.LambdaDeclarator" },
        { 8834454897001758730, "LambdaParser.LambdaSpecifiers" },
        { 8834454897001758731, "LambdaParser.LambdaTemplateParams" },
        { 2723703907904651265, "LiteralParser.Literal" },
        { 2723703907904651266, "LiteralParser.UserDefinedLiteral" },
        { 2723703907904651267, "LiteralParser.UdSuffix" },
        { 2723703907904651268, "LiteralParser.LiteralOperatorId" },
        { 2723703907904651269, "LiteralParser.StringLiteral" },
        { 2774545673465364481, "ModuleParser.ModuleDeclaration" },
        { 2774545673465364482, "ModuleParser.ModuleName" },
        { 2774545673465364483, "ModuleParser.ExportDeclaration" },
        { 2774545673465364484, "ModuleParser.ImportDeclaration" },
        { 2774545673465364485, "ModuleParser.ModulePartition" },
        { 2774545673465364486, "ModuleParser.ExportKeyword" },
        { 2774545673465364487, "ModuleParser.ImportKeyword" },
        { 2774545673465364488, "ModuleParser.ModuleKeyword" },
        { 2774545673465364489, "ModuleParser.GlobalModuleFragment" },
        { 2774545673465364490, "ModuleParser.PrivateModuleFragment" },
        { 2774545673465364491, "ModuleParser.HeaderName" },
        { 4573667023757770753, "ModuleDependencyParser.ModuleUnit" },
        { 4573667023757770754, "ModuleDependencyParser.GlobalModuleFragment" },
        { 4573667023757770755, "ModuleDependencyParser.DeclarationSeq" },
        { 4573667023757770756, "ModuleDependencyParser.Declaration" },
        { 4573667023757770757, "ModuleDependencyParser.ExportImportDeclaration" },
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
        { 1955786072029921293, "PunctuationParser.Assign" },
        { 695727793635328001, "SimpleTypeParser.SimpleType" },
        { 4569043890895585281, "StatementParser.Statement" },
        { 4569043890895585282, "StatementParser.LabeledStatement" },
        { 4569043890895585283, "StatementParser.CompoundStatementUnguarded" },
        { 4569043890895585284, "StatementParser.RBraceNext" },
        { 4569043890895585285, "StatementParser.CompoundStatementGuarded" },
        { 4569043890895585286, "StatementParser.CompoundStatementSaved" },
        { 4569043890895585287, "StatementParser.CompoundStatement" },
        { 4569043890895585288, "StatementParser.SelectionStatement" },
        { 4569043890895585289, "StatementParser.IfStatement" },
        { 4569043890895585290, "StatementParser.SwitchStatement" },
        { 4569043890895585291, "StatementParser.IterationStatement" },
        { 4569043890895585292, "StatementParser.WhileStatement" },
        { 4569043890895585293, "StatementParser.DoStatement" },
        { 4569043890895585294, "StatementParser.RangeForStatement" },
        { 4569043890895585295, "StatementParser.ForRangeDeclaration" },
        { 4569043890895585296, "StatementParser.ForRangeInitializer" },
        { 4569043890895585297, "StatementParser.ForStatement" },
        { 4569043890895585298, "StatementParser.JumpStatement" },
        { 4569043890895585299, "StatementParser.BreakStatement" },
        { 4569043890895585300, "StatementParser.ContinueStatement" },
        { 4569043890895585301, "StatementParser.ReturnStatement" },
        { 4569043890895585302, "StatementParser.CoroutineReturnStatement" },
        { 4569043890895585303, "StatementParser.GotoStatement" },
        { 4569043890895585304, "StatementParser.TryStatement" },
        { 4569043890895585305, "StatementParser.HandlerSeq" },
        { 4569043890895585306, "StatementParser.Handler" },
        { 4569043890895585307, "StatementParser.ExceptionDeclaration" },
        { 4569043890895585308, "StatementParser.ExpressionStatement" },
        { 4569043890895585309, "StatementParser.DeclarationStatement" },
        { 4569043890895585310, "StatementParser.InitStatement" },
        { 4569043890895585311, "StatementParser.Condition" },
        { 9050966169783107585, "TemplateParser.TemplateDeclaration" },
        { 9050966169783107586, "TemplateParser.TemplateHead" },
        { 9050966169783107587, "TemplateParser.TemplateParameterList" },
        { 9050966169783107588, "TemplateParser.TemplateParameter" },
        { 9050966169783107589, "TemplateParser.TypeParameter" },
        { 9050966169783107590, "TemplateParser.TypeParameterKey" },
        { 9050966169783107591, "TemplateParser.Typename" },
        { 9050966169783107592, "TemplateParser.Class" },
        { 9050966169783107593, "TemplateParser.TemplateId" },
        { 9050966169783107594, "TemplateParser.SimpleTemplateId" },
        { 9050966169783107595, "TemplateParser.TemplateName" },
        { 9050966169783107596, "TemplateParser.TemplateArgumentList" },
        { 9050966169783107597, "TemplateParser.TemplateArgument" },
        { 9050966169783107598, "TemplateParser.TemplateArgNext" },
        { 9050966169783107599, "TemplateParser.DeductionGuide" },
        { 9050966169783107600, "TemplateParser.Arrow" },
        { 9050966169783107601, "TemplateParser.ExplicitInstantiation" },
        { 9050966169783107602, "TemplateParser.ExplicitSpecialization" },
        { 9050966169783107603, "TemplateParser.Extern" },
        { 9050966169783107604, "TemplateParser.Template" },
        { 5945151541383004161, "TranslationUnitParser.TranslationUnit" },
        { 5945151541383004162, "TranslationUnitParser.ModuleUnit" },
        { 2330114084151754753, "TypeParser.TypeSpecifierSeq" },
        { 2330114084151754754, "TypeParser.TypeSpecifierSeqReset" },
        { 2330114084151754755, "TypeParser.DefiningTypeId" },
        { 2330114084151754756, "TypeParser.DefiningTypeSpecifierSeq" },
        { 2330114084151754757, "TypeParser.DefiningTypeSpecifierReset" },
        { 2330114084151754758, "TypeParser.DefiningTypeSpecifier" },
        { 2330114084151754759, "TypeParser.TypeSpecifier" },
        { 2330114084151754760, "TypeParser.ElaboratedTypeSpecifier" },
        { 2330114084151754761, "TypeParser.SimpleTypeSpecifierReset" },
        { 2330114084151754762, "TypeParser.SimpleTypeSpecifier" },
        { 2330114084151754763, "TypeParser.TypeName" },
        { 2330114084151754764, "TypeParser.TypeId" },
        { 2330114084151754765, "TypeParser.TypenameSpecifier" },
        { 2330114084151754766, "TypeParser.DeclTypeSpecifier" },
        { 2330114084151754767, "TypeParser.PlaceholderTypeSpecifier" }
    };
    return &ruleNameMap;
}

} // otava::parser::spg::rules
