// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#ifdef _WIN32
#include <Windows.h>
#endif

module util_expected.win_error;

import util_expected.unicode;

namespace util {

std::expected<std::string, int> WindowsErrorMessage(std::uint64_t errorCode)
{
#ifdef _WIN32
    char16_t buf[4096];
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, static_cast<DWORD>(errorCode), LANG_SYSTEM_DEFAULT, (LPWSTR)buf, 4096, nullptr);
    return ToUtf8(buf);
#else
    return std::expected<std::string, int>(std::to_string(errorCode));
#endif
}

int ErrorNumber()
{
    return errno;
}

} // util
