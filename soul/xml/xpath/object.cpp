// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.xml.xpath.object;

namespace soul::xml::xpath {

Object::Object(ObjectKind kind_) : kind(kind_)
{
}

Object::~Object()
{
}

NodeSet::NodeSet() : Object(ObjectKind::nodeSet)
{
}

void NodeSet::Add(soul::xml::Node* node)
{
    nodes.push_back(std::unique_ptr<soul::xml::Node>(node));
}

Boolean::Boolean() : Object(ObjectKind::boolean), value(false)
{
}

Boolean::Boolean(bool value_) : Object(ObjectKind::boolean), value(value_)
{
}

Number::Number() : Object(ObjectKind::number), value(0.0)
{
}

Number::Number(double value_) : Object(ObjectKind::number), value(value_)
{
}

String::String() : Object(ObjectKind::string), value()
{
}

String::String(const std::string& value_) : Object(ObjectKind::string), value(value_)
{
}

} // namespace soul::xml::xpath
