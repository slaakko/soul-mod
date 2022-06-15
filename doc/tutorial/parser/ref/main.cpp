// main.cpp:

import std.core;
import util;
import soul.lexer;
import soul.lexer.xml.parsing.log;
import minilang.ast;
import minilang.lexer;
import minilang.parser;

void TestLexer(const std::string& fileName, bool verbose)
{
    util::CodeFormatter formatter(std::cout);
    if (verbose)
    {
        formatter.WriteLine("testing lexer with file:");
        formatter.WriteLine("> " + fileName);
    }
    std::string content = util::ReadFile(fileName);
    std::u32string ucontent = util::ToUtf32(content);
    auto lexer = minilang::lexer::MakeLexer(ucontent.c_str(), ucontent.c_str() + ucontent.length(), fileName);
    soul::lexer::TestLexer(lexer, formatter);
}

void TestParser(const std::string& fileName, bool verbose)
{
    util::CodeFormatter formatter(std::cout);
    if (verbose)
    {
        formatter.WriteLine("testing parser with file:");
        formatter.WriteLine("> " + fileName);
    }
    std::string content = util::ReadFile(fileName);
    std::u32string ucontent = util::ToUtf32(content);
    auto lexer = minilang::lexer::MakeLexer(ucontent.c_str(), ucontent.c_str() + ucontent.length(), fileName);
    lexer.SetRuleNameMapPtr(minilang::spg::rules::GetRuleNameMapPtr());
    soul::lexer::XmlParsingLog log(std::cout); // set the SOUL_PARSER_DEBUG_SUPPORT preprocessing symbol in the parser project settings to enable logging.
    lexer.SetLog(&log);
    std::unique_ptr<minilang::ast::SourceFileNode> sourceFile = minilang::parser::source::file::SourceFileParser<decltype(lexer)>::Parse(lexer);
}

enum class Command
{
    testLexer, testParser
};

void PrintHelp()
{
    std::cout << "minilang example" << std::endl;
    std::cout << "usage: minilang [options] { FILE.minilang }" << std::endl;
    std::cout << "options:" << std::endl;
    std::cout << "--verbose | -v:" << std::endl;
    std::cout << "  Be verbose." << std::endl;
    std::cout << "--help | -h:" << std::endl;
    std::cout << "  Print help and exit." << std::endl;
    std::cout << "--test-lexer | -l:" << std::endl;
    std::cout << "  Test lexer." << std::endl;
    std::cout << "--test-parser | -p:" << std::endl;
    std::cout << "  Test parser." << std::endl;
}

int main(int argc, const char** argv)
{
    try
    {
        util::Init();
        std::vector<std::string> fileNames;
        bool verbose = false;
        Command command = Command::testLexer;
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
                else if (arg == "--test-lexer")
                {
                    command = Command::testLexer;
                }
                else if (arg == "--test-parser")
                {
                    command = Command::testParser;
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
                            command = Command::testLexer;
                            break;
                        }
                        case 'p':
                        {
                            command = Command::testParser;
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
        if (fileNames.empty())
        {
            throw std::runtime_error("no files given");
        }
        for (const auto& fileName : fileNames)
        {
            switch (command)
            {
                case Command::testLexer:
                {
                    TestLexer(fileName, verbose);
                    break;
                }
                case Command::testParser:
                {
                    TestParser(fileName, verbose);
                    break;
                }
                default:
                {
                    throw std::runtime_error("unknown command");
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
