import std.core;
import rb_tree;

int main()
{
    rb_tree<int, int, std::identity<int>, std::less<int>> tree;
    tree.insert(1);
    auto it = tree.find(1);
    tree.erase(it);
    rb_tree<int, int, std::identity<int>, std::less<int>> cp(tree);
    rb_tree<int, int, std::identity<int>, std::less<int>> mv(std::move(cp));
    rb_tree<int, int, std::identity<int>, std::less<int>> second;
    second = tree;
    rb_tree<int, int, std::identity<int>, std::less<int>> third;
    rb_tree<int, int, std::identity<int>, std::less<int>> fourth;
    fourth.insert(2);
    third = std::move(fourth);
    return 0;
}
