// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.concepts;

import std;
import otava.ast.node;

export namespace otava::ast {

class ConceptDefinitionNode : public CompoundNode
{
public:
    ConceptDefinitionNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ConceptDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* conceptName_, Node* assign_, Node* constraintExpr_, Node* semicolon_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ConceptName() const noexcept { return conceptName.get(); }
    inline Node* Assign() const noexcept { return assign.get(); }
    inline Node* ConstraintExpression() const noexcept { return constraintExpr.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
private:
    std::unique_ptr<Node> conceptName;
    std::unique_ptr<Node> assign;
    std::unique_ptr<Node> constraintExpr;
    std::unique_ptr<Node> semicolon;
};

class RequiresExprNode : public CompoundNode
{
public:
    RequiresExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    RequiresExprNode(const soul::ast::SourcePos& sourcePos_, Node* params_, Node* body_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Params() const noexcept { return params.get(); }
    inline Node* Body() const noexcept { return body.get(); }
private:
    std::unique_ptr<Node> params;
    std::unique_ptr<Node> body;
};

class RequirementBodyNode : public SequenceNode
{
public:
    RequirementBodyNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void SetLBracePos(const soul::ast::SourcePos& lbPos_) noexcept;
    void SetRBracePos(const soul::ast::SourcePos& rbPos_) noexcept;
    inline const soul::ast::SourcePos& LBracePos() const noexcept { return lbPos; }
    inline const soul::ast::SourcePos& RBracePos() const noexcept { return rbPos; }
private:
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class SimpleRequirementNode : public BinaryNode
{
public:
    SimpleRequirementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    SimpleRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, Node* semicolon_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TypeRequirementNode : public CompoundNode
{
public:
    TypeRequirementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    TypeRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* typeName_, Node* semicolon_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* NestedNameSpecifier() const noexcept { return nns.get(); }
    inline Node* TypeName() const noexcept { return typeName.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
private:
    std::unique_ptr<Node> nns;
    std::unique_ptr<Node> typeName;
    std::unique_ptr<Node> semicolon;
};

class CompoundRequirementNode : public CompoundNode
{
public:
    CompoundRequirementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    CompoundRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, Node* noexcept_, Node* returnTypeRequirement_, Node* semicolon_, 
        const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Expr() const noexcept { return expr.get(); }
    inline Node* NoExcept() const noexcept { return noexceptNode.get(); }
    inline Node* ReturnTypeRequirement() const noexcept { return returnTypeRequirement.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
    inline const soul::ast::SourcePos& LBracePos() const noexcept { return lbPos; }
    inline const soul::ast::SourcePos& RBracePos() const noexcept { return rbPos; }
private:
    std::unique_ptr<Node> expr;
    std::unique_ptr<Node> noexceptNode;
    std::unique_ptr<Node> returnTypeRequirement;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class ReturnTypeRequirementNode : public UnaryNode
{
public:
    ReturnTypeRequirementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ReturnTypeRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* typeConstraint_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class NestedRequirementNode : public BinaryNode
{
public:
    NestedRequirementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    NestedRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* constraintExpression_, Node* semicolon_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TypeConstraintNode : public ListNode
{
public:
    TypeConstraintNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    TypeConstraintNode(const soul::ast::SourcePos& sourcePos_, Node* conceptName_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline void SetHasTemplateArgumentList() noexcept { hasTemplateArgumentList = true; }
    inline bool HasTemplateArgumentList() const noexcept { return hasTemplateArgumentList; }
    inline Node* ConceptName() const noexcept { return conceptName.get(); }
    void SetLAnglePos(const soul::ast::SourcePos& laPos_) noexcept;
    void SetRAnglePos(const soul::ast::SourcePos& raPos_) noexcept;
    inline const soul::ast::SourcePos& LAnglePos() const noexcept { return laPos; }
    inline const soul::ast::SourcePos& RAnglePos() const noexcept { return laPos; }
private:
    std::unique_ptr<Node> conceptName;
    bool hasTemplateArgumentList;
    soul::ast::SourcePos laPos;
    soul::ast::SourcePos raPos;
};

class RequiresClauseNode : public UnaryNode
{
public:
    RequiresClauseNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    RequiresClauseNode(const soul::ast::SourcePos& sourcePos_, Node* constraintLogicalOrExpr_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

} // namespace otava::ast
