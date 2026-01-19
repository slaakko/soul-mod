// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.build.gen_main_unit;

import util.code.formatter;
import otava.symbols.bound.tree;
import otava.symbols.context;
import otava.symbols.class_templates;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.declarator;
import otava.symbols.instantiator;
import otava.symbols.scope;
import otava.symbols.symbol.table;
import otava.symbols.statement.binder;
import otava.symbols.namespaces;
import otava.symbols.conversion.table;
import otava.symbols.compound.type.symbol;
import otava.symbols.templates;
import otava.symbols.declaration;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.type.symbol;
import otava.symbols.expression.binder;
import otava.symbols.error;
import otava.codegen;
import otava.ast.declaration;
import otava.ast.function;
import otava.ast.simple.type;
import otava.ast.identifier;
import otava.ast.statement;
import otava.ast.qualifier;
import otava.ast.expression;
import otava.ast.literal;
import otava.ast.punctuation;
import otava.ast.type;

namespace otava::build {

std::expected<std::string, int> GenerateMainWrapper(otava::symbols::Context* context, int numParams)
{
    /*  int __main_wrapper(int argc, const char** argv)
    *   {
    *           __global_init__();
    *           @retval = main(argc, argv);
    *           std::run_at_exits();
    *           return @retval;
    *   }
    */
    otava::ast::IdentifierNode* mainFn = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"main");
    otava::ast::InvokeExprNode* mainFnCall = new otava::ast::InvokeExprNode(soul::ast::SourcePos(), mainFn);
    if (numParams == 2)
    {
        otava::ast::IdentifierNode* argcNode = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"argc");
        auto rv = mainFnCall->AddNode(argcNode);
        if (!rv) return std::unexpected<int>(rv.error());
        otava::ast::IdentifierNode* argvNode = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"argv");
        rv = mainFnCall->AddNode(argvNode);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    otava::ast::IdentifierNode* retValDeclarator = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"@retval");
    otava::ast::DeclSpecifierSequenceNode* retValDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(soul::ast::SourcePos());
    auto rv = retValDeclSpecifiers->AddNode(new otava::ast::IntNode(soul::ast::SourcePos()));
    if (!rv) return std::unexpected<int>(rv.error());
    otava::ast::InitDeclaratorListNode* retValInitDeclarators = new otava::ast::InitDeclaratorListNode(soul::ast::SourcePos());
    otava::ast::InitDeclaratorNode* retValInitDeclarator = new otava::ast::InitDeclaratorNode(soul::ast::SourcePos(), retValDeclarator, mainFnCall);
    rv = retValInitDeclarators->AddNode(retValInitDeclarator);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::ast::SimpleDeclarationNode* retValDeclaration = new otava::ast::SimpleDeclarationNode(
        soul::ast::SourcePos(), retValDeclSpecifiers, retValInitDeclarators, nullptr, new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    otava::ast::DeclSpecifierSequenceNode* declSpecifiers = new otava::ast::DeclSpecifierSequenceNode(soul::ast::SourcePos());
    rv = declSpecifiers->AddNode(new otava::ast::IntNode(soul::ast::SourcePos()));
    if (!rv) return std::unexpected<int>(rv.error());
    otava::ast::CompoundStatementNode* body = new otava::ast::CompoundStatementNode(soul::ast::SourcePos());
    otava::ast::IdentifierNode* globalInitFn = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"__global_init__");
    otava::ast::InvokeExprNode* globalInitFnCall = new otava::ast::InvokeExprNode(soul::ast::SourcePos(), globalInitFn);
    otava::ast::ExpressionStatementNode* globalInitStmt = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), globalInitFnCall, nullptr,
        new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    rv = body->AddNode(globalInitStmt);
    if (!rv) return std::unexpected<int>(rv.error());
    rv = body->AddNode(retValDeclaration);
    if (!rv) return std::unexpected<int>(rv.error());
    std::expected<otava::ast::Node*, int> t = otava::symbols::MakeTypeNameNodes(soul::ast::SourcePos(), U"std::run_at_exits");
    if (!t) return std::unexpected<int>(t.error());
    otava::ast::Node* runAtExitsFn = *t;
    otava::ast::InvokeExprNode* runAtExitsFnCall = new otava::ast::InvokeExprNode(soul::ast::SourcePos(), runAtExitsFn);
    otava::ast::ExpressionStatementNode* runAtExitsStmt = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), runAtExitsFnCall, nullptr,
        new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    rv = body->AddNode(runAtExitsStmt);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::ast::IdentifierNode* retValVarId = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"@retval");
    otava::ast::ReturnStatementNode* returnRetValStmt = new otava::ast::ReturnStatementNode(soul::ast::SourcePos(), retValVarId, nullptr, nullptr, soul::ast::SourcePos());
    rv = body->AddNode(returnRetValStmt);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::ast::FunctionBodyNode* functionBody = new otava::ast::FunctionBodyNode(soul::ast::SourcePos(), body);
    otava::ast::ParameterListNode* parameters = new otava::ast::ParameterListNode(soul::ast::SourcePos());
    otava::ast::ParameterNode* argcParam = new otava::ast::ParameterNode(soul::ast::SourcePos());
    otava::ast::DeclSpecifierSequenceNode* argcDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(soul::ast::SourcePos());
    rv = argcDeclSpecifiers->AddNode(new otava::ast::IntNode(soul::ast::SourcePos()));
    if (!rv) return std::unexpected<int>(rv.error());
    argcParam->SetDeclSpecifiers(argcDeclSpecifiers);
    argcParam->SetDeclarator(new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"argc"));
    rv = parameters->AddNode(argcParam);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::ast::ParameterNode* argvParam = new otava::ast::ParameterNode(soul::ast::SourcePos());
    otava::ast::DeclSpecifierSequenceNode* argvDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(soul::ast::SourcePos());
    rv = argvDeclSpecifiers->AddNode(new otava::ast::ConstNode(soul::ast::SourcePos()));
    if (!rv) return std::unexpected<int>(rv.error());
    rv = argvDeclSpecifiers->AddNode(new otava::ast::CharNode(soul::ast::SourcePos()));
    if (!rv) return std::unexpected<int>(rv.error());
    argvParam->SetDeclSpecifiers(argvDeclSpecifiers);
    otava::ast::PtrDeclaratorNode* argvDeclarator = new otava::ast::PtrDeclaratorNode(soul::ast::SourcePos());
    rv = argvDeclarator->AddNode(new otava::ast::PtrOperatorNode(soul::ast::SourcePos(), new otava::ast::PtrNode(soul::ast::SourcePos())));
    if (!rv) return std::unexpected<int>(rv.error());
    rv = argvDeclarator->AddNode(new otava::ast::PtrOperatorNode(soul::ast::SourcePos(), new otava::ast::PtrNode(soul::ast::SourcePos())));
    if (!rv) return std::unexpected<int>(rv.error());
    rv = argvDeclarator->AddNode(new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"argv"));
    if (!rv) return std::unexpected<int>(rv.error());
    argvParam->SetDeclarator(argvDeclarator);
    rv = parameters->AddNode(argvParam);
    if (!rv) return std::unexpected<int>(rv.error());
    otava::ast::FunctionDeclaratorNode* declarator = new otava::ast::FunctionDeclaratorNode(soul::ast::SourcePos(),
        new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"__main_wrapper__"), parameters);
    std::unique_ptr<otava::ast::FunctionDefinitionNode> mainWrapperFn(new otava::ast::FunctionDefinitionNode(soul::ast::SourcePos(), nullptr, declSpecifiers, 
        declarator, nullptr, functionBody));
    otava::symbols::InstantiationScope instantiationScope(context->GetSymbolTable()->CurrentScope());
    otava::symbols::Instantiator instantiator(context, &instantiationScope);
    context->PushSetFlag(otava::symbols::ContextFlags::saveDeclarations | otava::symbols::ContextFlags::dontBind | otava::symbols::ContextFlags::generateMainWrapper);
    instantiator.SetFunctionNode(mainWrapperFn.get());
    mainWrapperFn->Accept(instantiator);
    context->PopFlags();
    otava::symbols::FunctionSymbol* mainWrapperFnSymbol = instantiator.GetSpecialization();
    if (mainWrapperFnSymbol && mainWrapperFnSymbol->IsFunctionDefinitionSymbol())
    {
        otava::symbols::FunctionDefinitionSymbol* mainWrapperFnDefSymbol = static_cast<otava::symbols::FunctionDefinitionSymbol*>(mainWrapperFnSymbol);
        context->PushBoundFunction(new otava::symbols::BoundFunctionNode(mainWrapperFnDefSymbol, soul::ast::SourcePos()));
        std::expected<otava::symbols::FunctionDefinitionSymbol*, int> fn = otava::symbols::BindFunction(mainWrapperFn.get(), mainWrapperFnDefSymbol, context);
        if (!fn) return std::unexpected<int>(fn.error());
        mainWrapperFnDefSymbol = *fn;
        rv = context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<otava::symbols::BoundNode>(context->ReleaseBoundFunction()), context);
        if (!rv) return std::unexpected<int>(rv.error());
        context->PopBoundFunction();
        std::expected<std::string, int> irn = mainWrapperFnDefSymbol->IrName(context);
        if (!irn) return std::unexpected<int>(irn.error());
        std::string irName = std::move(*irn);
        return irName;
    }
    else
    {
        return otava::symbols::Error("error instantiating main wrapper: function definition symbol expected", soul::ast::SourcePos(), context);
    }
}

std::expected<std::string, int> GenerateMainUnit(
    otava::symbols::ModuleMapper& moduleMapper, const std::string& mainFilePath, const std::string& mainFunctionIrName, int numParams,
    const std::vector<std::string>& compileUnitInitFnNames, const std::string& config, int optLevel)
{
    std::expected<otava::symbols::Module*, int> m = moduleMapper.GetModule("std.core", config, optLevel);
    if (!m) return std::unexpected<int>(m.error());
    otava::symbols::Module* core = *m;
    otava::symbols::Module main("main");
    std::unique_ptr<otava::symbols::SymbolTable> symbolTable(new otava::symbols::SymbolTable());
    symbolTable->SetModule(&main);
    auto rv = symbolTable->Import(*core->GetSymbolTable(), moduleMapper.GetFunctionDefinitionSymbolSet());
    if (!rv) return std::unexpected<int>(rv.error());
    otava::symbols::Emitter emitter;
    otava::symbols::Context context;
    context.SetEmitter(&emitter);
    context.SetFunctionDefinitionSymbolSet(moduleMapper.GetFunctionDefinitionSymbolSet());
    context.SetSymbolTable(symbolTable.get());
    if (config == "release")
    {
        std::string fp = util::Path::GetDirectoryName(util::Path::GetDirectoryName(util::Path::GetDirectoryName(mainFilePath)));
        std::string fn = util::Path::GetFileName(mainFilePath);
        context.SetFileName(util::Path::Combine(fp, fn));
    }
    else
    {
        std::string fp = util::Path::GetDirectoryName(util::Path::GetDirectoryName(mainFilePath));
        std::string fn = util::Path::GetFileName(mainFilePath);
        context.SetFileName(util::Path::Combine(fp, fn));
    }
    context.GetBoundCompileUnit()->SetId("main_unit");
    std::expected<otava::symbols::FunctionSymbol*, int> f = context.GetSymbolTable()->AddFunction(U"__global_init__", std::vector<otava::symbols::TypeSymbol*>(), nullptr,
        otava::symbols::FunctionKind::function, otava::symbols::FunctionQualifiers::none, otava::symbols::DeclarationFlags::none, &context);
    if (!f) return std::unexpected<int>(f.error());
    otava::symbols::FunctionSymbol * globalInitFn = *f;
    globalInitFn->SetLinkage(otava::symbols::Linkage::c_linkage);
    f = context.GetSymbolTable()->AddFunction(U"main", std::vector<otava::symbols::TypeSymbol*>(), nullptr,
        otava::symbols::FunctionKind::function, otava::symbols::FunctionQualifiers::none, otava::symbols::DeclarationFlags::none, &context);
    if (!f) return std::unexpected<int>(f.error());
    otava::symbols::FunctionSymbol * mainFn = *f;
    std::expected<otava::symbols::TypeSymbol*, int> t = context.GetSymbolTable()->GetFundamentalTypeSymbol(otava::symbols::FundamentalTypeKind::intType);
    if (!t) return std::unexpected<int>(t.error());
    otava::symbols::TypeSymbol* intType = *t;
    rv = mainFn->SetReturnType(intType, &context);
    if (!rv) return std::unexpected<int>(rv.error());
    if (numParams == 2)
    {
        otava::symbols::ParameterSymbol* argcParam = context.GetSymbolTable()->CreateParameter(U"argc", nullptr, intType, &context);
        rv = mainFn->AddSymbol(argcParam, soul::ast::SourcePos(), &context);
        if (!rv) return std::unexpected<int>(rv.error());
        t = context.GetSymbolTable()->GetFundamentalTypeSymbol(otava::symbols::FundamentalTypeKind::charType);
        if (!t) return std::unexpected<int>(t.error());
        otava::symbols::TypeSymbol* charType = *t;
        t = charType->AddConst(&context);
        if (!t) return std::unexpected<int>(t.error());
        otava::symbols::TypeSymbol* constCharType = *t;
        t = constCharType->AddPointer(&context);
        if (!t) return std::unexpected<int>(t.error());
        otava::symbols::TypeSymbol* constCharPtrType = *t;
        t = constCharPtrType->AddPointer(&context);
        if (!t) return std::unexpected<int>(t.error());
        otava::symbols::TypeSymbol* constCharPtrPtrType = *t;
        otava::symbols::ParameterSymbol* argvParam = context.GetSymbolTable()->CreateParameter(U"argv", nullptr, constCharPtrPtrType, &context);
        rv = mainFn->AddSymbol(argvParam, soul::ast::SourcePos(), &context);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    std::expected<std::string, int> w = GenerateMainWrapper(&context, numParams);
    if (!w) return std::unexpected<int>(w.error());
    std::string mainWrapperIrName = *w;
    int np = numParams;
    std::expected<std::string, int> a = otava::codegen::GenerateCode(context, config, optLevel, true, mainWrapperIrName, np, true, compileUnitInitFnNames);
    if (!a) return std::unexpected<int>(a.error());
    std::string asmFilename = *a;
    std::ofstream mainFile(mainFilePath);
    if (!mainFile) return std::unexpected<int>(util::AllocateError("could not create file '" + mainFilePath + "'"));
    util::CodeFormatter formatter(mainFile);
    formatter.WriteLine("extern \"C\" void ort_init();");
    formatter.WriteLine("extern \"C\" void ort_done();");
    formatter.WriteLine("extern \"C\" int " + mainWrapperIrName + "(int argc, const char** argv); ");
    formatter.WriteLine();
    formatter.WriteLine("int main(int argc, const char** argv)");
    formatter.WriteLine("{");
    formatter.IncIndent();
    if (numParams == 0 || numParams == 2)
    {
        formatter.WriteLine("ort_init();");
        formatter.WriteLine("int retVal = " + mainWrapperIrName + "(argc, argv);");
        formatter.WriteLine("ort_done();");
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("invalid number of main function parameters"));
    }
    formatter.WriteLine("return retVal;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    return std::expected<std::string, int>(asmFilename);
}

} // namespace otava::build
