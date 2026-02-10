// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import std;
import otava.build.parser;
import otava.build.build;
import otava.build_project;
import otava.build_solution;
import otava.symbols.modules;
import otava.symbols.namespaces;
import otava.symbols.compound.type.symbol;
import otava.symbols.conversion.table;
import otava.symbols.type.symbol;
import otava.parser.recorded.parse;
import otava.opt;
import soul.lexer.file.map;
import util;

void PrintHelp()
{
    std::cout << "usage: ooc [options] { FILE.project | FILE.solution }" << std::endl;
    std::cout << "options:" << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
    std::cout << "--config=(debug|release) | -c=(debug|release)" << std::endl;
    std::cout << "  Set configuration to build to 'debug' or 'release'." << std::endl;
    std::cout << "  Default configuration is 'debug'." << std::endl;
    std::cout << "--opt=OPTIMIZATION_LEVEL | -O=OPTIMIZATION_LEVEL" << std::endl;
    std::cout << "  Set optimization level to OPTIMIZATION_LEVEL (0-3)" << std::endl;
    std::cout << "--rebuild | -r" << std::endl;
    std::cout << "  rebuild project" << std::endl;
    std::cout << "--all | -a" << std::endl;
    std::cout << "  build all dependent projects" << std::endl;
    std::cout << "--multithreaded | -m" << std::endl;
    std::cout << "  Build using all cores." << std::endl;
    std::cout << "--debug-parse | -d" << std::endl;
    std::cout << "  Print source parsing log to \"parse.log\" file located in the current working directory." << std::endl;
    std::cout << "--xml | -x" << std::endl;
    std::cout << "  Write ASTs as XML." << std::endl;
    std::cout << "--seed | -s" << std::endl;
    std::cout << "  Initialize uuid seed from hash code of the file path of each project." << std::endl;
    std::cout << "--symbol-xml | -y" << std::endl;
    std::cout << "  Write symbols as XML." << std::endl;
    std::cout << "--debug-memory | -b" << std::endl;
    std::cout << "  Debug memory allocations." << std::endl;
}

std::string Version()
{
    return "5.0.0";
}

int main(int argc, const char** argv)
{
    std::cout << "**********************************************" << "\n";
    std::cout << "* Otava (for Otava) C++ Compiler version " << Version() << "\n";
    std::cout << "**********************************************" << "\n";
    otava::parser::recorded::parse::Init();
    soul::lexer::FileMap fileMap;
    std::vector<std::string> files;
    bool verbose = false;
    bool rebuild = false;
    std::string config = "debug";
    bool multithreaded = false;
    bool debugParse = false;
    bool setSeed = false;
    bool xml = false;
    bool symbolXml = false;
    bool all = false;
    int optLevel = -1;
    bool debugMemory = false;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg.starts_with("--"))
        {
            if (arg.find('=') != std::string::npos)
            {
                std::vector<std::string> components = util::Split(arg, '=');
                if (components.size() == 2)
                {
                    if (components[0] == "--config")
                    {
                        config = components[1];
                    }
                    else if (components[0] == "--opt")
                    {
                        optLevel = std::stoi(components[1]);
                    }
                    else
                    {
                        std::cerr << "unknown option '" + arg + "'" << std::endl;
                        return 1;
                    }
                }
                else
                {
                    std::cerr << "unknown option '" + arg + "'" << std::endl;
                    return 1;
                }
            }
            else
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
                else if (arg == "--rebuild")
                {
                    rebuild = true;
                }
                else if (arg == "--multithreaded")
                {
                    multithreaded = true;
                }
                else if (arg == "--debug-parse")
                {
                    debugParse = true;
                }
                else if (arg == "--seed")
                {
                    setSeed = true;
                }
                else if (arg == "--xml")
                {
                    xml = true;
                }
                else if (arg == "--symbol-xml")
                {
                    symbolXml = true;
                }
                else if (arg == "--all")
                {
                    all = true;
                }
                else if (arg == "--debug-memory")
                {
                    debugMemory = true;
                }
                else
                {
                    std::cerr << "unknown option '" + arg + "'" << std::endl;
                    return 1;
                }
            }
        }
        else if (arg.starts_with("-"))
        {
            if (arg.find('=') != std::string::npos)
            {
                std::vector<std::string> components = util::Split(arg, '=');
                if (components.size() == 2)
                {
                    if (components[0] == "-c")
                    {
                        config = components[1];
                    }
                    else if (components[0] == "-O")
                    {
                        optLevel = std::stoi(components[1]);
                    }
                    else
                    {
                        std::cerr << "unknown option '" + arg + "'" << std::endl;
                        return 1;
                    }
                }
                else
                {
                    std::cerr << "unknown option '" + arg + "'" << std::endl;
                    return 1;
                }
            }
            else
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
                        case 'r':
                        {
                            rebuild = true;
                            break;
                        }
                        case 'a':
                        {
                            all = true;
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
                        case 'x':
                        {
                            xml = true;
                            break;
                        }
                        case 's':
                        {
                            setSeed = true;
                            break;
                        }
                        case 'y':
                        {
                            symbolXml = true;
                            break;
                        }
                        case 'b':
                        {
                            debugMemory = true;
                            break;
                        }
                        default:
                        {
                            std::cerr << "unknown option '-" << std::string(1, o) << "'" << std::endl;
                            return 1;
                        }
                    }
                }
            }
        }
        else
        {
            auto fp = util::GetFullPath(arg);
            if (!fp)
            {
                std::cerr << util::GetErrorMessage(fp.error(), true) << std::endl;
                return 1;
            }
            files.push_back(std::move(*fp));
        }
    }
    if (files.empty())
    {
        std::cerr << "no files given" << std::endl;
        return 1;
    }
    if (config != "debug" && config != "release")
    {
        std::cerr << "unknown configuration (" + config + "): not 'debug' or 'release'" << std::endl;
    }
    if (optLevel != -1)
    {
        std::expected<bool, int> rv = otava::optimizer::Optimizer::Instance().SetOptimizations(std::to_string(optLevel));
        if (!rv)
        {
            std::cerr << util::GetErrorMessage(rv.error(), true) << std::endl;
            return 1;
        }
    }
    if (debugMemory)
    {
        ort_debug_memory();
    }
    for (const auto& file : files)
    {
        if (verbose)
        {
            std::cout << "> " << file << std::endl;
        }
        if (file.ends_with(".project"))
        {
            auto p = otava::build::ParseProjectFile(file);
            if (!p)
            {
                std::cerr << util::GetErrorMessage(p.error(), true) << std::endl;
                return 1;
            }
            std::unique_ptr<otava::build::Project> project = std::move(*p);
            project->SetFileMap(&fileMap);
            otava::build::BuildFlags buildFlags = otava::build::BuildFlags::none;
            if (verbose)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::verbose;
            }
            if (rebuild)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::rebuild;
            }
            if (all)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::all;
            }
            if (multithreaded)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::multithreadedBuild;
            }
            if (debugParse)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::debugParse;
            }
            if (xml)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::xml;
            }
            if (symbolXml)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::symbolXml;
            }
            if (setSeed)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::seed;
            }
            std::set<otava::build::Project*, otava::build::ProjectLess> projectSet;
            auto rv = otava::build::Build(fileMap, project.get(), config, optLevel, buildFlags, projectSet);
            if (!rv)
            {
                std::cerr << util::GetErrorMessage(rv.error(), true) << std::endl;
                return 1;
            }
        }
        else if (file.ends_with(".solution"))
        { 
            auto s = otava::build::ParseSolutionFile(file);
            if (!s)
            {
                std::cerr << util::GetErrorMessage(s.error(), true) << std::endl;
                return 1;
            }
            std::unique_ptr<otava::build::Solution> solution = std::move(*s);
            otava::build::BuildFlags buildFlags = otava::build::BuildFlags::none;
            if (verbose)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::verbose;
            }
            if (rebuild)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::rebuild;
            }
            if (all)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::all;
            }
            if (multithreaded)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::multithreadedBuild;
            }
            if (xml)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::xml;
            }
            if (symbolXml)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::symbolXml;
            }
            if (setSeed)
            {
                buildFlags = buildFlags | otava::build::BuildFlags::seed;
            }
            std::set<otava::build::Project*, otava::build::ProjectLess> projectSet;
            auto rv = otava::build::Build(fileMap, solution.get(), config, optLevel, buildFlags, projectSet);
            if (!rv)
            {
                std::cerr << util::GetErrorMessage(rv.error(), true) << std::endl;
                return 1;
            }
        }
        else
        {
            std::cerr << "file '" << file << "' has invalid extension: not .project or .solution" << std::endl;
            return 1;
        }
    }
    return 0;
}
