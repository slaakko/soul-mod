// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.element;

import std;
import soul_expected.xml.parent.node;
import soul_expected.xml.attribute.node;

export namespace soul_expected::xml {

class Element : public ParentNode
{
public:
    Element(const soul_expected::ast::SourcePos& sourcePos_, const std::string& name_);
    const std::map<std::string, std::unique_ptr<AttributeNode>>& Attributes() const { return attributeMap; }
    AttributeNode* GetAttributeNode(const std::string& attributeName) const;
    std::string GetAttribute(const std::string& name) const;
    void AddAttribute(AttributeNode* attributeNode);
    void SetAttribute(const soul_expected::ast::SourcePos& sourcePos, const std::string& name, const std::string& value);
    void SetAttribute(const std::string& name, const std::string& value);
    bool HasAttributes() const final { return !attributeMap.empty(); }
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(util::CodeFormatter& formatter) override;
    void WalkAttribute(NodeOperation& operation) override;
private:
    std::expected<bool, int> WriteAttributes(util::CodeFormatter& formatter);
    bool HasMultilineContent() const;
    std::map<std::string, std::unique_ptr<AttributeNode>> attributeMap;
};

Element* MakeElement(const std::string& name);

} // namespace soul_expected::xml
