// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.node;

import otava.ast.attribute;
import otava.ast.classes;
import otava.ast.concepts;
import otava.ast.declaration;
import otava.ast.enums;
import otava.ast.expression;
import otava.ast.function;
import otava.ast.identifier;
import otava.ast.lambda;
import otava.ast.literal;
import otava.ast.modules;
import otava.ast.node.list;
import otava.ast.punctuation;
import otava.ast.reader;
import otava.ast.qualifier;
import otava.ast.simple.type;
import otava.ast.statement;
import otava.ast.templates;
import otava.ast.translation.unit;
import otava.ast.type;
import otava.ast.util;
import otava.ast.visitor;
import otava.ast.writer;

namespace otava::ast {

NodeDestroyedFunc nodeDestroyedFunc = nullptr;

void SetNodeDestroyedFunc(NodeDestroyedFunc func)
{
    nodeDestroyedFunc = func;
}

std::string NodeTypeStr(NodeType nodeType)
{
    switch (nodeType)
    {
        case NodeType::compound: return "compound";
        case NodeType::unary: return "unary";
        case NodeType::binary: return "binary";
        case NodeType::sequence: return "sequence";
        case NodeType::list: return "list";
    }
    return "single";
}

std::string NodeKindStr(NodeKind nodeKind)
{
    switch (nodeKind)
    {
        case NodeKind::nullNode: return "nullNode";
        case NodeKind::translationUnitNode: return "translationUnitNode";
        case NodeKind::moduleUnitNode: return "moduleUnitNode";
        case NodeKind::moduleDeclarationNode: return "moduleDeclarationNode";
        case NodeKind::exportDeclarationNode: return "exportDeclarationNode";
        case NodeKind::exportNode: return "exportNode";
        case NodeKind::importNode: return "importNode";
        case NodeKind::importDeclarationNode: return "importDeclarationNode";
        case NodeKind::modulePartitionNode: return "modulePartitionNode";
        case NodeKind::moduleNode: return "moduleNode";
        case NodeKind::globalModuleFragmentNode: return "globalModuleFragmentNode";
        case NodeKind::privateModuleFragmentNode: return "privateModuleFragmentNode";
        case NodeKind::angleHeaderNameNode: return "angleHeaderNameNode";
        case NodeKind::quoteHeaderNameNode: return "quoteHeaderNameNode";
        case NodeKind::identifierNode: return "identifierNode";
        case NodeKind::unnamedNode: return "unnamedNode";
        case NodeKind::colonColonNode: return "colonColonNode";
        case NodeKind::nestedNameSpecifierNode: return "nestedNameSpecifierNode";
        case NodeKind::qualifiedIdNode: return "qualifiedIdNode";
        case NodeKind::identifierListNode: return "identifierListNode";
        case NodeKind::moduleNameNode: return "moduleNameNode";
        case NodeKind::charNode: return "charNode";
        case NodeKind::char8Node: return "char8Node";
        case NodeKind::char16Node: return "char16Node";
        case NodeKind::char32Node: return "char32Node";
        case NodeKind::wcharNode: return "wcharNode";
        case NodeKind::boolNode: return "boolNode";
        case NodeKind::shortNode: return "shortNode";
        case NodeKind::intNode: return "intNode";
        case NodeKind::longNode: return "longNode";
        case NodeKind::signedNode: return "signedNode";
        case NodeKind::unsignedNode: return "unsignedNode";
        case NodeKind::floatNode: return "floatNode";
        case NodeKind::doubleNode: return "doubleNode";
        case NodeKind::voidNode: return "voidNode";
        case NodeKind::constNode: return "constNode";
        case NodeKind::volatileNode: return "volatileNode";
        case NodeKind::lvalueRefNode: return "lvalueRefNode";
        case NodeKind::rvalueRefNode: return "rvalueRefNode";
        case NodeKind::ptrNode: return "ptrNode";
        case NodeKind::cvQualifierSequenceNode: return "cvQualifierSequenceNode";
        case NodeKind::ptrOperatorNode: return "ptrOperatorNode";
        case NodeKind::noexceptSpecifierNode: return "noexceptSpecifierNode";
        case NodeKind::throwSpecifierNode: return "throwSpecifierNode";
        case NodeKind::packDeclaratorIdNode: return "packDeclaratorIdNode";
        case NodeKind::arrayDeclaratorNode: return "arrayDeclaratorNode";
        case NodeKind::functionDeclaratorNode: return "functionDeclaratorNode";
        case NodeKind::prefixNode: return "prefixNode";
        case NodeKind::trailingQualifiersNode: return "trailingQualifiersNode";
        case NodeKind::trailingAttributesNode: return "trailingAttributesNode";
        case NodeKind::ptrDeclaratorNode: return "ptrDeclaratorNode";
        case NodeKind::expressionListNode: return "expressionListNode";
        case NodeKind::assignmentInitializerNode: return "assignmentInitializerNode";
        case NodeKind::conditionalExprNode: return "conditionalExprNode";
        case NodeKind::questNode: return "questNode";
        case NodeKind::colonNode: return "colonNode";
        case NodeKind::commaNode: return "commaNode";
        case NodeKind::binaryExprNode: return "binaryExprNode";
        case NodeKind::unaryExprNode: return "unaryExprNode";
        case NodeKind::yieldExprNode: return "yieldExprNode";
        case NodeKind::throwExprNode: return "throwExprNode";
        case NodeKind::assignNode: return "assignNode";
        case NodeKind::plusAssignNode: return "plusAssignNode";
        case NodeKind::minusAssignNode: return "minusAssignNode";
        case NodeKind::mulAssignNode: return "mulAssignNode";
        case NodeKind::divAssignNode: return "divAssignNode";
        case NodeKind::modAssignNode: return "modAssignNode";
        case NodeKind::xorAssignNode: return "xorAssignNode";
        case NodeKind::andAssignNode: return "andAssignNode";
        case NodeKind::orAssignNode: return "orAssignNode";
        case NodeKind::shiftLeftAssignNode: return "shiftLeftAssignNode";
        case NodeKind::shiftRightAssignNode: return "shiftRightAssignNode";
        case NodeKind::disjunctionNode: return "disjunctionNode";
        case NodeKind::conjunctionNode: return "conjunctionNode";
        case NodeKind::inclusiveOrNode: return "inclusiveOrNode";
        case NodeKind::exclusiveOrNode: return "exclusiveOrNode";
        case NodeKind::andNode: return "andNode";
        case NodeKind::equalNode: return "equalNode";
        case NodeKind::notEqualNode: return "notEqualNode";
        case NodeKind::lessNode: return "lessNode";
        case NodeKind::greaterNode: return "greaterNode";
        case NodeKind::lessOrEqualNode: return "lessOrEqualNode";
        case NodeKind::greaterOrEqualNode: return "greaterOrEqualNode";
        case NodeKind::compareNode: return "compareNode";
        case NodeKind::shiftLeftNode: return "shiftLeftNode";
        case NodeKind::shiftRightNode: return "shiftRightNode";
        case NodeKind::plusNode: return "plusNode";
        case NodeKind::minusNode: return "minusNode";
        case NodeKind::mulNode: return "mulNode";
        case NodeKind::divNode: return "divNode";
        case NodeKind::modNode: return "modNode";
        case NodeKind::dotStarNode: return "dotStarNode";
        case NodeKind::arrowStarNode: return "arrowStarNode";
        case NodeKind::castExprNode: return "castExprNode";
        case NodeKind::derefNode: return "derefNode";
        case NodeKind::addrOfNode: return "addrOfNode";
        case NodeKind::notNode: return "notNode";
        case NodeKind::complementNode: return "complementNode";
        case NodeKind::prefixIncNode: return "prefixIncNode";
        case NodeKind::prefixDecNode: return "prefixDecNode";
        case NodeKind::awaitExprNode: return "awaitExprNode";
        case NodeKind::sizeOfTypeExprNode: return "sizeOfTypeExprNode";
        case NodeKind::sizeOfPackExpNode: return "sizeOfPackExpNode";
        case NodeKind::sizeOfUnaryExprNode: return "sizeOfUnaryExprNode";
        case NodeKind::alignOfExprNode: return "alignOfExprNode";
        case NodeKind::noexceptExprNode: return "noexceptExprNode";
        case NodeKind::foldExprNode: return "foldExprNode";
        case NodeKind::newDeclaratorNode: return "newDeclaratorNode";
        case NodeKind::arrayNewDeclaratorNode: return "arrayNewDeclaratorNode";
        case NodeKind::newInitializerNode: return "newInitializerNode";
        case NodeKind::ellipsisNode: return "ellipsisNode";
        case NodeKind::bracedInitListNode: return "bracedInitListNode";
        case NodeKind::designatedInitializerNode: return "designatedInitializerNode";
        case NodeKind::designatorNode: return "designatorNode";
        case NodeKind::newExprNode: return "newExprNode";
        case NodeKind::newPlacementNode: return "newPlacementNode";
        case NodeKind::parenNewTypeIdNode: return "parenNewTypeIdNode";
        case NodeKind::newTypeIdNode: return "newTypeIdNode";
        case NodeKind::arrayDeletePtrNode: return "arrayDeletePtrNode";
        case NodeKind::deletePtrNode: return "deletePtrNode";
        case NodeKind::subscriptExprNode: return "subscriptExprNode";
        case NodeKind::invokeExprNode: return "invokeExprNode";
        case NodeKind::dotNode: return "dotNode";
        case NodeKind::templateNode: return "templateNode";
        case NodeKind::arrowNode: return "arrowNode";
        case NodeKind::pairNode: return "pairNode";
        case NodeKind::memberExprNode: return "memberExprNode";
        case NodeKind::postfixIncExprNode: return "postfixIncExprNode";
        case NodeKind::postfixDecExprNode: return "postfixDecExprNode";
        case NodeKind::typeIdExprNode: return "typeIdExprNode";
        case NodeKind::dynamicCastNode: return "dynamicCastNode";
        case NodeKind::staticCastNode: return "staticCastNode";
        case NodeKind::reinterpretCastNode: return "reinterpretCastNode";
        case NodeKind::constCastNode: return "constCastNode";
        case NodeKind::cppCastExprNode: return "cppCastExprNode";
        case NodeKind::thisNode: return "thisNode";
        case NodeKind::parenExprNode: return "parenExprNode";
        case NodeKind::lambdaExpressionNode: return "lambdaExpressionNode";
        case NodeKind::lambdaIntroducerNode: return "lambdaIntroducerNode";
        case NodeKind::lambdaCaptureNode: return "lambdaCaptureNode";
        case NodeKind::lambdaDeclaratorNode: return "lambdaDeclaratorNode";
        case NodeKind::lambdaSpecifiersNode: return "lambdaSpecifiersNode";
        case NodeKind::lambdaTemplateParamsNode: return "lambdaTemplateParamsNode";
        case NodeKind::defaultRefCaptureNode: return "defaultRefCaptureNode";
        case NodeKind::defaultCopyCaptureNode: return "defaultCopyCaptureNode";
        case NodeKind::byRefCaptureNode: return "byRefCaptureNode";
        case NodeKind::simpleCaptureNode: return "simpleCaptureNode";
        case NodeKind::initCaptureNode: return "initCaptureNode";
        case NodeKind::currentObjectCopyCapture: return "currentObjectCopyCapture";
        case NodeKind::currentObjectByRefCapture: return "currentObjectByRefCapture";
        case NodeKind::integerLiteralNode: return "integerLiteralNode";
        case NodeKind::floatingLiteralNode: return "floatingLiteralNode";
        case NodeKind::characterLiteralNode: return "characterLiteralNode";
        case NodeKind::stringLiteralNode: return "stringLiteralNode";
        case NodeKind::rawStringLiteralNode: return "rawStringLiteralNode";
        case NodeKind::booleanLiteralNode: return "booleanLiteralNode";
        case NodeKind::nullPtrLiteralNode: return "nullPtrLiteralNode";
        case NodeKind::userDefinedLiteralNode: return "userDefinedLiteralNode";
        case NodeKind::literalOperatorIdNode: return "literalOperatorIdNode";
        case NodeKind::labeledStatementNode: return "labeledStatementNode";
        case NodeKind::caseStatmentNode: return "caseStatmentNode";
        case NodeKind::defaultStatementNode: return "defaultStatementNode";
        case NodeKind::compoundStatementNode: return "compoundStatementNode";
        case NodeKind::ifStatementNode: return "ifStatementNode";
        case NodeKind::switchStatemeNode: return "switchStatemeNode";
        case NodeKind::whileStatementNode: return "whileStatementNode";
        case NodeKind::doStatementNode: return "doStatementNode";
        case NodeKind::rangeForStatementNode: return "rangeForStatementNode";
        case NodeKind::forRangeDeclarationNode: return "forRangeDeclarationNode";
        case NodeKind::structuredBindingNode: return "structuredBindingNode";
        case NodeKind::forStatementNode: return "forStatementNode";
        case NodeKind::breakStatementNode: return "breakStatementNode";
        case NodeKind::continueStatementNode: return "continueStatementNode";
        case NodeKind::returnStatementNode: return "returnStatementNode";
        case NodeKind::coReturnStatementNode: return "coReturnStatementNode";
        case NodeKind::gotoStatementNode: return "gotoStatementNode";
        case NodeKind::tryStatementNode: return "tryStatementNode";
        case NodeKind::handlerSequenceNode: return "handlerSequenceNode";
        case NodeKind::handlerNode: return "handlerNode";
        case NodeKind::exceptionDeclarationNode: return "exceptionDeclarationNode";
        case NodeKind::expressionStatementNode: return "expressionStatementNode";
        case NodeKind::declarationStatementNode: return "declarationStatementNode";
        case NodeKind::initConditionNode: return "initConditionNode";
        case NodeKind::semicolonNode: return "semicolonNode";
        case NodeKind::templateDeclarationNode: return "templateDeclarationNode";
        case NodeKind::templateHeadNode: return "templateHeadNode";
        case NodeKind::templateParameterListNode: return "templateParameterListNode";
        case NodeKind::typeParameterNode: return "typeParameterNode";
        case NodeKind::templateIdNode: return "templateIdNode";
        case NodeKind::typenameNode: return "typenameNode";
        case NodeKind::deductionGuideNode: return "deductionGuideNode";
        case NodeKind::explicitInstantiationNode: return "explicitInstantiationNode";
        case NodeKind::explicitSpecializationNode: return "explicitSpecializationNode";
        case NodeKind::declarationSequenceNode: return "declarationSequenceNode";
        case NodeKind::simpleDeclarationNode: return "simpleDeclarationNode";
        case NodeKind::usingDeclarationNode: return "usingDeclarationNode";
        case NodeKind::usingNode: return "usingNode";
        case NodeKind::usingDeclaratorListNode: return "usingDeclaratorListNode";
        case NodeKind::usingEnumDeclarationNode: return "usingEnumDeclarationNode";
        case NodeKind::emptyDeclarationNode: return "emptyDeclarationNode";
        case NodeKind::namespaceNode: return "namespaceNode";
        case NodeKind::usingDirectiveNode: return "usingDirectiveNode";
        case NodeKind::asmDeclarationNode: return "asmDeclarationNode";
        case NodeKind::asmNode: return "asmNode";
        case NodeKind::namespaceAliasDefinitionNode: return "namespaceAliasDefinitionNode";
        case NodeKind::staticAssertDeclarationNode: return "staticAssertDeclarationNode";
        case NodeKind::staticAssertNode: return "staticAssertNode";
        case NodeKind::aliasDeclarationNode: return "aliasDeclarationNode";
        case NodeKind::definingTypeIdNode: return "definingTypeIdNode";
        case NodeKind::definingTypeSpecifierSequenceNode: return "definingTypeSpecifierSequenceNode";
        case NodeKind::opaqueEnumDeclarationNode: return "opaqueEnumDeclarationNode";
        case NodeKind::noDeclSpecFunctionDeclarationNode: return "noDeclSpecFunctionDeclarationNode";
        case NodeKind::linkageSpecificationNode: return "linkageSpecificationNode";
        case NodeKind::namespaceDefinitionNode: return "namespaceDefinitionNode";
        case NodeKind::namespaceBodyNode: return "namespaceBodyNode";
        case NodeKind::attributeDeclarationNode: return "attributeDeclarationNode";
        case NodeKind::initDeclaratorListNode: return "initDeclaratorListNode";
        case NodeKind::initDeclaratorNode: return "initDeclaratorNode";
        case NodeKind::trailingFunctionDeclaratorNode: return "trailingFunctionDeclaratorNode";
        case NodeKind::parenthesizedDeclaratorNode: return "parenthesizedDeclaratorNode";
        case NodeKind::abstractDeclaratorNode: return "abstractDeclaratorNode";
        case NodeKind::declSpecifierSequenceNode: return "declSpecifierSequenceNode";
        case NodeKind::friendNode: return "friendNode";
        case NodeKind::typedefNode: return "typedefNode";
        case NodeKind::constExprNode: return "constExprNode";
        case NodeKind::constEvalNode: return "constEvalNode";
        case NodeKind::constInitNode: return "constInitNode";
        case NodeKind::inlineNode: return "inlineNode";
        case NodeKind::staticNode: return "staticNode";
        case NodeKind::threadLocalNode: return "threadLocalNode";
        case NodeKind::externNode: return "externNode";
        case NodeKind::mutableNode: return "mutableNode";
        case NodeKind::virtualNode: return "virtualNode";
        case NodeKind::explicitNode: return "explicitNode";
        case NodeKind::conditionalExplicitNode: return "conditionalExplicitNode";
        case NodeKind::qualifiedPtrNode: return "qualifiedPtrNode";
        case NodeKind::typeSpecifierSequenceNode: return "typeSpecifierSequenceNode";
        case NodeKind::typenameSpecifierNode: return "typenameSpecifierNode";
        case NodeKind::typeIdNode: return "typeIdNode";
        case NodeKind::trailingReturnTypeNode: return "trailingReturnTypeNode";
        case NodeKind::elaboratedTypeSpecifierNode: return "elaboratedTypeSpecifierNode";
        case NodeKind::declTypeSpecifierNode: return "declTypeSpecifierNode";
        case NodeKind::placeholderTypeSpecifierNode: return "placeholderTypeSpecifierNode";
        case NodeKind::classSpecifierNode: return "classSpecifierNode";
        case NodeKind::classHeadNode: return "classHeadNode";
        case NodeKind::baseClauseNode: return "baseClauseNode";
        case NodeKind::baseSpecifierListNode: return "baseSpecifierListNode";
        case NodeKind::baseSpecifierNode: return "baseSpecifierNode";
        case NodeKind::beginAccessGroupNode: return "beginAccessGroupNode";
        case NodeKind::memberDeclarationNode: return "memberDeclarationNode";
        case NodeKind::memberDeclaratorListNode: return "memberDeclaratorListNode";
        case NodeKind::virtSpecifierSequenceNode: return "virtSpecifierSequenceNode";
        case NodeKind::constructorNode: return "constructorNode";
        case NodeKind::constructorInitializerNode: return "constructorInitializerNode";
        case NodeKind::memberInitializerListNode: return "memberInitializerListNode";
        case NodeKind::memberInitializerNode: return "memberInitializerNode";
        case NodeKind::publicNode: return "publicNode";
        case NodeKind::protectedNode: return "protectedNode";
        case NodeKind::privateNode: return "privateNode";
        case NodeKind::classNode: return "classNode";
        case NodeKind::structNode: return "structNode";
        case NodeKind::unionNode: return "unionNode";
        case NodeKind::overrideNode: return "overrideNode";
        case NodeKind::finalNode: return "finalNode";
        case NodeKind::pureSpecifierNode: return "pureSpecifierNode";
        case NodeKind::enumSpecifierNode: return "enumSpecifierNode";
        case NodeKind::enumHeadNode: return "enumHeadNode";
        case NodeKind::enumBaseNode: return "enumBaseNode";
        case NodeKind::enumClassNode: return "enumClassNode";
        case NodeKind::enumStructNode: return "enumStructNode";
        case NodeKind::enumNode: return "enumNode";
        case NodeKind::enumeratorDefinitionNode: return "enumeratorDefinitionNode";
        case NodeKind::enumeratorNode: return "enumeratorNode";
        case NodeKind::elaboratedEnumSpecifierNode: return "elaboratedEnumSpecifierNode";
        case NodeKind::functionDefinitionNode: return "functionDefinitionNode";
        case NodeKind::functionBodyNode: return "functionBodyNode";
        case NodeKind::defaultedOrDeletedFunctionNode: return "defaultedOrDeletedFunctionNode";
        case NodeKind::defaultNode: return "defaultNode";
        case NodeKind::deleteNode: return "deleteNode";
        case NodeKind::operatorFnIdNode: return "operatorFnIdNode";
        case NodeKind::operatorNode: return "operatorNode";
        case NodeKind::newArrayOpNode: return "newArrayOpNode";
        case NodeKind::newOpNode: return "newOpNode";
        case NodeKind::deleteArrayOpNode: return "deleteArrayOpNode";
        case NodeKind::deleteOpNode: return "deleteOpNode";
        case NodeKind::coAwaitOpNode: return "coAwaitOpNode";
        case NodeKind::invokeOpNode: return "invokeOpNode";
        case NodeKind::subscriptOpNode: return "subscriptOpNode";
        case NodeKind::conversionFnIdNode: return "conversionFnIdNode";
        case NodeKind::conversionTypeIdNode: return "conversionTypeIdNode";
        case NodeKind::conversionDeclaratorNode: return "conversionDeclaratorNode";
        case NodeKind::destructorIdNode: return "destructorIdNode";
        case NodeKind::parameterNode: return "parameterNode";
        case NodeKind::parameterListNode: return "parameterListNode";
        case NodeKind::noexceptNode: return "noexceptNode";
        case NodeKind::functionTryBlock: return "functionTryBlock";
        case NodeKind::conceptDefinitionNode: return "conceptDefinitionNode";
        case NodeKind::requiresExprNode: return "requiresExprNode";
        case NodeKind::requirementBodyNode: return "requirementBodyNode";
        case NodeKind::simpleRequirementNode: return "simpleRequirementNode";
        case NodeKind::typeRequirementNode: return "typeRequirementNode";
        case NodeKind::compoundRequirementNode: return "compoundRequirementNode";
        case NodeKind::returnTypeRequirementNode: return "returnTypeRequirementNode";
        case NodeKind::nestedRequirementNode: return "nestedRequirementNode";
        case NodeKind::typeConstraintNode: return "typeConstraintNode";
        case NodeKind::requiresClauseNode: return "requiresClauseNode";
        case NodeKind::attributeSpecifierSequenceNode: return "attributeSpecifierSequenceNode";
        case NodeKind::attributeSpecifierNode: return "attributeSpecifierNode";
        case NodeKind::attributeUsingPrefixNode: return "attributeUsingPrefixNode";
        case NodeKind::attrbuteNode: return "attrbuteNode";
        case NodeKind::attributeScopedTokenNode: return "attributeScopedTokenNode";
        case NodeKind::attributeArgumentsNode: return "attributeArgumentsNode";
        case NodeKind::balancedTokenSequenceNode: return "balancedTokenSequenceNode";
        case NodeKind::tokenNode: return "tokenNode";
        case NodeKind::lparenNode: return "lparenNode";
        case NodeKind::rparenNode: return "rparenNode";
        case NodeKind::lbracketNode: return "lbracketNode";
        case NodeKind::rbracketNode: return "rbracketNode";
        case NodeKind::lbraceNode: return "lbraceNode";
        case NodeKind::rbraceNode: return "rbraceNode";
        case NodeKind::alignmentSpecifierNode: return "alignmentSpecifierNode";
        case NodeKind::pragmaNode: return "pragmaNode";
        case NodeKind::boundStatementNode: return "boundStatementNode";
    }
    return "<node>";
}

Node::Node(NodeKind kind_, const soul::ast::SourcePos& sourcePos_) : kind(kind_), sourcePos(sourcePos_), parent(nullptr), id(GetNextNodeId())
{
}

Node::~Node()
{
    if (nodeDestroyedFunc)
    {
        nodeDestroyedFunc(this);
    }
}

std::expected<bool, int> Node::AddNode(Node* node)
{
    return std::unexpected<int>(util::AllocateError("cannot add node to this kind of node"));
}

std::expected<bool, int> Node::Clear()
{
    return std::unexpected<int>(util::AllocateError("cannot clear to this kind of node"));
}

void Node::Write(Writer& writer)
{
    writer.GetBinaryStreamWriter().Write(id);
    writer.Write(sourcePos);
}

std::expected<bool, int> Node::Read(Reader& reader)
{
    std::expected<std::int64_t, int> rv = reader.GetBinaryStreamReader().ReadLong();
    if (!rv) return std::unexpected<int>(rv.error()); 
    id = *rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    sourcePos = *posRv;
    return std::expected<bool, int>(true);
}

CompoundNode::CompoundNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_) : Node(kind_, sourcePos_)
{
}

UnaryNode::UnaryNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, Node* child_) : Node(kind_, sourcePos_), child(child_)
{
    if (child)
    {
        child->SetParent(this);
    }
}

void UnaryNode::Write(Writer& writer)
{
    Node::Write(writer);
    writer.Write(child.get());
}

std::expected<bool, int> UnaryNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = Node::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    child.reset(*nrv);
    return std::expected<bool, int>(true);
}

BinaryNode::BinaryNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, Node* left_, Node* right_) : Node(kind_, sourcePos_), left(left_), right(right_)
{
    if (left)
    {
        left->SetParent(this);
    }
    if (right)
    {
        right->SetParent(this);
    }
}

void BinaryNode::Write(Writer& writer)
{
    Node::Write(writer);
    writer.Write(left.get());
    writer.Write(right.get());
}

std::expected<bool, int> BinaryNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = Node::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    left.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    right.reset(*nrv);
    return std::expected<bool, int>(true);
}

SequenceNode::SequenceNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_) : Node(kind_, sourcePos_)
{
}

void SequenceNode::AddNode(Node* node)
{
    node->SetParent(this);
    nodes.Add(node);
}

void SequenceNode::Clear()
{
    nodes.Clear();
}

void SequenceNode::Write(Writer& writer)
{
    Node::Write(writer);
    std::uint32_t n = Nodes().Count();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(n);
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(n); ++i)
    {
        Node* node = nodes[i];
        writer.Write(node);
    }
}

std::expected<bool, int> SequenceNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = Node::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> crv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!crv) return std::unexpected<int>(crv.error());
    std::uint32_t n = *crv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(n); ++i)
    {
        std::expected<Node*, int> nrv = reader.ReadNode();
        if (!nrv) return std::unexpected<int>(nrv.error());
        Node* node = *nrv;
        AddNode(node);
    }
    return std::expected<bool, int>(true);
}

ListNode::ListNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_) : Node(kind_, sourcePos_)
{
}

void ListNode::AddNode(Node* node)
{
    node->SetParent(this);
    nodes.Add(node);
    if (node->Kind() != NodeKind::commaNode)
    {
        items.push_back(node);
    }
}

void ListNode::Clear()
{
    nodes.Clear();
    items.clear();
}

void ListNode::Write(Writer& writer)
{
    Node::Write(writer);
    std::uint32_t n = Nodes().Count();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(n);
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(n); ++i)
    {
        Node* node = nodes[i];
        writer.Write(node);
    }
}

std::expected<bool, int> ListNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = Node::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> crv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!crv) return std::unexpected<int>(crv.error());
    std::uint32_t n = *crv;
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(n); ++i)
    {
        std::expected<Node*, int> nrv = reader.ReadNode();
        if (!nrv) return std::unexpected<int>(nrv.error());
        Node* node = *nrv;
        AddNode(node);
    }
    return std::expected<bool, int>(true);
}

struct AbstractNodeFactory
{
    virtual Node* CreateNode(const soul::ast::SourcePos& sourcePos) = 0;
};

template<typename T>
struct NodeFactory : AbstractNodeFactory
{
    Node* CreateNode(const soul::ast::SourcePos& sourcePos) override
    {
        return new T(sourcePos);
    }
};

class NodeFactoryCollection
{
public:
    static NodeFactoryCollection& Instance();
    ~NodeFactoryCollection();
    std::expected<Node*, int> CreateNode(NodeKind kind, const soul::ast::SourcePos& sourcePos);
    void Register(NodeKind kind, AbstractNodeFactory* factory);
private:
    NodeFactoryCollection();
    static std::unique_ptr<NodeFactoryCollection> instance;
    std::vector<std::unique_ptr<AbstractNodeFactory>> factories;
};

NodeFactoryCollection& NodeFactoryCollection::Instance()
{
    static NodeFactoryCollection instance;
    return instance;
}

NodeFactoryCollection::~NodeFactoryCollection()
{
}

NodeFactoryCollection::NodeFactoryCollection()
{
    factories.resize(static_cast<int>(static_cast<std::uint16_t>(NodeKind::max)));
    // Attribute:
    Register(NodeKind::attributeSpecifierSequenceNode, new NodeFactory<AttributeSpecifierSequenceNode>());
    Register(NodeKind::attributeSpecifierNode, new NodeFactory<AttributeSpecifierNode>());
    Register(NodeKind::attributeUsingPrefixNode, new NodeFactory<AttributeUsingPrefixNode>());
    Register(NodeKind::attrbuteNode, new NodeFactory<AttributeNode>());
    Register(NodeKind::attributeScopedTokenNode, new NodeFactory<AttributeScopedTokenNode>());
    Register(NodeKind::attributeArgumentsNode, new NodeFactory<AttributeArgumentsNode>());
    Register(NodeKind::balancedTokenSequenceNode, new NodeFactory<BalancedTokenSequenceNode>());
    Register(NodeKind::tokenNode, new NodeFactory<TokenNode>());
    Register(NodeKind::alignmentSpecifierNode, new NodeFactory<AlignmentSpecifierNode>());
    Register(NodeKind::lparenNode, new NodeFactory<LParenNode>());
    Register(NodeKind::rparenNode, new NodeFactory<RParenNode>());
    Register(NodeKind::lbracketNode, new NodeFactory<LBracketNode>());
    Register(NodeKind::rbracketNode, new NodeFactory<RBracketNode>());
    Register(NodeKind::lbraceNode, new NodeFactory<LBraceNode>());
    Register(NodeKind::rbraceNode, new NodeFactory<RBraceNode>());
    // Class:
    Register(NodeKind::classSpecifierNode, new NodeFactory<ClassSpecifierNode>());
    Register(NodeKind::classHeadNode, new NodeFactory<ClassHeadNode>());
    Register(NodeKind::baseClauseNode, new NodeFactory<BaseClauseNode>());
    Register(NodeKind::baseSpecifierListNode, new NodeFactory<BaseSpecifierListNode>());
    Register(NodeKind::baseSpecifierNode, new NodeFactory<BaseSpecifierNode>());
    Register(NodeKind::beginAccessGroupNode, new NodeFactory<BeginAccessGroupNode>());
    Register(NodeKind::memberDeclarationNode, new NodeFactory<MemberDeclarationNode>());
    Register(NodeKind::memberDeclaratorListNode, new NodeFactory<MemberDeclaratorListNode>());
    Register(NodeKind::constructorNode, new NodeFactory<ConstructorNode>());
    Register(NodeKind::constructorInitializerNode, new NodeFactory<ConstructorInitializerNode>());
    Register(NodeKind::memberInitializerListNode, new NodeFactory<MemberInitializerListNode>());
    Register(NodeKind::memberInitializerNode, new NodeFactory<MemberInitializerNode>());
    Register(NodeKind::virtSpecifierSequenceNode, new NodeFactory<VirtSpecifierSequenceNode>());
    Register(NodeKind::classNode, new NodeFactory<ClassNode>());
    Register(NodeKind::structNode, new NodeFactory<StructNode>());
    Register(NodeKind::unionNode, new NodeFactory<UnionNode>());
    Register(NodeKind::publicNode, new NodeFactory<PublicNode>());
    Register(NodeKind::protectedNode, new NodeFactory<ProtectedNode>());
    Register(NodeKind::privateNode, new NodeFactory<PrivateNode>());
    Register(NodeKind::virtualNode, new NodeFactory<VirtualNode>());
    Register(NodeKind::overrideNode, new NodeFactory<OverrideNode>());
    Register(NodeKind::finalNode, new NodeFactory<FinalNode>());
    Register(NodeKind::pureSpecifierNode, new NodeFactory<PureSpecifierNode>());
    // Concept:
    Register(NodeKind::conceptDefinitionNode, new NodeFactory<ConceptDefinitionNode>());
    Register(NodeKind::requiresExprNode, new NodeFactory<RequiresExprNode>());
    Register(NodeKind::requirementBodyNode, new NodeFactory<RequirementBodyNode>());
    Register(NodeKind::simpleRequirementNode, new NodeFactory<SimpleRequirementNode>());
    Register(NodeKind::typeRequirementNode, new NodeFactory<TypeRequirementNode>());
    Register(NodeKind::compoundRequirementNode, new NodeFactory<CompoundRequirementNode>());
    Register(NodeKind::returnTypeRequirementNode, new NodeFactory<ReturnTypeRequirementNode>());
    Register(NodeKind::nestedRequirementNode, new NodeFactory<NestedRequirementNode>());
    Register(NodeKind::typeConstraintNode, new NodeFactory<TypeConstraintNode>());
    Register(NodeKind::requiresClauseNode, new NodeFactory<RequiresClauseNode>());
    // Declaration:
    Register(NodeKind::declarationSequenceNode, new NodeFactory<DeclarationSequenceNode>());
    Register(NodeKind::simpleDeclarationNode, new NodeFactory<SimpleDeclarationNode>());
    Register(NodeKind::asmDeclarationNode, new NodeFactory<AsmDeclarationNode>());
    Register(NodeKind::asmNode, new NodeFactory<AsmNode>());
    Register(NodeKind::linkageSpecificationNode, new NodeFactory<LinkageSpecificationNode>());
    Register(NodeKind::namespaceDefinitionNode, new NodeFactory<NamespaceDefinitionNode>());
    Register(NodeKind::namespaceBodyNode, new NodeFactory<NamespaceBodyNode>());
    Register(NodeKind::namespaceAliasDefinitionNode, new NodeFactory<NamespaceAliasDefinitionNode>());
    Register(NodeKind::usingDeclarationNode, new NodeFactory<UsingDeclarationNode>());
    Register(NodeKind::usingNode, new NodeFactory<UsingNode>());
    Register(NodeKind::usingDeclaratorListNode, new NodeFactory<UsingDeclaratorListNode>());
    Register(NodeKind::usingEnumDeclarationNode, new NodeFactory<UsingEnumDeclarationNode>());
    Register(NodeKind::usingDirectiveNode, new NodeFactory<UsingDirectiveNode>());
    Register(NodeKind::namespaceNode, new NodeFactory<NamespaceNode>());
    Register(NodeKind::staticAssertDeclarationNode, new NodeFactory<StaticAssertDeclarationNode>());
    Register(NodeKind::staticAssertNode, new NodeFactory<StaticAssertNode>());
    Register(NodeKind::aliasDeclarationNode, new NodeFactory<AliasDeclarationNode>());
    Register(NodeKind::emptyDeclarationNode, new NodeFactory<EmptyDeclarationNode>());
    Register(NodeKind::attributeDeclarationNode, new NodeFactory<AttributeDeclarationNode>());
    Register(NodeKind::initDeclaratorListNode, new NodeFactory<InitDeclaratorListNode>());
    Register(NodeKind::initDeclaratorNode, new NodeFactory<InitDeclaratorNode>());
    Register(NodeKind::trailingFunctionDeclaratorNode, new NodeFactory<TrailingFunctionDeclaratorNode>());
    Register(NodeKind::parenthesizedDeclaratorNode, new NodeFactory<ParenthesizedDeclaratorNode>());
    Register(NodeKind::abstractDeclaratorNode, new NodeFactory<AbstractDeclaratorNode>());
    Register(NodeKind::declSpecifierSequenceNode, new NodeFactory<DeclSpecifierSequenceNode>());
    Register(NodeKind::friendNode, new NodeFactory<FriendNode>());
    Register(NodeKind::typedefNode, new NodeFactory<TypedefNode>());
    Register(NodeKind::constExprNode, new NodeFactory<ConstExprNode>());
    Register(NodeKind::constEvalNode, new NodeFactory<ConstEvalNode>());
    Register(NodeKind::constInitNode, new NodeFactory<ConstInitNode>());
    Register(NodeKind::inlineNode, new NodeFactory<InlineNode>());
    Register(NodeKind::staticNode, new NodeFactory<StaticNode>());
    Register(NodeKind::threadLocalNode, new NodeFactory<ThreadLocalNode>());
    Register(NodeKind::externNode, new NodeFactory<ExternNode>());
    Register(NodeKind::mutableNode, new NodeFactory<MutableNode>());
    Register(NodeKind::explicitNode, new NodeFactory<ExplicitNode>());
    Register(NodeKind::conditionalExplicitNode, new NodeFactory<ConditionalExplicitNode>());
    Register(NodeKind::qualifiedPtrNode, new NodeFactory<QualifiedPtrNode>());
    Register(NodeKind::ptrOperatorNode, new NodeFactory<PtrOperatorNode>());
    Register(NodeKind::ptrDeclaratorNode, new NodeFactory<PtrDeclaratorNode>());
    Register(NodeKind::packDeclaratorIdNode, new NodeFactory<PackDeclaratorIdNode>());
    Register(NodeKind::arrayDeclaratorNode, new NodeFactory<ArrayDeclaratorNode>());
    Register(NodeKind::functionDeclaratorNode, new NodeFactory<FunctionDeclaratorNode>());
    Register(NodeKind::prefixNode, new NodeFactory<PrefixNode>());
    Register(NodeKind::trailingQualifiersNode, new NodeFactory<TrailingQualifiersNode>());
    Register(NodeKind::trailingAttributesNode, new NodeFactory<TrailingAttributesNode>());
    Register(NodeKind::noexceptSpecifierNode, new NodeFactory<NoexceptSpecifierNode>());
    Register(NodeKind::throwSpecifierNode, new NodeFactory<ThrowSpecifierNode>());
    //Enum:
    Register(NodeKind::enumSpecifierNode, new NodeFactory<EnumSpecifierNode>());
    Register(NodeKind::enumHeadNode, new NodeFactory<EnumHeadNode>());
    Register(NodeKind::enumBaseNode, new NodeFactory<EnumBaseNode>());
    Register(NodeKind::enumClassNode, new NodeFactory<EnumClassNode>());
    Register(NodeKind::enumStructNode, new NodeFactory<EnumStructNode>());
    Register(NodeKind::enumNode, new NodeFactory<EnumNode>());
    Register(NodeKind::enumeratorDefinitionNode, new NodeFactory<EnumeratorDefinitionNode>());
    Register(NodeKind::enumeratorNode, new NodeFactory<EnumeratorNode>());
    Register(NodeKind::elaboratedEnumSpecifierNode, new NodeFactory<ElaboratedEnumSpecifierNode>());
    Register(NodeKind::opaqueEnumDeclarationNode, new NodeFactory<OpaqueEnumDeclarationNode>());
    // Expression:
    Register(NodeKind::binaryExprNode, new NodeFactory<BinaryExprNode>());
    Register(NodeKind::unaryExprNode, new NodeFactory<UnaryExprNode>());
    Register(NodeKind::expressionListNode, new NodeFactory<ExpressionListNode>());
    Register(NodeKind::assignmentInitializerNode, new NodeFactory<AssignmentInitNode>());
    Register(NodeKind::yieldExprNode, new NodeFactory<YieldExprNode>());
    Register(NodeKind::conditionalExprNode, new NodeFactory<ConditionalExprNode>());
    Register(NodeKind::colonNode, new NodeFactory<ColonNode>());
    Register(NodeKind::commaNode, new NodeFactory<CommaNode>());
    Register(NodeKind::assignNode, new NodeFactory<AssignNode>());
    Register(NodeKind::plusAssignNode, new NodeFactory<PlusAssignNode>());
    Register(NodeKind::minusAssignNode, new NodeFactory<MinusAssignNode>());
    Register(NodeKind::mulAssignNode, new NodeFactory<MulAssignNode>());
    Register(NodeKind::divAssignNode, new NodeFactory<DivAssignNode>());
    Register(NodeKind::modAssignNode, new NodeFactory<ModAssignNode>());
    Register(NodeKind::xorAssignNode, new NodeFactory<XorAssignNode>());
    Register(NodeKind::andAssignNode, new NodeFactory<AndAssignNode>());
    Register(NodeKind::orAssignNode, new NodeFactory<OrAssignNode>());
    Register(NodeKind::shiftLeftAssignNode, new NodeFactory<ShiftLeftAssignNode>());
    Register(NodeKind::shiftRightAssignNode, new NodeFactory<ShiftRightAssignNode>());
    Register(NodeKind::questNode, new NodeFactory<QuestNode>());
    Register(NodeKind::disjunctionNode, new NodeFactory<DisjunctionNode>());
    Register(NodeKind::conjunctionNode, new NodeFactory<ConjunctionNode>());
    Register(NodeKind::inclusiveOrNode, new NodeFactory<InclusiveOrNode>());
    Register(NodeKind::exclusiveOrNode, new NodeFactory<ExclusiveOrNode>());
    Register(NodeKind::andNode, new NodeFactory<AndNode>());
    Register(NodeKind::equalNode, new NodeFactory<EqualNode>());
    Register(NodeKind::notEqualNode, new NodeFactory<NotEqualNode>());
    Register(NodeKind::lessNode, new NodeFactory<LessNode>());
    Register(NodeKind::greaterNode, new NodeFactory<GreaterNode>());
    Register(NodeKind::lessOrEqualNode, new NodeFactory<LessOrEqualNode>());
    Register(NodeKind::greaterOrEqualNode, new NodeFactory<GreaterOrEqualNode>());
    Register(NodeKind::compareNode, new NodeFactory<CompareNode>());
    Register(NodeKind::shiftLeftNode, new NodeFactory<ShiftLeftNode>());
    Register(NodeKind::shiftRightNode, new NodeFactory<ShiftRightNode>());
    Register(NodeKind::plusNode, new NodeFactory<PlusNode>());
    Register(NodeKind::minusNode, new NodeFactory<MinusNode>());
    Register(NodeKind::mulNode, new NodeFactory<MulNode>());
    Register(NodeKind::divNode, new NodeFactory<DivNode>());
    Register(NodeKind::modNode, new NodeFactory<ModNode>());
    Register(NodeKind::dotStarNode, new NodeFactory<DotStarNode>());
    Register(NodeKind::arrowStarNode, new NodeFactory<ArrowStarNode>());
    Register(NodeKind::castExprNode, new NodeFactory<CastExprNode>());
    Register(NodeKind::derefNode, new NodeFactory<DerefNode>());
    Register(NodeKind::addrOfNode, new NodeFactory<AddrOfNode>());
    Register(NodeKind::notNode, new NodeFactory<NotNode>());
    Register(NodeKind::complementNode, new NodeFactory<ComplementNode>());
    Register(NodeKind::prefixIncNode, new NodeFactory<PrefixIncNode>());
    Register(NodeKind::prefixDecNode, new NodeFactory<PrefixDecNode>());
    Register(NodeKind::awaitExprNode, new NodeFactory<AwaitExprNode>());
    Register(NodeKind::sizeOfTypeExprNode, new NodeFactory<SizeOfTypeExprNode>());
    Register(NodeKind::sizeOfPackExpNode, new NodeFactory<SizeOfPackExprNode>());
    Register(NodeKind::sizeOfUnaryExprNode, new NodeFactory<SizeOfUnaryExprNode>());
    Register(NodeKind::alignOfExprNode, new NodeFactory<AlignOfExprNode>());
    Register(NodeKind::noexceptExprNode, new NodeFactory<NoexceptExprNode>());
    Register(NodeKind::newExprNode, new NodeFactory<NewExprNode>());
    Register(NodeKind::newPlacementNode, new NodeFactory<NewPlacementNode>());
    Register(NodeKind::parenNewTypeIdNode, new NodeFactory<ParenNewTypeIdNode>());
    Register(NodeKind::newTypeIdNode, new NodeFactory<NewTypeIdNode>());
    Register(NodeKind::arrayDeletePtrNode, new NodeFactory<ArrayDeletePtrNode>());
    Register(NodeKind::deletePtrNode, new NodeFactory<DeletePtrNode>());
    Register(NodeKind::subscriptExprNode, new NodeFactory<SubscriptExprNode>());
    Register(NodeKind::invokeExprNode, new NodeFactory<InvokeExprNode>());
    Register(NodeKind::pairNode, new NodeFactory<PairNode>());
    Register(NodeKind::dotNode, new NodeFactory<DotNode>());
    Register(NodeKind::arrowNode, new NodeFactory<ArrowNode>());
    Register(NodeKind::memberExprNode, new NodeFactory<MemberExprNode>());
    Register(NodeKind::postfixIncExprNode, new NodeFactory<PostfixIncExprNode>());
    Register(NodeKind::postfixDecExprNode, new NodeFactory<PostfixDecExprNode>());
    Register(NodeKind::typeIdExprNode, new NodeFactory<TypeIdExprNode>());
    Register(NodeKind::dynamicCastNode, new NodeFactory<DynamicCastNode>());
    Register(NodeKind::staticCastNode, new NodeFactory<StaticCastNode>());
    Register(NodeKind::reinterpretCastNode, new NodeFactory<ReinterpretCastNode>());
    Register(NodeKind::constCastNode, new NodeFactory<ConstCastNode>());
    Register(NodeKind::cppCastExprNode, new NodeFactory<CppCastExprNode>());
    Register(NodeKind::thisNode, new NodeFactory<ThisNode>());
    Register(NodeKind::parenExprNode, new NodeFactory<ParenthesizedExprNode>());
    Register(NodeKind::foldExprNode, new NodeFactory<FoldExprNode>());
    Register(NodeKind::newDeclaratorNode, new NodeFactory<NewDeclaratorNode>());
    Register(NodeKind::arrayNewDeclaratorNode, new NodeFactory<ArrayNewDeclaratorNode>());
    Register(NodeKind::newInitializerNode, new NodeFactory<NewInitializerNode>());
    Register(NodeKind::bracedInitListNode, new NodeFactory<BracedInitListNode>());
    Register(NodeKind::designatedInitializerNode, new NodeFactory<DesignatedInitializerNode>());
    Register(NodeKind::designatorNode, new NodeFactory<DesignatorNode>());
    Register(NodeKind::ellipsisNode, new NodeFactory<EllipsisNode>());
    // Function:
    Register(NodeKind::functionDefinitionNode, new NodeFactory<FunctionDefinitionNode>());
    Register(NodeKind::functionBodyNode, new NodeFactory<FunctionBodyNode>());
    Register(NodeKind::defaultNode, new NodeFactory<DefaultNode>());
    Register(NodeKind::deleteNode, new NodeFactory<DeleteNode>());
    Register(NodeKind::defaultedOrDeletedFunctionNode, new NodeFactory<DefaultedOrDeletedFunctionNode>());
    Register(NodeKind::noDeclSpecFunctionDeclarationNode, new NodeFactory<NoDeclSpecFunctionDeclarationNode>());
    Register(NodeKind::operatorNode, new NodeFactory<OperatorNode>());
    Register(NodeKind::newArrayOpNode, new NodeFactory<NewArrayOpNode>());
    Register(NodeKind::newOpNode, new NodeFactory<NewOpNode>());
    Register(NodeKind::deleteArrayOpNode, new NodeFactory<DeleteArrayOpNode>());
    Register(NodeKind::deleteOpNode, new NodeFactory<DeleteOpNode>());
    Register(NodeKind::coAwaitOpNode, new NodeFactory<CoAwaitOpNode>());
    Register(NodeKind::invokeOpNode, new NodeFactory<InvokeOpNode>());
    Register(NodeKind::subscriptOpNode, new NodeFactory<SubscriptOpNode>());
    Register(NodeKind::operatorFnIdNode, new NodeFactory<OperatorFunctionIdNode>());
    Register(NodeKind::conversionFnIdNode, new NodeFactory<ConversionFunctionIdNode>());
    Register(NodeKind::conversionTypeIdNode, new NodeFactory<ConversionTypeIdNode>());
    Register(NodeKind::conversionDeclaratorNode, new NodeFactory<ConversionDeclaratorNode>());
    Register(NodeKind::destructorIdNode, new NodeFactory<DestructorIdNode>());
    Register(NodeKind::parameterNode, new NodeFactory<ParameterNode>());
    Register(NodeKind::parameterListNode, new NodeFactory<ParameterListNode>());
    Register(NodeKind::noexceptNode, new NodeFactory<NoexceptNode>());
    Register(NodeKind::functionTryBlock, new NodeFactory<FunctionTryBlockNode>());
    // Identifier:
    Register(NodeKind::identifierNode, new NodeFactory<IdentifierNode>());
    Register(NodeKind::colonColonNode, new NodeFactory<ColonColonNode>());
    Register(NodeKind::nestedNameSpecifierNode, new NodeFactory<NestedNameSpecifierNode>());
    Register(NodeKind::qualifiedIdNode, new NodeFactory<QualifiedIdNode>());
    Register(NodeKind::identifierListNode, new NodeFactory<IdentifierListNode>());
    Register(NodeKind::moduleNameNode, new NodeFactory<ModuleNameNode>());
    Register(NodeKind::unnamedNode, new NodeFactory<UnnamedNode>());
    // Lambda:
    Register(NodeKind::lambdaExpressionNode, new NodeFactory<LambdaExpressionNode>());
    Register(NodeKind::lambdaIntroducerNode, new NodeFactory<LambdaIntroducerNode>());
    Register(NodeKind::lambdaCaptureNode, new NodeFactory<LambdaCaptureNode>());
    Register(NodeKind::defaultRefCaptureNode, new NodeFactory<DefaultRefCaptureNode>());
    Register(NodeKind::defaultCopyCaptureNode, new NodeFactory<DefaultCopyCaptureNode>());
    Register(NodeKind::byRefCaptureNode, new NodeFactory<ByRefCaptureNode>());
    Register(NodeKind::simpleCaptureNode, new NodeFactory<SimpleCaptureNode>());
    Register(NodeKind::currentObjectCopyCapture, new NodeFactory<CurrentObjectCopyCapture>());
    Register(NodeKind::currentObjectByRefCapture, new NodeFactory<CurrentObjectByRefCapture>());
    Register(NodeKind::initCaptureNode, new NodeFactory<InitCaptureNode>());
    Register(NodeKind::lambdaDeclaratorNode, new NodeFactory<LambdaDeclaratorNode>());
    Register(NodeKind::lambdaSpecifiersNode, new NodeFactory<LambdaSpecifiersNode>());
    Register(NodeKind::lambdaTemplateParamsNode, new NodeFactory<LambdaTemplateParamsNode>());
    // Literal:
    Register(NodeKind::integerLiteralNode, new NodeFactory<IntegerLiteralNode>());
    Register(NodeKind::floatingLiteralNode, new NodeFactory<FloatingLiteralNode>());
    Register(NodeKind::characterLiteralNode, new NodeFactory<CharacterLiteralNode>());
    Register(NodeKind::stringLiteralNode, new NodeFactory<StringLiteralNode>());
    Register(NodeKind::rawStringLiteralNode, new NodeFactory<RawStringLiteralNode>());
    Register(NodeKind::booleanLiteralNode, new NodeFactory<BooleanLiteralNode>());
    Register(NodeKind::nullPtrLiteralNode, new NodeFactory<NullPtrLiteralNode>());
    Register(NodeKind::userDefinedLiteralNode, new NodeFactory< UserDefinedLiteraNode>());
    Register(NodeKind::literalOperatorIdNode, new NodeFactory<LiteralOperatorIdNode>());
    // Module:
    Register(NodeKind::moduleDeclarationNode, new NodeFactory<ModuleDeclarationNode>());
    Register(NodeKind::exportDeclarationNode, new NodeFactory<ExportDeclarationNode>());
    Register(NodeKind::exportNode, new NodeFactory<ExportNode>());
    Register(NodeKind::importNode, new NodeFactory<ImportNode>());
    Register(NodeKind::importDeclarationNode, new NodeFactory<ImportDeclarationNode>());
    Register(NodeKind::modulePartitionNode, new NodeFactory<ModulePartitionNode>());
    Register(NodeKind::moduleNode, new NodeFactory<ModuleNode>());
    Register(NodeKind::globalModuleFragmentNode, new NodeFactory<GlobalModuleFragmentNode>());
    Register(NodeKind::privateModuleFragmentNode, new NodeFactory<PrivateModuleFragmentNode>());
    // Qualifier:
    Register(NodeKind::constNode, new NodeFactory<ConstNode>());
    Register(NodeKind::volatileNode, new NodeFactory<VolatileNode>());
    Register(NodeKind::lvalueRefNode, new NodeFactory<LvalueRefNode>());
    Register(NodeKind::rvalueRefNode, new NodeFactory<RvalueRefNode>());
    Register(NodeKind::ptrNode, new NodeFactory<PtrNode>());
    Register(NodeKind::cvQualifierSequenceNode, new NodeFactory<CVQualifierSequenceNode>());
    // SimpleType:
    Register(NodeKind::charNode, new NodeFactory<CharNode>());
    Register(NodeKind::char8Node, new NodeFactory<Char8Node>());
    Register(NodeKind::char16Node, new NodeFactory<Char16Node>());
    Register(NodeKind::char32Node, new NodeFactory<Char32Node>());
    Register(NodeKind::wcharNode, new NodeFactory<WCharNode>());
    Register(NodeKind::boolNode, new NodeFactory<BoolNode>());
    Register(NodeKind::shortNode, new NodeFactory<ShortNode>());
    Register(NodeKind::intNode, new NodeFactory<IntNode>());
    Register(NodeKind::longNode, new NodeFactory<LongNode>());
    Register(NodeKind::signedNode, new NodeFactory<SignedNode>());
    Register(NodeKind::unsignedNode, new NodeFactory<UnsignedNode>());
    Register(NodeKind::floatNode, new NodeFactory<FloatNode>());
    Register(NodeKind::doubleNode, new NodeFactory<DoubleNode>());
    Register(NodeKind::voidNode, new NodeFactory<VoidNode>());
    // Statement:
    Register(NodeKind::labeledStatementNode, new NodeFactory<LabeledStatementNode>());
    Register(NodeKind::caseStatmentNode, new NodeFactory<CaseStatementNode>());
    Register(NodeKind::defaultStatementNode, new NodeFactory<DefaultStatementNode>());
    Register(NodeKind::compoundStatementNode, new NodeFactory<CompoundStatementNode>());
    Register(NodeKind::ifStatementNode, new NodeFactory<IfStatementNode>());
    Register(NodeKind::switchStatemeNode, new NodeFactory<SwitchStatementNode>());
    Register(NodeKind::whileStatementNode, new NodeFactory<WhileStatementNode>());
    Register(NodeKind::doStatementNode, new NodeFactory<DoStatementNode>());
    Register(NodeKind::rangeForStatementNode, new NodeFactory<RangeForStatementNode>());
    Register(NodeKind::forRangeDeclarationNode, new NodeFactory<ForRangeDeclarationNode>());
    Register(NodeKind::structuredBindingNode, new NodeFactory<StructuredBindingNode>());
    Register(NodeKind::forStatementNode, new NodeFactory<ForStatementNode>());
    Register(NodeKind::breakStatementNode, new NodeFactory<BreakStatementNode>());
    Register(NodeKind::continueStatementNode, new NodeFactory<ContinueStatementNode>());
    Register(NodeKind::returnStatementNode, new NodeFactory<ReturnStatementNode>());
    Register(NodeKind::coReturnStatementNode, new NodeFactory<CoReturnStatementNode>());
    Register(NodeKind::gotoStatementNode, new NodeFactory<GotoStatementNode>());
    Register(NodeKind::tryStatementNode, new NodeFactory<TryStatementNode>());
    Register(NodeKind::handlerSequenceNode, new NodeFactory<HandlerSequenceNode>());
    Register(NodeKind::handlerNode, new NodeFactory<HandlerNode>());
    Register(NodeKind::exceptionDeclarationNode, new NodeFactory<ExceptionDeclarationNode>());
    Register(NodeKind::expressionStatementNode, new NodeFactory<ExpressionStatementNode>());
    Register(NodeKind::declarationStatementNode, new NodeFactory<DeclarationStatementNode>());
    Register(NodeKind::initConditionNode, new NodeFactory<InitConditionNode>());
    Register(NodeKind::semicolonNode, new NodeFactory<SemicolonNode>());
    // Template:
    Register(NodeKind::templateDeclarationNode, new NodeFactory<TemplateDeclarationNode>());
    Register(NodeKind::templateHeadNode, new NodeFactory<TemplateHeadNode>());
    Register(NodeKind::templateParameterListNode, new NodeFactory<TemplateParameterListNode>());
    Register(NodeKind::typeParameterNode, new NodeFactory<TypeParameterNode>());
    Register(NodeKind::templateIdNode, new NodeFactory<TemplateIdNode>());
    Register(NodeKind::typenameNode, new NodeFactory<TypenameNode>());
    Register(NodeKind::deductionGuideNode, new NodeFactory<DeductionGuideNode>());
    Register(NodeKind::explicitInstantiationNode, new NodeFactory<ExplicitInstantiationNode>());
    Register(NodeKind::templateNode, new NodeFactory<TemplateNode>());
    Register(NodeKind::explicitSpecializationNode, new NodeFactory<ExplicitSpecializationNode>());
    // TranslationUnit:
    Register(NodeKind::translationUnitNode, new NodeFactory<TranslationUnitNode>());
    Register(NodeKind::moduleUnitNode, new NodeFactory<ModuleUnitNode>());
    // Type:
    Register(NodeKind::typeSpecifierSequenceNode, new NodeFactory<TypeSpecifierSequenceNode>());
    Register(NodeKind::typenameSpecifierNode, new NodeFactory<TypenameSpecifierNode>());
    Register(NodeKind::typeIdNode, new NodeFactory<TypeIdNode>());
    Register(NodeKind::definingTypeIdNode, new NodeFactory<DefiningTypeIdNode>());
    Register(NodeKind::definingTypeSpecifierSequenceNode, new NodeFactory<DefiningTypeSpecifierSequenceNode>());
    Register(NodeKind::trailingReturnTypeNode, new NodeFactory<TrailingReturnTypeNode>());
    Register(NodeKind::elaboratedTypeSpecifierNode, new NodeFactory<ElaboratedTypeSpecifierNode>());
    Register(NodeKind::declTypeSpecifierNode, new NodeFactory<DeclTypeSpecifierNode>());
    Register(NodeKind::placeholderTypeSpecifierNode, new NodeFactory<PlaceholderTypeSpecifierNode>());
}

std::expected<Node*, int> NodeFactoryCollection::CreateNode(NodeKind nodeKind, const soul::ast::SourcePos& sourcePos)
{
    AbstractNodeFactory* factory = factories[static_cast<int>(static_cast<std::uint16_t>(nodeKind))].get();
    if (factory)
    {
        return factory->CreateNode(sourcePos);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("factory for node kind '" + NodeKindStr(nodeKind) + "' not registered"));
    }
}

void NodeFactoryCollection::Register(NodeKind kind, AbstractNodeFactory* factory)
{
    factories[static_cast<int>(static_cast<std::uint16_t>(kind))] = std::unique_ptr<AbstractNodeFactory>(factory);
}

std::expected<Node*, int> CreateNode(NodeKind nodeKind, const soul::ast::SourcePos& sourcePos)
{
    return NodeFactoryCollection::Instance().CreateNode(nodeKind, sourcePos);
}

void MakeNodeFactoryCollection()
{
    NodeFactoryCollection::Instance();
}

NodeIdFactory::NodeIdFactory() : moduleId(0), nodeId(0), internallyMappedBit(0)
{
}

void NodeIdFactory::SetInternallyMapped(bool internallyMapped_)
{
    if (internallyMapped_)
    {
        internallyMappedBit = internallyMappedFlag;
    }
    else
    {
        internallyMappedBit = 0;
    }
}

bool NodeIdFactory::IsInternallyMapped() const
{
    return internallyMappedBit != 0;
}

std::int64_t NodeIdFactory::GetNextNodeId()
{
    std::int64_t nextNodeId = (static_cast<std::int64_t>(moduleId) << 32) | static_cast<std::int64_t>(nodeId) | static_cast<std::int64_t>(internallyMappedBit);
    ++nodeId;
    return nextNodeId;
}

thread_local NodeIdFactory* nodeIdFactory = nullptr;

void SetNodeIdFactory(NodeIdFactory* factory)
{
    nodeIdFactory = factory;
}

std::int64_t GetNextNodeId()
{
    return nodeIdFactory->GetNextNodeId();
}

} // namespace otava::ast
