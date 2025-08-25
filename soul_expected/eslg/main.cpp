// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import std;
import util_expected;
import soul_expected.ast.slg;
import soul_expected.slg.file.parsers;
import soul_expected.slg.lexer.generator;
import soul_expected.slg.classmap;
import soul_expected.lexer;

std::expected<bool, int> Init()
{
    return util::Init();
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
    std::cout << "Soul Expected Style Lexer Generator (eslg) version " << Version() << std::endl;
    std::cout << "Usage: eslg [options] { FILE.slg }" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
    std::cout << std::endl;
    std::cout << "--debug | -d" << std::endl;
    std::cout << "  Generate debug files." << std::endl;
    std::cout << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

int main(int argc, const char** argv)
{
    std::expected<bool, int> rv = Init();
    if (!rv)
    {
        std::cerr << util::GetErrorMessage(rv.error()) << "\n";
        return 1;
    }
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
                std::cerr << "unknown option '" << + "'" << "\n";
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
    soul_expected::lexer::FileMap fileMap;
    for (const std::string& file : files)
    {
        if (verbose)
        {
            std::cout << "> " << file << std::endl;
        }
        std::expected<std::unique_ptr<soul_expected::ast::slg::SlgFile>, int> rv = soul_expected::slg::ParseSlgFile(file, fileMap);
        if (!rv)
        {
            std::cerr << util::GetErrorMessage(rv.error()) << "\n";
            return 1;
        }
        std::unique_ptr<soul_expected::ast::slg::SlgFile> slgFile = std::move(*rv);
        std::expected<bool, int> grv = soul_expected::slg::GenerateLexer(slgFile.get(), fileMap, verbose, debug);
        if (!grv)
        {
            std::cerr << util::GetErrorMessage(grv.error()) << "\n";
            return 1;
        }
    }
    Done();
}
