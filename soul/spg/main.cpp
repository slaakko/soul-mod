// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import util;
import soul.ast.spg;
import soul.spg.file.parsers;
import soul.lexer.file.map;
import soul.spg.parser.generator;

void Init()
{
    util::Init();
}

void Done()
{
    util::Done();
}

std::string Version()
{
    return "4.1.0";
}

void PrintHelp()
{
    std::cout << "Soul Parser Generator (spg) version " << Version() << std::endl;
    std::cout << "Usage: spg [options] { FILE.spg }" << std::endl;
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
}

int main(int argc, const char** argv)
{
    try
    {
        Init();
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
                else if (arg == "xml")
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
                        case 'o' :
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
        soul::lexer::FileMap fileMap;
        for (const std::string& file : files)
        {
            std::unique_ptr<soul::ast::spg::SpgFile> spgFile = soul::spg::ParseSpgFile(file, fileMap, verbose);
            soul::spg::GenerateParsers(spgFile.get(), fileMap, verbose, noDebugSupport, optimize, xml, Version());
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    Done();
}
