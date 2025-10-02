// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module std.rt;

namespace std {

rt_init::rt_init()
{
    stdin = static_cast<FILE*>(&stdin_);
    stdout = static_cast<FILE*>(&stdout_);
    stderr = static_cast<FILE*>(&stderr_);
}

rt_init init_rt;

} // namespace std
