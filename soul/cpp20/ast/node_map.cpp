// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.node.map;

namespace soul::cpp20::ast {

NodeMap::NodeMap()
{
}

void NodeMap::Clear()
{
    nodeMap.clear();
}

void NodeMap::AddNode(Node* node)
{
    nodeMap[node->Id()] = node;
}

Node* NodeMap::GetNode(int32_t nodeId) const
{
    auto it = nodeMap.find(nodeId);
    if (it != nodeMap.cend())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("soul.cpp20.ast.node_map: node id " + std::to_string(nodeId) + " not found");
    }
}

} // namespace soul::cpp20::ast
