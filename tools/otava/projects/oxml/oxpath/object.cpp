// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.xml.xpath.object;

import soul.xml.text;
import soul.xml.processing.instruction;
import soul.xml.comment;
import util;

namespace soul::xml::xpath {

std::string ObjectKindStr(ObjectKind kind)
{
    switch (kind)
    {
        case ObjectKind::nodeSet:
        {
            return "node-set";
        }
        case ObjectKind::boolean:
        {
            return "Boolean";
        }
        case ObjectKind::number:
        {
            return "number";
        }
        case ObjectKind::string:
        {
            return "string";
        }
    }
    return std::string();
}

Object::Object(ObjectKind kind_) : kind(kind_)
{
}

Object::~Object()
{
}

NodeSet::NodeSet() : Object(ObjectKind::nodeSet)
{
}

void NodeSet::Add(soul::xml::Node* node)
{
    if (std::find(nodes.cbegin(), nodes.cend(), node) == nodes.cend())
    {
        nodes.push_back(node);
    }
}

std::expected<Node*, int> NodeSet::GetNode(int index) const
{
    if (index >= 0 && index < nodes.size())
    {
        return nodes[index];
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("error: soul::xml::xpath::NodeSet::GetNode: invalid index"));
    }
}

std::expected<soul::xml::Element*, int> NodeSet::ToXmlElement() const
{
    soul::xml::Element* element = soul::xml::MakeElement("node-set");
    element->SetAttribute("count", std::to_string(nodes.size()));
    int n = static_cast<int>(nodes.size());
    for (int i = 0; i < n; ++i)
    {
        soul::xml::Node* node = nodes[i];
        soul::xml::Element* nodeElement = soul::xml::MakeElement("node");
        nodeElement->SetAttribute("kind", soul::xml::NodeKindStr(node->Kind()));
        nodeElement->SetAttribute("name", node->Name());
        if (node->IsElementNode())
        {
            soul::xml::Element* elementNode = static_cast<soul::xml::Element*>(node);
            soul::xml::Element* attributesElement = soul::xml::MakeElement("attributes");
            auto rv = nodeElement->AppendChild(attributesElement);
            if (!rv) return std::unexpected<int>(rv.error());
            for (const auto& attr : elementNode->Attributes())
            {
                soul::xml::AttributeNode* attributeNode = attr.second;
                soul::xml::Element* attributeElement = soul::xml::MakeElement("attribute");
                attributeElement->SetAttribute("name", attributeNode->Name());
                attributeElement->SetAttribute("value", attributeNode->Value());
                rv = attributesElement->AppendChild(attributeElement);
                if (!rv) return std::unexpected<int>(rv.error());
            }
        }
        else if (node->IsAttributeNode())
        {
            soul::xml::AttributeNode* attributeNode = static_cast<soul::xml::AttributeNode*>(node);
            soul::xml::Element* attributeElement = soul::xml::MakeElement("attribute");
            attributeElement->SetAttribute("name", attributeNode->Name());
            attributeElement->SetAttribute("value", attributeNode->Value());
            auto rv = nodeElement->AppendChild(attributeElement);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        else if (node->IsTextNode())
        {
            soul::xml::Text* textNode = static_cast<soul::xml::Text*>(node);
            soul::xml::Element* textElement = soul::xml::MakeElement("text");
            textElement->SetAttribute("value", textNode->Data());
            auto rv = nodeElement->AppendChild(textElement);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        else if (node->IsProcessingInstructionNode())
        {
            soul::xml::ProcessingInstruction* processingInstructionNode = static_cast<soul::xml::ProcessingInstruction*>(node);
            soul::xml::Element* processingInstructionElement = soul::xml::MakeElement("processing-instruction");
            processingInstructionElement->SetAttribute("target", processingInstructionNode->Target());
            processingInstructionElement->SetAttribute("data", processingInstructionNode->Data());
            auto rv = nodeElement->AppendChild(processingInstructionElement);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        else if (node->IsCommentNode())
        {
            soul::xml::Comment* commentNode = static_cast<soul::xml::Comment*>(node);
            soul::xml::Element* commentElement = soul::xml::MakeElement("comment");
            commentElement->SetAttribute("data", commentNode->Data());
            auto rv = nodeElement->AppendChild(commentElement);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        auto rv = element->AppendChild(nodeElement);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return element;
}

Boolean::Boolean() : Object(ObjectKind::boolean), value(false)
{
}

Boolean::Boolean(bool value_) : Object(ObjectKind::boolean), value(value_)
{
}

std::expected<soul::xml::Element*, int> Boolean::ToXmlElement() const
{
    soul::xml::Element* element = soul::xml::MakeElement("boolean");
    element->SetAttribute("value", value ? "true" : "false");
    return element;
}

Number::Number() : Object(ObjectKind::number), value(0.0)
{
}

Number::Number(double value_) : Object(ObjectKind::number), value(value_)
{
}

std::expected<soul::xml::Element*, int> Number::ToXmlElement() const
{
    soul::xml::Element* element = soul::xml::MakeElement("number");
    element->SetAttribute("value", std::to_string(value));
    return element;
}

String::String() : Object(ObjectKind::string), value()
{
}

String::String(const std::string& value_) : Object(ObjectKind::string), value(value_)
{
}

std::expected<soul::xml::Element*, int> String::ToXmlElement() const
{
    soul::xml::Element* element = soul::xml::MakeElement("string");
    element->SetAttribute("value", value);
    return element;
}

} // namespace soul::xml::xpath
