import std;
import soul.xml.parser;
import soul.xml.processor;

std::string Version()
{
    return "5.0.0";
}

void PrintHelp()
{
    std::cout << "XML statistics collector version " << Version() << "\n";
    std::cout << "Usage: " << "oxml_stats [options] { FILE.xml }\n";
    std::cout << "options:" << "\n";
    std::cout << "--help | -h" << "\n";
    std::cout << "  Print help and exit." << "\n";
    std::cout << "--verbose | -v" << "\n";
    std::cout << "  Be verbose." << "\n";
}

class XmlStatisticsCollector : public soul::xml::XmlContentHandler
{
public:
    XmlStatisticsCollector();
    std::expected<bool, int> Comment(const soul::ast::SourcePos& sourcePos, const std::string& comment) override;
    std::expected<bool, int> PI(const soul::ast::SourcePos& sourcePos, const std::string& target, const std::string& data) override;
    std::expected<bool, int> Text(const soul::ast::SourcePos& sourcePos, const std::string& text) override;
    std::expected<bool, int> CDataSection(const soul::ast::SourcePos& sourcePos, const std::string& cdata) override;
    std::expected<bool, int> StartElement(const soul::ast::SourcePos& sourcePos, const std::string& namespaceUri, const std::string& localName,
        const std::string& qualifiedName, const soul::xml::processor::Attributes& attributes) override;
    std::expected<bool, int> SkippedEntity(const soul::ast::SourcePos& sourcePos, const std::string& entityName) override;
    void Print();
private:
    int comments;
    int processingInstructions;
    int textNodes;
    int cdataSections;
    int elements;
    int numAttributes;
    int skippedEntities;
};

XmlStatisticsCollector::XmlStatisticsCollector() : comments(0), processingInstructions(0), textNodes(0), cdataSections(0), elements(0), numAttributes(0), skippedEntities(0)
{
}

std::expected<bool, int> XmlStatisticsCollector::Comment(const soul::ast::SourcePos& sourcePos, const std::string& comment)
{
    ++comments;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlStatisticsCollector::PI(const soul::ast::SourcePos& sourcePos, const std::string& target, const std::string& data)
{
    ++processingInstructions;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlStatisticsCollector::Text(const soul::ast::SourcePos& sourcePos, const std::string& text)
{
    ++textNodes;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlStatisticsCollector::CDataSection(const soul::ast::SourcePos& sourcePos, const std::string& cdata)
{
    ++cdataSections;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlStatisticsCollector::StartElement(const soul::ast::SourcePos& sourcePos, const std::string& namespaceUri, const std::string& localName,
    const std::string& qualifiedName, const soul::xml::processor::Attributes& attributes)
{
    ++elements;
    numAttributes += static_cast<int>(attributes.GetAttributes().size());
    return std::expected<bool, int>(true);
}

std::expected<bool, int> XmlStatisticsCollector::SkippedEntity(const soul::ast::SourcePos& sourcePos, const std::string& entityName)
{
    ++skippedEntities;
    return std::expected<bool, int>(true);
}

void XmlStatisticsCollector::Print(const std::string& file, bool verbose)
{
    if (verbose)
    {
        std::cout << "file '" << file << "' XML statistics:" << std::endl;
    }
    std::cout << comments << " comments" << "\n";
    std::cout << processingInstructions << " processing instructions" << "\n";
    std::cout << textNodes << " text nodes" << "\n";
    std::cout << cdataSections << " character data sections" << "\n";
    std::cout << elements << " elements" << "\n";
    std::cout << numAttributes << " attributes" << "\n";
    std::cout << skippedEntities << " skipped entities" << "\n";
    std::cout << "\n";
}

std::expected<bool, int> PrintStatistics(const std::string& xmlFileName, bool verbose)
{
    XmlStatisticsCollector statisticsCollector;
    std::expected<bool, int> rv = soul::xml::parser::ParseXmlFile(xmlFileName, &statisticsCollector);
    if (!rv) return rv;
    statisticsCollector.Print(xmlFileName, verbose);
    return std::expected<bool, int>(true);
}

int main(int argc, const char** argv)
{
    bool verbose = false;
    std::vector<std::string> files;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg.starts_with("--"))
        {
            if (arg == "--verbose")
            {
                verbose = true;
            }
            else if (arg == "--help")
            {
                PrintHelp();
                return 0;
            }
            else
            {
                std::cerr << "unknown option '" << arg << "'" << std::endl;
                return 1;
            }
        }
        else if (arg.starts_with("-"))
        {
            std::string options = arg.substr(1);
            for (char o : options)
            {
                switch (o)
                {
                    case 'v':
                    {
                        verbose = true;
                        break;
                    }
                    case 'h':
                    {
                        PrintHelp();
                        return 0;
                    }
                    default:
                    {
                        std::cerr << "unknown option '-" << std::string(1, o) << "'" << std::endl;
                        return 1;
                    }
                }
            }
        }
        else
        {
            std::expected<std::string, int> rv = util::GetFullPath(arg);
            if (!rv)
            {
                std::cerr << util::GetErrorMessage(rv.error()) << std::endl;
                return 1;
            }
            files.push_back(*rv);
        }
    }
    if (files.empty())
    {
        std::cerr << "no files given" << std::endl;
        return 1;
    }
    for (const auto& file : files)
    {
        std::expected<bool, int> rv = PrintStatistics(file, verbose);
        if (!rv)
        {
            std::cerr << util::GetErrorMessage(rv.error()) << std::endl;
            return 1;
        }
    }
}
