module otava.symbols.exception_handling;

import otava.symbols.expr.parser;
import otava.symbols.stmt.parser;
import otava.symbols.block;
import otava.symbols.context;
import otava.symbols.expression.binder;
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
import otava.symbols.type_compare;
import otava.ast;
import util;

namespace otava::symbols {

CleanupBlock::CleanupBlock(Cleanup* cleanup_) : cleanup(cleanup_)
{
}

void CleanupBlock::Add(BoundExpressionNode* destructorCall, Context* context)
{
    BoundExpressionNode* clonedDestructorCall = static_cast<BoundExpressionNode*>(destructorCall->Clone());
    if (clonedDestructorCall->IsBoundFunctionCallNode())
    {
        BoundFunctionCallNode* clonedDtorCall = static_cast<BoundFunctionCallNode*>(clonedDestructorCall);
        if (!clonedDtorCall->Args().empty())
        {
            BoundNode* firstArg = clonedDtorCall->Args().front().get();
            if (firstArg->IsBoundAddressOfNode())
            {
                BoundAddressOfNode* boundAddrOfNode = static_cast<BoundAddressOfNode*>(firstArg);
                if (boundAddrOfNode->Subject()->IsBoundVariableNode())
                {
                    BoundVariableNode* boundVariable = static_cast<BoundVariableNode*>(boundAddrOfNode->Subject());
                    BoundParentVariableNode* boundParentVariable = new BoundParentVariableNode(boundVariable->GetVariable(), boundVariable->GetSourcePos());
                    boundAddrOfNode->SetSubject(boundParentVariable);
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
    }
    else
    {
        ThrowException("bound function call node expected", clonedDestructorCall->GetSourcePos(), context);
    }
    destructorCalls.push_back(std::unique_ptr<BoundExpressionNode>(clonedDestructorCall));
    cleanup->SetChanged();
}

void CleanupBlock::Make(otava::ast::CompoundStatementNode* compoundStatement)
{
    int n = destructorCalls.size();
    int end = n - 1;
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

class BoundNodeStack
{
public:
    BoundNodeStack(Context* context_);
    inline void Push(BoundNode* node)
    {
        s.push(node);
    }
    inline BoundNode* Pop()
    {
        if (s.empty())
        {
            ThrowException("bound node stack is empty", soul::ast::SourcePos(), context);
        }
        BoundNode* top = s.top();
        s.pop();
        return top;
    }
private:
    Context* context;
    std::stack<BoundNode*> s;
};

BoundNodeStack::BoundNodeStack(Context* context_) : context(context_)
{
}

class InvokeAndCleanupGenerator : public DefaultBoundTreeVisitor
{
public:
    InvokeAndCleanupGenerator(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_);
    void Visit(BoundFunctionNode& boundFunction) override;
    void Visit(BoundCtorInitializerNode& node) override;
    void Visit(BoundDtorTerminatorNode& node) override;
    void Visit(BoundEmptyStatementNode& node) override;
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
    void Visit(BoundValueExpressionNode& node) override;
    void Visit(BoundLiteralNode& node) override;
    void Visit(BoundStringLiteralNode& node) override;
    void Visit(BoundVariableNode& node) override;
    void Visit(BoundParentVariableNode& node) override;
    void Visit(BoundParameterNode& node) override;
    void Visit(BoundParentParameterNode& node) override;
    void Visit(BoundEnumConstant& node) override;
    void Visit(BoundFunctionGroupNode& node) override;
    void Visit(BoundClassGroupNode& node) override;
    void Visit(BoundAliasGroupNode& node) override;
    void Visit(BoundTypeNode& node) override;
    void Visit(BoundMemberExprNode& node) override;
    void Visit(BoundFunctionCallNode& node) override;
    void Visit(BoundEmptyFunctionCallNode& node) override;
    void Visit(BoundFunctionPtrCallNode& node) override;
    void Visit(BoundExpressionSequenceNode& node) override;
    void Visit(BoundExpressionListNode& node) override;
    void Visit(BoundConjunctionNode& node) override;
    void Visit(BoundDisjunctionNode& node) override;
    void Visit(BoundConditionalExprNode& node) override;
    void Visit(BoundConversionNode& node) override;
    void Visit(BoundAddressOfNode& node) override;
    void Visit(BoundDereferenceNode& node) override;
    void Visit(BoundRefToPtrNode& node) override;
    void Visit(BoundPtrToRefNode& node) override;
    void Visit(BoundDefaultInitNode& node) override;
    void Visit(BoundTemporaryNode& node) override;
    void Visit(BoundConstructTemporaryNode& node) override;
    void Visit(BoundConstructExpressionNode& node) override;
    void Visit(BoundGlobalVariableDefinitionNode& node) override;
    void Visit(BoundEmptyDestructorNode& node) override;
    void Visit(BoundFunctionValueNode& node) override;
    void Visit(BoundVariableAsVoidPtrNode& node) override;
    void Visit(BoundOperatorFnNode& node) override;
    BoundInvokeNode* MakeInvokeAndCleanup(BoundFunctionCallNode* fnCall);
    void SetDestructTemporariesNode(BoundDestructTemporariesNode* destructTemporariesNode_);
private:
    Context* context;
    FunctionDefinitionSymbol* functionDefinitionSymbol;
    BoundNodeStack s;
    Cleanup cleanup;
    std::unique_ptr<BoundDestructTemporariesNode> destructTemporariesNode;
};

FunctionDefinitionSymbol* MakeInvokeFn(BoundFunctionCallNode* fnCall, Scope* parentFnScope, FunctionDefinitionSymbol* parentFn,
    InvokeAndCleanupGenerator* generator, Context* context)
{
    soul::ast::SourcePos sourcePos = fnCall->GetSourcePos();
    bool prevInternallyMapped = context->GetModule()->GetNodeIdFactory()->IsInternallyMapped();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(true);
    otava::ast::CompoundStatementNode* invokeBlock = new otava::ast::CompoundStatementNode(sourcePos);
    if (!parentFn->Blocks().empty())
    {
        invokeBlock->SetBlockId(parentFn->Blocks().front()->BlockId());
    }
    if (!fnCall->GetType() || fnCall->GetType()->IsVoidType())
    {
        std::unique_ptr<otava::ast::Node> expr;
        expr.reset(fnCall->Source()->Clone());
        if (expr->IsSimpleDeclarationNode())
        {
            invokeBlock->AddNode(expr.release());
        }
        else
        {
            otava::ast::ExpressionStatementNode* exprStmt = new otava::ast::ExpressionStatementNode(sourcePos, expr.release(), nullptr, nullptr);
            invokeBlock->AddNode(exprStmt);
        }
    }
    else
    {
        std::unique_ptr<otava::ast::DeclarationStatementNode> declarationStatement = DeclarationToAst(
            fnCall->GetType(), context->ResultVarName(), fnCall->Source()->Clone(), sourcePos);
        invokeBlock->AddNode(declarationStatement.release());
    }
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
    BoundFunctionNode* boundFunction = new BoundFunctionNode(invokeFnSymbol, sourcePos);
    context->PushBoundFunction(boundFunction);
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
    invokeFnSymbol->SetFnDefNode(invokeFnNode.release());
    if (boundFunction->HasTemporaryDestructorCalls())
    {
        generator->SetDestructTemporariesNode(new BoundDestructTemporariesNode(sourcePos, boundFunction->GetTemporaryDestructorCalls()));
    }
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
    context->GetSymbolTable()->EndScope();
    cleanupInstantiationScope.PopParentScope();
    context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
    cleanupFnSymbol->SetFnDefNode(cleanupFnNode.release());
    cleanup.ResetChanged();
    return cleanupFnSymbol;
}

InvokeAndCleanupGenerator::InvokeAndCleanupGenerator(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_) :
    context(context_), functionDefinitionSymbol(functionDefinitionSymbol_), s(context)
{
}

BoundInvokeNode* InvokeAndCleanupGenerator::MakeInvokeAndCleanup(BoundFunctionCallNode* fnCall)
{
    std::unique_ptr<BoundInvokeNode> boundInvoke(new BoundInvokeNode(fnCall->GetSourcePos(), fnCall->GetType()));
    TypeSymbol* resultType = fnCall->GetType();
    bool hasResult = resultType && !resultType->IsVoidType();
    if (hasResult)
    {
        std::u32string resultVarName = context->NextResultVarName();
        VariableSymbol* resultVar = context->GetSymbolTable()->AddVariable(resultVarName, fnCall->Source(), resultType, nullptr, nullptr, DeclarationFlags::none, context);
        BoundVariableNode* boundResultVar = new BoundVariableNode(resultVar, fnCall->GetSourcePos());
        boundInvoke->SetResult(boundResultVar);
        context->PushResultVarName(resultVarName);
    }
    FunctionDefinitionSymbol* invokeFnSymbol = MakeInvokeFn(
        fnCall, context->GetSymbolTable()->CurrentScope(), functionDefinitionSymbol, this, context);
    FunctionDefinitionSymbol* cleanupFnSymbol = MakeCleanupFn(
        cleanup, context->GetSymbolTable()->CurrentScope(), functionDefinitionSymbol, context);
    std::u32string invokeCallText;
    invokeCallText.append(U"ort_invoke(").append(invokeFnSymbol->Name()).
        append(U", ").append(cleanupFnSymbol->Name()).append(U", ").
        append(U"__intrinsic_get_frame_ptr()").append(U")");
    std::unique_ptr<otava::ast::Node> invokeCallNode = ParseExpression(invokeCallText, context);
    std::unique_ptr<BoundExpressionNode> invokeCall(BindExpression(invokeCallNode.get(), context));
    boundInvoke->SetInvokeCall(invokeCall.release());
    if (hasResult)
    {
        context->PopResultVarName();
    }
    context->IncInvokes();
    return boundInvoke.release();
}

void InvokeAndCleanupGenerator::SetDestructTemporariesNode(BoundDestructTemporariesNode* destructTemporariesNode_)
{
    if (destructTemporariesNode)
    {
        std::unique_ptr<BoundDestructTemporariesNode> that(destructTemporariesNode_);
        destructTemporariesNode->Merge(that.get());
    }
    else
    {
        destructTemporariesNode.reset(destructTemporariesNode_);
    }
}

void InvokeAndCleanupGenerator::Visit(BoundFunctionNode& boundFunction)
{
    if (boundFunction.CtorInitializer())
    {
        boundFunction.CtorInitializer()->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundCtorInitializerNode())
        {
            BoundCtorInitializerNode* in = static_cast<BoundCtorInitializerNode*>(n);
            boundFunction.SetCtorInitializer(in);
        }
        else
        {
            ThrowException("constructor initializer node expected", n->GetSourcePos(), context);
        }
    }
    if (boundFunction.DtorTerminator())
    {
        boundFunction.DtorTerminator()->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundDtorTerminatorNode())
        {
            BoundDtorTerminatorNode* dn = static_cast<BoundDtorTerminatorNode*>(n);
            boundFunction.SetDtorTerminator(dn);
        }
        else
        {
            ThrowException("destructor terminator node expected", n->GetSourcePos(), context);
        }
    }
    boundFunction.Body()->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundCompoundStatementNode())
    {
        BoundCompoundStatementNode* cn = static_cast<BoundCompoundStatementNode*>(n);
        boundFunction.SetBody(cn);
    }
    else
    {
        ThrowException("compound statement node expected", n->GetSourcePos(), context);
    }
}

void InvokeAndCleanupGenerator::Visit(BoundCtorInitializerNode& node)
{
    BoundCtorInitializerNode* clone = new BoundCtorInitializerNode(node.GetSourcePos());
    for (const auto& baseInitializer : node.BaseInitializers())
    {
        baseInitializer->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundExpressionNode())
        {
            BoundExpressionNode* fn = static_cast<BoundExpressionNode*>(n);
            clone->AddBaseInitializer(fn);
        }
        else
        {
            ThrowException("function call node expected", n->GetSourcePos(), context);
        }
    }
    for (const auto& statement : node.SetVPtrStatements())
    {
        statement->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundStatementNode())
        {
            BoundStatementNode* sn = static_cast<BoundStatementNode*>(n);
            clone->AddSetVPtrStatement(sn);
        }
        else
        {
            ThrowException("statement node expected", n->GetSourcePos(), context);
        }
    }
    for (const auto& memberInitializer : node.MemberInitializers())
    {
        memberInitializer->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundExpressionNode())
        {
            BoundExpressionNode* fn = static_cast<BoundExpressionNode*>(n);
            clone->AddMemberInitializer(fn);
        }
        else
        {
            ThrowException("function call node expected", n->GetSourcePos(), context);
        }
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundDtorTerminatorNode& node)
{
    BoundDtorTerminatorNode* clone = new BoundDtorTerminatorNode(node.GetSourcePos());
    for (const auto& statement : node.SetVPtrStatements())
    {
        statement->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundStatementNode())
        {
            BoundStatementNode* sn = static_cast<BoundStatementNode*>(n);
            clone->AddSetVPtrStatement(sn);
        }
        else
        {
            ThrowException("statement node expected", n->GetSourcePos(), context);
        }
    }
    for (const auto& memberTerminator : node.MemberTerminators())
    {
        memberTerminator->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundExpressionNode())
        {
            BoundExpressionNode* fn = static_cast<BoundExpressionNode*>(n);
            clone->AddMemberTerminator(fn);
        }
        else
        {
            ThrowException("function call node expected", n->GetSourcePos(), context);
        }
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundEmptyStatementNode& node)
{
    BoundEmptyStatementNode* clone = new BoundEmptyStatementNode(node.GetSourcePos());
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundCompoundStatementNode& node)
{
    int blockId = node.BlockId();
    context->PushParentBlockId(blockId);
    context->PushParentStatementIndex(node.StatementIndex());
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
        }
    }
    BoundCompoundStatementNode* clone = new BoundCompoundStatementNode(node.GetSourcePos());
    clone->SetBlockId(node.BlockId());
    cleanup.PushCleanupBlock();
    for (const auto& statement : node.Statements())
    {
        statement->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundStatementNode())
        {
            BoundStatementNode* sn = static_cast<BoundStatementNode*>(n);
            clone->AddStatement(sn);
        }
        else
        {
            ThrowException("statement node expected", n->GetSourcePos(), context);
        }
    }
    cleanup.PopCleanupBlock();
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
    context->PopParentStatementIndex();
    context->PopParentBlockId();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundIfStatementNode& node)
{
    int blockId = node.BlockId();
    context->PushParentBlockId(blockId);
    context->PushParentStatementIndex(node.StatementIndex());
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
        }
    }
    BoundIfStatementNode* clone = new BoundIfStatementNode(node.GetSourcePos());
    clone->SetBlockId(node.BlockId());
    BoundExpressionNode* condition = node.GetCondition();
    condition->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetCondition(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    BoundStatementNode* thenStatement = node.ThenStatement();
    thenStatement->Accept(*this);
    BoundNode* tn = s.Pop();
    if (tn->IsBoundStatementNode())
    {
        BoundStatementNode* sn = static_cast<BoundStatementNode*>(tn);
        clone->SetThenStatement(sn);
    }
    else
    {
        ThrowException("statement node expected", tn->GetSourcePos(), context);
    }
    BoundStatementNode* elseStatement = node.ElseStatement();
    if (elseStatement)
    {
        elseStatement->Accept(*this);
        BoundNode* en = s.Pop();
        if (en->IsBoundStatementNode())
        {
            BoundStatementNode* sn = static_cast<BoundStatementNode*>(en);
            clone->SetElseStatement(sn);
        }
        else
        {
            ThrowException("statement node expected", en->GetSourcePos(), context);
        }
    }
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
    context->PopParentStatementIndex();
    context->PopParentBlockId();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundSwitchStatementNode& node)
{
    int blockId = node.BlockId();
    context->PushParentBlockId(blockId);
    context->PushParentStatementIndex(node.StatementIndex());
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
        }
    }
    BoundSwitchStatementNode* clone = new BoundSwitchStatementNode(node.GetSourcePos());
    clone->SetBlockId(node.BlockId());
    BoundExpressionNode* condition = node.GetCondition();
    condition->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetCondition(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    BoundStatementNode* statement = node.Statement();
    statement->Accept(*this);
    BoundNode* sn = s.Pop();
    if (sn->IsBoundStatementNode())
    {
        BoundStatementNode* cs = static_cast<BoundStatementNode*>(sn);
        clone->SetStatement(cs);
    }
    else
    {
        ThrowException("statement node expected", sn->GetSourcePos(), context);
    }
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
    context->PopParentStatementIndex();
    context->PopParentBlockId();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundCaseStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundCaseStatementNode* clone = new BoundCaseStatementNode(node.GetSourcePos());
    for (const auto& caseExpr : node.CaseExprs())
    {
        caseExpr->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundExpressionNode())
        {
            BoundExpressionNode* ce = static_cast<BoundExpressionNode*>(n);
            clone->AddCaseExpr(ce);
        }
        else
        {
            ThrowException("expression node expected", n->GetSourcePos(), context);
        }
    }
    BoundStatementNode* statement = node.Statement();
    statement->Accept(*this);
    BoundNode* sn = s.Pop();
    if (sn->IsBoundStatementNode())
    {
        BoundStatementNode* cs = static_cast<BoundStatementNode*>(sn);
        clone->SetStatement(cs);
    }
    else
    {
        ThrowException("statement node expected", sn->GetSourcePos(), context);
    }
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundDefaultStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundDefaultStatementNode* clone = new BoundDefaultStatementNode(node.GetSourcePos());
    BoundStatementNode* statement = node.Statement();
    statement->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundStatementNode())
    {
        BoundStatementNode* cs = static_cast<BoundStatementNode*>(n);
        clone->SetStatement(cs);
    }
    else
    {
        ThrowException("statement node expected", n->GetSourcePos(), context);
    }
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundWhileStatementNode& node)
{
    int blockId = node.BlockId();
    context->PushParentBlockId(blockId);
    context->PushParentStatementIndex(node.StatementIndex());
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
        }
    }
    BoundWhileStatementNode* clone = new BoundWhileStatementNode(node.GetSourcePos());
    clone->SetBlockId(node.BlockId());
    BoundExpressionNode* condition = node.GetCondition();
    condition->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* cn = static_cast<BoundExpressionNode*>(n);
        clone->SetCondition(cn);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    BoundStatementNode* statement = node.Statement();
    statement->Accept(*this);
    BoundNode* sn = s.Pop();
    if (sn->IsBoundStatementNode())
    {
        BoundStatementNode* cs = static_cast<BoundStatementNode*>(sn);
        clone->SetStatement(cs);
    }
    else
    {
        ThrowException("statement node expected", sn->GetSourcePos(), context);
    }
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
    context->PopParentStatementIndex();
    context->PopParentBlockId();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundDoStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundDoStatementNode* clone = new BoundDoStatementNode(node.GetSourcePos());
    s.Push(clone);
    BoundExpressionNode* expr = node.GetExpr();
    expr->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetExpr(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    BoundStatementNode* statement = node.Statement();
    statement->Accept(*this);
    BoundNode* sn = s.Pop();
    if (sn->IsBoundStatementNode())
    {
        BoundStatementNode* cs = static_cast<BoundStatementNode*>(sn);
        clone->SetStatement(cs);
    }
    else
    {
        ThrowException("statement node expected", sn->GetSourcePos(), context);
    }
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundForStatementNode& node)
{
    int blockId = node.BlockId();
    context->PushParentBlockId(blockId);
    context->PushParentStatementIndex(node.StatementIndex());
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
        }
    }
    BoundForStatementNode* clone = new BoundForStatementNode(node.GetSourcePos());
    clone->SetBlockId(node.BlockId());
    BoundStatementNode* initStatement = node.InitStatement();
    if (initStatement)
    {
        initStatement->Accept(*this);
        BoundNode* sn = s.Pop();
        if (sn->IsBoundStatementNode())
        {
            BoundStatementNode* cs = static_cast<BoundStatementNode*>(sn);
            clone->SetInitStatement(cs);
        }
        else
        {
            ThrowException("statement node expected", sn->GetSourcePos(), context);
        }
    }
    BoundExpressionNode* condition = node.GetCondition();
    if (condition)
    {
        condition->Accept(*this);
        BoundNode* cn = s.Pop();
        if (cn->IsBoundExpressionNode())
        {
            BoundExpressionNode* en = static_cast<BoundExpressionNode*>(cn);
            clone->SetCondition(en);
        }
        else
        {
            ThrowException("expression node expected", cn->GetSourcePos(), context);
        }
    }
    BoundExpressionNode* loopExpr = node.GetLoopExpr();
    if (loopExpr)
    {
        loopExpr->Accept(*this);
        BoundNode* ln = s.Pop();
        if (ln->IsBoundExpressionNode())
        {
            BoundExpressionNode* en = static_cast<BoundExpressionNode*>(ln);
            clone->SetLoopExpr(en);
        }
        else
        {
            ThrowException("expression node expected", ln->GetSourcePos(), context);
        }
    }
    BoundStatementNode* statement = node.Statement();
    statement->Accept(*this);
    BoundNode* sn = s.Pop();
    if (sn->IsBoundStatementNode())
    {
        BoundStatementNode* cs = static_cast<BoundStatementNode*>(sn);
        clone->SetStatement(cs);
    }
    else
    {
        ThrowException("statement node expected", sn->GetSourcePos(), context);
    }
    if (scope)
    {
        context->GetSymbolTable()->EndScopeGeneric(context);
    }
    context->PopParentStatementIndex();
    context->PopParentBlockId();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundSequenceStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundSequenceStatementNode* clone = new BoundSequenceStatementNode(node.GetSourcePos());
    BoundStatementNode* first = node.First();
    first->Accept(*this);
    BoundNode* fn = s.Pop();
    if (fn->IsBoundStatementNode())
    {
        BoundStatementNode* cs = static_cast<BoundStatementNode*>(fn);
        clone->SetFirst(cs);
    }
    else
    {
        ThrowException("statement node expected", fn->GetSourcePos(), context);
    }
    BoundStatementNode* second = node.Second();
    second->Accept(*this);
    BoundNode* sn = s.Pop();
    if (sn->IsBoundStatementNode())
    {
        BoundStatementNode* cs = static_cast<BoundStatementNode*>(sn);
        clone->SetSecond(cs);
    }
    else
    {
        ThrowException("statement node expected", sn->GetSourcePos(), context);
    }
    context->PopParentStatementIndex();
    if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundBreakStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundBreakStatementNode* clone = new BoundBreakStatementNode(node.GetSourcePos());
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundContinueStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundContinueStatementNode* clone = new BoundContinueStatementNode(node.GetSourcePos());
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundReturnStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundReturnStatementNode* clone = new BoundReturnStatementNode(node.GetSourcePos());
    BoundExpressionNode* expr = node.GetExpr();
    if (expr)
    {
        expr->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundExpressionNode())
        {
            BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
            clone->SetExpr(en);
        }
        else
        {
            ThrowException("expression node expected", n->GetSourcePos(), context);
        }
    }
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundGotoStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundGotoStatementNode* clone = new BoundGotoStatementNode(node.GetSourcePos());
    clone->SetTarget(node.Target());
    clone->SetLabeledStatement(node.GetLabeledStatement());
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundLabeledStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundLabeledStatementNode* clone = new BoundLabeledStatementNode(node.GetSourcePos());
    clone->SetLabel(node.Label());
    BoundStatementNode* statement = node.Statement();
    statement->Accept(*this);
    BoundNode* sn = s.Pop();
    if (sn->IsBoundStatementNode())
    {
        BoundStatementNode* cs = static_cast<BoundStatementNode*>(sn);
        clone->SetStatement(cs);
    }
    else
    {
        ThrowException("statement node expected", sn->GetSourcePos(), context);
    }
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundSetVPtrStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundSetVPtrStatementNode* clone = new BoundSetVPtrStatementNode(node.GetSourcePos());
    node.ThisPtr()->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* tn = static_cast<BoundExpressionNode*>(n);
        clone->SetThisPtr(tn);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    clone->SetForClass(node.GetClass());
    clone->SetVPtrHolderClass(node.GetVPtrHolderClass());
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundAliasDeclarationStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundAliasDeclarationStatementNode* clone = new BoundAliasDeclarationStatementNode(node.GetSourcePos());
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundConstructionStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundConstructionStatementNode* clone = new BoundConstructionStatementNode(node.GetSourcePos());
    BoundExpressionNode* ctorCall = node.ConstructorCall();
    ctorCall->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* cn = static_cast<BoundExpressionNode*>(n);
        clone->SetConstructorCall(cn);
    }
    else
    {
        ThrowException("function call node expected", n->GetSourcePos(), context);
    }
    BoundExpressionNode* dtorCall = node.DestructorCall();
    if (dtorCall)
    {
        dtorCall->Accept(*this);
        BoundNode* dn = s.Pop();
        if (dn->IsBoundExpressionNode())
        {
            BoundExpressionNode* fn = static_cast<BoundExpressionNode*>(dn);
            clone->SetDestructorCall(fn);
        }
        else
        {
            ThrowException("function call node expected", n->GetSourcePos(), context);
        }
        cleanup.CurrentCleanupBlock()->Add(dtorCall, context);
    }
    clone->SetVariable(node.Variable());
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundExpressionStatementNode& node)
{
    context->PushParentStatementIndex(node.StatementIndex());
    BoundExpressionStatementNode* clone = new BoundExpressionStatementNode(node.GetSourcePos());
    BoundExpressionNode* expr = node.GetExpr();
    if (expr)
    {
        expr->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundExpressionNode())
        {
            BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
            clone->SetExpr(en);
        }
        else
        {
            ThrowException("expression node expected", n->GetSourcePos(), context);
        }
    }
    context->PopParentStatementIndex();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundValueExpressionNode& node)
{
    ThrowException("value expression node not supported", node.GetSourcePos(), context);
}

void InvokeAndCleanupGenerator::Visit(BoundLiteralNode& node)
{
    BoundExpressionNode* clone = node.Clone();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundStringLiteralNode& node)
{
    BoundExpressionNode* clone = node.Clone();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundVariableNode& node)
{
    BoundVariableNode* clone = new BoundVariableNode(node.GetVariable(), node.GetSourcePos());
    if (node.ThisPtr())
    {
        node.ThisPtr()->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundExpressionNode())
        {
            BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
            clone->SetThisPtr(en);
        }
        else
        {
            ThrowException("expression node expected", n->GetSourcePos(), context);
        }
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundParentVariableNode& node)
{
    BoundParentVariableNode* clone = new BoundParentVariableNode(node.GetVariable(), node.GetSourcePos());
    clone->SetLevel(node.Level());
    if (node.ThisPtr())
    {
        node.ThisPtr()->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundExpressionNode())
        {
            BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
            clone->SetThisPtr(en);
        }
        else
        {
            ThrowException("expression node expected", n->GetSourcePos(), context);
        }
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundParameterNode& node)
{
    BoundParameterNode* clone = new BoundParameterNode(node.GetParameter(), node.GetSourcePos(), node.GetType());
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundParentParameterNode& node)
{
    BoundParentParameterNode* clone = new BoundParentParameterNode(node.GetParameter(), node.GetSourcePos(), node.GetType());
    clone->SetLevel(node.Level());
    clone->SetFlags(node.Flags());
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundEnumConstant& node)
{
    BoundExpressionNode* clone = node.Clone();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundFunctionGroupNode& node)
{
    BoundExpressionNode* clone = node.Clone();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundClassGroupNode& node)
{
    BoundExpressionNode* clone = node.Clone();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundAliasGroupNode& node)
{
    BoundExpressionNode* clone = node.Clone();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundTypeNode& node)
{
    BoundExpressionNode* clone = node.Clone();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundMemberExprNode& node)
{
    BoundMemberExprNode* clone = new BoundMemberExprNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* subject = node.Subject();
    subject->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetSubject(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    BoundExpressionNode* member = node.Member();
    member->Accept(*this);
    BoundNode* nm = s.Pop();
    if (nm->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(nm);
        clone->SetMember(en);
    }
    else
    {
        ThrowException("expression node expected", nm->GetSourcePos(), context);
    }
    clone->SetOp(node.Op());
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundFunctionCallNode& node)
{
    if (node.MayThrow() && !cleanup.IsEmpty() && node.Source())
    {
        BoundInvokeNode* boundInvoke = MakeInvokeAndCleanup(&node);
        if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
        {
            boundInvoke->SetDestructTemporariesNode(destructTemporariesNode.release());
        }
        s.Push(boundInvoke);
    }
    else
    {
        if (node.MayThrow() && !cleanup.IsEmpty() && !node.Source())
        {
            //std::cout << "NODE SOURCE NULL: " << util::ToUtf8(node.GetFunctionSymbol()->FullName()) << "\n";
            context->IncUnresolvedInvokes();
        }
        BoundFunctionCallNode* clone = new BoundFunctionCallNode(node.GetFunctionSymbol(), node.GetSourcePos(), node.GetType());
        for (const auto& arg : node.Args())
        {
            arg->Accept(*this);
            BoundNode* n = s.Pop();
            if (n->IsBoundExpressionNode())
            {
                BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
                clone->AddArgument(en);
            }
            else
            {
                ThrowException("expression node expected", n->GetSourcePos(), context);
            }
        }
        clone->SetFlags(node.Flags());
        if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
        {
            clone->SetDestructTemporariesNode(destructTemporariesNode.release());
        }
        else if (node.DestructTemporariesNode())
        {
            clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
        }
        s.Push(clone);
    }
}

void InvokeAndCleanupGenerator::Visit(BoundEmptyFunctionCallNode& node)
{
    BoundExpressionNode* clone = node.Clone();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundFunctionPtrCallNode& node)
{
    BoundFunctionPtrCallNode* clone = new BoundFunctionPtrCallNode(node.GetSourcePos(), node.GetType());
    for (const auto& arg : node.Args())
    {
        arg->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundExpressionNode())
        {
            BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
            clone->AddArgument(en);
        }
        else
        {
            ThrowException("expression node expected", n->GetSourcePos(), context);
        }
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundExpressionSequenceNode& node)
{
    BoundExpressionSequenceNode* clone = new BoundExpressionSequenceNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* left = node.Left();
    left->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        if (destructTemporariesNode)
        {
            en->SetDestructTemporariesNode(destructTemporariesNode.release());
        }
        clone->SetLeft(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    BoundExpressionNode* right = node.Right();
    right->Accept(*this);
    BoundNode* rn = s.Pop();
    if (rn->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(rn);
        if (destructTemporariesNode)
        {
            en->SetDestructTemporariesNode(destructTemporariesNode.release());
        }
        clone->SetRight(en);
    }
    else
    {
        ThrowException("expression node expected", rn->GetSourcePos(), context);
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundExpressionListNode& node)
{
    BoundExpressionListNode* clone = new BoundExpressionListNode(node.GetSourcePos());
    for (const auto& expr : node.Exprs())
    {
        expr->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundExpressionNode())
        {
            BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
            clone->AddExpression(en);
        }
        else
        {
            ThrowException("expression node expected", n->GetSourcePos(), context);
        }
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundConjunctionNode& node)
{
    BoundConjunctionNode* clone = new BoundConjunctionNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* left = node.Left();
    left->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetLeft(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    BoundExpressionNode* right = node.Right();
    right->Accept(*this);
    BoundNode* rn = s.Pop();
    if (rn->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(rn);
        clone->SetRight(en);
    }
    else
    {
        ThrowException("expression node expected", rn->GetSourcePos(), context);
    }
    if (node.Temporary())
    {
        node.Temporary()->Accept(*this);
        BoundNode* vn = s.Pop();
        if (vn->IsBoundVariableNode())
        {
            BoundVariableNode* tn = static_cast<BoundVariableNode*>(vn);
            clone->SetTemporary(tn);
        }
        else
        {
            ThrowException("variable node expected", vn->GetSourcePos(), context);
        }
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundDisjunctionNode& node)
{
    BoundDisjunctionNode* clone = new BoundDisjunctionNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* left = node.Left();
    left->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetLeft(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    BoundExpressionNode* right = node.Right();
    right->Accept(*this);
    BoundNode* rn = s.Pop();
    if (rn->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(rn);
        clone->SetRight(en);
    }
    else
    {
        ThrowException("expression node expected", rn->GetSourcePos(), context);
    }
    if (node.Temporary())
    {
        node.Temporary()->Accept(*this);
        BoundNode* vn = s.Pop();
        if (vn->IsBoundVariableNode())
        {
            BoundVariableNode* tn = static_cast<BoundVariableNode*>(vn);
            clone->SetTemporary(tn);
        }
        else
        {
            ThrowException("variable node expected", vn->GetSourcePos(), context);
        }
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundConditionalExprNode& node)
{
    BoundConditionalExprNode* clone = new BoundConditionalExprNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* condition = node.GetCondition();
    condition->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetCondition(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    BoundExpressionNode* thenExpr = node.GetThenExpr();
    thenExpr->Accept(*this);
    BoundNode* te = s.Pop();
    if (te->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(te);
        clone->SetThenExpr(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    BoundExpressionNode* elseExpr = node.GetElseExpr();
    elseExpr->Accept(*this);
    BoundNode* ee = s.Pop();
    if (ee->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(ee);
        clone->SetElseExpr(en);
    }
    else
    {
        ThrowException("expression node expected", ee->GetSourcePos(), context);
    }
    BoundVariableNode* temporary = node.Temporary();
    if (temporary)
    {
        temporary->Accept(*this);
        BoundNode* tn = s.Pop();
        if (tn->IsBoundVariableNode())
        {
            BoundVariableNode* vn = static_cast<BoundVariableNode*>(tn);
            clone->SetTemporary(vn);
        }
        else
        {
            ThrowException("variable node expected", ee->GetSourcePos(), context);
        }
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundConversionNode& node)
{
    BoundConversionNode* clone = new BoundConversionNode(node.ConversionFunction(), node.GetSourcePos());
    BoundExpressionNode* subject = node.Subject();
    subject->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetSubject(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundAddressOfNode& node)
{
    BoundAddressOfNode* clone = new BoundAddressOfNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* subject = node.Subject();
    subject->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetSubject(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundDereferenceNode& node)
{
    BoundDereferenceNode* clone = new BoundDereferenceNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* subject = node.Subject();
    subject->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetSubject(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    clone->SetKind(node.Kind());
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundRefToPtrNode& node)
{
    BoundRefToPtrNode* clone = new BoundRefToPtrNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* subject = node.Subject();
    subject->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetSubject(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundPtrToRefNode& node)
{
    BoundPtrToRefNode* clone = new BoundPtrToRefNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* subject = node.Subject();
    subject->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetSubject(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundDefaultInitNode& node)
{
    BoundDefaultInitNode* clone = new BoundDefaultInitNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* subject = node.Subject();
    subject->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetSubject(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundTemporaryNode& node)
{
    BoundTemporaryNode* clone = new BoundTemporaryNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* rvalueExpr = node.RvalueExpr();
    if (rvalueExpr)
    {
        rvalueExpr->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundExpressionNode())
        {
            BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
            clone->SetRvalueExpr(en);
        }
        else
        {
            ThrowException("expression node expected", n->GetSourcePos(), context);
        }
    }
    BoundVariableNode* backingStore = node.BackingStore();
    if (backingStore)
    {
        backingStore->Accept(*this);
        BoundNode* n = s.Pop();
        if (n->IsBoundVariableNode())
        {
            BoundVariableNode* vn = static_cast<BoundVariableNode*>(n);
            clone->SetBackingStore(vn);
        }
        else
        {
            ThrowException("variable node expected", n->GetSourcePos(), context);
        }
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundConstructTemporaryNode& node)
{
    BoundExpressionNode* temporary = node.Temporary();
    temporary->Accept(*this);
    BoundNode* nt = s.Pop();
    VariableSymbol* temporaryVar = nullptr;
    if (nt->IsBoundVariableNode())
    {
        BoundVariableNode* clonedTemporary = static_cast<BoundVariableNode*>(nt);
        temporaryVar = clonedTemporary->GetVariable();
    }
    else if (nt->IsBoundAddressOfNode())
    {
        BoundAddressOfNode* an = static_cast<BoundAddressOfNode*>(nt);
        if (an->Subject()->IsBoundVariableNode())
        {
            BoundVariableNode* clonedTemporary = static_cast<BoundVariableNode*>(an->Subject());
            temporaryVar = clonedTemporary->GetVariable();
        }
    }
    if (context->CurrentProject()->HasDefine("PRINT_TEMPORARIES"))
    {
        std::cout << "CLONE TEMPORARY:" << util::ToUtf8(temporaryVar->Name()) << ":" <<
            util::ToUtf8(temporaryVar->GetType()->FullName()) << ":" << temporaryVar->NodeId() << "\n";
    }
    BoundExpressionNode* constructorCall = node.ConstructorCall();
    constructorCall->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundInvokeNode())
    {
        BoundInvokeNode* invoke = static_cast<BoundInvokeNode*>(n);
        if (invoke->Result() && invoke->GetType() && invoke->GetType()->IsClassTypeSymbol() && TypesEqual(invoke->GetType(), node.GetType(), context))
        {
            s.Push(n);
            return;
        }
    }
    BoundConstructTemporaryNode* clone = new BoundConstructTemporaryNode(node.GetSourcePos(), node.GetType());
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetConstructorCall(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    if (nt->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(nt);
        clone->SetTemporary(en);
    }
    else
    {
        ThrowException("expression node expected", nt->GetSourcePos(), context);
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundConstructExpressionNode& node)
{
    BoundConstructExpressionNode* clone = new BoundConstructExpressionNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* allocation = node.Allocation();
    allocation->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetAllocation(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    BoundExpressionNode* constructObjectCall = node.ConstructObjectCall();
    constructObjectCall->Accept(*this);
    BoundNode* no = s.Pop();
    if (no->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(no);
        clone->SetConstructObjectCall(en);
    }
    else
    {
        ThrowException("expression node expected", no->GetSourcePos(), context);
    }
    clone->SetHasPlacement(node.HasPlacement());
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundGlobalVariableDefinitionNode& node)
{
    BoundGlobalVariableDefinitionNode* clone = new BoundGlobalVariableDefinitionNode(node.GetGlobalVariable(), node.GetSourcePos());
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundEmptyDestructorNode& node)
{
    BoundExpressionNode* clone = node.Clone();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundFunctionValueNode& node)
{
    BoundExpressionNode* clone = node.Clone();
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundVariableAsVoidPtrNode& node)
{
    BoundVariableAsVoidPtrNode* clone = new BoundVariableAsVoidPtrNode(node.GetSourcePos(), node.GetType());
    BoundExpressionNode* addrOfBoundVariable = node.AddrOfBoundVariable();
    addrOfBoundVariable->Accept(*this);
    BoundNode* n = s.Pop();
    if (n->IsBoundExpressionNode())
    {
        BoundExpressionNode* en = static_cast<BoundExpressionNode*>(n);
        clone->SetAddrOfBoundVariable(en);
    }
    else
    {
        ThrowException("expression node expected", n->GetSourcePos(), context);
    }
    clone->SetFlags(node.Flags());
    if (node.TemporaryDestructorCallsObtained() && destructTemporariesNode)
    {
        clone->SetDestructTemporariesNode(destructTemporariesNode.release());
    }
    else if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void InvokeAndCleanupGenerator::Visit(BoundOperatorFnNode& node)
{
    BoundExpressionNode* clone = node.Clone();
    if (node.DestructTemporariesNode())
    {
        clone->SetDestructTemporariesNode(static_cast<BoundDestructTemporariesNode*>(node.DestructTemporariesNode()->Clone()));
    }
    s.Push(clone);
}

void MakeInvokesAndCleanups(BoundFunctionNode* boundFunction, Context* context)
{
    InvokeAndCleanupGenerator generator(context, boundFunction->GetFunctionDefinitionSymbol());
    boundFunction->Accept(generator);
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

std::unique_ptr<BoundStatementNode> ConvertReturnStatement(otava::ast::ReturnStatementNode* returnStatement,
    FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context)
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
        std::unique_ptr<BoundStatementNode> boundExpressionStatement = BindStatement(exprStatementNode, functionDefinitionSymbol, context);
        std::unique_ptr<BoundStatementNode> boundSetChildControlResultStatement = BindStatement(setChildControlResultStmt.get(), functionDefinitionSymbol, context);
        std::unique_ptr<BoundReturnStatementNode> boundReturnStatement(new BoundReturnStatementNode(returnStatement->GetSourcePos()));
        std::unique_ptr<BoundSequenceStatementNode> boundSequenceStatement(new BoundSequenceStatementNode(returnStatement->GetSourcePos(), new BoundSequenceStatementNode(
            returnStatement->GetSourcePos(), boundExpressionStatement.release(), boundSetChildControlResultStatement.release()), boundReturnStatement.release()));
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
        return std::unique_ptr<BoundStatementNode>(boundSequenceStatement.release());
    }
    else
    {
        std::unique_ptr<BoundReturnStatementNode> boundReturnStatement(new BoundReturnStatementNode(returnStatement->GetSourcePos()));
        context->GetModule()->GetNodeIdFactory()->SetInternallyMapped(prevInternallyMapped);
        return std::unique_ptr<BoundStatementNode>(boundReturnStatement.release());
    }
}

} // namespace otava::symbols
