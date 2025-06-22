// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.node.list;

import std;

export namespace otava::ast {

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
    std::vector<std::unique_ptr<T>>::iterator begin() { return nodes.begin(); }
    std::vector<std::unique_ptr<T>>::const_iterator begin() const { return nodes.begin(); }
    std::vector<std::unique_ptr<T>>::const_iterator cbegin() const { return nodes.cbegin(); }
    std::vector<std::unique_ptr<T>>::iterator end() { return nodes.end(); }
    std::vector<std::unique_ptr<T>>::const_iterator end() const { return nodes.end(); }
    std::vector<std::unique_ptr<T>>::const_iterator cehnd() const { return nodes.cend(); }
private:
    std::vector<std::unique_ptr<T>> nodes;
};

} // namespace otava::ast
