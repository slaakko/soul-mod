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

void Element::WriteAttributes(util::CodeFormatter& formatter)
{
    for (const auto& a : attributeMap)
    {
        a.second->Write(formatter);
    }
}

void Element::Accept(Visitor& visitor)
{
    visitor.BeginVisit(*this);
    ParentNode::Accept(visitor);
    visitor.EndVisit(*this);
}

void Element::Write(util::CodeFormatter& formatter)
{
    if (HasChildNodes())
    {
        if (attributeMap.empty())
        {
            formatter.Write("<" + Name() + ">");
        }
        else
        {
            formatter.Write("<" + Name());
            WriteAttributes(formatter);
            formatter.Write(">");
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
        ParentNode::Write(formatter);
        if (!preserveSpace)
        {
            formatter.DecIndent();
            formatter.WriteLine("</" + Name() + ">");
        }
        else if (prevPreserveSpace)
        {
            formatter.Write("</" + Name() + ">");
        }
        else
        {
            formatter.WriteLine("</" + Name() + ">");
        }
        formatter.SetPreserveSpace(prevPreserveSpace);
    }
    else
    {
        if (attributeMap.empty())
        {
            formatter.WriteLine("<" + Name() + "/>");
        }
        else
        {
            formatter.Write("<" + Name());
            WriteAttributes(formatter);
            formatter.WriteLine("/>");
        }
    }
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
