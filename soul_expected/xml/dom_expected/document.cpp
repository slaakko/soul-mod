// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.document;

import util_expected;
import soul_expected.xml.visitor;
import soul_expected.xml.index;
import soul_expected.lexer.file.map;
import soul_expected.lexer.error;

namespace soul_expected::xml {

Document::Document() :
    ParentNode(NodeKind::documentNode, soul_expected::ast::SourcePos(), "document"), documentElement(nullptr), indexValid(false), xmlStandalone(false)
{
}

Document::Document(const soul_expected::ast::SourcePos& sourcePos_) :
    ParentNode(NodeKind::documentNode, sourcePos_, "document"), documentElement(nullptr), indexValid(false), xmlStandalone(false)
{
}

Element* Document::GetElementById(const std::string& elementId)
{
    if (!indexValid)
    {
        index.clear();
        BuildIndex(this);
        indexValid = true;
    }
    auto it = index.find(elementId);
    if (it != index.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

std::expected<bool, int> Document::AppendChild(Node* child)
{
    if (!child)
    {
        auto sp = GetSourcePos();
        return std::unexpected<int>(util::AllocateError("could not append node: given child is null: line=" + std::to_string(sp.line)));
    }
    auto rv = CheckValidInsert(child);
    if (!rv) return rv;
    rv = ParentNode::AppendChild(child);
    if (!rv) return rv;
    if (child->IsElementNode())
    {
        documentElement = static_cast<Element*>(child);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Document::InsertBefore(Node* newChild, Node* refChild)
{
    if (!newChild)
    {
        auto sp = GetSourcePos();
        return std::unexpected<int>(util::AllocateError("could not insert node: given child is null: line=" + std::to_string(sp.line)));
    }
    auto rv = CheckValidInsert(newChild);
    if (!rv) return rv;
    rv = ParentNode::InsertBefore(newChild, refChild);
    if (!rv) return rv;
    if (newChild->IsElementNode())
    {
        documentElement = static_cast<Element*>(newChild);
    }
    return std::expected<bool, int>(true);
}

std::expected<std::unique_ptr<Node>, int> Document::RemoveChild(Node* child)
{
    if (!child)
    {
        return std::unexpected<int>(util::AllocateError("could not remove node: given child is null: line=" + std::to_string(GetSourcePos().line)));
    }
    auto rv = ParentNode::RemoveChild(child);
    if (!rv) return rv;
    std::unique_ptr<Node> removedChild = std::move(*rv);
    if (removedChild.get() == documentElement)
    {
        documentElement = nullptr;
    }
    return std::expected<std::unique_ptr<Node>, int>(std::move(removedChild));
}

std::expected<std::unique_ptr<Node>, int> Document::ReplaceChild(Node* newChild, Node* oldChild)
{
    if (!newChild)
    {
        return std::unexpected<int>(util::AllocateError("could not replace node: given child is null: line=" + std::to_string(GetSourcePos().line)));
    }
    if (!oldChild)
    {
        return std::unexpected<int>(util::AllocateError("could not replace node: given old child is null: line=" + std::to_string(GetSourcePos().line)));
    }
    auto rv = CheckValidInsert(newChild);
    if (!rv) return std::unexpected<int>(rv.error());
    if (newChild->IsElementNode())
    {
        auto rv = RemoveChild(oldChild);
        if (!rv) return rv;
        std::unique_ptr<Node> removed = std::move(*rv);
        auto a = AppendChild(newChild);
        if (!a) return std::unexpected<int>(a.error());
        return std::expected<std::unique_ptr<Node>, int>(std::move(removed));
    }
    else
    {
        return ParentNode::ReplaceChild(newChild, oldChild);
    }
}

void Document::Accept(Visitor& visitor)
{
    visitor.BeginVisit(*this);
    ParentNode::Accept(visitor);
    visitor.EndVisit(*this);
}

std::expected<bool, int> Document::Write(util::CodeFormatter& formatter)
{
    if (!xmlVersion.empty() && !xmlEncoding.empty())
    {
        std::expected<bool, int> rv = formatter.WriteLine("<?xml version=\"" + xmlVersion + "\" encoding=\"" + xmlEncoding + "\"?>");
        if (!rv) return rv;
    }
    return ParentNode::Write(formatter);
}

void Document::InvalidateIndex()
{
    indexValid = false;
}

std::expected<bool, int> Document::CheckValidInsert(Node* node)
{
    if (node->IsElementNode())
    {
        if (documentElement)
        {
            std::string errorMessage = "attempted to insert an element to a document that already has a document element";
            soul_expected::ast::SourcePos sourcePos = GetSourcePos();
            soul_expected::lexer::FileMap* fileMap = soul_expected::lexer::GetGlobalFileMap();
            if (sourcePos.IsValid() && fileMap)
            {
                auto m = soul_expected::lexer::MakeMessage("error", errorMessage, sourcePos, *fileMap);
                if (!m) return std::unexpected<int>(m.error());
                errorMessage = *m;
            }
            return std::unexpected<int>(util::AllocateError(errorMessage));
        }
    }
    return std::expected<bool, int>(true);
}

std::unique_ptr<Document> MakeDocument()
{
    return std::unique_ptr<Document>(new Document(soul_expected::ast::SourcePos()));
}

} // namespace soul_expected::xml
