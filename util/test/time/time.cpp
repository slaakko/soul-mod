import std.core;
import util;

int main()
{
    util::DateTime dt = util::GetCurrentDateTime();
    std::cout << dt.ToString() << "\n";
    return 0;
}
