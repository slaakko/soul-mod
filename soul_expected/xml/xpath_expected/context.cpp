// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul_expected.xml.xpath.context;

namespace soul_expected::xml::xpath {

Context::Context(soul_expected::xml::Node* node_, int pos_, int size_) : node(node_), pos(pos_), size(size_)
{
}

} // namespace soul_expected::xml::xpath
