// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.rand;

import std;

export namespace util {

void set_rand_seed(std::uint64_t seed);
void reset_rng();
std::uint8_t get_random_byte();

} // namespace util
