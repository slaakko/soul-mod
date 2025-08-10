// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.bound.tree;

import std;
import soul.ast.source.pos;
import otava.ast.node;
import otava.symbols.emitter;
import otava.intermediate;
import otava.symbols.class_templates;
import otava.symbols.inline_functions;
import util;

export namespace otava::symbols {

class NamespaceSymbol;
class NamespaceTypeSymbol;

enum class OperationFlags : std::int32_t
{
    none = 0, addr = 1 << 0, deref = 1 << 1, defaultInit = 1 << 2, virtualCall = 1 << 3, setPtr = 1 << 4, dup = 1 << 5, storeDeref = 1 << 6, derefAfterConv = 1 << 7, 
    derefCount = 0xFF << 8
};

constexpr OperationFlags operator|(OperationFlags left, OperationFlags right)
{
    return OperationFlags(std::int32_t(left) | std::int32_t(right));
}

constexpr OperationFlags operator&(OperationFlags left, OperationFlags right)
{
    return OperationFlags(std::int32_t(left) & std::int32_t(right));
}

constexpr OperationFlags operator~(OperationFlags flags)
{
    return OperationFlags(~std::int32_t(flags));
}

constexpr std::uint8_t GetDerefCount(OperationFlags flags)
{
    return std::uint8_t(std::uint16_t(flags & OperationFlags::derefCount) >> 8);
}

constexpr OperationFlags SetDerefCount(OperationFlags flags, std::uint8_t n)
{
    return OperationFlags(flags | OperationFlags(std::uint16_t(n) << 8));
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
class InlineFunctionRepository;

enum class BoundNodeKind
{
    boundCompileUnitNode, boundClassNode, boundGlobalVariableDefinitionNode, boundFunctionNode,
    boundCompoundStatementNode, boundIfStatementNode, boundSwitchStatementNode, boundCaseStatementNode, boundDefaultStatementNode,
    boundWhileStatementNode, boundDoStatementNode, boundForStatementNode, boundBreakStatementNode, boundContinueStatementNode, boundReturnStatementNode, boundGotoStatementNode,
    boundConstructionStatementNode, boundExpressionStatementNode, boundSequenceStatementNode, boundSetVPtrStatementNode,
    boundValueNode, boundLiteralNode, boundStringLiteralNode, boundVariableNode, boundParameterNode, boundEnumConstantNode,
    boundFunctionGroupNode, boundTypeNode, boundMemberExprNode, boundFunctionCallNode, boundFunctionPtrCallNode, boundEmptyFunctionCallNode, boundExpressionListNode,
    boundConjunctionNode, boundDisjunctionNode, boundExpressionSequenceNode, boundConstructExpressionNode,
    boundConversionNode, boundAddressOfNode, boundDereferenceNode, boundRefToPtrNode, boundPtrToRefNode, boundDefaultInitNode,
    boundTemporaryNode, boundConstructTemporaryNode, boundCtorInitializerNode, boundDtorTerminatorNode, boundEmptyDestructorNode,
    boundThrowExpressionNode, boundTryStatementNode, boundHandlerNode, boundFunctionValueNode, boundVariableAsVoidPtrNode
};

std::string BoundNodeKindStr(BoundNodeKind nodeKind);

class BoundNode
{
public:
    BoundNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_);
    virtual ~BoundNode();
    virtual void Accept(BoundTreeVisitor& visitor) = 0;
    inline BoundNodeKind Kind() const { return kind; }
    virtual Scope* GetMemberScope(otava::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const { return nullptr; }
    inline const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
    inline bool IsBoundAddressOfNode() const { return kind == BoundNodeKind::boundAddressOfNode; }
    inline bool IsBoundDereferenceNode() const { return kind == BoundNodeKind::boundDereferenceNode; }
    inline virtual bool IsReturnStatementNode() const { return kind == BoundNodeKind::boundReturnStatementNode; }
    inline bool IsBoundCaseStatementNode() const { return kind == BoundNodeKind::boundCaseStatementNode; }
    inline bool IsBoundMemberExprNode() const { return kind == BoundNodeKind::boundMemberExprNode; }
    inline bool IsBoundTypeNode() const { return kind == BoundNodeKind::boundTypeNode; }
    inline bool IsBoundFunctionGroupNode() const { return kind == BoundNodeKind::boundFunctionGroupNode; }
    inline bool IsBoundExpressionListNode() const { return kind == BoundNodeKind::boundExpressionListNode; }
    inline bool IsBoundParameterNode() const { return kind == BoundNodeKind::boundParameterNode; }
    inline bool IsBoundVariableNode() const { return kind == BoundNodeKind::boundVariableNode; }
    inline bool IsBoundEnumConstant() const { return kind == BoundNodeKind::boundEnumConstantNode; }
    inline bool IsBoundFunctionCallNode() const { return kind == BoundNodeKind::boundFunctionCallNode; }
    inline bool IsBoundFunctionPtrCallNode() const { return kind == BoundNodeKind::boundFunctionPtrCallNode; }
    inline bool IsBoundEmptyDestructorNode() const { return kind == BoundNodeKind::boundEmptyDestructorNode; }
    inline bool IsBoundConversionNode() const { return kind == BoundNodeKind::boundConversionNode; }
    inline bool IsBoundFunctionNode() const { return kind == BoundNodeKind::boundFunctionNode; }
    inline bool IsBoundCompoundStatementNode() const { return kind == BoundNodeKind::boundCompoundStatementNode; }
    inline bool IsSwitchStatementNode() const { return kind == BoundNodeKind::boundSwitchStatementNode; }
    inline bool IsWhileStatementNode() const { return kind == BoundNodeKind::boundWhileStatementNode; }
    inline bool IsDoStatementNode() const { return kind == BoundNodeKind::boundDoStatementNode; }
    inline bool IsForStatementNode() const { return kind == BoundNodeKind::boundForStatementNode; }
    inline bool IsIfStatementNode() const { return kind == BoundNodeKind::boundIfStatementNode; }
    inline bool IsBoundLiteralNode() const { return kind == BoundNodeKind::boundLiteralNode; }
    inline int Index() const { return index; }
    inline void SetIndex(int index_) { index = index_; }
private:
    BoundNodeKind kind;
    int index;
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
    inline BoundExpressionFlags Flags() const { return flags; }
    inline void SetFlags(BoundExpressionFlags flags_) { flags = flags_; }
    inline TypeSymbol* GetType() const { return type; }
    inline void SetType(TypeSymbol* type_) { type = type_; }
    virtual void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context);
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
    virtual bool IsNoReturnFunctionCall() const { return false; }
    virtual bool IsBoundThrowExpression() const { return false; }
private:
    BoundExpressionFlags flags;
    TypeSymbol* type;
};

class BoundValueExpressionNode : public BoundExpressionNode
{
public:
    BoundValueExpressionNode(otava::intermediate::Value* value_, TypeSymbol* type);
    bool HasValue() const override { return true; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    otava::intermediate::Value* value;
};

class BoundFunctionNode;

class BoundCompileUnitNode : public BoundNode
{
public:
    BoundCompileUnitNode();
    void Sort();
    inline OperationRepository* GetOperationRepository() const { return operationRepository.get(); }
    inline ArgumentConversionTable* GetArgumentConversionTable() const { return argumentConversionTable.get(); }
    inline FunctionTemplateRepository* GetFunctionTemplateRepository() const { return functionTemplateRepository.get(); }
    inline ClassTemplateRepository* GetClassTemplateRepository() const { return classTemplateRepository.get(); }
    inline InlineFunctionRepository* GetInlineFunctionRepository() const { return inlineFunctionRepository.get(); }
    inline BoundFunctionNode* GetCompileUnitInitializationFunction() { return compileUnitInitializationFunction.get(); }
    void AddDynamicInitialization(BoundExpressionNode* dynamicInitialization, BoundExpressionNode* atExitCall, const soul::ast::SourcePos& sourcePos, Context* context);
    void Accept(BoundTreeVisitor& visitor) override;
    void AddBoundNode(std::unique_ptr<BoundNode>&& node, Context* context);
    void AddBoundNodeForClass(ClassTypeSymbol* cls, const soul::ast::SourcePos& sourcePos, Context* context);
    inline const std::vector<std::unique_ptr<BoundNode>>& BoundNodes() const { return boundNodes; }
    inline void SetId(const std::string& id_) { id = id_; }
    inline const std::string& Id() const { return id; }
    otava::intermediate::Value* CreateBoundGlobalVariable(VariableSymbol* globalVariableSymbol, Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context,
        bool definition);
    void AddClassToGenerateDestructorList(ClassTypeSymbol* classType);
    inline const std::vector<ClassTypeSymbol*>& GenerateDestructorList() const { return generateDestructorList; }
private:
    std::string id;
    std::vector<std::unique_ptr<BoundNode>> boundNodes;
    std::unique_ptr<OperationRepository> operationRepository;
    std::unique_ptr<ArgumentConversionTable> argumentConversionTable;
    std::unique_ptr<FunctionTemplateRepository> functionTemplateRepository;
    std::unique_ptr<ClassTemplateRepository> classTemplateRepository;
    std::unique_ptr<InlineFunctionRepository> inlineFunctionRepository;
    std::vector<ClassTypeSymbol*> boundClasses;
    std::unique_ptr<BoundFunctionNode> compileUnitInitializationFunction;
    std::vector<ClassTypeSymbol*> generateDestructorList;
};

class BoundStatementNode;

class BoundCtorInitializerNode : public BoundNode
{
public:
    BoundCtorInitializerNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void AddBaseInitializer(BoundFunctionCallNode* baseInitializer);
    void AddSetVPtrStatement(BoundStatementNode* setVPtrStatement);
    void AddMemberInitializer(BoundFunctionCallNode* memberInitializer);
    void GenerateCode(BoundTreeVisitor& visitor, Emitter& emitter, Context* context);
private:
    std::vector<std::unique_ptr<BoundFunctionCallNode>> baseInitializers;
    std::vector<std::unique_ptr<BoundStatementNode>> setVPtrStatements;
    std::vector<std::unique_ptr<BoundFunctionCallNode>> memberInitializers;
};

class BoundDtorTerminatorNode : public BoundNode
{
public:
    BoundDtorTerminatorNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void AddSetVPtrStatement(BoundStatementNode* setVPtrStatement);
    void AddMemberTerminator(BoundFunctionCallNode* memberTerminator);
    void GenerateCode(BoundTreeVisitor& visitor, Emitter& emitter, Context* context);
    const std::vector<std::unique_ptr<BoundStatementNode>>& SetVPtrStatements() const { return setVPtrStatements; }
private:
    std::vector<std::unique_ptr<BoundStatementNode>> setVPtrStatements;
    std::vector<std::unique_ptr<BoundFunctionCallNode>> memberTerminators;
};

class BoundClassNode : public BoundNode
{
public:
    BoundClassNode(ClassTypeSymbol* cls_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    inline ClassTypeSymbol* GetClass() const { return cls; }
private:
    ClassTypeSymbol* cls;
};

class BoundCompoundStatementNode;

class BoundFunctionNode : public BoundNode
{
public:
    BoundFunctionNode(FunctionDefinitionSymbol* functionDefinitionSymbol_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void SetBody(BoundCompoundStatementNode* body_);
    inline const BoundCompoundStatementNode* Body() const { return body.get(); }
    inline BoundCompoundStatementNode* Body() { return body.get(); }
    void SetCtorInitializer(BoundCtorInitializerNode* ctorInitializer_);
    void SetDtorTerminator(BoundDtorTerminatorNode* dtorTerminator_);
    inline BoundCtorInitializerNode* CtorInitializer() const { return ctorInitializer.get(); }
    inline BoundDtorTerminatorNode* DtorTerminator() const { return dtorTerminator.get(); }
    inline FunctionDefinitionSymbol* GetFunctionDefinitionSymbol() { return functionDefinitionSymbol; }
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
    virtual int IndexOf(BoundStatementNode* stmt) { return -1; }
    inline BoundStatementNode* Parent() const { return parent; }
    inline void SetParent(BoundStatementNode* parent_) { parent = parent_; }
    inline bool Generated() const { return generated; }
    inline void SetGenerated() { generated = true; }
    inline bool Postfix() const { return postfix; }
    inline void SetPostfix() { postfix = true; }
    bool IsConditionalStatementInBlock(BoundCompoundStatementNode* block) const;
    BoundCompoundStatementNode* Block();
private:
    BoundStatementNode* parent;
    bool generated;
    bool postfix;
};

class BoundCompoundStatementNode : public BoundStatementNode
{
public:
    BoundCompoundStatementNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    int IndexOf(BoundStatementNode* stmt) override;
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
    inline BoundStatementNode* InitStatement() const { return initStatement.get(); }
    void SetCondition(BoundExpressionNode* condition_);
    inline BoundExpressionNode* GetCondition() const { return condition.get(); }
    inline BoundStatementNode* ThenStatement() const { return thenStatement.get(); }
    void SetThenStatement(BoundStatementNode* thenStatement_);
    inline BoundStatementNode* ElseStatement() const { return elseStatement.get(); }
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
    inline BoundStatementNode* InitStatement() const { return initStatement.get(); }
    void SetCondition(BoundExpressionNode* condition_);
    inline BoundExpressionNode* GetCondition() const { return condition.get(); }
    void SetStatement(BoundStatementNode* statement);
    inline BoundStatementNode* Statement() const { return statement.get(); }
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
    inline const std::vector<std::unique_ptr<BoundExpressionNode>>& CaseExprs() const { return caseExprs; }
    void InsertCaseExprToFront(BoundExpressionNode* caseExpr);
    void AddCaseExpr(BoundExpressionNode* caseExpr);
    inline BoundStatementNode* Statement() const { return stmt.get(); }
    void SetStatement(BoundStatementNode* stmt_);
private:
    std::vector<std::unique_ptr<BoundExpressionNode>> caseExprs;
    std::unique_ptr<BoundStatementNode> stmt;
};

class BoundDefaultStatementNode : public BoundStatementNode
{
public:
    BoundDefaultStatementNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    inline BoundStatementNode* Statement() const { return stmt.get(); }
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
    inline BoundExpressionNode* GetCondition() const { return condition.get(); }
    void SetStatement(BoundStatementNode* statement);
    inline BoundStatementNode* Statement() const { return statement.get(); }
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
    inline BoundExpressionNode* GetExpr() const { return expr.get(); }
    void SetStatement(BoundStatementNode* statement);
    inline BoundStatementNode* Statement() const { return statement.get(); }
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
    inline BoundStatementNode* InitStatement() const { return initStatement.get(); }
    void SetCondition(BoundExpressionNode* condition_);
    inline BoundExpressionNode* GetCondition() const { return condition.get(); }
    void SetLoopExpr(BoundExpressionNode* loopExpr_);
    inline BoundExpressionNode* GetLoopExpr() const { return loopExpr.get(); }
    void SetStatement(BoundStatementNode* statement);
    inline BoundStatementNode* Statement() const { return statement.get(); }
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
    inline BoundStatementNode* First() const { return first.get(); }
    inline BoundStatementNode* Second() const { return second.get(); }
    bool IsReturnStatementNode() const override { return second->IsReturnStatementNode(); }
    bool IsTerminator() const override { return second->IsTerminator(); }
private:
    std::unique_ptr<BoundStatementNode> first;
    std::unique_ptr<BoundStatementNode> second;
};

class BoundReturnStatementNode : public BoundStatementNode
{
public:
    BoundReturnStatementNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void SetExpr(BoundExpressionNode* expr_, const soul::ast::SourcePos& sourcePos, Context* context);
    inline BoundExpressionNode* GetExpr() const { return expr.get(); }
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
    inline BoundFunctionCallNode* ConstructorCall() const { return constructorCall.get(); }
    void SetDestructorCall(BoundFunctionCallNode* destructorCall_);
    inline BoundFunctionCallNode* DestructorCall() const { return destructorCall.get(); }
    inline BoundFunctionCallNode* ReleaseDestructorCall() { return destructorCall.release(); }
private:
    std::unique_ptr<BoundFunctionCallNode> constructorCall;
    std::unique_ptr<BoundFunctionCallNode> destructorCall;
};
    
class BoundExpressionStatementNode : public BoundStatementNode
{
public:
    BoundExpressionStatementNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void SetExpr(BoundExpressionNode* expr_, const soul::ast::SourcePos& sourcePos, Context* context);
    inline BoundExpressionNode* GetExpr() const { return expr.get(); }
    bool IsTerminator() const override;
private:
    std::unique_ptr<BoundExpressionNode> expr;
};

class BoundSetVPtrStatementNode : public BoundStatementNode
{
public:
    BoundSetVPtrStatementNode(BoundExpressionNode* thisPtr_, ClassTypeSymbol* forClass_, ClassTypeSymbol* vptrHolderClass_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    inline BoundExpressionNode* ThisPtr() const { return thisPtr.get(); }
    inline ClassTypeSymbol* GetClass() const { return forClass; }
    inline ClassTypeSymbol* GetVPtrHolderClass() const { return vptrHolderClass; }
private:
    std::unique_ptr<BoundExpressionNode> thisPtr;
    ClassTypeSymbol* forClass;
    ClassTypeSymbol* vptrHolderClass;
};

class BoundLiteralNode : public BoundExpressionNode
{
public:
    BoundLiteralNode(Value* value_, const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    inline Value* GetValue() const { return value; }
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
    inline Value* GetValue() const { return value; }
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
    inline VariableSymbol* GetVariable() const { return variable; }
    inline BoundExpressionNode* ThisPtr() const { return thisPtr.get(); }
    void SetThisPtr(BoundExpressionNode* thisPtr_);
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsBoundLocalVariable() const override;
    bool IsBoundMemberVariable() const override;
    bool IsLvalueExpression() const override { return true; }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    VariableSymbol* variable;
    std::unique_ptr<BoundExpressionNode> thisPtr;
};

class BoundParameterNode : public BoundExpressionNode
{
public:
    BoundParameterNode(ParameterSymbol* parameter_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    inline ParameterSymbol* GetParameter() const { return parameter; }
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
    inline EnumConstantSymbol* EnumConstant() const { return enumConstant; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
private:
    EnumConstantSymbol* enumConstant;
};

class BoundFunctionGroupNode : public BoundExpressionNode
{
public:
    BoundFunctionGroupNode(FunctionGroupSymbol* functionGroupSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    void Accept(BoundTreeVisitor& visitor) override;
    inline FunctionGroupSymbol* GetFunctionGroupSymbol() const { return functionGroupSymbol; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    void AddTemplateArg(TypeSymbol* templateArg);
    inline const std::vector<TypeSymbol*>& TemplateArgs() const { return templateArgs; }
private:
    FunctionGroupSymbol* functionGroupSymbol;
    std::vector<TypeSymbol*> templateArgs;
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
    BoundMemberExprNode(BoundExpressionNode* subject_, BoundExpressionNode* member_, otava::ast::NodeKind op_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    void Accept(BoundTreeVisitor& visitor) override;
    inline BoundExpressionNode* Subject() const { return subject.get(); }
    inline BoundExpressionNode* Member() const { return member.get(); }
    inline otava::ast::NodeKind Op() const { return op; }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
    std::unique_ptr<BoundExpressionNode> member;
    otava::ast::NodeKind op;
};

class BoundFunctionCallNode : public BoundExpressionNode
{
public:
    BoundFunctionCallNode(FunctionSymbol* functionSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override;
    inline FunctionSymbol* GetFunctionSymbol() const { return functionSymbol; }
    void AddArgument(BoundExpressionNode* arg);
    inline const std::vector<std::unique_ptr<BoundExpressionNode>>& Args() const { return args; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsLvalueExpression() const override;
    BoundExpressionNode* Clone() const override;
    bool CallsClassConstructor(ClassTypeSymbol*& cls, BoundExpressionNode*& firstArg, FunctionDefinitionSymbol*& destructor) const;
    bool IsNoReturnFunctionCall() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    FunctionSymbol* functionSymbol;
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
};

class BoundEmptyFunctionCallNode : public BoundExpressionNode
{
public:
    BoundEmptyFunctionCallNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
};

class BoundFunctionPtrCallNode : public BoundExpressionNode
{
public:
    BoundFunctionPtrCallNode(const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override { return true; }
    void AddArgument(BoundExpressionNode* arg);
    inline const std::vector<std::unique_ptr<BoundExpressionNode>>& Args() const { return args; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
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
    inline BoundExpressionNode* Left() const { return left.get(); }
    inline BoundExpressionNode* Right() const { return right.get(); }
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
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
    inline int Count() const { return exprs.size(); }
    inline const std::vector<std::unique_ptr<BoundExpressionNode>>& Exprs() const { return exprs; }
    inline BoundExpressionNode* ReleaseExpr(int i) { return exprs[i].release(); }
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::vector<std::unique_ptr<BoundExpressionNode>> exprs;
};

class BoundConjunctionNode : public BoundExpressionNode
{
public:
    BoundConjunctionNode(BoundExpressionNode* left_, BoundExpressionNode* right_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* boolType);
    inline BoundExpressionNode* Left() const { return left.get(); }
    inline BoundExpressionNode* Right() const { return right.get(); }
    void SetTemporary(BoundVariableNode* temporary_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> left;
    std::unique_ptr<BoundExpressionNode> right;
    std::unique_ptr<BoundVariableNode> temporary;
};

class BoundDisjunctionNode : public BoundExpressionNode
{
public:
    BoundDisjunctionNode(BoundExpressionNode* left_, BoundExpressionNode* right_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* boolType);
    inline BoundExpressionNode* Left() const { return left.get(); }
    inline BoundExpressionNode* Right() const { return right.get(); }
    void SetTemporary(BoundVariableNode* temporary_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
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
    inline BoundExpressionNode* Subject() const { return subject.get(); }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
    FunctionSymbol* conversionFunction;
};

class BoundAddressOfNode : public BoundExpressionNode
{
public:    
    BoundAddressOfNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline BoundExpressionNode* Subject() { return subject.get(); }
    inline BoundExpressionNode* ReleaseSubject() { return subject.release(); }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
};

class BoundDereferenceNode : public BoundExpressionNode
{
public:
    BoundDereferenceNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    BoundDereferenceNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_, OperationFlags kind_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsLvalueExpression() const override { return true; }
    inline BoundExpressionNode* Subject() { return subject.get(); }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    OperationFlags kind;
    std::unique_ptr<BoundExpressionNode> subject;
};

class BoundRefToPtrNode : public BoundExpressionNode
{
public:
    BoundRefToPtrNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
};

class BoundPtrToRefNode : public BoundExpressionNode
{
public:
    BoundPtrToRefNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    inline BoundExpressionNode* Subject() const { return subject.get(); }
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
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
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
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
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
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
    inline BoundExpressionNode* Temporary() const { return temporary.get(); }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
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
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> allocation;
    std::unique_ptr<BoundExpressionNode> constructObjectCall;
    bool hasPlacement;
};

class BoundGlobalVariableDefinitionNode : public BoundNode
{
public:
    BoundGlobalVariableDefinitionNode(VariableSymbol* globalVariable_, const soul::ast::SourcePos& sourcePos_);
    inline VariableSymbol* GetGlobalVariable() const { return globalVariable; }
    void Accept(BoundTreeVisitor& visitor) override;
private:
    VariableSymbol* globalVariable;
};

class BoundEmptyDestructorNode : public BoundExpressionNode
{
public:
    BoundEmptyDestructorNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

class BoundFunctionValueNode : public BoundExpressionNode
{
public:
    BoundFunctionValueNode(FunctionSymbol* function_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    FunctionSymbol* function;
};

class BoundVariableAsVoidPtrNode : public BoundExpressionNode
{
public:
    BoundVariableAsVoidPtrNode(BoundExpressionNode* addrOfBoundVariable_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_);
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> addrOfBoundVariable;
};

bool InDirectSwitchStatement(BoundStatementNode* statement);

} // namespace otava::symbols
