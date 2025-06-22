// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.node.map;

namespace otava::ast {

NodeMap::NodeMap()
{
}

void NodeMap::AddNode(Node* node)
{
    nodeMap[node->Id()] = node;
}

Node* NodeMap::GetNode(std::int64_t nodeId) const
{
    auto it = nodeMap.find(nodeId);
    if (it != nodeMap.cend())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("otava.ast.node_map: node id " + std::to_string(nodeId) + " not found");
    }
}

} // namespace otava::ast
