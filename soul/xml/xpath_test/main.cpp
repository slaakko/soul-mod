// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import soul.xml.document;
import soul.xml.xpath;
import util;

std::string Version()
{
    return "4.0.0";
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
    try
    {
        util::Init();
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
                            throw std::runtime_error("unknown option '-" + std::string(1, o) + "'");
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
            throw std::runtime_error("no XPATH expression given");
        }
        if (xmlFileName.empty())
        {
            throw std::runtime_error("no XML file name given");
        }
        if (verbose)
        {
            std::cout << "> evaluating XPATH expression '" << xpathExpr << "' against XML file '" << xmlFileName << "':" << std::endl;
        }
        std::unique_ptr<soul::xml::Document> infoDoc = soul::xml::xpath::EvaluateToXMLInfoDocument(xpathExpr, xmlFileName);
        util::CodeFormatter formatter(std::cout);
        formatter.SetIndentSize(2);
        infoDoc->Write(formatter);
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    util::Done();
    return 0;
}
