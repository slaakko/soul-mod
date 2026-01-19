// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.xml.document.handler;

import soul.xml.dom;
import util;

namespace soul::xml {

DocumentHandler::DocumentHandler(soul::xml::ParsingFlags flags_) : currentParentNode(nullptr), flags(flags_)
{
}

std::expected<bool, int> DocumentHandler::StartDocument(const soul::ast::SourcePos& sourcePos)
{
    document.reset(new soul::xml::Document(sourcePos));
    currentParentNode = document.get();
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DocumentHandler::XmlVersion(const std::string& xmlVersion)
{
    document->SetXmlVersion(xmlVersion);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DocumentHandler::XmlEncoding(const std::string& xmlEncoding)
{
    document->SetXmlEncoding(xmlEncoding);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DocumentHandler::Standalone(bool standalone)
{
    document->SetXmlStandalone(standalone);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DocumentHandler::Comment(const soul::ast::SourcePos& sourcePos, const std::string& comment)
{
    auto rv = AddTextContent();
    if (!rv) return rv;
    return currentParentNode->AppendChild(new soul::xml::Comment(sourcePos, comment));
}

std::expected<bool, int> DocumentHandler::PI(const soul::ast::SourcePos& sourcePos, const std::string& target, const std::string& data)
{
    auto rv = AddTextContent();
    if (!rv) return rv;
    rv = currentParentNode->AppendChild(new soul::xml::ProcessingInstruction(sourcePos, target, data));
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DocumentHandler::Text(const soul::ast::SourcePos& sourcePos, const std::string& text)
{
    if (!textSourcePos.IsValid())
    {
        textSourcePos = sourcePos;
    }
    textContent.append(text);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DocumentHandler::CDataSection(const soul::ast::SourcePos& sourcePos, const std::string& cdata)
{
    auto rv = AddTextContent();
    if (!rv) return rv;
    rv = currentParentNode->AppendChild(new soul::xml::CDataSection(sourcePos, cdata));
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DocumentHandler::StartElement(const soul::ast::SourcePos& sourcePos, const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName,
    const soul::xml::processor::Attributes& attributes)
{
    auto rv = AddTextContent(true);
    if (!rv) return rv;
    parentNodeStack.push(currentParentNode);
    elementStack.push(std::move(currentElement));
    currentElement.reset(new soul::xml::Element(sourcePos, qualifiedName));
    currentParentNode = currentElement.get();
    for (const auto& attribute : attributes.GetAttributes())
    {
        currentElement->SetAttribute(sourcePos, attribute->QualifiedName(), attribute->Value());
    }
    currentElement->SetOwnerDocument(document.get());
    if (!namespaceUri.empty())
    {
        currentElement->SetNamespaceUri(namespaceUri);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DocumentHandler::EndElement(const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName)
{
    auto rv = AddTextContent();
    if (!rv) return rv;
    currentParentNode = parentNodeStack.top();
    parentNodeStack.pop();
    rv = currentParentNode->AppendChild(currentElement.release());
    if (!rv) return rv;
    currentElement = std::move(elementStack.top());
    elementStack.pop();
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DocumentHandler::SkippedEntity(const soul::ast::SourcePos& sourcePos, const std::string& entityName)
{
    if ((flags & ParsingFlags::generateWarnings) != ParsingFlags::none)
    {
        auto lexer = GetLexer();
        auto e = lexer->ErrorLines(sourcePos.pos);
        if (!e) return std::unexpected<int>(e.error());
        std::cout << "warning: skipped entity '" << entityName << "' in file " <<
            lexer->FileName() << " line " << std::to_string(sourcePos.line) << ":\n" << *e << std::endl;
    }
    auto rv = AddTextContent();
    if (!rv) return rv;
    rv = currentParentNode->AppendChild(MakeEntityReference(entityName));
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DocumentHandler::AddTextContent()
{
    return AddTextContent(false);
}

std::expected<bool, int> DocumentHandler::AddTextContent(bool addSpace)
{
    if (currentElement)
    {
        auto u = util::ToUtf32(textContent);
        if (!u) return std::unexpected<int>(u.error());
        auto t = util::TrimAll(*u);
        if (!t) return std::unexpected<int>(t.error());
        auto u2 = util::ToUtf8(*t);
        if (!u2) return std::unexpected<int>(u2.error());
        textContent = *u2;
        if (!textContent.empty())
        {
            if (addSpace)
            {
                textContent.append(1, ' ');
            }
            auto rv = currentElement->AppendChild(new soul::xml::Text(textSourcePos, textContent));
            if (!rv) return rv;
            textSourcePos = soul::ast::SourcePos();
        }
    }
    textContent.clear();
    return std::expected<bool, int>(true);
}

} // namespace soul::xml
