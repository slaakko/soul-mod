import std;
import std.filesystem;
import soul.xml.dom;
import soul.xml.dom.parser;
import soul.xml.xpath;
import util.path;
import util.code.formatter;

void PrintHelp()
{

}

void ProcessFile(const std::string& filePath)
{
    std::string root = util::Path::GetDirectoryName(filePath);
    std::unique_ptr<soul::xml::Document> doc = soul::xml::ParseXmlFile(filePath);
    std::unique_ptr<soul::xml::xpath::NodeSet> compileItems = soul::xml::xpath::EvaluateToNodeSet("/Project/ItemGroup/ClCompile", doc.get());
    int n = compileItems->Count();
    for (int i = 0; i < n; ++i)
    {
        soul::xml::Node* node = compileItems->GetNode(i);
        if (node->IsElementNode())
        {
            soul::xml::Element* element = static_cast<soul::xml::Element*>(node);
            std::string includeAttribute = element->GetAttribute("Include");
            if (!includeAttribute.empty())
            {
                std::filesystem::path p = std::filesystem::path(root) / includeAttribute;
                if (p.extension() == ".ixx")
                {
                    std::filesystem::path q = p;
                    q.replace_extension(".cppm");
                    std::string fileName = p.stem().generic_string() + ".cppm";
                    element->SetAttribute("Include", fileName);
                    std::filesystem::rename(p, q);
                    std::cout << p.generic_string() << " --> " << q.generic_string() << "\n";
                }
            }
        }
    }
}

int main(int argc, const char** argv)
{
    try
    {
        bool verbose = false;
        std::vector<std::string> files;
        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];
            if (arg.starts_with("--"))
            {
                if (arg == "--help")
                {
                    PrintHelp();
                    return 1;
                }
                else if (arg == "--verbose")
                {
                    verbose = true;
                }
                else
                {
                    throw std::runtime_error("unknown option '" + arg + "'");
                }
            }
            else if (arg.starts_with("-"))
            {
                std::string options = arg.substr(1);
                for (char o : options)
                {
                    switch (o)
                    {
                        case 'h':
                        {
                            PrintHelp();
                            return 1;
                        }
                        case 'v':
                        {
                            verbose = true;
                            break;
                        }
                        default:
                        {
                            throw std::runtime_error("unknown option '-" + std::string(1, o) + "'");
                        }
                    }
                }
            }
            else
            {
                files.push_back(util::GetFullPath(arg));
            }
        }
        if (files.empty())
        {
            throw std::runtime_error("no files given");
        }
        for (const std::string& file : files)
        {
            ProcessFile(file);
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}