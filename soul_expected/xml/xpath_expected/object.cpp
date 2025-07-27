// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.xpath.object;

import soul_expected.xml.text;
import soul_expected.xml.processing.instruction;
import soul_expected.xml.comment;
import util_expected;

namespace soul_expected::xml::xpath {

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

void NodeSet::Add(soul_expected::xml::Node* node)
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
        return std::unexpected<int>(util::AllocateError("error: soul_expected::xml::xpath::NodeSet::GetNode: invalid index"));
    }
}

std::expected<soul_expected::xml::Element*, int> NodeSet::ToXmlElement() const
{
    soul_expected::xml::Element* element = soul_expected::xml::MakeElement("node-set");
    element->SetAttribute("count", std::to_string(nodes.size()));
    int n = static_cast<int>(nodes.size());
    for (int i = 0; i < n; ++i)
    {
        soul_expected::xml::Node* node = nodes[i];
        soul_expected::xml::Element* nodeElement = soul_expected::xml::MakeElement("node");
        nodeElement->SetAttribute("kind", soul_expected::xml::NodeKindStr(node->Kind()));
        nodeElement->SetAttribute("name", node->Name());
        if (node->IsElementNode())
        {
            soul_expected::xml::Element* elementNode = static_cast<soul_expected::xml::Element*>(node);
            soul_expected::xml::Element* attributesElement = soul_expected::xml::MakeElement("attributes");
            auto rv = nodeElement->AppendChild(attributesElement);
            if (!rv) return std::unexpected<int>(rv.error());
            for (const auto& attr : elementNode->Attributes())
            {
                soul_expected::xml::AttributeNode* attributeNode = attr.second.get();
                soul_expected::xml::Element* attributeElement = soul_expected::xml::MakeElement("attribute");
                attributeElement->SetAttribute("name", attributeNode->Name());
                attributeElement->SetAttribute("value", attributeNode->Value());
                rv = attributesElement->AppendChild(attributeElement);
                if (!rv) return std::unexpected<int>(rv.error());
            }
        }
        else if (node->IsAttributeNode())
        {
            soul_expected::xml::AttributeNode* attributeNode = static_cast<soul_expected::xml::AttributeNode*>(node);
            soul_expected::xml::Element* attributeElement = soul_expected::xml::MakeElement("attribute");
            attributeElement->SetAttribute("name", attributeNode->Name());
            attributeElement->SetAttribute("value", attributeNode->Value());
            auto rv = nodeElement->AppendChild(attributeElement);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        else if (node->IsTextNode())
        {
            soul_expected::xml::Text* textNode = static_cast<soul_expected::xml::Text*>(node);
            soul_expected::xml::Element* textElement = soul_expected::xml::MakeElement("text");
            textElement->SetAttribute("value", textNode->Data());
            auto rv = nodeElement->AppendChild(textElement);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        else if (node->IsProcessingInstructionNode())
        {
            soul_expected::xml::ProcessingInstruction* processingInstructionNode = static_cast<soul_expected::xml::ProcessingInstruction*>(node);
            soul_expected::xml::Element* processingInstructionElement = soul_expected::xml::MakeElement("processing-instruction");
            processingInstructionElement->SetAttribute("target", processingInstructionNode->Target());
            processingInstructionElement->SetAttribute("data", processingInstructionNode->Data());
            auto rv = nodeElement->AppendChild(processingInstructionElement);
            if (!rv) return std::unexpected<int>(rv.error());
        }
        else if (node->IsCommentNode())
        {
            soul_expected::xml::Comment* commentNode = static_cast<soul_expected::xml::Comment*>(node);
            soul_expected::xml::Element* commentElement = soul_expected::xml::MakeElement("comment");
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

std::expected<soul_expected::xml::Element*, int> Boolean::ToXmlElement() const
{
    soul_expected::xml::Element* element = soul_expected::xml::MakeElement("boolean");
    element->SetAttribute("value", value ? "true" : "false");
    return element;
}

Number::Number() : Object(ObjectKind::number), value(0.0)
{
}

Number::Number(double value_) : Object(ObjectKind::number), value(value_)
{
}

std::expected<soul_expected::xml::Element*, int> Number::ToXmlElement() const
{
    soul_expected::xml::Element* element = soul_expected::xml::MakeElement("number");
    element->SetAttribute("value", std::to_string(value));
    return element;
}

String::String() : Object(ObjectKind::string), value()
{
}

String::String(const std::string& value_) : Object(ObjectKind::string), value(value_)
{
}

std::expected<soul_expected::xml::Element*, int> String::ToXmlElement() const
{
    soul_expected::xml::Element* element = soul_expected::xml::MakeElement("string");
    element->SetAttribute("value", value);
    return element;
}

} // namespace soul_expected::xml::xpath
