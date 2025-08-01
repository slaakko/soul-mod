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
import otava.symbols.exception;
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

std::string GenerateMainWrapper(otava::symbols::Context* context, int numParams)
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
        mainFnCall->AddNode(argcNode);
        otava::ast::IdentifierNode* argvNode = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"argv");
        mainFnCall->AddNode(argvNode);
    }
    otava::ast::IdentifierNode* retValDeclarator = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"@retval");
    otava::ast::DeclSpecifierSequenceNode* retValDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(soul::ast::SourcePos());
    retValDeclSpecifiers->AddNode(new otava::ast::IntNode(soul::ast::SourcePos()));
    otava::ast::InitDeclaratorListNode* retValInitDeclarators = new otava::ast::InitDeclaratorListNode(soul::ast::SourcePos());
    otava::ast::InitDeclaratorNode* retValInitDeclarator = new otava::ast::InitDeclaratorNode(soul::ast::SourcePos(), retValDeclarator, mainFnCall);
    retValInitDeclarators->AddNode(retValInitDeclarator);
    otava::ast::SimpleDeclarationNode* retValDeclaration = new otava::ast::SimpleDeclarationNode(
        soul::ast::SourcePos(), retValDeclSpecifiers, retValInitDeclarators, nullptr, new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    otava::ast::DeclSpecifierSequenceNode* declSpecifiers = new otava::ast::DeclSpecifierSequenceNode(soul::ast::SourcePos());
    declSpecifiers->AddNode(new otava::ast::IntNode(soul::ast::SourcePos()));
    otava::ast::CompoundStatementNode* body = new otava::ast::CompoundStatementNode(soul::ast::SourcePos());
    otava::ast::IdentifierNode* globalInitFn = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"__global_init__");
    otava::ast::InvokeExprNode* globalInitFnCall = new otava::ast::InvokeExprNode(soul::ast::SourcePos(), globalInitFn);
    otava::ast::ExpressionStatementNode* globalInitStmt = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), globalInitFnCall, nullptr, 
        new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    body->AddNode(globalInitStmt);
    body->AddNode(retValDeclaration);
    otava::ast::Node* runAtExitsFn = otava::symbols::MakeTypeNameNodes(soul::ast::SourcePos(), U"std::run_at_exits");
    otava::ast::InvokeExprNode* runAtExitsFnCall = new otava::ast::InvokeExprNode(soul::ast::SourcePos(), runAtExitsFn);
    otava::ast::ExpressionStatementNode* runAtExitsStmt = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), runAtExitsFnCall, nullptr,
        new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    body->AddNode(runAtExitsStmt);
    otava::ast::IdentifierNode* retValVarId = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"@retval");
    otava::ast::ReturnStatementNode* returnRetValStmt = new otava::ast::ReturnStatementNode(soul::ast::SourcePos(), retValVarId, nullptr, nullptr, soul::ast::SourcePos());
    body->AddNode(returnRetValStmt);
    otava::ast::FunctionBodyNode* functionBody = new otava::ast::FunctionBodyNode(soul::ast::SourcePos(), body);
    otava::ast::ParameterListNode* parameters = new otava::ast::ParameterListNode(soul::ast::SourcePos());
    otava::ast::ParameterNode* argcParam = new otava::ast::ParameterNode(soul::ast::SourcePos());
    otava::ast::DeclSpecifierSequenceNode* argcDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(soul::ast::SourcePos());
    argcDeclSpecifiers->AddNode(new otava::ast::IntNode(soul::ast::SourcePos()));
    argcParam->SetDeclSpecifiers(argcDeclSpecifiers);
    argcParam->SetDeclarator(new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"argc"));
    parameters->AddNode(argcParam);
    otava::ast::ParameterNode* argvParam = new otava::ast::ParameterNode(soul::ast::SourcePos());
    otava::ast::DeclSpecifierSequenceNode* argvDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(soul::ast::SourcePos());
    argvDeclSpecifiers->AddNode(new otava::ast::ConstNode(soul::ast::SourcePos()));
    argvDeclSpecifiers->AddNode(new otava::ast::CharNode(soul::ast::SourcePos()));
    argvParam->SetDeclSpecifiers(argvDeclSpecifiers);
    otava::ast::PtrDeclaratorNode* argvDeclarator = new otava::ast::PtrDeclaratorNode(soul::ast::SourcePos());
    argvDeclarator->AddNode(new otava::ast::PtrOperatorNode(soul::ast::SourcePos(), new otava::ast::PtrNode(soul::ast::SourcePos())));
    argvDeclarator->AddNode(new otava::ast::PtrOperatorNode(soul::ast::SourcePos(), new otava::ast::PtrNode(soul::ast::SourcePos())));
    argvDeclarator->AddNode(new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"argv"));
    argvParam->SetDeclarator(argvDeclarator);
    parameters->AddNode(argvParam);
    otava::ast::FunctionDeclaratorNode* declarator = new otava::ast::FunctionDeclaratorNode(soul::ast::SourcePos(),
        new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"__main_wrapper__"), parameters);
    std::unique_ptr<otava::ast::FunctionDefinitionNode> mainWrapperFn(new otava::ast::FunctionDefinitionNode(soul::ast::SourcePos(), nullptr, declSpecifiers, declarator, nullptr, 
        functionBody));
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
        otava::symbols::BindFunction(mainWrapperFn.get(), mainWrapperFnDefSymbol, context);
        context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<otava::symbols::BoundNode>(context->ReleaseBoundFunction()), context);
        context->PopBoundFunction();
        return mainWrapperFnDefSymbol->IrName(context);
    }
    else
    {
        otava::symbols::ThrowException("error instantiating main wrapper: function definition symbol expected", soul::ast::SourcePos(), context);
    }
}

std::string GenerateMainUnit(otava::symbols::ModuleMapper& moduleMapper, const std::string& mainFilePath, const std::string& mainFunctionIrName, int numParams, 
    const std::vector<std::string>& compileUnitInitFnNames, const std::string& config)
{
    otava::symbols::Module* core = moduleMapper.GetModule("std.core", config);
    otava::symbols::Module main("main");
    std::unique_ptr<otava::symbols::SymbolTable> symbolTable(new otava::symbols::SymbolTable());
    symbolTable->SetModule(&main);
    symbolTable->Import(*core->GetSymbolTable(), moduleMapper.GetFunctionDefinitionSymbolSet());
    otava::symbols::Context context;
    context.SetFunctionDefinitionSymbolSet(moduleMapper.GetFunctionDefinitionSymbolSet());
    context.SetSymbolTable(symbolTable.get());
    context.SetFileName((std::filesystem::path(mainFilePath).parent_path().parent_path() / std::filesystem::path(mainFilePath).filename()).generic_string());
    context.GetBoundCompileUnit()->SetId("main_unit");
    otava::symbols::FunctionSymbol* globalInitFn = context.GetSymbolTable()->AddFunction(U"__global_init__", std::vector<otava::symbols::TypeSymbol*>(), nullptr, 
        otava::symbols::FunctionKind::function, otava::symbols::FunctionQualifiers::none, otava::symbols::DeclarationFlags::none, &context);
    globalInitFn->SetLinkage(otava::symbols::Linkage::c_linkage);
    otava::symbols::FunctionSymbol* mainFn = context.GetSymbolTable()->AddFunction(U"main", std::vector<otava::symbols::TypeSymbol*>(), nullptr,
        otava::symbols::FunctionKind::function, otava::symbols::FunctionQualifiers::none, otava::symbols::DeclarationFlags::none, &context);
    otava::symbols::TypeSymbol* intType = context.GetSymbolTable()->GetFundamentalTypeSymbol(otava::symbols::FundamentalTypeKind::intType);
    mainFn->SetReturnType(intType, &context);
    if (numParams == 2)
    {
        otava::symbols::TypeSymbol* intType = context.GetSymbolTable()->GetFundamentalTypeSymbol(otava::symbols::FundamentalTypeKind::intType);
        otava::symbols::ParameterSymbol* argcParam = context.GetSymbolTable()->CreateParameter(U"argc", nullptr, intType, &context);
        mainFn->AddSymbol(argcParam, soul::ast::SourcePos(), &context);
        otava::symbols::TypeSymbol* constCharPtrPtrType = context.GetSymbolTable()->GetFundamentalTypeSymbol(
            otava::symbols::FundamentalTypeKind::charType)->AddConst(&context)->AddPointer(&context)->AddPointer(&context);
        otava::symbols::ParameterSymbol* argvParam = context.GetSymbolTable()->CreateParameter(U"argv", nullptr, constCharPtrPtrType, &context);
        mainFn->AddSymbol(argvParam, soul::ast::SourcePos(), &context);
    }
    std::string mainWrapperIrName = GenerateMainWrapper(&context, numParams);
    int np = numParams;
    std::string asmFilename = otava::codegen::GenerateCode(context, config, true, mainWrapperIrName, np, true, compileUnitInitFnNames);
    std::ofstream mainFile(mainFilePath);
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
        throw std::runtime_error("invalid number of main function parameters");
    }
    formatter.WriteLine("return retVal;");
    formatter.DecIndent();
    formatter.WriteLine("}");
    return asmFilename;
}

} // namespace otava::build

