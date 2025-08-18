// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.lexer.xml.parsing.log;

namespace soul::lexer {

XmlParsingLog::XmlParsingLog(std::ostream& stream_) : ParsingLog(), formatter(stream_)
{
    formatter.SetIndentSize(1);
}

XmlParsingLog::XmlParsingLog(std::ostream& stream_, int maxLineLength_) : ParsingLog(maxLineLength_), formatter(stream_)
{
    formatter.SetIndentSize(1);
}

void XmlParsingLog::IncIndent()
{
    formatter.IncIndent();
}

void XmlParsingLog::DecIndent()
{
    formatter.DecIndent();
}

std::expected<bool, int> XmlParsingLog::WriteBeginRule(const std::string& ruleName)
{
    return Write("<" + ruleName + ">");
}

std::expected<bool, int> XmlParsingLog::WriteEndRule(const std::string& ruleName)
{
    return Write("</" + ruleName + ">");
}

std::expected<bool, int> XmlParsingLog::WriteTry(const std::string& s)
{
    return WriteElement("try", s);
}

std::expected<bool, int> XmlParsingLog::WriteSuccess(const std::string& match)
{
    return WriteElement("success", match);
}

std::expected<bool, int> XmlParsingLog::WriteFail()
{
    return Write("<fail/>");
}

std::expected<bool, int> XmlParsingLog::WriteElement(const std::string& elementName, const std::string& elementContent)
{
    std::expected<std::u32string, int> rv = util::ToUtf32(elementContent);
    if (!rv) return std::unexpected<int>(rv.error());
    std::u32string content = std::move(*rv);
    std::string converted = XmlEscape(content.c_str(), content.c_str() + content.length());
    int convertedLength = static_cast<int>(converted.length());
    int lineLength = 2 * static_cast<int>(elementName.length()) + 5 + convertedLength;
    std::string s = converted;
    if (lineLength > MaxLineLength())
    {
        lineLength += 3;
        s = converted.substr(0, std::max(0, convertedLength - (lineLength - MaxLineLength()))) + "...";
    }
    return Write("<" + elementName + ">" + s + "</" + elementName + ">");
}

std::expected<bool, int> XmlParsingLog::Write(const std::string& s)
{
    return formatter.WriteLine(s);
}

} // namespace soul::lexer
