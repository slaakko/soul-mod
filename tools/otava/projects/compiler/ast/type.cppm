// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.type;

import std;
import otava.ast.node;
import otava.ast.reader;

export namespace otava::ast {

class TypeSpecifierSequenceNode : public SequenceNode
{
public:
    TypeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TypenameSpecifierNode : public CompoundNode
{
public:
    TypenameSpecifierNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    TypenameSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* id_, Node* templateNode_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* NestedNameSpecifier() const noexcept { return nns.get(); }
    inline Node* Id() const noexcept { return id.get(); }
    inline Node* TemplateNode() const noexcept { return templateNode.get(); }
private:
    std::unique_ptr<Node> nns;
    std::unique_ptr<Node> id;
    std::unique_ptr<Node> templateNode;
};

class TypeIdNode : public CompoundNode
{
public:
    TypeIdNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    TypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_, Node* declarator_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TypeSpecifiers() const noexcept { return typeSpecifiers.get(); }
    inline Node* Declarator() const noexcept { return declarator.get(); }
private:
    std::unique_ptr<Node> typeSpecifiers;
    std::unique_ptr<Node> declarator;
};

class DefiningTypeIdNode : public CompoundNode
{
public:
    DefiningTypeIdNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    DefiningTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* definingTypeSpecifiers_, Node* abstractDeclarator_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* DefiningTypeSpecifiers() const noexcept { return definingTypeSpecifiers.get(); }
    inline Node* AbstractDeclarator() const noexcept { return abstractDeclarator.get(); }
private:
    std::unique_ptr<Node> definingTypeSpecifiers;
    std::unique_ptr<Node> abstractDeclarator;
};

class DefiningTypeSpecifierSequenceNode : public SequenceNode
{
public:
    DefiningTypeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TrailingReturnTypeNode : public UnaryNode
{
public:
    TrailingReturnTypeNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    TrailingReturnTypeNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ElaboratedTypeSpecifierNode : public CompoundNode
{
public:
    ElaboratedTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ElaboratedTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* classKey_, Node* id_, Node* attributes_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ClassKey() const noexcept { return classKey.get(); }
    inline Node* Id() const noexcept { return id.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
private:
    std::unique_ptr<Node> classKey;
    std::unique_ptr<Node> id;
    std::unique_ptr<Node> attributes;
};

class DeclTypeSpecifierNode : public CompoundNode
{
public:
    DeclTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    DeclTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Expression() const noexcept { return expr.get(); }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    std::unique_ptr<Node> expr;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class PlaceholderTypeSpecifierNode : public CompoundNode
{
public:
    PlaceholderTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    PlaceholderTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* typeConstraint_, const soul::ast::SourcePos& dtPos_,
        const soul::ast::SourcePos& autoPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TypeConstraint() const { return typeConstraint.get(); }
    inline const soul::ast::SourcePos& DeclTypePos() const noexcept { return dtPos; }
    inline const soul::ast::SourcePos& AutoPos() const noexcept { return autoPos; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    inline bool IsDeclType() const noexcept { return dtPos.IsValid(); };
private:
    std::unique_ptr<Node> typeConstraint;
    soul::ast::SourcePos dtPos;
    soul::ast::SourcePos autoPos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

} // namespace otava::ast
