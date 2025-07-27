// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <boost/process.hpp>

std::string MakeExecutableArg(const std::string& arg)
{
    std::filesystem::path p(arg);
    if (!std::filesystem::exists(p))
    {
        if (!p.has_extension())
        {
            std::string b = p.generic_string();
            b.append(".exe");
            if (std::filesystem::exists(b))
            {
                p = b;
            }
            else
            {
                std::string b = p.generic_string();
                b.append(".bat");
                if (std::filesystem::exists(b))
                {
                    p = b;
                }
            }
        }
    }
    if (std::filesystem::exists(p))
    {
        if (p.extension() == ".bat")
        {
            std::string cmd = "cmd /C \"" + p.generic_string() + "\"";
            return cmd;
        }
    }
    return p.generic_string();
}

int main(int argc, const char** argv)
{
    try
    {
        std::string command;
        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];
            if (i == 1)
            {
                arg = MakeExecutableArg(arg);
            }
            if (i > 1)
            {
                command.append(" ");
            }
            command.append(arg);
        }
        auto start = std::chrono::steady_clock::now();
        boost::process::system(command);
        auto end = std::chrono::steady_clock::now();
        std::chrono::steady_clock::duration elapsed = end - start;
        std::int64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << ms << " milliseconds elapsed" << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
