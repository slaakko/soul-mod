import std;

template<typename T>
class Node
{
public:
    Node() : ptr(nullptr) {}
    Node(T* ptr_) : ptr(ptr_) {}
    T& operator*() { return *ptr; }
    const T& operator*() const { return *ptr; }
private:
    T* ptr;
};

int main()
{
    double d = 1.0;
    Node<double> n(&d);
    int i = static_cast<int>(*n);
    std::cout << i << "\n";
}
