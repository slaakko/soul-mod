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

std::string Version()
{
    return "4.1.0";
}

void PrintHelp()
{
    std::cout << "soul.cpp20.build.cpp20build version " << Version() << std::endl;
    std::cout << "Usage: cpp20build [options] { FILE.project | FILE.solution }" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
    std::cout << "--multithreaded | -m" << std::endl;
    std::cout << "  Build using all cores." << std::endl;
    std::cout << "--debug-parse | -d" << std::endl;
    std::cout << "  Print source parsing log to \"parse.log\" file located in the current working directory." << std::endl;
}

int main(int argc, const char** argv)
{
    try
    {
        util::Init();
        soul::cpp20::project::init::Init init;
        bool verbose = false;
        bool multithreaded = false;
        bool debugParse = false;
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
                else if (arg == "--debug-parse")
                {
                    debugParse = true;
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
                        case 'd':
                        {
                            debugParse = true;
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
            if (file.ends_with(".project"))
            {
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
                if (debugParse)
                {
                    buildFlags = buildFlags | soul::cpp20::project::build::BuildFlags::debugParse;
                }
                soul::cpp20::project::build::Build(init.moduleMapper, project.get(), buildFlags);
            }
            else if (file.ends_with(".solution"))
            {
                std::unique_ptr<soul::cpp20::proj::ast::Solution> solution = soul::cpp20::project::parser::ParseSolutionFile(file);
                soul::cpp20::project::build::BuildFlags buildFlags = soul::cpp20::project::build::BuildFlags::none;
                if (verbose)
                {
                    buildFlags = buildFlags | soul::cpp20::project::build::BuildFlags::verbose;
                }
                if (multithreaded)
                {
                    buildFlags = buildFlags | soul::cpp20::project::build::BuildFlags::multithreadedBuild;
                }
                soul::cpp20::project::build::Build(init.moduleMapper, solution.get(), buildFlags);
            }
            else
            {
                throw std::runtime_error("file '" + file + "' has invalid extension: not .project or .solution");
            }
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
