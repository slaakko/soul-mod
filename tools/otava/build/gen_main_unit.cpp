// =================================
// Copyright (c) 2022 Seppo Laakko
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
import otava.codegen;
import otava.ast.declaration;
import otava.ast.function;
import otava.ast.simple.type;
import otava.ast.identifier;
import otava.ast.statement;
import otava.ast.qualifier;
import otava.ast.expression;
import std.filesystem;

namespace otava::build {

std::string GenerateMainWrapper(otava::symbols::Context* context)
{
    otava::ast::DeclSpecifierSequenceNode* declSpecifiers = new otava::ast::DeclSpecifierSequenceNode(soul::ast::SourcePos());
    declSpecifiers->AddNode(new otava::ast::IntNode(soul::ast::SourcePos()));
    otava::ast::CompoundStatementNode* body = new otava::ast::CompoundStatementNode(soul::ast::SourcePos());
    otava::ast::CompoundStatementNode* tryBlock = new otava::ast::CompoundStatementNode(soul::ast::SourcePos());
    otava::ast::IdentifierNode* globalInitFn = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"__global_init__");
    otava::ast::InvokeExprNode* globalInitFnCall = new otava::ast::InvokeExprNode(soul::ast::SourcePos(), globalInitFn);
    otava::ast::ExpressionStatementNode* globalInitStmt = new otava::ast::ExpressionStatementNode(soul::ast::SourcePos(), globalInitFnCall, nullptr, nullptr);
    tryBlock->AddNode(globalInitStmt);
    otava::ast::IdentifierNode* mainFn = new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"main");
    otava::ast::InvokeExprNode* mainFnCall = new otava::ast::InvokeExprNode(soul::ast::SourcePos(), mainFn);
    otava::ast::ReturnStatementNode* mainCallStmt = new otava::ast::ReturnStatementNode(soul::ast::SourcePos(), mainFnCall, nullptr, nullptr, soul::ast::SourcePos());
    tryBlock->AddNode(mainCallStmt);
    otava::ast::HandlerSequenceNode* handlers = new otava::ast::HandlerSequenceNode(soul::ast::SourcePos());
    otava::ast::NestedNameSpecifierNode* stdNns = new otava::ast::NestedNameSpecifierNode(soul::ast::SourcePos());
    stdNns->AddNode(new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"std"));
    stdNns->AddNode(new otava::ast::ColonColonNode(soul::ast::SourcePos()));
    otava::ast::CompoundStatementNode* catchStdExceptionBlock = new otava::ast::CompoundStatementNode(soul::ast::SourcePos());
    otava::ast::QualifiedIdNode* stdExceptionId = new otava::ast::QualifiedIdNode(soul::ast::SourcePos(), stdNns, new otava::ast::IdentifierNode(soul::ast::SourcePos(), U"exception"));
    otava::ast::HandlerNode* stdExceptionHandler = new otava::ast::HandlerNode(soul::ast::SourcePos(), stdExceptionId, catchStdExceptionBlock, soul::ast::SourcePos(), soul::ast::SourcePos());
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
    mainWrapperFn->Accept(instantiator);
    context->PopFlags();
    otava::symbols::FunctionDefinitionSymbol* mainWrapperFnSymbol = context->GetSpecialization();
    context->PushBoundFunction(new otava::symbols::BoundFunctionNode(mainWrapperFnSymbol, soul::ast::SourcePos()));
    otava::symbols::BindFunction(mainWrapperFn.get(), mainWrapperFnSymbol, context);
    context->GetBoundCompileUnit()->AddBoundNode(context->ReleaseBoundFunction());
    context->PopBoundFunction();
    return mainWrapperFnSymbol->IrName(context);
}

std::string GenerateMainUnit(otava::symbols::ModuleMapper& moduleMapper, const std::string& mainFilePath, const std::string& mainFunctionIrName, int numParams, 
    const std::vector<std::string>& compileUnitInitFnNames, const std::string& config)
{
    otava::symbols::Module* fundamentalTypes = moduleMapper.GetModule("std.type.fundamental");
    std::unique_ptr<otava::symbols::SymbolTable> symbolTable(new otava::symbols::SymbolTable());
    symbolTable->Import(*fundamentalTypes->GetSymbolTable());
    otava::symbols::Context context;
    context.SetSymbolTable(symbolTable.get());
    context.SetFileName((std::filesystem::path(mainFilePath).parent_path().parent_path() / std::filesystem::path(mainFilePath).filename()).generic_string());
    context.GetBoundCompileUnit()->SetId("main_unit");
    otava::symbols::FunctionSymbol* globalInitFn = context.GetSymbolTable()->AddFunction(U"__global_init__", nullptr, 
        otava::symbols::FunctionKind::function, otava::symbols::FunctionQualifiers::none, otava::symbols::DeclarationFlags::none, &context);
    globalInitFn->SetLinkage(otava::symbols::Linkage::c_linkage);
    otava::symbols::FunctionSymbol* mainFn = context.GetSymbolTable()->AddFunction(U"main", nullptr, 
        otava::symbols::FunctionKind::function, otava::symbols::FunctionQualifiers::none, otava::symbols::DeclarationFlags::none, &context);
    otava::symbols::TypeSymbol* intType = context.GetSymbolTable()->GetFundamentalTypeSymbol(otava::symbols::FundamentalTypeKind::intType);
    mainFn->SetReturnType(intType, &context);
    if (numParams == 2)
    {
        otava::symbols::TypeSymbol* intType = context.GetSymbolTable()->GetFundamentalTypeSymbol(otava::symbols::FundamentalTypeKind::intType);
        otava::symbols::ParameterSymbol* argcParam = context.GetSymbolTable()->CreateParameter(U"argc", nullptr, intType, &context);
        mainFn->AddSymbol(argcParam, soul::ast::SourcePos(), &context);
        otava::symbols::TypeSymbol* charPtrPtrType = context.GetSymbolTable()->GetFundamentalTypeSymbol(
            otava::symbols::FundamentalTypeKind::charType)->AddConst(&context)->AddPointer(&context)->AddPointer(&context);
        otava::symbols::ParameterSymbol* argvParam = context.GetSymbolTable()->CreateParameter(U"argv", nullptr, charPtrPtrType, &context);
        mainFn->AddSymbol(argvParam, soul::ast::SourcePos(), &context);
    }
    std::string mainWrapperIrName = GenerateMainWrapper(&context);
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

