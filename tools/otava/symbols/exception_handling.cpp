// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.exception_handling;

import otava.symbols.stmt.parser;
import otava.symbols.block;
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
import otava.symbols.bound.tree.visitor;
import otava.ast;
import util;

namespace otava::symbols {

CleanupBlock::CleanupBlock(Cleanup* cleanup_) : cleanup(cleanup_)
{
}

void CleanupBlock::Add(BoundFunctionCallNode* destructorCall, Context* context)
{
    BoundFunctionCallNode* clonedDestructorCall = static_cast<BoundFunctionCallNode*>(destructorCall->Clone());
    if (!clonedDestructorCall->Args().empty())
    {
        BoundNode* firstArg = clonedDestructorCall->Args().front().get();
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
                ThrowException("bound variable node expected", clonedDestructorCall->GetSourcePos(), context);
            }
        }
        else
        {
            ThrowException("bound address-of node expected", clonedDestructorCall->GetSourcePos(), context);
        }
    }
    else
    {
        ThrowException("nonempty argument list expected", clonedDestructorCall->GetSourcePos(), context);
    }
    destructorCalls.push_back(std::unique_ptr<BoundFunctionCallNode>(clonedDestructorCall));
    cleanup->SetChanged();
}

void CleanupBlock::Make(otava::ast::CompoundStatementNode* compoundStatement)
{
    int n = destructorCalls.size();
    for (int i = n - 1; i >= 0; --i)
    {
        BoundExpressionStatementNode* exprStmt = new BoundExpressionStatementNode(destructorCalls[i]->GetSourcePos());
        exprStmt->SetExpr(destructorCalls[i]->Clone());
        otava::ast::BoundStatementNode* stmt = new otava::ast::BoundStatementNode(exprStmt, exprStmt->GetSourcePos());
        compoundStatement->AddNode(stmt);
    }
}

soul::ast::SourcePos CleanupBlock::GetSourcePos() const
{
    for (const auto& dtorCall : destructorCalls)
    {
        soul::ast::SourcePos sourcePos = dtorCall->GetSourcePos();
        if (sourcePos.IsValid()) return sourcePos;
    }
    return soul::ast::SourcePos(); 
}

Cleanup::Cleanup() : changed(false)
{
}

bool Cleanup::IsEmpty() const
{
    for (const auto& cleanupBlock : cleanupBlocks)
    {
        if (!cleanupBlock->IsEmpty()) return false;
    }
    return true;
}

void Cleanup::PushCleanupBlock()
{
    cleanupBlocks.push_back(std::unique_ptr<CleanupBlock>(new CleanupBlock(this)));
}

void Cleanup::PopCleanupBlock()
{
    cleanupBlocks.pop_back();
}

void Cleanup::Make(otava::ast::CompoundStatementNode* compoundStatement)
{
    int n = cleanupBlocks.size();
    for (int i = n - 1; i >= 0; --i)
    {
        CleanupBlock* cleanupBlock = cleanupBlocks[i].get();;
        cleanupBlock->Make(compoundStatement);
    }
}

soul::ast::SourcePos Cleanup::GetSourcePos() const
{
    if (!cleanupBlocks.empty())
    {
        for (const auto& cleanupBlock : cleanupBlocks)
        {
            soul::ast::SourcePos sourcePos = cleanupBlock->GetSourcePos();
            if (sourcePos.IsValid()) return sourcePos;
        }
    }
    return soul::ast::SourcePos();
}

Invoke::Invoke()
{
}

void Invoke::Clear()
{
    statements.clear();
}

void Invoke::Add(BoundStatementNode* stmt)
{
    statements.push_back(std::unique_ptr<BoundStatementNode>(stmt));
}

void Invoke::Make(otava::ast::CompoundStatementNode* compoundStatement, Context* context)
{
    for (const auto& stmt : statements)
    {
        if (!stmt->Source())
        {
            ThrowException("statement source not set", stmt->GetSourcePos(), context);
        }
        otava::ast::Node* stmtNode = stmt->Source()->Clone();
        compoundStatement->AddNode(stmtNode);
    }
}

soul::ast::SourcePos Invoke::GetSourcePos() const
{
    for (const auto& stmt : statements)
    {
        soul::ast::SourcePos sourcePos = stmt->GetSourcePos();
        if (sourcePos.IsValid()) return sourcePos;
    }
    return soul::ast::SourcePos();
}

FunctionDefinitionSymbol* MakeInvokeFn(Invoke& invoke, Scope* parentFnScope, FunctionDefinitionSymbol* parentFn, Context* context)
{
    soul::ast::SourcePos sourcePos = invoke.GetSourcePos();
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    otava::ast::CompoundStatementNode* invokeBlock = new otava::ast::CompoundStatementNode(sourcePos);
    if (!parentFn->Blocks().empty())
    {
        invokeBlock->SetBlockId(parentFn->Blocks().front()->BlockId());
    }
    invoke.Make(invokeBlock, context);
    otava::ast::DeclSpecifierSequenceNode* invokeDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    invokeDeclSpecifiers->AddNode(new otava::ast::VoidNode(sourcePos));
    otava::ast::ParameterListNode* invokeParameters = new otava::ast::ParameterListNode(sourcePos);
    otava::ast::ParameterNode* invokeParentFrameParameter = new otava::ast::ParameterNode(sourcePos);
    otava::ast::DeclSpecifierSequenceNode* invokeParentFrameParamDeclSpecifiers = new otava::ast::DeclSpecifierSequenceNode(sourcePos);
    invokeParentFrameParamDeclSpecifiers->AddNode(new otava::ast::VoidNode(sourcePos));
    invokeParentFrameParameter->SetDeclSpecifiers(invokeParentFrameParamDeclSpecifiers);
    otava::ast::PtrDeclaratorNode* invokeParentFramePtrDeclarator = new otava::ast::PtrDeclaratorNode(sourcePos);
    invokeParentFramePtrDeclarator->AddNode(new otava::ast::PtrNode(sourcePos));
    invokeParentFramePtrDeclarator->AddNode(new otava::ast::IdentifierNode(sourcePos, U"__parentFrame"));
    invokeParentFrameParameter->SetDeclarator(invokeParentFramePtrDeclarator);
    invokeParameters->AddNode(invokeParentFrameParameter);
    int invokeSerial = context->NextInvokeSerial();
    otava::ast::FunctionDeclaratorNode* invokeDeclarator = new otava::ast::FunctionDeclaratorNode(sourcePos,
        new otava::ast::IdentifierNode(sourcePos, U"invoke_" +
            util::ToUtf32(std::to_string(invokeSerial)) + U"_" + util::ToUtf32(context->GetBoundCompileUnit()->Id())), invokeParameters);
    std::unique_ptr<otava::ast::FunctionDefinitionNode> invokeFnNode(
        new otava::ast::FunctionDefinitionNode(sourcePos, nullptr, invokeDeclSpecifiers, invokeDeclarator, nullptr, 
            new otava::ast::FunctionBodyNode(sourcePos, invokeBlock)));
    InstantiationScope invokeInstantiationScope(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->Parent()->GetScope());
    invokeInstantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
    context->GetSymbolTable()->BeginScope(&invokeInstantiationScope);
    Instantiator invokeInstantiator(context, &invokeInstantiationScope);
    invokeInstantiator.SetFunctionNode(invokeFnNode.get());
    context->PushSetFlag(ContextFlags::instantiateInlineFunction | ContextFlags::saveDeclarations | ContextFlags::dontBind);
    invokeFnNode->Accept(invokeInstantiator);
    int invokeFnScopeCount = invokeInstantiator.ScopeCount();
    FunctionDefinitionSymbol* invokeFnSymbol = static_cast<FunctionDefinitionSymbol*>(invokeInstantiator.GetSpecialization());
    invokeFnSymbol->SetSkipInvokeChecking();
    invokeFnSymbol->SetParentFn(parentFn);
    invokeFnSymbol->SetParentFnScope(parentFnScope);
    context->PushBoundFunction(new BoundFunctionNode(invokeFnSymbol, sourcePos));
    context->PushSetFlag(ContextFlags::makeChildFn);
    invokeFnSymbol->SetResultVarName(context->ResultVarName());
    invokeFnSymbol = BindFunction(invokeFnNode.get(), invokeFnSymbol, context);
    otava::symbols::EndFunctionDefinition(invokeFnNode.get(), invokeFnScopeCount, context);
    context->PopFlags();
    context->PopFlags();
    //if (invokeFnSymbol->IsBound())
    //{
        //context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
    //}
    //context->PopBoundFunction();
    context->GetSymbolTable()->EndScope();
    invokeInstantiationScope.PopParentScope();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    invoke.Clear();
    invokeFnSymbol->SetFnDefNode(invokeFnNode.release());
    return invokeFnSymbol;
}

FunctionDefinitionSymbol* MakeCleanupFn(Cleanup& cleanup, Scope* parentFnScope, FunctionDefinitionSymbol* parentFn, Context* context)
{
    soul::ast::SourcePos sourcePos = cleanup.GetSourcePos();
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    otava::ast::CompoundStatementNode* cleanupBlock = new otava::ast::CompoundStatementNode(sourcePos);
    if (!parentFn->Blocks().empty())
    {
        cleanupBlock->SetBlockId(parentFn->Blocks().front()->BlockId());
    }
    cleanup.Make(cleanupBlock);
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
    std::unique_ptr<otava::ast::FunctionDefinitionNode> cleanupFnNode(new otava::ast::FunctionDefinitionNode(sourcePos, nullptr, cleanupDeclSpecifiers, 
        cleanupDeclarator, nullptr, new otava::ast::FunctionBodyNode(sourcePos, cleanupBlock)));
    InstantiationScope cleanupInstantiationScope(context->GetBoundFunction()->GetFunctionDefinitionSymbol()->Parent()->GetScope());
    cleanupInstantiationScope.PushParentScope(context->GetSymbolTable()->CurrentScope()->GetNamespaceScope());
    context->GetSymbolTable()->BeginScope(&cleanupInstantiationScope);
    Instantiator cleanupInstantiator(context, &cleanupInstantiationScope);
    cleanupInstantiator.SetFunctionNode(cleanupFnNode.get());
    context->PushSetFlag(ContextFlags::instantiateInlineFunction | ContextFlags::saveDeclarations | ContextFlags::dontBind);
    cleanupFnNode->Accept(cleanupInstantiator);
    int cleanupFnScopeCount = cleanupInstantiator.ScopeCount();
    FunctionDefinitionSymbol* cleanupFnSymbol = static_cast<FunctionDefinitionSymbol*>(cleanupInstantiator.GetSpecialization());
    cleanupFnSymbol->SetNoExcept();
    cleanupFnSymbol->SetParentFn(parentFn);
    cleanupFnSymbol->SetParentFnScope(parentFnScope);
    context->PushBoundFunction(new BoundFunctionNode(cleanupFnSymbol, sourcePos));
    context->PushSetFlag(ContextFlags::makeChildFn);
    cleanupFnSymbol->SetResultVarName(context->ResultVarName());
    cleanupFnSymbol = BindFunction(cleanupFnNode.get(), cleanupFnSymbol, context);
    otava::symbols::EndFunctionDefinition(cleanupFnNode.get(), cleanupFnScopeCount, context);
    context->PopFlags();
    context->PopFlags();
//    if (cleanupFnSymbol->IsBound())
//    {
//        context->GetBoundCompileUnit()->AddBoundNode(std::unique_ptr<BoundNode>(context->ReleaseBoundFunction()), context);
//    }
//    context->PopBoundFunction();
    context->GetSymbolTable()->EndScope();
    cleanupInstantiationScope.PopParentScope();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    cleanupFnSymbol->SetFnDefNode(cleanupFnNode.release());
    return cleanupFnSymbol;
}

/*
BoundStatementNode* GenerateInvoke(Invoke& invoke, Cleanup& cleanup, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
{
    soul::ast::SourcePos sourcePos = invoke.GetSourcePos();
    context->PushFlags();
    context->ResetFlags();
    std::unique_ptr<BoundStatementNode> boundChildControlResultStatement;
    std::unique_ptr<BoundStatementNode> boundVarDeclarationStatement;
    TypeSymbol* resultType = functionDefinitionSymbol->NonChildFunctionResultType(context);
    std::u32string childControlResultVarName = context->NextChildControlResultVarName();
    std::u32string resultVarName = context->NextResultVarName();
    context->PushResultVarName(resultVarName);
    context->PushChildControlResultVarName(childControlResultVarName);
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
        try
        {
            std::unique_ptr<otava::ast::Node> varDeclarationStmtNode = ParseStatement(varDeclarationStatementText, context);
            context->PushSetFlag(ContextFlags::skipInvokeChecking);
            boundVarDeclarationStatement.reset(BindStatement(varDeclarationStmtNode.get(), functionDefinitionSymbol, context));
            context->PopFlags();
        }
        catch (const std::exception& ex)
        {
            if (nonReferenceType->IsClassTypeSymbol())
            {
                ThrowException("error generating exception handling invoke, possible reason: class '" + util::ToUtf8(resultType->FullName()) +
                    "' not default constructible: " + ex.what());
            }
            else
            {
                throw;
            }
        }
    }
    std::u32string childControlResultStatementText;
    childControlResultStatementText.append(U"std::child_control_result ").append(childControlResultVarName).append(U" = std::child_control_result::none;");
    std::unique_ptr<otava::ast::Node> setChildControlResultStmtNode = ParseStatement(childControlResultStatementText, context);
    context->PushSetFlag(ContextFlags::skipInvokeChecking);
    boundChildControlResultStatement.reset(BindStatement(setChildControlResultStmtNode.get(), functionDefinitionSymbol, context));
    context->PopFlags();
    FunctionDefinitionSymbol* invokeFnSymbol = MakeInvokeFn(invoke, functionDefinitionSymbol, context);
    FunctionDefinitionSymbol* cleanupFnSymbol = MakeCleanupFn(cleanup, functionDefinitionSymbol, context);
    std::u32string invokeStmtText;
    invokeStmtText.append(U"ort_invoke(").append(invokeFnSymbol->Name()).append(U", ").append(cleanupFnSymbol->Name()).append(U", ").
        append(U"__intrinsic_get_frame_ptr()").append(U");");
    std::unique_ptr<otava::ast::Node> invokeStmtNode = ParseStatement(invokeStmtText, context);
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    context->PushSetFlag(ContextFlags::skipInvokeChecking);
    BoundStatementNode* boundInvokeStatement = BindStatement(invokeStmtNode.get(), functionDefinitionSymbol, context);
    context->PopFlags();
    if (invokeFnSymbol->GetFlag(FunctionSymbolFlags::containsReturnStatement))
    {
        std::u32string returnStatementText;
        returnStatementText.append(U"if (").append(childControlResultVarName).append(U" == std::child_control_result::ret) return ").append(
            invokeFnSymbol->ResultVarExprStr(resultType)).append(U";");
        std::unique_ptr<otava::ast::Node> returnStmtNode = ParseStatement(returnStatementText, context);
        context->PushSetFlag(ContextFlags::skipInvokeChecking);
        BoundStatementNode* boundReturnStmt = BindStatement(returnStmtNode.get(), functionDefinitionSymbol, context);
        context->PopFlags();
        boundInvokeStatement = new BoundSequenceStatementNode(sourcePos, boundInvokeStatement, boundReturnStmt);
    }
    else if (functionDefinitionSymbol->ParentFn())
    {
        otava::ast::BinaryExprNode* binaryExpr = new otava::ast::BinaryExprNode(sourcePos,
            new otava::ast::AssignNode(sourcePos),
            new otava::ast::IdentifierNode(sourcePos, context->ResultVarName()),
                new otava::ast::IdentifierNode(sourcePos, invokeFnSymbol->ResultVarExprStr(resultType)));
        otava::ast::ExpressionStatementNode exprStmt(sourcePos, binaryExpr, nullptr, nullptr);
        BoundStatementNode* boundExpressionStatement = BindStatement(&exprStmt, functionDefinitionSymbol, context);
        boundInvokeStatement = new BoundSequenceStatementNode(sourcePos, boundInvokeStatement, boundExpressionStatement);
    }
    if (boundVarDeclarationStatement && boundChildControlResultStatement && invokeFnSymbol->GetFlag(FunctionSymbolFlags::containsReturnStatement))
    {
        boundInvokeStatement = new BoundSequenceStatementNode(sourcePos, boundVarDeclarationStatement.release(), boundInvokeStatement);
        boundInvokeStatement = new BoundSequenceStatementNode(sourcePos, boundChildControlResultStatement.release(), boundInvokeStatement);
    }
    context->PopResultVarName();
    context->PopChildControlResultVarName();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    context->PopFlags();
    return boundInvokeStatement;
}
*/

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
        otava::ast::ExpressionStatementNode* exprStatementNode = new otava::ast::ExpressionStatementNode(returnStatement->GetSourcePos(), binaryExpr, nullptr, nullptr);
        std::u32string setChildControlResultStmtText;
        setChildControlResultStmtText = context->ChildControlResultVarName();
        setChildControlResultStmtText.append(U" = std::child_control_result::ret;");
        std::unique_ptr<otava::ast::Node> setChildControlResultStmt = ParseStatement(setChildControlResultStmtText, context);
        BoundStatementNode* boundExpressionStatement = BindStatement(exprStatementNode, functionDefinitionSymbol, context);
        boundExpressionStatement->SetSource(exprStatementNode);
        BoundStatementNode* boundSetChildControlResultStatement = BindStatement(setChildControlResultStmt.get(), functionDefinitionSymbol, context);
        boundSetChildControlResultStatement->SetSource(setChildControlResultStmt.release());
        BoundReturnStatementNode* boundReturnStatement = new BoundReturnStatementNode(returnStatement->GetSourcePos());
        boundReturnStatement->SetSource(returnStatement->Clone());
        BoundSequenceStatementNode* boundSequenceStatement = new BoundSequenceStatementNode(returnStatement->GetSourcePos(), new BoundSequenceStatementNode(
            returnStatement->GetSourcePos(), boundExpressionStatement, boundSetChildControlResultStatement), boundReturnStatement);
        return boundSequenceStatement;
    }
    else
    {
        BoundReturnStatementNode* boundReturnStatement = new BoundReturnStatementNode(returnStatement->GetSourcePos());
        boundReturnStatement->SetSource(returnStatement->Clone());
        return boundReturnStatement;
    }
}

class InvokeAndCleanupGenerator : public DefaultBoundTreeVisitor
{
public:
    InvokeAndCleanupGenerator(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_);
    std::unique_ptr<BoundCompoundStatementNode> GetFunctionBody() { return std::move(functionBody); }
    void Visit(BoundCompoundStatementNode& node) override;
    void Visit(BoundIfStatementNode& node) override;
    void Visit(BoundSwitchStatementNode& node) override;
    void Visit(BoundCaseStatementNode& node) override;
    void Visit(BoundDefaultStatementNode& node) override;
    void Visit(BoundWhileStatementNode& node) override;
    void Visit(BoundDoStatementNode& node) override;
    void Visit(BoundForStatementNode& node) override;
    void Visit(BoundSequenceStatementNode& node) override;
    void Visit(BoundBreakStatementNode& node) override;
    void Visit(BoundContinueStatementNode& node) override;
    void Visit(BoundReturnStatementNode& node) override;
    void Visit(BoundGotoStatementNode& node) override;
    void Visit(BoundLabeledStatementNode& node) override;
    void Visit(BoundConstructionStatementNode& node) override;
    void Visit(BoundExpressionStatementNode& node) override;
    void Visit(BoundSetVPtrStatementNode& node) override;
    void Visit(BoundAliasDeclarationStatementNode& node) override;
private:
    void GenerateInvokeAndCleanup();
    void Emit(BoundStatementNode* stmt);
    Context* context;
    FunctionDefinitionSymbol* functionDefinitionSymbol;
    std::unique_ptr<BoundCompoundStatementNode> functionBody;
    BoundCompoundStatementNode* currentCompound;
    Cleanup cleanup;
    Invoke invoke;
    bool collect;
    std::unique_ptr<BoundStatementNode> boundStatement;
};

InvokeAndCleanupGenerator::InvokeAndCleanupGenerator(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_) :
    context(context_), functionDefinitionSymbol(functionDefinitionSymbol_), functionBody(), currentCompound(nullptr), collect(false), boundStatement()
{
}

void InvokeAndCleanupGenerator::GenerateInvokeAndCleanup()
{
    if (cleanup.IsEmpty()) return;
    if (invoke.IsEmpty()) return;
    soul::ast::SourcePos sourcePos = invoke.GetSourcePos();
    InstantiationScope invokeInstantiationScope(context->GetSymbolTable()->CurrentScope());
    context->GetSymbolTable()->BeginScope(&invokeInstantiationScope);
    context->PushFlags();
    context->ResetFlags();
    std::unique_ptr<BoundStatementNode> boundChildControlResultStatement;
    std::unique_ptr<BoundStatementNode> boundVarDeclarationStatement;
    TypeSymbol* resultType = functionDefinitionSymbol->NonChildFunctionResultType(context);
    std::u32string childControlResultVarName = context->NextChildControlResultVarName();
    std::u32string resultVarName = context->NextResultVarName();
    context->PushChildControlResultVarName(childControlResultVarName);
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
        try
        {
            std::unique_ptr<otava::ast::Node> varDeclarationStmtNode = ParseStatement(varDeclarationStatementText, context);
            boundVarDeclarationStatement.reset(BindStatement(varDeclarationStmtNode.get(), functionDefinitionSymbol, context));
            boundVarDeclarationStatement->SetSource(varDeclarationStmtNode.release());
        }
        catch (const std::exception& ex)
        {
            if (nonReferenceType->IsClassTypeSymbol())
            {
                ThrowException("error generating exception handling invoke, possible reason: class '" + util::ToUtf8(resultType->FullName()) +
                    "' not default constructible: " + ex.what());
            }
            else
            {
                throw;
            }
        }
    }
    std::u32string childControlResultStatementText;
    childControlResultStatementText.append(U"std::child_control_result ").append(childControlResultVarName).append(U" = std::child_control_result::none;");
    std::unique_ptr<otava::ast::Node> setChildControlResultStmtNode = ParseStatement(childControlResultStatementText, context);
    boundChildControlResultStatement.reset(BindStatement(setChildControlResultStmtNode.get(), functionDefinitionSymbol, context));
    boundChildControlResultStatement->SetSource(setChildControlResultStmtNode.release());
    FunctionDefinitionSymbol* invokeFnSymbol = MakeInvokeFn(invoke, context->GetSymbolTable()->CurrentScope(), functionDefinitionSymbol, context);
    FunctionDefinitionSymbol* cleanupFnSymbol = MakeCleanupFn(cleanup, context->GetSymbolTable()->CurrentScope(), functionDefinitionSymbol, context);
    std::u32string invokeStmtText;
    invokeStmtText.append(U"ort_invoke(").append(invokeFnSymbol->Name()).append(U", ").append(cleanupFnSymbol->Name()).append(U", ").
        append(U"__intrinsic_get_frame_ptr()").append(U");");
    std::unique_ptr<otava::ast::Node> invokeStmtNode = ParseStatement(invokeStmtText, context);
    std::unique_ptr<otava::ast::CompoundStatementNode> invokeBlock(new otava::ast::CompoundStatementNode(sourcePos));
    invokeBlock->SetBlockId(context->NextBlockId());
    invokeBlock->AddNode(new otava::ast::BoundStatementNode(boundChildControlResultStatement.release(), sourcePos));
    if (resultType)
    {
        invokeBlock->AddNode(new otava::ast::BoundStatementNode(boundVarDeclarationStatement.release(), sourcePos));
    }
    invokeBlock->AddNode(invokeStmtNode.release());
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    if (invokeFnSymbol->GetFlag(FunctionSymbolFlags::containsReturnStatement))
    {
        std::u32string returnStatementText;
        returnStatementText.append(U"if (").append(childControlResultVarName).append(U" == std::child_control_result::ret) return ").append(
            invokeFnSymbol->ResultVarExprStr(resultType)).append(U";");
        std::unique_ptr<otava::ast::Node> returnStmtNode = ParseStatement(returnStatementText, context);
        context->PushSetFlag(ContextFlags::skipInvokeChecking);
        BoundStatementNode* boundReturnStmt = BindStatement(returnStmtNode.get(), functionDefinitionSymbol, context);
        boundReturnStmt->SetSource(returnStmtNode.release());
        context->PopFlags();
        invokeBlock->AddNode(new otava::ast::BoundStatementNode(boundReturnStmt, sourcePos));
    }
    else if (functionDefinitionSymbol->ParentFn())
    {
        otava::ast::BinaryExprNode* binaryExpr = new otava::ast::BinaryExprNode(sourcePos,
            new otava::ast::AssignNode(sourcePos),
            new otava::ast::IdentifierNode(sourcePos, context->ResultVarName()),
            new otava::ast::IdentifierNode(sourcePos, invokeFnSymbol->ResultVarExprStr(resultType)));
        otava::ast::ExpressionStatementNode* exprStmt = new otava::ast::ExpressionStatementNode(sourcePos, binaryExpr, nullptr, nullptr);
        BoundStatementNode* boundExpressionStatement = BindStatement(exprStmt, functionDefinitionSymbol, context);
        boundExpressionStatement->SetSource(exprStmt);
        otava::ast::BoundStatementNode* boundStmt = new otava::ast::BoundStatementNode(boundExpressionStatement, sourcePos);
        invokeBlock->AddNode(boundStmt);
    }
    context->PopResultVarName();
    context->PopChildControlResultVarName();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    context->PopFlags();
    Instantiator invokeInstantiator(context, &invokeInstantiationScope);
    context->PushSetFlag(ContextFlags::saveDeclarations | ContextFlags::dontBind);
    invokeBlock->Accept(invokeInstantiator);
    context->PopFlags();
    std::unique_ptr<BoundStatementNode> boundInvokeBlock(BindStatement(invokeBlock.get(), functionDefinitionSymbol, context));
    context->GetSymbolTable()->EndScope();
    currentCompound->AddStatement(boundInvokeBlock.release());
    cleanup.ResetChanged();
}

void InvokeAndCleanupGenerator::Emit(BoundStatementNode* stmt)
{
    if (collect)
    {
        boundStatement.reset(stmt);
    }
    else
    {
        if (stmt->MayThrow() && !cleanup.IsEmpty())
        {
            invoke.Add(stmt);
        }
        else
        {
            if (cleanup.Changed() && !stmt->ConstructsLocalVariableWithDestructor())
            {
                GenerateInvokeAndCleanup();
            }
            currentCompound->AddStatement(stmt);
        }
    }
}

void InvokeAndCleanupGenerator::Visit(BoundCompoundStatementNode& node)
{
    if (context->GetBoundFunction()->GetFunctionDefinitionSymbol()->GroupName() == U"main")
    {
        int x = 0;
    }
    int blockId = node.BlockId();
    Scope* scope = nullptr;
    if (blockId != -1)
    {
        Symbol* block = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->GetBlock(blockId);
        if (block)
        {
            scope = block->GetScope();
            if (scope)
            {
                context->GetSymbolTable()->BeginScopeGeneric(scope, context);
            }
            else
            {
                int x = 0;
            }
        }
        else
        {
            int x = 0;
        }
    }
    BoundCompoundStatementNode* prevCompound = currentCompound;
    currentCompound = new BoundCompoundStatementNode(node.GetSourcePos());
    cleanup.PushCleanupBlock();
    for (const auto& stmt : node.Statements())
    {
        stmt->Accept(*this);
    }
    GenerateInvokeAndCleanup();
    cleanup.PopCleanupBlock();
    if (!prevCompound)
    {
        functionBody.reset(currentCompound);
    }
    else
    {
        prevCompound->AddStatement(currentCompound);
    }
    currentCompound = prevCompound;
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
}

void InvokeAndCleanupGenerator::Visit(BoundIfStatementNode& node)
{
    int blockId = node.BlockId();
    Scope* scope = nullptr;
    if (blockId != -1)
    {
        Symbol* block = context->GetBoundFunction()->GetFunctionDefinitionSymbol()->GetBlock(blockId);
        if (block)
        {
            scope = block->GetScope();
            if (scope)
            {
                context->GetSymbolTable()->BeginScopeGeneric(scope, context);
            }
            else
            {
                int x = 0;
            }
        }
        else
        {
            int x = 0;
        }
    }
    std::unique_ptr<BoundIfStatementNode> clone(static_cast<BoundIfStatementNode*>(node.Clone()));
    if (node.ThenStatement()->ContainsLocalVariableWithDestructor())
    {
        bool prevCollect = collect;
        collect = true;
        node.ThenStatement()->Accept(*this);
        clone->SetThenStatement(boundStatement.release());
        collect = prevCollect;
    }
    if (node.ElseStatement() && node.ElseStatement()->ContainsLocalVariableWithDestructor())
    {
        bool prevCollect = collect;
        collect = true;
        node.ElseStatement()->Accept(*this);
        clone->SetElseStatement(boundStatement.release());
        collect = prevCollect;
    }
    Emit(clone.release());
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
}

void InvokeAndCleanupGenerator::Visit(BoundSwitchStatementNode& node)
{
}

void InvokeAndCleanupGenerator::Visit(BoundCaseStatementNode& node)
{
}

void InvokeAndCleanupGenerator::Visit(BoundDefaultStatementNode& node)
{
}

void InvokeAndCleanupGenerator::Visit(BoundWhileStatementNode& node)
{
}

void InvokeAndCleanupGenerator::Visit(BoundDoStatementNode& node)
{
}

void InvokeAndCleanupGenerator::Visit(BoundForStatementNode& node)
{
}

void InvokeAndCleanupGenerator::Visit(BoundSequenceStatementNode& node)
{
    std::unique_ptr<BoundSequenceStatementNode> clone(static_cast<BoundSequenceStatementNode*>(node.Clone()));
    if (node.First()->ContainsLocalVariableWithDestructor())
    {
        bool prevCollect = collect;
        collect = true;
        node.First()->Accept(*this);
        clone->SetFirst(boundStatement.release());
        collect = prevCollect;
    }
    if (node.Second()->ContainsLocalVariableWithDestructor())
    {
        bool prevCollect = collect;
        collect = true;
        node.Second()->Accept(*this);
        clone->SetSecond(boundStatement.release());
        collect = prevCollect;
    }
    Emit(clone.release());
}

void InvokeAndCleanupGenerator::Visit(BoundBreakStatementNode& node)
{
}

void InvokeAndCleanupGenerator::Visit(BoundContinueStatementNode& node)
{
}

void InvokeAndCleanupGenerator::Visit(BoundReturnStatementNode& node)
{
    Emit(node.Clone());
}

void InvokeAndCleanupGenerator::Visit(BoundGotoStatementNode& node)
{
}

void InvokeAndCleanupGenerator::Visit(BoundLabeledStatementNode& node)
{
}

void InvokeAndCleanupGenerator::Visit(BoundSetVPtrStatementNode& node)
{
    Emit(node.Clone());
}

void InvokeAndCleanupGenerator::Visit(BoundAliasDeclarationStatementNode& node)
{
    Emit(node.Clone());
}

void InvokeAndCleanupGenerator::Visit(BoundConstructionStatementNode& node)
{
    if (node.DestructorCall())
    {
        GenerateInvokeAndCleanup();
        cleanup.CurrentCleanupBlock()->Add(node.DestructorCall(), context);
    }
    Emit(node.Clone());
}

void InvokeAndCleanupGenerator::Visit(BoundExpressionStatementNode& node)
{
    Emit(node.Clone());
}

std::unique_ptr<BoundCompoundStatementNode> MakeInvokesAndCleanups(FunctionDefinitionSymbol* functionDefinitionSymbol, 
    BoundCompoundStatementNode* functionNody, Context* context)
{
    InvokeAndCleanupGenerator generator(context, functionDefinitionSymbol);
    functionNody->Accept(generator);
    return generator.GetFunctionBody();
}

} // namespace otava::symbols
