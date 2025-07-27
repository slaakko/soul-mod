// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.document.handler;

import std;
import soul_expected.xml.document;
import soul_expected.xml.element;
import soul_expected.xml.parent.node;
import soul_expected.xml.content.handler;
import soul_expected.xml.dom.document.parser;

export namespace soul_expected::xml {

class DocumentHandlerData;

class DocumentHandler : public soul_expected::xml::XmlContentHandler
{
public:
    DocumentHandler(soul_expected::xml::ParsingFlags flags_);
    std::unique_ptr<soul_expected::xml::Document> GetDocument() { return std::move(document); };
    std::expected<bool, int> StartDocument(const soul_expected::ast::SourcePos& sourcePos) override;
    std::expected<bool, int> XmlVersion(const std::string& xmlVersion) override;
    std::expected<bool, int> XmlEncoding(const std::string& xmlEncoding) override;
    std::expected<bool, int> Standalone(bool standalone) override;
    std::expected<bool, int> Comment(const soul_expected::ast::SourcePos& sourcePos, const std::string& comment) override;
    std::expected<bool, int> PI(const soul_expected::ast::SourcePos& sourcePos, const std::string& target, const std::string& data) override;
    std::expected<bool, int> Text(const soul_expected::ast::SourcePos& sourcePos, const std::string& text) override;
    std::expected<bool, int> CDataSection(const soul_expected::ast::SourcePos& sourcePos, const std::string& cdata) override;
    std::expected<bool, int> StartElement(const soul_expected::ast::SourcePos& sourcePos, const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName,
        const soul_expected::xml::processor::Attributes& attributes) override;
    std::expected<bool, int> EndElement(const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName) override;
    std::expected<bool, int> SkippedEntity(const soul_expected::ast::SourcePos& sourcePos, const std::string& entityName) override;
private:
    std::expected<bool, int> AddTextContent();
    std::expected<bool, int> AddTextContent(bool addSpace);
    soul_expected::xml::ParsingFlags flags;
    std::unique_ptr<soul_expected::xml::Document> document;
    soul_expected::xml::ParentNode* currentParentNode;
    std::stack<soul_expected::xml::ParentNode*> parentNodeStack;
    std::unique_ptr<soul_expected::xml::Element> currentElement;
    std::stack<std::unique_ptr<soul_expected::xml::Element>> elementStack;
    soul_expected::ast::SourcePos textSourcePos;
    std::string textContent;
};

} // namespace soul_expected::xml
