// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

import gendoc.project;
import std.core;
import util;

std::string Version()
{
    return "4.1.0";
}

void PrintHelp()
{

}

int main(int argc, const char** argv)
{
    try
    {
        util::Init();
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