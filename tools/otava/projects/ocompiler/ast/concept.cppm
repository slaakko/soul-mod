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
    ConceptDefinitionNode(const soul::ast::SourcePos& sourcePos_);
    ConceptDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* conceptName_, Node* assign_, Node* constraintExpr_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* ConceptName() const { return conceptName.get(); }
    inline Node* Assign() const { return assign.get(); }
    inline Node* ConstraintExpression() const { return constraintExpr.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> conceptName;
    std::unique_ptr<Node> assign;
    std::unique_ptr<Node> constraintExpr;
    std::unique_ptr<Node> semicolon;
};

class RequiresExprNode : public CompoundNode
{
public:
    RequiresExprNode(const soul::ast::SourcePos& sourcePos_);
    RequiresExprNode(const soul::ast::SourcePos& sourcePos_, Node* params_, Node* body_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* Params() const { return params.get(); }
    inline Node* Body() const { return body.get(); }
private:
    std::unique_ptr<Node> params;
    std::unique_ptr<Node> body;
};

class RequirementBodyNode : public SequenceNode
{
public:
    RequirementBodyNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void SetLBracePos(const soul::ast::SourcePos& lbPos_);
    void SetRBracePos(const soul::ast::SourcePos& rbPos_);
    inline const soul::ast::SourcePos& LBracePos() const { return lbPos; }
    inline const soul::ast::SourcePos& RBracePos() const { return rbPos; }
private:
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class SimpleRequirementNode : public BinaryNode
{
public:
    SimpleRequirementNode(const soul::ast::SourcePos& sourcePos_);
    SimpleRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TypeRequirementNode : public CompoundNode
{
public:
    TypeRequirementNode(const soul::ast::SourcePos& sourcePos_);
    TypeRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* typeName_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* NestedNameSpecifier() const { return nns.get(); }
    inline Node* TypeName() const { return typeName.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> nns;
    std::unique_ptr<Node> typeName;
    std::unique_ptr<Node> semicolon;
};

class CompoundRequirementNode : public CompoundNode
{
public:
    CompoundRequirementNode(const soul::ast::SourcePos& sourcePos_);
    CompoundRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, Node* noexcept_, Node* returnTypeRequirement_, Node* semicolon_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* Expr() const { return expr.get(); }
    inline Node* NoExcept() const { return noexceptNode.get(); }
    inline Node* ReturnTypeRequirement() const { return returnTypeRequirement.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline const soul::ast::SourcePos& LBracePos() const { return lbPos; }
    inline const soul::ast::SourcePos& RBracePos() const { return rbPos; }
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
    ReturnTypeRequirementNode(const soul::ast::SourcePos& sourcePos_);
    ReturnTypeRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* typeConstraint_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class NestedRequirementNode : public BinaryNode
{
public:
    NestedRequirementNode(const soul::ast::SourcePos& sourcePos_);
    NestedRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* constraintExpression_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TypeConstraintNode : public ListNode
{
public:
    TypeConstraintNode(const soul::ast::SourcePos& sourcePos_);
    TypeConstraintNode(const soul::ast::SourcePos& sourcePos_, Node* conceptName_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline void SetHasTemplateArgumentList() { hasTemplateArgumentList = true; }
    inline bool HasTemplateArgumentList() const { return hasTemplateArgumentList; }
    inline Node* ConceptName() const { return conceptName.get(); }
    void SetLAnglePos(const soul::ast::SourcePos& laPos_);
    void SetRAnglePos(const soul::ast::SourcePos& raPos_);
    inline const soul::ast::SourcePos& LAnglePos() const { return laPos; }
    inline const soul::ast::SourcePos& RAnglePos() const { return laPos; }
private:
    std::unique_ptr<Node> conceptName;
    bool hasTemplateArgumentList;
    soul::ast::SourcePos laPos;
    soul::ast::SourcePos raPos;
};

class RequiresClauseNode : public UnaryNode
{
public:
    RequiresClauseNode(const soul::ast::SourcePos& sourcePos_);
    RequiresClauseNode(const soul::ast::SourcePos& sourcePos_, Node* constraintLogicalOrExpr_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

} // namespace otava::ast
