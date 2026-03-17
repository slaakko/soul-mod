import std.filesystem;
import std.core;

int main()
{
    std::filesystem::path defaultPath;
    bool defaultExists = std::filesystem::exists(defaultPath);
    std::cout << defaultExists << "\n";
    std::filesystem::path work("D:/work");
    bool workExists = std::filesystem::exists(work);
    std::cout << workExists << "\n";
    bool work2Exists = std::filesystem::exists("D:/work");
    std::cout << work2Exists << "\n";
    return 0;
}
