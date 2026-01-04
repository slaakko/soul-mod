// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.exception_handling;

import otava.symbols.stmt.parser;
import otava.symbols.context;
import otava.symbols.statement.binder;
import otava.symbols.variable.symbol;
import otava.symbols.type.symbol;
import otava.symbols.function.symbol;
import otava.symbols.inline_functions;
import otava.symbols.function.templates;
import otava.symbols.argument.conversion.table;
import otava.symbols.operation.repository;
import otava.symbols.instantiator;
import otava.symbols.modules;
import otava.symbols.symbol.table;
import otava.symbols.declaration;
import otava.symbols.decl_specifier_seq.parser;
import otava.symbols.exception;
import otava.ast;
import util;

namespace otava::symbols {

CleanUp::CleanUp(): changed(false), cleanupFnSymbol(nullptr)
{
}

void CleanUp::Add(BoundExpressionStatementNode* destructionStatement, Context* context)
{
    BoundExpressionStatementNode* clone = static_cast<BoundExpressionStatementNode*>(destructionStatement->Clone());
    BoundExpressionNode* expr = clone->GetExpr();
    if (expr->IsBoundFunctionCallNode())
    {
        BoundFunctionCallNode* destructorCall = static_cast<BoundFunctionCallNode*>(expr);
        if (!destructorCall->Args().empty())
        {
            BoundNode* firstArg = destructorCall->Args().front().get();
            if (firstArg->IsBoundAddressOfNode())
            {
                BoundAddressOfNode* boundAddrOfNode = static_cast<BoundAddressOfNode*>(firstArg);
                if (boundAddrOfNode->Subject()->IsBoundVariableNode())
                {
                    BoundVariableNode* boundVariable = static_cast<BoundVariableNode*>(boundAddrOfNode->Subject());
                    BoundParentVariableNode* boundParentVariable = new BoundParentVariableNode(boundVariable->GetVariable(), boundVariable->GetSourcePos());
                    boundAddrOfNode->ResetSubject(boundParentVariable);
                }
                else
                {
                    ThrowException("bound variable node expected", destructionStatement->GetSourcePos(), context);
                }
            }
            else
            {
                ThrowException("bound address-of node expected", destructionStatement->GetSourcePos(), context);
            }
        }
        else
        {
            ThrowException("nonempty argument list expected", destructionStatement->GetSourcePos(), context);
        }
    }
    destructionStatements.push_back(std::unique_ptr<BoundStatementNode>(clone));
    changed = true;
}

BoundStatementNode* CleanUp::CloneStatement(int index) const
{
    return destructionStatements[index]->Clone();
}

void BeginChild(FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    std::u32string resultVariableName = context->NextResultVarName();
    functionDefinitionSymbol->SetResultVarName(resultVariableName);
    context->PushResultVarName(resultVariableName);
}

void EndChild(Context* context)
{
    context->PopResultVarName();
}

FunctionDefinitionSymbol* MakeInvokeFn(BoundStatementNode* stmt, FunctionDefinitionSymbol* parentFn, Context* context)
{
    Scope* parenFnScope = context->GetSymbolTable()->CurrentScope();
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    otava::ast::CompoundStatementNode* invokeBlock = new otava::ast::CompoundStatementNode(stmt->GetSourcePos());
    invokeBlock->AddNode(stmt->Source()->Clone());
    otava::ast::DeclSpecifierSequenceNode* invokeDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(stmt->GetSourcePos());
    invokeDeclSpecifiers->AddNode(new otava::ast::VoidNode(stmt->GetSourcePos()));
    otava::ast::ParameterListNode* invokeParameters = new otava::ast::ParameterListNode(stmt->GetSourcePos());
    otava::ast::ParameterNode* invokeParentFrameParameter = new otava::ast::ParameterNode(stmt->GetSourcePos());
    otava::ast::DeclSpecifierSequenceNode* invokeParentFrameParamDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(stmt->GetSourcePos());
    invokeParentFrameParamDeclSpecifiers->AddNode(new otava::ast::VoidNode(stmt->GetSourcePos()));
    invokeParentFrameParameter->SetDeclSpecifiers(invokeParentFrameParamDeclSpecifiers);
    otava::ast::PtrDeclaratorNode* invokeParentFramePtrDeclarator = new otava::ast::PtrDeclaratorNode(stmt->GetSourcePos());
    invokeParentFramePtrDeclarator->AddNode(new otava::ast::PtrNode(stmt->GetSourcePos()));
    invokeParentFramePtrDeclarator->AddNode(new otava::ast::IdentifierNode(stmt->GetSourcePos(), U"__parentFrame"));
    invokeParentFrameParameter->SetDeclarator(invokeParentFramePtrDeclarator);
    invokeParameters->AddNode(invokeParentFrameParameter);
    int invokeSerial = context->NextInvokeSerial();
    otava::ast::FunctionDeclaratorNode* invokeDeclarator = new otava::ast::FunctionDeclaratorNode(stmt->GetSourcePos(),
        new otava::ast::IdentifierNode(stmt->GetSourcePos(), U"invoke_" + 
            util::ToUtf32(std::to_string(invokeSerial)) + U"_" + util::ToUtf32(context->GetBoundCompileUnit()->Id())), invokeParameters);
    otava::ast::FunctionDefinitionNode invokeFnNode(stmt->GetSourcePos(), nullptr, invokeDeclSpecifiers, invokeDeclarator, nullptr,
        new otava::ast::FunctionBodyNode(stmt->GetSourcePos(), invokeBlock));
    InstantiationScope invokeInstantiationScope(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->Parent()->GetScope());
    invokeInstantiationScope.PushParentScope(context->GetSymbolTable()->GetNamespaceScope(U"std", stmt->GetSourcePos(), context));
    invokeInstantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
    context->GetSymbolTable()->BeginScope(&invokeInstantiationScope);
    Instantiator invokeInstantiator(context, &invokeInstantiationScope);
    invokeInstantiator.SetFunctionNode(&invokeFnNode);
    context->PushSetFlag(ContextFlags::instantiateInlineFunction | ContextFlags::saveDeclarations | ContextFlags::dontBind);
    invokeFnNode.Accept(invokeInstantiator);
    FunctionDefinitionSymbol* invokeFnSymbol = static_cast<FunctionDefinitionSymbol*>(invokeInstantiator.GetSpecialization());
    invokeFnSymbol->SetParentFn(parentFn);
    invokeFnSymbol->SetParentFnScope(parenFnScope);
    context->PushBoundFunction(new BoundFunctionNode(invokeFnSymbol, stmt->GetSourcePos()));
    context->PushSetFlag(ContextFlags::skipInvokeChecking | ContextFlags::makeChildFn);
    invokeFnSymbol->SetResultVarName(context->ResultVarName());
    invokeFnSymbol = BindFunction(&invokeFnNode, invokeFnSymbol, context);
    context->PopFlags();
    context->PopFlags();
    if (invokeFnSymbol->IsBound())
    {
        context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
    }
    context->PopBoundFunction();
    context->GetSymbolTable()->EndScope();
    invokeInstantiationScope.PopParentScope();
    invokeInstantiationScope.PopParentScope();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    return invokeFnSymbol;
}

FunctionDefinitionSymbol* MakeCleanupFn(const soul::ast::SourcePos& sourcePos, FunctionDefinitionSymbol* parentFn, Context* context)
{
    CleanUp& cleanup = context->GetCleanup();
    if (!cleanup.Changed())
    {
        return cleanup.CleanupFnSymbol();
    }
    Scope* parenFnScope = context->GetSymbolTable()->CurrentScope();
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    otava::ast::CompoundStatementNode* cleanupBlock = new otava::ast::CompoundStatementNode(sourcePos);
    int count = cleanup.Count();
    for (int i = count - 1; i >= 0; --i)
    {
        otava::ast::Node* stmt = new otava::ast::BoundStatementNode(cleanup.CloneStatement(i), sourcePos);
        cleanupBlock->AddNode(stmt);
    }
    otava::ast::DeclSpecifierSequenceNode* cleanupDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    cleanupDeclSpecifiers->AddNode(new otava::ast::VoidNode(sourcePos));
    otava::ast::ParameterListNode* cleanupParameters = new otava::ast::ParameterListNode(sourcePos);
    int cleanupSerial = context->NextCleanupSerial();
    otava::ast::ParameterNode* cleanupParentFrameParameter = new otava::ast::ParameterNode(sourcePos);
    otava::ast::DeclSpecifierSequenceNode* cleanupParentFrameParamDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    cleanupParentFrameParamDeclSpecifiers->AddNode(new otava::ast::VoidNode(sourcePos));
    cleanupParentFrameParameter->SetDeclSpecifiers(cleanupParentFrameParamDeclSpecifiers);
    otava::ast::PtrDeclaratorNode* cleanupParentFramePtrDeclarator = new otava::ast::PtrDeclaratorNode(sourcePos);
    cleanupParentFramePtrDeclarator->AddNode(new otava::ast::PtrNode(sourcePos));
    cleanupParentFramePtrDeclarator->AddNode(new otava::ast::IdentifierNode(sourcePos, U"__parentFrame"));
    cleanupParentFrameParameter->SetDeclarator(cleanupParentFramePtrDeclarator);
    cleanupParameters->AddNode(cleanupParentFrameParameter);
    otava::ast::FunctionDeclaratorNode* cleanupDeclarator = new otava::ast::FunctionDeclaratorNode(sourcePos,
        new otava::ast::IdentifierNode(sourcePos, U"cleanup_" + 
            util::ToUtf32(std::to_string(cleanupSerial)) + U"_" + util::ToUtf32(context->GetBoundCompileUnit()->Id())), cleanupParameters);
    otava::ast::FunctionDefinitionNode cleanupFnNode(sourcePos, nullptr, cleanupDeclSpecifiers, cleanupDeclarator, nullptr,
        new otava::ast::FunctionBodyNode(sourcePos, cleanupBlock));
    InstantiationScope cleanupInstantiationScope(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->Parent()->GetScope());
    cleanupInstantiationScope.PushParentScope(context->GetSymbolTable()->GetNamespaceScope(U"std", sourcePos, context));
    cleanupInstantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
    context->GetSymbolTable()->BeginScope(&cleanupInstantiationScope);
    Instantiator cleanupInstantiator(context, &cleanupInstantiationScope);
    cleanupInstantiator.SetFunctionNode(&cleanupFnNode);
    context->PushSetFlag(ContextFlags::instantiateInlineFunction | ContextFlags::saveDeclarations | ContextFlags::dontBind);
    cleanupFnNode.Accept(cleanupInstantiator);
    FunctionDefinitionSymbol* cleanupFnSymbol = static_cast<FunctionDefinitionSymbol*>(cleanupInstantiator.GetSpecialization());
    cleanupFnSymbol->SetParentFn(parentFn);
    cleanupFnSymbol->SetParentFnScope(parenFnScope);
    context->PushBoundFunction(new BoundFunctionNode(cleanupFnSymbol, sourcePos));
    context->PushSetFlag(ContextFlags::skipInvokeChecking | ContextFlags::makeChildFn);
    cleanupFnSymbol->SetResultVarName(context->ResultVarName());
    cleanupFnSymbol = BindFunction(&cleanupFnNode, cleanupFnSymbol, context);
    context->PopFlags();
    context->PopFlags();
    if (cleanupFnSymbol->IsBound())
    {
        context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
    }
    context->PopBoundFunction();
    context->GetSymbolTable()->EndScope();
    cleanupInstantiationScope.PopParentScope();
    cleanupInstantiationScope.PopParentScope();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    cleanup.ResetChanged();
    cleanup.SetCleanupFnSymbol(cleanupFnSymbol);
    return cleanupFnSymbol;
}

BoundStatementNode* GenerateInvoke(BoundStatementNode* stmt, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    std::unique_ptr<BoundStatementNode> owner(stmt);
    context->PushFlags();
    context->ResetFlags();
    std::unique_ptr<BoundStatementNode> boundVarDeclarationStatement;
    TypeSymbol* resultType = functionDefinitionSymbol->NonChildFunctionResultType(context);
    std::u32string resultVarName = context->NextResultVarName();
    context->PushResultVarName(resultVarName);
    if (resultType)
    {
        std::u32string varDeclarationStatementText;
        TypeSymbol* nonReferenceType = ConvertRefToPtrType(resultType, context);
        varDeclarationStatementText.append(nonReferenceType->FullName()).append(1, ' ').append(resultVarName);
        if (nonReferenceType->IsPointerType())
        {
            varDeclarationStatementText.append(U" = nullptr;");
        }
        else
        {
            varDeclarationStatementText.append(U";");
        }
        std::unique_ptr<otava::ast::Node> varDeclarationStmtNode = ParseStatement(varDeclarationStatementText, context);
        context->PushSetFlag(ContextFlags::skipInvokeChecking);
        boundVarDeclarationStatement.reset(BindStatement(varDeclarationStmtNode.get(), functionDefinitionSymbol, context));
        context->PopFlags();
    }
    FunctionDefinitionSymbol* invokeFnSymbol = MakeInvokeFn(stmt, functionDefinitionSymbol, context);
    FunctionDefinitionSymbol* cleanupFnSymbol = MakeCleanupFn(stmt->GetSourcePos(), functionDefinitionSymbol, context);
    std::u32string invokeStmtText;
    invokeStmtText.append(U"ort_invoke(").append(invokeFnSymbol->Name()).append(U", ").append(cleanupFnSymbol->Name()).append(U", ").
        append(U"__intrinsic_get_frame_ptr()").append(U");");
    std::unique_ptr<otava::ast::Node> invokeStmtNode = ParseStatement(invokeStmtText, context);
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    context->PushSetFlag(ContextFlags::skipInvokeChecking);
    BoundStatementNode* boundInvokeStatement = BindStatement(invokeStmtNode.get(), functionDefinitionSymbol, context);
    context->PopFlags();
    if (stmt->IsReturnStatementNode())
    {
        std::u32string returnStatementText;
        returnStatementText.append(U"return ").append(invokeFnSymbol->ResultVarExprStr(resultType)).append(U";");
        std::unique_ptr<otava::ast::Node> returnStmtNode = ParseStatement(returnStatementText, context);
        context->PushSetFlag(ContextFlags::skipInvokeChecking);
        BoundStatementNode* boundReturnStmt = BindStatement(returnStmtNode.get(), functionDefinitionSymbol, context);
        context->PopFlags();
        boundInvokeStatement = new BoundSequenceStatementNode(stmt->GetSourcePos(), boundInvokeStatement, boundReturnStmt);
    }
    if (functionDefinitionSymbol->ParentFn())
    {
        otava::ast::BinaryExprNode* binaryExpr = new otava::ast::BinaryExprNode(stmt->GetSourcePos(),
            new otava::ast::AssignNode(stmt->GetSourcePos()),
            new otava::ast::IdentifierNode(stmt->GetSourcePos(), context->ResultVarName()), 
                new otava::ast::IdentifierNode(stmt->GetSourcePos(), invokeFnSymbol->ResultVarExprStr(resultType)));
        otava::ast::ExpressionStatementNode exprStmt(stmt->GetSourcePos(), binaryExpr, nullptr, nullptr);
        BoundStatementNode* boundExpressionStatement = BindStatement(&exprStmt, functionDefinitionSymbol, context);
        boundInvokeStatement = new BoundSequenceStatementNode(stmt->GetSourcePos(), boundInvokeStatement, boundExpressionStatement);
    }
    if (boundVarDeclarationStatement && invokeFnSymbol->GetFlag(FunctionSymbolFlags::containsReturnStatement))
    {
        boundInvokeStatement = new BoundSequenceStatementNode(stmt->GetSourcePos(), boundVarDeclarationStatement.release(), boundInvokeStatement);
    }
    context->PopResultVarName();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    context->PopFlags();
    return boundInvokeStatement;
}

otava::ast::Node* MakeClonedRetValExprNode(otava::ast::Node* node, bool makeAddrOfNode)
{
    if (makeAddrOfNode)
    {
        return new otava::ast::UnaryExprNode(node->GetSourcePos(), new otava::ast::AddrOfNode(node->GetSourcePos()), node->Clone());
    }
    else
    {
        return node->Clone();
    }
}

BoundStatementNode* ConvertReturnStatement(otava::ast::ReturnStatementNode* returnStatement, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    functionDefinitionSymbol->SetFlag(FunctionSymbolFlags::containsReturnStatement);
    if (returnStatement->ReturnValue())
    {
        bool makeAddrOfNode = functionDefinitionSymbol->NonChildFunctionResultType(context)->IsReferenceType();
        otava::ast::BinaryExprNode* binaryExpr = new otava::ast::BinaryExprNode(returnStatement->GetSourcePos(), 
            new otava::ast::AssignNode(returnStatement->GetSourcePos()),
            new otava::ast::IdentifierNode(returnStatement->GetSourcePos(), context->ResultVarName()), 
            MakeClonedRetValExprNode(returnStatement->ReturnValue(), makeAddrOfNode));
        otava::ast::ExpressionStatementNode exprStatementNode(returnStatement->GetSourcePos(), binaryExpr, nullptr, nullptr);
        BoundStatementNode* boundExpressionStatement = BindStatement(&exprStatementNode, functionDefinitionSymbol, context);
        BoundReturnStatementNode* boundReturnStatement = new BoundReturnStatementNode(returnStatement->GetSourcePos());
        boundReturnStatement->SetSource(returnStatement);
        BoundSequenceStatementNode* boundSequenceStatement = new BoundSequenceStatementNode(
            returnStatement->GetSourcePos(), boundExpressionStatement, boundReturnStatement);
        return boundSequenceStatement;
    }
    else
    {
        BoundReturnStatementNode* boundReturnStatement = new BoundReturnStatementNode(returnStatement->GetSourcePos());
        boundReturnStatement->SetSource(returnStatement);
        return boundReturnStatement;
    }
}

} // namespace otava::symbols
