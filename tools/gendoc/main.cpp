// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

import std;
import util;
import gendoc.project;
import otava.symbols;
import otava.symbols.init;
import otava.symbols.expr.parser;
import otava.symbols.stmt.parser;
import otava.symbols.decl_specifier_seq.parser;
import otava.parser.recorded.parse;
import otava.expr.parser;
import otava.stmt.parser;
import otava.decl_specifier_seq.parser;

std::string Version()
{
    return "5.0.0";
}

void PrintHelp()
{
    std::cout << "gendoc reference documentation generator version " << Version() << "\n";
    std::cout << "usage: gendoc [options] [paths]" << "\n";
    std::cout << "options:\n";
    std::cout << "--verbose | -v" << "\n";
    std::cout << "  Be verbose." << "\n";
    std::cout << "--force | -f" << "\n";
    std::cout << "  Rebuild although up to date." << "\n";
    std::cout << "--help | -h" << "\n";
    std::cout << "  Print help and exit." << "\n";
    std::cout << "paths:\n";
    std::cout << "  If no paths are given and current directory contains 'gendoc.xml' file, process it." << "\n";
    std::cout << "  If paths to gendoc.xml's are given, process them in order." << "\n";
}

int main(int argc, const char** argv)
{
    try
    {
        util::Init();
        otava::symbols::Init();
        otava::parser::recorded::parse::Init();
        otava::symbols::SetExprParser(otava::parser::ParseExpression);
        otava::symbols::SetStmtParser(otava::parser::ParseStatement);
        otava::symbols::SetDeclarationSpecifierSequenceParser(otava::parser::ParseDeclarationSpecifierSequence);
        bool verbose = false;
        bool force = false;
        bool multithreaded = false;
        std::vector<std::string> paths;
        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];
            if (arg.starts_with("--"))
            {
                if (arg == "--verbose")
                {
                    verbose = true;
                }
                else if (arg == "--force")
                {
                    force = true;
                }
                else if (arg == "--multithreaded")
                {
                    multithreaded = true;
                }
                else if (arg == "--help")
                {
                    PrintHelp();
                    return 1;
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
                        case 'v':
                        {
                            verbose = true;
                            break;
                        }
                        case 'f':
                        {
                            force = true;
                            break;
                        }
                        case 'm':
                        {
                            multithreaded = true;
                            break;
                        }
                        case 'h':
                        {
                            PrintHelp();
                            return 1;
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
                paths.push_back(arg);
            }
        }
        if (paths.empty())
        {
            paths.push_back(std::string());
        }
        for (const auto& path : paths)
        {
            gendoc::BuildProject(path, verbose, force, multithreaded);
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    util::Done();
    return 0;
}
