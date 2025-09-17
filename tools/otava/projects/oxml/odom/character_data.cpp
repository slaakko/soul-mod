// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.xml.character.data;

import util;

namespace soul::xml {

std::expected<std::string, int> XmlCharDataEscape(const std::string& text)
{
    std::string result;
    auto u = util::ToUtf32(text);
    if (!u) return std::unexpected<int>(u.error());
    std::u32string value = *u;
    for (char32_t c : value)
    {
        switch (c)
        {
            case '<': { result.append("&lt;"); break; }
            case '&': { result.append("&amp;"); break; }
            case '\r': case '\n': { result.append(1, static_cast<char>(c)); break; }
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

CharacterData::CharacterData(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::string& name_) :
    CharacterData(kind_, sourcePos_, name_, std::string())
{
}

CharacterData::CharacterData(NodeKind kind_, const soul::ast::SourcePos& sourcePos_, const std::string& name_, const std::string& data_) :
    Node(kind_, sourcePos_, name_), data(data_)
{
}

std::expected<bool, int> CharacterData::Write(util::CodeFormatter& formatter)
{
    auto e = XmlCharDataEscape(data);
    if (!e) return std::unexpected<int>(e.error());
    return formatter.Write(*e);
}

bool CharacterData::ValueContainsNewLine() const
{
    return data.find('\n') != std::string::npos;
}

} // namespace soul::xml
