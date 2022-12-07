// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.bound.tree.visitor;

import std.core;

export namespace otava::symbols {

class BoundCompileUnitNode;
class BoundFunctionNode;
class BoundCtorInitializerNode;
class BoundCompoundStatementNode;
class BoundIfStatementNode;
class BoundSwitchStatementNode;
class BoundCaseStatementNode;
class BoundDefaultStatementNode;
class BoundWhileStatementNode;
class BoundDoStatementNode;
class BoundForStatementNode;
class BoundSequenceStatementNode;
class BoundBreakStatementNode;
class BoundContinueStatementNode;
class BoundReturnStatementNode;
class BoundGotoStatementNode;
class BoundConstructionStatementNode;
class BoundExpressionStatementNode;
class BoundLiteralNode;
class BoundStringLiteralNode;
class BoundVariableNode;
class BoundParameterNode;
class BoundEnumConstant;
class BoundFunctionGroupNode;
class BoundTypeNode;
class BoundMemberExprNode;
class BoundFunctionCallNode;
class BoundExpressionSequenceNode;
class BoundExpressionListNode;
class BoundConjunctionNode;
class BoundDisjunctionNode;
class BoundConversionNode;
class BoundAddressOfNode;
class BoundDereferenceNode;
class BoundRefToPtrNode;
class BoundDefaultInitNode;
class BoundTemporaryNode;
class BoundGlobalVariableDefinitionNode;

class BoundTreeVisitor
{
public:
    virtual ~BoundTreeVisitor();
    virtual void Visit(BoundCompileUnitNode& node) {}
    virtual void Visit(BoundFunctionNode& node) {}
    virtual void Visit(BoundCtorInitializerNode& node) {}
    virtual void Visit(BoundCompoundStatementNode& node) {}
    virtual void Visit(BoundIfStatementNode& node) {}
    virtual void Visit(BoundSwitchStatementNode& node) {}
    virtual void Visit(BoundCaseStatementNode& node) {}
    virtual void Visit(BoundDefaultStatementNode& node) {}
    virtual void Visit(BoundWhileStatementNode& node) {}
    virtual void Visit(BoundDoStatementNode& node) {}
    virtual void Visit(BoundForStatementNode& node) {}
    virtual void Visit(BoundSequenceStatementNode& node) {}
    virtual void Visit(BoundBreakStatementNode& node) {}
    virtual void Visit(BoundContinueStatementNode& node) {}
    virtual void Visit(BoundReturnStatementNode& node) {}
    virtual void Visit(BoundGotoStatementNode& node) {}
    virtual void Visit(BoundConstructionStatementNode& node) {}
    virtual void Visit(BoundExpressionStatementNode& node) {}
    virtual void Visit(BoundLiteralNode& node) {}
    virtual void Visit(BoundStringLiteralNode& node) {}
    virtual void Visit(BoundVariableNode& node) {}
    virtual void Visit(BoundParameterNode& node) {}
    virtual void Visit(BoundEnumConstant& node) {}
    virtual void Visit(BoundFunctionGroupNode& node) {}
    virtual void Visit(BoundTypeNode& node) {}
    virtual void Visit(BoundMemberExprNode& node) {}
    virtual void Visit(BoundFunctionCallNode& node) {}
    virtual void Visit(BoundExpressionSequenceNode& node) {}
    virtual void Visit(BoundExpressionListNode& node) {}
    virtual void Visit(BoundConjunctionNode& node) {}
    virtual void Visit(BoundDisjunctionNode& node) {}
    virtual void Visit(BoundConversionNode& node) {}
    virtual void Visit(BoundAddressOfNode& node) {}
    virtual void Visit(BoundDereferenceNode& node) {}
    virtual void Visit(BoundRefToPtrNode& node) {}
    virtual void Visit(BoundDefaultInitNode& node) {}
    virtual void Visit(BoundTemporaryNode& node) {}
    virtual void Visit(BoundGlobalVariableDefinitionNode& node) {}
};

class DefaultBoundTreeVisitor : public BoundTreeVisitor
{
public:
    void Visit(BoundCompileUnitNode& node) override;
    void Visit(BoundFunctionNode& node) override;
    void Visit(BoundCompoundStatementNode& node) override;
    void Visit(BoundIfStatementNode& node) override;
    void Visit(BoundSwitchStatementNode& node) override;
    void Visit(BoundCaseStatementNode& node) override;
    void Visit(BoundDefaultStatementNode& node) override;
    void Visit(BoundWhileStatementNode& node) override;
    void Visit(BoundDoStatementNode& node) override;
    void Visit(BoundForStatementNode& node) override;
    void Visit(BoundSequenceStatementNode& node) override;
    void Visit(BoundReturnStatementNode& node) override;
    void Visit(BoundConstructionStatementNode& node) override;
    void Visit(BoundExpressionStatementNode& node) override;
    void Visit(BoundMemberExprNode& node) override;
};

} // namespace otava::symbols
