// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module ort;

import std.core;

export extern "C" void prints(const char* s, int handle);
export extern "C" void flush_handle(int handle);
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
export extern "C" void* open_file(const char* path, const char* mode);
export extern "C" int close_file(void* stream);
export extern "C" int get_char(void* stream);
export extern "C" int put_char(int character, void* stream);
export extern "C" int read_file(void* ptr, size_t size, size_t count, void* stream);
export extern "C" int write_file(void* ptr, size_t size, size_t count, void* stream);
export extern "C" int eof_file(void* stream);
export extern "C" int flush_file(void* stream);
export extern "C" int error_file(void* stream);
export extern "C" int seek_file(void* stream, int offset, int origin);
export extern "C" int tell_file(void* stream);
export extern "C" char* str_error(int errnum);
export extern "C" int error_number();
export extern "C" void destroy_str(const char* str);
