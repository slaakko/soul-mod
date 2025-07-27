// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.xpath.context;

import std;
import soul_expected.xml.node;

export namespace soul_expected::xml::xpath {

class Context
{
public:
    Context(soul_expected::xml::Node* node_, int pos_, int size_);
    soul_expected::xml::Node* Node() const { return node; }
    int Pos() const { return pos; }
    int Size() const { return size; }
private:
    soul_expected::xml::Node* node;
    int pos;
    int size;
};

} // namespace soul_expected::xml::xpath
