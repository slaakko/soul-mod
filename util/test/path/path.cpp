import std.core;
import std.filesystem;
import util.unicode;

int main()
{
    std::filesystem::path f = util::SoulRoot();
    f /= "util";
    return 0;
}
