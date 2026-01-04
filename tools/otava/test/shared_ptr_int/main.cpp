import std;

template class std::shared_ptr<int>;

int main()
{
    std::shared_ptr<int> s0;
    std::cout << s0.use_count() << "\n";
    std::shared_ptr<int> s1(new int(1));
    std::cout << s1.use_count() << "\n";
    std::shared_ptr<int> s2(s1);
    std::cout << s1.use_count() << "\n";
    std::cout << s2.use_count() << "\n";
}
