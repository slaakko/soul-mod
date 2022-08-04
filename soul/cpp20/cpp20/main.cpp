// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import util;
import soul.lexer.test;
import soul.cpp20.ast;
import soul.cpp20.lexer;
import cpp20.parser.spg.rules;
import soul.cpp20.symbols.modules;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.context;
import soul.cpp20.parser.translation.unit;

std::string Version()
{
    return "5.0.0";
}

void PrintHelp()
{
    std::cout << "C++20 tester version " << Version() << std::endl;
    std::cout << "usage: cpp20 [options] { FILE.cpp | FILE.ixx }" << std::endl;
    std::cout << "options:" << std::endl;
    std::cout << "--verbose | -v" << std::endl;
    std::cout << "  Be verbose." << std::endl;
    std::cout << "--help | -h" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
    std::cout << "--lex | -l" << std::endl;
    std::cout << "  Do lexical analysis." << std::endl;
    std::cout << "--parse | -p" << std::endl;
    std::cout << "  Parse." << std::endl;
    std::cout << "--source | -s" << std::endl;
    std::cout << "  Generate source." << std::endl;
    std::cout << "--xml | -x" << std::endl;
    std::cout << "  Generate XML." << std::endl;
}

int main(int argc, const char** argv)
{
    try
    {
        util::Init();
        bool verbose = false;
        bool lex = false;
        bool parse = false;
        bool source = false;
        bool xml = false;
        std::vector<std::string> fileNames;
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
                else if (arg == "--lex")
                {
                    lex = true;
                }
                else if (arg == "--parse")
                {
                    parse = true;
                }
                else if (arg == "--source")
                {
                    source = true;
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
                        case 'h':
                        {
                            PrintHelp();
                            return 1;
                        }
                        case 'l':
                        {
                            lex = true;
                            break;
                        }
                        case 'p':
                        {
                            parse = true;
                            break;
                        }
                        case 's':
                        {
                            source = true;
                            break;
                        }
                        case 'x':
                        {
                            xml = true;
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
                fileNames.push_back(util::GetFullPath(arg));
            }
        }
        for (const auto& fileName : fileNames)
        {
            util::CodeFormatter formatter(std::cout);
            std::string content = util::ReadFile(fileName);
            std::u32string ucontent = util::ToUtf32(content);
            auto lexer = soul::cpp20::lexer::MakeLexer(ucontent.c_str(), ucontent.c_str() + ucontent.length(), fileName);
            lexer.SetRuleNameMapPtr(::cpp20::parser::spg::rules::GetRuleNameMapPtr());
            if (verbose)
            {
                std::cout << "> " << fileName << std::endl;
            }
            if (lex)
            {
                soul::lexer::TestLexer(lexer, formatter);
            }
            if (parse)
            {
                soul::cpp20::symbols::ModuleMapper moduleMapper;
                soul::cpp20::symbols::SymbolTable symbolTable;
                soul::cpp20::symbols::Context context;
                context.SetLexer(&lexer);
                context.SetSymbolTable(&symbolTable);
                std::unique_ptr<soul::cpp20::ast::Node> translationUnit = soul::cpp20::parser::translation::unit::TranslationUnitParser<decltype(lexer)>::Parse(lexer, &context);
                if (source)
                {
                    soul::cpp20::ast::PrintSource(*translationUnit, std::cout);
                }
                if (xml)
                {
                    soul::cpp20::ast::PrintXml(*translationUnit, std::cout);
                }
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
