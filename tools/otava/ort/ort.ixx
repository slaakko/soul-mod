// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module ort;

import std.core;

export extern "C" void prints(const char* s, int handle);
export extern "C" void flush_file(int handle);
export extern "C" void set_rand_seed(uint64_t seed);
export extern "C" uint8_t get_random_byte();
export extern "C" int save_context(void* ctx);
export extern "C" void restore_context(void* ctx, int retval);
export extern "C" void set_exception(void* ex, uint64_t eth, uint64_t etl);
export extern "C" void* get_exception();
export extern "C" void throw_exception();
export extern "C" bool handle_exception(uint64_t hth, uint64_t htl);
export extern "C" bool is_space(int c);
export extern "C" const char* get_env(const char* env);