// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.bound.tree;

import otava.symbols.context;
import otava.symbols.exception;
import otava.symbols.value;
import otava.symbols.variable.symbol;
import otava.symbols.function.symbol;
import otava.symbols.emitter;
import otava.symbols.enums;
import otava.symbols.classes;
import otava.symbols.symbol.table;
import otava.symbols.type.resolver;
import otava.symbols.operation.repository;
import otava.symbols.argument.conversion.table;
import otava.symbols.bound.tree.visitor;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.class_templates;
import otava.symbols.type.symbol;
import otava.symbols.namespaces;
import otava.symbols.fundamental.type.symbol;
import otava.intermediate.code;
import util.unicode;

namespace otava::symbols {

std::string BoundNodeKindStr(BoundNodeKind nodeKind)
{
    switch (nodeKind)
    {
        case BoundNodeKind::boundCompileUnitNode:
        {
            return "boundCompileUnitNode";
        }
        case BoundNodeKind::boundFunctionNode:
        {
            return "boundFunctionNode";
        }
        case BoundNodeKind::boundCompoundStatementNode:
        {
            return "boundCompoundStatementNode";
        }
        case BoundNodeKind::boundIfStatementNode:
        {
            return "boundIfStatementNode";
        }
        case BoundNodeKind::boundSwitchStatementNode:
        {
            return "boundSwitchStatementNode";
        }
        case BoundNodeKind::boundCaseStatementNode:
        {
            return "boundCaseStatementNode";
        }
        case BoundNodeKind::boundDefaultStatementNode:
        {
            return "boundDefaultStatementNode";
        }
        case BoundNodeKind::boundWhileStatementNode:
        {
            return "boundWhileStatementNode";
        }
        case BoundNodeKind::boundDoStatementNode:
        {
            return "boundDoStatementNode";
        }
        case BoundNodeKind::boundForStatementNode:
        {
            return "boundForStatementNode";
        }
        case BoundNodeKind::boundBreakStatementNode:
        {
            return "boundBreakStatementNode";
        }
        case BoundNodeKind::boundContinueStatementNode:
        {
            return "boundContinueStatementNode";
        }
        case BoundNodeKind::boundReturnStatementNode:
        {
            return "boundReturnStatementNode";
        }
        case BoundNodeKind::boundGotoStatementNode:
        {
            return "boundGotoStatementNode";
        }
        case BoundNodeKind::boundConstructionStatementNode:
        {
            return "boundConstructionStatementNode";
        }
        case BoundNodeKind::boundExpressionStatementNode:
        {
            return "boundExpressionStatementNode";
        }
        case BoundNodeKind::boundSequenceStatementNode:
        {
            return "boundSequenceStatementNode";
        }
        case BoundNodeKind::boundSetVPtrStatementNode:
        {
            return "boundSetVPtrStatementNode";
        }
        case BoundNodeKind::boundTryStatementNode:
        {
            return "boundTryStatementNode";
        }
        case BoundNodeKind::boundHandlerNode:
        {
            return "boundHandlerNode";
        }
        case BoundNodeKind::boundValueNode:
        {
            return "boundValueNode";
        }
        case BoundNodeKind::boundLiteralNode:
        {
            return "boundLiteralNode";
        }
        case BoundNodeKind::boundVariableNode:
        {
            return "boundVariableNode";
        }
        case BoundNodeKind::boundParameterNode:
        {
            return "boundParameterNode";
        }
        case BoundNodeKind::boundEnumConstantNode:
        {
            return "boundEnumConstantNode";
        }
        case BoundNodeKind::boundFunctionGroupNode:
        {
            return "boundFunctionGroupNode";
        }
        case BoundNodeKind::boundTypeNode:
        {
            return "boundTypeNode";
        }
        case BoundNodeKind::boundMemberExprNode:
        {
            return "boundMemberExprNode";
        }
        case BoundNodeKind::boundFunctionCallNode:
        {
            return "boundFunctionCallNode";
        }
        case BoundNodeKind::boundEmptyFunctionCallNode:
        {
            return "boundEmptyFunctionCallNode";
        }
        case BoundNodeKind::boundExpressionSequenceNode:
        {
            return "boundExpressionSequenceNode";
        }
        case BoundNodeKind::boundExpressionListNode:
        {
            return "boundExpressionListNode";
        }
        case BoundNodeKind::boundDisjunctionNode:
        {
            return "boundDisjunctionNode";
        }
        case BoundNodeKind::boundConjunctionNode:
        {
            return "boundConjunctionNode";
        }
        case BoundNodeKind::boundConversionNode:
        {
            return "boundConversionNode";
        }
        case BoundNodeKind::boundAddressOfNode:
        {
            return "boundAddressOfNode";
        }
        case BoundNodeKind::boundDereferenceNode:
        {
            return "boundDereferenceNode";
        }
        case BoundNodeKind::boundRefToPtrNode:
        {
            return "boundRefToPtrNode";
        }
        case BoundNodeKind::boundPtrToRefNode:
        {
            return "boundPtrToRefNode";
        }
        case BoundNodeKind::boundDefaultInitNode:
        {
            return "boundDefaultInitNode";
        }
        case BoundNodeKind::boundConstructTemporaryNode:
        {
            return "boundConstructTemporaryNode";
        }
        case BoundNodeKind::boundConstructExpressionNode:
        {
            return "boundConstructExpressionNode";
        }
        case BoundNodeKind::boundClassNode:
        {
            return "boundClassNode";
        }
        case BoundNodeKind::boundEmptyDestructorNode:
        {
            return "boundEmptyDestructorNode";
        }
        case BoundNodeKind::boundThrowExpressionNode:
        {
            return "boundThrowExpressionNode";
        }
        case BoundNodeKind::boundFunctionValueNode:
        {
            return "boundFunctionValueNode";
        }
        case BoundNodeKind::boundVariableAsVoidPtrNode:
        {
            return "boundVariableAsVoidPtrNode";
        }
    }
    return "<unknown bound node>";
}

struct BoundNodeLess
{
    bool operator()(const std::unique_ptr<BoundNode>& left, const std::unique_ptr<BoundNode>& right) const;
};

bool BoundNodeLess::operator()(const std::unique_ptr<BoundNode>& left, const std::unique_ptr<BoundNode>& right) const
{
    if (left->Kind() < right->Kind()) return true;
    if (left->Kind() > right->Kind()) return false;
    return left->Index() < right->Index();
}

BoundNode::BoundNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_) : kind(kind_), index(-1), sourcePos(sourcePos_)
{
}

BoundNode::~BoundNode()
{
}

BoundExpressionNode::BoundExpressionNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) : 
    BoundNode(kind_, sourcePos_), flags(BoundExpressionFlags::none), type(type_)
{
}

void BoundExpressionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("LOAD not implemented for " + BoundNodeKindStr(Kind()), sourcePos, context);
}

void BoundExpressionNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("STORE not implemented for " + BoundNodeKindStr(Kind()), sourcePos, context);
}

Scope* BoundExpressionNode::GetMemberScope(otava::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const
{
    if (type)
    {
        if (op->IsDotNode())
        {
            TypeSymbol* baseType = type->DirectType(context)->FinalType(sourcePos, context)->GetBaseType();
            return baseType->GetScope();
        }
        else if (op->IsArrowNode() && type->IsPointerType())
        {
            TypeSymbol* baseType = type->DirectType(context)->FinalType(sourcePos, context)->RemovePointer(context)->GetBaseType();
            return baseType->GetScope();
        }
        else if (op->IsArrowNode() && type->PlainType(context)->IsClassTypeSymbol())
        {
            TypeSymbol* baseType = type->PlainType(context)->DirectType(context)->FinalType(sourcePos, context);
            return baseType->GetScope();
        }
    }
    return nullptr;
}

bool BoundExpressionNode::GetFlag(BoundExpressionFlags flag) const
{
    return (flags & flag) != BoundExpressionFlags::none;
}

void BoundExpressionNode::SetFlag(BoundExpressionFlags flag)
{
    flags = flags | flag;
}

void BoundExpressionNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (type)
    {
        type = type->FinalType(sourcePos, context)->DirectType(context);
    }
}

BoundValueExpressionNode::BoundValueExpressionNode(otava::intermediate::Value* value_, TypeSymbol* type) :
    BoundExpressionNode(BoundNodeKind::boundValueNode, soul::ast::SourcePos(), type), value(value_)
{
}

void BoundValueExpressionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundValueExpressionNode::Clone() const
{
    return new BoundValueExpressionNode(value, GetType());
}

void BoundValueExpressionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    emitter.Stack().Push(value);
}

BoundCompileUnitNode::BoundCompileUnitNode() :
    BoundNode(BoundNodeKind::boundCompileUnitNode, soul::ast::SourcePos()),
    operationRepository(new OperationRepository()),
    argumentConversionTable(new ArgumentConversionTable()),
    functionTemplateRepository(new FunctionTemplateRepository()),
    classTemplateRepository(new ClassTemplateRepository()),
    inlineFunctionRepository(new InlineFunctionRepository()),
    id()
{
}

void BoundCompileUnitNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundCompileUnitNode::AddBoundNode(std::unique_ptr<BoundNode>&& node, Context* context)
{
    if (node->IsBoundFunctionNode())
    {
        BoundFunctionNode* boundFunction = static_cast<BoundFunctionNode*>(node.get());
        std::set<const Symbol*> visited;
        if (boundFunction->GetFunctionDefinitionSymbol()->IsTemplateParameterInstantiation(context, visited))
        {
            return;
        }
        FunctionDefinitionSymbolSet* functionDefinitionSymbolSet = context->GetFunctionDefinitionSymbolSet();
        FunctionDefinitionSymbol* functionDefinition = boundFunction->GetFunctionDefinitionSymbol();
        functionDefinition->SetFlag(FunctionSymbolFlags::fixedIrName);
        functionDefinition->IrName(context);
        if (functionDefinitionSymbolSet->FunctionDefinitionSymbolFound(functionDefinition))
        {
            return;
        }
        functionDefinitionSymbolSet->AddFunctionDefinitionSymbol(functionDefinition);
    }
    if (context->GetFlag(ContextFlags::generatingVTab))
    {
        if (node->IsBoundFunctionNode())
        {
            context->AddBoundVTabFunction(static_cast<BoundFunctionNode*>(node.release()));
        }
    }
    else
    {
        node->SetIndex(boundNodes.size());
        boundNodes.push_back(std::move(node));
    }
}

void BoundCompileUnitNode::AddBoundNodeForClass(ClassTypeSymbol* cls, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::set<const Symbol*> visited;
    if (cls->IsTemplateParameterInstantiation(context, visited)) return;
    for (const auto& prev : boundClasses)
    {
        if (prev == cls) return;
    }
    boundClasses.push_back(cls);
    AddBoundNode(std::unique_ptr<BoundNode>(new BoundClassNode(cls, sourcePos)), context);
}

void BoundCompileUnitNode::Sort()
{
    std::sort(boundNodes.begin(), boundNodes.end(), BoundNodeLess());
}

otava::intermediate::Value* BoundCompileUnitNode::CreateBoundGlobalVariable(VariableSymbol* globalVariableSymbol, Emitter& emitter, const soul::ast::SourcePos& sourcePos, 
    Context* context, bool definition)
{
    otava::symbols::TypeSymbol* type = otava::symbols::ResolveFwdDeclaredType(globalVariableSymbol->GetType(), sourcePos, context);
    globalVariableSymbol->SetDeclaredType(type);
    otava::intermediate::Value* initializer = nullptr;
    otava::intermediate::Type* irType = globalVariableSymbol->GetType()->IrType(emitter, sourcePos, context);
    otava::intermediate::Type* ptrIrType = emitter.MakePtrType(irType);
    if (definition)
    {
        if (globalVariableSymbol->GetValue())
        {
            initializer = globalVariableSymbol->GetValue()->IrValue(emitter, sourcePos, context);
        }
        else
        {
            initializer = irType->DefaultValue();
        }
    }
    otava::intermediate::Value* irVariable = emitter.EmitGlobalVariable(irType, globalVariableSymbol->IrName(context), initializer);
    emitter.SetIrObject(globalVariableSymbol, irVariable);
    return irVariable;
}

void BoundCompileUnitNode::AddDynamicInitialization(BoundExpressionNode* dynamicInitialization, BoundExpressionNode* atExitCall, 
    const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!compileUnitInitializationFunction)
    {
        FunctionDefinitionSymbol* compileUnitInitializationFunctionSymbol = new FunctionDefinitionSymbol(U"@dynamic_init_" + util::ToUtf32(id));
        context->GetSymbolTable()->GlobalNs()->AddSymbol(compileUnitInitializationFunctionSymbol, sourcePos, context);
        compileUnitInitializationFunction.reset(new BoundFunctionNode(compileUnitInitializationFunctionSymbol, sourcePos));
        compileUnitInitializationFunction->SetBody(new BoundCompoundStatementNode(sourcePos));
    }
    BoundCompoundStatementNode* body = compileUnitInitializationFunction->Body();
    BoundExpressionStatementNode* initExprStmt = new BoundExpressionStatementNode(sourcePos);
    initExprStmt->SetExpr(dynamicInitialization, sourcePos, context);
    body->AddStatement(initExprStmt);
    if (atExitCall)
    {
        BoundExpressionStatementNode* atExitStmt = new BoundExpressionStatementNode(sourcePos);
        atExitStmt->SetExpr(atExitCall, sourcePos, context);
        body->AddStatement(atExitStmt);
    }
}

void BoundCompileUnitNode::AddClassToGenerateDestructorList(ClassTypeSymbol* classType)
{
    if (std::find(generateDestructorList.begin(), generateDestructorList.end(), classType) == generateDestructorList.end())
    {
        generateDestructorList.push_back(classType);
    }
}

BoundCtorInitializerNode::BoundCtorInitializerNode(const soul::ast::SourcePos& sourcePos_) : BoundNode(BoundNodeKind::boundCtorInitializerNode, sourcePos_)
{
}

void BoundCtorInitializerNode::AddBaseInitializer(BoundFunctionCallNode* baseInitializer)
{
    baseInitializers.push_back(std::unique_ptr<BoundFunctionCallNode>(baseInitializer));
}

void BoundCtorInitializerNode::AddSetVPtrStatement(BoundStatementNode* setVPtrStatement)
{
    setVPtrStatements.push_back(std::unique_ptr<BoundStatementNode>(setVPtrStatement));
}

void BoundCtorInitializerNode::AddMemberInitializer(BoundFunctionCallNode* memberInitializer)
{
    memberInitializers.push_back(std::unique_ptr<BoundFunctionCallNode>(memberInitializer));
}

void BoundCtorInitializerNode::GenerateCode(BoundTreeVisitor& visitor, Emitter& emitter, Context* context)
{
    for (const auto& baseInitializer : baseInitializers)
    {
        baseInitializer->Load(emitter, OperationFlags::defaultInit, GetSourcePos(), context);
    }
    for (const auto& setVPtrStatement : setVPtrStatements)
    {
        setVPtrStatement->Accept(visitor);
    }
    for (const auto& memberInitializer : memberInitializers)
    {
        memberInitializer->Load(emitter, OperationFlags::defaultInit, GetSourcePos(), context);
    }
}

void BoundCtorInitializerNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundDtorTerminatorNode::BoundDtorTerminatorNode(const soul::ast::SourcePos& sourcePos_) : BoundNode(BoundNodeKind::boundDtorTerminatorNode, sourcePos_)
{
}

void BoundDtorTerminatorNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundDtorTerminatorNode::AddSetVPtrStatement(BoundStatementNode* setVPtrStatement)
{
    setVPtrStatements.push_back(std::unique_ptr<BoundStatementNode>(setVPtrStatement));
}

void BoundDtorTerminatorNode::AddMemberTerminator(BoundFunctionCallNode* memberTerminator)
{
    memberTerminators.push_back(std::unique_ptr<BoundFunctionCallNode>(memberTerminator));
}

void BoundDtorTerminatorNode::GenerateCode(BoundTreeVisitor& visitor, Emitter& emitter, Context* context)
{
    for (const auto& memberTerminator : memberTerminators)
    {
        memberTerminator->Load(emitter, OperationFlags::none, GetSourcePos(), context);
    }
}

BoundClassNode::BoundClassNode(ClassTypeSymbol* cls_, const soul::ast::SourcePos& sourcePos_) : BoundNode(BoundNodeKind::boundClassNode, sourcePos_), cls(cls_)
{
}

void BoundClassNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundFunctionNode::BoundFunctionNode(FunctionDefinitionSymbol* functionDefinitionSymbol_, const soul::ast::SourcePos& sourcePos_) :
    BoundNode(BoundNodeKind::boundFunctionNode, sourcePos_),
    functionDefinitionSymbol(functionDefinitionSymbol_), 
    body()
{
}

void BoundFunctionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundFunctionNode::SetBody(BoundCompoundStatementNode* body_)
{
    body.reset(body_);
}

void BoundFunctionNode::SetCtorInitializer(BoundCtorInitializerNode* ctorInitializer_)
{
    ctorInitializer.reset(ctorInitializer_);
}

void BoundFunctionNode::SetDtorTerminator(BoundDtorTerminatorNode* dtorTerminator_)
{
    dtorTerminator.reset(dtorTerminator_);
}

BoundStatementNode::BoundStatementNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_) : 
    BoundNode(kind_, sourcePos_), parent(nullptr), generated(false), postfix(false)
{
}

bool BoundStatementNode::IsConditionalStatementInBlock(BoundCompoundStatementNode* block) const
{
    if (this == block)
    {
        return false;
    }
    if (IsIfStatementNode() || IsSwitchStatementNode()) return true;
    BoundStatementNode* parent = Parent();
    if (parent)
    {
        return parent->IsConditionalStatementInBlock(block);
    }
    return false;
}

BoundCompoundStatementNode* BoundStatementNode::Block()
{
    if (IsBoundCompoundStatementNode()) return static_cast<BoundCompoundStatementNode*>(this);
    BoundStatementNode* parentStatement = Parent();
    if (parentStatement != nullptr)
    {
        return parentStatement->Block();
    }
    else
    {
        return nullptr;
    }
}

BoundCompoundStatementNode::BoundCompoundStatementNode(const soul::ast::SourcePos& sourcePos_) : 
    BoundStatementNode(BoundNodeKind::boundCompoundStatementNode, sourcePos_)
{
}

void BoundCompoundStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

int BoundCompoundStatementNode::IndexOf(BoundStatementNode* stmt)
{
    int n = statements.size();
    for (int i = 0; i < n; ++i)
    {
        BoundStatementNode* statement = statements[i].get();
        if (statement == stmt) return i;
    }
    return -1;
}

void BoundCompoundStatementNode::AddStatement(BoundStatementNode* statement)
{
    statement->SetParent(this);
    statements.push_back(std::unique_ptr<BoundStatementNode>(statement));
}

bool BoundCompoundStatementNode::EndsWithTerminator() const
{
    if (!statements.empty())
    {
        if (statements.back()->IsTerminator()) return true;
        if (statements.back()->IsBoundCompoundStatementNode() && statements.back()->EndsWithTerminator()) return true;
    }
    return false;
}

BoundIfStatementNode::BoundIfStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundIfStatementNode, sourcePos_)
{
}

void BoundIfStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundIfStatementNode::SetInitStatement(BoundStatementNode* initStatement_)
{
    initStatement.reset(initStatement_);
}

void BoundIfStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundIfStatementNode::SetThenStatement(BoundStatementNode* thenStatement_)
{
    thenStatement.reset(thenStatement_);
}

void BoundIfStatementNode::SetElseStatement(BoundStatementNode* elseStatement_)
{
    elseStatement.reset(elseStatement_);
}

BoundSwitchStatementNode::BoundSwitchStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundSwitchStatementNode, sourcePos_)
{
}

void BoundSwitchStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundSwitchStatementNode::SetInitStatement(BoundStatementNode* initStatement_)
{
    initStatement.reset(initStatement_);
}

void BoundSwitchStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundSwitchStatementNode::SetStatement(BoundStatementNode* statement_)
{
    statement.reset(statement_);
}

BoundCaseStatementNode::BoundCaseStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundCaseStatementNode, sourcePos_)
{
}

void BoundCaseStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundCaseStatementNode::AddCaseExpr(BoundExpressionNode* caseExpr)
{
    caseExprs.push_back(std::unique_ptr<BoundExpressionNode>(caseExpr));
}

void BoundCaseStatementNode::InsertCaseExprToFront(BoundExpressionNode* caseExpr)
{
    caseExprs.insert(caseExprs.begin(), std::unique_ptr<BoundExpressionNode>(caseExpr));
}

void BoundCaseStatementNode::SetStatement(BoundStatementNode* stmt_)
{
    stmt.reset(stmt_);
}

BoundDefaultStatementNode::BoundDefaultStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundDefaultStatementNode, sourcePos_)
{
}

void BoundDefaultStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundDefaultStatementNode::SetStatement(BoundStatementNode* stmt_)
{
    stmt.reset(stmt_);
}

BoundWhileStatementNode::BoundWhileStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundWhileStatementNode, sourcePos_)
{
}

void BoundWhileStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundWhileStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundWhileStatementNode::SetStatement(BoundStatementNode* statement_)
{
    statement.reset(statement_);
}

BoundDoStatementNode::BoundDoStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundDoStatementNode, sourcePos_)
{
}

void BoundDoStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundDoStatementNode::SetExpr(BoundExpressionNode* expr_)
{
    expr.reset(expr_);
}

void BoundDoStatementNode::SetStatement(BoundStatementNode* statement_)
{
    statement.reset(statement_);
}

BoundForStatementNode::BoundForStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundForStatementNode, sourcePos_)
{
}

void BoundForStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundForStatementNode::SetInitStatement(BoundStatementNode* initStatement_)
{
    initStatement.reset(initStatement_);
}

void BoundForStatementNode::SetCondition(BoundExpressionNode* condition_)
{
    condition.reset(condition_);
}

void BoundForStatementNode::SetLoopExpr(BoundExpressionNode* loopExpr_)
{
    loopExpr.reset(loopExpr_);
}

void BoundForStatementNode::SetStatement(BoundStatementNode* statement_)
{
statement.reset(statement_);
}

BoundSequenceStatementNode::BoundSequenceStatementNode(const soul::ast::SourcePos& sourcePos_, BoundStatementNode* first_, BoundStatementNode* second_) :
    BoundStatementNode(BoundNodeKind::boundSequenceStatementNode, sourcePos_), first(first_), second(second_)
{
}

void BoundSequenceStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundBreakStatementNode::BoundBreakStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundBreakStatementNode, sourcePos_)
{
}

void BoundBreakStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundContinueStatementNode::BoundContinueStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundContinueStatementNode, sourcePos_)
{
}

void BoundContinueStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundReturnStatementNode::BoundReturnStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundReturnStatementNode, sourcePos_)
{
}

void BoundReturnStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundReturnStatementNode::SetExpr(BoundExpressionNode* expr_, const soul::ast::SourcePos& sourcePos, Context* context)
{
    expr.reset(expr_);
    expr->ModifyTypes(sourcePos, context);
}

BoundGotoStatementNode::BoundGotoStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundGotoStatementNode, sourcePos_)
{
}

void BoundGotoStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundConstructionStatementNode::BoundConstructionStatementNode(const soul::ast::SourcePos& sourcePos_, BoundFunctionCallNode* constructorCall_) :
    BoundStatementNode(BoundNodeKind::boundConstructionStatementNode, sourcePos_), constructorCall(constructorCall_)
{
}

void BoundConstructionStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundConstructionStatementNode::SetDestructorCall(BoundFunctionCallNode* destructorCall_)
{
    destructorCall.reset(destructorCall_);
}

BoundExpressionStatementNode::BoundExpressionStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundExpressionStatementNode, sourcePos_)
{
}

void BoundExpressionStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundExpressionStatementNode::SetExpr(BoundExpressionNode* expr_, const soul::ast::SourcePos& sourcePos, Context* context)
{
    expr.reset(expr_);
    expr->ModifyTypes(sourcePos, context);
}

bool BoundExpressionStatementNode::IsTerminator() const
{
    return expr && (expr->IsNoreturnFunctionCall() || expr->IsBoundThrowExpression());
}

BoundSetVPtrStatementNode::BoundSetVPtrStatementNode(BoundExpressionNode* thisPtr_, ClassTypeSymbol* forClass_, ClassTypeSymbol* vptrHolderClass_, 
    const soul::ast::SourcePos& sourcePos_) :
    BoundStatementNode(BoundNodeKind::boundSetVPtrStatementNode, sourcePos_), thisPtr(thisPtr_), forClass(forClass_), vptrHolderClass(vptrHolderClass_)
{
}

void BoundSetVPtrStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundLiteralNode::BoundLiteralNode(Value* value_, const soul::ast::SourcePos& sourcePos_) : 
    BoundExpressionNode(BoundNodeKind::boundLiteralNode, sourcePos_, value_->GetType()), value(value_)
{
}

void BoundLiteralNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundLiteralNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    emitter.Stack().Push(value->IrValue(emitter, sourcePos, context));
}

BoundExpressionNode* BoundLiteralNode::Clone() const
{
    BoundExpressionNode* clone = new BoundLiteralNode(value, GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

BoundStringLiteralNode::BoundStringLiteralNode(Value* value_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundStringLiteralNode, sourcePos_, value_->GetType()), value(value_), irValue(nullptr)
{
}

void BoundStringLiteralNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundStringLiteralNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!irValue)
    {
        irValue = value->IrValue(emitter, sourcePos, context);
    }
    emitter.Stack().Push(irValue);
}

BoundExpressionNode* BoundStringLiteralNode::Clone() const
{
    BoundExpressionNode* clone = new BoundStringLiteralNode(value, GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

BoundVariableNode::BoundVariableNode(VariableSymbol* variable_, const soul::ast::SourcePos& sourcePos_) : 
    BoundExpressionNode(BoundNodeKind::boundVariableNode, sourcePos_, variable_->GetReferredType()), variable(variable_)
{
}

void BoundVariableNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundVariableNode::SetThisPtr(BoundExpressionNode* thisPtr_)
{
    thisPtr.reset(thisPtr_);
}

void BoundVariableNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (variable->IsLocalVariable())
    {
        if ((flags & OperationFlags::addr) != OperationFlags::none || variable->GetType()->IsClassTypeSymbol())
        {
            emitter.Stack().Push(static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context)));
        }
        else if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            otava::intermediate::Value* value = emitter.EmitLoad(static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context)));
            std::uint8_t derefCount = GetDerefCount(flags);
            for (std::uint8_t i = 0; i < derefCount; ++i)
            {
                value = emitter.EmitLoad(value);
            }
            emitter.Stack().Push(value);
        }
        else
        {
            emitter.Stack().Push(emitter.EmitLoad(static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context))));
        }
    }
    else if (variable->IsMemberVariable())
    {
        if (variable->IsStatic())
        {
            otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context));
            if (!ptr)
            {
                ptr = context->GetBoundCompileUnit()->CreateBoundGlobalVariable(variable, emitter, sourcePos, context, true);
            }
            if ((flags & OperationFlags::addr) != OperationFlags::none)
            {
                emitter.Stack().Push(ptr);
            }
            else if ((flags & OperationFlags::deref) != OperationFlags::none)
            {
                otava::intermediate::Value* value = emitter.EmitLoad(ptr);
                std::uint8_t n = GetDerefCount(flags);
                for (std::uint8_t i = 0; i < n; ++i)
                {
                    value = emitter.EmitLoad(value);
                }
                emitter.Stack().Push(value);
            }
            else
            {
                emitter.Stack().Push(emitter.EmitLoad(ptr));
            }
        }
        else
        {
            if (!thisPtr)
            {
                ThrowException("'this ptr' of bound member variable not set", sourcePos, context);
            }
            thisPtr->Load(emitter, OperationFlags::none, sourcePos, context);
            otava::intermediate::Value* ptr = emitter.Stack().Pop();
            std::int32_t layoutIndex = variable->LayoutIndex();
            otava::intermediate::Value* elementPtr = emitter.EmitElemAddr(ptr, emitter.EmitLong(layoutIndex));
            if ((flags & OperationFlags::addr) != OperationFlags::none)
            {
                emitter.Stack().Push(elementPtr);
            }
            else if ((flags & OperationFlags::deref) != OperationFlags::none)
            {
                otava::intermediate::Value* value = emitter.EmitLoad(elementPtr);
                std::uint8_t n = GetDerefCount(flags);
                for (std::uint8_t i = 0; i < n; ++i)
                {
                    value = emitter.EmitLoad(value);
                }
                emitter.Stack().Push(value);
            }
            else
            {
                emitter.Stack().Push(emitter.EmitLoad(elementPtr));
            }
        }
    }
    else if (variable->IsGlobalVariable())
    {
        otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context));
        if (!ptr)
        {
            ptr = context->GetBoundCompileUnit()->CreateBoundGlobalVariable(variable, emitter, sourcePos, context, false);
        }
        if ((flags & OperationFlags::addr) != OperationFlags::none)
        {
            emitter.Stack().Push(ptr);
        }
        else if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            otava::intermediate::Value* value = emitter.EmitLoad(ptr);
            std::uint8_t n = GetDerefCount(flags);
            for (std::uint8_t i = 0; i < n; ++i)
            {
                value = emitter.EmitLoad(value);
            }
            emitter.Stack().Push(value);
        }
        else
        {
            emitter.Stack().Push(emitter.EmitLoad(ptr));
        }
    }
}

void BoundVariableNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        ThrowException("invalid operation flag 'addr' for variable store operation", sourcePos, context);
    }
    if (variable->IsLocalVariable())
    {
        otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context));
        otava::intermediate::Value* value = emitter.Stack().Pop();
        if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            ptr = emitter.EmitLoad(ptr);
            std::uint8_t n = GetDerefCount(flags);
            for (std::uint8_t i = 1; i < n; ++i)
            {
                ptr = emitter.EmitLoad(ptr);
            }
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
        else
        {
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
    }
    else if (variable->IsMemberVariable())
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        if (!thisPtr)
        {
            ThrowException("'this ptr' of bound member variable not set", sourcePos, context);
        }
        thisPtr->Load(emitter, OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* ptr = emitter.Stack().Pop();
        std::int32_t layoutIndex = variable->LayoutIndex();
        otava::intermediate::Value* elementPtr = emitter.EmitElemAddr(ptr, emitter.EmitLong(layoutIndex));
        if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            elementPtr = emitter.EmitLoad(elementPtr);
            std::uint8_t n = GetDerefCount(flags);
            for (std::uint8_t i = 1; i < n; ++i)
            {
                elementPtr = emitter.EmitLoad(elementPtr);
            }
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(elementPtr);
            }
            emitter.EmitStore(value, elementPtr);
        }
        else
        {
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(elementPtr);
            }
            emitter.EmitStore(value, elementPtr);
        }
    }
    else if (variable->IsGlobalVariable())
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context));
        if (!ptr)
        {
            ptr = context->GetBoundCompileUnit()->CreateBoundGlobalVariable(variable, emitter, sourcePos, context, false);
        }
        if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            ptr = emitter.EmitLoad(ptr);
            std::uint8_t n = GetDerefCount(flags);
            for (std::uint8_t i = 1; i < n; ++i)
            {
                ptr = emitter.EmitLoad(ptr);
            }
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
        else
        {
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
    }
}

BoundExpressionNode* BoundVariableNode::Clone() const
{
    BoundVariableNode* clone = new BoundVariableNode(variable, GetSourcePos());
    if (thisPtr)
    {
        clone->SetThisPtr(thisPtr->Clone());
    }
    clone->SetFlags(Flags());
    return clone;
}

bool BoundVariableNode::IsBoundLocalVariable() const 
{ 
    return variable->IsLocalVariable(); 
}

bool BoundVariableNode::IsBoundMemberVariable() const 
{
    return variable->IsMemberVariable(); 
}

void BoundVariableNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    if (thisPtr)
    {
        thisPtr->ModifyTypes(sourcePos, context);
    }
}

BoundParameterNode::BoundParameterNode(ParameterSymbol* parameter_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type) : 
    BoundExpressionNode(BoundNodeKind::boundParameterNode, sourcePos_, type), parameter(parameter_)
{
}

void BoundParameterNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundParameterNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        emitter.Stack().Push(static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, sourcePos, context)));
    }
    else if ((flags & OperationFlags::deref) != OperationFlags::none)
    {
        otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, sourcePos, context));
        otava::intermediate::Value* value = emitter.EmitLoad(ptr);
        std::uint8_t n = GetDerefCount(flags);
        for (std::uint8_t i = 0; i < n; ++i)
        {
            value = emitter.EmitLoad(value);
        }
        emitter.Stack().Push(value);
    }
    else
    {
        emitter.Stack().Push(emitter.EmitLoad(static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, sourcePos, context))));
    }
}

void BoundParameterNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, sourcePos, context));
    otava::intermediate::Value* value = emitter.Stack().Pop();
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        ThrowException("invalid operation flag 'addr' for parameter store operation", sourcePos, context);
    }
    else if ((flags & OperationFlags::deref) != OperationFlags::none)
    {
        ptr = emitter.EmitLoad(ptr);
        std::uint8_t n = GetDerefCount(flags);
        for (std::uint8_t i = 1; i < n; ++i)
        {
            ptr = emitter.EmitLoad(ptr);
        }
        if ((flags & OperationFlags::setPtr) != OperationFlags::none)
        {
            context->SetPtr(ptr);
        }
        emitter.EmitStore(value, ptr);
    }
    else
    {
        if ((flags & OperationFlags::setPtr) != OperationFlags::none)
        {
            context->SetPtr(ptr);
        }
        emitter.EmitStore(value, ptr);
    }
}

BoundExpressionNode* BoundParameterNode::Clone() const
{
    BoundExpressionNode* clone = new BoundParameterNode(parameter, GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

BoundEnumConstant::BoundEnumConstant(EnumConstantSymbol* enumConstant_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundEnumConstantNode, sourcePos_, enumConstant_->GetType()), enumConstant(enumConstant_)
{
}

void BoundEnumConstant::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundEnumConstant::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        ThrowException("cannot take address of an enumeration constant", sourcePos, context);
    }
    else if ((flags & OperationFlags::deref) != OperationFlags::none)
    {
        ThrowException("cannot dereference an enumeration constant", sourcePos, context);
    }
    else
    {
        emitter.Stack().Push(enumConstant->GetValue()->IrValue(emitter, sourcePos, context));
    }
}

BoundExpressionNode* BoundEnumConstant::Clone() const
{
    BoundExpressionNode* clone = new BoundEnumConstant(enumConstant, GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

BoundFunctionGroupNode::BoundFunctionGroupNode(FunctionGroupSymbol* functionGroupSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionGroupNode, sourcePos_, type_), functionGroupSymbol(functionGroupSymbol_)
{
}

void BoundFunctionGroupNode::Accept(BoundTreeVisitor& visitor) 
{
    visitor.Visit(*this);
}

void BoundFunctionGroupNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    emitter.Stack().Push(nullptr);
}

BoundExpressionNode* BoundFunctionGroupNode::Clone() const
{
    BoundFunctionGroupNode* clone = new BoundFunctionGroupNode(functionGroupSymbol, GetSourcePos(), GetType());
    for (auto templateArg : templateArgs)
    {
        clone->AddTemplateArg(templateArg);
    }
    clone->SetFlags(Flags());
    return clone;
}

void BoundFunctionGroupNode::AddTemplateArg(TypeSymbol* templateArg)
{
    templateArgs.push_back(templateArg);
}

BoundTypeNode::BoundTypeNode(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos_) : 
    BoundExpressionNode(BoundNodeKind::boundTypeNode, sourcePos_, type_)
{
}

void BoundTypeNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundTypeNode::Clone() const
{
    BoundExpressionNode* clone = new BoundTypeNode(GetType(), GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

BoundMemberExprNode::BoundMemberExprNode(BoundExpressionNode* subject_, BoundExpressionNode* member_, otava::ast::NodeKind op_, const soul::ast::SourcePos& sourcePos_, 
    TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundMemberExprNode, sourcePos_, type_), subject(subject_), member(member_), op(op_)
{
}

void BoundMemberExprNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundMemberExprNode::Clone() const
{
    BoundExpressionNode* clone = new BoundMemberExprNode(subject->Clone(), member->Clone(), op, GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

void BoundMemberExprNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    subject->ModifyTypes(sourcePos, context);
    member->ModifyTypes(sourcePos, context);
}

BoundFunctionCallNode::BoundFunctionCallNode(FunctionSymbol* functionSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionCallNode, sourcePos_, type_), functionSymbol(functionSymbol_)
{
}

void BoundFunctionCallNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

bool BoundFunctionCallNode::HasValue() const
{
    return functionSymbol->ReturnType() && !functionSymbol->ReturnType()->IsVoidType();
}

void BoundFunctionCallNode::AddArgument(BoundExpressionNode* arg)
{
    args.push_back(std::unique_ptr<BoundExpressionNode>(arg));
}

void BoundFunctionCallNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::vector<BoundExpressionNode*> arguments;
    for (const auto& arg : args)
    {
        arguments.push_back(arg.get());
    }
    if (GetFlag(BoundExpressionFlags::virtualCall))
    {
        flags = flags | OperationFlags::virtualCall;
    }
    functionSymbol->GenerateCode(emitter, arguments, flags, sourcePos, context);
    if ((flags & OperationFlags::deref) != OperationFlags::none)
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        std::uint8_t n = GetDerefCount(flags);
        for (std::uint8_t i = 0; i < n; ++i)
        {
            value = emitter.EmitLoad(value);
        }
        emitter.Stack().Push(value);
    }
}

void BoundFunctionCallNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        ThrowException("cannot take address of a function call", sourcePos, context);
    }
    else 
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        std::vector<BoundExpressionNode*> arguments;
        for (const auto& arg : args)
        {
            arguments.push_back(arg.get());
        }
        OperationFlags callFlags = OperationFlags::none;
        if (GetFlag(BoundExpressionFlags::virtualCall))
        {
            callFlags = callFlags | OperationFlags::virtualCall;
        }
        functionSymbol->GenerateCode(emitter, arguments, callFlags, sourcePos, context);
        otava::intermediate::Value* ptr = emitter.Stack().Pop();
        if ((flags & OperationFlags::deref) != OperationFlags::none || GetFlag(BoundExpressionFlags::deref))
        {
            std::uint8_t n = GetDerefCount(flags);
            for (std::uint8_t i = 1; i < n; ++i)
            {
                ptr = emitter.EmitLoad(ptr);
            }
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
        else
        {
            if ((flags & OperationFlags::setPtr) != OperationFlags::none)
            {
                context->SetPtr(ptr);
            }
            emitter.EmitStore(emitter.EmitLoad(value), ptr);
        }
    }
}

bool BoundFunctionCallNode::IsLvalueExpression() const
{
    if (functionSymbol->IsArrayElementAccess()) return true;
    TypeSymbol* returnType = functionSymbol->ReturnType();
    if (returnType && !returnType->IsVoidType())
    {
        return !returnType->IsConstType() && returnType->IsLValueRefType();
    }
    return false;
}

BoundExpressionNode* BoundFunctionCallNode::Clone() const
{
    BoundFunctionCallNode* clone = new BoundFunctionCallNode(functionSymbol, GetSourcePos(), GetType());
    for (auto& arg : args)
    {
        clone->AddArgument(arg->Clone());
    }
    clone->SetFlags(Flags());
    return clone;
}

bool BoundFunctionCallNode::CallsClassConstructor(ClassTypeSymbol*& cls, BoundExpressionNode*& firstArg, FunctionDefinitionSymbol*& destructor) const
{
    if (functionSymbol->GetFunctionKind() != otava::symbols::FunctionKind::constructor) return false;
    if (args.empty()) return false;
    firstArg = args[0].get();
    if (!firstArg->IsBoundAddressOfNode()) return false;
    BoundAddressOfNode* addrOf = static_cast<BoundAddressOfNode*>(firstArg);
    TypeSymbol* subjectType = addrOf->Subject()->GetType();
    if (!subjectType->IsClassTypeSymbol()) return false;
    cls = static_cast<ClassTypeSymbol*>(subjectType);
    destructor = functionSymbol->Destructor();
    return true;
}

bool BoundFunctionCallNode::IsNoreturnFunctionCall() const
{
    if ((functionSymbol->Qualifiers() & FunctionQualifiers::noreturn) != FunctionQualifiers::none)
    {
        return true;
    }
    return false;
}

void BoundFunctionCallNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    for (auto& arg : args)
    {
        arg->ModifyTypes(sourcePos, context);
    }
}

BoundEmptyFunctionCallNode::BoundEmptyFunctionCallNode(const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundEmptyFunctionCallNode, sourcePos_, nullptr)
{
}

void BoundEmptyFunctionCallNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundEmptyFunctionCallNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
}

BoundExpressionNode* BoundEmptyFunctionCallNode::Clone() const
{
    BoundExpressionNode* clone = new BoundEmptyFunctionCallNode(GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

BoundFunctionPtrCallNode::BoundFunctionPtrCallNode(const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionPtrCallNode, sourcePos_, type_)
{
}

void BoundFunctionPtrCallNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundFunctionPtrCallNode::AddArgument(BoundExpressionNode* arg)
{
    args.push_back(std::unique_ptr<BoundExpressionNode>(arg));
}

void BoundFunctionPtrCallNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Value* callee = nullptr;
    std::vector<otava::intermediate::Value*> irArgs;
    bool first = true;
    for (const auto& arg : args)
    {
        arg->Load(emitter, OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* irArg = emitter.Stack().Pop();
        if (first)
        {
            callee = irArg;
            first = false;
        }
        else
        {
            irArgs.push_back(irArg);
        }
    }
    otava::intermediate::Value* value = emitter.EmitCall(callee, irArgs);
    emitter.Stack().Push(value);
}

BoundExpressionNode* BoundFunctionPtrCallNode::Clone() const
{
    BoundFunctionPtrCallNode* clone = new BoundFunctionPtrCallNode(GetSourcePos(), GetType());
    for (auto& arg : args)
    {
        clone->AddArgument(arg->Clone());
    }
    clone->SetFlags(Flags());
    return clone;
}

void BoundFunctionPtrCallNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    for (auto& arg : args)
    {
        arg->ModifyTypes(sourcePos, context);
    }
}

BoundExpressionSequenceNode::BoundExpressionSequenceNode(const soul::ast::SourcePos& sourcePos_, BoundExpressionNode* left_, BoundExpressionNode* right_) : 
    BoundExpressionNode(BoundNodeKind::boundExpressionSequenceNode, sourcePos_, right_->GetType()), left(left_), right(right_)
{
}

void BoundExpressionSequenceNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

bool BoundExpressionSequenceNode::IsLvalueExpression() const
{
    return right->IsLvalueExpression();
}

BoundExpressionNode* BoundExpressionSequenceNode::Clone() const
{
    BoundExpressionSequenceNode* clone = new BoundExpressionSequenceNode(GetSourcePos(), left->Clone(), right->Clone());
    clone->SetFlags(Flags());
    return clone;
}

void BoundExpressionSequenceNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    left->Load(emitter, flags, sourcePos, context);
    if (left->HasValue())
    {
        emitter.Stack().Pop();
    }
    right->Load(emitter, flags, sourcePos, context);
}

void BoundExpressionSequenceNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    left->Load(emitter, flags, sourcePos, context);
    if (left->HasValue())
    {
        emitter.Stack().Pop();
    }
    right->Store(emitter, flags, sourcePos, context);
}

bool BoundExpressionSequenceNode::HasValue() const
{
    return right->HasValue();
}

void BoundExpressionSequenceNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    left->ModifyTypes(sourcePos, context);
    right->ModifyTypes(sourcePos, context);
}

BoundExpressionListNode::BoundExpressionListNode(const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundExpressionListNode, sourcePos_, nullptr)
{
}

void BoundExpressionListNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundExpressionListNode::Clone() const
{
    BoundExpressionListNode* clone = new BoundExpressionListNode(GetSourcePos());
    for (auto& expr : exprs)
    {
        clone->AddExpression(expr->Clone());
    }
    clone->SetFlags(Flags());
    return clone;
}

void BoundExpressionListNode::AddExpression(BoundExpressionNode* expr)
{
    if (exprs.empty())
    {
        SetType(expr->GetType());
    }
    else
    {
        SetType(nullptr);
    }
    exprs.push_back(std::unique_ptr<BoundExpressionNode>(expr));
}

void BoundExpressionListNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    for (auto& expr : exprs)
    {
        expr->ModifyTypes(sourcePos, context);
    }
}

BoundConjunctionNode::BoundConjunctionNode(BoundExpressionNode* left_, BoundExpressionNode* right_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* boolType) :
    BoundExpressionNode(BoundNodeKind::boundConjunctionNode, sourcePos_, boolType), left(left_), right(right_)
{
}

void BoundConjunctionNode::SetTemporary(BoundVariableNode* temporary_)
{
    temporary.reset(temporary_);
}

void BoundConjunctionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

bool BoundConjunctionNode::HasValue() const
{
    return true;
}

void BoundConjunctionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    temporary->Load(emitter, OperationFlags::addr, sourcePos, context);
    otava::intermediate::Value* temp = emitter.Stack().Pop();
    left->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* leftValue = emitter.Stack().Pop();
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* rightBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* falseBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(leftValue, rightBlock, falseBlock);
    emitter.SetCurrentBasicBlock(rightBlock);
    right->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* rightValue = emitter.Stack().Pop();
    emitter.EmitBranch(rightValue, trueBlock, falseBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    emitter.EmitStore(emitter.EmitBool(true), temp);
    emitter.EmitJump(nextBlock);
    emitter.SetCurrentBasicBlock(falseBlock);
    emitter.EmitStore(emitter.EmitBool(false), temp);
    emitter.EmitJump(nextBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
    otava::intermediate::Value* value = emitter.EmitLoad(temp);
    emitter.Stack().Push(value);
}

BoundExpressionNode* BoundConjunctionNode::Clone() const
{
    BoundConjunctionNode* clone = new BoundConjunctionNode(left->Clone(), right->Clone(), GetSourcePos(), GetType());
    if (temporary)
    {
        clone->SetTemporary(static_cast<BoundVariableNode*>(temporary->Clone()));
    }
    clone->SetFlags(Flags());
    return clone;
}

void BoundConjunctionNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    left->ModifyTypes(sourcePos, context);
    right->ModifyTypes(sourcePos, context);
    if (temporary)
    {
        temporary->ModifyTypes(sourcePos, context);
    }
}

BoundDisjunctionNode::BoundDisjunctionNode(BoundExpressionNode* left_, BoundExpressionNode* right_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* boolType) :
    BoundExpressionNode(BoundNodeKind::boundDisjunctionNode, sourcePos_, boolType), left(left_), right(right_)
{
}

void BoundDisjunctionNode::SetTemporary(BoundVariableNode* temporary_)
{
    temporary.reset(temporary_);
}

void BoundDisjunctionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

bool BoundDisjunctionNode::HasValue() const
{
    return true;
}

void BoundDisjunctionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) 
{
    temporary->Load(emitter, OperationFlags::addr, sourcePos, context);
    otava::intermediate::Value* temp = emitter.Stack().Pop();
    left->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* leftValue = emitter.Stack().Pop();
    otava::intermediate::BasicBlock* trueBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* rightBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* falseBlock = emitter.CreateBasicBlock();
    otava::intermediate::BasicBlock* nextBlock = emitter.CreateBasicBlock();
    emitter.EmitBranch(leftValue, trueBlock, rightBlock);
    emitter.SetCurrentBasicBlock(rightBlock);
    right->Load(emitter, OperationFlags::none, sourcePos, context);
    otava::intermediate::Value* rightValue = emitter.Stack().Pop();
    emitter.EmitBranch(rightValue, trueBlock, falseBlock);
    emitter.SetCurrentBasicBlock(trueBlock);
    emitter.EmitStore(emitter.EmitBool(true), temp);
    emitter.EmitJump(nextBlock);
    emitter.SetCurrentBasicBlock(falseBlock);
    emitter.EmitStore(emitter.EmitBool(false), temp);
    emitter.EmitJump(nextBlock);
    emitter.SetCurrentBasicBlock(nextBlock);
    otava::intermediate::Value* value = emitter.EmitLoad(temp);
    emitter.Stack().Push(value);
}

BoundExpressionNode* BoundDisjunctionNode::Clone() const
{
    BoundDisjunctionNode* clone = new BoundDisjunctionNode(left->Clone(), right->Clone(), GetSourcePos(), GetType());
    if (temporary)
    {
        clone->SetTemporary(static_cast<BoundVariableNode*>(temporary->Clone()));
    }
    clone->SetFlags(Flags());
    return clone;
}

void BoundDisjunctionNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    left->ModifyTypes(sourcePos, context);
    right->ModifyTypes(sourcePos, context);
    if (temporary)
    {
        temporary->ModifyTypes(sourcePos, context);
    }
}

BoundConversionNode::BoundConversionNode(BoundExpressionNode* subject_, FunctionSymbol* conversionFunction_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundConversionNode, sourcePos_, conversionFunction_->ReturnType()), subject(subject_), conversionFunction(conversionFunction_)
{
    int x = 0;
}

void BoundConversionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundConversionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    subject->Load(emitter, flags, sourcePos, context);
    std::vector<BoundExpressionNode*> args;
    conversionFunction->GenerateCode(emitter, args, flags, sourcePos, context);
    if ((flags & OperationFlags::derefAfterConv) != OperationFlags::none)
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        std::uint8_t derefCount = GetDerefCount(flags);
        for (std::uint8_t i = 0; i < derefCount; ++i)
        {
            value = emitter.EmitLoad(value);
        }
        emitter.Stack().Push(value);
    }
}

void BoundConversionNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    Load(emitter, flags, sourcePos, context);
    subject->Store(emitter, flags, sourcePos, context);
}

bool BoundConversionNode::IsLvalueExpression() const
{
    return false; // todo???
}

BoundExpressionNode* BoundConversionNode::Clone() const
{
    BoundExpressionNode* clone = new BoundConversionNode(subject->Clone(), conversionFunction, GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

void BoundConversionNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    subject->ModifyTypes(sourcePos, context);
}

BoundAddressOfNode::BoundAddressOfNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundAddressOfNode, sourcePos_, type_), subject(subject_) 
{
}

void BoundAddressOfNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundAddressOfNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!subject->IsBoundDereferenceNode())
    {
        subject->Load(emitter, OperationFlags::addr, sourcePos, context);
    }
    else
    {
        BoundDereferenceNode* derefExpr = static_cast<BoundDereferenceNode*>(subject.get());
        derefExpr->Subject()->Load(emitter, flags, sourcePos, context);
    }
}

void BoundAddressOfNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) 
{
    if (!subject->IsBoundDereferenceNode())
    {
        subject->Store(emitter, OperationFlags::addr | (flags & OperationFlags::setPtr), sourcePos, context);
    }
    else
    {
        BoundDereferenceNode* derefExpr = static_cast<BoundDereferenceNode*>(subject.get());
        derefExpr->Subject()->Store(emitter, flags, sourcePos, context);
    }
}

BoundExpressionNode* BoundAddressOfNode::Clone() const
{
    BoundExpressionNode* clone = new BoundAddressOfNode(subject->Clone(), GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

void BoundAddressOfNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    subject->ModifyTypes(sourcePos, context);
}

BoundDereferenceNode::BoundDereferenceNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) : 
    BoundExpressionNode(BoundNodeKind::boundDereferenceNode, sourcePos_, type_), subject(subject_), kind(OperationFlags::deref)
{
}

BoundDereferenceNode::BoundDereferenceNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_, OperationFlags kind_) :
    BoundExpressionNode(BoundNodeKind::boundDereferenceNode, sourcePos_, type_), subject(subject_), kind(kind_)
{
}

void BoundDereferenceNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundDereferenceNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!subject->IsBoundAddressOfNode())
    {
        if (GetDerefCount(flags) == 0 && (flags & OperationFlags::addr) != OperationFlags::none)
        {
            subject->Load(emitter, OperationFlags::none, sourcePos, context);
        }
        else
        {
            subject->Load(emitter, SetDerefCount(kind, GetDerefCount(flags) + 1), sourcePos, context);
        }
    }
    else
    {
        BoundAddressOfNode* addressOfExpr = static_cast<BoundAddressOfNode*>(subject.get());
        addressOfExpr->Subject()->Load(emitter, flags, sourcePos, context);
    }
}

void BoundDereferenceNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!subject->IsBoundAddressOfNode())
    {
        subject->Store(emitter, SetDerefCount(OperationFlags::deref | (flags & OperationFlags::setPtr), GetDerefCount(flags) + 1), sourcePos, context);
    }
    else
    {
        BoundAddressOfNode* addressOfExpr = static_cast<BoundAddressOfNode*>(subject.get());
        addressOfExpr->Subject()->Store(emitter, flags, sourcePos, context);
    }
}

BoundExpressionNode* BoundDereferenceNode::Clone() const
{
    BoundExpressionNode* clone = new BoundDereferenceNode(subject->Clone(), GetSourcePos(), GetType(), kind);
    clone->SetFlags(Flags());
    return clone;
}

void BoundDereferenceNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    subject->ModifyTypes(sourcePos, context);
}

BoundRefToPtrNode::BoundRefToPtrNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) : 
    BoundExpressionNode(BoundNodeKind::boundRefToPtrNode, sourcePos_, type_), subject(subject_) 
{
}

void BoundRefToPtrNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundRefToPtrNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    subject->Load(emitter, flags, sourcePos, context);
}

void BoundRefToPtrNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    subject->Store(emitter, flags, sourcePos, context);
}

BoundExpressionNode* BoundRefToPtrNode::Clone() const
{
    BoundExpressionNode* clone = new BoundRefToPtrNode(subject->Clone(), GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

void BoundRefToPtrNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    subject->ModifyTypes(sourcePos, context);
}

BoundPtrToRefNode::BoundPtrToRefNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundPtrToRefNode, sourcePos_, type_), subject(subject_) 
{
}

void BoundPtrToRefNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundPtrToRefNode::Clone() const
{
    BoundExpressionNode* clone = new BoundPtrToRefNode(subject->Clone(), GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

void BoundPtrToRefNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    subject->Load(emitter, flags, sourcePos, context);
}

void BoundPtrToRefNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    subject->Store(emitter, flags, sourcePos, context);
}

void BoundPtrToRefNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    subject->ModifyTypes(sourcePos, context);
}

BoundDefaultInitNode::BoundDefaultInitNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundDefaultInitNode, sourcePos_, subject_->GetType()), subject(subject_)
{
}

void BoundDefaultInitNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundDefaultInitNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    subject->Load(emitter, flags | OperationFlags::defaultInit, sourcePos, context);
}

void BoundDefaultInitNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    subject->Store(emitter, flags | OperationFlags::defaultInit, sourcePos, context);
}

BoundExpressionNode* BoundDefaultInitNode::Clone() const
{
    BoundExpressionNode* clone = new BoundDefaultInitNode(subject->Clone(), GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

void BoundDefaultInitNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    subject->ModifyTypes(sourcePos, context);
}

BoundTemporaryNode::BoundTemporaryNode(BoundExpressionNode* rvalueExpr_, BoundVariableNode* backingStore_, const soul::ast::SourcePos& sourcePos_) : 
    BoundExpressionNode(BoundNodeKind::boundTemporaryNode, sourcePos_, rvalueExpr_->GetType()), rvalueExpr(rvalueExpr_), backingStore(backingStore_)
{
}

void BoundTemporaryNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!backingStore)
    {
        ThrowException("backing store of temporary not set", sourcePos, context);
    }    
    rvalueExpr->Load(emitter, OperationFlags::none, sourcePos, context);
    backingStore->Store(emitter, OperationFlags::none, sourcePos, context);
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        backingStore->Load(emitter, OperationFlags::addr, sourcePos, context);
    }
    else if ((flags & OperationFlags::deref) != OperationFlags::none)
    {
        backingStore->Load(emitter, SetDerefCount(OperationFlags::deref, GetDerefCount(flags) + 1), sourcePos, context);
    }
    else
    {
        backingStore->Load(emitter, OperationFlags::none, sourcePos, context);
    }
}

void BoundTemporaryNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    backingStore->Store(emitter, OperationFlags::none, sourcePos, context);
}

void BoundTemporaryNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundTemporaryNode::Clone() const
{
    BoundExpressionNode* clone = new BoundTemporaryNode(rvalueExpr->Clone(), static_cast<BoundVariableNode*>(backingStore->Clone()), GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

void BoundTemporaryNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    rvalueExpr->ModifyTypes(sourcePos, context);
    backingStore->ModifyTypes(sourcePos, context);
}

BoundConstructTemporaryNode::BoundConstructTemporaryNode(BoundExpressionNode* constructorCall_, BoundExpressionNode* temporary_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundConstructTemporaryNode, sourcePos_, temporary_->GetType()), constructorCall(constructorCall_), temporary(temporary_)
{
}

void BoundConstructTemporaryNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    constructorCall->Load(emitter, OperationFlags::defaultInit, sourcePos, context);
    temporary->Load(emitter, flags, sourcePos, context);
}

void BoundConstructTemporaryNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    temporary->Store(emitter, flags, sourcePos, context);
}

void BoundConstructTemporaryNode::Accept(BoundTreeVisitor& visitor) 
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundConstructTemporaryNode::Clone() const
{
    BoundExpressionNode* clone = new BoundConstructTemporaryNode(constructorCall->Clone(), temporary->Clone(), GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

void BoundConstructTemporaryNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    constructorCall->ModifyTypes(sourcePos, context);
    temporary->ModifyTypes(sourcePos, context);
}

BoundConstructExpressionNode::BoundConstructExpressionNode(BoundExpressionNode* allocation_, BoundExpressionNode* constructObjectCall_, TypeSymbol* type_, 
    bool hasPlacement_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundConstructExpressionNode, sourcePos_, type_), allocation(allocation_), constructObjectCall(constructObjectCall_),
    hasPlacement(hasPlacement_)
{
}

void BoundConstructExpressionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    allocation->Load(emitter, flags | OperationFlags::dup, sourcePos, context);
    constructObjectCall->Load(emitter, flags | OperationFlags::storeDeref, sourcePos, context);
}

void BoundConstructExpressionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundConstructExpressionNode::Clone() const
{
    BoundExpressionNode* clone = new BoundConstructExpressionNode(allocation->Clone(), constructObjectCall->Clone(), GetType(), hasPlacement, GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

void BoundConstructExpressionNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    allocation->ModifyTypes(sourcePos, context);
    constructObjectCall->ModifyTypes(sourcePos, context);
}

BoundGlobalVariableDefinitionNode::BoundGlobalVariableDefinitionNode(VariableSymbol* globalVariable_, const soul::ast::SourcePos& sourcePos_) : 
    BoundNode(BoundNodeKind::boundGlobalVariableDefinitionNode, sourcePos_), globalVariable(globalVariable_)
{
}

void BoundGlobalVariableDefinitionNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundEmptyDestructorNode::BoundEmptyDestructorNode(const soul::ast::SourcePos& sourcePos_) : BoundExpressionNode(BoundNodeKind::boundEmptyDestructorNode, sourcePos_, nullptr)
{
}

void BoundEmptyDestructorNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundEmptyDestructorNode::Clone() const
{
    BoundExpressionNode* clone = new BoundEmptyDestructorNode(GetSourcePos());
    clone->SetFlags(Flags());
    return clone;
}

void BoundEmptyDestructorNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
}

BoundFunctionValueNode::BoundFunctionValueNode(FunctionSymbol* function_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionValueNode, sourcePos_, type_), function(function_)
{
}

void BoundFunctionValueNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundFunctionValueNode::Clone() const
{
    BoundExpressionNode* clone = new BoundFunctionValueNode(function, GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

void BoundFunctionValueNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    emitter.GetOrInsertFunction(function->IrName(context), static_cast<otava::intermediate::FunctionType*>(function->IrType(emitter, sourcePos, context)));
    otava::intermediate::Value* functionValue = emitter.EmitSymbolValue(function->IrType(emitter, sourcePos, context), function->IrName(context));
    otava::intermediate::Type* voidPtrIrType = emitter.MakePtrType(emitter.GetVoidType());
    otava::intermediate::Value* functionValueAsVoidPtr = emitter.EmitBitcast(functionValue, voidPtrIrType);
    emitter.Stack().Push(functionValueAsVoidPtr);
}

BoundVariableAsVoidPtrNode::BoundVariableAsVoidPtrNode(BoundExpressionNode* addrOfBoundVariable_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) :
    BoundExpressionNode(BoundNodeKind::boundVariableAsVoidPtrNode, sourcePos_, type_), addrOfBoundVariable(addrOfBoundVariable_)
{
}

void BoundVariableAsVoidPtrNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundExpressionNode* BoundVariableAsVoidPtrNode::Clone() const
{
    BoundExpressionNode* clone = new BoundVariableAsVoidPtrNode(addrOfBoundVariable->Clone(), GetSourcePos(), GetType());
    clone->SetFlags(Flags());
    return clone;
}

void BoundVariableAsVoidPtrNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    addrOfBoundVariable->Load(emitter, flags, sourcePos, context);
    otava::intermediate::Value* variableValue = emitter.Stack().Pop();
    otava::intermediate::Type* voidPtrIrType = emitter.MakePtrType(emitter.GetVoidType());
    otava::intermediate::Value* variableAsVoidPtr = emitter.EmitBitcast(variableValue, voidPtrIrType);
    emitter.Stack().Push(variableAsVoidPtr);
}

void BoundVariableAsVoidPtrNode::ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context)
{
    BoundExpressionNode::ModifyTypes(sourcePos, context);
    addrOfBoundVariable->ModifyTypes(sourcePos, context);
}

bool InDirectSwitchStatement(BoundStatementNode* statement)
{
    BoundStatementNode* parent = statement->Parent();
    while (parent)
    {
        if (parent->IsSwitchStatementNode()) return true;
        if (parent->IsWhileStatementNode() || parent->IsDoStatementNode() || parent->IsForStatementNode()) return false;
        parent = parent->Parent();
    }
    return false;
}

} // namespace otava::symbols
