import std;

int main()
{
    std::vector<std::pair<std::int32_t, std::string>> files;
    int file = 0;
    std::string filePath = "file";
    files.push_back(std::make_pair(file, filePath));
    for (const auto& p : files)
    {
        std::cout << p.first << ":" << p.second << "\n";
    }
}
