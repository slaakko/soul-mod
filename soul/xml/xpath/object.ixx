// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.xpath.object;

import std.core;
import soul.xml.node;

export namespace soul::xml::xpath {

enum class ObjectKind 
{
    nodeSet, boolean, number, string
};

class Object
{
public:
    Object(ObjectKind kind_);
    virtual ~Object();
    ObjectKind Kind() const { return kind; }
    bool IsNodeSet() const { return kind == ObjectKind::nodeSet; }
    bool IsBoolean() const { return kind == ObjectKind::boolean; }
    bool IsNumber() const { return kind == ObjectKind::number; }
    bool IsString() const { return kind == ObjectKind::string; }
private:
    ObjectKind kind;
};

class NodeSet : public Object
{
public:
    NodeSet();
    const std::vector<std::unique_ptr<soul::xml::Node>>& Nodes() const { return nodes; }
    int Length() const { return nodes.size(); }
    void Add(soul::xml::Node* node);
private:
    std::vector<std::unique_ptr<soul::xml::Node>> nodes;
};

class Boolean : public Object
{
public:
    Boolean();
    Boolean(bool value_);
    bool Value() const { return value; }
private:
    bool value;
};

class Number : public Object
{
public:
    Number();
    Number(double value_);
    double Value() const { return value; }
private:
    double value;
};

class String : public Object
{
public:
    String();
    String(const std::string& value_);
    const std::string& Value() const { return value; }
private:
    std::string value;
};

} // namespace soul::xml::xpath
