// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.file.util;

import std;

export namespace util {

std::expected<bool, int> CopyFile(const std::string& source, const std::string& dest, bool force, bool verbose);

} // namespace util
