// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.enums;

import std.core;
import soul.cpp20.ast.node;

export namespace soul::cpp20::ast {

class EnumSpecifierNode : public ListNode
{
public:
    EnumSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    EnumSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* enumHead_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* EnumHead() const { return enumHead.get(); }
    void SetLBracePos(const soul::ast::SourcePos& lbPos_) { lbPos = lbPos_; }
    void SetRBracePos(const soul::ast::SourcePos& rbPos_) { rbPos = rbPos_; }
    const soul::ast::SourcePos& LBracePos() const { return lbPos; }
    const soul::ast::SourcePos& RBracePos() const { return rbPos; }
private:
    std::unique_ptr<Node> enumHead;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class EnumHeadNode : public CompoundNode
{
public:
    EnumHeadNode(const soul::ast::SourcePos& sourcePos_);
    EnumHeadNode(const soul::ast::SourcePos& sourcePos_, Node* enumKey_, Node* enumHeadName_, Node* enumBase_, Node* attributes_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* EnumKey() const { return enumKey.get(); }
    Node* EnumHeadName() const { return enumHeadName.get(); }
    Node* EnumBase() const { return enumBase.get(); }
    Node* Attributes() const { return attributes.get(); }
private:
    std::unique_ptr<Node> enumKey;
    std::unique_ptr<Node> enumHeadName;
    std::unique_ptr<Node> enumBase;
    std::unique_ptr<Node> attributes;
};

class EnumBaseNode : public UnaryNode
{
public:
    EnumBaseNode(const soul::ast::SourcePos& sourcePos_);
    EnumBaseNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class EnumClassNode : public CompoundNode
{
public:
    EnumClassNode(const soul::ast::SourcePos& sourcePos_);
    EnumClassNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& classPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& ClassPos() const { return classPos; }
private:
    soul::ast::SourcePos classPos;
};

class EnumStructNode : public CompoundNode
{
public:
    EnumStructNode(const soul::ast::SourcePos& sourcePos_);
    EnumStructNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& structPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& StructPos() const { return structPos; }
private:
    soul::ast::SourcePos structPos;
};

class EnumNode : public Node
{
public:
    EnumNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class EnumeratorDefinitionNode : public CompoundNode
{
public:
    EnumeratorDefinitionNode(const soul::ast::SourcePos& sourcePos_);
    EnumeratorDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* enumerator_, Node* value_, const soul::ast::SourcePos& assignPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Enumerator() const { return enumerator.get(); }
    Node* Value() const { return value.get(); }
    const soul::ast::SourcePos& AssignPos() const { return assignPos; }
private:
    std::unique_ptr<Node> enumerator;
    std::unique_ptr<Node> value;
    soul::ast::SourcePos assignPos;
};

class EnumeratorNode : public CompoundNode
{
public:
    EnumeratorNode(const soul::ast::SourcePos& sourcePos_);
    EnumeratorNode(const soul::ast::SourcePos& sourcePos_, Node* identifier_, Node* attributes_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Identifier() const { return identifier.get(); }
    Node* Attributes() const { return attributes.get(); }
private:
    std::unique_ptr<Node> identifier;
    std::unique_ptr<Node> attributes;
};

class ElaboratedEnumSpecifierNode : public UnaryNode
{
public:
    ElaboratedEnumSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    ElaboratedEnumSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* enumName_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class OpaqueEnumDeclarationNode : public CompoundNode
{
public:
    OpaqueEnumDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    OpaqueEnumDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* enumKey_, Node* enumHeadName_, Node* enumBase_, Node* attributes_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* EnumKey() const { return enumKey.get(); }
    Node* EnumHeadName() const { return enumHeadName.get(); }
    Node* EnumBase() const { return enumBase.get(); }
    Node* Attributes() const { return attributes.get(); }
    Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> enumKey;
    std::unique_ptr<Node> enumHeadName;
    std::unique_ptr<Node> enumBase;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
};

} // namespace soul::cpp20::ast
