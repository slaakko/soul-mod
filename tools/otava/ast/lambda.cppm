// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.lambda;

import std;
import otava.ast.node;

export namespace otava::ast {

class LambdaExpressionNode : public CompoundNode
{
public:
    LambdaExpressionNode(const soul::ast::SourcePos& sourcePos_);
    LambdaExpressionNode(const soul::ast::SourcePos& sourcePos_, Node* introducer_, Node* templateParams_, Node* declarator_, Node* body_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Introducer() const { return introducer.get(); }
    inline Node* TemplateParams() const { return templateParams.get(); }
    inline Node* Declarator() const { return declarator.get(); }
    inline Node* Body() const { return body.get(); }
private:
    std::unique_ptr<Node> introducer;
    std::unique_ptr<Node> templateParams;
    std::unique_ptr<Node> declarator;
    std::unique_ptr<Node> body;
};

class LambdaIntroducerNode : public CompoundNode
{
public:
    LambdaIntroducerNode(const soul::ast::SourcePos& sourcePos_);
    LambdaIntroducerNode(const soul::ast::SourcePos& sourcePos_, Node* capture_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Capture() const { return capture.get(); }
    inline const soul::ast::SourcePos& LBracketPos() const { return lbPos; }
    inline const soul::ast::SourcePos& RBracketPos() const { return rbPos; }
private:
    std::unique_ptr<Node> capture;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class LambdaCaptureNode : public ListNode
{
public:
    LambdaCaptureNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DefaultRefCaptureNode : public Node
{
public:
    DefaultRefCaptureNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DefaultCopyCaptureNode : public Node
{
public:
    DefaultCopyCaptureNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ByRefCaptureNode : public Node
{
public:
    ByRefCaptureNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class SimpleCaptureNode : public CompoundNode
{
public:
    SimpleCaptureNode(const soul::ast::SourcePos& sourcePos_);
    SimpleCaptureNode(const soul::ast::SourcePos& sourcePos_, Node* identifier_, Node* byRefCapture_, Node* ellipsis_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Identifier() const { return identifier.get(); }
    inline Node* ByRefCapture() const { return byRefCapture.get(); }
    inline Node* Ellipsis() const { return ellipsis.get(); }
private:
    std::unique_ptr<Node> identifier;
    std::unique_ptr<Node> byRefCapture;
    std::unique_ptr<Node> ellipsis;
};

class CurrentObjectCopyCapture : public CompoundNode
{
public:
    CurrentObjectCopyCapture(const soul::ast::SourcePos& sourcePos_);
    CurrentObjectCopyCapture(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& thisPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& ThisPos() const { return thisPos; }
private:
    soul::ast::SourcePos thisPos;
};

class CurrentObjectByRefCapture : public CompoundNode
{
public:
    CurrentObjectByRefCapture(const soul::ast::SourcePos& sourcePos_);
    CurrentObjectByRefCapture(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& thisPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& ThisPos() const { return thisPos; }
private:
    soul::ast::SourcePos thisPos;
};

class InitCaptureNode : public CompoundNode
{
public:
    InitCaptureNode(const soul::ast::SourcePos& sourcePos_);
    InitCaptureNode(const soul::ast::SourcePos& sourcePos_, Node* identifier_, Node* initializer_, Node* byRefCapture_, Node* ellipsis_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Identifier() const { return identifier.get(); }
    inline Node* Initializer() const { return initializer.get(); }
    inline Node* ByRefCapture() const { return byRefCapture.get(); }
    inline Node* Ellipsis() const { return ellipsis.get(); }
private:
    std::unique_ptr<Node> identifier;
    std::unique_ptr<Node> initializer;
    std::unique_ptr<Node> byRefCapture;
    std::unique_ptr<Node> ellipsis;
};

class LambdaDeclaratorNode : public CompoundNode
{
public:
    LambdaDeclaratorNode(const soul::ast::SourcePos& sourcePos_);
    LambdaDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* parameterList_, Node* specifiers_, Node* requiresClause_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ParameterList() const { return parameterList.get(); }
    inline Node* Specifiers() const { return specifiers.get(); }
    inline Node* RequiresClause() const { return requiresClause.get(); }
private:
    std::unique_ptr<Node> parameterList;
    std::unique_ptr<Node> specifiers;
    std::unique_ptr<Node> requiresClause;
};

class LambdaSpecifiersNode : public CompoundNode
{
public:
    LambdaSpecifiersNode(const soul::ast::SourcePos& sourcePos_);
    LambdaSpecifiersNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifiers_, Node* noexceptSpecifier_, Node* attributes_, Node* trailingReturnType_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    bool IsEmpty() const;
    inline Node* DeclSpecifiers() const { return declSpecifiers.get(); }
    inline Node* NoexceptionSpecifier() const { return noexceptSpecifier.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* TrailingReturnType() const { return trailingReturnType.get(); }
private:
    std::unique_ptr<Node> declSpecifiers;
    std::unique_ptr<Node> noexceptSpecifier;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> trailingReturnType;
};

class LambdaTemplateParamsNode : public CompoundNode
{
public:
    LambdaTemplateParamsNode(const soul::ast::SourcePos& sourcePos_);
    LambdaTemplateParamsNode(const soul::ast::SourcePos& sourcePos_, Node* templateParams_, Node* requiresClause_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TemplateParams() const { return templateParams.get(); }
    inline Node* RequiresClause() const { return requiresClause.get(); }
private:
    std::unique_ptr<Node> templateParams;
    std::unique_ptr<Node> requiresClause;
};

} // namespace otava::ast
