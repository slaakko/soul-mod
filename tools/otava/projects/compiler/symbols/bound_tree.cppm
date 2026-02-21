// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.bound.tree;

import std;
import soul.ast.source.pos;
import otava.ast;
import otava.symbols.emitter;
import otava.symbols.symbol;
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

constexpr OperationFlags operator|(OperationFlags left, OperationFlags right) noexcept
{
    return OperationFlags(std::int32_t(left) | std::int32_t(right));
}

constexpr OperationFlags operator&(OperationFlags left, OperationFlags right) noexcept
{
    return OperationFlags(std::int32_t(left) & std::int32_t(right));
}

constexpr OperationFlags operator~(OperationFlags flags) noexcept
{
    return OperationFlags(~std::int32_t(flags));
}

constexpr std::uint8_t GetDerefCount(OperationFlags flags) noexcept
{
    return static_cast<std::uint8_t>(static_cast<std::int32_t>(flags & OperationFlags::derefCount) >> 8);
}

constexpr OperationFlags SetDerefCount(OperationFlags flags, std::uint8_t n) noexcept
{
    return OperationFlags(flags | OperationFlags(static_cast<std::int32_t>(n) << 8));
}

class FunctionSymbol;
class FunctionGroupSymbol;
class VariableSymbol;
class ParameterSymbol;
class EnumConstantSymbol;
class TypeSymbol;
class ClassTypeSymbol;
class ClassGroupSymbol;
class AliasGroupSymbol;
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
    boundWhileStatementNode, boundDoStatementNode, boundForStatementNode, boundBreakStatementNode, boundContinueStatementNode,
    boundReturnStatementNode, boundGotoStatementNode, boundLabeledStatementNode, boundEmptyStatementNode,
    boundConstructionStatementNode, boundExpressionStatementNode, boundSequenceStatementNode, boundSetVPtrStatementNode, boundAliasDeclarationStatementNode,
    boundValueNode, boundLiteralNode, boundStringLiteralNode, boundVariableNode, boundParentVariableNode, boundParameterNode, boundParentParameterNode,
    boundEnumConstantNode, boundFunctionGroupNode, boundClassGroupNode, boundAliasGroupNode, boundTypeNode, boundMemberExprNode, boundFunctionCallNode,
    boundFunctionPtrCallNode, boundEmptyFunctionCallNode, boundExpressionListNode,
    boundConjunctionNode, boundDisjunctionNode, boundConditionalExprNode, boundExpressionSequenceNode, boundConstructExpressionNode,
    boundConversionNode, boundAddressOfNode, boundDereferenceNode, boundRefToPtrNode, boundPtrToRefNode, boundDefaultInitNode,
    boundTemporaryNode, boundConstructTemporaryNode, boundCtorInitializerNode, boundDtorTerminatorNode, boundEmptyDestructorNode,
    boundHandlerNode, boundFunctionValueNode, boundVariableAsVoidPtrNode, boundAdjustedThisPtrNode, boundOperatorFnNode
};

std::string BoundNodeKindStr(BoundNodeKind nodeKind);

class BoundNode
{
public:
    BoundNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_) noexcept;
    virtual ~BoundNode();
    virtual void Accept(BoundTreeVisitor& visitor) = 0;
    virtual bool MayThrow() const noexcept { return false; }
    inline BoundNodeKind Kind() const noexcept { return kind; }
    virtual Scope* GetMemberScope(otava::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const { return nullptr; }
    inline const soul::ast::SourcePos& GetSourcePos() const noexcept { return sourcePos; }
    void SetSourcePos(const soul::ast::SourcePos& sourcePos_) noexcept { sourcePos = sourcePos_; }
    inline bool IsBoundAddressOfNode() const noexcept { return kind == BoundNodeKind::boundAddressOfNode; }
    inline bool IsBoundDereferenceNode() const noexcept { return kind == BoundNodeKind::boundDereferenceNode; }
    inline bool IsReturnStatementNode() const noexcept { return kind == BoundNodeKind::boundReturnStatementNode; }
    virtual bool IsReturnOrSequenceReturnStatementNode() const noexcept { return false; }
    inline bool IsBoundCaseStatementNode() const noexcept { return kind == BoundNodeKind::boundCaseStatementNode; }
    inline bool IsBoundMemberExprNode() const noexcept { return kind == BoundNodeKind::boundMemberExprNode; }
    inline bool IsBoundTypeNode() const noexcept { return kind == BoundNodeKind::boundTypeNode; }
    inline bool IsBoundFunctionGroupNode() const noexcept { return kind == BoundNodeKind::boundFunctionGroupNode; }
    inline bool IsBoundClassGroupNode() const noexcept { return kind == BoundNodeKind::boundClassGroupNode; }
    inline bool IsBoundAliasGroupNode() const noexcept { return kind == BoundNodeKind::boundAliasGroupNode; }
    inline bool IsBoundExpressionListNode() const noexcept { return kind == BoundNodeKind::boundExpressionListNode; }
    inline bool IsBoundParameterNode() const noexcept { return kind == BoundNodeKind::boundParameterNode; }
    inline bool IsBoundParentParameterNode() const noexcept { return kind == BoundNodeKind::boundParentParameterNode; }
    inline bool IsBoundVariableNode() const noexcept { return kind == BoundNodeKind::boundVariableNode; }
    inline bool IsBoundParentVariableNode() const noexcept { return kind == BoundNodeKind::boundParentVariableNode; }
    inline bool IsBoundEnumConstant() const noexcept { return kind == BoundNodeKind::boundEnumConstantNode; }
    inline bool IsBoundFunctionCallNode() const noexcept { return kind == BoundNodeKind::boundFunctionCallNode; }
    inline bool IsBoundConstructTemporaryNode() const noexcept { return kind == BoundNodeKind::boundConstructTemporaryNode; }
    inline bool IsBoundFunctionPtrCallNode() const noexcept { return kind == BoundNodeKind::boundFunctionPtrCallNode; }
    inline bool IsBoundEmptyDestructorNode() const noexcept { return kind == BoundNodeKind::boundEmptyDestructorNode; }
    inline bool IsBoundConversionNode() const noexcept { return kind == BoundNodeKind::boundConversionNode; }
    inline bool IsBoundFunctionNode() const noexcept { return kind == BoundNodeKind::boundFunctionNode; }
    inline bool IsBoundCompoundStatementNode() const { return kind == BoundNodeKind::boundCompoundStatementNode; }
    inline bool IsSwitchStatementNode() const noexcept { return kind == BoundNodeKind::boundSwitchStatementNode; }
    inline bool IsWhileStatementNode() const noexcept { return kind == BoundNodeKind::boundWhileStatementNode; }
    inline bool IsDoStatementNode() const noexcept { return kind == BoundNodeKind::boundDoStatementNode; }
    inline bool IsForStatementNode() const noexcept { return kind == BoundNodeKind::boundForStatementNode; }
    inline bool IsIfStatementNode() const noexcept { return kind == BoundNodeKind::boundIfStatementNode; }
    inline bool IsBoundConstructionStatementNode() const noexcept { return kind == BoundNodeKind::boundConstructionStatementNode; }
    inline bool IsBoundExpressionStatementNode() const noexcept { return kind == BoundNodeKind::boundExpressionStatementNode; }
    inline bool IsBoundSequenceStatementNode() const noexcept { return kind == BoundNodeKind::boundSequenceStatementNode; }
    inline bool IsBoundLiteralNode() const noexcept { return kind == BoundNodeKind::boundLiteralNode; }
    inline int Index() const noexcept { return index; }
    inline void SetIndex(int index_) noexcept { index = index_; }
    inline otava::ast::Node* Source() const noexcept { return source.get(); }
    inline void SetSource(otava::ast::Node* source_) noexcept { source.reset(source_); }
private:
    BoundNodeKind kind;
    int index;
    soul::ast::SourcePos sourcePos;
    std::unique_ptr<otava::ast::Node> source;
};

enum class BoundExpressionFlags
{
    none = 0, bindToRvalueRef = 1 << 0, virtualCall = 1 << 1, deref = 1 << 2
};

constexpr BoundExpressionFlags operator|(BoundExpressionFlags left, BoundExpressionFlags right) noexcept
{
    return BoundExpressionFlags(int(left) | int(right));
}

constexpr BoundExpressionFlags operator&(BoundExpressionFlags left, BoundExpressionFlags right) noexcept
{
    return BoundExpressionFlags(int(left) & int(right));
}

constexpr BoundExpressionFlags operator~(BoundExpressionFlags flag) noexcept
{
    return BoundExpressionFlags(~int(flag));
}

class BoundExpressionNode : public BoundNode
{
public:
    BoundExpressionNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    inline BoundExpressionFlags Flags() const noexcept { return flags; }
    inline void SetFlags(BoundExpressionFlags flags_) noexcept { flags = flags_; }
    inline TypeSymbol* GetType() const noexcept { return type; }
    inline void SetType(TypeSymbol* type_) noexcept { type = type_; }
    virtual void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context);
    Scope* GetMemberScope(otava::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const override;
    bool BindToRvalueRef() const noexcept { return GetFlag(BoundExpressionFlags::bindToRvalueRef); }
    virtual bool HasValue() const noexcept { return false; }
    virtual void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context);
    virtual BoundExpressionNode* Clone() const = 0;
    inline bool GetFlag(BoundExpressionFlags flag) const noexcept { return (flags & flag) != BoundExpressionFlags::none; }
    inline void SetFlag(BoundExpressionFlags flag) noexcept { flags = flags | flag; }
    virtual bool IsBoundLocalVariable() const noexcept { return false; }
    virtual bool IsBoundMemberVariable() const noexcept { return false; }
    virtual bool IsBoundParentLocalVariable() const noexcept { return false; }
    virtual bool IsBoundParentMemberVariable() const noexcept { return false; }
    virtual bool IsLvalueExpression() const noexcept { return false; }
    virtual bool IsNoReturnFunctionCall() const noexcept { return false; }
private:
    BoundExpressionFlags flags;
    TypeSymbol* type;
};

class BoundValueExpressionNode : public BoundExpressionNode
{
public:
    BoundValueExpressionNode(otava::intermediate::Value* value_, TypeSymbol* type);
    bool HasValue() const noexcept override { return true; }
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
    ~BoundCompileUnitNode();
    void Sort();
    inline OperationRepository* GetOperationRepository() const { return operationRepository.get(); }
    inline ArgumentConversionTable* GetArgumentConversionTable() const { return argumentConversionTable.get(); }
    inline FunctionTemplateRepository* GetFunctionTemplateRepository() const { return functionTemplateRepository.get(); }
    inline ClassTemplateRepository* GetClassTemplateRepository() const { return classTemplateRepository.get(); }
    inline InlineFunctionRepository* GetInlineFunctionRepository() const { return inlineFunctionRepository.get(); }
    inline BoundFunctionNode* GetCompileUnitInitializationFunction() { return compileUnitInitializationFunction; }
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
    std::set<ClassTypeSymbol*> boundClasses;
    BoundFunctionNode* compileUnitInitializationFunction;
    std::vector<ClassTypeSymbol*> generateDestructorList;
};

class BoundStatementNode;

class BoundCtorInitializerNode : public BoundNode
{
public:
    BoundCtorInitializerNode(const soul::ast::SourcePos& sourcePos_);
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
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
class BoundReturnStatementNode;
class BoundConstructionStatementNode;

class BoundFunctionNode : public BoundNode
{
public:
    BoundFunctionNode(FunctionDefinitionSymbol* functionDefinitionSymbol_, const soul::ast::SourcePos& sourcePos_);
    ~BoundFunctionNode();
    void Accept(BoundTreeVisitor& visitor) override;
    void SetBody(BoundCompoundStatementNode* body_);
    inline const BoundCompoundStatementNode* Body() const { return body.get(); }
    inline BoundCompoundStatementNode* Body() { return body.get(); }
    void SetCtorInitializer(BoundCtorInitializerNode* ctorInitializer_);
    void SetDtorTerminator(BoundDtorTerminatorNode* dtorTerminator_);
    inline BoundCtorInitializerNode* CtorInitializer() const { return ctorInitializer.get(); }
    inline BoundDtorTerminatorNode* DtorTerminator() const { return dtorTerminator.get(); }
    FunctionDefinitionSymbol* GetFunctionDefinitionSymbol() { return functionDefinitionSymbol; }
    void AddDefaultFunctionSymbol(FunctionSymbol* defaultFunctionSymbol);
    inline void SetSerial(int serial_) { serial = serial_; };
    inline int Serial() const { return serial; }
    void SetSetLineStatementNode(otava::ast::Node* setLineStatementNode_);
    inline otava::ast::Node* GetSetLineStatementNode() const { return setLineStatementNode.get(); }
    void SetBoundSetLineStatement(BoundStatementNode* boundSetLineStatement_);
    inline BoundStatementNode* GetBoundSetLineStatement() const { return boundSetLineStatement.get(); }
private:
    FunctionDefinitionSymbol* functionDefinitionSymbol;
    std::unique_ptr<BoundCtorInitializerNode> ctorInitializer;
    std::unique_ptr<BoundDtorTerminatorNode> dtorTerminator;
    std::unique_ptr<BoundCompoundStatementNode> body;
    std::vector<std::unique_ptr<FunctionSymbol>> defaultFunctionSymbols;
    int serial;
    std::unique_ptr<otava::ast::Node> setLineStatementNode;
    std::unique_ptr<BoundStatementNode> boundSetLineStatement;
};

class BoundStatementNode : public BoundNode
{
public:
    BoundStatementNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_) noexcept;
    virtual std::string Name() const = 0;
    virtual BoundStatementNode* Clone() const = 0;
    virtual bool EndsWithTerminator() const noexcept { return IsTerminator(); }
    virtual bool IsTerminator() const noexcept { return false; }
    virtual int IndexOf(BoundStatementNode* stmt) noexcept { return -1; }
    virtual bool ContainsLocalVariableWithDestructor() const noexcept { return false; }
    virtual bool ConstructsLocalVariableWithDestructor() const noexcept { return false; }
    virtual bool HasInvokeStatementsWithDestructor() const noexcept { return false; }
    virtual std::vector<std::unique_ptr<BoundConstructionStatementNode>> ReleaseInvokeStatementsWithDestructor();
    inline BoundStatementNode* Parent() const noexcept { return parent; }
    inline void SetParent(BoundStatementNode* parent_) noexcept { parent = parent_; }
    inline bool Generated() const noexcept { return generated; }
    inline void SetGenerated() noexcept { generated = true; }
    inline bool Postfix() const noexcept { return postfix; }
    inline void SetPostfix() noexcept { postfix = true; }
    bool IsConditionalStatementInBlock(BoundCompoundStatementNode* block) const noexcept;
    BoundCompoundStatementNode* Block() noexcept;
private:
    BoundStatementNode* parent;
    bool generated;
    bool postfix;
};

class BoundEmptyStatementNode : public BoundStatementNode
{
public:
    BoundEmptyStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "empty"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
};

class BoundCompoundStatementNode : public BoundStatementNode
{
public:
    BoundCompoundStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "compound"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    int IndexOf(BoundStatementNode* stmt) noexcept override;
    void AddStatement(BoundStatementNode* statement);
    inline const std::vector<std::unique_ptr<BoundStatementNode>>& Statements() const noexcept { return statements; }
    void SetInvokeStatementsWithDestructor(std::vector<std::unique_ptr<BoundConstructionStatementNode>>&& invokeStatementsWithDestructor_);
    bool HasInvokeStatementsWithDestructor() const noexcept override { return !invokeStatementsWithDestructor.empty(); }
    const std::vector<std::unique_ptr<BoundConstructionStatementNode>>& InvokeStatementsWithDestructor() const { return invokeStatementsWithDestructor; }
    std::vector<std::unique_ptr<BoundConstructionStatementNode>> ReleaseInvokeStatementsWithDestructor() override
    {
        return std::move(invokeStatementsWithDestructor);
    }
    bool EndsWithTerminator() const noexcept override;
    bool ContainsLocalVariableWithDestructor() const noexcept override;
    inline int BlockId() const noexcept { return blockId; }
    inline void SetBlockId(int blockId_) noexcept { blockId = blockId_; }
private:
    std::vector<std::unique_ptr<BoundStatementNode>> statements;
    std::vector<std::unique_ptr<BoundConstructionStatementNode>> invokeStatementsWithDestructor;
    int blockId;
};

class BoundIfStatementNode : public BoundStatementNode
{
public:
    BoundIfStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "if"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool MayThrow() const noexcept override;
    void SetCondition(BoundExpressionNode* condition_) noexcept;
    inline BoundExpressionNode* GetCondition() const noexcept { return condition.get(); }
    inline BoundStatementNode* ThenStatement() const noexcept { return thenStatement.get(); }
    void SetThenStatement(BoundStatementNode* thenStatement_) noexcept;
    inline BoundStatementNode* ElseStatement() const noexcept { return elseStatement.get(); }
    void SetElseStatement(BoundStatementNode* elseStatement_) noexcept;
    bool ContainsLocalVariableWithDestructor() const noexcept override;
    inline int BlockId() const noexcept { return blockId; }
    inline void SetBlockId(int blockId_) noexcept { blockId = blockId_; }
private:
    std::unique_ptr<BoundExpressionNode> condition;
    std::unique_ptr<BoundStatementNode> thenStatement;
    std::unique_ptr<BoundStatementNode> elseStatement;
    int blockId;
};

class BoundSwitchStatementNode : public BoundStatementNode
{
public:
    BoundSwitchStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "switch"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool MayThrow() const noexcept override;
    void SetCondition(BoundExpressionNode* condition_) noexcept;
    inline BoundExpressionNode* GetCondition() const noexcept { return condition.get(); }
    void SetStatement(BoundStatementNode* statement) noexcept;
    inline BoundStatementNode* Statement() const noexcept { return statement.get(); }
    bool ContainsLocalVariableWithDestructor() const noexcept override;
    inline int BlockId() const noexcept { return blockId; }
    inline void SetBlockId(int blockId_) noexcept { blockId = blockId_; }
private:
    std::unique_ptr<BoundExpressionNode> condition;
    std::unique_ptr<BoundStatementNode> statement;
    int blockId;
};

class BoundCaseStatementNode : public BoundStatementNode
{
public:
    BoundCaseStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "case"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool MayThrow() const noexcept override;
    inline const std::vector<std::unique_ptr<BoundExpressionNode>>& CaseExprs() const noexcept { return caseExprs; }
    void InsertCaseExprToFront(BoundExpressionNode* caseExpr);
    void AddCaseExpr(BoundExpressionNode* caseExpr);
    inline BoundStatementNode* Statement() const noexcept { return stmt.get(); }
    void SetStatement(BoundStatementNode* stmt_) noexcept;
    bool ContainsLocalVariableWithDestructor() const noexcept override;
private:
    std::vector<std::unique_ptr<BoundExpressionNode>> caseExprs;
    std::unique_ptr<BoundStatementNode> stmt;
};

class BoundDefaultStatementNode : public BoundStatementNode
{
public:
    BoundDefaultStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "default"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool MayThrow() const noexcept override;
    inline BoundStatementNode* Statement() const noexcept { return stmt.get(); }
    void SetStatement(BoundStatementNode* stmt_) noexcept;
    bool ContainsLocalVariableWithDestructor() const noexcept override;
private:
    std::unique_ptr<BoundStatementNode> stmt;
};

class BoundWhileStatementNode : public BoundStatementNode
{
public:
    BoundWhileStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "while"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool MayThrow() const noexcept override;
    void SetCondition(BoundExpressionNode* condition_) noexcept;
    inline BoundExpressionNode* GetCondition() const noexcept { return condition.get(); }
    void SetStatement(BoundStatementNode* statement) noexcept;
    inline BoundStatementNode* Statement() const noexcept { return statement.get(); }
    bool ContainsLocalVariableWithDestructor() const noexcept override;
    inline int BlockId() const noexcept { return blockId; }
    inline void SetBlockId(int blockId_) noexcept { blockId = blockId_; }
private:
    std::unique_ptr<BoundExpressionNode> condition;
    std::unique_ptr<BoundStatementNode> statement;
    int blockId;
};

class BoundDoStatementNode : public BoundStatementNode
{
public:
    BoundDoStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "do"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool MayThrow() const noexcept override;
    void SetExpr(BoundExpressionNode* condition_) noexcept;
    inline BoundExpressionNode* GetExpr() const noexcept { return expr.get(); }
    void SetStatement(BoundStatementNode* statement) noexcept;
    inline BoundStatementNode* Statement() const noexcept { return statement.get(); }
    bool ContainsLocalVariableWithDestructor() const noexcept override;
private:
    std::unique_ptr<BoundExpressionNode> expr;
    std::unique_ptr<BoundStatementNode> statement;
};

class BoundForStatementNode : public BoundStatementNode
{
public:
    BoundForStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "for"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool MayThrow() const noexcept override;
    void SetInitStatement(BoundStatementNode* initStatement_) noexcept;
    inline BoundStatementNode* InitStatement() const noexcept { return initStatement.get(); }
    void SetCondition(BoundExpressionNode* condition_) noexcept;
    inline BoundExpressionNode* GetCondition() const noexcept { return condition.get(); }
    void SetLoopExpr(BoundExpressionNode* loopExpr_) noexcept;
    inline BoundExpressionNode* GetLoopExpr() const noexcept { return loopExpr.get(); }
    void SetStatement(BoundStatementNode* statement) noexcept;
    inline BoundStatementNode* Statement() const noexcept { return statement.get(); }
    bool ContainsLocalVariableWithDestructor() const noexcept override;
    inline int BlockId() const noexcept { return blockId; }
    inline void SetBlockId(int blockId_) noexcept { blockId = blockId_; }
private:
    std::unique_ptr<BoundStatementNode> initStatement;
    std::unique_ptr<BoundExpressionNode> condition;
    std::unique_ptr<BoundExpressionNode> loopExpr;
    std::unique_ptr<BoundStatementNode> statement;
    int blockId;
};

class BoundSequenceStatementNode : public BoundStatementNode
{
public:
    BoundSequenceStatementNode(const soul::ast::SourcePos& sourcePos_, BoundStatementNode* first_, BoundStatementNode* second_) noexcept;
    std::string Name() const override { return "sequence"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool MayThrow() const noexcept override;
    inline BoundStatementNode* First() const noexcept { return first.get(); }
    inline void SetFirst(BoundStatementNode* first_)noexcept { first.reset(first_); }
    inline BoundStatementNode* Second() const noexcept { return second.get(); }
    inline void SetSecond(BoundStatementNode* second_) noexcept { second.reset(second_); }
    bool IsTerminator() const noexcept override { return second->IsTerminator(); }
    bool IsReturnOrSequenceReturnStatementNode() const noexcept override { return second->IsReturnStatementNode(); }
    bool ContainsLocalVariableWithDestructor() const noexcept override;
    bool HasInvokeStatementsWithDestructor() const noexcept override { return first->HasInvokeStatementsWithDestructor(); }
    std::vector<std::unique_ptr<BoundConstructionStatementNode>> ReleaseInvokeStatementsWithDestructor() override
    {
        return first->ReleaseInvokeStatementsWithDestructor();
    }
private:
    std::unique_ptr<BoundStatementNode> first;
    std::unique_ptr<BoundStatementNode> second;
};

class BoundBreakStatementNode : public BoundStatementNode
{
public:
    BoundBreakStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "break"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool IsTerminator() const noexcept override { return true; }
};

class BoundContinueStatementNode : public BoundStatementNode
{
public:
    BoundContinueStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "continue"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool IsTerminator() const noexcept override { return true; }
};

class BoundReturnStatementNode : public BoundStatementNode
{
public:
    BoundReturnStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "return"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool MayThrow() const noexcept override;
    void SetExpr(BoundExpressionNode* expr_) noexcept;
    void SetExpr(BoundExpressionNode* expr_, const soul::ast::SourcePos& sourcePos, Context* context);
    inline BoundExpressionNode* GetExpr() const noexcept { return expr.get(); }
    bool IsTerminator() const noexcept override { return true; }
    bool IsReturnOrSequenceReturnStatementNode() const noexcept override { return true; }
private:
    std::unique_ptr<BoundExpressionNode> expr;
};

class BoundLabeledStatementNode : public BoundStatementNode
{
public:
    BoundLabeledStatementNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& label_, BoundStatementNode* stmt_);
    std::string Name() const override { return "labeled"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    const std::u32string& Label() const noexcept { return label; }
    inline void SetStatement(BoundStatementNode* stmt_) noexcept { stmt.reset(stmt_); }
    BoundStatementNode* Statement() const noexcept { return stmt.get(); }
    otava::intermediate::BasicBlock* GetBB(Emitter& emitter);
    bool ContainsLocalVariableWithDestructor() const noexcept override;
private:
    std::u32string label;
    std::unique_ptr<BoundStatementNode> stmt;
    otava::intermediate::BasicBlock* bb;
};

class BoundGotoStatementNode : public BoundStatementNode
{
public:
    BoundGotoStatementNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& target_);
    std::string Name() const override { return "goto"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool IsTerminator() const noexcept override { return true; }
    inline const std::u32string& Target() const noexcept { return target; }
    inline void SetLabeledStatement(BoundLabeledStatementNode* labeledStatement_) noexcept { labeledStatement = labeledStatement_; }
    otava::intermediate::BasicBlock* GetBB(Emitter& emitter);
private:
    std::u32string target;
    BoundLabeledStatementNode* labeledStatement;
};

class BoundConstructionStatementNode : public BoundStatementNode
{
public:
    BoundConstructionStatementNode(const soul::ast::SourcePos& sourcePos_, BoundFunctionCallNode* constructorCall_) noexcept;
    std::string Name() const override { return "construction"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool MayThrow() const noexcept override;
    inline BoundFunctionCallNode* ConstructorCall() const noexcept { return constructorCall.get(); }
    void SetDestructorCall(BoundFunctionCallNode* destructorCall_) noexcept;
    inline BoundFunctionCallNode* DestructorCall() const noexcept { return destructorCall.get(); }
    inline BoundFunctionCallNode* ReleaseDestructorCall() noexcept { return destructorCall.release(); }
    inline VariableSymbol* Variable() const noexcept { return variable; }
    inline void SetVariable(VariableSymbol* variable_) noexcept { variable = variable_; }
    bool ContainsLocalVariableWithDestructor() const noexcept override;
    bool ConstructsLocalVariableWithDestructor() const noexcept override;
private:
    std::unique_ptr<BoundFunctionCallNode> constructorCall;
    std::unique_ptr<BoundFunctionCallNode> destructorCall;
    VariableSymbol* variable;
};

class BoundExpressionStatementNode : public BoundStatementNode
{
public:
    BoundExpressionStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "expression"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    bool MayThrow() const noexcept override;
    void SetExpr(BoundExpressionNode* expr_) noexcept;
    void SetExpr(BoundExpressionNode* expr_, const soul::ast::SourcePos& sourcePos, Context* context);
    inline BoundExpressionNode* GetExpr() const noexcept { return expr.get(); }
    bool IsTerminator() const noexcept override;
private:
    std::unique_ptr<BoundExpressionNode> expr;
};

class BoundSetVPtrStatementNode : public BoundStatementNode
{
public:
    BoundSetVPtrStatementNode(BoundExpressionNode* thisPtr_, ClassTypeSymbol* forClass_, ClassTypeSymbol* vptrHolderClass_,
        const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "setvptr"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
    inline BoundExpressionNode* ThisPtr() const noexcept { return thisPtr.get(); }
    inline ClassTypeSymbol* GetClass() const noexcept { return forClass; }
    inline ClassTypeSymbol* GetVPtrHolderClass() const noexcept { return vptrHolderClass; }
private:
    std::unique_ptr<BoundExpressionNode> thisPtr;
    ClassTypeSymbol* forClass;
    ClassTypeSymbol* vptrHolderClass;
};

class BoundAliasDeclarationStatementNode : public BoundStatementNode
{
public:
    BoundAliasDeclarationStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    std::string Name() const override { return "alias"; }
    void Accept(BoundTreeVisitor& visitor) override;
    BoundStatementNode* Clone() const override;
};

class BoundLiteralNode : public BoundExpressionNode
{
public:
    BoundLiteralNode(Value* value_, const soul::ast::SourcePos& sourcePos_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const noexcept override { return true; }
    Value* GetValue() const noexcept { return value; }
    void SetValue(Value* value_) noexcept { value = value_; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
private:
    Value* value;
};

class BoundStringLiteralNode : public BoundExpressionNode
{
public:
    BoundStringLiteralNode(Value* value_, const soul::ast::SourcePos& sourcePos_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const noexcept override { return true; }
    inline Value* GetValue() const noexcept { return value; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
private:
    Value* value;
    otava::intermediate::Value* irValue;
};

class BoundVariableNode : public BoundExpressionNode
{
public:
    BoundVariableNode(VariableSymbol* variable_, const soul::ast::SourcePos& sourcePos_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const noexcept override { return true; }
    VariableSymbol* GetVariable() const noexcept { return variable; }
    BoundExpressionNode* ThisPtr() const noexcept { return thisPtr.get(); }
    void SetThisPtr(BoundExpressionNode* thisPtr_) noexcept;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsBoundLocalVariable() const noexcept override;
    bool IsBoundMemberVariable() const noexcept override;
    bool IsLvalueExpression() const noexcept override { return true; }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    VariableSymbol* variable;
    std::unique_ptr<BoundExpressionNode> thisPtr;
};

class BoundParentVariableNode : public BoundExpressionNode
{
public:
    BoundParentVariableNode(VariableSymbol* variable_, const soul::ast::SourcePos& sourcePos_) noexcept;
    inline int Level() const noexcept { return level; }
    inline void SetLevel(int level_) noexcept { level = level_; }
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const noexcept override { return true; }
    inline VariableSymbol* GetVariable() const noexcept { return variable; }
    void SetThisPtr(BoundExpressionNode* thisPtr_) noexcept;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsBoundParentLocalVariable() const noexcept override;
    bool IsBoundParentMemberVariable() const noexcept override;
    bool IsLvalueExpression() const noexcept override { return true; }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    VariableSymbol* variable;
    int level;
    std::unique_ptr<BoundExpressionNode> thisPtr;
};

class BoundParameterNode : public BoundExpressionNode
{
public:
    BoundParameterNode(ParameterSymbol* parameter_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const noexcept override { return true; }
    inline ParameterSymbol* GetParameter() const noexcept { return parameter; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsLvalueExpression() const noexcept override { return true; }
    BoundExpressionNode* Clone() const override;
private:
    ParameterSymbol* parameter;
};

class BoundParentParameterNode : public BoundExpressionNode
{
public:
    BoundParentParameterNode(ParameterSymbol* parameter_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type) noexcept;
    inline int Level() const noexcept { return level; }
    inline void SetLevel(int level_) noexcept { level = level_; }
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const noexcept override { return true; }
    inline ParameterSymbol* GetParameter() const noexcept { return parameter; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsLvalueExpression() const noexcept override { return true; }
    BoundExpressionNode* Clone() const override;
private:
    ParameterSymbol* parameter;
    int level;
};

class BoundEnumConstant : public BoundExpressionNode
{
public:
    BoundEnumConstant(EnumConstantSymbol* enumConstant_, const soul::ast::SourcePos& sourcePos_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool HasValue() const noexcept override { return true; }
    EnumConstantSymbol* EnumConstant() const noexcept { return enumConstant; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
private:
    EnumConstantSymbol* enumConstant;
};

class BoundFunctionGroupNode : public BoundExpressionNode
{
public:
    BoundFunctionGroupNode(FunctionGroupSymbol* functionGroupSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    inline FunctionGroupSymbol* GetFunctionGroupSymbol() const noexcept { return functionGroupSymbol; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    void AddTemplateArg(TypeSymbol* templateArg);
    inline const std::vector<TypeSymbol*>& TemplateArgs() const noexcept { return templateArgs; }
private:
    FunctionGroupSymbol* functionGroupSymbol;
    std::vector<TypeSymbol*> templateArgs;
};

class BoundClassGroupNode : public BoundExpressionNode
{
public:
    BoundClassGroupNode(ClassGroupSymbol* classGroupSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    inline ClassGroupSymbol* GetClassGroupSymbol() const noexcept { return classGroupSymbol; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    void AddTemplateArg(TypeSymbol* templateArg);
    inline const std::vector<TypeSymbol*>& TemplateArgs() const noexcept { return templateArgs; }
private:
    ClassGroupSymbol* classGroupSymbol;
    std::vector<TypeSymbol*> templateArgs;
};

class BoundAliasGroupNode : public BoundExpressionNode
{
public:
    BoundAliasGroupNode(AliasGroupSymbol* aliasGroupSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    inline AliasGroupSymbol* GetAliasGroupSymbol() const noexcept { return aliasGroupSymbol; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    void AddTemplateArg(TypeSymbol* templateArg);
    inline const std::vector<TypeSymbol*>& TemplateArgs() const noexcept { return templateArgs; }
private:
    AliasGroupSymbol* aliasGroupSymbol;
    std::vector<TypeSymbol*> templateArgs;
};

class BoundTypeNode : public BoundExpressionNode
{
public:
    BoundTypeNode(TypeSymbol* type_, const soul::ast::SourcePos& sourcePos_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
};

class BoundMemberExprNode : public BoundExpressionNode
{
public:
    BoundMemberExprNode(BoundExpressionNode* subject_, BoundExpressionNode* member_, otava::ast::NodeKind op_, const soul::ast::SourcePos& sourcePos_,
        TypeSymbol* type_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    inline BoundExpressionNode* Subject() const noexcept { return subject.get(); }
    inline BoundExpressionNode* Member() const noexcept { return member.get(); }
    inline otava::ast::NodeKind Op() const noexcept { return op; }
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
    BoundFunctionCallNode(FunctionSymbol* functionSymbol_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    bool HasValue() const noexcept override;
    inline FunctionSymbol* GetFunctionSymbol() const noexcept { return functionSymbol; }
    void AddArgument(BoundExpressionNode* arg);
    inline const std::vector<std::unique_ptr<BoundExpressionNode>>& Args() const noexcept { return args; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsLvalueExpression() const noexcept override;
    BoundExpressionNode* Clone() const override;
    bool CallsClassConstructor(ClassTypeSymbol*& cls, BoundExpressionNode*& firstArg, FunctionDefinitionSymbol*& destructor) const noexcept;
    bool IsNoReturnFunctionCall() const noexcept override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    FunctionSymbol* functionSymbol;
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
};

class BoundEmptyFunctionCallNode : public BoundExpressionNode
{
public:
    BoundEmptyFunctionCallNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
};

class BoundFunctionPtrCallNode : public BoundExpressionNode
{
public:
    BoundFunctionPtrCallNode(const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    bool HasValue() const noexcept override { return true; }
    void AddArgument(BoundExpressionNode* arg);
    inline const std::vector<std::unique_ptr<BoundExpressionNode>>& Args() const noexcept { return args; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::vector<std::unique_ptr<BoundExpressionNode>> args;
};

class BoundExpressionSequenceNode : public BoundExpressionNode
{
public:
    BoundExpressionSequenceNode(const soul::ast::SourcePos& sourcePos_, BoundExpressionNode* left_, BoundExpressionNode* right_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    bool HasValue() const noexcept override;
    bool IsLvalueExpression() const noexcept override;
    BoundExpressionNode* Clone() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline BoundExpressionNode* Left() const noexcept { return left.get(); }
    inline BoundExpressionNode* Right() const noexcept { return right.get(); }
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> left;
    std::unique_ptr<BoundExpressionNode> right;
};

class BoundExpressionListNode : public BoundExpressionNode
{
public:
    BoundExpressionListNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
    void AddExpression(BoundExpressionNode* expr);
    inline int Count() const noexcept { return exprs.size(); }
    inline const std::vector<std::unique_ptr<BoundExpressionNode>>& Exprs() const noexcept { return exprs; }
    inline BoundExpressionNode* ReleaseExpr(int i) noexcept { return exprs[i].release(); }
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::vector<std::unique_ptr<BoundExpressionNode>> exprs;
};

class BoundConjunctionNode : public BoundExpressionNode
{
public:
    BoundConjunctionNode(BoundExpressionNode* left_, BoundExpressionNode* right_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* boolType) noexcept;
    inline BoundExpressionNode* Left() const noexcept { return left.get(); }
    inline BoundExpressionNode* Right() const noexcept { return right.get(); }
    void SetTemporary(BoundVariableNode* temporary_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    bool HasValue() const noexcept override;
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
    BoundDisjunctionNode(BoundExpressionNode* left_, BoundExpressionNode* right_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* boolType) noexcept;
    inline BoundExpressionNode* Left() const noexcept { return left.get(); }
    inline BoundExpressionNode* Right() const noexcept { return right.get(); }
    void SetTemporary(BoundVariableNode* temporary_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    bool HasValue() const noexcept override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> left;
    std::unique_ptr<BoundExpressionNode> right;
    std::unique_ptr<BoundVariableNode> temporary;
};

class BoundConditionalExprNode : public BoundExpressionNode
{
public:
    BoundConditionalExprNode(BoundExpressionNode* condition_, BoundExpressionNode* thenExpr_, BoundExpressionNode* elseExpr_, TypeSymbol* type_) noexcept;
    void SetTemporary(BoundVariableNode* temporary_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    bool HasValue() const noexcept override { return true; }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> condition;
    std::unique_ptr<BoundExpressionNode> thenExpr;
    std::unique_ptr<BoundExpressionNode> elseExpr;
    std::unique_ptr<BoundVariableNode> temporary;
};

class BoundConversionNode : public BoundExpressionNode
{
public:
    BoundConversionNode(BoundExpressionNode* subject_, FunctionSymbol* conversionFunction_, const soul::ast::SourcePos& sourcePos_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsLvalueExpression() const noexcept override;
    inline BoundExpressionNode* Subject() const noexcept { return subject.get(); }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
    FunctionSymbol* conversionFunction;
};

class BoundAddressOfNode : public BoundExpressionNode
{
public:
    BoundAddressOfNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline BoundExpressionNode* Subject() noexcept { return subject.get(); }
    inline BoundExpressionNode* ReleaseSubject() noexcept { return subject.release(); }
    inline void ResetSubject(BoundExpressionNode* newSubject) noexcept { subject.reset(newSubject); }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
};

class BoundDereferenceNode : public BoundExpressionNode
{
public:
    BoundDereferenceNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    BoundDereferenceNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_, OperationFlags kind_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsLvalueExpression() const noexcept override { return true; }
    inline BoundExpressionNode* Subject() noexcept { return subject.get(); }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    OperationFlags kind;
    std::unique_ptr<BoundExpressionNode> subject;
};

class BoundRefToPtrNode : public BoundExpressionNode
{
public:
    BoundRefToPtrNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
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
    BoundPtrToRefNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    BoundExpressionNode* Clone() const override;
    inline BoundExpressionNode* Subject() const noexcept { return subject.get(); }
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> subject;
};

class BoundDefaultInitNode : public BoundExpressionNode
{
public:
    BoundDefaultInitNode(BoundExpressionNode* subject_, const soul::ast::SourcePos& sourcePos_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
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
    BoundTemporaryNode(BoundExpressionNode* rvalueExpr_, BoundVariableNode* backingStore_, const soul::ast::SourcePos& sourcePos_) noexcept;
    inline BoundExpressionNode* RvalueExpr() noexcept { return rvalueExpr.get(); }
    inline BoundVariableNode* BackingStore() noexcept { return backingStore.get(); }
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    bool HasValue() const noexcept override { return true; }
    bool IsLvalueExpression() const noexcept override { return true; }
    BoundExpressionNode* Clone() const override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> rvalueExpr;
    std::unique_ptr<BoundVariableNode> backingStore;
};

class BoundConstructTemporaryNode : public BoundExpressionNode
{
public:
    BoundConstructTemporaryNode(BoundExpressionNode* constructorCall_, BoundExpressionNode* temporary_, const soul::ast::SourcePos& sourcePos_) noexcept;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    bool HasValue() const noexcept override { return true; }
    bool IsLvalueExpression() const noexcept override { return true; }
    inline BoundExpressionNode* ConstructorCall() const noexcept { return constructorCall.get(); }
    inline BoundExpressionNode* Temporary() const noexcept { return temporary.get(); }
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
        const soul::ast::SourcePos& sourcePos_) noexcept;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void Accept(BoundTreeVisitor& visitor) override;
    bool MayThrow() const noexcept override;
    bool HasValue() const noexcept override { return !hasPlacement; }
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
    BoundGlobalVariableDefinitionNode(VariableSymbol* globalVariable_, const soul::ast::SourcePos& sourcePos_) noexcept;
    VariableSymbol* GetGlobalVariable() const noexcept { return globalVariable; }
    void Accept(BoundTreeVisitor& visitor) override;
private:
    VariableSymbol* globalVariable;
};

class BoundEmptyDestructorNode : public BoundExpressionNode
{
public:
    BoundEmptyDestructorNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
};

class BoundFunctionValueNode : public BoundExpressionNode
{
public:
    BoundFunctionValueNode(FunctionSymbol* function_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    FunctionSymbol* function;
};

class BoundVariableAsVoidPtrNode : public BoundExpressionNode
{
public:
    BoundVariableAsVoidPtrNode(BoundExpressionNode* addrOfBoundVariable_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
    void Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context) override;
    void ModifyTypes(const soul::ast::SourcePos& sourcePos, Context* context) override;
private:
    std::unique_ptr<BoundExpressionNode> addrOfBoundVariable;
};

class BoundOperatorFnNode : public BoundExpressionNode
{
public:
    BoundOperatorFnNode(otava::ast::NodeKind operatorFnNodeKind_, const soul::ast::SourcePos& sourcePos_) noexcept;
    void Accept(BoundTreeVisitor& visitor) override;
    BoundExpressionNode* Clone() const override;
    inline otava::ast::NodeKind OperatorFnNodeKind() const { return operatorFnNodeKind; }
private:
    otava::ast::NodeKind operatorFnNodeKind;
};

bool InDirectSwitchStatement(BoundStatementNode* statement);

} // namespace otava::symbols
