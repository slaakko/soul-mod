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
class Emitter;
class Scope;
class TypeSymbol;

enum class BoundNodeKind
{
    boundCompileUnitNode, boundFunctionNode, boundCompoundStatementNode, boundIfStatementNode, boundSwitchStatementNode, boundCaseStatementNode, boundDefaultStatementNode,
    boundWhileStatementNode, boundDoStatementNode, boundForStatementNode, boundBreakStatementNode, boundContinueStatementNode, boundReturnStatementNode, boundGotoStatementNode,
    boundConstructionStatementNode, boundExpressionStatementNode, boundSequenceStatementNode,
    boundLiteralNode, boundStringLiteralNode, boundVariableNode, boundParameterNode, boundEnumConstantNode, 
    boundFunctionGroupNode, boundTypeNode, boundMemberExprNode, boundFunctionCallNode,
    boundConjunctionNode, boundDisjunctionNode,
    boundConversionNode, boundAddressOfNode, boundDereferenceNode, boundRefToPtrNode, boundDefaultInitNode,
    boundTemporaryNode, boundConstructTemporaryNode, boundGlobalVariableDefinitionNode, boundCtorInitializerNode,
};

std::string BoundNodeKindStr(BoundNodeKind nodeKind);

class BoundNode
{
public:
    BoundNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_);
    virtual ~BoundNode();
    virtual void Accept(BoundTreeVisitor& visitor) = 0;
    BoundNodeKind Kind() const { return kind; }
    virtual Scope* GetMemberScope(otava::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const { return nullptr; }
    const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
    bool IsBoundAddressOfNode() const { return kind == BoundNodeKind::boundAddressOfNode; }
    bool IsBoundDereferenceNode() const { return kind == BoundNodeKind::boundDereferenceNode; }
    bool IsReturnStatementNode() const { return kind == BoundNodeKind::boundReturnStatementNode; }
    bool IsBoundMemberExprNode() const { return kind == BoundNodeKind::boundMemberExprNode; }
    bool IsBoundTypeNode() const { return kind == BoundNodeKind::boundTypeNode; }
private:
    BoundNodeKind kind;
    soul::ast::SourcePos sourcePos;
};

enum class BoundExpressionFlags
{
    none = 0, bindToRvalueRef = 1 << 0
};

constexpr BoundExpressionFlags operator|(BoundExpressionFlags left, BoundExpressionFlags right)
{
    return BoundExpressionFlags(int(left) | int(right));
}

constexpr BoundExpressionFlags operator&(BoundExpressionFlags left, BoundExpressionFlags right)
{
    return BoundExpressionFlags(int(left) & int(right));
}

constexpr BoundExpressionFlags operator~(BoundExpressionFlags flag)
{
    return BoundExpressionFlags(~int(flag));
}

class BoundExpressionNode : public BoundNode
{
public:
    BoundExpressionNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    TypeSymbol* GetType() const { return type; }
    Scope* GetMemberScope(otava::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const override;
    bool BindToRvalueRef() const { return GetFlag(BoundExpressionFlags::bindToRvalueRef); }
    virtual bool HasValue() const { return false; }
    virtual void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual BoundExpressionNode* Clone() const = 0;
    bool GetFlag(BoundExpressionFlags flag) const;
    void SetFlag(BoundExpressionFlags flag);
    virtual bool IsBoundLocalVariable() const { return false; }
    virtual bool IsBoundMemberVariable() const { return false; }
    virtual bool IsLvalueExpression() const { return false; }
private:
    BoundExpressionFlags flags;
    TypeSymbol* type;
};

} // namespace otava::symbols
