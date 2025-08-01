// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.processor.attribute;

import std;
import soul_expected.ast.source.pos;

export namespace soul_expected::xml::processor {

class Attribute
{
public:
    Attribute(const soul_expected::ast::SourcePos& sourcePos_, const std::string& namespaceUri_, const std::string& localName_, const std::string& qualifiedName_, const std::string& value_);
    inline const soul_expected::ast::SourcePos& GetSourcePos() const { return sourcePos; }
    inline const std::string& NamespaceUri() const { return namespaceUri; }
    inline const std::string& LocalName() const { return localName; }
    inline const std::string& QualifiedName() const { return qualifiedName; }
    inline const std::string& Value() const { return value; }
    std::string ToString() const;
private:
    soul_expected::ast::SourcePos sourcePos;
    std::string namespaceUri;
    std::string localName;
    std::string qualifiedName;
    std::string value;
};

class Attributes
{
public:
    Attributes();
    void Clear();
    void AddAttribute(Attribute* attribute);
    inline const std::vector<std::unique_ptr<Attribute>>& GetAttributes() const { return attributes; }
    const std::string* GetAttributeValue(const std::string& qualifiedName) const;
    std::string ToString() const;
private:
    std::vector<std::unique_ptr<Attribute>> attributes;
};

} // namespace soul_expected::xml::processor
