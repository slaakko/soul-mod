// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.parser.intf;

import std;
import soul.xml.content.handler;
import soul.lexer.file.map;

export namespace soul::xml::parser {

//  =============================================================================
//  ParseXmlFile parses given UTF-8 encoded XML file using given content handler.
//  =============================================================================

std::expected<bool, int> ParseXmlFile(const std::string& xmlFileName, XmlContentHandler* contentHandler);

//  =======================================================================================================
//  The FileMap can be used to generate error messages containing source locations after successul parsing. 
//  (see soul::lexer::MakeMessage)
//  =======================================================================================================

std::expected<bool, int> ParseXmlFile(const std::string& xmlFileName, XmlContentHandler* contentHandler, soul::lexer::FileMap& fileMap);

//  ============================================================================================
//  ParseXmlContent parses given UTF-8 or UTF-32 encoded XML string using given content handler.
//  The systemId parameter is used for error messages only. 
//  It can be for example a file name or URL that identifies the XML string to parse.
//  ============================================================================================

std::expected<bool, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId, XmlContentHandler* contentHandler);

//  =======================================================================================================
//  The FileMap can be used to generate error messages containing source locations after successul parsing. 
//  (see soul::lexer::MakeMessage)
//  =======================================================================================================

std::expected<bool, int> ParseXmlContent(const std::string& xmlContent, const std::string& systemId, XmlContentHandler* contentHandler, soul::lexer::FileMap& fileMap);

std::expected<bool, int> ParseXmlContent(const std::u32string& xmlContent, const std::string& systemId, XmlContentHandler* contentHandler);

std::expected<bool, int> ParseXmlContent(std::u32string&& xmlContent, const std::string& systemId, XmlContentHandler* contentHandler, soul::lexer::FileMap& fileMap);

} // namespace soul::xml::parser
