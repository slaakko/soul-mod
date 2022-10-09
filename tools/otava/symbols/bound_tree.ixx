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
    void Accept(BoundTreeVisitor& visitor) override;
    void SetBody(BoundCompoundStatementNode* body_);
    const BoundCompoundStatementNode* Body() const { return body.get(); }
    BoundCompoundStatementNode* Body() { return body.get(); }
    FunctionDefinitionSymbol* GetFunctionDefinitionSymbol() { return functionDefinitionSymbol; }
private:
    FunctionDefinitionSymbol* functionDefinitionSymbol;
    std::unique_ptr<BoundCompoundStatementNode> body;
};

class BoundStatementNode : public BoundNode
{
public:
    BoundStatementNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_);
    virtual bool EndsWithTerminator() const { return IsTerminator(); }
    virtual bool IsTerminator() const { return false; }
    bool Generated() const { return generated; }
    void SetGenerated() { generated = true; }
private:
    bool generated;
};

class BoundCompoundStatementNode : public BoundStatementNode
{
public:
    BoundCompoundStatementNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void AddStatement(BoundStatementNode* statement);
    const std::vector<std::unique_ptr<BoundStatementNode>>& Statements() const { return statements; }
    bool EndsWithTerminator() const override;
private:
    std::vector<std::unique_ptr<BoundStatementNode>> statements;
};

class BoundIfStatementNode : public BoundStatementNode
{
public:
    BoundIfStatementNode(const soul::ast::SourcePos& sourcePos_);
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
    BoundSwitchStatementNode(const soul::ast::SourcePos& sourcePos_);
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
    BoundCaseStatementNode(const soul::ast::SourcePos& sourcePos_);
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
    BoundDefaultStatementNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Statement() const { return stmt.get(); }
    void SetStatement(BoundStatementNode* stmt_);
private:
    std::unique_ptr<BoundStatementNode> stmt;
};

class BoundWhileStatementNode : public BoundStatementNode
{
public:
    BoundWhileStatementNode(const soul::ast::SourcePos& sourcePos_);
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
    BoundDoStatementNode(const soul::ast::SourcePos& sourcePos_);
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
    BoundForStatementNode(const soul::ast::SourcePos& sourcePos_);
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

class BoundSequenceStatementNode : public BoundStatementNode
{
public:
    BoundSequenceStatementNode(const soul::ast::SourcePos& sourcePos_, BoundStatementNode* first_, BoundStatementNode* second_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* First() const { return first.get(); }
    BoundStatementNode* Second() const { return second.get(); }
private:
    std::unique_ptr<BoundStatementNode> first;
    std::unique_ptr<BoundStatementNode> second;
};

class BoundReturnStatementNode : public BoundStatementNode
{
public:
    BoundReturnStatementNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void SetExpr(BoundExpressionNode* expr_);
    BoundExpressionNode* GetExpr() const { return expr.get(); }
    bool IsTerminator() const override { return true; }
private:
    std::unique_ptr<BoundExpressionNode> expr;
};

class BoundBreakStatementNode : public BoundStatementNode
{
public:
    BoundBreakStatementNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool IsTerminator() const override { return true; }
};

class BoundContinueStatementNode : public BoundStatementNode
{
public:
    BoundContinueStatementNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool IsTerminator() const override { return true; }
};

class BoundGotoStatementNode : public BoundStatementNode
{
public:
    BoundGotoStatementNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool IsTerminator() const override { return true; }
};

class BoundConstructionStatementNode : public BoundStatementNode
{
public:
    BoundConstructionStatementNode(const soul::ast::SourcePos& sourcePos_, VariableSymbol* variable_, BoundExpressionNode* initializer_);
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
    BoundExpressionStatementNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void SetExpr(BoundExpressionNode* expr_);
    BoundExpressionNode* GetExpr() const { return expr.get(); }
private:
    std::unique_ptr<BoundExpressionNode> expr;
};

class BoundLiteralNode : public BoundExpressionNode
{
public:
    BoundLiteralNode(Value* value_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    Value* GetValue() const { return value; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    Value* value;
};

class BoundVariableNode : public BoundExpressionNode
{
public:
    BoundVariableNode(VariableSymbol* variable_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    VariableSymbol* GetVariable() const { return variable; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    VariableSymbol* variable;
};

class BoundParameterNode : public BoundExpressionNode
{
public:
    BoundParameterNode(ParameterSymbol* parameter_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    ParameterSymbol* GetParameter() const { return parameter; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    ParameterSymbol* parameter;
};

class BoundEnumConstant : public BoundExpressionNode
{
public:
    BoundEnumConstant(EnumConstantSymbol* enumConstant_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    EnumConstantSymbol* EnumConstant() const { return enumConstant; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    EnumConstantSymbol* enumConstant;
};

class BoundFunctionGroupNode : public BoundExpressionNode
{
public:
    BoundFunctionGroupNode(FunctionGroupSymbol* functionGroupSymbol_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    FunctionGroupSymbol* GetFunctionGroupSymbol() const { return functionGroupSymbol; }
private:
    FunctionGroupSymbol* functionGroupSymbol;
};

class BoundTypeNode : public BoundExpressionNode
{
public:
    BoundTypeNode(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
};

class BoundMemberExprNode : public BoundExpressionNode
{
public:
    BoundMemberExprNode(BoundExpressionNode* subject_, BoundExpressionNode* member_, const soul::ast::SourcePos& sourcePos_);
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
    BoundFunctionCallNode(FunctionSymbol* functionSymbol_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override;
    FunctionSymbol* GetFunctionSymbol() const { return functionSymbol; }
    void AddArgument(BoundExpressionNode* arg);
    const std::vector<std::unique_ptr<BoundExpressionNode>>& Args() const { return args; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    FunctionSymbol* functionSymbol;
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
};

class BoundConversionNode : public BoundExpressionNode
{
public:
    BoundConversionNode(BoundExpressionNode* subject_, FunctionSymbol* conversionFunction_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
    FunctionSymbol* conversionFunction;
};

class BoundErrorNode : public BoundExpressionNode
{
public:
    BoundErrorNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
};

} // namespace otava::symbols
