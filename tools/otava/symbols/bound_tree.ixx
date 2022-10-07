// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.bound.tree;

import std.core;
import otava.ast.node;
import otava.symbols.bound.node;

export namespace otava::symbols {

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
class Emitter;

class BoundTreeVisitor;

class BoundExpressionNode;
class OperationRepository;

class BoundCompileUnitNode : public BoundNode
{
public:
    BoundCompileUnitNode();
    OperationRepository* GetOperationRepository() const { return operationRepository.get(); }
    void Accept(BoundTreeVisitor& visitor) override;
    void AddBoundNode(BoundNode* node);
    const std::vector<std::unique_ptr<BoundNode>>& BoundNodes() const { return boundNodes; }
    void SetId(const std::string& id_) { id = id_; }
    const std::string& Id() const { return id; }
private:
    std::string id;
    std::vector<std::unique_ptr<BoundNode>> boundNodes;
    std::unique_ptr<OperationRepository> operationRepository;
};

class BoundCompoundStatementNode;

class BoundFunctionNode : public BoundNode
{
public:
    BoundFunctionNode(FunctionDefinitionSymbol* functionDefinitionSymbol_, const soul::ast::SourcePos& sourcePos_);
    const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
    void Accept(BoundTreeVisitor& visitor) override;
    void SetBody(BoundCompoundStatementNode* body_);
    const BoundCompoundStatementNode* Body() const { return body.get(); }
    BoundCompoundStatementNode* Body() { return body.get(); }
    FunctionDefinitionSymbol* GetFunctionDefinitionSymbol() { return functionDefinitionSymbol; }
private:
    FunctionDefinitionSymbol* functionDefinitionSymbol;
    std::unique_ptr<BoundCompoundStatementNode> body;
    soul::ast::SourcePos sourcePos;
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

class BoundLiteralNode : public BoundExpressionNode
{
public:
    BoundLiteralNode(Value* value_);
    void Accept(BoundTreeVisitor& visitor) override;
    Value* GetValue() const { return value; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
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

class BoundErrorNode : public BoundExpressionNode
{
public:
    BoundErrorNode();
    void Accept(BoundTreeVisitor& visitor) override;
};

} // namespace otava::symbols
