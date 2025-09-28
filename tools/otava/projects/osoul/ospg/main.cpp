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
    std::cout << "Otava Soul Parser Generator (ospg) version " << Version() << "\n";
    std::cout << "Usage: ospg [options] { FILE.ospg }" << "\n";
    std::cout << "\n";
    std::cout << "Options:" << "\n";
    std::cout << "\n";
    std::cout << "--help | -h" << "\n";
    std::cout << "  Print help and exit." << "\n";
    std::cout << "\n";
    std::cout << "--verbose | -v" << "\n";
    std::cout << "  Be verbose." << "\n";
    std::cout << "\n";
    std::cout << "--no-debug-support | -n" << "\n";
    std::cout << "  Do not generate parser debugging code." << "\n";
    std::cout << "\n";
    std::cout << "--optimize | -o" << "\n";
    std::cout << "  Do switch optimization." << "\n";
    std::cout << "\n";
}

int main(int argc, const char** argv)
{
    bool verbose = false;
    bool noDebugSupport = false;
    bool optimize = false;
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
            else
            {
                std::cerr << "unknown option '" << arg << "'" << "\n";
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
                    default:
                    {
                        std::cerr << "unknown option '-" << std::string(1, o) << "'" << "\n";
                        return 1;
                    }
                }
            }
        }
        else
        {
            auto u = util::GetFullPath(arg);
            if (!u)
            {
                std::cerr << util::GetErrorMessage(u.error()) << "\n";
                return 1;
            }
            files.push_back(*u);
        }
    }
    soul::lexer::FileMap fileMap;
    for (const std::string& file : files)
    {
        std::expected<std::unique_ptr<soul::ast::spg::SpgFile>, int> rv = soul::spg::ParseSpgFile(file, fileMap, verbose);
        if (!rv)
        {
            std::cerr << util::GetErrorMessage(rv.error()) << "\n";
            return 1;
        }
        std::unique_ptr<soul::ast::spg::SpgFile> spgFile = std::move(*rv);
        std::expected<bool, int> grv = soul::spg::GenerateParsers(spgFile.get(), fileMap, verbose, noDebugSupport, optimize, false, Version());
        if (!grv)
        {
            std::cerr << util::GetErrorMessage(grv.error()) << "\n";
            return 1;
        }
    }
}
