import std.core;

int main()
{
    auto ex = static_cast<std::exception*>(get_exception());
    return 0;
}
