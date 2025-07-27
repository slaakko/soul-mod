// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.dom.document.parser;

import std;
import soul_expected.xml.document;
import soul_expected.lexer.file.map;
import util_expected;

export namespace soul_expected::xml {

enum class ParsingFlags : int
{
    none = 0, generateWarnings = 1 << 0
};

constexpr ParsingFlags operator|(ParsingFlags left, ParsingFlags right)
{
    return ParsingFlags(int(left) | int(right));
}

constexpr ParsingFlags operator&(ParsingFlags left, ParsingFlags right)
{
    return ParsingFlags(int(left) & int(right));
}

constexpr ParsingFlags operator~(ParsingFlags flags)
{
    return ParsingFlags(~int(flags));
}

//  =======================================================================================================
//  ParseXmlFile parses given UTF-8 encoded XML file to a DOM document.
//  The FileMap can be used to generate error messages containing source locations after successul parsing. 
//  (see soul_expected::lexer::MakeMessage)
//  =======================================================================================================

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlFile(const std::string& xmlFileName);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlFile(const std::string& xmlFileName, ParsingFlags parsingFlags);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlFile(const std::string& xmlFileName, soul_expected::lexer::FileMap& fileMap);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlFile(const std::string& xmlFileName, soul_expected::lexer::FileMap& fileMap, ParsingFlags parsingFlags);

//  =======================================================================================================
//  ParseXmlContent parses given UTF-8 or UTF-32 encoded XML string to a DOM document.
//  The systemId parameter is used for error messages only. 
//  It can be for example a file name or URL that identifies the XML string to parse.
//  The FileMap can be used to generate error messages containing source locations after successul parsing. 
//  (see soul_expected::lexer::MakeMessage)
//  =======================================================================================================

std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId, ParsingFlags parsingFlags);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId, soul_expected::lexer::FileMap& fileMap);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId, soul_expected::lexer::FileMap& fileMap, ParsingFlags parsingFlags);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::u32string& xmlContent, const std::string& systemId);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(const std::u32string& xmlContent, const std::string& systemId, ParsingFlags parsingFlags);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(std::u32string&& xmlContent, const std::string& systemId, soul_expected::lexer::FileMap& fileMap);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ParseXmlContent(std::u32string&& xmlContent, const std::string& systemId, soul_expected::lexer::FileMap& fileMap, ParsingFlags parsingFlags);

std::expected<bool, int> SendDocument(util::TcpSocket& socket, soul_expected::xml::Document& document);
std::expected<std::unique_ptr<soul_expected::xml::Document>, int> ReceiveDocument(util::TcpSocket& socket);

} // namespace soul_expected::xml
