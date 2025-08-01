// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.xml.xpath.context;

import std;
import soul.xml.node;

export namespace soul::xml::xpath {

class Context
{
public:
    Context(soul::xml::Node* node_, int pos_, int size_);
    inline soul::xml::Node* Node() const { return node; }
    inline int Pos() const { return pos; }
    inline int Size() const { return size; }
private:
    soul::xml::Node* node;
    int pos;
    int size;
};

} // namespace soul::xml::xpath
