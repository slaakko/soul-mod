// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.document.handler;

import std;
import soul.xml.document;
import soul.xml.element;
import soul.xml.parent.node;
import soul.xml.content.handler;
import soul.xml.dom.document.parser;

export namespace soul::xml {

class DocumentHandlerData;

class DocumentHandler : public soul::xml::XmlContentHandler
{
public:
    DocumentHandler(soul::xml::ParsingFlags flags_);
    std::unique_ptr<soul::xml::Document> GetDocument() { return std::move(document); };
    std::expected<bool, int> StartDocument(const soul::ast::SourcePos& sourcePos) override;
    std::expected<bool, int> XmlVersion(const std::string& xmlVersion) override;
    std::expected<bool, int> XmlEncoding(const std::string& xmlEncoding) override;
    std::expected<bool, int> Standalone(bool standalone) override;
    std::expected<bool, int> Comment(const soul::ast::SourcePos& sourcePos, const std::string& comment) override;
    std::expected<bool, int> PI(const soul::ast::SourcePos& sourcePos, const std::string& target, const std::string& data) override;
    std::expected<bool, int> Text(const soul::ast::SourcePos& sourcePos, const std::string& text) override;
    std::expected<bool, int> CDataSection(const soul::ast::SourcePos& sourcePos, const std::string& cdata) override;
    std::expected<bool, int> StartElement(const soul::ast::SourcePos& sourcePos, const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName,
        const soul::xml::processor::Attributes& attributes) override;
    std::expected<bool, int> EndElement(const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName) override;
    std::expected<bool, int> SkippedEntity(const soul::ast::SourcePos& sourcePos, const std::string& entityName) override;
private:
    std::expected<bool, int> AddTextContent();
    std::expected<bool, int> AddTextContent(bool addSpace);
    soul::xml::ParsingFlags flags;
    std::unique_ptr<soul::xml::Document> document;
    soul::xml::ParentNode* currentParentNode;
    std::stack<soul::xml::ParentNode*> parentNodeStack;
    std::unique_ptr<soul::xml::Element> currentElement;
    std::stack<std::unique_ptr<soul::xml::Element>> elementStack;
    soul::ast::SourcePos textSourcePos;
    std::string textContent;
};

} // namespace soul::xml
