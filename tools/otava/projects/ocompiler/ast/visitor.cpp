// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.visitor;

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
import otava.ast.node;
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
import otava.ast.writer;

namespace otava::ast {

Visitor::Visitor() : error(0)
{
}

Visitor::~Visitor()
{
}

void Visitor::VisitSingleNode(Node& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    EndVisit(node);
}

void Visitor::VisitUnaryNode(UnaryNode& unaryNode)
{
    if (!Valid()) return;
    BeginVisit(unaryNode);
    if (!Valid()) return;
    unaryNode.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(unaryNode);
}

void Visitor::VisitBinaryNode(BinaryNode& binaryNode)
{
    if (!Valid()) return;
    BeginVisit(binaryNode);
    if (!Valid()) return;
    binaryNode.Left()->Accept(*this);
    if (!Valid()) return;
    binaryNode.Right()->Accept(*this);
    if (!Valid()) return;
    EndVisit(binaryNode);
}

void Visitor::VisitSequence(SequenceNode& sequenceNode)
{
    if (!Valid()) return;
    BeginVisit(sequenceNode);
    if (!Valid()) return;
    VisitSequenceContent(sequenceNode);
    if (!Valid()) return;
    EndVisit(sequenceNode);
}

void Visitor::VisitSequenceContent(SequenceNode& sequenceNode)
{
    if (!Valid()) return;
    int n = sequenceNode.Nodes().Count();
    for (int i = 0; i < n; ++i)
    {
        Node* node = sequenceNode.Nodes()[i];
        node->Accept(*this);
        if (!Valid()) return;
    }
}

void Visitor::VisitList(ListNode& listNode)
{
    if (!Valid()) return;
    BeginVisit(listNode);
    if (!Valid()) return;
    VisitListContent(listNode);
    if (!Valid()) return;
    EndVisit(listNode);
}

void Visitor::VisitListContent(ListNode& listNode)
{
    if (!Valid()) return;
    int n = listNode.Nodes().Count();
    for (int i = 0; i < n; ++i)
    {
        Node* node = listNode.Nodes()[i];
        node->Accept(*this);
        if (!Valid()) return;
    }
}

// DefaultVisitor:

// Attribute:

void DefaultVisitor::Visit(AttributeSpecifierSequenceNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(AttributeSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("[", node.LBracketPos1());
    if (!Valid()) return;
    VisitOperator("[", node.LBracketPos2());
    if (!Valid()) return;
    if (node.UsingPrefix())
    {
        node.UsingPrefix()->Accept(*this);
        if (!Valid()) return;
    }
    VisitListContent(node);
    if (!Valid()) return;
    VisitOperator("]", node.RBracketPos1());
    if (!Valid()) return;
    VisitOperator("]", node.RBracketPos2());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AttributeUsingPrefixNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("using", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(":", node.ColonPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AttributeNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.AttributeToken()->Accept(*this);
    if (!Valid()) return;
    if (node.AttributeArgs())
    {
        node.AttributeArgs()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(AttributeScopedTokenNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Ns()->Accept(*this);
    if (!Valid()) return;
    node.ColonColon()->Accept(*this);
    if (!Valid()) return;
    node.Identifier()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AttributeArgumentsNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    if (node.BalancedTokenSequence())
    {
        node.BalancedTokenSequence()->Accept(*this);
        if (!Valid()) return;
    }
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(BalancedTokenSequenceNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(TokenNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitToken(node.Str(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AlignmentSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("alignas", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Alignment()->Accept(*this);
    if (!Valid()) return;
    if (node.Ellipsis())
    {
        node.Ellipsis()->Accept(*this);
        if (!Valid()) return;
    }
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(LParenNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(RParenNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(")", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(LBracketNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("[", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(RBracketNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("]", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(LBraceNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("{", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(RBraceNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("}", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

//  Class:

void DefaultVisitor::Visit(ClassSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.ClassHead()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("{", node.LBracePos());
    if (!Valid()) return;
    VisitSequenceContent(node);
    if (!Valid()) return;
    VisitOperator("}", node.RBracePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ClassHeadNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.ClassKey()->Accept(*this);
    if (!Valid()) return;
    if (node.Attibutes())
    {
        node.Attibutes()->Accept(*this);
        if (!Valid()) return;
    }
    node.ClassHeadName()->Accept(*this);
    if (!Valid()) return;
    if (node.ClassVirtSpecifier())
    {
        node.ClassVirtSpecifier()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.BaseClause())
    {
        node.BaseClause()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(BaseClauseNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(":", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(BaseSpecifierListNode& node)
{
    VisitList(node);
}

void DefaultVisitor::Visit(BaseSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.VirtualFirst())
    {
        if (node.VirtualSpecifier())
        {
            node.VirtualSpecifier()->Accept(*this);
            if (!Valid()) return;
        }
        if (node.AccessSpecifier())
        {
            node.AccessSpecifier()->Accept(*this);
            if (!Valid()) return;
        }
    }
    else
    {
        if (node.AccessSpecifier())
        {
            node.AccessSpecifier()->Accept(*this);
            if (!Valid()) return;
        }
        if (node.VirtualSpecifier())
        {
            node.VirtualSpecifier()->Accept(*this);
            if (!Valid()) return;
        }
    }
    node.ClassOrDeclType()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(BeginAccessGroupNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(":", node.ColonPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(MemberDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.DeclSpecifiers())
    {
        node.DeclSpecifiers()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.MemberDeclarators())
    {
        node.MemberDeclarators()->Accept(*this);
        if (!Valid()) return;
    }
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(MemberDeclaratorListNode& node)
{
    VisitList(node);
}

void DefaultVisitor::Visit(ConstructorNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(ConstructorInitializerNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(":", node.GetSourcePos());
    if (!Valid()) return;
    node.GetMemberInitializerListNode()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(MemberInitializerListNode& node)
{
    VisitList(node);
}

void DefaultVisitor::Visit(MemberInitializerNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(VirtSpecifierSequenceNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(ClassNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("class", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(StructNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("struct", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(UnionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("union", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(PublicNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("public", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ProtectedNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("protected", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(PrivateNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("private", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(VirtualNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("virtual", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(OverrideNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("override", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(FinalNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("final", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(PureSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("=", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("0", node.ZeroPos());
    if (!Valid()) return;
    EndVisit(node);
}

// Concept:

void DefaultVisitor::Visit(ConceptDefinitionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("concept", node.GetSourcePos());
    if (!Valid()) return;
    node.ConceptName()->Accept(*this);
    if (!Valid()) return;
    node.Assign()->Accept(*this);
    if (!Valid()) return;
    node.ConstraintExpression()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(RequiresExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("requires", node.GetSourcePos());
    if (node.Params())
    {
        node.Params()->Accept(*this);
        if (!Valid()) return;
    }
    node.Body()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(RequirementBodyNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("{", node.LBracePos());
    if (!Valid()) return;
    VisitSequenceContent(node);
    if (!Valid()) return;
    VisitOperator("}", node.RBracePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(SimpleRequirementNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(TypeRequirementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("typename", node.GetSourcePos());
    if (node.NestedNameSpecifier())
    {
        node.NestedNameSpecifier()->Accept(*this);
        if (!Valid()) return;
    }
    node.TypeName()->Accept(*this);
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CompoundRequirementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("{", node.LBracePos());
    if (!Valid()) return;
    node.Expr()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("}", node.RBracePos());
    if (!Valid()) return;
    if (node.NoExcept())
    {
        node.NoExcept()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.ReturnTypeRequirement())
    {
        node.ReturnTypeRequirement()->Accept(*this);
        if (!Valid()) return;
    }
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ReturnTypeRequirementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("->", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NestedRequirementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("requires", node.GetSourcePos());
    if (!Valid()) return;
    node.Left()->Accept(*this);
    if (!Valid()) return;
    node.Right()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(TypeConstraintNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.ConceptName()->Accept(*this);
    if (!Valid()) return;
    if (node.HasTemplateArgumentList())
    {
        VisitOperator("<", node.LAnglePos());
        if (!Valid()) return;
        VisitListContent(node);
        if (!Valid()) return;
        VisitOperator(">", node.RAnglePos());
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(RequiresClauseNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("requires", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

// Declaration:

void DefaultVisitor::Visit(DeclarationSequenceNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(SimpleDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.DeclarationSpecifiers()->Accept(*this);
    if (!Valid()) return;
    if (node.InitDeclaratorList())
    {
        node.InitDeclaratorList()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Semicolon())
    {
        node.Semicolon()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(AsmDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.Asm()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.AsmText()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AsmNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("asm", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(LinkageSpecificationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    node.Extern()->Accept(*this);
    if (!Valid()) return;
    node.Linkage()->Accept(*this);
    if (!Valid()) return;
    if (node.LBracePos().IsValid())
    {
        VisitOperator("{", node.LBracePos());
        if (!Valid()) return;
        if (node.Declarations())
        {
            node.Declarations()->Accept(*this);
            if (!Valid()) return;
        }
        VisitOperator("}", node.RBracePos());
        if (!Valid()) return;
    }
    else
    {
        node.Declarations()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(NamespaceDefinitionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (node.Inline())
    {
        node.Inline()->Accept(*this);
        if (!Valid()) return;
    }
    node.Namespace()->Accept(*this);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.NamespaceName())
    {
        node.NamespaceName()->Accept(*this);
        if (!Valid()) return;
    }
    VisitOperator("{", node.LBracePos());
    if (!Valid()) return;
    node.NamespaceBody()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("}", node.RBracePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NamespaceBodyNode& node)
{
    if (!Valid()) return;
    if (node.Declarations())
    {
        BeginVisit(node);
        node.Declarations()->Accept(*this);
        if (!Valid()) return;
        EndVisit(node);
    }
}

void DefaultVisitor::Visit(NamespaceAliasDefinitionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("namespace", node.GetSourcePos());
    node.Id()->Accept(*this);
    if (!Valid()) return;
    node.Assign()->Accept(*this);
    if (!Valid()) return;
    node.QualifiedNamespaceSpecifier()->Accept(*this);
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(UsingDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    node.Using()->Accept(*this);
    if (!Valid()) return;
    node.Declarators()->Accept(*this);
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(UsingNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("using", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(UsingDeclaratorListNode& node)
{
    VisitList(node);
}

void DefaultVisitor::Visit(UsingEnumDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Using()->Accept(*this);
    if (!Valid()) return;
    node.ElaboratedEnumSpecifier()->Accept(*this);
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(UsingDirectiveNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.Using()->Accept(*this);
    if (!Valid()) return;
    node.Namespace()->Accept(*this);
    if (!Valid()) return;
    node.Id()->Accept(*this);
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NamespaceNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("namespace", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(StaticAssertDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.StaticAssert()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.ConstantExpr()->Accept(*this);
    if (!Valid()) return;
    if (node.Comma())
    {
        node.Comma()->Accept(*this);
        if (!Valid()) return;
        node.StringLiteral()->Accept(*this);
        if (!Valid()) return;
    }
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(StaticAssertNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("static_assert", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AliasDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Using()->Accept(*this);
    if (!Valid()) return;
    node.Identifier()->Accept(*this);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.Assign()->Accept(*this);
    if (!Valid()) return;
    node.DefiningTypeId()->Accept(*this);
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(EmptyDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(";", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AttributeDeclarationNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(InitDeclaratorListNode& node)
{
    VisitList(node);
}

void DefaultVisitor::Visit(InitDeclaratorNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(TrailingFunctionDeclaratorNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Declarator()->Accept(*this);
    if (!Valid()) return;
    node.Parameters()->Accept(*this);
    if (!Valid()) return;
    node.TrailingReturnType()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ParenthesizedDeclaratorNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Declarator()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AbstractDeclaratorNode& node)
{
    VisitSingleNode(node);
}

void DefaultVisitor::Visit(DeclSpecifierSequenceNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(FriendNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("friend", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(TypedefNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("typedef", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ConstExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("constexpr", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ConstEvalNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("consteval", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ConstInitNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("constinit", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(InlineNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("inline", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(StaticNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("static", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ThreadLocalNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("thread_local", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ExternNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("extern", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(MutableNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("mutable", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ExplicitNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("explicit", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ConditionalExplicitNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("explicit", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Condition()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
}

void DefaultVisitor::Visit(QualifiedPtrNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(PtrOperatorNode& node)
{
    VisitUnaryNode(node);
}

void DefaultVisitor::Visit(PtrDeclaratorNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(PackDeclaratorIdNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(ArrayDeclaratorNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("[", node.LBracketPos());
    if (!Valid()) return;
    if (node.Dimension())
    {
        node.Dimension()->Accept(*this);
        if (!Valid()) return;
    }
    VisitOperator("]", node.RBracketPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(FunctionDeclaratorNode& node)
{
    if (!Valid()) return;
    VisitUnaryNode(node);
    if (!Valid()) return;
    node.Params()->Accept(*this);
}

void DefaultVisitor::Visit(PrefixNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(TrailingQualifiersNode& node)
{
    if (!Valid()) return;
    node.Subject()->Accept(*this);
    if (!Valid()) return;
    VisitSequence(node);
}

void DefaultVisitor::Visit(TrailingAttributesNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(NoexceptSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.ConstantExpr())
    {
        VisitOperator("(", node.LParenPos());
        if (!Valid()) return;
        node.ConstantExpr()->Accept(*this);
        if (!Valid()) return;
        VisitOperator("}", node.RParenPos());
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(ThrowSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    VisitOperator("}", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

// Enum:

void DefaultVisitor::Visit(EnumSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.EnumHead()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("{", node.LBracePos());
    if (!Valid()) return;
    VisitListContent(node);
    if (!Valid()) return;
    VisitOperator("}", node.RBracePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(EnumHeadNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.EnumKey()->Accept(*this);
    if (!Valid()) return;
    node.EnumHeadName()->Accept(*this);
    if (!Valid()) return;
    if (node.EnumBase())
    {
        node.EnumBase()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(EnumBaseNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(":", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(EnumClassNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("enum", node.GetSourcePos());
    if (!Valid()) return;
    VisitKeyword("class", node.ClassPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(EnumStructNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("enum", node.GetSourcePos());
    if (!Valid()) return;
    VisitKeyword("struct", node.StructPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(EnumNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("enum", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(EnumeratorDefinitionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Enumerator()->Accept(*this);
    if (!Valid()) return;
    if (node.Value())
    {
        VisitOperator("=", node.AssignPos());
        if (!Valid()) return;
        node.Value()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(EnumeratorNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Identifier()->Accept(*this);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(ElaboratedEnumSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("enum", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(OpaqueEnumDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.EnumKey()->Accept(*this);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.EnumHeadName()->Accept(*this);
    if (!Valid()) return;
    if (node.EnumBase())
    {
        node.EnumBase()->Accept(*this);
        if (!Valid()) return;
    }
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

// Expression:

void DefaultVisitor::Visit(BinaryExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Left()->Accept(*this);
    if (!Valid()) return;
    node.Op()->Accept(*this);
    if (!Valid()) return;
    node.Right()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(UnaryExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Op()->Accept(*this);
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ExpressionListNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    VisitListContent(node);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AssignmentInitNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("=", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(YieldExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("co_yield", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ConditionalExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Condition()->Accept(*this);
    if (!Valid()) return;
    node.Quest()->Accept(*this);
    if (!Valid()) return;
    node.ThenExpr()->Accept(*this);
    if (!Valid()) return;
    node.Colon()->Accept(*this);
    if (!Valid()) return;
    node.ElseExpr()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CommaNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(",", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AssignNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(PlusAssignNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("+=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(MinusAssignNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("-=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(MulAssignNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("*=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DivAssignNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("/=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ModAssignNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("%=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(XorAssignNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("^=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AndAssignNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("&=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(OrAssignNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("|=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ShiftLeftAssignNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("<<=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ShiftRightAssignNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(">>=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(QuestNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("?", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ColonNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(":", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DisjunctionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("||", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ConjunctionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("&&", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(InclusiveOrNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("|", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ExclusiveOrNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("^", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AndNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("&", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(EqualNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("==", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NotEqualNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("!=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(LessNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("<", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(GreaterNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(">", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(LessOrEqualNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("<=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(GreaterOrEqualNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(">=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CompareNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("<=>", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ShiftLeftNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("<<", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ShiftRightNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(">>", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(PlusNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("+", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(MinusNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("-", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(MulNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("*", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DivNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("/", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ModNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("%", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DotStarNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(".*", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ArrowStarNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("->*", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CastExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.TypeId()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DerefNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("*", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AddrOfNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("&", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NotNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("!", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ComplementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("~", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(PrefixIncNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("++", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(PrefixDecNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("--", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AwaitExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("co_await", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(SizeOfTypeExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("sizeof", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(SizeOfPackExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("sizeof", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("...", node.EllipsisPos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(SizeOfUnaryExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("sizeof", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(AlignOfExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("alignof", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NoexceptExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("noexcept", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NewExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.ColonColonHead())
    {
        node.ColonColonHead()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("new", node.NewPos());
    if (!Valid()) return;
    if (node.Placement())
    {
        node.Placement()->Accept(*this);
        if (!Valid()) return;
    }
    node.Child()->Accept(*this);
    if (!Valid()) return;
    if (node.Initializer())
    {
        node.Initializer()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(NewPlacementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    VisitListContent(node);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ParenNewTypeIdNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.LParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NewTypeIdNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.TypeSpecifierSeq()->Accept(*this);
    if (!Valid()) return;
    if (node.NewDeclarator())
    {
        node.NewDeclarator()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(ArrayDeletePtrNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.ColonColonHead())
    {
        node.ColonColonHead()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("delete", node.DeletePos());
    if (!Valid()) return;
    VisitOperator("[", node.LBracketPos());
    if (!Valid()) return;
    VisitOperator("]", node.RBracketPos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DeletePtrNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.ColonColonHead())
    {
        node.ColonColonHead()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("delete", node.DeletePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(SubscriptExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("[", node.LBracketPos());
    if (!Valid()) return;
    node.Index()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("]", node.RBracketPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(InvokeExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Subject()->Accept(*this);
    if (!Valid()) return;
    if (node.LParenPos().IsValid())
    {
        VisitOperator("(", node.LParenPos());
        if (!Valid()) return;
    }
    VisitListContent(node);
    if (!Valid()) return;
    if (node.RParenPos().IsValid())
    {
        VisitOperator(")", node.RParenPos());
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(PairNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(DotNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(".", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ArrowNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("->", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(MemberExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    node.Op()->Accept(*this);
    if (!Valid()) return;
    node.Id()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(PostfixIncExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("++", node.OpPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(PostfixDecExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("--", node.OpPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(TypeIdExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("typeid", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DynamicCastNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("dynamic_cast", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(StaticCastNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("static_cast", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ReinterpretCastNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("reinterpret_cast", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ConstCastNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("const_cast", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CppCastExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Op()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("<", node.LAnglePos());
    if (!Valid()) return;
    node.TypeId()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(">", node.RAnglePos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ThisNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("this", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ParenthesizedExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(FoldExprNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    VisitSequence(node);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NewDeclaratorNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(ArrayNewDeclaratorNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(NewInitializerNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    VisitListContent(node);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
}

void DefaultVisitor::Visit(BracedInitListNode& node)
{
    VisitList(node);
}

void DefaultVisitor::Visit(DesignatedInitializerNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(DesignatorNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(".", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(EllipsisNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("...", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

// Function:

void DefaultVisitor::Visit(FunctionDefinitionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.DeclSpecifiers())
    {
        node.DeclSpecifiers()->Accept(*this);
        if (!Valid()) return;
    }
    node.Declarator()->Accept(*this);
    if (!Valid()) return;
    if (node.Specifiers())
    {
        node.Specifiers()->Accept(*this);
        if (!Valid()) return;
    }
    node.FunctionBody()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(FunctionBodyNode& node)
{
    VisitUnaryNode(node);
}

void DefaultVisitor::Visit(DefaultNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("default", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DeleteNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("delete", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DefaultedOrDeletedFunctionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Assign()->Accept(*this);
    if (!Valid()) return;
    node.DefaultOrDelete()->Accept(*this);
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NoDeclSpecFunctionDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.Declarator()->Accept(*this);
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(OperatorNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("operator", node.GetSourcePos());
    EndVisit(node);
}

void DefaultVisitor::Visit(NewArrayOpNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("new", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("[", node.LBracketPos());
    if (!Valid()) return;
    VisitOperator("]", node.RBracketPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NewOpNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("new", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DeleteArrayOpNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("delete", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("[", node.LBracketPos());
    if (!Valid()) return;
    VisitOperator("]", node.RBracketPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DeleteOpNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("delete", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CoAwaitOpNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("co_await", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(InvokeOpNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("()", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(SubscriptOpNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("[]", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(OperatorFunctionIdNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(ConversionFunctionIdNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(ConversionTypeIdNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.TypeSpecifierSeq()->Accept(*this);
    if (!Valid()) return;
    if (node.ConversionDeclarator())
    {
        node.ConversionDeclarator()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(ConversionDeclaratorNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.PtrOp()->Accept(*this);
    if (!Valid()) return;
    if (node.ConversionDeclarator())
    {
        node.ConversionDeclarator()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(DestructorIdNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("~", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ParameterNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.DeclSpecifiers()->Accept(*this);
    if (!Valid()) return;
    if (node.Declarator())
    {
        node.Declarator()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Assign())
    {
        node.Assign()->Accept(*this);
        if (!Valid()) return;
        node.Initializer()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(ParameterListNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    VisitListContent(node);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NoexceptNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("noexcept", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(FunctionTryBlockNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("try", node.GetSourcePos());
    if (!Valid()) return;
    if (node.CtorInitializer())
    {
        node.CtorInitializer()->Accept(*this);
        if (!Valid()) return;
    }
    node.TryBlock()->Accept(*this);
    if (!Valid()) return;
    node.Handlers()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

// Identifier:

void DefaultVisitor::Visit(IdentifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitIdentifier(node.Str(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(UnnamedNode& node)
{
    VisitSingleNode(node);
}

void DefaultVisitor::Visit(ColonColonNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("::", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NestedNameSpecifierNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(QualifiedIdNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(IdentifierListNode& node)
{
    VisitList(node);
}

void DefaultVisitor::Visit(ModuleNameNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitIdentifier(node.Str(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

// Lambda:

void DefaultVisitor::Visit(LambdaExpressionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Introducer()->Accept(*this);
    if (!Valid()) return;
    if (node.TemplateParams())
    {
        node.TemplateParams()->Accept(*this);
        if (!Valid()) return;
    }
    node.Declarator()->Accept(*this);
    if (!Valid()) return;
    node.Body()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(LambdaIntroducerNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("[", node.LBracketPos());
    if (!Valid()) return;
    if (node.Capture())
    {
        node.Capture()->Accept(*this);
        if (!Valid()) return;
    }
    VisitOperator("]", node.RBracketPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(LambdaCaptureNode& node)
{
    VisitList(node);
}

void DefaultVisitor::Visit(DefaultRefCaptureNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("&", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DefaultCopyCaptureNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("=", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ByRefCaptureNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("&", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(SimpleCaptureNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.ByRefCapture())
    {
        node.ByRefCapture()->Accept(*this);
        if (!Valid()) return;
    }
    node.Identifier()->Accept(*this);
    if (!Valid()) return;
    if (node.Ellipsis())
    {
        node.Ellipsis()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(CurrentObjectCopyCapture& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("*", node.GetSourcePos());
    if (!Valid()) return;
    VisitKeyword("this", node.ThisPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CurrentObjectByRefCapture& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("this", node.ThisPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(InitCaptureNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.ByRefCapture())
    {
        node.ByRefCapture()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Ellipsis())
    {
        node.Ellipsis()->Accept(*this);
        if (!Valid()) return;
    }
    node.Identifier()->Accept(*this);
    if (!Valid()) return;
    node.Initializer()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(LambdaDeclaratorNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.ParameterList())
    {
        node.ParameterList()->Accept(*this);
        if (!Valid()) return;
    }
    node.Specifiers()->Accept(*this);
    if (!Valid()) return;
    if (node.RequiresClause())
    {
        node.RequiresClause()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(LambdaSpecifiersNode& node)
{
    if (!Valid()) return;
    if (!node.IsEmpty())
    {
        BeginVisit(node);
        if (!Valid()) return;
        if (node.DeclSpecifiers())
        {
            node.DeclSpecifiers()->Accept(*this);
            if (!Valid()) return;
        }
        if (node.NoexceptionSpecifier())
        {
            node.NoexceptionSpecifier()->Accept(*this);
            if (!Valid()) return;
        }
        if (node.Attributes())
        {
            node.Attributes()->Accept(*this);
            if (!Valid()) return;
        }
        if (node.TrailingReturnType())
        {
            node.TrailingReturnType()->Accept(*this);
            if (!Valid()) return;
        }
        EndVisit(node);
    }
}

void DefaultVisitor::Visit(LambdaTemplateParamsNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.TemplateParams()->Accept(*this);
    if (!Valid()) return;
    if (node.RequiresClause())
    {
        node.RequiresClause()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

// Literal:

void DefaultVisitor::Visit(IntegerLiteralNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitLiteral(node.Rep(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(FloatingLiteralNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitLiteral(node.Rep(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CharacterLiteralNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitLiteral(node.Rep(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(StringLiteralNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitLiteral(node.Rep(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(RawStringLiteralNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitLiteral(node.Rep(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(BooleanLiteralNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitLiteral(node.Rep(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(NullPtrLiteralNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitLiteral(node.Rep(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(UserDefinedLiteraNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(LiteralOperatorIdNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("operator", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("\"\"", node.StringLitPos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

// Module:

void DefaultVisitor::Visit(ModuleDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Export())
    {
        node.Export()->Accept(*this);
        if (!Valid()) return;
    }
    node.Module()->Accept(*this);
    if (!Valid()) return;
    node.ModuleName()->Accept(*this);
    if (!Valid()) return;
    if (node.ModulePartition())
    {
        node.ModulePartition()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ExportDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Export()->Accept(*this);
    if (!Valid()) return;
    if (node.LBracePos().IsValid())
    {
        VisitOperator("{", node.LBracePos());
        if (!Valid()) return;
        if (node.Subject())
        {
            node.Subject()->Accept(*this);
            if (!Valid()) return;
        }
        VisitOperator("}", node.RBracePos());
        if (!Valid()) return;
    }
    else
    {
        node.Subject()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(ExportNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("export", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ImportNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("import", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ImportDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Import()->Accept(*this);
    if (!Valid()) return;
    node.Subject()->Accept(*this);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ModulePartitionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(":", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ModuleNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("module", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(GlobalModuleFragmentNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Module()->Accept(*this);
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    if (node.Declarations())
    {
        node.Declarations()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(PrivateModuleFragmentNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Module()->Accept(*this);
    if (!Valid()) return;
    node.Colon()->Accept(*this);
    if (!Valid()) return;
    node.Private()->Accept(*this);
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    if (node.Declarations())
    {
        node.Declarations()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(AngleHeaderName& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitHeaderName(node.Rep(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(QuoteHeaderName& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitHeaderName(node.Rep(), node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

// Qualifier:

void DefaultVisitor::Visit(ConstNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("const", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(VolatileNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("volatile", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(LvalueRefNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("&", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(RvalueRefNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("&&", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(PtrNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("*", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CVQualifierSequenceNode& node)
{
    VisitSequence(node);
}

// SimpleType:

void DefaultVisitor::Visit(CharNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("char", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(Char8Node& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("char8_t", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(Char16Node& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("char16_t", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(Char32Node& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("char32_t", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(WCharNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("wchar_t", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(BoolNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("bool", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ShortNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("short", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(IntNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("int", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(LongNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("long", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(SignedNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("signed", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(UnsignedNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("unsigned", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(FloatNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("float", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DoubleNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("double", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(VoidNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("void", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

// Statement:

void DefaultVisitor::Visit(LabeledStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.Label()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(":", node.ColonPos());
    if (!Valid()) return;
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CaseStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("case", node.CasePos());
    if (!Valid()) return;
    node.CaseExpression()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(":", node.ColonPos());
    if (!Valid()) return;
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DefaultStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("default", node.DefaultPos());
    if (!Valid()) return;
    VisitOperator(":", node.ColonPos());
    if (!Valid()) return;
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CompoundStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitOperator("{", node.LBracePos());
    if (!Valid()) return;
    VisitSequenceContent(node);
    if (!Valid()) return;
    VisitOperator("}", node.RBracePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(IfStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("if", node.IfPos());
    if (!Valid()) return;
    if (node.IsConstExprIf())
    {
        VisitKeyword("constexpr", node.ConstExprSourcePos());
        if (!Valid()) return;
    }
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
        if (!Valid()) return;
    }
    node.Condition()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    node.ThenStatement()->Accept(*this);
    if (!Valid()) return;
    if (node.ElseStatement())
    {
        VisitKeyword("else", node.ElsePos());
        if (!Valid()) return;
        node.ElseStatement()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(SwitchStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("switch", node.SwitchPos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
        if (!Valid()) return;
    }
    node.Condition()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(WhileStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("while", node.WhilePos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Condition()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DoStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("do", node.DoPos());
    if (!Valid()) return;
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    VisitKeyword("while", node.WhilePos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Expression()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(RangeForStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("for", node.ForPos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    if (node.InitStatement())
    {
        node.InitStatement()->Accept(*this);
        if (!Valid()) return;
    }
    node.Declaration()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(":", node.ColonPos());
    if (!Valid()) return;
    node.Initializer()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ForRangeDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.Left()->Accept(*this);
    if (!Valid()) return;
    node.Right()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(StructuredBindingNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.DeclSpecifiers()->Accept(*this);
    if (!Valid()) return;
    if (node.RefQualifier())
    {
        node.RefQualifier()->Accept(*this);
        if (!Valid()) return;
    }
    VisitOperator("[", node.LBracketPos());
    if (!Valid()) return;
    node.Identifiers()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("]", node.RBracketPos());
    if (!Valid()) return;
    if (node.Initializer())
    {
        node.Initializer()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Semicolon())
    {
        node.Semicolon()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(ForStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("for", node.ForPos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.InitStatement()->Accept(*this);
    if (!Valid()) return;
    if (node.Condition())
    {
        node.Condition()->Accept(*this);
        if (!Valid()) return;
    }
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    if (node.LoopExpr())
    {
        node.LoopExpr()->Accept(*this);
        if (!Valid()) return;
    }
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    node.Statement()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(BreakStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("break", node.BreakPos());
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ContinueStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("continue", node.ContinuePos());
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ReturnStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("return", node.ReturnPos());
    if (!Valid()) return;
    if (node.ReturnValue())
    {
        node.ReturnValue()->Accept(*this);
        if (!Valid()) return;
    }
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(CoReturnStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("co_return", node.CoReturnPos());
    if (!Valid()) return;
    if (node.ReturnValue())
    {
        node.ReturnValue()->Accept(*this);
        if (!Valid()) return;
    }
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(GotoStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("goto", node.GotoPos());
    if (!Valid()) return;
    node.Target()->Accept(*this);
    if (!Valid()) return;
    node.Semimcolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(TryStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    VisitKeyword("try", node.TryPos());
    if (!Valid()) return;
    node.TryBlock()->Accept(*this);
    if (!Valid()) return;
    node.Handlers()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(HandlerSequenceNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(HandlerNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("catch", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Exception()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    node.CatchBlock()->Accept(*this);
}

void DefaultVisitor::Visit(ExceptionDeclarationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.TypeSpecifiers())
    {
        node.TypeSpecifiers()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Declarator())
    {
        node.Declarator()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Ellipsis())
    {
        node.Ellipsis()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(ExpressionStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Expression())
    {
        node.Expression()->Accept(*this);
        if (!Valid()) return;
    }
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DeclarationStatementNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Declaration()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(InitConditionNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.DeclSpecifiers()->Accept(*this);
    if (!Valid()) return;
    node.Declarator()->Accept(*this);
    if (!Valid()) return;
    node.Initializer()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(SemicolonNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator(";", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

// Template:

void DefaultVisitor::Visit(TemplateDeclarationNode& node)
{
    VisitBinaryNode(node);
}

void DefaultVisitor::Visit(TemplateHeadNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("template", node.GetSourcePos());
    if (!Valid()) return;
    node.TemplateParamList()->Accept(*this);
    if (!Valid()) return;
    if (node.RequiresClause())
    {
        node.RequiresClause()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(TemplateParameterListNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("<", node.LAnglePos());
    if (!Valid()) return;
    VisitListContent(node);
    if (!Valid()) return;
    VisitOperator(">", node.RAnglePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(TypeParameterNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.TemplateHead())
    {
        node.TemplateHead()->Accept(*this);
        if (!Valid()) return;
    }
    node.TypeConstraint()->Accept(*this);
    if (!Valid()) return;
    if (node.Ellipsis())
    {
        node.Ellipsis()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Identifier())
    {
        node.Identifier()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.Assign())
    {
        node.Assign()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.TypeId())
    {
        node.TypeId()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(TemplateIdNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.TemplateName()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("<", node.LAnglePos());
    if (!Valid()) return;
    VisitListContent(node);
    if (!Valid()) return;
    VisitOperator(">", node.RAnglePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(TypenameNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("typename", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DeductionGuideNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.ExplicitSpecifier())
    {
        node.ExplicitSpecifier()->Accept(*this);
        if (!Valid()) return;
    }
    node.TemplateName()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Parameters()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    node.Arrow()->Accept(*this);
    if (!Valid()) return;
    node.TemplateId()->Accept(*this);
    if (!Valid()) return;
    node.Semicolon()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ExplicitInstantiationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Extern())
    {
        node.Extern()->Accept(*this);
        if (!Valid()) return;
    }
    node.Template()->Accept(*this);
    if (!Valid()) return;
    node.Declaration()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(TemplateNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("template", node.GetSourcePos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ExplicitSpecializationNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.Template()->Accept(*this);
    if (!Valid()) return;
    VisitOperator("<", node.LAnglePos());
    if (!Valid()) return;
    VisitOperator(">", node.RAnglePos());
    if (!Valid()) return;
    node.Declaration()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

// TranslationUnit:

void DefaultVisitor::Visit(TranslationUnitNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.Unit())
    {
        node.Unit()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(ModuleUnitNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.GlobalModuleFragment())
    {
        node.GlobalModuleFragment()->Accept(*this);
        if (!Valid()) return;
    }
    node.ModuleDeclaration()->Accept(*this);
    if (!Valid()) return;
    if (node.Declarations())
    {
        node.Declarations()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.PrivateModuleFragment())
    {
        node.PrivateModuleFragment()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

// Type:

void DefaultVisitor::Visit(TypeSpecifierSequenceNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(TypenameSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("typename", node.GetSourcePos());
    if (!Valid()) return;
    node.NestedNameSpecifier()->Accept(*this);
    if (!Valid()) return;
    if (node.TemplateNode())
    {
        node.TemplateNode()->Accept(*this);
        if (!Valid()) return;
    }
    node.Id()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(TypeIdNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.TypeSpecifiers()->Accept(*this);
    if (!Valid()) return;
    if (node.Declarator())
    {
        node.Declarator()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(DefiningTypeIdNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.DefiningTypeSpecifiers()->Accept(*this);
    if (!Valid()) return;
    if (node.AbstractDeclarator())
    {
        node.AbstractDeclarator()->Accept(*this);
        if (!Valid()) return;
    }
    EndVisit(node);
}

void DefaultVisitor::Visit(DefiningTypeSpecifierSequenceNode& node)
{
    VisitSequence(node);
}

void DefaultVisitor::Visit(TrailingReturnTypeNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitOperator("->", node.GetSourcePos());
    if (!Valid()) return;
    node.Child()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(ElaboratedTypeSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    node.ClassKey()->Accept(*this);
    if (!Valid()) return;
    if (node.Attributes())
    {
        node.Attributes()->Accept(*this);
        if (!Valid()) return;
    }
    node.Id()->Accept(*this);
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(DeclTypeSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    VisitKeyword("delctype", node.GetSourcePos());
    if (!Valid()) return;
    VisitOperator("(", node.LParenPos());
    if (!Valid()) return;
    node.Expression()->Accept(*this);
    if (!Valid()) return;
    VisitOperator(")", node.RParenPos());
    if (!Valid()) return;
    EndVisit(node);
}

void DefaultVisitor::Visit(PlaceholderTypeSpecifierNode& node)
{
    if (!Valid()) return;
    BeginVisit(node);
    if (!Valid()) return;
    if (node.TypeConstraint())
    {
        node.TypeConstraint()->Accept(*this);
        if (!Valid()) return;
    }
    if (node.IsDeclType())
    {
        VisitKeyword("delctype", node.DeclTypePos());
        if (!Valid()) return;
        VisitOperator("(", node.LParenPos());
        if (!Valid()) return;
        VisitKeyword("auto", node.AutoPos());
        if (!Valid()) return;
        VisitOperator(")", node.RParenPos());
        if (!Valid()) return;
    }
    else
    {
        VisitKeyword("auto", node.AutoPos());
        if (!Valid()) return;
    }
    EndVisit(node);
}

} // namespace otava::ast
