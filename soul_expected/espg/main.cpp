// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import soul_expected.ast.spg;
import soul_expected.spg.file.parsers;
import soul_expected.lexer.file.map;
import soul_expected.spg.parser.generator;
import std;
import util_expected;

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
    std::cout << "Soul Expected Style Parser Generator (espg) version " << Version() << std::endl;
    std::cout << "Usage: espg [options] { FILE.spg }" << std::endl;
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

int main(int argc, const char** argv)
{
    std::expected<bool, int> irv = Init();
    if (!irv)
    {
        std::cerr << util::GetErrorMessage(irv.error()) << "\n";
        return 1;
    }
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
                    case 'x':
                    {
                        xml = true;
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
    soul_expected::lexer::FileMap fileMap;
    for (const std::string& file : files)
    {
        std::expected<std::unique_ptr<soul_expected::ast::spg::SpgFile>, int> rv = soul_expected::spg::ParseSpgFile(file, fileMap, verbose);
        if (!rv)
        {
            std::cerr << util::GetErrorMessage(rv.error()) << "\n";
            return 1;
        }
        std::unique_ptr<soul_expected::ast::spg::SpgFile> spgFile = std::move(*rv);
        std::expected<bool, int> grv = soul_expected::spg::GenerateParsers(spgFile.get(), fileMap, verbose, noDebugSupport, optimize, xml, Version());
        if (!grv)
        {
            std::cerr << util::GetErrorMessage(grv.error()) << "\n";
            return 1;
        }
    }
    Done();
}
