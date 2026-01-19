// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.node.map;

import util;

namespace otava::ast {

NodeMap::NodeMap()
{
}

void NodeMap::AddNode(Node* node)
{
    nodeMap[node->InternalId()] = node;
}

std::expected<Node*, int> NodeMap::GetNode(std::int64_t nodeId) const
{
    auto it = nodeMap.find(nodeId);
    if (it != nodeMap.cend())
    {
        return std::expected<Node*, int>(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.ast.node_map: node id " + std::to_string(nodeId) + " not found"));
    }
}

} // namespace otava::ast
