// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module util.process;

namespace util {

int RunProcess(const char* commandLine)
{
    return ort_run_process(commandLine);
}

} // namespace util
