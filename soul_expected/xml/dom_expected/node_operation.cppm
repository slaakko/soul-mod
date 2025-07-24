// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul_expected.xml.node.operation;

import std;
import soul_expected.xml.node;

export namespace soul_expected::xml {

class NodeOperation
{
public:
    virtual ~NodeOperation();
    virtual void Apply(Node* node) = 0;
};

} // namespace soul_expected::xml
