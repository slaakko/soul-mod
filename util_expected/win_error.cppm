// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.win_error;

import std;

export namespace util {

std::expected<std::string, int> WindowsErrorMessage(std::uint64_t errorCode);

int ErrorNumber();

} // util
