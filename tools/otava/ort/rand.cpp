// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module ort.rand;

import util;

std::uint32_t ort_random()
{
    return util::Random();
}

std::uint64_t ort_random64()
{
    return util::Random64();
}
