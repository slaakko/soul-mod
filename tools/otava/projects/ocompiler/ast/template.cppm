// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.templates;

import std;
import otava.ast.node;

export namespace otava::ast {

class TemplateDeclarationNode : public BinaryNode
{
public:
    TemplateDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    TemplateDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* templateHead_, Node* declaration_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TemplateHeadNode : public CompoundNode
{
public:
    TemplateHeadNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void SetTemplateParameterList(Node* templateParamList_);
    inline Node* TemplateParamList() const { return templateParamList.get(); }
    void SetRequiresClause(Node* requiresClause_);
    inline Node* RequiresClause() const { return requiresClause.get(); }
private:
    std::unique_ptr<Node> templateParamList;
    std::unique_ptr<Node> requiresClause;
};

class TemplateParameterListNode : public ListNode
{
public:
    TemplateParameterListNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline void SetLAnglePos(const soul::ast::SourcePos& laPos_) { laPos = laPos_; }
    inline void SetRAnglePos(const soul::ast::SourcePos& raPos_) { raPos = raPos_; }
    inline const soul::ast::SourcePos& LAnglePos() const { return laPos; }
    inline const soul::ast::SourcePos& RAnglePos() const { return raPos; }
private:
    soul::ast::SourcePos laPos;
    soul::ast::SourcePos raPos;
};

class TypeParameterNode : public CompoundNode
{
public:
    TypeParameterNode(const soul::ast::SourcePos& sourcePos_);
    TypeParameterNode(const soul::ast::SourcePos& sourcePos_, Node* typeConstraint_, Node* identifier_, Node* assign_, Node* typeId_, Node* ellipsis_, Node* templateHead_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* TypeConstraint() const { return typeConstraint.get(); }
    inline Node* Identifier() const { return identifier.get(); }
    inline Node* Assign() const { return assign.get(); }
    inline Node* TypeId() const { return typeId.get(); }
    inline Node* Ellipsis() const { return ellipsis.get(); }
    inline Node* TemplateHead() const { return templateHead.get(); }
private:
    std::unique_ptr<Node> typeConstraint;
    std::unique_ptr<Node> identifier;
    std::unique_ptr<Node> assign;
    std::unique_ptr<Node> typeId;
    std::unique_ptr<Node> ellipsis;
    std::unique_ptr<Node> templateHead;
};

class TemplateIdNode : public ListNode
{
public:
    TemplateIdNode(const soul::ast::SourcePos& sourcePos_);
    TemplateIdNode(const soul::ast::SourcePos& sourcePos_, Node* templateName_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* TemplateName() const { return templateName.get(); }
    inline void SetLAnglePos(const soul::ast::SourcePos& laPos_) { laPos = laPos_; }
    inline void SetRAnglePos(const soul::ast::SourcePos& raPos_) { raPos = raPos_; }
    inline const soul::ast::SourcePos& LAnglePos() const { return laPos; }
    inline const soul::ast::SourcePos& RAnglePos() const { return raPos; }
    inline const std::vector<bool>& TemplateArgKinds() const { return templateArgKinds; }
    void SetTemplateArgKinds(const std::vector<bool>& templateArgKinds_);
private:
    std::unique_ptr<Node> templateName;
    soul::ast::SourcePos laPos;
    soul::ast::SourcePos raPos;
    std::vector<bool> templateArgKinds;
};

class TypenameNode : public Node
{
public:
    TypenameNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DeductionGuideNode : public CompoundNode
{
public:
    DeductionGuideNode(const soul::ast::SourcePos& sourcePos_);
    DeductionGuideNode(const soul::ast::SourcePos& sourcePos_, Node* templateName_, Node* params_, Node* arrow_, Node* templateId_, Node* explicitSpecifier_, Node* semicolon_,
        const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* TemplateName() const { return templateName.get(); }
    inline Node* Parameters() const { return params.get(); }
    inline Node* Arrow() const { return arrow.get(); }
    inline Node* TemplateId() const { return templateId.get(); }
    inline Node* ExplicitSpecifier() const { return explicitSpecifier.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> templateName;
    std::unique_ptr<Node> params;
    std::unique_ptr<Node> arrow;
    std::unique_ptr<Node> templateId;
    std::unique_ptr<Node> explicitSpecifier;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class ExplicitInstantiationNode : public CompoundNode
{
public:
    ExplicitInstantiationNode(const soul::ast::SourcePos& sourcePos_);
    ExplicitInstantiationNode(const soul::ast::SourcePos& sourcePos_, Node* extrn_, Node* tmp_, Node* declaration_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* Extern() const { return extrn.get(); }
    inline Node* Template() const { return tmp.get(); }
    inline Node* Declaration() const { return declaration.get(); }
private:
    std::unique_ptr<Node> extrn;
    std::unique_ptr<Node> tmp;
    std::unique_ptr<Node> declaration;
};

class TemplateNode : public Node
{
public:
    TemplateNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ExplicitSpecializationNode : public CompoundNode
{
public:
    ExplicitSpecializationNode(const soul::ast::SourcePos& sourcePos_);
    ExplicitSpecializationNode(const soul::ast::SourcePos& sourcePos_, Node* tmp_, Node* templateHeadNode_, Node* declaration_,
        const soul::ast::SourcePos& laPos_, const soul::ast::SourcePos& raPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    inline Node* Template() const { return tmp.get(); }
    inline Node* Declaration() const { return declaration.get(); }
    inline const soul::ast::SourcePos& LAnglePos() const { return laPos; }
    inline const soul::ast::SourcePos& RAnglePos() const { return raPos; }
private:
    std::unique_ptr<Node> tmp;
    std::unique_ptr<Node> templateHeadNode;
    std::unique_ptr<Node> declaration;
    soul::ast::SourcePos laPos;
    soul::ast::SourcePos raPos;
};

} // namespace otava::ast
