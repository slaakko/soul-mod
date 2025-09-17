// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.xml.element;

import soul.xml.visitor;
import soul.xml.node.operation;

namespace soul::xml {

Element::Element(const soul::ast::SourcePos& sourcePos_, const std::string& name_) : ParentNode(NodeKind::elementNode, sourcePos_, name_)
{
}

AttributeNode* Element::GetAttributeNode(const std::string& attributeName) const
{
    auto it = attributeMap.find(attributeName);
    if (it != attributeMap.cend())
    {
        return it->second.get();
    }
    else
    {
        return nullptr;
    }
}

std::string Element::GetAttribute(const std::string& name) const
{
    AttributeNode* attributeNode = GetAttributeNode(name);
    if (attributeNode)
    {
        return attributeNode->Value();
    }
    else
    {
        return std::string();
    }
}

void Element::AddAttribute(AttributeNode* attributeNode)
{
    attributeMap[attributeNode->Name()] = std::unique_ptr<AttributeNode>(attributeNode);
}

void Element::SetAttribute(const soul::ast::SourcePos& sourcePos, const std::string& name, const std::string& value)
{
    AttributeNode* attributeNode = GetAttributeNode(name);
    if (attributeNode)
    {
        attributeNode->SetValue(value);
    }
    else
    {
        AddAttribute(new AttributeNode(sourcePos, name, value));
    }
}

void Element::SetAttribute(const std::string& name, const std::string& value)
{
    SetAttribute(soul::ast::SourcePos(), name, value);
}

std::expected<bool, int> Element::WriteAttributes(util::CodeFormatter& formatter)
{
    for (const auto& a : attributeMap)
    {
        auto rv = a.second->Write(formatter);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

void Element::Accept(Visitor& visitor)
{
    visitor.BeginVisit(*this);
    ParentNode::Accept(visitor);
    visitor.EndVisit(*this);
}

std::expected<bool, int> Element::Write(util::CodeFormatter& formatter)
{
    if (HasChildNodes())
    {
        if (attributeMap.empty())
        {
            auto rv = formatter.Write("<" + Name() + ">");
            if (!rv) return rv;
        }
        else
        {
            auto rv = formatter.Write("<" + Name());
            if (!rv) return rv;
            rv = WriteAttributes(formatter);
            if (!rv) return rv;
            rv = formatter.Write(">");
            if (!rv) return rv;
        }

        bool prevPreserveSpace = formatter.PreserveSpace();
        if (GetAttribute("xml:space") == "preserve")
        {
            formatter.SetPreserveSpace(true);
        }
        bool preserveSpace = formatter.PreserveSpace() || !HasMultilineContent();
        if (!preserveSpace)
        {
            formatter.WriteLine();
            formatter.IncIndent();
        }
        auto rv = ParentNode::Write(formatter);
        if (!rv) return rv;
        if (!preserveSpace)
        {
            formatter.DecIndent();
            rv = formatter.WriteLine("</" + Name() + ">");
            if (!rv) return rv;
        }
        else if (prevPreserveSpace)
        {
            rv = formatter.Write("</" + Name() + ">");
            if (!rv) return rv;
        }
        else
        {
            rv = formatter.WriteLine("</" + Name() + ">");
            if (!rv) return rv;
        }
        formatter.SetPreserveSpace(prevPreserveSpace);
    }
    else
    {
        if (attributeMap.empty())
        {
            auto rv = formatter.WriteLine("<" + Name() + "/>");
            if (!rv) return rv;
        }
        else
        {
            auto rv = formatter.Write("<" + Name());
            if (!rv) return rv;
            rv = WriteAttributes(formatter);
            if (!rv) return rv;
            rv = formatter.WriteLine("/>");
            if (!rv) return rv;
        }
    }
    return std::expected<bool, int>(true);
}

bool Element::HasMultilineContent() const
{
    if (FirstChild() != LastChild())
    {
        return true;
    }
    Node* child = FirstChild();
    if (child)
    {
        if (child->IsElementNode() || child->IsDocumentNode())
        {
            return true;
        }
        if (child->ValueContainsNewLine())
        {
            return true;
        }
    }
    return false;
}

void Element::WalkAttribute(NodeOperation& operation)
{
    for (const auto& attribute : attributeMap)
    {
        operation.Apply(attribute.second.get());
    }
}

Element* MakeElement(const std::string& name)
{
    return new Element(soul::ast::SourcePos(), name);
}

} // namespace soul::xml
