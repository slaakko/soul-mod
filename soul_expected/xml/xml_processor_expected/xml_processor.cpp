// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.xml_processor;

import soul_expected.xml.processor.entity;
import util_expected;

namespace soul_expected::xml::processor {

XmlProcessor::XmlProcessor(soul_expected::xml::XmlContentHandler* contentHandler_) : lexer(nullptr), contentHandler(contentHandler_), error(0)
{
    if (!contentHandler)
    {
        error = util::AllocateError("error: XmlProcessor: content handler is null");
        return;
    }
}

XmlProcessor::~XmlProcessor()
{
}

std::expected<bool, int> XmlProcessor::StartDocument(soul_expected::lexer::LexerBase<char32_t>* lexer_, const soul_expected::ast::SourcePos& sourcePos)
{
    if (!Valid()) return std::unexpected<int>(Error());
    lexer = lexer_;
    contentHandler->SetLexer(lexer);
    return contentHandler->StartDocument(sourcePos);
}

std::expected<bool, int> XmlProcessor::EndDocument()
{
    if (!Valid()) return std::unexpected<int>(Error());
    return contentHandler->EndDocument();
}

std::expected<bool, int> XmlProcessor::XmlVersion(const std::string& xmlVersion)
{
    if (!Valid()) return std::unexpected<int>(Error());
    return contentHandler->XmlVersion(xmlVersion);
}

std::expected<bool, int> XmlProcessor::XmlEncoding(const std::string& xmlEncoding)
{
    if (!Valid()) return std::unexpected<int>(Error());
    return contentHandler->XmlEncoding(xmlEncoding);
}

std::expected<bool, int> XmlProcessor::Standalone(bool standalone)
{
    if (!Valid()) return std::unexpected<int>(Error());
    return contentHandler->Standalone(standalone);
}

std::expected<bool, int>  XmlProcessor::Comment(const soul_expected::ast::SourcePos& sourcePos, const std::string& comment)
{
    if (!Valid()) return std::unexpected<int>(Error());
    return contentHandler->Comment(sourcePos, comment);
}

std::expected<bool, int>  XmlProcessor::PI(const soul_expected::ast::SourcePos& sourcePos, const std::string& target, const std::string& data)
{
    if (!Valid()) return std::unexpected<int>(Error());
    return contentHandler->PI(sourcePos, target, data);
}

std::expected<bool, int> XmlProcessor::BeginStartTag(const soul_expected::ast::SourcePos& sourcePos, const std::string& tagName)
{
    if (!Valid()) return std::unexpected<int>(Error());
    tagStack.push(currentTag);
    currentTag = Tag(sourcePos, tagName);
    attributes.Clear();
    namespaceUriStack.push(currentNamespaceUri);
    namespacePrefixStack.push(currentNamespacePrefix);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlProcessor::EndStartTag()
{
    if (!Valid()) return std::unexpected<int>(Error());
    std::string localName;
    std::string prefix;
    auto q = ParseQualifiedName(currentTag.sourcePos, currentTag.name, localName, prefix);
    if (!q) return q;
    if (prefix == "xmlns")
    {
        auto rv = lexer->ErrorLines(currentTag.sourcePos.pos);
        if (!rv) return std::unexpected<int>(rv.error());
        int err = util::AllocateError("error: 'xmlns' prefix cannot be declared for an element in file " +
                lexer->FileName() + " line " + std::to_string(currentTag.sourcePos.line) + ":\n" + *rv);
        return std::unexpected<int>(err);
    }
    std::expected<std::string, int> u = GetNamespaceUri(prefix, currentTag.sourcePos);
    if (!u) return std::unexpected<int>(u.error());
    std::string namespaceUri = *u;
    return contentHandler->StartElement(currentTag.sourcePos, namespaceUri, localName, currentTag.name, attributes);
}

std::expected<bool, int> XmlProcessor::EndTag(const soul_expected::ast::SourcePos& sourcePos, const std::string& tagName)
{
    if (!Valid()) return std::unexpected<int>(Error());
    if (tagStack.empty())
    {
        auto rv = lexer->ErrorLines(currentTag.sourcePos.pos);
        if (!rv) return std::unexpected<int>(rv.error());
        return std::unexpected<int>(util::AllocateError("error: end tag '" + tagName + "' has no corresponding start tag in file " +
            lexer->FileName() + " line " + std::to_string(sourcePos.line) + ":\n" + *rv));
    }
    if (tagName != currentTag.name)
    {
        auto rv = lexer->ErrorLines(currentTag.sourcePos.pos);
        if (!rv) return std::unexpected<int>(rv.error());
        auto rv2 = lexer->ErrorLines(sourcePos.pos);
        if (!rv2) return std::unexpected<int>(rv2.error());
        return std::unexpected<int>(util::AllocateError("error: end tag '" + tagName + "' does not match start tag '" + currentTag.name + "' in file " +
            lexer->FileName() + " line " + std::to_string(sourcePos.line) + ":\n" + *rv +
            "\nsee reference line " + std::to_string(currentTag.sourcePos.line) + ":\n" + *rv2));
    }
    std::string localName;
    std::string prefix;
    std::expected<bool, int> q = ParseQualifiedName(sourcePos, currentTag.name, localName, prefix);
    if (!q) return q;
    if (prefix == "xmlns")
    {
        auto rv = lexer->ErrorLines(sourcePos.pos);
        if (!rv) return std::unexpected<int>(rv.error());
        return std::unexpected<int>(util::AllocateError("error: 'xmlns' prefix cannot be declared for an element in file " +
            lexer->FileName() + " line " + std::to_string(sourcePos.line) + ":\n" + *rv));
    }
    std::expected<std::string, int> u = GetNamespaceUri(prefix, sourcePos);
    if (!u) return std::unexpected<int>(u.error());
    std::string namespaceUri = *u;
    auto rv = contentHandler->EndElement(namespaceUri, localName, currentTag.name);
    if (!rv) return rv;
    if (namespaceUriStack.empty())
    {
        return std::unexpected<int>(util::AllocateError("namespace URI stack is empty"));
    }
    currentNamespaceUri = namespaceUriStack.top();
    namespaceUriStack.pop();
    namespacePrefixMap.erase(currentNamespacePrefix);
    if (namespacePrefixStack.empty())
    {
        return std::unexpected<int>(util::AllocateError("namespace prefix stack is empty"));
    }
    currentNamespacePrefix = namespacePrefixStack.top();
    namespacePrefixStack.pop();
    namespacePrefixMap[currentNamespacePrefix] = currentNamespaceUri;
    currentTag = tagStack.top();
    tagStack.pop();
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlProcessor::AddAttribute(const soul_expected::ast::SourcePos& sourcePos, const std::string& attName, const std::string& attValue)
{
    if (!Valid()) return std::unexpected<int>(Error());
    std::string localName;
    std::string prefix;
    auto q = ParseQualifiedName(sourcePos, attName, localName, prefix);
    if (!q) return q;
    if (prefix == "xmlns")
    {
        currentNamespacePrefix = localName;
        currentNamespaceUri = attValue;
        namespacePrefixMap[currentNamespacePrefix] = currentNamespaceUri;
    }
    else if (localName == "xmlns")
    {
        currentNamespacePrefix.clear();
        currentNamespaceUri = attValue;
    }
    auto u = GetNamespaceUri(prefix, sourcePos);
    if (!u) return std::unexpected<int>(u.error());
    std::string namespaceUri = *u;
    attributes.AddAttribute(new Attribute(sourcePos, namespaceUri, localName, attName, attValue));
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlProcessor::BeginAttributeValue()
{
    if (!Valid()) return std::unexpected<int>(Error());
    attValueStack.push(attValue);
    attValue.clear();
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlProcessor::EndAttributeValue()
{
    if (!Valid()) return std::unexpected<int>(Error());
    if (attValueStack.empty())
    {
        return std::unexpected<int>(util::AllocateError("attribute value stack is empty"));
    }
    attValue = attValueStack.top();
    attValueStack.pop();
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlProcessor::AddAttValueChar(char32_t chr)
{
    if (!Valid()) return std::unexpected<int>(Error());
    attValue.append(1, chr);
    return std::expected<bool, int>(true);
}

std::expected<std::string, int> XmlProcessor::AttValue() const
{
    if (!Valid()) return std::unexpected<int>(Error());
    return util::ToUtf8(attValue);
}

std::expected<bool, int> XmlProcessor::CharRef(const soul_expected::ast::SourcePos& sourcePos, char32_t chr)
{
    if (!Valid()) return std::unexpected<int>(Error());
    if (attValueStack.empty())
    {
        auto u = util::ToUtf8(std::u32string(1, chr));
        if (!u) return std::unexpected<int>(u.error());
        auto rv = Text(sourcePos, *u);
        if (!rv) return rv;
    }
    else
    {
        auto rv = AddAttValueChar(chr);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlProcessor::EntityRef(const soul_expected::ast::SourcePos& sourcePos, const std::string& entityName)
{
    if (!Valid()) return std::unexpected<int>(Error());
    Entities& entities = Entities::Instance();
    Entity* entity = entities.GetEntity(entityName);
    if (entity)
    {
        if (entity->IsInternal())
        {
            if (attValueStack.empty())
            {
                auto u = util::ToUtf8(entity->Value());
                if (!u) return std::unexpected<int>(u.error());
                auto rv = Text(sourcePos, *u);
                if (!rv) return rv;
            }
            else
            {
                attValue.append(entity->Value());
            }
        }
        else
        {
            auto rv = contentHandler->SkippedEntity(sourcePos, entityName);
            if (!rv) return rv;
        }
    }
    else
    {
        auto rv =contentHandler->SkippedEntity(sourcePos, entityName);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlProcessor::Text(const soul_expected::ast::SourcePos& sourcePos, const std::string& text)
{
    if (!Valid()) return std::unexpected<int>(Error());
    return contentHandler->Text(sourcePos, text);
}

std::expected<bool, int> XmlProcessor::CDataSection(const soul_expected::ast::SourcePos& sourcePos, const std::string& cdata)
{
    if (!Valid()) return std::unexpected<int>(Error());
    return contentHandler->CDataSection(sourcePos, cdata);
}

std::expected<bool, int> XmlProcessor::ParseQualifiedName(const soul_expected::ast::SourcePos& sourcePos, const std::string& qualifiedName, std::string& localName, std::string& prefix) const
{
    if (!Valid()) return std::unexpected<int>(Error());
    std::vector<std::string> components = util::Split(qualifiedName, ':');
    if (components.size() > 2)
    {
        auto u = lexer->ErrorLines(sourcePos.pos);
        if (!u) return std::unexpected<int>(u.error());
        return std::unexpected<int>(util::AllocateError("error: qualified name '" + qualifiedName + "' has more than one ':' character in file " +
            lexer->FileName() + " line " + std::to_string(sourcePos.line) + ":\n" + *u));
    }
    else if (components.size() == 2)
    {
        prefix = components[0];
        localName = components[1];
    }
    else
    {
        prefix.clear();
        localName = qualifiedName;
    }
    return std::expected<bool, int>(true);
}

std::expected<std::string, int> XmlProcessor::GetNamespaceUri(const std::string& namespacePrefix, const soul_expected::ast::SourcePos& sourcePos) const
{
    if (!Valid()) return std::unexpected<int>(Error());
    if (namespacePrefix.empty())
    {
        return currentNamespaceUri;
    }
    auto it = namespacePrefixMap.find(namespacePrefix);
    if (it != namespacePrefixMap.cend())
    {
        return it->second;
    }
    else
    {
        if (namespacePrefix != "xml")
        {
            auto u = lexer->ErrorLines(sourcePos.pos);
            if (!u) return std::unexpected<int>(u.error());
            return std::unexpected<int>(util::AllocateError("error: namespace prefix '" + namespacePrefix + "' not bound to any namespace URI in file " +
                lexer->FileName() + " line " + std::to_string(sourcePos.line) + ":\n" + *u));
        }
    }
    return std::expected<std::string, int>(std::string());
}

} // namespace soul_expected::xml::processor
