// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util_expected.init.done;

import util_expected.ansi;
import util_expected.socket;

namespace util {

std::expected<bool, int> Init()
{
    std::expected<bool, int> rv = util::SocketInit();
    if (!rv) return rv;
    util::AnsiInit();
    return std::expected<bool, int>(true);
}

void Done()
{
    util::AnsiDone();
    util::SocketDone();
}

} // namespace util
