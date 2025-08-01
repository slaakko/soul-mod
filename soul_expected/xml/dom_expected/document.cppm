// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.document;

import std;
import soul_expected.xml.parent.node;
import soul_expected.xml.element;

export namespace soul_expected::xml {

class Document : public ParentNode
{
public:
    Document();
    Document(const soul_expected::ast::SourcePos& sourcePos_);
    inline Element* DocumentElement() const { return documentElement; }
    inline bool XmlStandalone() const { return xmlStandalone; }
    inline void SetXmlStandalone(bool xmlStandalone_) { xmlStandalone = xmlStandalone_; }
    inline const std::string& XmlVersion() const { return xmlVersion; }
    inline void SetXmlVersion(const std::string& xmlVersion_) { xmlVersion = xmlVersion_; }
    inline const std::string& XmlEncoding() const { return xmlEncoding; }
    inline void SetXmlEncoding(const std::string& xmlEncoding_) { xmlEncoding = xmlEncoding_; }
    inline std::map<std::string, Element*>& Index() { return index; }
    Element* GetElementById(const std::string& elementId);
    std::expected<bool, int> AppendChild(Node* child) override;
    std::expected<bool, int> InsertBefore(Node* newChild, Node* refChild) override;
    std::expected<std::unique_ptr<Node>, int> RemoveChild(Node* child) override;
    std::expected<std::unique_ptr<Node>, int> ReplaceChild(Node* newChild, Node* oldChild) override;
    void Accept(Visitor& visitor) override;
    std::expected<bool, int> Write(util::CodeFormatter& formatter) override;
private:
    friend class ParentNode;
    void InvalidateIndex();
    std::expected<bool, int> CheckValidInsert(Node* node);
    Element* documentElement;
    bool indexValid;
    bool xmlStandalone;
    std::string xmlVersion;
    std::string xmlEncoding;
    std::map<std::string, Element*> index;
};

std::unique_ptr<Document> MakeDocument();

} // namespace soul_expected::xml
