// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.content.handler;

import std;
import soul.ast.source.pos;
import soul.xml.processor.attribute;
import soul.lexer.base;

export namespace soul::xml {

class XmlContentHandler
{
public:
    XmlContentHandler();
    inline soul::lexer::LexerBase<char32_t>* GetLexer() { return lxr; }
    inline void SetLexer(soul::lexer::LexerBase<char32_t>* lexer_) { lxr = lexer_; }
    virtual ~XmlContentHandler();
    virtual std::expected<bool, int> StartDocument(const soul::ast::SourcePos& sourcePos);
    virtual std::expected<bool, int> EndDocument();
    virtual std::expected<bool, int> XmlVersion(const std::string& xmlVersion);
    virtual std::expected<bool, int> XmlEncoding(const std::string& xmlEncoding);
    virtual std::expected<bool, int> Standalone(bool standalone);
    virtual std::expected<bool, int> Comment(const soul::ast::SourcePos& sourcePos, const std::string& comment);
    virtual std::expected<bool, int> PI(const soul::ast::SourcePos& sourcePos, const std::string& target, const std::string& data);
    virtual std::expected<bool, int> Text(const soul::ast::SourcePos& sourcePos, const std::string& text);
    virtual std::expected<bool, int> CDataSection(const soul::ast::SourcePos& sourcePos, const std::string& cdata);
    virtual std::expected<bool, int> StartElement(const soul::ast::SourcePos& sourcePos, const std::string& namespaceUri, const std::string& localName,
        const std::string& qualifiedName, const soul::xml::processor::Attributes& attributes);
    virtual std::expected<bool, int> EndElement(const std::string& namespaceUri, const std::string& localName, const std::string& qualifiedName);
    virtual std::expected<bool, int> SkippedEntity(const soul::ast::SourcePos& sourcePos, const std::string& entityName);
private:
    soul::lexer::LexerBase<char32_t>* lxr;
};

} // namespace soul::xml
