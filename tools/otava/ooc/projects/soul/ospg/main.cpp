// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import soul.ast.spg;
import soul.spg.file.parsers;
import soul.lexer.file.map;
import soul.spg.parser.generator;
import std;
import util;

std::string Version()
{
    return "5.0.0";
}

void PrintHelp()
{
    std::cout << "Soul Parser Generator for Otava (ospg) version " << Version() << std::endl;
    std::cout << "Usage: ospg [options] { FILE.spg }" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
    std::cout << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
    std::cout << std::endl;
    std::cout << "--no-debug-support | -n" << std::endl;
    std::cout << "  Do not generate parser debugging code." << std::endl;
    std::cout << std::endl;
    std::cout << "--optimize | -o" << std::endl;
    std::cout << "  Do switch optimization." << std::endl;
    std::cout << std::endl;
    std::cout << "--xml | -x" << std::endl;
    std::cout << "  Generate XML info documents." << std::endl;
    std::cout << std::endl;
}

int Action(int argc, const char** argv)
{
    bool verbose = false;
    bool noDebugSupport = false;
    bool optimize = false;
    bool xml = false;
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
            else if (arg == "--no-debug-support")
            {
                noDebugSupport = true;
            }
            else if (arg == "--optimize")
            {
                optimize = true;
            }
            else if (arg == "--xml")
            {
                xml = true;
            }
            else
            {
                throw std::runtime_error("unknown option '" + arg + "'");
            }
        }
        else if (arg.starts_with("-"))
        {
            std::string options = arg.substr(1);
            char unknownOpt = ' ';
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
                    case 'n':
                    {
                        noDebugSupport = true;
                        break;
                    }
                    case 'o':
                    {
                        optimize = true;
                        break;
                    }
                    case 'x':
                    {
                        xml = true;
                        break;
                    }
                    default:
                    {
                        unknownOpt = o;
                        break;
                    }
                }
                if (unknownOpt != ' ')
                {
                    throw std::runtime_error("unknown option '-" + std::string(1, unknownOpt) + "'");
                }
            }
        }
        else
        {
            files.push_back(util::GetFullPath(arg));
        }
    }
    soul::lexer::FileMap fileMap;
    for (const std::string& file : files)
    {
        std::unique_ptr<soul::ast::spg::SpgFile> spgFile = soul::spg::ParseSpgFile(file, fileMap, verbose);
        soul::spg::GenerateParsers(spgFile.get(), fileMap, verbose, noDebugSupport, optimize, xml, Version());
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
