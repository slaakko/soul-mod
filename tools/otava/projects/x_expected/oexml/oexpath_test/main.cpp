// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import std;
import soul.xml.document;
import soul.xml.xpath;
import util;

std::string Version()
{
    return "5.0.0";
}

void PrintHelp()
{
    std::cout << "XPATH tester version " << Version() << std::endl;
    std::cout << "Executes an XPATH expression against an XML file and prints the results." << std::endl;
    std::cout << "Usage: xpath_test [options] <xpath_expr> <xml_file_name>" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
}

int main(int argc, const char** argv)
{
    bool verbose = false;
    std::string xpathExpr;
    std::string xmlFileName;
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
                return 1;
            }
            else
            {
                std::cerr << "unknown option '" + arg + "'" << "\n";
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
                        return 1;
                    }
                    default:
                    {
                        std::cerr << "unknown option '-" + std::string(1, o) + "'" << "\n";
                        return 1;
                    }
                }
            }
        }
        else
        {
            if (xpathExpr.empty())
            {
                xpathExpr = arg;
            }
            else if (xmlFileName.empty())
            {
                xmlFileName = arg;
            }
        }
    }
    if (xpathExpr.empty())
    {
        std::cerr << "no XPATH expression given" << "\n";
    }
    if (xmlFileName.empty())
    {
        std::cerr << "no XML file name given" << "\n";
    }
    if (verbose)
    {
        std::cout << "> evaluating XPATH expression '" << xpathExpr << "' against XML file '" << xmlFileName << "':" << std::endl;
    }
    auto rv = soul::xml::xpath::EvaluateToXMLInfoDocument(xpathExpr, xmlFileName);
    if (!rv)
    {
        std::cerr << util::GetErrorMessage(rv.error()) << "\n";
        return 1;
    }
    std::unique_ptr<soul::xml::Document> infoDoc = std::move(*rv);
    util::CodeFormatter formatter(std::cout);
    formatter.SetIndentSize(2);
    auto wrv = infoDoc->Write(formatter);
    if (!wrv)
    {
        std::cerr << util::GetErrorMessage(wrv.error()) << "\n";
        return 1;
    }
    return 0;
}
