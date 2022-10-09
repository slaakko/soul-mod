// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.bound.node;

import std.core;
import soul.ast.source.pos;
import otava.ast.node;
import otava.symbols.bound.tree.util;

export namespace otava::symbols {

class BoundTreeVisitor;
class Context;
class Emitter;
class Scope;
class TypeSymbol;

enum class BoundNodeKind
{
    boundCompileUnitNode, boundFunctionNode, boundCompoundStatementNode, boundIfStatementNode, boundSwitchStatementNode, boundCaseStatementNode, boundDefaultStatementNode,
    boundWhileStatementNode, boundDoStatementNode, boundForStatementNode, boundBreakStatementNode, boundContinueStatementNode, boundReturnStatementNode, boundGotoStatementNode,
    boundConstructionStatementNode, boundExpressionStatementNode, boundSequenceStatementNode,
    boundLiteralNode, boundVariableNode, boundParameterNode, boundEnumConstantNode, boundFunctionGroupNode, boundTypeNode, boundMemberExprNode, boundFunctionCallNode,
    boundConversionNode,
    boundErrorNode
};

class BoundNode
{
public:
    BoundNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_);
    virtual ~BoundNode();
    virtual void Accept(BoundTreeVisitor& visitor) = 0;
    BoundNodeKind Kind() const { return kind; }
    virtual Scope* GetMemberScope(otava::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const { return nullptr; }
    const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
private:
    BoundNodeKind kind;
    soul::ast::SourcePos sourcePos;
};

class BoundExpressionNode : public BoundNode
{
public:
    BoundExpressionNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    TypeSymbol* GetType() const { return type; }
    Scope* GetMemberScope(otava::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const override;
    virtual bool HasValue() const { return false; }
    virtual void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context);
private:
    TypeSymbol* type;
};

} // namespace otava::symbols