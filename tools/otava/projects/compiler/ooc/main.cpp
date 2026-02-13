// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import std;
import util;

std::string Version()
{
    return "5.0.0";
}

void PrintHelp()
{
    std::cout << "Usage: ooc [options] { FILE.project | FILE.solution }" << "\n";
    std::cout << "Options:" << "\n";
    std::cout << "--help | -h" << "\n";
    std::cout << "  Print help and exit." << "\n";
    std::cout << "--verbose | -v" << "\n";
    std::cout << "  Be verbose." << "\n";
}

int Action(int argc, const char** argv)
{
    std::cout << "************************************************" << "\n";
    std::cout << "* Otava (for Otava) C++ Compiler version " << Version() << " *" << "\n";
    std::cout << "************************************************" << "\n";
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
            bool unknownOpt = false;
            char opt = ' ';
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
                        unknownOpt = true;
                        opt = o;
                        break;
                    }
                }
            }
            if (unknownOpt)
            {
                throw std::runtime_error("unknown option '-" + std::string(1, opt) + "'");
            }
        }
        else
        {
            files.push_back(util::GetFullPath(arg));
        }
    }
    return 0;
}

int main(int argc, const char** argv)
{
    try
    {
        return Action(argc, argv);
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}
