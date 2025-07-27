// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.content.handler;

namespace soul_expected::xml {

XmlContentHandler::XmlContentHandler() : lexer(nullptr)
{
}

XmlContentHandler::~XmlContentHandler()
{
}

std::expected<bool, int> XmlContentHandler::StartDocument(const soul_expected::ast::SourcePos& sourcePos)
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlContentHandler::EndDocument()
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlContentHandler::XmlVersion(const std::string& xmlVersion)
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlContentHandler::XmlEncoding(const std::string& xmlEncoding)
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlContentHandler::Standalone(bool standalone)
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlContentHandler::Comment(const soul_expected::ast::SourcePos& sourcePos, const std::string& comment)
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlContentHandler::PI(const soul_expected::ast::SourcePos& sourcePos, const std::string& target, const std::string& data)
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlContentHandler::Text(const soul_expected::ast::SourcePos& sourcePos, const std::string& text)
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlContentHandler::CDataSection(const soul_expected::ast::SourcePos& sourcePos, const std::string& cdata)
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlContentHandler::StartElement(const soul_expected::ast::SourcePos& sourcePos, const std::string& namespaceUri, const std::string& localName,
    const std::string& qualifiedName, const soul_expected::xml::processor::Attributes& attributes)
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlContentHandler::EndElement(const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName)
{
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlContentHandler::SkippedEntity(const soul_expected::ast::SourcePos& sourcePos, const std::string& entityName)
{
    return std::expected<bool, int>(true);
}

} // namespace soul_expected::xml {
