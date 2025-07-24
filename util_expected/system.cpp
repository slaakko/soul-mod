// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#ifdef _WIN32
#include <Windows.h>
#endif

module util_expected.system;

import util_expected.error;

namespace util {

std::expected<std::string, int> GetPathToExecutable()
{
    char buf[4096];
    DWORD result = GetModuleFileNameA(NULL, buf, sizeof(buf));
    if (result == 0)
    {
        return std::unexpected<int>(AllocateError("could not get path to current executable: GetModuleFileName failed"));
    }
    return std::expected<std::string, int>(std::string(buf));
}

} // util