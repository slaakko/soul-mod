// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.system;

import std;

export namespace util {

std::expected<std::string, int> GetPathToExecutable();

} // util;
