// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import util;
import soul.ast.slg;
import soul.slg.file.parsers;
import soul.slg.lexer.generator;

void Init()
{
    util::Init();
}

void Done()
{
    util::Done();
}

void PrintHelp()
{
    
}

int main(int argc, const char** argv)
{
/*
    std::string root = GetFullPath("C:\\work\\soul-mod\\soul\\slg");
    std::string classMapName = "soul.slg.lex.classmap";
    MakeClassMap(root, classMapName, 0x110000);
    MakeResourceFile(root, classMapName);
*/
    try
    {
        Init();
        bool verbose = false;
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
            soul::slg::GenerateLexer(slgFile.get(), verbose);
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    Done();
}
