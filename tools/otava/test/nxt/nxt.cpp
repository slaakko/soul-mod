import std;

template<typename IterT>
constexpr IterT nxt(IterT it, typename std::iterator_traits<IterT>::difference_type n = 1)
{
    return it;
}

int main()
{
    int* it = nullptr;
    it = nxt<int*>(it);
}
