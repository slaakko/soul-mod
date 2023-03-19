import std.core;
import std.filesystem;
import util.unicode;

int main()
{
    std::filesystem::path f = util::SoulRoot();
    f /= "util";
    std::cout << f.generic_string() << "\n";
    return 0;
}

