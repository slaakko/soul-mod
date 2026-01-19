// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.node;

import std;
import util;
import soul.ast.source.pos;
import soul.xml.axis;

export namespace soul::xml {

enum class NodeKind
{
    attributeNode, documentFragmentNode, documentNode, elementNode, entityNode, entityReferenceNode, notationNode, processingInstructionNode, textNode,
    cdataSectionNode, commentNode
};

std::string NodeKindStr(NodeKind nodeKind);

class ParentNode;
class Document;
class Visitor;
class NodeOperation;

class Node
{
public:
    Node(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::string& name_);
    virtual ~Node();
    NodeKind Kind() const { return kind; }
    inline const soul::ast::SourcePos& GetSourcePos() const { return sourcePos; }
    inline const std::string& Name() const { return name; }
    inline const std::string& NamespaceUri() const { return namespaceUri; }
    void SetNamespaceUri(const std::string& namespaceUri_);
    inline bool IsAttributeNode() const { return kind == NodeKind::attributeNode; }
    inline bool IsDocumentFragmentNode() const { return kind == NodeKind::documentFragmentNode; }
    inline bool IsDocumentNode() const { return kind == NodeKind::documentNode; }
    inline bool IsElementNode() const { return kind == NodeKind::elementNode; }
    inline bool IsEntityNode() const { return kind == NodeKind::entityNode; }
    inline bool IsEntityReferenceNode() const { return kind == NodeKind::entityReferenceNode; }
    inline bool IsNotationNode() const { return kind == NodeKind::notationNode; }
    inline bool IsProcessingInstructionNode() const { return kind == NodeKind::processingInstructionNode; }
    inline bool IsTextNode() const { return kind == NodeKind::textNode; }
    inline bool IsCDataSectionNode() const { return kind == NodeKind::cdataSectionNode; }
    inline bool IsCommentNode() const { return kind == NodeKind::commentNode; }
    void Walk(NodeOperation& operation, Axis axis);
    virtual void WalkChildren(NodeOperation& operation);
    virtual void WalkDescendant(NodeOperation& operation);
    virtual void WalkDescendantOrSelf(NodeOperation& operation);
    void WalkParent(NodeOperation& operation);
    virtual void WalkFollowing(NodeOperation& operation);
    virtual void WalkPreceding(NodeOperation& operation);
    virtual void WalkPrecedingOrSelf(NodeOperation& operation);
    void WalkAncestor(NodeOperation& operation);
    void WalkAncestorOrSelf(NodeOperation& operation);
    void WalkFollowingSibling(NodeOperation& operation);
    void WalkPrecedingSibling(NodeOperation& operation);
    virtual void WalkAttribute(NodeOperation& operation);
    inline ParentNode* Parent() const { return parent; }
    inline Node* Prev() const { return prev; }
    inline Node* Next() const { return next; }
    inline Document* OwnerDocument() const { return ownerDocument; }
    inline void SetOwnerDocument(Document* ownerDocumnent_) { ownerDocument = ownerDocumnent_; }
    std::string Prefix() const;
    std::expected<bool, int> SetPrefix(const std::string& prefix);
    std::string LocalName() const;
    virtual void Accept(Visitor& visitor) {}
    virtual bool HasChildNodes() const { return false; }
    virtual bool HasAttributes() const { return false; }
    virtual bool ValueContainsNewLine() const { return false; }
    virtual std::expected<bool, int> Write(util::CodeFormatter& formatter) = 0;
private:
    friend class ParentNode;
    inline void SetParent(ParentNode* parent_) { parent = parent_; }
    inline void SetPrev(Node* prev_) { prev = prev_; }
    inline void SetNext(Node* next_) { next = next_; }
    void LinkBefore(Node* node);
    void LinkAfter(Node* node);
    void Unlink();
    NodeKind kind;
    soul::ast::SourcePos sourcePos;
    std::string name;
    std::string namespaceUri;
    ParentNode* parent;
    Node* prev;
    Node* next;
    Document* ownerDocument;
};

} // namespace soul::xml
