export module otava.ast.node.list;

import std;

export namespace otava::ast {

template<typename T>
class NodeList
{
public:
    inline NodeList() noexcept {}
    NodeList(const NodeList&) = delete;
    NodeList& operator=(const NodeList&) = delete;
    inline int Count() const noexcept { return nodes.size(); }
    inline bool IsEmpty() const noexcept { return nodes.empty(); }
    inline void Clear() noexcept { nodes.clear(); }
    inline T* operator[](int index) const noexcept { return nodes[index].get(); }
    inline void Add(T* node)
    {
        nodes.push_back(std::unique_ptr<T>(node));
    }
    inline T* Release(int index)
    {
        return nodes[index].release();
    }
    void Insert(int index, T* node)
    {
        nodes.insert(nodes.begin() + index, std::unique_ptr<T>(node));
    }
    inline std::vector<std::unique_ptr<T>>& Nodes() noexcept { return nodes; }
    inline std::vector<std::unique_ptr<T>>::iterator begin() noexcept { return nodes.begin(); }
    inline std::vector<std::unique_ptr<T>>::const_iterator begin() const noexcept { return nodes.begin(); }
    inline std::vector<std::unique_ptr<T>>::const_iterator cbegin() const noexcept { return nodes.cbegin(); }
    inline std::vector<std::unique_ptr<T>>::iterator end() noexcept { return nodes.end(); }
    inline std::vector<std::unique_ptr<T>>::const_iterator end() const noexcept { return nodes.end(); }
    inline std::vector<std::unique_ptr<T>>::const_iterator cehnd() const noexcept { return nodes.cend(); }
private:
    std::vector<std::unique_ptr<T>> nodes;
};

} // namespace otava::ast
