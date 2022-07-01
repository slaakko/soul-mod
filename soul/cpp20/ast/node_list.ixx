// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.node.list;

import std.core;

export namespace soul::cpp20::ast {

template<typename T>
class NodeList
{
public:
    NodeList() {}
    NodeList(const NodeList&) = delete;
    NodeList& operator=(const NodeList&) = delete;
    int Count() const { return nodes.size(); }
    bool IsEmpty() const { return nodes.empty(); }
    void Clear() { nodes.clear(); }
    T* operator[](int index) const { return nodes[index].get(); }
    void Add(T* node)
    {
        nodes.push_back(std::unique_ptr<T>(node));
    }
    T* Release(int index)
    {
        return nodes[index].release();
    }
    std::vector<std::unique_ptr<T>>& Nodes() { return nodes; }
private:
    std::vector<std::unique_ptr<T>> nodes;
};

} // namespace soul::cpp20::ast
