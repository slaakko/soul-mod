// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <chrono>
#include <boost/process.hpp>

int main(int argc, const char** argv)
{
    try
    {
        std::string command;
        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];
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
        int64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
        std::cout << ms << " milliseconds elapsed" << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
