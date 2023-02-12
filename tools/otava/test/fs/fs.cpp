import std.filesystem;
import std.core;

int main()
{
    std::filesystem::path defaultPath;
    bool defaultExists = std::filesystem::exists(defaultPath);
    std::filesystem::path work("C:/work");
    bool workExists = std::filesystem::exists(work);
    return 0;
}
