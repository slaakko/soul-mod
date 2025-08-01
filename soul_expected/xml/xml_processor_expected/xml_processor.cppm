// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.xml_processor;

import std;
import soul_expected.xml.content.handler;
import soul_expected.xml.processor.attribute;
import soul_expected.ast.source.pos;
import soul_expected.lexer.base;

export namespace soul_expected::xml::processor {

struct Tag
{
    Tag() : sourcePos(), name() {}
    Tag(const soul_expected::ast::SourcePos& sourcePos_, const std::string& name_) : sourcePos(sourcePos_), name(name_) {}
    soul_expected::ast::SourcePos sourcePos;
    std::string name;
};

class XmlProcessor
{
public:
    XmlProcessor(soul_expected::xml::XmlContentHandler* contentHandler_);
    virtual ~XmlProcessor();
    virtual std::expected<bool, int> StartDocument(soul_expected::lexer::LexerBase<char32_t>* lexer_, const soul_expected::ast::SourcePos& sourcePos);
    virtual std::expected<bool, int> EndDocument();
    virtual std::expected<bool, int> XmlVersion(const std::string& xmlVersion);
    virtual std::expected<bool, int> XmlEncoding(const std::string& xmlEncoding);
    virtual std::expected<bool, int> Standalone(bool standalone);
    virtual std::expected<bool, int> Comment(const soul_expected::ast::SourcePos& sourcePos, const std::string& comment);
    virtual std::expected<bool, int> PI(const soul_expected::ast::SourcePos& sourcePos, const std::string& target, const std::string& data);
    virtual std::expected<bool, int> BeginStartTag(const soul_expected::ast::SourcePos& sourcePos, const std::string& tagName);
    virtual std::expected<bool, int> EndStartTag();
    virtual std::expected<bool, int> EndTag(const soul_expected::ast::SourcePos& sourcePos, const std::string& tagName);
    virtual std::expected<bool, int> AddAttribute(const soul_expected::ast::SourcePos& sourcePos, const std::string& attName, const std::string& attValue);
    virtual std::expected<bool, int> BeginAttributeValue();
    virtual std::expected<bool, int> EndAttributeValue();
    virtual std::expected<bool, int> AddAttValueChar(char32_t chr);
    virtual std::expected<std::string, int> AttValue() const;
    virtual std::expected<bool, int> CharRef(const soul_expected::ast::SourcePos& sourcePos, char32_t chr);
    virtual std::expected<bool, int> EntityRef(const soul_expected::ast::SourcePos& sourcePos, const std::string& entityName);
    virtual std::expected<bool, int> Text(const soul_expected::ast::SourcePos& sourcePos, const std::string& text);
    virtual std::expected<bool, int> CDataSection(const soul_expected::ast::SourcePos& sourcePos, const std::string& cdata);
    inline bool Valid() const { return error == 0; }
    inline int Error() const { return error; }
    inline explicit operator bool() const { return Valid(); }
private:
    std::expected<bool, int> ParseQualifiedName(const soul_expected::ast::SourcePos& sourcePos, const std::string& qualifiedName, std::string& localName, std::string& prefix) const;
    std::expected<std::string, int> GetNamespaceUri(const std::string& namespacePrefix, const soul_expected::ast::SourcePos& sourcePos) const;
    soul_expected::lexer::LexerBase<char32_t>* lexer;
    soul_expected::xml::XmlContentHandler* contentHandler;
    std::stack<Tag> tagStack;
    Tag currentTag;
    soul_expected::xml::processor::Attributes attributes;
    std::u32string attValue;
    std::stack<std::u32string> attValueStack;
    std::string currentNamespaceUri;
    std::stack<std::string> namespaceUriStack;
    std::string currentNamespacePrefix;
    std::stack<std::string> namespacePrefixStack;
    std::map<std::string, std::string> namespacePrefixMap;
    int error;
};

} // namespace soul_expected::xml::processor
