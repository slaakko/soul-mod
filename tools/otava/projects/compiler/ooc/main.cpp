// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

import std;
import otava.build.parser;
import otava.build.build;
import otava.build_project;
import otava.build_solution;
import otava.build.config;
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

std::string Version()
{
    return "5.0.0";
}

void PrintHelp()
{
    std::cout << "Usage: ooc [options] { FILE.project | FILE.solution }" << "\n";
    std::cout << "Options:" << "\n";
    std::cout << "--help | -h" << "\n";
    std::cout << "  Print help and exit." << "\n";
    std::cout << "--verbose | -v" << "\n";
    std::cout << "  Be verbose." << "\n";
    std::cout << "--config=(debug|release|trace|CONFIG) | -c=(debug|release|trace|CONFIG)" << "\n";
    std::cout << "  Set configuration to build to 'debug', 'release', 'trace' or user defined configuration CONFIG." << "\n";
    std::cout << "  Default configuration is 'debug'." << "\n";
    std::cout << "--opt=OPTIMIZATION_LEVEL | -O=OPTIMIZATION_LEVEL" << "\n";
    std::cout << "  Set release mode optimization level to OPTIMIZATION_LEVEL (0-3)" << "\n";
    std::cout << "--define=SYMBOL | -d=SYMBOL" << "\n";
    std::cout << "  Define build symbol SYMBOL." << "\n";
    std::cout << "--rebuild | -r" << "\n";
    std::cout << "  rebuild project" << "\n";
    std::cout << "--all | -a" << "\n";
    std::cout << "  build all dependent projects" << "\n";
    std::cout << "--multithreaded | -m" << "\n";
    std::cout << "  Build using all cores." << "\n";
    std::cout << "--debug-parse | -p" << "\n";
    std::cout << "  Print source parsing log to \"parse.log\" file located in the current working directory." << "\n";
    std::cout << "--xml | -x" << "\n";
    std::cout << "  Write ASTs as XML." << "\n";
    std::cout << "--seed | -s" << "\n";
    std::cout << "  Initialize uuid seed from hash code of the file path of each project." << "\n";
    std::cout << "--symbol-xml | -y" << "\n";
    std::cout << "  Write symbols as XML" << "\n";
}

int Action(int argc, const char** argv)
{
    std::cout << "************************************************" << "\n";
    std::cout << "* Otava (for Otava) C++ Compiler version " << Version() << " *" << "\n";
    std::cout << "************************************************" << "\n";
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
                    else if (components[0] == "--define")
                    {
                        otava::build::DefineSymbol(components[1]);
                    }
                    else
                    {
                        otava::symbols::SetExceptionThrown();
                        throw std::runtime_error("unknown option '" + arg + "'");
                    }
                }
                else
                {
                    otava::symbols::SetExceptionThrown();
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
                    otava::symbols::SetExceptionThrown();
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
                    else if (components[0] == "-d")
                    {
                        otava::build::DefineSymbol(components[1]);
                    }
                    else
                    {
                        otava::symbols::SetExceptionThrown();
                        throw std::runtime_error("unknown option '" + arg + "'");
                    }
                }
                else
                {
                    otava::symbols::SetExceptionThrown();
                    throw std::runtime_error("unknown option '" + arg + "'");
                }
            }
            else
            {
                std::string options = arg.substr(1);
                bool unknownOpt = false;
                char opt = ' ';
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
                            unknownOpt = true;
                            opt = o;
                            break;
                        }
                    }
                }
                if (unknownOpt)
                {
                    otava::symbols::SetExceptionThrown();
                    throw std::runtime_error("unknown option '-" + std::string(1, opt) + "'");
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
        otava::symbols::SetExceptionThrown();
        throw std::runtime_error("no files given");
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
    return 0;
}

int main(int argc, const char** argv)
{
    try
    {
        return Action(argc, argv);
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    catch (const otava::symbols::Exception& ex)
    {
        std::cerr << ex.Message() << std::endl;
        return 1;
    }
}
