// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.attribute.node;

import std;
import soul.xml.node;

export namespace soul::xml {

std::expected<std::string, int> AttrValueEscape(const std::string& attributeValue, char delimiter);
std::expected<std::string, int> MakeXmlAttrValue(const std::string& value);

class AttributeNode : public Node
{
public:
    AttributeNode(const soul::ast::SourcePos& sourcePos_, const std::string& name_, const std::string& value_);
    inline const std::string& Value() const { return value; }
    void SetValue(const std::string& value_);
    std::expected<bool, int> Write(util::CodeFormatter& formatter) override;
private:
    std::string value;
};

AttributeNode* MakeAttribute(const std::string& name, const std::string& value);

} // namespace soul::xml
