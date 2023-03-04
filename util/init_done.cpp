// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.init.done;

import util.unicode;
import util.ansi;
import util.time;
import util.socket;

namespace util {

void Init()
{
    util::SocketInit();
    util::AnsiInit();
    util::TimeInit();
}

void Done()
{
    util::TimeDone();
    util::AnsiDone();
    util::SocketDone();
}

} // namespace util
