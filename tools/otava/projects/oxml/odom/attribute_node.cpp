// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.xml.attribute.node;

import util;

namespace soul::xml {

std::expected<std::string, int> AttrValueEscape(const std::string& attributeValue, char delimiter)
{
    std::string result;
    auto u = util::ToUtf32(attributeValue);
    if (!u) return std::unexpected<int>(u.error());
    std::u32string attValue = *u;
    for (char32_t c : attValue)
    {
        switch (c)
        {
            case '<': { result.append("&lt;"); break; }
            case '&': { result.append("&amp;"); break; }
            case '"': { if (delimiter == '"') result.append("&quot;"); else result.append(1, '"'); break; }
            case '\'': { if (delimiter == '\'') result.append("&apos;"); else result.append(1, '\''); break; }
            default:
            {
                if (static_cast<int>(c) >= 32 && static_cast<int>(c) < 127)
                {
                    result.append(1, static_cast<char>(c));
                }
                else
                {
                    int codePoint = static_cast<int>(c);
                    std::string charText = "&#";
                    charText.append(std::to_string(codePoint)).append(";");
                    result.append(charText);
                }
                break;
            }
        }
    }
    return std::expected<std::string, int>(result);
}

std::expected<std::string, int> MakeXmlAttrValue(const std::string& value)
{
    std::string result;
    if (value.find('"') == std::string::npos)
    {
        result.append(1, '"');
        auto e = AttrValueEscape(value, '"');
        if (!e) return e;
        result.append(*e);
        result.append(1, '"');
    }
    else if (value.find('\'') == std::string::npos)
    {
        result.append(1, '\'');
        auto e = AttrValueEscape(value, '\'');
        if (!e) return e;
        result.append(*e);
        result.append(1, '\'');
    }
    else
    {
        result.append(1, '"');
        auto e = AttrValueEscape(value, '"');
        if (!e) return e;
        result.append(*e);
        result.append(1, '"');
    }
    return std::expected<std::string, int>(result);
}

AttributeNode::AttributeNode(const soul::ast::SourcePos& sourcePos_, const std::string& name_, const std::string& value_) :
    Node(NodeKind::attributeNode, sourcePos_, name_), value(value_)
{
}

void AttributeNode::SetValue(const std::string& value_)
{
    value = value_;
}

std::expected<bool, int> AttributeNode::Write(util::CodeFormatter& formatter)
{
    auto rv = formatter.Write(" " + Name() + "=");
    if (!rv) return rv;
    auto v = MakeXmlAttrValue(value);
    if (!v) return std::unexpected<int>(v.error());
    return formatter.Write(*v);
}

AttributeNode* MakeAttribute(const std::string& name, const std::string& value)
{
    return new AttributeNode(soul::ast::SourcePos(), name, value);
}

} // namespace soul::xml
