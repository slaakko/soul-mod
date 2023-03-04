// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import solution_file.ast;
import util.path;

std::string version = "1.0.0";

void PrintHelp()
{
    std::cout << "slines version " << version << std::endl;
    std::cout << "usage: slines [options] { file.sln | file.vcxproj | file.ixx | file.cpp }" << std::endl;
    std::cout << "print number of source lines in solution, project, or source file." << std::endl;
    std::cout << "options:" << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
}

int main(int argc, const char** argv)
{
    try
    {
        bool verbose = false;
        std::vector<std::string> files;
        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];
            if (arg.starts_with("--"))
            {
                if (arg == "--verbose")
                {
                    verbose = true;
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
        for (const auto& file : files)
        {
            if (file.ends_with(".sln"))
            {
                std::unique_ptr<solution_file::ast::Solution> solution = solution_file::ast::ParseSolutionFile(file);
                solution_file::ast::ProcessSolution(solution.get());
            }
            else if (file.ends_with(".vcxproj"))
            {
                // todo
            }
            else if (file.ends_with(".ixx") || file.ends_with(".cpp"))
            {
                // todo
            }
            else
            {
                throw std::runtime_error("unknown file extension '" + util::Path::GetExtension(file) + "'");
            }
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
