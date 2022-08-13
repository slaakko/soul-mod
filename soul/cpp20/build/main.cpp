// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import util;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.symbols.writer;
import soul.cpp20.project.build;
import soul.cpp20.project.init;
import soul.cpp20.project.parser;
import soul.cpp20.proj.ast;

void PrintHelp()
{
    // todo
}

int main(int argc, const char** argv)
{
    try
    {
        util::Init();
        soul::cpp20::project::init::Init init;
        bool verbose = false;
        bool multithreaded = false;
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
                else if (arg == "--multithreaded")
                {
                    multithreaded = true;
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
                        case 'm':
                        {
                            multithreaded = true;
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
            std::unique_ptr<soul::cpp20::proj::ast::Project> project = soul::cpp20::project::parser::ParseProjectFile(file);
            soul::cpp20::project::build::BuildFlags buildFlags = soul::cpp20::project::build::BuildFlags::none;
            if (verbose)
            {
                buildFlags = buildFlags | soul::cpp20::project::build::BuildFlags::verbose;
            }
            if (multithreaded)
            {
                buildFlags = buildFlags | soul::cpp20::project::build::BuildFlags::multithreadedBuild;
            }
            soul::cpp20::project::build::Build(init.moduleMapper, project.get(), buildFlags);
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
