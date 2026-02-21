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
import otava.symbols.fundamental.type.symbol;
import otava.symbols.overload.resolution;
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

void CleanupBlock::Make(otava::ast::CompoundStatementNode* compoundStatement, bool skipLast)
{
    int n = destructorCalls.size();
    int end = n - 1;
    if (skipLast)
    {
        --end;
    }
    for (int i = end; i >= 0; --i)
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

bool Cleanup::IsEmpty() const noexcept
{
    int n = cleanupBlocks.size();
    for (int i = 0; i < n; ++i)
    {
        CleanupBlock* cleanupBlock = cleanupBlocks[i].get();
        if (!cleanupBlock->IsEmpty()) return false;
    }
    return true;
}

bool Cleanup::ContainsOne() const noexcept
{
    int n = cleanupBlocks.size();
    for (int i = 0; i < n; ++i)
    { 
        CleanupBlock* cleanupBlock = cleanupBlocks[i].get();
        if (i < n - 1)
        {
            if (!cleanupBlock->IsEmpty()) return false;
        }
        else
        {
            if (cleanupBlock->ContainsOne()) return true;
        }
    }
    return false;
}

void Cleanup::PushCleanupBlock()
{
    cleanupBlocks.push_back(std::unique_ptr<CleanupBlock>(new CleanupBlock(this)));
}

void Cleanup::PopCleanupBlock()
{
    cleanupBlocks.pop_back();
}

void Cleanup::Make(otava::ast::CompoundStatementNode* compoundStatement, bool skipLast)
{
    int n = cleanupBlocks.size();
    for (int i = n - 1; i >= 0; --i)
    {
        CleanupBlock* cleanupBlock = cleanupBlocks[i].get();;
        bool skip = false;
        if (i == n - 1)
        {
            skip = skipLast;
        }
        cleanupBlock->Make(compoundStatement, skip);
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
    if (stmt->ConstructsLocalVariableWithDestructor())
    {
        statementsWithDestructor.push_back(std::unique_ptr<BoundConstructionStatementNode>(static_cast<BoundConstructionStatementNode*>(stmt->Clone())));
    }
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
    context->PushParentFn(parentFn);
    context->PushSetFlag(ContextFlags::instantiateInlineFunction | ContextFlags::saveDeclarations | ContextFlags::dontBind | ContextFlags::invoke);
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
    context->GetSymbolTable()->EndScope();
    context->PopParentFn();
    invokeInstantiationScope.PopParentScope();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    invoke.Clear();
    invokeFnSymbol->SetFnDefNode(invokeFnNode.release());
    return invokeFnSymbol;
}

FunctionDefinitionSymbol* MakeCleanupFn(Cleanup& cleanup, bool skipLast, Scope* parentFnScope, FunctionDefinitionSymbol* parentFn, Context* context)
{
    soul::ast::SourcePos sourcePos = cleanup.GetSourcePos();
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    otava::ast::CompoundStatementNode* cleanupBlock = new otava::ast::CompoundStatementNode(sourcePos);
    if (!parentFn->Blocks().empty())
    {
        cleanupBlock->SetBlockId(parentFn->Blocks().front()->BlockId());
    }
    cleanup.Make(cleanupBlock, skipLast);
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
    context->GetSymbolTable()->EndScope();
    cleanupInstantiationScope.PopParentScope();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    cleanupFnSymbol->SetFnDefNode(cleanupFnNode.release());
    cleanup.ResetChanged();
    return cleanupFnSymbol;
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
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
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
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
        return boundSequenceStatement;
    }
    else
    {
        BoundReturnStatementNode* boundReturnStatement = new BoundReturnStatementNode(returnStatement->GetSourcePos());
        boundReturnStatement->SetSource(returnStatement->Clone());
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
        return boundReturnStatement;
    }
}

class InvokeAndCleanupGenerator : public DefaultBoundTreeVisitor
{
public:
    InvokeAndCleanupGenerator(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_);
    std::unique_ptr<BoundCompoundStatementNode> GetFunctionBody();
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
    void GenerateInvokeAndCleanup(bool skipLast);
    BoundVariableNode* ConvertCondition(BoundExpressionNode* condition, const soul::ast::SourcePos& sourcePos);
    void Emit(BoundStatementNode* stmt);
    void AddCurrentInvokeToCurrentCompound();
    Context* context;
    FunctionDefinitionSymbol* functionDefinitionSymbol;
    std::unique_ptr<BoundStatementNode> currentInvoke;
    std::unique_ptr<BoundStatementNode> currentStatement;
    Cleanup cleanup;
    Invoke invoke;
    BoundCompoundStatementNode* currentCompound;
    std::vector<std::unique_ptr<BoundConstructionStatementNode>>* currentInvokeStatementsWithDestructor;
};

InvokeAndCleanupGenerator::InvokeAndCleanupGenerator(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_) :
    context(context_), functionDefinitionSymbol(functionDefinitionSymbol_), currentStatement(), currentCompound(nullptr), 
    currentInvokeStatementsWithDestructor(nullptr)
{
}

std::unique_ptr<BoundCompoundStatementNode> InvokeAndCleanupGenerator::GetFunctionBody()
{
    if (currentStatement->IsBoundCompoundStatementNode())
    {
        return std::unique_ptr<BoundCompoundStatementNode>(static_cast<BoundCompoundStatementNode*>(currentStatement.release()));
    }
    else
    {
        ThrowException("compound statement expected", currentStatement->GetSourcePos(), context);
    }
    return std::unique_ptr<BoundCompoundStatementNode>();
}

void InvokeAndCleanupGenerator::GenerateInvokeAndCleanup(bool skipLast)
{
    currentInvoke.reset();
    if (skipLast && cleanup.ContainsOne()) return;
    if (cleanup.IsEmpty()) return;
    if (invoke.IsEmpty()) return;
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
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
    FunctionDefinitionSymbol* cleanupFnSymbol = MakeCleanupFn(cleanup, skipLast, context->GetSymbolTable()->CurrentScope(), functionDefinitionSymbol, context);
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
    if (functionDefinitionSymbol->ParentFn())
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
    context->PopFlags();
    Instantiator invokeInstantiator(context, &invokeInstantiationScope);
    context->PushSetFlag(ContextFlags::saveDeclarations | ContextFlags::dontBind);
    invokeBlock->Accept(invokeInstantiator);
    context->PopFlags();
    std::unique_ptr<BoundCompoundStatementNode> boundInvokeBlock(static_cast<BoundCompoundStatementNode*>(
        BindStatement(invokeBlock.get(), functionDefinitionSymbol, context)));
    if (invoke.HasStatementsWithDestructor())
    {
        boundInvokeBlock->SetInvokeStatementsWithDestructor(invoke.StatementsWithDestructor());
    }
    context->GetSymbolTable()->EndScope();
    currentInvoke.reset(boundInvokeBlock.release());
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    context->IncInvokes();
}

BoundVariableNode* InvokeAndCleanupGenerator::ConvertCondition(BoundExpressionNode* condition, const soul::ast::SourcePos& sourcePos)
{
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    std::vector<TypeSymbol*> templateArgs;
    TypeSymbol* boolType = context->GetSymbolTable()->GetFundamentalTypeSymbol(FundamentalTypeKind::boolType);
    VariableSymbol* localVariable = context->GetSymbolTable()->AddVariable(context->NextConditionVariableName(), nullptr, boolType, boolType,
        nullptr, DeclarationFlags::none, context);
    std::vector<std::unique_ptr<BoundExpressionNode>> arguments;
    BoundVariableNode* boundVariable = new BoundVariableNode(localVariable, sourcePos);
    arguments.push_back(std::unique_ptr<BoundExpressionNode>(new BoundAddressOfNode(boundVariable, sourcePos, boundVariable->GetType()->AddPointer(context))));
    arguments.push_back(std::unique_ptr<BoundExpressionNode>(condition->Clone()));
    std::unique_ptr<BoundFunctionCallNode> constructorCall = ResolveOverloadThrow(context->GetSymbolTable()->CurrentScope(),
        U"@constructor", templateArgs, arguments, sourcePos, context);
    BoundConstructionStatementNode* boundConstructionStatement = new BoundConstructionStatementNode(sourcePos, constructorCall.release());
    boundConstructionStatement->SetSource(new otava::ast::BoundStatementNode(boundConstructionStatement->Clone(), sourcePos));
    boundConstructionStatement->SetVariable(localVariable);
    functionDefinitionSymbol->AddLocalVariable(localVariable);
    Emit(boundConstructionStatement);
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    return new BoundVariableNode(localVariable, sourcePos);
}

void InvokeAndCleanupGenerator::Emit(BoundStatementNode* stmt)
{
    currentInvoke.reset();
    currentStatement.reset();
    if (stmt->MayThrow() && !cleanup.IsEmpty())
    {
        if (cleanup.Changed())
        {
            GenerateInvokeAndCleanup(true);
        }
        invoke.Add(stmt);
        if (stmt->ConstructsLocalVariableWithDestructor())
        {
            GenerateInvokeAndCleanup(false);
        }
    }
    else
    {
        GenerateInvokeAndCleanup(false);
        currentStatement.reset(stmt);
    }
    if (currentInvoke && currentStatement)
    {
        BoundSequenceStatementNode* sequence = new BoundSequenceStatementNode(stmt->GetSourcePos(), currentInvoke.release(), currentStatement.release());
        currentStatement.reset(sequence);
    }
    else if (currentInvoke)
    {
        currentStatement.reset(currentInvoke.release());
    }
    else if (!currentStatement)
    {
        BoundEmptyStatementNode* empty = new BoundEmptyStatementNode(stmt->GetSourcePos());
        currentStatement.reset(empty);
    }
}

void InvokeAndCleanupGenerator::AddCurrentInvokeToCurrentCompound()
{
    if (currentInvoke)
    {
        if (currentInvoke->HasInvokeStatementsWithDestructor())
        {
            std::vector<std::unique_ptr<BoundConstructionStatementNode>> constructionStatements = currentInvoke->ReleaseInvokeStatementsWithDestructor();
            for (auto& constructionStatementNode : constructionStatements)
            {
                currentInvokeStatementsWithDestructor->push_back(std::move(constructionStatementNode));
            }
        }
        currentCompound->AddStatement(currentInvoke.release());
    }
}

void InvokeAndCleanupGenerator::Visit(BoundCompoundStatementNode& node)
{
    int blockId = node.BlockId();
    context->PushParentBlockId(blockId);
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
    BoundCompoundStatementNode* compound = new BoundCompoundStatementNode(node.GetSourcePos());
    cleanup.PushCleanupBlock();
    BoundCompoundStatementNode* prevCompound = currentCompound;
    currentCompound = compound;
    std::vector<std::unique_ptr<BoundConstructionStatementNode>> invokeStatementsWithDestructor;
    std::vector<std::unique_ptr<BoundConstructionStatementNode>>* prevInvokeStatementsWithDestructor = currentInvokeStatementsWithDestructor;
    currentInvokeStatementsWithDestructor = &invokeStatementsWithDestructor;
    for (const auto& stmt : node.Statements())
    {
        stmt->Accept(*this);
        if (currentStatement->HasInvokeStatementsWithDestructor())
        {
            std::vector<std::unique_ptr<BoundConstructionStatementNode>> constructionStatements = currentStatement->ReleaseInvokeStatementsWithDestructor(); 
            for (auto& constructionStatementNode : constructionStatements)
            {
                invokeStatementsWithDestructor.push_back(std::move(constructionStatementNode));
            }
        }
        compound->AddStatement(currentStatement.release());
    }
    GenerateInvokeAndCleanup(false);
    if (currentInvoke)
    {
        if (currentInvoke->HasInvokeStatementsWithDestructor())
        {
            std::vector<std::unique_ptr<BoundConstructionStatementNode>> currentInvokeStatementsWithDestructor = currentStatement->ReleaseInvokeStatementsWithDestructor();
            for (auto& constructionStatementNode : currentInvokeStatementsWithDestructor)
            {
                invokeStatementsWithDestructor.push_back(std::move(constructionStatementNode));
            }
        }
        compound->AddStatement(currentInvoke.release());
    }
    cleanup.PopCleanupBlock();
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
    context->PopParentBlockId();
    if (!invokeStatementsWithDestructor.empty())
    {
        compound->SetInvokeStatementsWithDestructor(std::move(invokeStatementsWithDestructor));
    }
    currentStatement.reset(compound);
    currentCompound = prevCompound;
    currentInvokeStatementsWithDestructor = prevInvokeStatementsWithDestructor;
}

void InvokeAndCleanupGenerator::Visit(BoundIfStatementNode& node)
{
    GenerateInvokeAndCleanup(false);
    AddCurrentInvokeToCurrentCompound();
    int blockId = node.BlockId();
    context->PushParentBlockId(blockId);
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
    if (clone->GetCondition()->MayThrow())
    {
        BoundVariableNode* boundLocalVariable = ConvertCondition(clone->GetCondition(), node.GetSourcePos());
        clone->SetCondition(boundLocalVariable);
    }
    if (clone->ThenStatement()->ContainsLocalVariableWithDestructor())
    {
        node.ThenStatement()->Accept(*this);
        clone->SetThenStatement(currentStatement.release());
    }
    if (clone->ElseStatement() && clone->ElseStatement()->ContainsLocalVariableWithDestructor())
    {
        node.ElseStatement()->Accept(*this);
        clone->SetElseStatement(currentStatement.release());
    }
    Emit(clone.release());
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
    context->PopParentBlockId();
}

void InvokeAndCleanupGenerator::Visit(BoundSwitchStatementNode& node)
{
    GenerateInvokeAndCleanup(false);
    AddCurrentInvokeToCurrentCompound();
    int blockId = node.BlockId();
    context->PushParentBlockId(blockId);
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
    std::unique_ptr<BoundSwitchStatementNode> clone(static_cast<BoundSwitchStatementNode*>(node.Clone()));
    if (clone->GetCondition()->MayThrow())
    {
        BoundVariableNode* boundLocalVariable = ConvertCondition(clone->GetCondition(), node.GetSourcePos());
        clone->SetCondition(boundLocalVariable);
    }
    if (clone->Statement()->ContainsLocalVariableWithDestructor())
    {
        node.Statement()->Accept(*this);
        clone->SetStatement(currentStatement.release());
    }
    Emit(clone.release());
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
    context->PopParentBlockId();
}

void InvokeAndCleanupGenerator::Visit(BoundCaseStatementNode& node)
{
    std::unique_ptr<BoundCaseStatementNode> clone(static_cast<BoundCaseStatementNode*>(node.Clone()));
    if (clone->Statement()->ContainsLocalVariableWithDestructor())
    {
        node.Statement()->Accept(*this);
        clone->SetStatement(currentStatement.release());
    }
    Emit(clone.release());
}

void InvokeAndCleanupGenerator::Visit(BoundDefaultStatementNode& node)
{
    std::unique_ptr<BoundDefaultStatementNode> clone(static_cast<BoundDefaultStatementNode*>(node.Clone()));
    if (clone->Statement()->ContainsLocalVariableWithDestructor())
    {
        node.Statement()->Accept(*this);
        clone->SetStatement(currentStatement.release());
    }
    Emit(clone.release());
}

void InvokeAndCleanupGenerator::Visit(BoundWhileStatementNode& node)
{
    GenerateInvokeAndCleanup(false);
    AddCurrentInvokeToCurrentCompound();
    int blockId = node.BlockId();
    context->PushParentBlockId(blockId);
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
    std::unique_ptr<BoundWhileStatementNode> clone(static_cast<BoundWhileStatementNode*>(node.Clone()));
    if (clone->GetCondition()->MayThrow())
    {
        BoundVariableNode* boundLocalVariable = ConvertCondition(clone->GetCondition(), node.GetSourcePos());
        clone->SetCondition(boundLocalVariable);
    }
    if (clone->Statement()->ContainsLocalVariableWithDestructor())
    {
        node.Statement()->Accept(*this);
        clone->SetStatement(currentStatement.release());
    }
    Emit(clone.release());
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
    context->PopParentBlockId();
}

void InvokeAndCleanupGenerator::Visit(BoundDoStatementNode& node)
{
    GenerateInvokeAndCleanup(false);
    AddCurrentInvokeToCurrentCompound();
    std::unique_ptr<BoundDoStatementNode> clone(static_cast<BoundDoStatementNode*>(node.Clone()));
    if (clone->Statement()->ContainsLocalVariableWithDestructor())
    {
        node.Statement()->Accept(*this);
        clone->SetStatement(currentStatement.release());
    }
    Emit(clone.release());
}

void InvokeAndCleanupGenerator::Visit(BoundForStatementNode& node)
{
    GenerateInvokeAndCleanup(false);
    AddCurrentInvokeToCurrentCompound();
    int blockId = node.BlockId();
    context->PushParentBlockId(blockId);
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
    std::unique_ptr<BoundForStatementNode> clone(static_cast<BoundForStatementNode*>(node.Clone()));
    if (clone->GetCondition()->MayThrow())
    {
        BoundVariableNode* boundLocalVariable = ConvertCondition(clone->GetCondition(), node.GetSourcePos());
        clone->SetCondition(boundLocalVariable);
    }
    if (clone->Statement()->ContainsLocalVariableWithDestructor())
    {
        node.Statement()->Accept(*this);
        clone->SetStatement(currentStatement.release());
    }
    Emit(clone.release());
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
    context->PopParentBlockId();
}

void InvokeAndCleanupGenerator::Visit(BoundSequenceStatementNode& node)
{
    std::unique_ptr<BoundSequenceStatementNode> clone(static_cast<BoundSequenceStatementNode*>(node.Clone()));
    if (node.First()->ContainsLocalVariableWithDestructor())
    {
        node.First()->Accept(*this);
        clone->SetFirst(currentStatement.release());
    }
    if (node.Second()->ContainsLocalVariableWithDestructor())
    {
        node.Second()->Accept(*this);
        clone->SetSecond(currentStatement.release());
    }
    Emit(clone.release());
}

void InvokeAndCleanupGenerator::Visit(BoundBreakStatementNode& node)
{
    Emit(node.Clone());
}

void InvokeAndCleanupGenerator::Visit(BoundContinueStatementNode& node)
{
    Emit(node.Clone());
}

void InvokeAndCleanupGenerator::Visit(BoundReturnStatementNode& node)
{
    Emit(node.Clone());
}

void InvokeAndCleanupGenerator::Visit(BoundGotoStatementNode& node)
{
    Emit(node.Clone());
}

void InvokeAndCleanupGenerator::Visit(BoundLabeledStatementNode& node)
{
    std::unique_ptr<BoundLabeledStatementNode> clone(static_cast<BoundLabeledStatementNode*>(node.Clone()));
    if (node.Statement()->ContainsLocalVariableWithDestructor())
    {
        node.Statement()->Accept(*this);
        clone->SetStatement(currentStatement.release());
    }
    Emit(clone.release());
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
    Emit(node.Clone());
    if (node.DestructorCall())
    {
        cleanup.CurrentCleanupBlock()->Add(node.DestructorCall(), context);
    }
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
