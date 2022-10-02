module cpp20.parser.spg.rules;

namespace cpp20::parser::spg::rules {

std::mutex ruleMtx;

std::map<int64_t, std::string>* GetRuleNameMapPtr()
{
    std::lock_guard<std::mutex> lock(ruleMtx);
    static std::map<int64_t, std::string> ruleNameMap = {
        { 5156478082776825857, "AttributeParser.AttributeSpecifierSeq" },
        { 5156478082776825858, "AttributeParser.AttributeSpecifier" },
        { 5156478082776825859, "AttributeParser.AttributeList" },
        { 5156478082776825860, "AttributeParser.AttributeUsingPrefix" },
        { 5156478082776825861, "AttributeParser.AttributeNamespace" },
        { 5156478082776825862, "AttributeParser.Attribute" },
        { 5156478082776825863, "AttributeParser.AttributeToken" },
        { 5156478082776825864, "AttributeParser.AttributeScopedToken" },
        { 5156478082776825865, "AttributeParser.AttributeArgumentClause" },
        { 5156478082776825866, "AttributeParser.BalancedTokenSeq" },
        { 5156478082776825867, "AttributeParser.BalancedToken" },
        { 5156478082776825868, "AttributeParser.AlignmentSpecifier" },
        { 8201428699560542209, "ClassParser.ClassSpecifier" },
        { 8201428699560542210, "ClassParser.ClassHead" },
        { 8201428699560542211, "ClassParser.ClassKey" },
        { 8201428699560542212, "ClassParser.ClassHeadName" },
        { 8201428699560542213, "ClassParser.ClassName" },
        { 8201428699560542214, "ClassParser.ClassVirtSpecifier" },
        { 8201428699560542215, "ClassParser.VirtSpecifierSeq" },
        { 8201428699560542216, "ClassParser.VirtSpecifier" },
        { 8201428699560542217, "ClassParser.OverrideKeyword" },
        { 8201428699560542218, "ClassParser.FinalKeyword" },
        { 8201428699560542219, "ClassParser.BaseClause" },
        { 8201428699560542220, "ClassParser.BaseSpecifierList" },
        { 8201428699560542221, "ClassParser.BaseSpecifier" },
        { 8201428699560542222, "ClassParser.ClassOrDeclType" },
        { 8201428699560542223, "ClassParser.MemberSpecification" },
        { 8201428699560542224, "ClassParser.MemberDeclaration" },
        { 8201428699560542225, "ClassParser.RBraceNext" },
        { 8201428699560542226, "ClassParser.MemberDeclSpecifiers" },
        { 8201428699560542227, "ClassParser.RetMemberDeclSpecifiers" },
        { 8201428699560542228, "ClassParser.MemberFunctionDefinition" },
        { 8201428699560542229, "ClassParser.RetMemberFunctionDefinition" },
        { 8201428699560542230, "ClassParser.MemberTemplateDeclaration" },
        { 8201428699560542231, "ClassParser.MemberDeclaratorList" },
        { 8201428699560542232, "ClassParser.MemberDeclarator" },
        { 8201428699560542233, "ClassParser.CtorInitializer" },
        { 8201428699560542234, "ClassParser.MemberInitializerList" },
        { 8201428699560542235, "ClassParser.MemberInitializer" },
        { 8201428699560542236, "ClassParser.MemberInitializerId" },
        { 8201428699560542237, "ClassParser.PureSpecifier" },
        { 8201428699560542238, "ClassParser.AccessSpecifier" },
        { 8201428699560542239, "ClassParser.Private" },
        { 8201428699560542240, "ClassParser.VirtualSpecifier" },
        { 7901898380417171457, "ConceptParser.ConceptDefinition" },
        { 7901898380417171458, "ConceptParser.ConceptName" },
        { 7901898380417171459, "ConceptParser.ConceptNameChecked" },
        { 7901898380417171460, "ConceptParser.ConstraintExpression" },
        { 7901898380417171461, "ConceptParser.RequiresClause" },
        { 7901898380417171462, "ConceptParser.ConstraintLogicalOrExpression" },
        { 7901898380417171463, "ConceptParser.ConstraintLogicalAndExpression" },
        { 7901898380417171464, "ConceptParser.RequiresExpression" },
        { 7901898380417171465, "ConceptParser.RequirementParameterList" },
        { 7901898380417171466, "ConceptParser.RequirementBody" },
        { 7901898380417171467, "ConceptParser.RequirementSeq" },
        { 7901898380417171468, "ConceptParser.Requirement" },
        { 7901898380417171469, "ConceptParser.SimpleRequirement" },
        { 7901898380417171470, "ConceptParser.TypeRequirement" },
        { 7901898380417171471, "ConceptParser.CompoundRequirement" },
        { 7901898380417171472, "ConceptParser.ReturnTypeRequirement" },
        { 7901898380417171473, "ConceptParser.NestedRequirement" },
        { 7901898380417171474, "ConceptParser.TypeConstraint" },
        { 5276324781484933121, "DeclarationParser.DeclarationSeq" },
        { 5276324781484933122, "DeclarationParser.NamespaceDeclarationSeq" },
        { 5276324781484933123, "DeclarationParser.RBraceNext" },
        { 5276324781484933124, "DeclarationParser.Declaration" },
        { 5276324781484933125, "DeclarationParser.BlockDeclaration" },
        { 5276324781484933126, "DeclarationParser.NoDeclSpecFunctionDeclaration" },
        { 5276324781484933127, "DeclarationParser.EmptyDeclaration" },
        { 5276324781484933128, "DeclarationParser.SimpleDeclaration" },
        { 5276324781484933129, "DeclarationParser.AsmDeclaration" },
        { 5276324781484933130, "DeclarationParser.Asm" },
        { 5276324781484933131, "DeclarationParser.LinkageSpecification" },
        { 5276324781484933132, "DeclarationParser.NamespaceDefinition" },
        { 5276324781484933133, "DeclarationParser.NamedNamespaceDefinition" },
        { 5276324781484933134, "DeclarationParser.UnnamedNamespaceDefinition" },
        { 5276324781484933135, "DeclarationParser.NestedNamespaceDefinition" },
        { 5276324781484933136, "DeclarationParser.NamespaceAliasDefinition" },
        { 5276324781484933137, "DeclarationParser.QualifiedNamespaceSpecifier" },
        { 5276324781484933138, "DeclarationParser.NamespaceBody" },
        { 5276324781484933139, "DeclarationParser.NestedNamespaceSpecifier" },
        { 5276324781484933140, "DeclarationParser.Namespace" },
        { 5276324781484933141, "DeclarationParser.NamespaceName" },
        { 5276324781484933142, "DeclarationParser.UsingDeclaration" },
        { 5276324781484933143, "DeclarationParser.Using" },
        { 5276324781484933144, "DeclarationParser.UsingDeclaratorList" },
        { 5276324781484933145, "DeclarationParser.UsingDeclarator" },
        { 5276324781484933146, "DeclarationParser.UsingEnumDeclaration" },
        { 5276324781484933147, "DeclarationParser.UsingDirective" },
        { 5276324781484933148, "DeclarationParser.StaticAssertDeclaration" },
        { 5276324781484933149, "DeclarationParser.StaticAssert" },
        { 5276324781484933150, "DeclarationParser.AliasDeclaration" },
        { 5276324781484933151, "DeclarationParser.DeclSpecifierSeq" },
        { 5276324781484933152, "DeclarationParser.Inline" },
        { 5276324781484933153, "DeclarationParser.DeclSpecifier" },
        { 5276324781484933154, "DeclarationParser.StorageClassSpecifier" },
        { 5276324781484933155, "DeclarationParser.FunctionSpecifier" },
        { 5276324781484933156, "DeclarationParser.ExplicitSpecifier" },
        { 5276324781484933157, "DeclarationParser.InitDeclaratorList" },
        { 5276324781484933158, "DeclarationParser.InitDeclarator" },
        { 5276324781484933159, "DeclarationParser.DeclaratorPushClassScope" },
        { 5276324781484933160, "DeclarationParser.Declarator" },
        { 5276324781484933161, "DeclarationParser.PtrDeclarator" },
        { 5276324781484933162, "DeclarationParser.NoPtrDeclarator" },
        { 5276324781484933163, "DeclarationParser.ParametersAndQualifiers" },
        { 5276324781484933164, "DeclarationParser.TrailingReturnType" },
        { 5276324781484933165, "DeclarationParser.PtrOperator" },
        { 5276324781484933166, "DeclarationParser.AbstractDeclarator" },
        { 5276324781484933167, "DeclarationParser.NoPtrAbstractDeclarator" },
        { 5276324781484933168, "DeclarationParser.PtrAbstractDeclarator" },
        { 5276324781484933169, "DeclarationParser.AbstractPackDeclarator" },
        { 5276324781484933170, "DeclarationParser.NoPtrAbstractPackDeclarator" },
        { 5276324781484933171, "DeclarationParser.DeclaratorId" },
        { 5276324781484933172, "DeclarationParser.Ptr" },
        { 5276324781484933173, "DeclarationParser.LvalueRef" },
        { 5276324781484933174, "DeclarationParser.RvalueRef" },
        { 5276324781484933175, "DeclarationParser.RefQualifier" },
        { 5276324781484933176, "DeclarationParser.CVQualifierSeq" },
        { 5276324781484933177, "DeclarationParser.CVQualifier" },
        { 5276324781484933178, "DeclarationParser.NoexceptSpecifier" },
        { 5276324781484933179, "DeclarationParser.ThrowSpecifier" },
        { 5276324781484933180, "DeclarationParser.AttributeDeclaration" },
        { 3876992812603932673, "EnumParser.EnumName" },
        { 3876992812603932674, "EnumParser.EnumSpecifier" },
        { 3876992812603932675, "EnumParser.EnumHead" },
        { 3876992812603932676, "EnumParser.EnumKey" },
        { 3876992812603932677, "EnumParser.EnumHeadName" },
        { 3876992812603932678, "EnumParser.EnumBase" },
        { 3876992812603932679, "EnumParser.EnumeratorList" },
        { 3876992812603932680, "EnumParser.EnumeratorDefinition" },
        { 3876992812603932681, "EnumParser.Enumerator" },
        { 3876992812603932682, "EnumParser.OpaqueEnumDeclaration" },
        { 3876992812603932683, "EnumParser.ElaboratedEnumSpecifier" },
        { 7352148961735475201, "ExpressionParser.Expression" },
        { 7352148961735475202, "ExpressionParser.ConstantExpression" },
        { 7352148961735475203, "ExpressionParser.AssignmentExpression" },
        { 7352148961735475204, "ExpressionParser.AssignmentOp" },
        { 7352148961735475205, "ExpressionParser.ConditionalExpression" },
        { 7352148961735475206, "ExpressionParser.YieldExpression" },
        { 7352148961735475207, "ExpressionParser.ThrowExpression" },
        { 7352148961735475208, "ExpressionParser.LogicalOrExpression" },
        { 7352148961735475209, "ExpressionParser.LogicalAndExpression" },
        { 7352148961735475210, "ExpressionParser.InclusiveOrExpression" },
        { 7352148961735475211, "ExpressionParser.ExclusiveOrExpression" },
        { 7352148961735475212, "ExpressionParser.AndExpression" },
        { 7352148961735475213, "ExpressionParser.EqualityExpression" },
        { 7352148961735475214, "ExpressionParser.EqualityOp" },
        { 7352148961735475215, "ExpressionParser.RelationalExpression" },
        { 7352148961735475216, "ExpressionParser.RelationalOp" },
        { 7352148961735475217, "ExpressionParser.CompareExpression" },
        { 7352148961735475218, "ExpressionParser.ShiftExpression" },
        { 7352148961735475219, "ExpressionParser.ShiftOp" },
        { 7352148961735475220, "ExpressionParser.AdditiveExpression" },
        { 7352148961735475221, "ExpressionParser.AdditiveOp" },
        { 7352148961735475222, "ExpressionParser.MultiplicativeExpression" },
        { 7352148961735475223, "ExpressionParser.MultiplicativeOp" },
        { 7352148961735475224, "ExpressionParser.PmExpression" },
        { 7352148961735475225, "ExpressionParser.PmOp" },
        { 7352148961735475226, "ExpressionParser.CastExpression" },
        { 7352148961735475227, "ExpressionParser.UnaryExpression" },
        { 7352148961735475228, "ExpressionParser.UnaryOp" },
        { 7352148961735475229, "ExpressionParser.AwaitExpression" },
        { 7352148961735475230, "ExpressionParser.SizeOfExpression" },
        { 7352148961735475231, "ExpressionParser.AlignOfExpression" },
        { 7352148961735475232, "ExpressionParser.NoexceptEpression" },
        { 7352148961735475233, "ExpressionParser.NewExpression" },
        { 7352148961735475234, "ExpressionParser.NewPlacement" },
        { 7352148961735475235, "ExpressionParser.NewInitializer" },
        { 7352148961735475236, "ExpressionParser.NewTypeId" },
        { 7352148961735475237, "ExpressionParser.NewDeclarator" },
        { 7352148961735475238, "ExpressionParser.NoPtrNewDeclarator" },
        { 7352148961735475239, "ExpressionParser.DeleteExpression" },
        { 7352148961735475240, "ExpressionParser.PostfixExpression" },
        { 7352148961735475241, "ExpressionParser.CppCastExpression" },
        { 7352148961735475242, "ExpressionParser.TypeIdExpression" },
        { 7352148961735475243, "ExpressionParser.IntrinsicInvokeExpr" },
        { 7352148961735475244, "ExpressionParser.PrimaryExpression" },
        { 7352148961735475245, "ExpressionParser.FoldExpression" },
        { 7352148961735475246, "ExpressionParser.FoldOp" },
        { 7352148961735475247, "ExpressionParser.ParenthesizedExpression" },
        { 7352148961735475248, "ExpressionParser.DotOp" },
        { 7352148961735475249, "ExpressionParser.ArrowOp" },
        { 7352148961735475250, "ExpressionParser.IdExpression" },
        { 7352148961735475251, "ExpressionParser.IdExpr" },
        { 7352148961735475252, "ExpressionParser.ExpressionList" },
        { 4456440676007018497, "FunctionParser.FunctionDefinition" },
        { 4456440676007018498, "FunctionParser.NoDeclSpecFunctionDefinition" },
        { 4456440676007018499, "FunctionParser.FunctionBody" },
        { 4456440676007018500, "FunctionParser.Default" },
        { 4456440676007018501, "FunctionParser.Delete" },
        { 4456440676007018502, "FunctionParser.ParameterDeclarationClause" },
        { 4456440676007018503, "FunctionParser.ParameterDeclarationList" },
        { 4456440676007018504, "FunctionParser.ParameterDeclaration" },
        { 4456440676007018505, "FunctionParser.OperatorFunctionId" },
        { 4456440676007018506, "FunctionParser.ConversionFunctionId" },
        { 4456440676007018507, "FunctionParser.DestructorId" },
        { 4456440676007018508, "FunctionParser.ConversionTypeId" },
        { 4456440676007018509, "FunctionParser.ConversionDeclarator" },
        { 4456440676007018510, "FunctionParser.OperatorKw" },
        { 4456440676007018511, "FunctionParser.Operator" },
        { 4456440676007018512, "FunctionParser.Noexcept" },
        { 4456440676007018513, "FunctionParser.FunctionTryBlock" },
        { 6068940122420674561, "GuardParser.ConceptGuard" },
        { 6068940122420674562, "GuardParser.NotDefiningTypeSpecifierGuard" },
        { 6068940122420674563, "GuardParser.AssumeTypeGuard" },
        { 6068940122420674564, "GuardParser.MemberFunctionGuard" },
        { 6068940122420674565, "GuardParser.SavedMemberFunctionBodyGuard" },
        { 6068940122420674566, "GuardParser.NoDeclSpecFunctionDeclarationGuard" },
        { 6068940122420674567, "GuardParser.NoDeclSpecFunctionDefinitionGuard" },
        { 7037905317291622401, "IdentifierParser.Identifier" },
        { 7037905317291622402, "IdentifierParser.UnqualifiedId" },
        { 7037905317291622403, "IdentifierParser.QualifiedId" },
        { 7037905317291622404, "IdentifierParser.Template" },
        { 7037905317291622405, "IdentifierParser.NestedNameSpecifier" },
        { 7037905317291622406, "IdentifierParser.IdentifierList" },
        { 7037905317291622407, "IdentifierParser.TypeIdentifier" },
        { 7037905317291622408, "IdentifierParser.TypeIdentifierUnchecked" },
        { 7037905317291622409, "IdentifierParser.TypeIdentifierChecked" },
        { 7037905317291622410, "IdentifierParser.Unnamed" },
        { 5255170298025607169, "InitializationParser.Initializer" },
        { 5255170298025607170, "InitializationParser.InitializerClause" },
        { 5255170298025607171, "InitializationParser.InitializerList" },
        { 5255170298025607172, "InitializationParser.DesignatedInitializerList" },
        { 5255170298025607173, "InitializationParser.DesignatedInitializerClause" },
        { 5255170298025607174, "InitializationParser.Designator" },
        { 5255170298025607175, "InitializationParser.ExprOrBracedInitList" },
        { 5255170298025607176, "InitializationParser.BraceOrEqualInitializer" },
        { 5255170298025607177, "InitializationParser.BracedInitList" },
        { 5939336778434478081, "LambdaParser.LambdaExpression" },
        { 5939336778434478082, "LambdaParser.LambdaIntroducer" },
        { 5939336778434478083, "LambdaParser.LambdaCapture" },
        { 5939336778434478084, "LambdaParser.CaptureDefault" },
        { 5939336778434478085, "LambdaParser.CaptureList" },
        { 5939336778434478086, "LambdaParser.Capture" },
        { 5939336778434478087, "LambdaParser.InitCapture" },
        { 5939336778434478088, "LambdaParser.SimpleCapture" },
        { 5939336778434478089, "LambdaParser.LambdaDeclarator" },
        { 5939336778434478090, "LambdaParser.LambdaSpecifiers" },
        { 5939336778434478091, "LambdaParser.LambdaTemplateParams" },
        { 7147880918433136641, "LiteralParser.Literal" },
        { 7147880918433136642, "LiteralParser.UserDefinedLiteral" },
        { 7147880918433136643, "LiteralParser.UdSuffix" },
        { 7147880918433136644, "LiteralParser.LiteralOperatorId" },
        { 7147880918433136645, "LiteralParser.StringLiteral" },
        { 6653537866360029185, "ModuleParser.ModuleDeclaration" },
        { 6653537866360029186, "ModuleParser.ModuleName" },
        { 6653537866360029187, "ModuleParser.ExportDeclaration" },
        { 6653537866360029188, "ModuleParser.ImportDeclaration" },
        { 6653537866360029189, "ModuleParser.ModulePartition" },
        { 6653537866360029190, "ModuleParser.ExportKeyword" },
        { 6653537866360029191, "ModuleParser.ImportKeyword" },
        { 6653537866360029192, "ModuleParser.ModuleKeyword" },
        { 6653537866360029193, "ModuleParser.GlobalModuleFragment" },
        { 6653537866360029194, "ModuleParser.PrivateModuleFragment" },
        { 6653537866360029195, "ModuleParser.HeaderName" },
        { 1949352228200382465, "ModuleDependencyParser.ModuleUnit" },
        { 1949352228200382466, "ModuleDependencyParser.GlobalModuleFragment" },
        { 1949352228200382467, "ModuleDependencyParser.DeclarationSeq" },
        { 1949352228200382468, "ModuleDependencyParser.Declaration" },
        { 1949352228200382469, "ModuleDependencyParser.ExportImportDeclaration" },
        { 7326029410182627329, "PunctuationParser.Semicolon" },
        { 7326029410182627330, "PunctuationParser.Comma" },
        { 7326029410182627331, "PunctuationParser.Quest" },
        { 7326029410182627332, "PunctuationParser.Colon" },
        { 7326029410182627333, "PunctuationParser.ColonColon" },
        { 7326029410182627334, "PunctuationParser.Ellipsis" },
        { 7326029410182627335, "PunctuationParser.LParen" },
        { 7326029410182627336, "PunctuationParser.RParen" },
        { 7326029410182627337, "PunctuationParser.LBracket" },
        { 7326029410182627338, "PunctuationParser.RBracket" },
        { 7326029410182627339, "PunctuationParser.LBrace" },
        { 7326029410182627340, "PunctuationParser.RBrace" },
        { 7326029410182627341, "PunctuationParser.Assign" },
        { 3815342804792508417, "SimpleTypeParser.SimpleType" },
        { 4943488507084537857, "StatementParser.Statement" },
        { 4943488507084537858, "StatementParser.LabeledStatement" },
        { 4943488507084537859, "StatementParser.CompoundStatementUnguarded" },
        { 4943488507084537860, "StatementParser.RBraceNext" },
        { 4943488507084537861, "StatementParser.CompoundStatementGuarded" },
        { 4943488507084537862, "StatementParser.CompoundStatementSaved" },
        { 4943488507084537863, "StatementParser.CompoundStatement" },
        { 4943488507084537864, "StatementParser.SelectionStatement" },
        { 4943488507084537865, "StatementParser.IfStatement" },
        { 4943488507084537866, "StatementParser.SwitchStatement" },
        { 4943488507084537867, "StatementParser.IterationStatement" },
        { 4943488507084537868, "StatementParser.WhileStatement" },
        { 4943488507084537869, "StatementParser.DoStatement" },
        { 4943488507084537870, "StatementParser.RangeForStatement" },
        { 4943488507084537871, "StatementParser.ForRangeDeclaration" },
        { 4943488507084537872, "StatementParser.ForRangeInitializer" },
        { 4943488507084537873, "StatementParser.ForStatement" },
        { 4943488507084537874, "StatementParser.JumpStatement" },
        { 4943488507084537875, "StatementParser.BreakStatement" },
        { 4943488507084537876, "StatementParser.ContinueStatement" },
        { 4943488507084537877, "StatementParser.ReturnStatement" },
        { 4943488507084537878, "StatementParser.CoroutineReturnStatement" },
        { 4943488507084537879, "StatementParser.GotoStatement" },
        { 4943488507084537880, "StatementParser.TryStatement" },
        { 4943488507084537881, "StatementParser.HandlerSeq" },
        { 4943488507084537882, "StatementParser.Handler" },
        { 4943488507084537883, "StatementParser.ExceptionDeclaration" },
        { 4943488507084537884, "StatementParser.DeclarationStatement" },
        { 4943488507084537885, "StatementParser.ExpressionStatement" },
        { 4943488507084537886, "StatementParser.InitStatement" },
        { 4943488507084537887, "StatementParser.Condition" },
        { 7965804375635394561, "TemplateParser.TemplateDeclaration" },
        { 7965804375635394562, "TemplateParser.TemplateHead" },
        { 7965804375635394563, "TemplateParser.TemplateParameterList" },
        { 7965804375635394564, "TemplateParser.TemplateParameter" },
        { 7965804375635394565, "TemplateParser.TypeParameter" },
        { 7965804375635394566, "TemplateParser.TypeParameterKey" },
        { 7965804375635394567, "TemplateParser.Typename" },
        { 7965804375635394568, "TemplateParser.Class" },
        { 7965804375635394569, "TemplateParser.TemplateId" },
        { 7965804375635394570, "TemplateParser.SimpleTemplateId" },
        { 7965804375635394571, "TemplateParser.TemplateName" },
        { 7965804375635394572, "TemplateParser.TemplateArgumentList" },
        { 7965804375635394573, "TemplateParser.TemplateArgument" },
        { 7965804375635394574, "TemplateParser.TemplateArgNext" },
        { 7965804375635394575, "TemplateParser.DeductionGuide" },
        { 7965804375635394576, "TemplateParser.Arrow" },
        { 7965804375635394577, "TemplateParser.ExplicitInstantiation" },
        { 7965804375635394578, "TemplateParser.ExplicitSpecialization" },
        { 7965804375635394579, "TemplateParser.Extern" },
        { 7965804375635394580, "TemplateParser.Template" },
        { 7135412954790363137, "TranslationUnitParser.TranslationUnit" },
        { 7135412954790363138, "TranslationUnitParser.ModuleUnit" },
        { 5708918577642340353, "TypeParser.TypeSpecifierSeq" },
        { 5708918577642340354, "TypeParser.TypeSpecifierSeqReset" },
        { 5708918577642340355, "TypeParser.DefiningTypeId" },
        { 5708918577642340356, "TypeParser.DefiningTypeSpecifierSeq" },
        { 5708918577642340357, "TypeParser.DefiningTypeSpecifierReset" },
        { 5708918577642340358, "TypeParser.DefiningTypeSpecifier" },
        { 5708918577642340359, "TypeParser.TypeSpecifier" },
        { 5708918577642340360, "TypeParser.ElaboratedTypeSpecifier" },
        { 5708918577642340361, "TypeParser.SimpleTypeSpecifierReset" },
        { 5708918577642340362, "TypeParser.SimpleTypeSpecifier" },
        { 5708918577642340363, "TypeParser.TypeName" },
        { 5708918577642340364, "TypeParser.TypeId" },
        { 5708918577642340365, "TypeParser.TypenameSpecifier" },
        { 5708918577642340366, "TypeParser.DeclTypeSpecifier" },
        { 5708918577642340367, "TypeParser.PlaceholderTypeSpecifier" }
    };
    return &ruleNameMap;
}

} // cpp20::parser::spg::rules
