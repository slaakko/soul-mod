// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.bound.tree;

import std.core;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

class FunctionSymbol;
class FunctionGroupSymbol;
class VariableSymbol;
class ParameterSymbol;
class EnumConstantSymbol;
class TypeSymbol;
class ClassTypeSymbol;
class Value;
class Scope;
class FunctionDefinitionSymbol;
class Context;

enum class BoundNodeKind
{
    boundCompileUnitNode, boundFunctionNode, boundCompoundStatementNode, boundIfStatementNode, boundSwitchStatementNode, boundCaseStatementNode, boundDefaultStatementNode,
    boundWhileStatementNode, boundDoStatementNode, boundForStatementNode, boundBreakStatementNode, boundContinueStatementNode, boundReturnStatementNode, boundGotoStatementNode,
    boundConstructionStatementNode, boundExpressionStatementNode,
    boundLiteralNode, boundVariableNode, boundParameterNode, boundEnumConstantNode, boundFunctionGroupNode, boundTypeNode, boundMemberExprNode, boundFunctionCallNode, 
    boundBinaryExprNode, boundUnaryExprNode,
    boundErrorNode
};

class BoundTreeVisitor;

class BoundNode
{
public:
    BoundNode(BoundNodeKind kind_);
    virtual ~BoundNode();
    virtual void Accept(BoundTreeVisitor& visitor) = 0;
    BoundNodeKind Kind() const { return kind; }
    virtual Scope* GetMemberScope(soul::cpp20::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const { return nullptr; }
private:
    BoundNodeKind kind;
};

class BoundExpressionNode;
class OperationRepository;

class BoundCompileUnitNode : public BoundNode
{
public:
    BoundCompileUnitNode();
    OperationRepository* GetOperationRepository() const { return operationRepository; }
    void SetOperationRepository(OperationRepository* operationRepository_);
    void Accept(BoundTreeVisitor& visitor) override;
    void AddBoundNode(BoundNode* node);
    const std::vector<std::unique_ptr<BoundNode>>& BoundNodes() const { return boundNodes; }
private:
    std::vector<std::unique_ptr<BoundNode>> boundNodes;
    OperationRepository* operationRepository;
};

class BoundCompoundStatementNode;

class BoundFunctionNode : public BoundNode
{
public:
    BoundFunctionNode(FunctionDefinitionSymbol* functionDefinitionSymbol_);
    void Accept(BoundTreeVisitor& visitor) override;
    void SetBody(BoundCompoundStatementNode* body_);
    const BoundCompoundStatementNode* Body() const { return body.get(); }
    BoundCompoundStatementNode* Body() { return body.get(); }
private:
    FunctionDefinitionSymbol* functionDefinitionSymbol;
    std::unique_ptr<BoundCompoundStatementNode> body;
};

class BoundStatementNode : public BoundNode
{
public:
    BoundStatementNode(BoundNodeKind kind_);
};

class BoundCompoundStatementNode : public BoundStatementNode
{
public:
    BoundCompoundStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
    void AddStatement(BoundStatementNode* statement);
    const std::vector<std::unique_ptr<BoundStatementNode>>& Statements() const { return statements; }
private:
    std::vector<std::unique_ptr<BoundStatementNode>> statements;
};

class BoundIfStatementNode : public BoundStatementNode
{
public:
    BoundIfStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
    void SetInitStatement(BoundStatementNode* initStatement_);
    BoundStatementNode* InitStatement() const { return initStatement.get(); }
    void SetCondition(BoundExpressionNode* condition_);
    BoundExpressionNode* GetCondition() const { return condition.get(); }
    BoundStatementNode* ThenStatement() const { return thenStatement.get(); }
    void SetThenStatement(BoundStatementNode* thenStatement_);
    BoundStatementNode* ElseStatement() const { return elseStatement.get(); }
    void SetElseStatement(BoundStatementNode* elseStatement_);
private:
    std::unique_ptr<BoundStatementNode> initStatement;
    std::unique_ptr<BoundExpressionNode> condition;
    std::unique_ptr<BoundStatementNode> thenStatement;
    std::unique_ptr<BoundStatementNode> elseStatement;
};

class BoundSwitchStatementNode : public BoundStatementNode
{
public:
    BoundSwitchStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
    void SetInitStatement(BoundStatementNode* initStatement_);
    BoundStatementNode* InitStatement() const { return initStatement.get(); }
    void SetCondition(BoundExpressionNode* condition_);
    BoundExpressionNode* GetCondition() const { return condition.get(); }
    void SetStatement(BoundStatementNode* statement);
    BoundStatementNode* Statement() const { return statement.get(); }
private:
    std::unique_ptr<BoundStatementNode> initStatement;
    std::unique_ptr<BoundExpressionNode> condition;
    std::unique_ptr<BoundStatementNode> statement;
};

class BoundCaseStatementNode : public BoundStatementNode
{
public:
    BoundCaseStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* CaseExpr() const { return caseExpr.get(); }
    void SetCaseExpr(BoundExpressionNode* caseExpr_);
    BoundStatementNode* Statement() const { return stmt.get(); }
    void SetStatement(BoundStatementNode* stmt_);
private:
    std::unique_ptr<BoundExpressionNode> caseExpr;
    std::unique_ptr<BoundStatementNode> stmt;
};

class BoundDefaultStatementNode : public BoundStatementNode
{
public:
    BoundDefaultStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Statement() const { return stmt.get(); }
    void SetStatement(BoundStatementNode* stmt_);
private:
    std::unique_ptr<BoundStatementNode> stmt;
};

class BoundWhileStatementNode : public BoundStatementNode
{
public:
    BoundWhileStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
    void SetCondition(BoundExpressionNode* condition_);
    BoundExpressionNode* GetCondition() const { return condition.get(); }
    void SetStatement(BoundStatementNode* statement);
    BoundStatementNode* Statement() const { return statement.get(); }
private:
    std::unique_ptr<BoundExpressionNode> condition;
    std::unique_ptr<BoundStatementNode> statement;
};

class BoundDoStatementNode : public BoundStatementNode
{
public:
    BoundDoStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
    void SetExpr(BoundExpressionNode* condition_);
    BoundExpressionNode* GetExpr() const { return expr.get(); }
    void SetStatement(BoundStatementNode* statement);
    BoundStatementNode* Statement() const { return statement.get(); }
private:
    std::unique_ptr<BoundExpressionNode> expr;
    std::unique_ptr<BoundStatementNode> statement;
};

class BoundForStatementNode : public BoundStatementNode
{
public:
    BoundForStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
    void SetInitStatement(BoundStatementNode* initStatement_);
    BoundStatementNode* InitStatement() const { return initStatement.get(); }
    void SetCondition(BoundExpressionNode* condition_);
    BoundExpressionNode* GetCondition() const { return condition.get(); }
    void SetLoopExpr(BoundExpressionNode* loopExpr_);
    BoundExpressionNode* GetLoopExpr() const { return loopExpr.get(); }
    void SetStatement(BoundStatementNode* statement);
    BoundStatementNode* Statement() const { return statement.get(); }
private:
    std::unique_ptr<BoundStatementNode> initStatement;
    std::unique_ptr<BoundExpressionNode> condition;
    std::unique_ptr<BoundExpressionNode> loopExpr;
    std::unique_ptr<BoundStatementNode> statement;
};

class BoundBreakStatementNode : public BoundStatementNode
{
public:
    BoundBreakStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
};

class BoundContinueStatementNode : public BoundStatementNode
{
public:
    BoundContinueStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
};

class BoundReturnStatementNode : public BoundStatementNode
{
public:
    BoundReturnStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
    void SetExpr(BoundExpressionNode* expr_);
    BoundExpressionNode* GetExpr() const { return expr.get(); }
private:
    std::unique_ptr<BoundExpressionNode> expr;
};

class BoundGotoStatementNode : public BoundStatementNode
{
public:
    BoundGotoStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
};

class BoundConstructionStatementNode : public BoundStatementNode
{
public:
    BoundConstructionStatementNode(VariableSymbol* variable_, BoundExpressionNode* initializer_);
    void Accept(BoundTreeVisitor& visitor) override;
    VariableSymbol* Variable() const { return variable; }
    BoundExpressionNode* Initializer() const { return initializer.get(); }
private:
    VariableSymbol* variable;
    std::unique_ptr<BoundExpressionNode> initializer;
};
    
class BoundExpressionStatementNode : public BoundStatementNode
{
public:
    BoundExpressionStatementNode();
    void Accept(BoundTreeVisitor& visitor) override;
    void SetExpr(BoundExpressionNode* expr_);
    BoundExpressionNode* GetExpr() const { return expr.get(); }
private:
    std::unique_ptr<BoundExpressionNode> expr;
};

class BoundExpressionNode : public BoundNode
{
public:
    BoundExpressionNode(BoundNodeKind kind_, TypeSymbol* type_);
    TypeSymbol* GetType() const { return type; }
    Scope* GetMemberScope(soul::cpp20::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const override;
private:
    TypeSymbol* type;
};

class BoundLiteralNode : public BoundExpressionNode
{
public:
    BoundLiteralNode(Value* value_);
    void Accept(BoundTreeVisitor& visitor) override;
    Value* GetValue() const { return value; }
private:
    Value* value;
};

class BoundVariableNode : public BoundExpressionNode
{
public:
    BoundVariableNode(VariableSymbol* variable_);
    void Accept(BoundTreeVisitor& visitor) override;
    VariableSymbol* GetVariable() const { return variable; }
private:
    VariableSymbol* variable;
};

class BoundParameterNode : public BoundExpressionNode
{
public:
    BoundParameterNode(ParameterSymbol* parameter_);
    void Accept(BoundTreeVisitor& visitor) override;
    ParameterSymbol* GetParameter() const { return parameter; }
private:
    ParameterSymbol* parameter;
};

class BoundEnumConstant : public BoundExpressionNode
{
public:
    BoundEnumConstant(EnumConstantSymbol* enumConstant_);
    void Accept(BoundTreeVisitor& visitor) override;
    EnumConstantSymbol* EnumConstant() const { return enumConstant; }
private:
    EnumConstantSymbol* enumConstant;
};

class BoundFunctionGroupNode : public BoundExpressionNode
{
public:
    BoundFunctionGroupNode(FunctionGroupSymbol* functionGroupSymbol_);
    void Accept(BoundTreeVisitor& visitor) override;
    FunctionGroupSymbol* GetFunctionGroupSymbol() const { return functionGroupSymbol; }
private:
    FunctionGroupSymbol* functionGroupSymbol;
};

class BoundTypeNode : public BoundExpressionNode
{
public:
    BoundTypeNode(TypeSymbol* type_);
    void Accept(BoundTreeVisitor& visitor) override;
};

class BoundMemberExprNode : public BoundExpressionNode
{
public:
    BoundMemberExprNode(BoundExpressionNode* subject_, BoundExpressionNode* member_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Subject() const { return subject.get(); }
    BoundExpressionNode* Member() const { return member.get(); }
private:
    std::unique_ptr<BoundExpressionNode> subject;
    std::unique_ptr<BoundExpressionNode> member;
};

class BoundFunctionCallNode : public BoundExpressionNode
{
public:
    BoundFunctionCallNode(FunctionSymbol* functionSymbol_);
    void Accept(BoundTreeVisitor& visitor) override;
    FunctionSymbol* GetFunctionSymbol() const { return functionSymbol; }
    void AddArgument(BoundExpressionNode* arg);
    const std::vector<std::unique_ptr<BoundExpressionNode>>& Args() const { return args; }
private:
    FunctionSymbol* functionSymbol;
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
};

class BoundBinaryExprNode : public BoundExpressionNode
{
public:
    BoundBinaryExprNode(BoundExpressionNode* left_, BoundExpressionNode* right_, soul::cpp20::ast::NodeKind kind_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Left() const { return left.get(); }
    BoundExpressionNode* Right() const { return right.get(); }
    soul::cpp20::ast::NodeKind Kind() const { return kind; }
private:
    std::unique_ptr<BoundExpressionNode> left;
    std::unique_ptr<BoundExpressionNode> right;
    soul::cpp20::ast::NodeKind kind;
};

class BoundUnaryExprNode : public BoundExpressionNode
{
public:
    BoundUnaryExprNode(BoundExpressionNode* child_, soul::cpp20::ast::NodeKind kind_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Child() const { return child.get(); }
    soul::cpp20::ast::NodeKind Kind() const { return kind; }
private:
    std::unique_ptr<BoundExpressionNode> child;
    soul::cpp20::ast::NodeKind kind;
};

class BoundErrorNode : public BoundExpressionNode
{
public:
    BoundErrorNode();
    void Accept(BoundTreeVisitor& visitor) override;
};

class BoundTreeVisitor
{
public:
    virtual ~BoundTreeVisitor();
    virtual void Visit(BoundCompileUnitNode& node) {}
    virtual void Visit(BoundFunctionNode& node) {}
    virtual void Visit(BoundCompoundStatementNode& node) {}
    virtual void Visit(BoundIfStatementNode& node) {}
    virtual void Visit(BoundSwitchStatementNode& node) {}
    virtual void Visit(BoundCaseStatementNode& node) {}
    virtual void Visit(BoundDefaultStatementNode& node) {}
    virtual void Visit(BoundWhileStatementNode& node) {}
    virtual void Visit(BoundDoStatementNode& node) {}
    virtual void Visit(BoundForStatementNode& node) {}
    virtual void Visit(BoundBreakStatementNode& node) {}
    virtual void Visit(BoundContinueStatementNode& node) {}
    virtual void Visit(BoundReturnStatementNode& node) {}
    virtual void Visit(BoundGotoStatementNode& node) {}
    virtual void Visit(BoundConstructionStatementNode& node) {}
    virtual void Visit(BoundExpressionStatementNode& node) {}
    virtual void Visit(BoundLiteralNode& node) {}
    virtual void Visit(BoundVariableNode& node) {}
    virtual void Visit(BoundParameterNode& node) {}
    virtual void Visit(BoundEnumConstant& node) {}
    virtual void Visit(BoundFunctionGroupNode& node) {}
    virtual void Visit(BoundTypeNode& node) {}
    virtual void Visit(BoundMemberExprNode& node) {}
    virtual void Visit(BoundFunctionCallNode& node) {}
    virtual void Visit(BoundBinaryExprNode& node) {}
    virtual void Visit(BoundUnaryExprNode& node) {}
    virtual void Visit(BoundErrorNode& node) {}
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
    void Visit(BoundReturnStatementNode& node) override;
    void Visit(BoundConstructionStatementNode& node) override;
    void Visit(BoundExpressionStatementNode& node) override;
    void Visit(BoundMemberExprNode& node) override;
};

} // namespace soul::cpp20::symbols
