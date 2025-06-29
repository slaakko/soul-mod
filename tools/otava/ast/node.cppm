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
    assignNode, plusAssignNode, minusAssignNode, mulAssignNode, divAssignNode, modAssignNode, xorAssignNode, andAssignNode, orAssignNode, shiftLeftAssignNode, shiftRightAssignNode,
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
    labeledStatementNode, caseStatmentNode, defaultStatementNode, compoundStatementNode, ifStatementNode, switchStatemeNode, whileStatementNode, doStatementNode,
    rangeForStatementNode, forRangeDeclarationNode, structuredBindingNode, forStatementNode, breakStatementNode, continueStatementNode, returnStatementNode, coReturnStatementNode,
    gotoStatementNode, tryStatementNode, handlerSequenceNode, handlerNode, exceptionDeclarationNode, expressionStatementNode, declarationStatementNode, initConditionNode, 
    semicolonNode,
    templateDeclarationNode, templateHeadNode, templateParameterListNode, typeParameterNode, templateIdNode, typenameNode, deductionGuideNode, explicitInstantiationNode, 
    explicitSpecializationNode,
    declarationSequenceNode, simpleDeclarationNode, usingDeclarationNode, usingNode, usingDeclaratorListNode, usingEnumDeclarationNode, emptyDeclarationNode, namespaceNode, 
    usingDirectiveNode,
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
    attributeSpecifierSequenceNode, attributeSpecifierNode, attributeUsingPrefixNode, attrbuteNode, attributeScopedTokenNode, attributeArgumentsNode, balancedTokenSequenceNode, 
    tokenNode,
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
    NodeKind Kind() const { return kind; }
    void SetId(std::int64_t id_) { id = id_; }
    virtual std::u32string Str() const { return std::u32string(); }
    virtual NodeType Type() const { return NodeType::single; }
    virtual int Count() const { return 0; }
    const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
    void SetSourcePos(const soul::ast::SourcePos& sourcePos_) { sourcePos = sourcePos_; }
    virtual void Accept(Visitor& visitor) = 0;
    virtual void Write(Writer& writer);
    virtual void Read(Reader& reader);
    virtual void AddNode(Node* node);
    virtual void Clear();
    Node* Parent() const { return parent; }
    void SetParent(Node* parent_) { parent = parent_; }
    std::int64_t Id() const { return id & ~internallyMappedFlag; }
    bool IsInternallyMapped() const { return (id & internallyMappedFlag) != 0; }
    bool IsImportDeclarationNode() const { return kind == NodeKind::importDeclarationNode; }
    bool IsClassNode() const { return kind == NodeKind::classNode; }
    bool IsStructNode() const { return kind == NodeKind::structNode;  }
    bool IsUnionNode() const { return kind == NodeKind::unionNode; }
    bool IsClassSpecifierNode() const { return kind == NodeKind::classSpecifierNode; }
    bool IsCompoundStatementNode() const { return kind == NodeKind::compoundStatementNode; }
    bool IsCtorInitializerNode() const { return kind == NodeKind::constructorInitializerNode; }
    bool IsFunctionBodyNode() const { return kind == NodeKind::functionBodyNode; }
    bool IsConstructorNode() const { return kind == NodeKind::constructorNode; }
    bool IsIdentifierNode() const { return kind == NodeKind::identifierNode; }
    bool IsQualifiedIdNode() const { return kind == NodeKind::qualifiedIdNode; }
    bool IsArrowNode() const { return kind == NodeKind::arrowNode; }
    bool IsDotNode() const { return kind == NodeKind::dotNode; }
    bool IsBinaryExprNode() const { return kind == NodeKind::binaryExprNode; }
    bool IsDefaultedOrDeletedFunctionNode() const { return kind == NodeKind::defaultedOrDeletedFunctionNode; } 
    bool IsStringLiteralNode() const { return kind == NodeKind::stringLiteralNode; }
    bool IsFunctionDefinitionNode() const { return kind == NodeKind::functionDefinitionNode; }
    bool IsNewPlacementNode() const { return kind == NodeKind::newPlacementNode; }
    bool IsCommaNode() const { return kind == NodeKind::commaNode; }
    bool IsStaticNode() const { return kind == NodeKind::staticNode; }
    bool IsBoundStatementNode() const { return kind == NodeKind::boundStatementNode; }
    bool IsInitDeclaratorNode() const { return kind == NodeKind::initDeclaratorNode; }
    bool IsAliasDeclarationNode() const { return kind == NodeKind::aliasDeclarationNode; }
    bool IsLBraceNode() const { return kind == NodeKind::lbraceNode; }
    bool IsRBraceNode() const { return kind == NodeKind::rbraceNode; }
    bool IsFunctionDeclaratorNode() const { return kind == NodeKind::functionDeclaratorNode; }
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
    Node* Child() const { return child.get(); }
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
    Node* Left() const { return left.get(); }
    Node* Right() const { return right.get(); }
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
    void Clear() override;
    NodeList<Node>& Nodes() { return nodes; }
    const NodeList<Node>& Nodes() const { return nodes; }
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
    NodeList<Node>& Nodes() { return nodes; }
    const NodeList<Node>& Nodes() const { return nodes; }
    const std::vector<Node*>& Items() const { return items; }
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
    void SetModuleId(std::int32_t moduleId_) { moduleId = moduleId_; }
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
