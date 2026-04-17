import std;

struct Predicate
{
    Predicate(const std::string& s_) : s(s_) {}
    std::string s;
};

void Partition(Predicate p)
{
}

int main()
{
    std::string s = "abc";
    Partition(Predicate(s));
}
