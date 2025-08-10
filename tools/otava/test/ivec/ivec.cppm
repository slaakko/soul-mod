export module ivec;

import std;

template class std::vector<int>;

export void print_ivec(const std::vector<int>& v)
{
    bool first = true;
    for (int x : v)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            std::cout << ", ";
        }
        std::cout << x;
    }
    std::cout << "\n";
}
