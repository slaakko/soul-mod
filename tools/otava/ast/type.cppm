// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.type;

import std;
import otava.ast.node;

export namespace otava::ast {

class TypeSpecifierSequenceNode : public SequenceNode
{
public:
    TypeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TypenameSpecifierNode : public CompoundNode
{
public:
    TypenameSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    TypenameSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* id_, Node* templateNode_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* NestedNameSpecifier() const { return nns.get(); }
    inline Node* Id() const { return id.get(); }
    inline Node* TemplateNode() const { return templateNode.get(); }
private:
    std::unique_ptr<Node> nns;
    std::unique_ptr<Node> id;
    std::unique_ptr<Node> templateNode;
};

class TypeIdNode : public CompoundNode
{
public:
    TypeIdNode(const soul::ast::SourcePos& sourcePos_);
    TypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_, Node* declarator_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TypeSpecifiers() const { return typeSpecifiers.get(); }
    inline Node* Declarator() const { return declarator.get(); }
private:
    std::unique_ptr<Node> typeSpecifiers;
    std::unique_ptr<Node> declarator;
};

class DefiningTypeIdNode : public CompoundNode
{
public:
    DefiningTypeIdNode(const soul::ast::SourcePos& sourcePos_);
    DefiningTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* definingTypeSpecifiers_, Node* abstractDeclarator_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* DefiningTypeSpecifiers() const { return definingTypeSpecifiers.get(); }
    inline Node* AbstractDeclarator() const { return abstractDeclarator.get(); }
private:
    std::unique_ptr<Node> definingTypeSpecifiers;
    std::unique_ptr<Node> abstractDeclarator;
};

class DefiningTypeSpecifierSequenceNode : public SequenceNode
{
public:
    DefiningTypeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TrailingReturnTypeNode : public UnaryNode
{
public:
    TrailingReturnTypeNode(const soul::ast::SourcePos& sourcePos_);
    TrailingReturnTypeNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ElaboratedTypeSpecifierNode : public CompoundNode
{
public:
    ElaboratedTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    ElaboratedTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* classKey_, Node* id_, Node* attributes_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ClassKey() const { return classKey.get(); }
    inline Node* Id() const { return id.get(); }
    inline Node* Attributes() const { return attributes.get(); }
private:
    std::unique_ptr<Node> classKey;
    std::unique_ptr<Node> id;
    std::unique_ptr<Node> attributes;
};

class DeclTypeSpecifierNode : public CompoundNode
{
public:
    DeclTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    DeclTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Expression() const { return expr.get(); }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> expr;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class PlaceholderTypeSpecifierNode : public CompoundNode
{
public:
    PlaceholderTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    PlaceholderTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* typeConstraint_, const soul::ast::SourcePos& dtPos_, const soul::ast::SourcePos& autoPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TypeConstraint() const { return typeConstraint.get(); }
    inline const soul::ast::SourcePos& DeclTypePos() const { return dtPos; }
    inline const soul::ast::SourcePos& AutoPos() const { return autoPos; }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
    inline bool IsDeclType() const { return dtPos.IsValid(); };
private:
    std::unique_ptr<Node> typeConstraint;
    soul::ast::SourcePos dtPos;
    soul::ast::SourcePos autoPos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

} // namespace otava::ast
