// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.xpath.object;

import std;
import soul.xml.node;
import soul.xml.element;

export namespace soul::xml::xpath {

enum class ObjectKind
{
    nodeSet, boolean, number, string
};

std::string ObjectKindStr(ObjectKind kind);

class Object
{
public:
    Object(ObjectKind kind_);
    virtual ~Object();
    inline ObjectKind Kind() const { return kind; }
    inline bool IsNodeSet() const { return kind == ObjectKind::nodeSet; }
    inline bool IsBoolean() const { return kind == ObjectKind::boolean; }
    inline bool IsNumber() const { return kind == ObjectKind::number; }
    inline bool IsString() const { return kind == ObjectKind::string; }
    virtual std::expected<soul::xml::Element*, int> ToXmlElement() const = 0;
private:
    ObjectKind kind;
};

class NodeSet : public Object
{
public:
    NodeSet();
    inline const std::vector<soul::xml::Node*>& Nodes() const { return nodes; }
    inline int Count() const { return static_cast<int>(nodes.size()); }
    void Add(soul::xml::Node* node);
    std::expected<Node*, int> GetNode(int index) const;
    std::expected<soul::xml::Element*, int> ToXmlElement() const override;
private:
    std::vector<soul::xml::Node*> nodes;
};

class Boolean : public Object
{
public:
    Boolean();
    Boolean(bool value_);
    inline bool Value() const { return value; }
    std::expected<soul::xml::Element*, int> ToXmlElement() const override;
private:
    bool value;
};

class Number : public Object
{
public:
    Number();
    Number(double value_);
    inline double Value() const { return value; }
    std::expected<soul::xml::Element*, int> ToXmlElement() const override;
private:
    double value;
};

class String : public Object
{
public:
    String();
    String(const std::string& value_);
    inline const std::string& Value() const { return value; }
    std::expected<soul::xml::Element*, int> ToXmlElement() const override;
private:
    std::string value;
};

} // namespace soul::xml::xpath
