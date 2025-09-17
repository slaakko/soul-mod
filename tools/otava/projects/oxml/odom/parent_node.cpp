// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.xml.parent.node;

import util;
import soul.xml.document;
import soul.xml.document.fragment;
import soul.lexer.error;
import soul.lexer.file.map;
import soul.xml.visitor;
import soul.xml.node.operation;

namespace soul::xml {

ParentNode::ParentNode(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::string& name_) : Node(kind_, sourcePos_, name_), firstChild(nullptr), lastChild(nullptr)
{
}

ParentNode::~ParentNode()
{
    Node* child = firstChild;
    while (child)
    {
        Node* toDel = child;
        child = child->Next();
        delete toDel;
    }
}

std::expected<bool, int> ParentNode::AppendChild(Node* child)
{
    if (!child)
    {
        auto sp = GetSourcePos();
        return std::unexpected<int>(util::AllocateError("could not append child node: given child is null: line=" + std::to_string(sp.line)));
    }
    if (OwnerDocument())
    {
        OwnerDocument()->InvalidateIndex();
    }
    if (child->Parent())
    {
        auto c = child->Parent()->RemoveChild(child);
        if (!c) return std::unexpected<int>(c.error());
        child = c->release();
    }
    if (child->IsDocumentFragmentNode())
    {
        DocumentFragment* documentFragment = static_cast<DocumentFragment*>(child);
        Node* docFragChild = documentFragment->FirstChild();
        Node* nodeInserted = nullptr;
        while (docFragChild)
        {
            auto c = documentFragment->RemoveChild(docFragChild);
            if (!c) return std::unexpected<int>(c.error());
            std::unique_ptr<Node> docFragChildRemoved(c->release());
            std::expected<bool, int>  rv = AppendChild(docFragChildRemoved.release());
            if (!rv) return rv;
            docFragChild = documentFragment->FirstChild();
        }
    }
    else
    {
        if (lastChild)
        {
            lastChild->LinkAfter(child);
        }
        if (!firstChild)
        {
            firstChild = child;
        }
        child->SetOwnerDocument(OwnerDocument());
        child->SetParent(this);
        lastChild = child;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ParentNode::InsertBefore(Node* newChild, Node* refChild)
{
    if (!newChild)
    {
        return std::unexpected<int>(util::AllocateError("could not insert child node: given child is null: line=" + std::to_string(GetSourcePos().line)));
    }
    if (refChild == nullptr)
    {
        auto rv = AppendChild(newChild);
        if (!rv) return rv;
    }
    if (OwnerDocument())
    {
        OwnerDocument()->InvalidateIndex();
    }
    if (newChild->IsDocumentFragmentNode())
    {
        DocumentFragment* documentFragment = static_cast<DocumentFragment*>(newChild);
        Node* docFragChild = documentFragment->FirstChild();
        Node* nodeInserted = nullptr;
        while (docFragChild)
        {
            auto c = documentFragment->RemoveChild(docFragChild);
            if (!c) return std::unexpected<int>(c.error());
            std::unique_ptr<Node> docFragChildRemoved(c->release());
            auto rv = InsertBefore(docFragChildRemoved.release(), refChild);
            if (!rv) return rv;
            docFragChild = documentFragment->FirstChild();
        }
    }
    else
    {
        if (newChild->Parent())
        {
            auto c = newChild->Parent()->RemoveChild(newChild);
            if (!c) return std::unexpected<int>(c.error());
            newChild = c->release();
        }
        if (firstChild == refChild)
        {
            firstChild = newChild;
        }
        newChild->SetParent(this);
        newChild->SetOwnerDocument(OwnerDocument());
        refChild->LinkBefore(newChild);
    }
    return std::expected<bool, int>(true);
}

std::expected<std::unique_ptr<Node>, int> ParentNode::RemoveChild(Node* child)
{
    if (!child)
    {
        return std::unexpected<int>(util::AllocateError("could not remove node: given child is null: line=" + std::to_string(GetSourcePos().line)));
    }
    if (child->Parent() != this)
    {
        std::string errorMessage = "could not remove node: given child is not child of node '" + Name() + "'";
        soul::ast::SourcePos sourcePos = GetSourcePos();
        soul::lexer::FileMap* fileMap = soul::lexer::GetGlobalFileMap();
        if (sourcePos.IsValid() && fileMap)
        {
            auto em = soul::lexer::MakeMessage("error", errorMessage, sourcePos, *fileMap);
            if (!em) return std::unexpected<int>(em.error());
            errorMessage = *em;
        }
        soul::ast::SourcePos childSourcePos = child->GetSourcePos();
        if (childSourcePos.IsValid() && fileMap)
        {
            auto m = soul::lexer::MakeMessage("info", "see reference", childSourcePos, *fileMap);
            if (!m) return std::unexpected<int>(m.error());
            errorMessage.append(1, '\n').append(*m);
        }
        return std::unexpected<int>(util::AllocateError(errorMessage));
    }
    if (OwnerDocument())
    {
        OwnerDocument()->InvalidateIndex();
    }
    child->Unlink();
    if (child == firstChild)
    {
        firstChild = child->Next();
    }
    if (child == lastChild)
    {
        lastChild = child->Prev();
    }
    std::unique_ptr<Node> removedNode = std::unique_ptr<Node>(child);
    removedNode->SetOwnerDocument(nullptr);
    removedNode->SetParent(nullptr);
    return removedNode;
}

std::expected<std::unique_ptr<Node>, int> ParentNode::ReplaceChild(Node* newChild, Node* oldChild)
{
    if (!newChild)
    {
        return std::unexpected<int>(util::AllocateError("could not replace node: given child is null: line=" + std::to_string(GetSourcePos().line)));
    }
    if (!oldChild)
    {
        return std::unexpected<int>(util::AllocateError("could not replace node: given old child is null: line=" + std::to_string(GetSourcePos().line)));
    }
    if (oldChild->Parent() != this)
    {
        std::string errorMessage = "could not replace node: given old child is not child of node '" + Name() + "'";
        soul::ast::SourcePos sourcePos = GetSourcePos();
        soul::lexer::FileMap* fileMap = soul::lexer::GetGlobalFileMap();
        if (sourcePos.IsValid() && fileMap)
        {
            auto m = soul::lexer::MakeMessage("error", errorMessage, sourcePos, *fileMap);
            if (!m) return std::unexpected<int>(m.error());
            errorMessage = *m;
        }
        soul::ast::SourcePos childSourcePos = oldChild->GetSourcePos();
        if (childSourcePos.IsValid() && fileMap)
        {
            auto m = soul::lexer::MakeMessage("info", "see reference", childSourcePos, *fileMap);
            if (!m) return std::unexpected<int>(m.error());
            errorMessage.append(1, '\n').append(*m);
        }
        return std::unexpected<int>(util::AllocateError(errorMessage));
    }
    if (OwnerDocument())
    {
        OwnerDocument()->InvalidateIndex();
    }
    if (newChild->Parent())
    {
        auto c = newChild->Parent()->RemoveChild(newChild);
        if (!c) return std::unexpected<int>(c.error());
        newChild = c->release();
    }
    auto rv = InsertBefore(newChild, oldChild);
    if (!rv) return std::unexpected<int>(rv.error());
    return RemoveChild(oldChild);
}

void ParentNode::Accept(Visitor& visitor)
{
    Node* child = firstChild;
    while (child)
    {
        child->Accept(visitor);
        child = child->Next();
    }
}

std::expected<bool, int> ParentNode::Write(util::CodeFormatter& formatter)
{
    Node* child = firstChild;
    while (child)
    {
        auto rv = child->Write(formatter);
        if (!rv) return rv;
        child = child->Next();
    }
    return std::expected<bool, int>(true);
}

void ParentNode::WalkChildren(NodeOperation& operation)
{
    Node* child = firstChild;
    while (child)
    {
        operation.Apply(child);
        child = child->Next();
    }
}

void ParentNode::WalkDescendant(NodeOperation& operation)
{
    Node* child = firstChild;
    while (child)
    {
        child->WalkDescendantOrSelf(operation);
        child = child->Next();
    }
}

void ParentNode::WalkDescendantOrSelf(NodeOperation& operation)
{
    Node::WalkDescendantOrSelf(operation);
    Node* child = firstChild;
    while (child)
    {
        child->WalkDescendantOrSelf(operation);
        child = child->Next();
    }
}

void ParentNode::WalkPreceding(NodeOperation& operation)
{
    Node* preceding = Prev();
    if (preceding)
    {
        preceding->WalkPrecedingOrSelf(operation);
    }
}

void ParentNode::WalkPrecedingOrSelf(NodeOperation& operation)
{
    Node::WalkPrecedingOrSelf(operation);
    Node* child = lastChild;
    while (child)
    {
        child->WalkPrecedingOrSelf(operation);
        child = child->Prev();
    }
}

} // namespace soul::xml
