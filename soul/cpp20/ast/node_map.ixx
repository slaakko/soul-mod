// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.node.map;

import soul.cpp20.ast.node;

export namespace soul::cpp20::ast {

class NodeMap
{
public:
    NodeMap();
    void Clear();
    void AddNode(Node* node);
    Node* GetNode(int32_t nodeId) const;
private:
    std::map<int32_t, Node*> nodeMap;
};

} // namespace soul::cpp20::ast
