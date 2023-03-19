// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.node.map;

import std.core;
import otava.ast.node;

export namespace otava::ast {

class NodeMap
{
public:
    NodeMap();
    void AddNode(Node* node);
    Node* GetNode(int64_t nodeId) const;
private:
    std::map<int64_t, Node*> nodeMap;
};

} // namespace otava::ast
