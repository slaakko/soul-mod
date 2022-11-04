// =================================
// Copyright (c) 2022 Seppo Laakko
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

namespace otava::symbols {

BoundCompileUnitNode::BoundCompileUnitNode() :
    BoundNode(BoundNodeKind::boundCompileUnitNode, soul::ast::SourcePos()),
    operationRepository(new OperationRepository()),
    argumentConversionTable(new ArgumentConversionTable()),
    functionTemplateRepository(new FunctionTemplateRepository()),
    id()
{
}

void BoundCompileUnitNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundCompileUnitNode::AddBoundNode(BoundNode* node)
{
    boundNodes.push_back(std::unique_ptr<BoundNode>(node));
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

BoundStatementNode::BoundStatementNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_) : BoundNode(kind_, sourcePos_), generated(false)
{
}

BoundCompoundStatementNode::BoundCompoundStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundCompoundStatementNode, sourcePos_)
{
}

void BoundCompoundStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundCompoundStatementNode::AddStatement(BoundStatementNode* statement)
{
    statements.push_back(std::unique_ptr<BoundStatementNode>(statement));
}

bool BoundCompoundStatementNode::EndsWithTerminator() const
{
    return !statements.empty() && statements.back()->IsTerminator();
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

void BoundCaseStatementNode::SetCaseExpr(BoundExpressionNode* caseExpr_)
{
    caseExpr.reset(caseExpr_);
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

void BoundReturnStatementNode::SetExpr(BoundExpressionNode* expr_)
{
    expr.reset(expr_);
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

BoundExpressionStatementNode::BoundExpressionStatementNode(const soul::ast::SourcePos& sourcePos_) : BoundStatementNode(BoundNodeKind::boundExpressionStatementNode, sourcePos_)
{
}

void BoundExpressionStatementNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundExpressionStatementNode::SetExpr(BoundExpressionNode* expr_)
{
    expr.reset(expr_);
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
        if ((flags & OperationFlags::addr) != OperationFlags::none)
        {
            emitter.Stack().Push(static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context)));
        }
        else if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            otava::intermediate::Value* value = emitter.EmitLoad(static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context)));
            uint8_t derefCount = GetDerefCount(flags);
            for (uint8_t i = 0; i < derefCount; ++i)
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
        if (!thisPtr)
        {
            ThrowException("'this ptr' of bound member variable not set", sourcePos, context);
        }
        thisPtr->Load(emitter, OperationFlags::none, sourcePos, context);
        otava::intermediate::Value* ptr = emitter.Stack().Pop();
        int32_t layoutIndex = variable->LayoutIndex();
        otava::intermediate::Value* elementPtr = emitter.EmitElemAddr(ptr, emitter.EmitLong(layoutIndex));
        if ((flags & OperationFlags::addr) != OperationFlags::none)
        {
            emitter.Stack().Push(elementPtr);
        }
        else if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            otava::intermediate::Value* value = emitter.EmitLoad(elementPtr);
            uint8_t n = GetDerefCount(flags);
            for (uint8_t i = 0; i < n; ++i)
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
    else if (variable->IsGlobalVariable())
    {
        otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context));
        if ((flags & OperationFlags::addr) != OperationFlags::none)
        {
            emitter.Stack().Push(ptr);
        }
        else if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            otava::intermediate::Value* value = emitter.EmitLoad(ptr);
            uint8_t n = GetDerefCount(flags);
            for (uint8_t i = 0; i < n; ++i)
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
            uint8_t n = GetDerefCount(flags);
            for (uint8_t i = 1; i < n; ++i)
            {
                ptr = emitter.EmitLoad(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
        else
        {
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
        int32_t layoutIndex = variable->LayoutIndex();
        otava::intermediate::Value* elementPtr = emitter.EmitElemAddr(ptr, emitter.EmitLong(layoutIndex));
        if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            elementPtr = emitter.EmitLoad(elementPtr);
            uint8_t n = GetDerefCount(flags);
            for (uint8_t i = 1; i < n; ++i)
            {
                elementPtr = emitter.EmitLoad(elementPtr);
            }
            emitter.EmitStore(value, elementPtr);
        }
        else
        {
            emitter.EmitStore(value, elementPtr);
        }
    }
    else if (variable->IsGlobalVariable())
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        otava::intermediate::Value* ptr = static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context));
        if ((flags & OperationFlags::deref) != OperationFlags::none)
        {
            ptr = emitter.EmitLoad(ptr);
            uint8_t n = GetDerefCount(flags);
            for (uint8_t i = 1; i < n; ++i)
            {
                ptr = emitter.EmitLoad(ptr);
            }
            emitter.EmitStore(value, ptr);
        }
        else
        {
            emitter.EmitStore(value, ptr);
        }
    }
}

bool BoundVariableNode::IsBoundLocalVariable() const 
{ 
    return variable->IsLocalVariable(); 
}

bool BoundVariableNode::IsBoundMemberVariable() const 
{
    return variable->IsMemberVariable(); 
}

BoundParameterNode::BoundParameterNode(ParameterSymbol* parameter_, const soul::ast::SourcePos& sourcePos_) : 
    BoundExpressionNode(BoundNodeKind::boundParameterNode, sourcePos_, parameter_->GetReferredType()), parameter(parameter_)
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
        uint8_t n = GetDerefCount(flags);
        for (uint8_t i = 0; i < n; ++i)
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
        uint8_t n = GetDerefCount(flags);
        for (uint8_t i = 1; i < n; ++i)
        {
            ptr = emitter.EmitLoad(ptr);
        }
        emitter.EmitStore(value, ptr);
    }
    else
    {
        emitter.EmitStore(value, ptr);
    }
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

BoundFunctionGroupNode::BoundFunctionGroupNode(FunctionGroupSymbol* functionGroupSymbol_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionGroupNode, sourcePos_, nullptr), functionGroupSymbol(functionGroupSymbol_)
{
}

void BoundFunctionGroupNode::Accept(BoundTreeVisitor& visitor) 
{
    visitor.Visit(*this);
}

BoundTypeNode::BoundTypeNode(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos_) : 
    BoundExpressionNode(BoundNodeKind::boundTypeNode, sourcePos_, type_)
{
}

void BoundTypeNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundMemberExprNode::BoundMemberExprNode(BoundExpressionNode* subject_, BoundExpressionNode* member_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundMemberExprNode, sourcePos_, nullptr), subject(subject_), member(member_)
{
}

void BoundMemberExprNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundFunctionCallNode::BoundFunctionCallNode(FunctionSymbol* functionSymbol_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundFunctionCallNode, sourcePos_, functionSymbol_->ReturnType()), functionSymbol(functionSymbol_)
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
    functionSymbol->GenerateCode(emitter, arguments, flags, sourcePos, context);
    if ((flags & OperationFlags::deref) != OperationFlags::none)
    {
        otava::intermediate::Value* value = emitter.Stack().Pop();
        uint8_t n = GetDerefCount(flags);
        for (uint8_t i = 0; i < n; ++i)
        {
            value = emitter.EmitLoad(value);
        }
        emitter.Stack().Push(value);
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

BoundConversionNode::BoundConversionNode(BoundExpressionNode* subject_, FunctionSymbol* conversionFunction_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundConversionNode, sourcePos_, subject_->GetType()), subject(subject_), conversionFunction(conversionFunction_)
{
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
}

bool BoundConversionNode::IsLvalueExpression() const
{
    return false; // todo???
}

BoundAddressOfNode::BoundAddressOfNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundAddressOfNode, sourcePos_, subject_->GetType()->AddPointer()), subject(subject_)
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
        subject->Store(emitter, OperationFlags::addr, sourcePos, context);
    }
    else
    {
        BoundDereferenceNode* derefExpr = static_cast<BoundDereferenceNode*>(subject.get());
        derefExpr->Subject()->Store(emitter, flags, sourcePos, context);
    }
}

BoundDereferenceNode::BoundDereferenceNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_) :
    BoundExpressionNode(BoundNodeKind::boundDereferenceNode, sourcePos_, subject_->GetType()->RemoveRefOrPtr()), subject(subject_)
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
            subject->Load(emitter, SetDerefCount(OperationFlags::deref, GetDerefCount(flags) + 1), sourcePos, context);
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
        subject->Store(emitter, SetDerefCount(OperationFlags::deref, GetDerefCount(flags) + 1), sourcePos, context);
    }
    else
    {
        BoundAddressOfNode* addressOfExpr = static_cast<BoundAddressOfNode*>(subject.get());
        addressOfExpr->Subject()->Store(emitter, flags, sourcePos, context);
    }
}

BoundRefToPtrNode::BoundRefToPtrNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_) : 
    BoundExpressionNode(BoundNodeKind::boundRefToPtrNode, sourcePos_, subject_->GetType()->RemoveReference()->AddPointer()), subject(subject_)
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

void BoundTemporaryNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

BoundErrorNode::BoundErrorNode(const soul::ast::SourcePos& sourcePos_) : BoundExpressionNode(BoundNodeKind::boundErrorNode, sourcePos_, nullptr)
{
}

void BoundErrorNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::symbols
