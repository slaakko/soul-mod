import std;
import util_expected;
import soul_expected.xml.dom_expected;
import soul_expected.xml.dom.parser;

std::expected<bool, int> Init()
{
    return util::Init();
}

void Done()
{
    util::Done();
}

int main(int argc, const char** argv)
{
    auto rv = Init();
    if (!rv)
    {
        std::cerr << util::GetErrorMessage(rv.error()) + "\n";
        return 1;
    }
    std::vector<std::string> files;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        files.push_back(arg);
    }
    for (const std::string& file : files)
    {
        std::expected<std::unique_ptr<soul_expected::xml::Document>, int> d = soul_expected::xml::ParseXmlFile(file);
        if (!d)
        {
            std::cerr << util::GetErrorMessage(d.error()) << "\n";
            return 1;
        }
        std::unique_ptr<soul_expected::xml::Document> doc = std::move(*d);
    }
    Done();
}