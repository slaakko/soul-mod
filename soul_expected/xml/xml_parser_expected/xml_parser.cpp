// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.parser;

import util_expected;
import soul_expected.lexer.trivial;
import soul_expected.xml.parser.rules;
import soul_expected.xml.document.parser;
import soul_expected.xml.processor;

namespace soul_expected::xml::parser {

std::expected<bool, int> ParseXmlFile(const std::string& xmlFileName, XmlContentHandler* contentHandler)
{
    auto rv = util::ReadFile(xmlFileName);
    if (!rv) return std::unexpected<int>(rv.error());
    std::string xmlContent = *rv;
    auto u = util::ToUtf32(xmlContent);
    if (!u) return std::unexpected<int>(u.error());
    std::u32string fileContent = *u;
    return ParseXmlContent(fileContent, xmlFileName, contentHandler);
}

std::expected<bool, int> ParseXmlFile(const std::string& xmlFileName, XmlContentHandler* contentHandler, soul_expected::lexer::FileMap& fileMap)
{
    auto rv = util::ReadFile(xmlFileName);
    if (!rv) return std::unexpected<int>(rv.error());
    std::string xmlContent = *rv;
    auto u = util::ToUtf32(xmlContent);
    if (!u) return std::unexpected<int>(u.error());
    std::u32string fileContent = *u;
    return ParseXmlContent(std::move(fileContent), xmlFileName, contentHandler, fileMap);
}

std::expected<bool, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId, XmlContentHandler* contentHandler)
{
    std::expected<std::u32string, int> rv = util::ToUtf32(xmlContent);
    if (!rv) return std::unexpected<int>(rv.error());
    return ParseXmlContent(*rv, systemId, contentHandler);
}

std::expected<bool, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId, XmlContentHandler* contentHandler, soul_expected::lexer::FileMap& fileMap)
{
    std::expected<std::u32string, int> rv = util::ToUtf32(xmlContent);
        if (!rv) return std::unexpected<int>(rv.error());
    return ParseXmlContent(std::move(*rv), systemId, contentHandler, fileMap);
}

std::expected<bool, int> ParseXmlContent(const std::u32string& xmlContent, const std::string& systemId, XmlContentHandler* contentHandler)
{
    auto lexer = soul_expected::lexer::trivial::MakeLexer(xmlContent.c_str(), xmlContent.c_str() + xmlContent.length(), systemId);
    lexer.SetRuleNameMapPtr(soul_expected::xml::parser::rules::GetRuleNameMapPtr());
    soul_expected::xml::processor::XmlProcessor processor(contentHandler);
    using LexerType = decltype(lexer);
    return soul_expected::xml::document::parser::XmlParser<LexerType>::Parse(lexer, &processor);
}

std::expected<bool, int> ParseXmlContent(std::u32string&& xmlContent, const std::string& systemId, XmlContentHandler* contentHandler, soul_expected::lexer::FileMap& fileMap)
{
    auto lexer = soul_expected::lexer::trivial::MakeLexer(xmlContent.c_str(), xmlContent.c_str() + xmlContent.length(), systemId);
    lexer.SetRuleNameMapPtr(soul_expected::xml::parser::rules::GetRuleNameMapPtr());
    std::int32_t fileId = fileMap.MapFile(systemId);
    lexer.SetFile(fileId);
    soul_expected::xml::processor::XmlProcessor processor(contentHandler);
    using LexerType = decltype(lexer);
    auto rv = soul_expected::xml::document::parser::XmlParser<LexerType>::Parse(lexer, &processor);
    if (!rv) return rv;
    fileMap.AddFileContent(fileId, std::move(xmlContent), std::move(lexer.GetLineStartIndeces()));
    return std::expected<bool, int>(true);
}

} // namespace soul_expected::xml::parser
