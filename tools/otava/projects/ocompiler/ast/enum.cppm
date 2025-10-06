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
    EnumSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    EnumSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* enumHead_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* EnumHead() const { return enumHead.get(); }
    inline void SetLBracePos(const soul::ast::SourcePos& lbPos_) { lbPos = lbPos_; }
    inline void SetRBracePos(const soul::ast::SourcePos& rbPos_) { rbPos = rbPos_; }
    inline const soul::ast::SourcePos& LBracePos() const { return lbPos; }
    inline const soul::ast::SourcePos& RBracePos() const { return rbPos; }
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
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* EnumKey() const { return enumKey.get(); }
    inline Node* EnumHeadName() const { return enumHeadName.get(); }
    inline Node* EnumBase() const { return enumBase.get(); }
    inline Node* Attributes() const { return attributes.get(); }
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
    std::expected<bool, int> Read(Reader& reader) override;
    inline const soul::ast::SourcePos& ClassPos() const { return classPos; }
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
    std::expected<bool, int> Read(Reader& reader) override;
    inline const soul::ast::SourcePos& StructPos() const { return structPos; }
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
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* Enumerator() const { return enumerator.get(); }
    inline Node* Value() const { return value.get(); }
    inline const soul::ast::SourcePos& AssignPos() const { return assignPos; }
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
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* Identifier() const { return identifier.get(); }
    inline Node* Attributes() const { return attributes.get(); }
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
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* EnumKey() const { return enumKey.get(); }
    inline Node* EnumHeadName() const { return enumHeadName.get(); }
    inline Node* EnumBase() const { return enumBase.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> enumKey;
    std::unique_ptr<Node> enumHeadName;
    std::unique_ptr<Node> enumBase;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
};

} // namespace otava::ast
