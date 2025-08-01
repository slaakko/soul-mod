// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.declaration;

import std;
import otava.ast.node;

export namespace otava::ast {

class DeclarationSequenceNode : public SequenceNode
{
public:
    DeclarationSequenceNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class SimpleDeclarationNode : public CompoundNode
{
public:
    SimpleDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    SimpleDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* declarationSpecifiers_, Node* initDeclaratorList_, Node* attributes_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* DeclarationSpecifiers() const { return declarationSpecifiers.get(); }
    inline Node* InitDeclaratorList() const { return initDeclaratorList.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> declarationSpecifiers;
    std::unique_ptr<Node> initDeclaratorList;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
};

class AsmDeclarationNode : public CompoundNode
{
public:
    AsmDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    AsmDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* asm__, Node* asmText_, Node* semicolon_, Node* attributes_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Asm() const { return asm_.get(); }
    inline Node* AsmText() const { return asmText.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> asm_;
    std::unique_ptr<Node> asmText;
    std::unique_ptr<Node> semicolon;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class AsmNode : public Node
{
public:
    AsmNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class LinkageSpecificationNode : public CompoundNode
{
public:
    LinkageSpecificationNode(const soul::ast::SourcePos& sourcePos_);
    LinkageSpecificationNode(const soul::ast::SourcePos& sourcePos_, Node* extrn_, Node* linkage_, Node* declarations_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Extern() const { return extrn.get(); }
    inline Node* Linkage() const { return linkage.get(); }
    inline Node* Declarations() const { return declarations.get(); }
    inline const soul::ast::SourcePos& LBracePos() const { return lbPos; }
    inline const soul::ast::SourcePos& RBracePos() const { return rbPos; }
private:
    std::unique_ptr<Node> extrn;
    std::unique_ptr<Node> linkage;
    std::unique_ptr<Node> declarations;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class NamespaceDefinitionNode : public CompoundNode
{
public:
    NamespaceDefinitionNode(const soul::ast::SourcePos& sourcePos_);
    NamespaceDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* nskw_, Node* nsName_, Node* nsBody_, Node* inln_, Node* attributes_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Namespace() const { return nskw.get(); }
    inline Node* NamespaceName() const { return nsName.get(); }
    inline Node* NamespaceBody() const { return nsBody.get(); }
    inline Node* Inline() const { return inln.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline const soul::ast::SourcePos& LBracePos() const { return lbPos; }
    inline const soul::ast::SourcePos& RBracePos() const { return rbPos; }
private:
    std::unique_ptr<Node> nskw;
    std::unique_ptr<Node> nsName;
    std::unique_ptr<Node> nsBody;
    std::unique_ptr<Node> inln;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class NamespaceBodyNode : public CompoundNode
{
public:
    NamespaceBodyNode(const soul::ast::SourcePos& sourcePos_);
    NamespaceBodyNode(const soul::ast::SourcePos& sourcePos_, Node* declarations_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Declarations() const { return declarations.get(); }
private:
    std::unique_ptr<Node> declarations;
};

class NamespaceAliasDefinitionNode : public CompoundNode
{
public:
    NamespaceAliasDefinitionNode(const soul::ast::SourcePos& sourcePos_);
    NamespaceAliasDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* id_, Node* assign_, Node* qns_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Id() const { return id.get(); }
    inline Node* Assign() const { return assign.get(); }
    inline Node* QualifiedNamespaceSpecifier() const { return qns.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> id;
    std::unique_ptr<Node> assign;
    std::unique_ptr<Node> qns;
    std::unique_ptr<Node> semicolon;
};

class UsingDeclarationNode : public CompoundNode
{
public:
    UsingDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    UsingDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* usng_, Node* declarators_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Using() const { return usng.get(); }
    inline Node* Declarators() const { return declarators.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> usng;
    std::unique_ptr<Node> declarators;
    std::unique_ptr<Node> semicolon;
};

class UsingNode : public Node
{
public:
    UsingNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class UsingDeclaratorListNode : public ListNode
{
public:
    UsingDeclaratorListNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class UsingEnumDeclarationNode : public CompoundNode
{
public:
    UsingEnumDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    UsingEnumDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* usng_, Node* ees_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Using() const { return usng.get(); }
    inline Node* ElaboratedEnumSpecifier() const { return ees.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> usng;
    std::unique_ptr<Node> ees;
    std::unique_ptr<Node> semicolon;
};

class UsingDirectiveNode : public CompoundNode
{
public:
    UsingDirectiveNode(const soul::ast::SourcePos& sourcePos_);
    UsingDirectiveNode(const soul::ast::SourcePos& sourcePos_, Node* usng_, Node* nskw_, Node* id_, Node* semicolon_, Node* attributes_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Using() const { return usng.get(); }
    inline Node* Namespace() const { return nskw.get(); }
    inline Node* Id() const { return id.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline Node* Attributes() const { return attributes.get(); }
private:
    std::unique_ptr<Node> usng;
    std::unique_ptr<Node> nskw;
    std::unique_ptr<Node> id;
    std::unique_ptr<Node> semicolon;
    std::unique_ptr<Node> attributes;
};

class NamespaceNode : public Node
{
public:
    NamespaceNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class StaticAssertDeclarationNode : public CompoundNode
{
public:
    StaticAssertDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    StaticAssertDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* staticAssert_, Node* constantExpr_, Node* comma_, Node* stringLiteral_, Node* semicolon_,
        const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* StaticAssert() const { return staticAssert.get(); }
    inline Node* ConstantExpr() const { return constantExpr.get(); }
    inline Node* Comma() const { return comma.get(); }
    inline Node* StringLiteral() const { return stringLiteral.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> staticAssert;
    std::unique_ptr<Node> constantExpr;
    std::unique_ptr<Node> comma;
    std::unique_ptr<Node> stringLiteral;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class StaticAssertNode : public Node
{
public:
    StaticAssertNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class AliasDeclarationNode : public CompoundNode
{
public:
    AliasDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    AliasDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* usng_, Node* identifier_, Node* assign_, Node* definingTypeId_, Node* attributes_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Using() const { return usng.get(); }
    inline Node* Identifier() const { return identifier.get(); }
    inline Node* Assign() const { return assign.get(); }
    inline Node* DefiningTypeId() const { return definingTypeId.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> usng;
    std::unique_ptr<Node> identifier;
    std::unique_ptr<Node> assign;
    std::unique_ptr<Node> definingTypeId;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
};

class EmptyDeclarationNode : public Node
{
public:
    EmptyDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class AttributeDeclarationNode : public BinaryNode
{
public:
    AttributeDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    AttributeDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class InitDeclaratorListNode : public ListNode
{
public:
    InitDeclaratorListNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class InitDeclaratorNode : public BinaryNode
{
public:
    InitDeclaratorNode(const soul::ast::SourcePos& sourcePos_);
    InitDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* declarator_, Node* init_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TrailingFunctionDeclaratorNode : public CompoundNode
{
public:
    TrailingFunctionDeclaratorNode(const soul::ast::SourcePos& sourcePos_);
    TrailingFunctionDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* declarator_, Node* params_, Node* trailingReturnType_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Declarator() const { return declarator.get(); }
    inline Node* Parameters() const { return params.get(); }
    inline Node* TrailingReturnType() const { return trailingReturnType.get(); }
private:
    std::unique_ptr<Node> declarator;
    std::unique_ptr<Node> params;
    std::unique_ptr<Node> trailingReturnType;
};

class ParenthesizedDeclaratorNode : public CompoundNode
{
public:
    ParenthesizedDeclaratorNode(const soul::ast::SourcePos& sourcePos_);
    ParenthesizedDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* declarator_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Declarator() const { return declarator.get(); }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> declarator;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class AbstractDeclaratorNode : public Node
{
public:
    AbstractDeclaratorNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DeclSpecifierSequenceNode : public SequenceNode
{
public:
    DeclSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class FriendNode : public Node
{
public:
    FriendNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TypedefNode : public Node
{
public:
    TypedefNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ConstExprNode : public Node
{
public:
    ConstExprNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ConstEvalNode : public Node
{
public:
    ConstEvalNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ConstInitNode : public Node
{
public:
    ConstInitNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class InlineNode : public Node
{
public:
    InlineNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override; 
    void Accept(Visitor& visitor) override;
};

class StaticNode : public Node
{
public:
    StaticNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ThreadLocalNode : public Node
{
public:
    ThreadLocalNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ExternNode : public Node
{
public:
    ExternNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class MutableNode : public Node
{
public:
    MutableNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ExplicitNode : public Node
{
public:
    ExplicitNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ConditionalExplicitNode : public UnaryNode
{
public:
    ConditionalExplicitNode(const soul::ast::SourcePos& sourcePos_);
    ConditionalExplicitNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Condition() const { return cond.get(); }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> cond;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class QualifiedPtrNode : public BinaryNode
{
public:
    QualifiedPtrNode(const soul::ast::SourcePos& sourcePos_);
    QualifiedPtrNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* ptr_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class PtrOperatorNode : public UnaryNode
{
public:
    PtrOperatorNode(const soul::ast::SourcePos& sourcePos_);
    PtrOperatorNode(const soul::ast::SourcePos& sourcePos_, Node* child_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class PtrDeclaratorNode : public SequenceNode
{
public:
    PtrDeclaratorNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class PackDeclaratorIdNode : public BinaryNode
{
public:
    PackDeclaratorIdNode(const soul::ast::SourcePos& sourcePos_);
    PackDeclaratorIdNode(const soul::ast::SourcePos& sourcePos_, Node* ellipsis_, Node* idExpr_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ArrayDeclaratorNode : public UnaryNode
{
public:
    ArrayDeclaratorNode(const soul::ast::SourcePos& sourcePos_);
    ArrayDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* dimension_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Dimension() const { return dimension.get(); }
    inline const soul::ast::SourcePos& LBracketPos() const { return lbPos; }
    inline const soul::ast::SourcePos& RBracketPos() const { return rbPos; }
private:
    std::unique_ptr<Node> dimension;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class FunctionDeclaratorNode : public UnaryNode
{
public:
    FunctionDeclaratorNode(const soul::ast::SourcePos& sourcePos_);
    FunctionDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* parameters_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Params() const { return params.get(); }
private:
    std::unique_ptr<Node> params;
};

class PrefixNode : public BinaryNode
{
public:
    PrefixNode(const soul::ast::SourcePos& sourcePos_);
    PrefixNode(const soul::ast::SourcePos& sourcePos_, Node* prefix_, Node* subject_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class TrailingQualifiersNode : public SequenceNode
{
public:
    TrailingQualifiersNode(const soul::ast::SourcePos& sourcePos_);
    TrailingQualifiersNode(const soul::ast::SourcePos& sourcePos_, Node* subject_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Subject() const { return subject.get(); }
    inline Node* ReleaseSubject() { return subject.release(); }
private:
    std::unique_ptr<Node> subject;
};

class TrailingAttributesNode : public BinaryNode
{
public:
    TrailingAttributesNode(const soul::ast::SourcePos& sourcePos_);
    TrailingAttributesNode(const soul::ast::SourcePos& sourcePos_, Node* left_, Node* attributes_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class NoexceptSpecifierNode : public CompoundNode
{
public:
    NoexceptSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    NoexceptSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* constantExpr_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ConstantExpr() const { return constantExpr.get(); }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> constantExpr;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class ThrowSpecifierNode : public CompoundNode
{
public:
    ThrowSpecifierNode(const soul::ast::SourcePos& sourcePos_);
    ThrowSpecifierNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

} // namespace otava::ast
