// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.system;

import util.error;

namespace util {

std::expected<std::string, int> GetPathToExecutable()
{
    char buf[4096];
    bool result = ort_get_path_to_executable(buf, 4096);
    if (result)
    {
        return std::expected<std::string, int>(std::string(buf));
    }
    else
    {
        std::uint32_t error = ort_get_last_windows_error();
        ort_get_windows_error_message(error, buf, 4096);
        std::string msg(buf);
        return std::unexpected<int>(AllocateError("could not get path to current executable: " + msg));
    }
}

} // util
