// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.bound.tree;

import std.core;
import soul.ast.source.pos;
import otava.ast.node;
import otava.symbols.emitter;

export namespace otava::symbols {

enum class OperationFlags : int32_t
{
    none = 0, addr = 1 << 0, deref = 1 << 1, defaultInit = 1 << 2, virtualCall = 1 << 3, setPtr = 1 << 4, dup = 1 << 5, storeDeref = 1 << 6, derefCount = 0xFF << 8
};

constexpr OperationFlags operator|(OperationFlags left, OperationFlags right)
{
    return OperationFlags(int32_t(left) | int32_t(right));
}

constexpr OperationFlags operator&(OperationFlags left, OperationFlags right)
{
    return OperationFlags(int32_t(left) & int32_t(right));
}

constexpr OperationFlags operator~(OperationFlags flags)
{
    return OperationFlags(~int32_t(flags));
}

constexpr uint8_t GetDerefCount(OperationFlags flags)
{
    return uint8_t(uint16_t(flags & OperationFlags::derefCount) >> 8);
}

constexpr OperationFlags SetDerefCount(OperationFlags flags, uint8_t n)
{
    return OperationFlags(flags | OperationFlags(uint16_t(n) << 8));
}

class FunctionSymbol;
class FunctionGroupSymbol;
class VariableSymbol;
class ParameterSymbol;
class EnumConstantSymbol;
class TypeSymbol;
class ClassTypeSymbol;
class Context;
class Value;
class Scope;
class FunctionDefinitionSymbol;

class BoundTreeVisitor;

class BoundFunctionCallNode;
class OperationRepository;
class ArgumentConversionTable;
class FunctionTemplateRepository;
class ClassTemplateRepository;

enum class BoundNodeKind
{
    boundCompileUnitNode, boundFunctionNode, boundCompoundStatementNode, boundIfStatementNode, boundSwitchStatementNode, boundCaseStatementNode, boundDefaultStatementNode,
    boundWhileStatementNode, boundDoStatementNode, boundForStatementNode, boundBreakStatementNode, boundContinueStatementNode, boundReturnStatementNode, boundGotoStatementNode,
    boundConstructionStatementNode, boundExpressionStatementNode, boundSequenceStatementNode,
    boundLiteralNode, boundStringLiteralNode, boundVariableNode, boundParameterNode, boundEnumConstantNode,
    boundFunctionGroupNode, boundTypeNode, boundMemberExprNode, boundFunctionCallNode, boundExpressionListNode,
    boundConjunctionNode, boundDisjunctionNode, boundExpressionSequenceNode, boundConstructExpressionNode,
    boundConversionNode, boundAddressOfNode, boundDereferenceNode, boundRefToPtrNode, boundPtrToRefNode, boundDefaultInitNode,
    boundTemporaryNode, boundConstructTemporaryNode, boundGlobalVariableDefinitionNode, boundCtorInitializerNode, boundDtorTerminatorNode
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
    virtual bool IsReturnStatementNode() const { return kind == BoundNodeKind::boundReturnStatementNode; }
    bool IsBoundMemberExprNode() const { return kind == BoundNodeKind::boundMemberExprNode; }
    bool IsBoundTypeNode() const { return kind == BoundNodeKind::boundTypeNode; }
    bool IsBoundExpressionListNode() const { return kind == BoundNodeKind::boundExpressionListNode; }
    bool IsBoundParameterNode() const { return kind == BoundNodeKind::boundParameterNode; }
private:
    BoundNodeKind kind;
    soul::ast::SourcePos sourcePos;
};

enum class BoundExpressionFlags
{
    none = 0, bindToRvalueRef = 1 << 0, virtualCall = 1 << 1, deref = 1 << 2
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
    void SetType(TypeSymbol* type_) { type = type_; }
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

class BoundCompileUnitNode : public BoundNode
{
public:
    BoundCompileUnitNode();
    OperationRepository* GetOperationRepository() const { return operationRepository.get(); }
    ArgumentConversionTable* GetArgumentConversionTable() const { return argumentConversionTable.get(); }
    FunctionTemplateRepository* GetFunctionTemplateRepository() const { return functionTemplateRepository.get(); }
    ClassTemplateRepository* GetClassTemplateRepository() const { return classTemplateRepository.get(); }
    void Accept(BoundTreeVisitor& visitor) override;
    void AddBoundNode(BoundNode* node);
    const std::vector<std::unique_ptr<BoundNode>>& BoundNodes() const { return boundNodes; }
    void SetId(const std::string& id_) { id = id_; }
    const std::string& Id() const { return id; }
private:
    std::string id;
    std::vector<std::unique_ptr<BoundNode>> boundNodes;
    std::unique_ptr<OperationRepository> operationRepository;
    std::unique_ptr<ArgumentConversionTable> argumentConversionTable;
    std::unique_ptr<FunctionTemplateRepository> functionTemplateRepository;
    std::unique_ptr<ClassTemplateRepository> classTemplateRepository;
};

class BoundCtorInitializerNode : public BoundNode
{
public:
    BoundCtorInitializerNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void AddMemberInitializer(BoundFunctionCallNode* memberInitializer);
    void GenerateCode(Emitter& emitter, Context* context);
private:
    std::vector<std::unique_ptr<BoundFunctionCallNode>> memberInitializers;
};

class BoundDtorTerminatorNode : public BoundNode
{
public:
    BoundDtorTerminatorNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void AddMemberTerminator(BoundFunctionCallNode* memberTerminator);
    void GenerateCode(Emitter& emitter, Context* context);
private:
    std::vector<std::unique_ptr<BoundFunctionCallNode>> memberTerminators;
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
    void SetCtorInitializer(BoundCtorInitializerNode* ctorInitializer_);
    void SetDtorTerminator(BoundDtorTerminatorNode* dtorTerminator_);
    BoundCtorInitializerNode* CtorInitializer() const { return ctorInitializer.get(); }
    BoundDtorTerminatorNode* DtorTerminator() const { return dtorTerminator.get(); }
    FunctionDefinitionSymbol* GetFunctionDefinitionSymbol() { return functionDefinitionSymbol; }
private:
    FunctionDefinitionSymbol* functionDefinitionSymbol;
    std::unique_ptr<BoundCtorInitializerNode> ctorInitializer;
    std::unique_ptr<BoundDtorTerminatorNode> dtorTerminator;
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
    bool Postfix() const { return postfix; }
    void SetPostfix() { postfix = true; }
private:
    bool generated;
    bool postfix;
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
    bool IsReturnStatementNode() const override { return second->IsReturnStatementNode(); }
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
    BoundConstructionStatementNode(const soul::ast::SourcePos& sourcePos_, BoundFunctionCallNode* constructorCall_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundFunctionCallNode* ConstructorCall() const { return constructorCall.get(); }
private:
    std::unique_ptr<BoundFunctionCallNode> constructorCall;
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
    BoundExpressionNode* Clone() const override;
private:
    Value* value;
};

class BoundStringLiteralNode : public BoundExpressionNode
{
public:
    BoundStringLiteralNode(Value* value_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    Value* GetValue() const { return value; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
private:
    Value* value;
    otava::intermediate::Value* irValue;
};

class BoundVariableNode : public BoundExpressionNode
{
public:
    BoundVariableNode(VariableSymbol* variable_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    VariableSymbol* GetVariable() const { return variable; }
    void SetThisPtr(BoundExpressionNode* thisPtr_);
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsBoundLocalVariable() const override;
    bool IsBoundMemberVariable() const override;
    bool IsLvalueExpression() const override { return true; }
    BoundExpressionNode* Clone() const override;
private:
    VariableSymbol* variable;
    std::unique_ptr<BoundExpressionNode> thisPtr;
};

class BoundParameterNode : public BoundExpressionNode
{
public:
    BoundParameterNode(ParameterSymbol* parameter_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    ParameterSymbol* GetParameter() const { return parameter; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsLvalueExpression() const override { return true; }
    BoundExpressionNode* Clone() const override;
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
    BoundExpressionNode* Clone() const override;
private:
    EnumConstantSymbol* enumConstant;
};

class BoundFunctionGroupNode : public BoundExpressionNode
{
public:
    BoundFunctionGroupNode(FunctionGroupSymbol* functionGroupSymbol_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    FunctionGroupSymbol* GetFunctionGroupSymbol() const { return functionGroupSymbol; }
    BoundExpressionNode* Clone() const override;
private:
    FunctionGroupSymbol* functionGroupSymbol;
};

class BoundTypeNode : public BoundExpressionNode
{
public:
    BoundTypeNode(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
};

class BoundMemberExprNode : public BoundExpressionNode
{
public:
    BoundMemberExprNode(BoundExpressionNode* subject_, BoundExpressionNode* member_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Subject() const { return subject.get(); }
    BoundExpressionNode* Member() const { return member.get(); }
    BoundExpressionNode* Clone() const override;
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
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsLvalueExpression() const override;
    BoundExpressionNode* Clone() const override;
private:
    FunctionSymbol* functionSymbol;
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
};

class BoundExpressionSequenceNode : public BoundExpressionNode
{
public:
    BoundExpressionSequenceNode(const soul::ast::SourcePos& sourcePos_, BoundExpressionNode* left_, BoundExpressionNode* right_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override;
    bool IsLvalueExpression() const override;
    BoundExpressionNode* Clone() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Left() const { return left.get(); }
    BoundExpressionNode* Right() const { return right.get(); }
private:
    std::unique_ptr<BoundExpressionNode> left;
    std::unique_ptr<BoundExpressionNode> right;
};

class BoundExpressionListNode : public BoundExpressionNode
{
public:
    BoundExpressionListNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
    void AddExpression(BoundExpressionNode* expr);
    int Count() const { return exprs.size(); }
    const std::vector<std::unique_ptr<BoundExpressionNode>>& Exprs() const { return exprs; }
    BoundExpressionNode* ReleaseExpr(int i) { return exprs[i].release(); }
private:
    std::vector<std::unique_ptr<BoundExpressionNode>> exprs;
};

class BoundConjunctionNode : public BoundExpressionNode
{
public:
    BoundConjunctionNode(BoundExpressionNode* left_, BoundExpressionNode* right_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* boolType);
    BoundExpressionNode* Left() const { return left.get(); }
    BoundExpressionNode* Right() const { return right.get(); }
    void SetTemporary(BoundVariableNode* temporary_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
private:
    std::unique_ptr<BoundExpressionNode> left;
    std::unique_ptr<BoundExpressionNode> right;
    std::unique_ptr<BoundVariableNode> temporary;
};

class BoundDisjunctionNode : public BoundExpressionNode
{
public:
    BoundDisjunctionNode(BoundExpressionNode* left_, BoundExpressionNode* right_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* boolType);
    BoundExpressionNode* Left() const { return left.get(); }
    BoundExpressionNode* Right() const { return right.get(); }
    void SetTemporary(BoundVariableNode* temporary_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
private:
    std::unique_ptr<BoundExpressionNode> left;
    std::unique_ptr<BoundExpressionNode> right;
    std::unique_ptr<BoundVariableNode> temporary;
};

class BoundConversionNode : public BoundExpressionNode
{
public:
    BoundConversionNode(BoundExpressionNode* subject_, FunctionSymbol* conversionFunction_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsLvalueExpression() const override;
    BoundExpressionNode* Clone() const override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
    FunctionSymbol* conversionFunction;
};

class BoundAddressOfNode : public BoundExpressionNode
{
public:    
    BoundAddressOfNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Subject() { return subject.get(); }
    BoundExpressionNode* ReleaseSubject() { return subject.release(); }
    BoundExpressionNode* Clone() const override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
};

class BoundDereferenceNode : public BoundExpressionNode
{
public:
    BoundDereferenceNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsLvalueExpression() const override { return true; }
    BoundExpressionNode* Subject() { return subject.get(); }
    BoundExpressionNode* Clone() const override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
};

class BoundRefToPtrNode : public BoundExpressionNode
{
public:
    BoundRefToPtrNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
};

class BoundPtrToRefNode : public BoundExpressionNode
{
public:
    BoundPtrToRefNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
};

class BoundDefaultInitNode : public BoundExpressionNode
{
public:    
    BoundDefaultInitNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
};

class BoundTemporaryNode : public BoundExpressionNode
{
public:
    BoundTemporaryNode(BoundExpressionNode* rvalueExpr_, BoundVariableNode* backingStore_, const soul::ast::SourcePos& sourcePos_);
    BoundExpressionNode* RvalueExpr() { return rvalueExpr.get(); }
    BoundVariableNode* BackingStore() { return backingStore.get(); }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    bool IsLvalueExpression() const override { return true; }
    BoundExpressionNode* Clone() const override;
private:
    std::unique_ptr<BoundExpressionNode> rvalueExpr;
    std::unique_ptr<BoundVariableNode> backingStore;
};

class BoundConstructTemporaryNode : public BoundExpressionNode
{
public:
    BoundConstructTemporaryNode(BoundExpressionNode* constructorCall_, BoundExpressionNode* temporary_, const soul::ast::SourcePos& sourcePos_);
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    bool IsLvalueExpression() const override { return true; }
    BoundExpressionNode* Clone() const override;
private:
    std::unique_ptr<BoundExpressionNode> constructorCall;
    std::unique_ptr<BoundExpressionNode> temporary;
};

class BoundConstructExpressionNode : public BoundExpressionNode
{
public:
    BoundConstructExpressionNode(BoundExpressionNode* allocation_, BoundExpressionNode* constructObjectCall_, TypeSymbol* type_, bool hasPlacement_, 
        const soul::ast::SourcePos& sourcePos_);
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return !hasPlacement; }
    BoundExpressionNode* Clone() const override;
private:
    std::unique_ptr<BoundExpressionNode> allocation;
    std::unique_ptr<BoundExpressionNode> constructObjectCall;
    bool hasPlacement;
};

class BoundGlobalVariableDefinitionNode : public BoundNode
{
public:
    BoundGlobalVariableDefinitionNode(VariableSymbol* globalVariable_, const soul::ast::SourcePos& sourcePos_);
    VariableSymbol* GetGlobalVariable() const { return globalVariable; }
    void Accept(BoundTreeVisitor& visitor) override;
private:
    VariableSymbol* globalVariable;
};

} // namespace otava::symbols
