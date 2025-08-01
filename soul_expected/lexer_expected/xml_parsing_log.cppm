// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.lexer.xml.parsing.log;

import std;
import util_expected;
import soul_expected.lexer.parsing.log;

export namespace soul_expected::lexer {

class XmlParsingLog : public ParsingLog
{
public:
    XmlParsingLog(std::ostream& stream_);
    XmlParsingLog(std::ostream& stream_, int maxLineLength_);
    void IncIndent() override;
    void DecIndent() override;
    std::expected<bool, int> WriteBeginRule(const std::string& ruleName) override;
    std::expected<bool, int> WriteEndRule(const std::string& ruleName) override;
    std::expected<bool, int> WriteTry(const std::string& s) override;
    std::expected<bool, int> WriteSuccess(const std::string& match) override;
    std::expected<bool, int> WriteFail() override;
    std::expected<bool, int> WriteElement(const std::string& elementName, const std::string& elementContent);
    std::expected<bool, int> Write(const std::string& s);
    inline util::CodeFormatter& Formatter() { return formatter; }
private:
    util::CodeFormatter formatter;
};

template<typename Char>
std::string XmlHexEscape(Char c)
{
    return "&#x" + util::ToHexString(std::uint32_t(c)) + ";";
}

template<typename Char>
std::string XmlCharStr(Char c)
{
    switch (c)
    {
    case '&': return "&amp;";
    case '<': return "&lt;";
    case '>': return "&gt;";
    case '\a': return "\\a";
    case '\b': return "\\b";
    case '\f': return "\\f";
    case '\n': return "\\n";
    case '\r': return "\\r";
    case '\t': return "\\t";
    case '\v': return "\\v";
    default:
    {
        if ((std::int32_t(c) >= 32 && std::int32_t(c) <= 126))
        {
            return std::string(1, char(c));
        }
        else
        {
            return XmlHexEscape(c);
        }
    }
    }
    return std::string();
}

template<typename Char>
std::string XmlEscape(const Char* begin, const Char* end)
{
    std::string result;
    result.reserve(2 * (end - begin));
    for (const Char* i = begin; i != end; ++i)
    {
        result.append(XmlCharStr(*i));
    }
    return result;
}

} // namespace soul_expected::lexer
