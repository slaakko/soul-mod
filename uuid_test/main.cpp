import std.core;
import util.uuid;
import util.rand;

int main()
{
    util::set_rand_seed(0);
    std::set<util::uuid> s;
    int n = 100'000'000;
    for (int i = 0; i < n; ++i)
    {
        util::uuid id = util::random_uuid();
        if (s.find(id) != s.cend())
        {
            std::cout << "found!" << std::endl;
        }
        s.insert(id);
    }
    return 0;
}