// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.element;

import std;
import soul.xml.parent.node;
import soul.xml.attribute.node;

export namespace soul::xml {

class Element : public ParentNode
{
public:
    Element(const soul::ast::SourcePos& sourcePos_, const std::string& name_);
    inline const std::map<std::string, std::unique_ptr<AttributeNode>>& Attributes() const { return attributeMap; }
    AttributeNode* GetAttributeNode(const std::string& attributeName) const;
    std::string GetAttribute(const std::string& name) const;
    void AddAttribute(AttributeNode* attributeNode);
    void SetAttribute(const soul::ast::SourcePos& sourcePos, const std::string& name, const std::string& value);
    void SetAttribute(const std::string& name, const std::string& value);
    inline bool HasAttributes() const final { return !attributeMap.empty(); }
    void Accept(Visitor& visitor) override;
    void Write(util::CodeFormatter& formatter) override;
    void WalkAttribute(NodeOperation& operation) override;
private:
    void WriteAttributes(util::CodeFormatter& formatter);
    bool HasMultilineContent() const;
    std::map<std::string, std::unique_ptr<AttributeNode>> attributeMap;
};

Element* MakeElement(const std::string& name);

} // namespace soul::xml
