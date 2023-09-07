// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

import std.core;
import soul.json;
import util;

std::string Version()
{
    return "5.0.0";
}

void PrintHelp()
{
    std::cout << "JSON parser version " << Version() << "\n";
    std::cout << "usage: jsonp [options] { FILE... ]" << "\n";
    std::cout << "Parse given JSON files and write their contents to FILE.out files." << "\n";
    std::cout << "options:" << "\n";
    std::cout << "--help | -h" << "\n";
    std::cout << "  Print help and exit." << "\n";
    std::cout << "--verbose | -v" << "\n";
    std::cout << "  Be verbose." << "\n";
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
                if (arg == "--help")
                {
                    PrintHelp();
                    return 1;
                }
                else if (arg == "--verbose")
                {
                    verbose = true;
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
            if (verbose)
            {
                std::cout << "> " << file << "\n";
            }
            std::string jsonText = util::ReadFile(file);
            std::unique_ptr<util::JsonObject> object = soul::json::ParseJsonObject(jsonText, file);
            std::string outputFilePath = file + ".out";
            std::ofstream outputFile(outputFilePath);
            util::CodeFormatter formatter(outputFile);
            object->Write(formatter);
            if (verbose)
            {
                std::cout << "==> " << outputFilePath << "\n";
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
