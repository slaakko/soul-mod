// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import std;
// import std.filesystem;
import util;
import soul.ast.slg;
import soul.slg.file.parsers;
import soul.slg.lexer.generator;
import soul.slg.classmap;
import soul.common.module_map;

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
    std::cout << "Soul Lexer Generator (slg) version " << Version() << std::endl;
    std::cout << "Usage: slg [options] { FILE.slg }" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
    std::cout << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
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
        for (const std::string& file : files)
        {
            if (verbose)
            {
                std::cout << "> " << file << std::endl;
            }
            std::unique_ptr<soul::ast::slg::SlgFile> slgFile = soul::slg::ParseSlgFile(file);
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
            soul::slg::GenerateLexer(slgFile.get(), verbose, moduleMap, ppstyle);
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
