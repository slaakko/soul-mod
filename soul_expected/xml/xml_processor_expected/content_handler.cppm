// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.content.handler;

import std;
import soul_expected.ast.source.pos;
import soul_expected.xml.processor.attribute;
import soul_expected.lexer.base;

export namespace soul_expected::xml {

class XmlContentHandler
{
public:
    XmlContentHandler();
    soul_expected::lexer::LexerBase<char32_t>* GetLexer() { return lexer; }
    void SetLexer(soul_expected::lexer::LexerBase<char32_t>* lexer_) { lexer = lexer_; }
    virtual ~XmlContentHandler();
    virtual std::expected<bool, int> StartDocument(const soul_expected::ast::SourcePos& sourcePos);
    virtual std::expected<bool, int> EndDocument();
    virtual std::expected<bool, int> XmlVersion(const std::string& xmlVersion);
    virtual std::expected<bool, int> XmlEncoding(const std::string& xmlEncoding);
    virtual std::expected<bool, int> Standalone(bool standalone);
    virtual std::expected<bool, int> Comment(const soul_expected::ast::SourcePos& sourcePos, const std::string& comment);
    virtual std::expected<bool, int> PI(const soul_expected::ast::SourcePos& sourcePos, const std::string& target, const std::string& data);
    virtual std::expected<bool, int> Text(const soul_expected::ast::SourcePos& sourcePos, const std::string& text);
    virtual std::expected<bool, int> CDataSection(const soul_expected::ast::SourcePos& sourcePos, const std::string& cdata);
    virtual std::expected<bool, int> StartElement(const soul_expected::ast::SourcePos& sourcePos, const std::string& namespaceUri, const std::string& localName,
        const std::string& qualifiedName, const soul_expected::xml::processor::Attributes& attributes);
    virtual std::expected<bool, int> EndElement(const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName);
    virtual std::expected<bool, int> SkippedEntity(const soul_expected::ast::SourcePos& sourcePos, const std::string& entityName);
private:
    soul_expected::lexer::LexerBase<char32_t>* lexer;
};

} // namespace soul_expected::xml
