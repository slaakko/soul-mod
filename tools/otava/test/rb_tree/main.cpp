import std.core;
import rb_tree;

int main()
{
    rb_tree<int, int, std::identity<int>, std::less<int>> tree;
    tree.insert(1);
    return 0;
}
