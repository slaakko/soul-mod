// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import std;
import otava.build.parser;
import otava.build.build;
import otava.build_project;
import otava.build_solution;
import otava.symbols.init;
import otava.symbols.expr.parser;
import otava.symbols.stmt.parser;
import otava.symbols.decl_specifier_seq.parser;
import otava.symbols.modules;
import otava.symbols.namespaces;
import otava.symbols.compound.type.symbol;
import otava.symbols.conversion.table;
import otava.symbols.type.symbol;
import otava.parser.recorded.parse;
import otava.expr.parser;
import otava.stmt.parser;
import otava.decl_specifier_seq.parser;
import otava.opt;
import soul.lexer.file.map;
import util;

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
    std::cout << "--opt=OPTIMIZATION_LEVEL | -O=OPTIMIZATION_LEVEL" << std::endl;
    std::cout << "  Set release mode optimization level to OPTIMIZATION_LEVEL (0-3)" << std::endl;
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
    std::cout << "  Write symbols as XML" << std::endl;
}

std::string Version()
{
    return "5.0.0";
}

int main(int argc, const char** argv)
{
    try
    {
        std::cout << "****************************************" << "\n";
        std::cout << "* Otava C++ Compiler version " << Version() << "\n";
        std::cout << "****************************************" << "\n";
        util::Init();
        otava::symbols::Init();
        otava::parser::recorded::parse::Init();
        otava::symbols::SetExprParser(otava::parser::ParseExpression);
        otava::symbols::SetStmtParser(otava::parser::ParseStatement);
        otava::symbols::SetDeclarationSpecifierSequenceParser(otava::parser::ParseDeclarationSpecifierSequence);
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
                        else if (components[0] == "-O")
                        {
                            optLevel = std::stoi(components[1]);
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
        if (optLevel != -1)
        {
            otava::optimizer::Optimizer::Instance().SetOptimizations(std::to_string(optLevel));
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
                otava::build::Build(fileMap, project.get(), config, optLevel, buildFlags, projectSet);
            }
            else if (file.ends_with(".solution"))
            {
                std::unique_ptr<otava::build::Solution> solution = otava::build::ParseSolutionFile(file);
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
                otava::build::Build(fileMap, solution.get(), config, optLevel, buildFlags, projectSet);
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
