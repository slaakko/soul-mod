// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.enums;

import std;
import otava.ast.node;

export namespace otava::ast {

class EnumSpecifierNode : public ListNode
{
public:
    EnumSpecifierNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    EnumSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* enumHead_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* EnumHead() const noexcept { return enumHead.get(); }
    inline void SetLBracePos(const soul::ast::SourcePos& lbPos_) noexcept { lbPos = lbPos_; }
    inline void SetRBracePos(const soul::ast::SourcePos& rbPos_) noexcept { rbPos = rbPos_; }
    inline const soul::ast::SourcePos& LBracePos() const noexcept { return lbPos; }
    inline const soul::ast::SourcePos& RBracePos() const noexcept { return rbPos; }
private:
    std::unique_ptr<Node> enumHead;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class EnumHeadNode : public CompoundNode
{
public:
    EnumHeadNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    EnumHeadNode(const soul::ast::SourcePos& sourcePos_, Node* enumKey_, Node* enumHeadName_, Node* enumBase_, Node* attributes_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* EnumKey() const noexcept { return enumKey.get(); }
    inline Node* EnumHeadName() const noexcept { return enumHeadName.get(); }
    inline Node* EnumBase() const noexcept { return enumBase.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
private:
    std::unique_ptr<Node> enumKey;
    std::unique_ptr<Node> enumHeadName;
    std::unique_ptr<Node> enumBase;
    std::unique_ptr<Node> attributes;
};

class EnumBaseNode : public UnaryNode
{
public:
    EnumBaseNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    EnumBaseNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class EnumClassNode : public CompoundNode
{
public:
    EnumClassNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    EnumClassNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& classPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& ClassPos() const noexcept { return classPos; }
private:
    soul::ast::SourcePos classPos;
};

class EnumStructNode : public CompoundNode
{
public:
    EnumStructNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    EnumStructNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& structPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& StructPos() const noexcept { return structPos; }
private:
    soul::ast::SourcePos structPos;
};

class EnumNode : public Node
{
public:
    EnumNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class EnumeratorDefinitionNode : public CompoundNode
{
public:
    EnumeratorDefinitionNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    EnumeratorDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* enumerator_, Node* value_, const soul::ast::SourcePos& assignPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Enumerator() const noexcept { return enumerator.get(); }
    inline Node* GetValue() const noexcept { return value.get(); }
    inline const soul::ast::SourcePos& AssignPos() const noexcept { return assignPos; }
private:
    std::unique_ptr<Node> enumerator;
    std::unique_ptr<Node> value;
    soul::ast::SourcePos assignPos;
};

class EnumeratorNode : public CompoundNode
{
public:
    EnumeratorNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    EnumeratorNode(const soul::ast::SourcePos& sourcePos_, Node* identifier_, Node* attributes_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Identifier() const noexcept { return identifier.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
private:
    std::unique_ptr<Node> identifier;
    std::unique_ptr<Node> attributes;
};

class ElaboratedEnumSpecifierNode : public UnaryNode
{
public:
    ElaboratedEnumSpecifierNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ElaboratedEnumSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* enumName_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class OpaqueEnumDeclarationNode : public CompoundNode
{
public:
    OpaqueEnumDeclarationNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    OpaqueEnumDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* enumKey_, Node* enumHeadName_, Node* enumBase_, Node* attributes_, Node* semicolon_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* EnumKey() const noexcept { return enumKey.get(); }
    inline Node* EnumHeadName() const noexcept { return enumHeadName.get(); }
    inline Node* EnumBase() const noexcept { return enumBase.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
private:
    std::unique_ptr<Node> enumKey;
    std::unique_ptr<Node> enumHeadName;
    std::unique_ptr<Node> enumBase;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
};

} // namespace otava::ast
