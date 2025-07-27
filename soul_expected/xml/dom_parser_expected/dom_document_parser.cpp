// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.dom.document.parser;

import soul_expected.xml.document.handler;
import soul_expected.xml.parser;

namespace soul_expected::xml {

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlFile(const std::string& xmlFileName)
{
    return ParseXmlFile(xmlFileName, ParsingFlags::none);
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlFile(const std::string& xmlFileName, ParsingFlags parsingFlags)
{
    DocumentHandler documentHandler(parsingFlags);
    auto rv = soul_expected::xml::parser::ParseXmlFile(xmlFileName, &documentHandler);
    if (!rv) return std::unexpected<int>(rv.error());
    return documentHandler.GetDocument();
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlFile(const std::string& xmlFileName, soul_expected::lexer::FileMap& fileMap)
{
    return ParseXmlFile(xmlFileName, fileMap, ParsingFlags::none);
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlFile(const std::string& xmlFileName, soul_expected::lexer::FileMap& fileMap, ParsingFlags parsingFlags)
{
    DocumentHandler documentHandler(parsingFlags);
    auto rv = soul_expected::xml::parser::ParseXmlFile(xmlFileName, &documentHandler, fileMap);
    if (!rv) return std::unexpected<int>(rv.error());
    return documentHandler.GetDocument();
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId)
{
    return ParseXmlContent(xmlContent, systemId, ParsingFlags::none);
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId, ParsingFlags parsingFlags)
{
    DocumentHandler documentHandler(parsingFlags);
    auto rv = soul_expected::xml::parser::ParseXmlContent(xmlContent, systemId, &documentHandler);
    if (!rv) return std::unexpected<int>(rv.error());
    return documentHandler.GetDocument();
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId, soul_expected::lexer::FileMap& fileMap)
{
    return ParseXmlContent(xmlContent, systemId, fileMap, ParsingFlags::none);
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId, soul_expected::lexer::FileMap& fileMap, ParsingFlags parsingFlags)
{
    DocumentHandler documentHandler(parsingFlags);
    auto rv = soul_expected::xml::parser::ParseXmlContent(xmlContent, systemId, &documentHandler, fileMap);
    if (!rv) return std::unexpected<int>(rv.error());
    return documentHandler.GetDocument();
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::u32string& xmlContent, const std::string& systemId)
{
    return ParseXmlContent(xmlContent, systemId, ParsingFlags::none);
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::u32string& xmlContent, const std::string& systemId, ParsingFlags parsingFlags)
{
    DocumentHandler documentHandler(parsingFlags);
    auto rv = soul_expected::xml::parser::ParseXmlContent(xmlContent, systemId, &documentHandler);
    if (!rv) return std::unexpected<int>(rv.error());
    return documentHandler.GetDocument();
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(std::u32string&& xmlContent, const std::string& systemId, soul_expected::lexer::FileMap& fileMap)
{
    return ParseXmlContent(std::move(xmlContent), systemId, fileMap, ParsingFlags::none);
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(std::u32string&& xmlContent, const std::string& systemId, soul_expected::lexer::FileMap& fileMap, ParsingFlags parsingFlags)
{
    DocumentHandler documentHandler(parsingFlags);
    auto rv = soul_expected::xml::parser::ParseXmlContent(std::move(xmlContent), systemId, &documentHandler, fileMap);
    if (!rv) return std::unexpected<int>(rv.error());
    return documentHandler.GetDocument();
}

std::expected<bool, int> SendDocument(util::TcpSocket& socket, soul_expected::xml::Document& document)
{
    std::stringstream sstream;
    util::CodeFormatter formatter(sstream);
    auto rv = document.Write(formatter);
    if (!rv) return rv;
    return Write(socket, sstream.str());
}

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ReceiveDocument(util::TcpSocket& socket)
{
    auto s = ReadStr(socket);
    if (!s) return std::unexpected<int>(s.error());
    std::string str = *s;
    if (str.empty()) return std::unique_ptr<Document>();
    auto u = util::ToUtf32(str);
    if (!u)  return std::unexpected<int>(u.error());
    std::u32string content = *u;
    auto d = ParseXmlContent(content, "socket");
    if (!d) return std::unexpected<int>(d.error());
    std::unique_ptr<soul_expected::xml::Document> doc = std::move(*d);
    return doc;
}

} // namespace soul_expected::xml
