// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module ort;

import std.core;

export extern "C" void prints(const char* s, int handle);
export extern "C" void set_rand_seed(uint64_t seed);
export extern "C" uint8_t get_random_byte();
export extern "C" void throw_exception(void* ex);

