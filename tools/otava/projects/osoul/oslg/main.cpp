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
import soul.lexer;
import soul.lex;

std::string Version()
{
    return "5.0.0";
}

void PrintHelp()
{
    std::cout << "Otava Soul Lexer Generator (oslg) version " << Version() << "\n";
    std::cout << "Usage: oslg [options] { FILE.oslg }" << "\n";
    std::cout << "\n";
    std::cout << "Options:" << "\n";
    std::cout << "\n";
    std::cout << "--help | -h" << "\n";
    std::cout << "  Print help and exit." << "\n";
    std::cout << "\n";
    std::cout << "--debug | -d" << "\n";
    std::cout << "  Generate debug files." << "\n";
    std::cout << "\n";
    std::cout << "--verbose | -v" << "\n";
    std::cout << "  Be verbose." << "\n";
    std::cout << "\n";
    std::cout << "\n";
}

int main(int argc, const char** argv)
{
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
                std::cerr << "unknown option '" << "'" << "\n";
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
                    case 'd':
                    {
                        debug = true;
                        break;
                    }
                    case 'v':
                    {
                        verbose = true;
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
            std::expected<std::string, int> rv = util::GetFullPath(arg);
            if (!rv)
            {
                std::cerr << util::GetErrorMessage(rv.error()) << "\n";
                return 1;
            }
            files.push_back(std::move(*rv));
        }
    }
    if (files.empty())
    {
        std::cerr << "no files given" << "\n";
        PrintHelp();
        return 1;
    }
    soul::lexer::FileMap fileMap;
    for (const std::string& file : files)
    {
        if (verbose)
        {
            std::cout << "> " << file << std::endl;
        }
        std::expected<std::unique_ptr<soul::ast::slg::SlgFile>, int> rv = soul::slg::ParseSlgFile(file, fileMap);
        if (!rv)
        {
            std::cerr << util::GetErrorMessage(rv.error()) << "\n";
            return 1;
        }
        std::unique_ptr<soul::ast::slg::SlgFile> slgFile = std::move(*rv);
        std::expected<bool, int> grv = soul::slg::GenerateLexer(slgFile.get(), fileMap, verbose, debug);
        if (!grv)
        {
            std::cerr << util::GetErrorMessage(grv.error()) << "\n";
            return 1;
        }
    }
}
