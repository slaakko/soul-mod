// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.parent.node;

import std;
import soul_expected.xml.node;

export namespace soul_expected::xml {

class ParentNode : public Node
{
public:
    ParentNode(NodeKind kind_, const soul_expected::ast::SourcePos& sourcePos_, const std::string& name_);
    ~ParentNode();
    virtual std::expected<bool, int> AppendChild(Node* child);
    virtual std::expected<bool, int> InsertBefore(Node* newChild, Node* refChild);
    virtual std::expected<std::unique_ptr<Node>, int> RemoveChild(Node* child);
    virtual std::expected<std::unique_ptr<Node>, int> ReplaceChild(Node* newChild, Node* oldChild);
    bool HasChildNodes() const final { return firstChild != nullptr; }
    Node* FirstChild() const { return firstChild; }
    Node* LastChild() const { return lastChild; }
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(util::CodeFormatter& formatter) override;
    void WalkChildren(NodeOperation& operation) override;
    void WalkDescendant(NodeOperation& operation) override;
    void WalkDescendantOrSelf(NodeOperation& operation) override;
    void WalkPreceding(NodeOperation& operation) override;
    void WalkPrecedingOrSelf(NodeOperation& operation) override;
private:
    Node* firstChild;
    Node* lastChild;
};

} // namespace soul_expected::xml
