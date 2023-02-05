// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import otava.build.parser;
import otava.build.build;
import otava.build_project;
import otava.build_solution;
import otava.symbols.init;
import otava.symbols.modules;
import otava.symbols.namespaces;
import otava.symbols.compound.type.symbol;
import otava.symbols.conversion.table;
import otava.parser.recorded.parse;
import util.init.done;
import util.unicode;
import util.path;
import util.text.util;
import util.rand;
import util.uuid;

void PrintHelp()
{
    std::cout << "usage: oc [options] { FILE.project | FILE.solution }" << std::endl;
    std::cout << "options:" << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
    std::cout << "--config=(debug|release) | -c=(debug|release)" << std::endl;
    std::cout << "  Set configuration to build to 'debug' or 'release'." << std::endl;
    std::cout << "  Default configuration is 'debug'." << std::endl;
    std::cout << "--multithreaded | -m" << std::endl;
    std::cout << "  Build using all cores." << std::endl;
    std::cout << "--debug-parse | -d" << std::endl;
    std::cout << "  Print source parsing log to \"parse.log\" file located in the current working directory." << std::endl;
    std::cout << "--xml | -x" << std::endl;
    std::cout << "  Write ASTs as XML." << std::endl;
    std::cout << "--seed | -s" << std::endl;
    std::cout << "  Initialize uuid seed to 0." << std::endl;
}

int main(int argc, const char** argv)
{
    try
    {
        util::Init();
        otava::symbols::Init();
        otava::parser::recorded::parse::Init();
        otava::symbols::ModuleMapper moduleMapper;
        std::vector<std::string> files;
        bool verbose = false;
        std::string config = "debug";
        bool multithreaded = false;
        bool debugParse = false;
        bool setSeed = false;
        bool xml = false;
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
                        else
                        {
                            throw std::runtime_error("unknown option '" + arg + "'");
                        }
                    }
                    else
                    {
                        throw std::runtime_error("unknown option '" + arg + "'");
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
                    else
                    {
                        throw std::runtime_error("unknown option '" + arg + "'");
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
                        else
                        {
                            throw std::runtime_error("unknown option '" + arg + "'");
                        }
                    }
                    else
                    {
                        throw std::runtime_error("unknown option '" + arg + "'");
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
                            default:
                            {
                                throw std::runtime_error("unknown option '-" + std::string(1, o) + "'");
                            }
                        }
                    }
                }
            }
            else
            {
                files.push_back(util::GetFullPath(arg));
            }
        }
        if (files.empty())
        {
            throw std::runtime_error("no files given");
        }
        if (config != "debug" && config != "release")
        {
            throw std::runtime_error("unknown configuration (" + config + "): not 'debug' or 'release'");
        }
        if (setSeed)
        {
            util::set_rand_seed(0);
        }
        for (const auto& file : files)
        {
            if (verbose)
            {
                std::cout << "> " << file << std::endl;
            }
            if (file.ends_with(".project"))
            {
                std::unique_ptr<otava::build::Project> project = otava::build::ParseProjectFile(file);
                otava::build::BuildFlags buildFlags = otava::build::BuildFlags::none;
                if (verbose)
                {
                    buildFlags = buildFlags | otava::build::BuildFlags::verbose;
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
                otava::build::Build(moduleMapper, project.get(), config, buildFlags);
            }
            else if (file.ends_with(".solution"))
            {
                std::unique_ptr<otava::build::Solution> solution = otava::build::ParseSolutionFile(file);
                otava::build::BuildFlags buildFlags = otava::build::BuildFlags::none;
                if (verbose)
                {
                    buildFlags = buildFlags | otava::build::BuildFlags::verbose;
                }
                if (multithreaded)
                {
                    buildFlags = buildFlags | otava::build::BuildFlags::multithreadedBuild;
                }
                if (xml)
                {
                    buildFlags = buildFlags | otava::build::BuildFlags::xml;
                }
                otava::build::Build(moduleMapper, solution.get(), config, buildFlags);
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
