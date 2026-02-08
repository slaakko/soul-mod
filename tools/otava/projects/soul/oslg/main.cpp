// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import std;
import util;
import soul.ast.slg;
import soul.slg.file.parsers;
import soul.slg.lexer.generator;
import soul.slg.classmap;
import soul.lexer.file.map;

std::string Version()
{
    return "5.0.0";
}

void PrintHelp()
{
    std::cout << "Soul Lexer Generator for Otava (oslg) version " << Version() << std::endl;
    std::cout << "Usage: oslg [options] { FILE.slg }" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
    std::cout << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
    std::cout << std::endl;
    std::cout << "--debug | -d" << std::endl;
    std::cout << "  Generate debug files." << std::endl;
    std::cout << std::endl;
}
 
int Action(int argc, const char** argv)
{
    soul::lexer::FileMap fileMap;
    bool verbose = false;
    bool debug = false;
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
            else if (arg == "--debug")
            {
                debug = true;
            }
            else
            {
                throw std::runtime_error("unknown option '" + arg + "'");
            }
        }
        else if (arg.starts_with("-"))
        {
            std::string options = arg.substr(1);
            bool optNotFound = false;
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
                    case 'd':
                    {
                        debug = true;
                        break;
                    }
                    default:
                    {
                        optNotFound = true;
                        opt = o;
                        break;
                    }
                }
            }
            if (optNotFound)
            {
                throw std::runtime_error("unknown option '-" + std::string(1, opt) + "'");
            }
        }
        else
        {
            files.push_back(util::GetFullPath(arg));
        }
    }
    for (const std::string& file : files)
    {
        if (verbose)
        {
            std::cout << "> " << file << std::endl;
        }
        std::unique_ptr<soul::ast::slg::SlgFile> slgFile = soul::slg::ParseSlgFile(file, fileMap);
        soul::slg::GenerateLexer(slgFile.get(), verbose, fileMap, debug);
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
