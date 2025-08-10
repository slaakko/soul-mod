// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module ort.rand;

import std;

export extern "C" std::uint32_t ort_random();
export extern "C" std::uint64_t ort_random64();
