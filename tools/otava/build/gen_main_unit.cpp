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
// import std.filesystem;

namespace otava::build {

std::string GenerateMainWrapper(otava::symbols::Context* context, int numParams)
{
/*  int __main_wrapper(int argc, const char** argv)
*   {
*       try
*       {
*           __global_init__();
*           @retval = main(argc, argv);
*           std::run_at_exits();
*           return @retval;
*       }
*       catch (const std::exception& ex)
*       {
*           std::cerr << "unhandled exception escaped from main:";
*           std::cerr << ex.what();
*           std::cerr << "\n";
*           return 1;
*       }
*       catch (...)
*       {
*           std::cerr << "unhandled unknown exception escaped from main.";
*           std::cerr << "\n";
*           return 1;
*       }
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
    otava::ast::CompoundStatementNode* tryBlock = new otava::ast::CompoundStatementNode(soul::ast::SourcePos());
    otava::ast::IdentifierNode* globalInitFn = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"__global_init__");
    otava::ast::InvokeExprNode* globalInitFnCall = new otava::ast::InvokeExprNode(soul::ast::SourcePos(), globalInitFn);
    otava::ast::ExpressionStatementNode* globalInitStmt = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), globalInitFnCall, nullptr, 
        new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    tryBlock->AddNode(globalInitStmt);
    tryBlock->AddNode(retValDeclaration);
    otava::ast::Node* runAtExitsFn = otava::symbols::MakeTypeNameNodes(soul::ast::SourcePos(), U"std::run_at_exits");
    otava::ast::InvokeExprNode* runAtExitsFnCall = new otava::ast::InvokeExprNode(soul::ast::SourcePos(), runAtExitsFn);
    otava::ast::ExpressionStatementNode* runAtExitsStmt = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), runAtExitsFnCall, nullptr,
        new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    tryBlock->AddNode(runAtExitsStmt);
    otava::ast::IdentifierNode* retValVarId = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"@retval");
    otava::ast::ReturnStatementNode* returnRetValStmt = new otava::ast::ReturnStatementNode(soul::ast::SourcePos(), retValVarId, nullptr, nullptr, soul::ast::SourcePos());
    tryBlock->AddNode(returnRetValStmt);
    otava::ast::HandlerSequenceNode* handlers = new otava::ast::HandlerSequenceNode(soul::ast::SourcePos());
    otava::ast::CompoundStatementNode* catchStdExceptionBlock = new otava::ast::CompoundStatementNode(soul::ast::SourcePos());
    otava::ast::Node* stdCerr = otava::symbols::MakeTypeNameNodes(soul::ast::SourcePos(), U"std::cerr");
    otava::ast::BinaryExprNode* printMsg = new otava::ast::BinaryExprNode(soul::ast::SourcePos(), new otava::ast::ShiftLeftNode(soul::ast::SourcePos()), stdCerr->Clone(),
        new otava::ast::StringLiteralNode(soul::ast::SourcePos(), U"unhandled exception escaped from main: ", otava::ast::EncodingPrefix::none, U"unhandled exception escaped from main: "));
    otava::ast::ExpressionStatementNode* printMsgStmt = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), printMsg, nullptr, 
        new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    catchStdExceptionBlock->AddNode(printMsgStmt);
    otava::ast::BinaryExprNode* printNl = new otava::ast::BinaryExprNode(soul::ast::SourcePos(), new otava::ast::ShiftLeftNode(soul::ast::SourcePos()), stdCerr->Clone(),
        new otava::ast::StringLiteralNode(soul::ast::SourcePos(), U"\n", otava::ast::EncodingPrefix::none, U"\\n"));
    otava::ast::ExpressionStatementNode* printNlStmt = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), printNl, nullptr,
        new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    catchStdExceptionBlock->AddNode(printNlStmt);
    otava::ast::MemberExprNode* exWhat = new otava::ast::MemberExprNode(soul::ast::SourcePos(), new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"ex"),
        new otava::ast::DotNode(soul::ast::SourcePos()), new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"what"));
    otava::ast::InvokeExprNode* invokeExWhat = new otava::ast::InvokeExprNode(soul::ast::SourcePos(), exWhat);
    otava::ast::BinaryExprNode* printExExpr = new otava::ast::BinaryExprNode(soul::ast::SourcePos(), new otava::ast::ShiftLeftNode(soul::ast::SourcePos()), stdCerr, invokeExWhat);
    otava::ast::ExpressionStatementNode* printExStmt = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), printExExpr, nullptr, 
        new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    catchStdExceptionBlock->AddNode(printExStmt);
    catchStdExceptionBlock->AddNode(printNlStmt->Clone());
    otava::ast::ReturnStatementNode* returnStmt = new otava::ast::ReturnStatementNode(soul::ast::SourcePos(), new otava::ast::IntegerLiteralNode(soul::ast::SourcePos(), 1, 
        otava::ast::Suffix::none, otava::ast::Base::decimal, U"1"), nullptr, new otava::ast::SemicolonNode(soul::ast::SourcePos()), soul::ast::SourcePos());
    catchStdExceptionBlock->AddNode(returnStmt);
    otava::ast::Node* stdExceptionId = otava::symbols::MakeTypeNameNodes(soul::ast::SourcePos(), U"std::exception");
    otava::ast::TypeSpecifierSequenceNode* stdExceptionType = new otava::ast::TypeSpecifierSequenceNode(soul::ast::SourcePos());
    stdExceptionType->AddNode(new otava::ast::ConstNode(soul::ast::SourcePos()));
    stdExceptionType->AddNode(stdExceptionId);
    otava::ast::PtrDeclaratorNode* stdExceptionDeclarator = new otava::ast::PtrDeclaratorNode(soul::ast::SourcePos());
    stdExceptionDeclarator->AddNode(new otava::ast::LvalueRefNode(soul::ast::SourcePos()));
    stdExceptionDeclarator->AddNode(new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"ex"));
    otava::ast::ExceptionDeclarationNode* stdExceptionDecl = new otava::ast::ExceptionDeclarationNode(soul::ast::SourcePos(), stdExceptionType,
        stdExceptionDeclarator, nullptr, nullptr);
    otava::ast::HandlerNode* stdExceptionHandler = new otava::ast::HandlerNode(soul::ast::SourcePos(), stdExceptionDecl, catchStdExceptionBlock, 
        soul::ast::SourcePos(), soul::ast::SourcePos());
    handlers->AddNode(stdExceptionHandler);
    otava::ast::CompoundStatementNode* catchAllExceptionBlock = new otava::ast::CompoundStatementNode(soul::ast::SourcePos());
    otava::ast::BinaryExprNode* printAllMsg = new otava::ast::BinaryExprNode(soul::ast::SourcePos(), new otava::ast::ShiftLeftNode(soul::ast::SourcePos()), stdCerr->Clone(),
        new otava::ast::StringLiteralNode(soul::ast::SourcePos(), U"unhandled unknown exception escaped from main", otava::ast::EncodingPrefix::none, 
            U"unhandled unknown exception escaped from main"));
    otava::ast::ExpressionStatementNode* printAllMsgStmt = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), printAllMsg, nullptr, 
        new otava::ast::SemicolonNode(soul::ast::SourcePos()));
    catchAllExceptionBlock->AddNode(printAllMsgStmt);
    catchAllExceptionBlock->AddNode(returnStmt->Clone());
    otava::ast::ExceptionDeclarationNode* allExceptionDecl = new otava::ast::ExceptionDeclarationNode(soul::ast::SourcePos(), nullptr,
        nullptr, new otava::ast::EllipsisNode(soul::ast::SourcePos()), nullptr);
    otava::ast::HandlerNode* allHandler = new otava::ast::HandlerNode(soul::ast::SourcePos(), allExceptionDecl, catchAllExceptionBlock,
        soul::ast::SourcePos(), soul::ast::SourcePos());
    handlers->AddNode(allHandler);
    otava::ast::TryStatementNode* tryStmt = new otava::ast::TryStatementNode(soul::ast::SourcePos(), tryBlock, handlers, nullptr, soul::ast::SourcePos());
    body->AddNode(tryStmt);
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
    otava::symbols::Module* core = moduleMapper.GetModule("std.core");
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
    formatter.WriteLine("extern \"C\" int " + mainWrapperIrName + "(int argc, const char** argv); ");
    formatter.WriteLine();
    formatter.WriteLine("int main(int argc, const char** argv)");
    formatter.WriteLine("{");
    formatter.IncIndent();
    if (numParams == 0 || numParams == 2)
    {
        formatter.WriteLine("int retVal = " + mainWrapperIrName + "(argc, argv);");
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

