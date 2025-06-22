// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import soul.ast.spg;
import soul.spg.file.parsers;
import soul.lexer.file.map;
import soul.spg.parser.generator;
import soul.common.module_map;
import std.core;
import std.filesystem;
import util;

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
    return "5.0.0";
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
    std::cout << "--xml | -x" << std::endl;
    std::cout << "  Generate XML info documents." << std::endl;
    std::cout << std::endl;
    std::cout << "--ppstyle | -p" << std::endl;
    std::cout << "  Generate old preprocessor style code." << std::endl;
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
        bool ppstyle = false;
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
                else if (arg == "--ppstyle")
                {
                    ppstyle = true;
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
                        case 'p':
                        {
                            ppstyle = true;
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
            soul::common::ModuleMap moduleMap;
            std::string moduleMapFilePath;
            if (ppstyle)
            {
                moduleMapFilePath = util::Path::ChangeExtension(file, ".mm");
                std::string root = util::Path::GetDirectoryName(util::GetFullPath(moduleMapFilePath));
                moduleMap.SetRoot(root);
                if (std::filesystem::exists(moduleMapFilePath))
                {
                    moduleMap.Read(moduleMapFilePath);
                }
            }
            soul::spg::GenerateParsers(spgFile.get(), fileMap, verbose, noDebugSupport, optimize, xml, ppstyle, Version(), moduleMap);
            if (ppstyle)
            {
                moduleMap.Write(moduleMapFilePath);
            }
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    Done();
}
