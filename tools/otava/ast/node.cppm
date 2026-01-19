// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.node;

import std;
import soul.ast.source.pos;
import otava.ast.node.list;

export namespace otava::ast {

class Node;
class Visitor;
class Writer;
class Reader;

enum class NodeType
{
    single, compound, unary, binary, sequence, list
};

std::string NodeTypeStr(NodeType nodeType);

using NodeDestroyedFunc = void(*)(Node*);

void SetNodeDestroyedFunc(NodeDestroyedFunc func);

constexpr std::int32_t internallyMappedFlag = 0x40000000;
constexpr std::int32_t destructorNodeId = 0x20000000;

enum class NodeKind : std::uint16_t
{
    nullNode,
    translationUnitNode, moduleUnitNode,
    moduleDeclarationNode, exportDeclarationNode, exportNode, importNode, importDeclarationNode, modulePartitionNode, moduleNode, globalModuleFragmentNode, 
    privateModuleFragmentNode, angleHeaderNameNode, quoteHeaderNameNode,
    identifierNode, unnamedNode, colonColonNode, nestedNameSpecifierNode, qualifiedIdNode, identifierListNode, moduleNameNode,
    charNode, char8Node, char16Node, char32Node, wcharNode, boolNode, shortNode, intNode, longNode, signedNode, unsignedNode, floatNode, doubleNode, voidNode,
    constNode, volatileNode, lvalueRefNode, rvalueRefNode, ptrNode, cvQualifierSequenceNode, ptrOperatorNode, noexceptSpecifierNode, throwSpecifierNode, 
    packDeclaratorIdNode, arrayDeclaratorNode, functionDeclaratorNode, prefixNode, trailingQualifiersNode, trailingAttributesNode, ptrDeclaratorNode,
    expressionListNode, assignmentInitializerNode,
    conditionalExprNode, questNode, colonNode, commaNode, binaryExprNode, unaryExprNode, yieldExprNode, throwExprNode,
    assignNode, plusAssignNode, minusAssignNode, mulAssignNode, divAssignNode, modAssignNode, xorAssignNode, andAssignNode, orAssignNode, 
    shiftLeftAssignNode, shiftRightAssignNode,
    disjunctionNode, conjunctionNode, inclusiveOrNode, exclusiveOrNode, andNode, equalNode, notEqualNode, lessNode, greaterNode, lessOrEqualNode, greaterOrEqualNode,
    compareNode, shiftLeftNode, shiftRightNode, plusNode, minusNode, mulNode, divNode, modNode, dotStarNode, arrowStarNode,
    castExprNode, derefNode, addrOfNode, notNode, complementNode, prefixIncNode, prefixDecNode,
    awaitExprNode, sizeOfTypeExprNode, sizeOfPackExpNode, sizeOfUnaryExprNode, alignOfExprNode, noexceptExprNode,
    foldExprNode, newDeclaratorNode, arrayNewDeclaratorNode, newInitializerNode, ellipsisNode, bracedInitListNode, designatedInitializerNode, designatorNode,
    newExprNode, newPlacementNode, parenNewTypeIdNode, newTypeIdNode, arrayDeletePtrNode, deletePtrNode,
    subscriptExprNode, invokeExprNode, dotNode, templateNode, arrowNode, pairNode, memberExprNode, postfixIncExprNode, postfixDecExprNode, typeIdExprNode,
    dynamicCastNode, staticCastNode, reinterpretCastNode, constCastNode, cppCastExprNode, thisNode, parenExprNode,
    lambdaExpressionNode, lambdaIntroducerNode, lambdaCaptureNode, lambdaDeclaratorNode, lambdaSpecifiersNode, lambdaTemplateParamsNode,
    defaultRefCaptureNode, defaultCopyCaptureNode, byRefCaptureNode, simpleCaptureNode, initCaptureNode, currentObjectCopyCapture, currentObjectByRefCapture,
    integerLiteralNode, floatingLiteralNode, characterLiteralNode, stringLiteralNode, rawStringLiteralNode, booleanLiteralNode, nullPtrLiteralNode, 
    userDefinedLiteralNode, literalOperatorIdNode,
    labeledStatementNode, caseStatmentNode, defaultStatementNode, compoundStatementNode, sequenceStatementNode, ifStatementNode, switchStatemeNode, 
    whileStatementNode, doStatementNode, rangeForStatementNode, forRangeDeclarationNode, structuredBindingNode, forStatementNode, 
    breakStatementNode, continueStatementNode, returnStatementNode, coReturnStatementNode,
    gotoStatementNode, tryStatementNode, handlerSequenceNode, handlerNode, exceptionDeclarationNode, expressionStatementNode, declarationStatementNode, initConditionNode, 
    semicolonNode,
    templateDeclarationNode, templateHeadNode, templateParameterListNode, typeParameterNode, templateIdNode, typenameNode, deductionGuideNode, explicitInstantiationNode, 
    explicitSpecializationNode,
    declarationSequenceNode, simpleDeclarationNode, usingDeclarationNode, usingNode, usingDeclaratorListNode, usingEnumDeclarationNode, 
    emptyDeclarationNode, namespaceNode, usingDirectiveNode,
    asmDeclarationNode, asmNode, namespaceAliasDefinitionNode, staticAssertDeclarationNode, staticAssertNode, aliasDeclarationNode, definingTypeIdNode, 
    definingTypeSpecifierSequenceNode,
    opaqueEnumDeclarationNode, noDeclSpecFunctionDeclarationNode, linkageSpecificationNode, namespaceDefinitionNode, namespaceBodyNode, attributeDeclarationNode,
    initDeclaratorListNode, initDeclaratorNode, trailingFunctionDeclaratorNode, parenthesizedDeclaratorNode, abstractDeclaratorNode, declSpecifierSequenceNode,
    friendNode, typedefNode, constExprNode, constEvalNode, constInitNode, inlineNode, staticNode, threadLocalNode, externNode, mutableNode, virtualNode, explicitNode, 
    conditionalExplicitNode,
    qualifiedPtrNode,
    typeSpecifierSequenceNode, typenameSpecifierNode, typeIdNode, trailingReturnTypeNode, elaboratedTypeSpecifierNode, declTypeSpecifierNode, placeholderTypeSpecifierNode,
    classSpecifierNode, classHeadNode, baseClauseNode, baseSpecifierListNode, baseSpecifierNode, beginAccessGroupNode, memberDeclarationNode, memberDeclaratorListNode, 
    virtSpecifierSequenceNode,
    constructorNode, constructorInitializerNode, memberInitializerListNode, memberInitializerNode,
    publicNode, protectedNode, privateNode, classNode, structNode, unionNode, overrideNode, finalNode, pureSpecifierNode,
    enumSpecifierNode, enumHeadNode, enumBaseNode, enumClassNode, enumStructNode, enumNode, enumeratorDefinitionNode, enumeratorNode, elaboratedEnumSpecifierNode,
    functionDefinitionNode, functionBodyNode, defaultedOrDeletedFunctionNode, defaultNode, deleteNode,
    operatorFnIdNode, operatorNode, newArrayOpNode, newOpNode, deleteArrayOpNode, deleteOpNode, coAwaitOpNode, invokeOpNode, subscriptOpNode,
    conversionFnIdNode, conversionTypeIdNode, conversionDeclaratorNode, destructorIdNode, parameterNode, parameterListNode, noexceptNode, functionTryBlock,
    conceptDefinitionNode, requiresExprNode, requirementBodyNode, simpleRequirementNode, typeRequirementNode, compoundRequirementNode, returnTypeRequirementNode, 
    nestedRequirementNode,
    typeConstraintNode, requiresClauseNode,
    attributeSpecifierSequenceNode, attributeSpecifierNode, attributeUsingPrefixNode, attrbuteNode, attributeScopedTokenNode, 
    attributeArgumentsNode, balancedTokenSequenceNode, tokenNode,
    lparenNode, rparenNode, lbracketNode, rbracketNode, lbraceNode, rbraceNode, alignmentSpecifierNode,
    pragmaNode, boundStatementNode,
    max
};

std::string NodeKindStr(NodeKind nodeKind);

class Node
{
public:
    Node(NodeKind kind_, const soul::ast::SourcePos& sourcePos_);
    virtual ~Node();
    virtual Node* Clone() const = 0;
    inline NodeKind Kind() const { return kind; }
    inline void SetId(std::int64_t id_) { id = id_; }
    virtual std::u32string Str() const { return std::u32string(); }
    virtual NodeType Type() const { return NodeType::single; }
    virtual int Count() const { return 0; }
    inline const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
    inline void SetSourcePos(const soul::ast::SourcePos& sourcePos_) { sourcePos = sourcePos_; }
    virtual void Accept(Visitor& visitor) = 0;
    virtual void Write(Writer& writer);
    virtual void Read(Reader& reader);
    virtual void AddNode(Node* node);
    virtual void Clear();
    inline Node* Parent() const { return parent; }
    inline void SetParent(Node* parent_) { parent = parent_; }
    inline std::int32_t NodeId() const { return id & 0xFFFFFFFF; }
    inline std::int64_t InternalId() const { return id & ~internallyMappedFlag; }
    inline bool IsInternallyMapped() const { return (id & internallyMappedFlag) != 0; }
    inline bool IsImportDeclarationNode() const { return kind == NodeKind::importDeclarationNode; }
    inline bool IsClassNode() const { return kind == NodeKind::classNode; }
    inline bool IsStructNode() const { return kind == NodeKind::structNode;  }
    inline bool IsUnionNode() const { return kind == NodeKind::unionNode; }
    inline bool IsClassSpecifierNode() const { return kind == NodeKind::classSpecifierNode; }
    inline bool IsCompoundStatementNode() const { return kind == NodeKind::compoundStatementNode; }
    inline bool IsSequenceStatemetnNode() const { return kind == NodeKind::sequenceStatementNode; }
    inline bool IsReturnStatementNode() const { return kind == NodeKind::returnStatementNode; }
    inline bool IsInitConditionNode() const { return kind == NodeKind::initConditionNode; }
    inline bool IsCtorInitializerNode() const { return kind == NodeKind::constructorInitializerNode; }
    inline bool IsFunctionBodyNode() const { return kind == NodeKind::functionBodyNode; }
    inline bool IsConstructorNode() const { return kind == NodeKind::constructorNode; }
    inline bool IsEnumeratorNode() const { return kind == NodeKind::enumeratorNode; }
    inline bool IsIdentifierNode() const { return kind == NodeKind::identifierNode; }
    inline bool IsQualifiedIdNode() const { return kind == NodeKind::qualifiedIdNode; }
    inline bool IsTemplateIdNode() const { return kind == NodeKind::templateIdNode; }
    inline bool IsArrowNode() const { return kind == NodeKind::arrowNode; }
    inline bool IsDotNode() const { return kind == NodeKind::dotNode; }
    inline bool IsInvokeExprNode() const { return kind == NodeKind::invokeExprNode; }
    inline bool IsMemberExprNode() const { return kind == NodeKind::memberExprNode; }
    inline bool IsBinaryExprNode() const { return kind == NodeKind::binaryExprNode; }
    inline bool IsDefaultedOrDeletedFunctionNode() const { return kind == NodeKind::defaultedOrDeletedFunctionNode; }
    inline bool IsStringLiteralNode() const { return kind == NodeKind::stringLiteralNode; }
    inline bool IsFunctionDefinitionNode() const { return kind == NodeKind::functionDefinitionNode; }
    inline bool IsNewPlacementNode() const { return kind == NodeKind::newPlacementNode; }
    inline bool IsCommaNode() const { return kind == NodeKind::commaNode; }
    inline bool IsStaticNode() const { return kind == NodeKind::staticNode; }
    inline bool IsBoundStatementNode() const { return kind == NodeKind::boundStatementNode; }
    inline bool IsInitDeclaratorNode() const { return kind == NodeKind::initDeclaratorNode; }
    inline bool IsAliasDeclarationNode() const { return kind == NodeKind::aliasDeclarationNode; }
    inline bool IsLBraceNode() const { return kind == NodeKind::lbraceNode; }
    inline bool IsRBraceNode() const { return kind == NodeKind::rbraceNode; }
    inline bool IsFunctionDeclaratorNode() const { return kind == NodeKind::functionDeclaratorNode; }
    inline bool IsTypenameSpecifierNode() const { return kind == NodeKind::typenameSpecifierNode; }
    inline bool IsConstNode() const { return kind == NodeKind::constNode; }
    inline bool IsLvalueRefNode() const { return kind == NodeKind::lvalueRefNode; }
    inline bool IsRvalueRefNode() const { return kind == NodeKind::rvalueRefNode; }
    inline bool IsPtrNode() const { return kind == NodeKind::ptrNode; }
private:
    NodeKind kind;
    soul::ast::SourcePos sourcePos;
    Node* parent;
    std::int64_t id;
};

class CompoundNode : public Node
{
public:
    CompoundNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_);
    NodeType Type() const override { return NodeType::compound; }
};

class UnaryNode : public Node
{
public:
    UnaryNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, Node* child_);
    UnaryNode(const UnaryNode&) = delete;
    UnaryNode& operator=(const UnaryNode&) = delete;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    NodeType Type() const override { return NodeType::unary; }
    int Count() const override { return 1; }
    inline Node* Child() const { return child.get(); }
    std::u32string Str() const override;
private:
    std::unique_ptr<Node> child;
};

class BinaryNode : public Node
{
public:
    BinaryNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, Node* left_, Node* right_);
    BinaryNode(const BinaryNode&) = delete;
    BinaryNode& operator=(const BinaryNode&) = delete;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    NodeType Type() const override { return NodeType::binary; }
    int Count() const override { return 2; }
    inline Node* Left() const { return left.get(); }
    inline Node* Right() const { return right.get(); }
    std::u32string Str() const override;
private:
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

class SequenceNode : public Node
{
public:
    SequenceNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    NodeType Type() const override { return NodeType::sequence; }
    int Count() const override { return nodes.Count(); }
    void AddNode(Node* node) override;
    void InsertNode(int index, Node* node);
    void Clear() override;
    inline NodeList<Node>& Nodes() { return nodes; }
    inline const NodeList<Node>& Nodes() const { return nodes; }
    std::u32string Str() const override;
private:
    NodeList<Node> nodes;
};

class ListNode : public Node
{
public:
    ListNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    NodeType Type() const override { return NodeType::list; }
    int Count() const override { return nodes.Count(); }
    void AddNode(Node* node) override;
    void Clear() override;
    inline NodeList<Node>& Nodes() { return nodes; }
    inline const NodeList<Node>& Nodes() const { return nodes; }
    inline const std::vector<Node*>& Items() const { return items; }
    std::u32string Str() const override;
private:
    NodeList<Node> nodes;
    std::vector<Node*> items;
};

class NodeIdFactory
{
public:
    NodeIdFactory();
    void SetInternallyMapped(bool internallyMapped_);
    bool IsInternallyMapped() const;
    inline void SetModuleId(std::int32_t moduleId_) { moduleId = moduleId_; }
    std::int64_t GetNextNodeId();
private:
    std::int32_t moduleId;
    std::int32_t nodeId;
    std::int32_t internallyMappedBit;
};

void MakeNodeFactoryCollection();
void SetNodeIdFactory(NodeIdFactory* factory);
Node* CreateNode(NodeKind nodeKind, const soul::ast::SourcePos& sourcePos);
std::int64_t GetNextNodeId();

} // namespace otava::ast
