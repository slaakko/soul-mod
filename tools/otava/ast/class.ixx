// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.classes;

import std.core;
import otava.ast.node;
import soul.ast.lexer.pos.pair;

export namespace otava::ast {

class ClassSpecifierNode : public SequenceNode
{
public:
    ClassSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    ClassSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* classHead_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* ClassHead() const { return classHead.get(); }
    void SetLBracePos(const soul::ast::SourcePos& lbPos_) { lbPos = lbPos_; }
    void SetRBracePos(const soul::ast::SourcePos& rbPos_) { rbPos = rbPos_; }
    const soul::ast::SourcePos& LBracePos() const { return lbPos; }
    const soul::ast::SourcePos& RBracePos() const { return rbPos; }
    bool Complete() const { return complete; }
    void SetComplete() { complete = true; }
private:
    std::unique_ptr<Node> classHead;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
    bool complete;
};

class ClassHeadNode : public CompoundNode
{
public:
    ClassHeadNode(const soul::ast::SourcePos& sourcePos_);
    ClassHeadNode(const soul::ast::SourcePos& sourcePos_, Node* classKey_, Node* classHeadName_, Node* classVirtSpecifier_, Node* baseClause_, Node* attributes_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* ClassKey() const { return classKey.get(); }
    Node* ClassHeadName() const { return classHeadName.get(); }
    Node* ClassVirtSpecifier() const { return classVirtSpecifier.get(); }
    Node* BaseClause() const { return baseClause.get(); }
    Node* Attibutes() const { return attributes.get(); }
private:
    std::unique_ptr<Node> classKey;
    std::unique_ptr<Node> classHeadName;
    std::unique_ptr<Node> classVirtSpecifier;
    std::unique_ptr<Node> baseClause;
    std::unique_ptr<Node> attributes;
};

class BaseClauseNode : public UnaryNode
{
public:
    BaseClauseNode(const soul::ast::SourcePos& sourcePos_);
    BaseClauseNode(const soul::ast::SourcePos& sourcePos_, Node* baseSpecifierList_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class BaseSpecifierListNode : public ListNode
{
public:
    BaseSpecifierListNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class BaseSpecifierNode : public CompoundNode
{
public:
    BaseSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    BaseSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* classOrDeclType_, Node* accessSpecifier_, Node* virtualSpecifier_, Node* attributes_, bool virtualFirst_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* ClassOrDeclType() const { return classOrDeclType.get(); }
    Node* AccessSpecifier() const { return accessSpecifier.get(); }
    Node* VirtualSpecifier() const { return virtualSpecifier.get(); }
    Node* Attributes() const { return attributes.get(); }
    bool VirtualFirst() const { return virtualFirst; }
private:
    std::unique_ptr<Node> classOrDeclType;
    std::unique_ptr<Node> accessSpecifier;
    std::unique_ptr<Node> virtualSpecifier;
    std::unique_ptr<Node> attributes;
    bool virtualFirst;
};

class BeginAccessGroupNode : public UnaryNode
{
public:
    BeginAccessGroupNode(const soul::ast::SourcePos& sourcePos_);
    BeginAccessGroupNode(const soul::ast::SourcePos& sourcePos_, Node* accessSpecifier_, const soul::ast::SourcePos& colonPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& ColonPos() const { return colonPos; }
private:
    soul::ast::SourcePos colonPos;
};

class MemberDeclarationNode : public CompoundNode
{
public:
    MemberDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    MemberDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* declSpecifiers_, Node* memberDeclarators_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Attributes() const { return attributes.get(); }
    Node* DeclSpecifiers() const { return declSpecifiers.get(); }
    Node* MemberDeclarators() const { return memberDeclarators.get(); }
    Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> declSpecifiers;
    std::unique_ptr<Node> memberDeclarators;
    std::unique_ptr<Node> semicolon;
};

class MemberDeclaratorListNode : public ListNode
{
public:
    MemberDeclaratorListNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ConstructorNode : public BinaryNode
{
public:
    ConstructorNode(const soul::ast::SourcePos& sourcePos_);
    ConstructorNode(const soul::ast::SourcePos& sourcePos_, Node* constructorInitializer_, Node* compoundStatement_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ConstructorInitializerNode : public CompoundNode
{
public:
    ConstructorInitializerNode(const soul::ast::SourcePos& sourcePos_);
    ConstructorInitializerNode(const soul::ast::SourcePos& sourcePos_, Node* memberInitializerList_);
    Node* MemberInitializerListNode() const { return memberInitializerListNode.get(); }
    void SetMemberInitializerListNode(Node* memberInitializerListNode_);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void SetLexerPosPair(const soul::ast::lexer::pos::pair::LexerPosPair& lexerPosPair_);
    const soul::ast::lexer::pos::pair::LexerPosPair& GetLexerPosPair() const { return lexerPosPair; }
    void* FunctionScope() const { return functionScope; }
    void SetFunctionScope(void* functionScope_) { functionScope = functionScope_; }
private:
    std::unique_ptr<Node> memberInitializerListNode;
    soul::ast::lexer::pos::pair::LexerPosPair lexerPosPair;
    void* functionScope;
};

class MemberInitializerListNode : public ListNode
{
public:
    MemberInitializerListNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class MemberInitializerNode : public BinaryNode
{
public:
    MemberInitializerNode(const soul::ast::SourcePos& sourcePos_);
    MemberInitializerNode(const soul::ast::SourcePos& sourcePos_, Node* id_, Node* initializer_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class VirtSpecifierSequenceNode : public SequenceNode
{
public:
    VirtSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ClassNode : public Node
{
public:
    ClassNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class StructNode : public Node
{
public:
    StructNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class UnionNode : public Node
{
public:
    UnionNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class PublicNode : public Node
{
public:
    PublicNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ProtectedNode : public Node
{
public:
    ProtectedNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class PrivateNode : public Node
{
public:
    PrivateNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class VirtualNode : public Node
{
public:
    VirtualNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class OverrideNode : public Node
{
public:
    OverrideNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class FinalNode : public Node
{
public:
    FinalNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class PureSpecifierNode : public Node
{
public:
    PureSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    PureSpecifierNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& zeroPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& ZeroPos() const { return zeroPos; }
private:
    soul::ast::SourcePos zeroPos;
};

} // namespace otava::ast
