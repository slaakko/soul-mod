// =================================
// Copyright (c) 2026 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util_expected.init.done;

import std;

export namespace util {

std::expected<bool, int> Init();
void Done();

} // namespace util
