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
import otava.symbols.bound.tree.visitor;

namespace otava::symbols {

BoundCompileUnitNode::BoundCompileUnitNode() : BoundNode(BoundNodeKind::boundCompileUnitNode, soul::ast::SourcePos()), operationRepository(new OperationRepository()), id()
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

BoundConstructionStatementNode::BoundConstructionStatementNode(const soul::ast::SourcePos& sourcePos_, VariableSymbol* variable_, BoundExpressionNode* initializer_) :
    BoundStatementNode(BoundNodeKind::boundConstructionStatementNode, sourcePos_), variable(variable_), initializer(initializer_)
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
    BoundExpressionNode(BoundNodeKind::boundVariableNode, sourcePos_, variable_->GetType()), variable(variable_)
{
}

void BoundVariableNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

void BoundVariableNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if ((flags & OperationFlags::addr) != OperationFlags::none)
    {
        emitter.Stack().Push(static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context)));
    }
    else if ((flags & OperationFlags::deref) != OperationFlags::none)
    {
        // TODO deref
    }
    else 
    {
        emitter.Stack().Push(emitter.EmitLoad(static_cast<otava::intermediate::Value*>(variable->IrObject(emitter, sourcePos, context))));
    }
}

BoundParameterNode::BoundParameterNode(ParameterSymbol* parameter_, const soul::ast::SourcePos& sourcePos_) : 
    BoundExpressionNode(BoundNodeKind::boundParameterNode, sourcePos_, parameter_->GetType()), parameter(parameter_)
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
        // TODO deref
    }
    else
    {
        emitter.Stack().Push(emitter.EmitLoad(static_cast<otava::intermediate::Value*>(parameter->IrObject(emitter, sourcePos, context))));
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
    functionSymbol->GenerateCode(emitter, arguments, sourcePos, context);
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
    conversionFunction->GenerateCode(emitter, args, sourcePos, context);
}

BoundErrorNode::BoundErrorNode(const soul::ast::SourcePos& sourcePos_) : BoundExpressionNode(BoundNodeKind::boundErrorNode, sourcePos_, nullptr)
{
}

void BoundErrorNode::Accept(BoundTreeVisitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::symbols
